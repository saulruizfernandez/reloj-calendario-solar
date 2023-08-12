/**
 * @file reloj-solar.cc
 * @author Saúl Ruiz Fernández (ruizfernandezsaul@gmail.com)
 * @brief Definición de los métodos de la clase RelojSolar
 * @version 0.1
 * @date 2023-07-04
 *
 * @copyright Copyright (c) 2023
 *
 */

#include "reloj-solar.h"

/**
 * @brief Función que calcula el Local Standard Time Meridian (LSTM), referencia
 * para una zona horaria concreta
 *
 * @return lstm
 */
int RelojSolar::Lstm(const int utc) const {
  int lstm{15 * utc};
  return lstm;
}

/**
 * @brief Fución que calcula la Equation of Time (EoT), corrige la excentricidad
 * de la óribita y el ángulo de inclinación del eje de rotación
 *
 * @return eot
 */
double RelojSolar::Eot(const int dias_desde_inicio_de_year) const {
  double b{(360 / 365.0) * (dias_desde_inicio_de_year - 81)};
  double eot{(9.87 * sin(2 * b * M_PI / 180) - (7.53 * cos(b * M_PI / 180)) -
              (1.5 * sin(b * M_PI / 180)))};
  return eot;
}

/**
 * @brief Función que calcula el Time Correction Factor (TC), corrige la
 * variación del LST por la longitud de la zona horaria
 *
 * @return tc
 */
double RelojSolar::Tc(const double longitud, const int lstm,
                      const double eot) const {
  double tc{4 * (longitud - lstm) + eot};
  return tc;
}

/**
 * @brief Función que calcula el Local Solar Time (LST)
 *
 * @return lst
 */
double RelojSolar::Lst(const int lt, const double tc) const {
  double lst{lt + (tc / 60.0)};
  return lst;
}

/**
 * @brief Función que calcula el Hour Angle (HRA), convierte la hora solar local
 * (LST) en los grados que se mueve el sol en el cielo. El 0 se corresponde con
 * las 12 am por la manana es negativo, y por la tarde positivo
 *
 * @return hra
 */
double RelojSolar::Hra(const double lst) const {
  double hra{15 * (lst - 12)};
  return hra;
}

/**
 * @brief Función que calcula el ángulo de declinación del sol
 *
 * @return dec
 */
double RelojSolar::Dec(const int d) const {
  double dec{23.45 * sin((360 / 365.0) * (d - 81) * M_PI / 180)};
  return dec;
}

/**
 * @brief Función que calcula la altitud del sol
 *
 * @return altitud
 */
long double RelojSolar::Altitud(const double dec, const double latitud,
                           const double hra) const {
  long double altitud{asin(((sin(dec * M_PI / 180) * sin(latitud * M_PI / 180)) +
                       cos(dec * M_PI / 180) * cos(latitud * M_PI / 180) *
                           cos(hra * M_PI / 180))) *
                 180 / M_PI};
  return altitud;
}

/**
 * @brief Función que calcula el acimut del sol
 *
 * @return acimut
 */
long double RelojSolar::Acimut(const double dec, const double latitud,
                          const double hra, const long double altitud) const {
  long double cuenta{(sin(dec * M_PI / 180) * cos(latitud * M_PI / 180) -
                 cos(dec * M_PI / 180) * sin(latitud * M_PI / 180) *
                     cos(hra * M_PI / 180)) /
                cos(altitud * M_PI / 180)};
  if (cuenta > 1.0)
    cuenta = 1.0;
  else if (cuenta < -1)
    cuenta = -1.0;
  long double acimut{0.0};
  if (hra >= 0)
    acimut = 360 - (acos(cuenta) * 180 / M_PI);
  else
    acimut = acos(cuenta) * 180 / M_PI;
  return acimut;
}

/**
 * @brief Función que calcula la hora de la salida del sol
 *
 * @return salida
 */
int RelojSolar::Salida(const double latitud, const double declinacion,
                       const double tc) const {
  int salida{static_cast<int>(
      floor(12.0 -
            ((1 / 15.0) * 180 / M_PI *
             acos(-tan(latitud * M_PI / 180) * tan(declinacion * M_PI / 180))) -
            (tc / 60.0)))};
  return salida;
}

/**
 * @brief Función que calcula la hora de la puesta del sol
 *
 * @return puesta
 */
int RelojSolar::Puesta(const double latitud, const double declinacion,
                       const double tc) const {
  int puesta{static_cast<int>(
      ceil(12.0 +
           ((1 / 15.0) * 180 / M_PI *
            acos(-tan(latitud * M_PI / 180) * tan(declinacion * M_PI / 180))) -
           (tc / 60.0)))};
  return puesta;
}

/**
 * @brief Función que calcula la longitude de la sombra del gnomon
 *
 * @return longitud_sombra
 */
double RelojSolar::LongitudSombra(const double altitud,
                                  const double altura_gnomon) const {
  double longitud_sombra{altura_gnomon / tan(altitud * M_PI / 180)};
  return longitud_sombra;
}

/**
 * @brief Función que calcula el punto (x, y) donde se proyecta la sombra en un
 * instante
 *
 * @return punto
 */
Punto RelojSolar::CalculaPunto(const double longitud_sombra,
                               const double acimut) const {
  Punto punto;
  const double angulo{((acimut + 180.0) < 360.0) ? (acimut + 180.0)
                                                 : (acimut - 180.0)};
  double modulo_x;
  double modulo_y;
  // Distingo los cuatro cuadrantes en los que se puede proyectar la sombra
  if (angulo >= 0 && angulo < 90) {
    modulo_x = fabs(longitud_sombra * sin(angulo * M_PI / 180));
    modulo_y = fabs(longitud_sombra * cos(angulo * M_PI / 180));
    punto.x = modulo_x;
    punto.y = modulo_y;
  } else if (angulo >= 90 && angulo < 180) {
    modulo_x = fabs(longitud_sombra * sin((180 - angulo) * M_PI / 180));
    modulo_y = fabs(longitud_sombra * cos((180 - angulo) * M_PI / 180));
    punto.x = modulo_x;
    punto.y = -modulo_y;
  } else if (angulo >= 180 && angulo < 270) {
    modulo_x = fabs(longitud_sombra * sin((angulo - 180) * M_PI / 180));
    modulo_y = fabs(longitud_sombra * cos((angulo - 180) * M_PI / 180));
    punto.x = -modulo_x;
    punto.y = -modulo_y;
  } else if (angulo >= 270 && angulo < 360) {
    modulo_x = fabs(longitud_sombra * sin((360 - angulo) * M_PI / 180));
    modulo_y = fabs(longitud_sombra * cos((360 - angulo) * M_PI / 180));
    punto.x = -modulo_x;
    punto.y = modulo_y;
  }
  return punto;
}

/**
 * @brief Función que calcula el ángulo de proyección de la sombra en un reloj vertical
 *
 * @return angulo_vertical
 */
double RelojSolar::ObtenerAnguloVertical(const double altitud, const double acimut) const {
    double angulo_vertical{((acimut >= 270.0 && acimut <= 360.0)? (270.0 - altitud):(90.0 + altitud))};
  return angulo_vertical;
}

/**
 * @brief Función que calcula el punto (x, y) donde se proyecta la sombra en un reloj vertical
 *
 * @return punto_vertical
 */
Punto RelojSolar::CalculaPuntoVertical(const double longitud_sombra, const double angulo_vertical) const {
  double modulo_x, modulo_y;
  Punto punto_vertical;
  if (angulo_vertical >= 180 && angulo_vertical <= 270) {
    modulo_x = fabs(longitud_sombra * sin((angulo_vertical - 180) * M_PI / 180));
    modulo_y = fabs(longitud_sombra * cos((angulo_vertical - 180) * M_PI / 180));
    punto_vertical.x = -modulo_x;
    punto_vertical.y = -modulo_y;
  } else if (angulo_vertical > 90 && angulo_vertical < 180) {
    modulo_x = fabs(longitud_sombra * sin((360 - angulo_vertical) * M_PI / 180));
    modulo_y = fabs(longitud_sombra * cos((360 - angulo_vertical) * M_PI / 180));
    punto_vertical.x = modulo_x;
    punto_vertical.y = -modulo_y;
  }
  return punto_vertical;
}