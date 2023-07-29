/**
 * @file angulos_solares.cc
 * @author Saúl Ruiz Fernández (ruizfernandezsaul@gmail.com)
 * @brief Programa que calcula las posiciones solares a los largo del year
 * @version 0.1
 * @date 2023-07-04
 *
 * @copyright Copyright (c) 2023
 *
 */

#include <cmath>
#include <iostream>
#include <vector>

/**
 * @brief Función que calcula el Local Standard Time Meridian (LSTM), referencia
 * para una zona horaria concreta
 *
 * @return lstm
 */
int Lstm(const int utc) {
  int lstm{15 * utc};
  // std::cout << "lstm: " << lstm << "\n";
  return lstm;
}

/**
 * @brief Fución que calcula la Equation of Time (EoT), corrige la excentricidad
 * de la óribita y el ángulo de inclinación del eje de rotación
 *
 * @return eot
 */
double Eot(const int dias_desde_inicio_de_year) {
  double b{(360 / 365.0) * (dias_desde_inicio_de_year - 81)};
  double eot{(9.87 * sin(2 * b * M_PI / 180) - (7.53 * cos(b * M_PI / 180)) -
              (1.5 * sin(b * M_PI / 180)))};
  // std::cout << "eot: " << eot << "\n";
  return eot;
}

/**
 * @brief Función que calcula el Time Correction Factor (TC), corrige la
 * variación del LST por la longitud de la zona horaria
 *
 * @return tc
 */
double Tc(const double longitud, const int lstm, const double eot) {
  double tc{4 * (longitud - lstm) + eot};
  // std::cout << "tc: " << tc << "\n";
  return tc;
}

/**
 * @brief Función que calcula el Local Solar Time (LST)
 *
 * @return lst
 */
double Lst(const int lt, const double tc) {
  double lst{lt + (tc / 60.0)};
  // std::cout << "lst: " << lst << "\n";
  return lst;
}

/**
 * @brief Función que calcula el Hour Angle (HRA), convierte la hora solar local
 * (LST) en los grados que se mueve el sol en el cielo. El 0 se corresponde con
 * las 12 am por la manana es negativo, y por la tarde positivo
 *
 * @return hra
 */
double Hra(const double lst) {
  double hra{15 * (lst - 12)};
  // std::cout << "hra: " << hra << "\n";
  return hra;
}

/**
 * @brief Función que calcula el ángulo de declinación del sol
 *
 * @return dec
 */
double Dec(const int d) {
  double dec{23.45 * sin((360 / 365.0) * (d - 81) * M_PI / 180)};
  // std::cout << "dec: " << dec << "\n";
  return dec;
}

/**
 * @brief Función que calcula la altitud del sol
 *
 * @return altitud
 */
double Altitud(const double dec, const double latitud, const double hra) {
  double altitud{asin(((sin(dec * M_PI / 180) * sin(latitud * M_PI / 180)) +
                          cos(dec * M_PI / 180) * cos(latitud * M_PI / 180) *
                          cos(hra * M_PI / 180))) * 180 / M_PI};
  return altitud;
}

/**
 * @brief Función que calcula el acimut del sol
 *
 * @return acimut
 */
double Acimut(const double dec, const double latitud, const double hra,
              const double altitud) {
  double cuenta{(sin(dec * M_PI / 180) * cos(latitud * M_PI / 180) -
                           cos(dec * M_PI / 180) * sin(latitud * M_PI / 180) *
                           cos(hra * M_PI / 180)) /
                           cos(altitud * M_PI / 180)};
  if (cuenta > 1.0) cuenta = 1.0;
  else if (cuenta < -1) cuenta = -1.0;
  double acimut{0.0};
  if (hra >= 0) acimut = 360 - (acos(cuenta) * 180 / M_PI);
  else acimut = acos(cuenta) * 180 / M_PI;
  return acimut;
}

/**
 * @brief Función que calcula la hora de la salida del sol
 * 
 * @return salida
 */
int Salida(const double latitud, const double declinacion, const double tc) {
  int salida{static_cast<int>(floor(12.0 -
             ((1 / 15.0) * 180 / M_PI * acos(-tan(latitud * M_PI / 180) * tan(declinacion * M_PI / 180))) -
             (tc / 60.0)))};
  return salida;
}

/**
 * @brief Función que calcula la hora de la puesta del sol
 * 
 * @return puesta
 */
int Puesta(const double latitud, const double declinacion, const double tc) {
  int puesta {static_cast<int>(ceil(12.0 +
              ((1 / 15.0) * 180 / M_PI * acos(-tan(latitud * M_PI / 180) * tan(declinacion * M_PI / 180))) -
              (tc / 60.0)))};
  return puesta;
}

/**
 * @brief Función que calcula la longitude de la sombra del gnomon
 * 
 * @return longitud_sombra
 */
double LongitudSombra(const double altitud, const double altura_gnomon) {
  double longitud_sombra{tan(altitud * M_PI / 180) * altura_gnomon};
  return longitud_sombra;
}

// Estructura que representa un punto en el plano cartesiano
struct Punto {
  double x;
  double y;
};

/**
 * @brief Función que calcula el punto (x, y) donde se proyecta la sombra en un instante
 * 
 * @return Punto
 */
Punto CalculaPunto(const double longitud_sombra, const double acimut, const Punto& pos_gnomon) {
  Punto punto;
  const double angulo{((acimut + 180.0) < 360.0)? (acimut + 180.0) : (acimut - 180.0)};
  double modulo_x;
  double modulo_y;
  // Distingo los cuatro cuadrantes en los que se puede proyectar la sombra
  if (angulo >= 0 && angulo < 90) {
    modulo_x = abs(longitud_sombra * sin(angulo * M_PI / 180));
    modulo_y = abs(longitud_sombra * cos(angulo * M_PI / 180));
    punto.x = pos_gnomon.x + modulo_x;
    punto.y = pos_gnomon.y + modulo_y;
  } else if (angulo >= 90 && angulo < 180) {
    modulo_x = abs(longitud_sombra * sin((180 - angulo) * M_PI / 180));
    modulo_y = abs(longitud_sombra * cos((180 - angulo) * M_PI / 180));
    punto.x = pos_gnomon.x + modulo_x;
    punto.y = pos_gnomon.y - modulo_y;
  } else if (angulo >= 180 && angulo < 270) {
    modulo_x = abs(longitud_sombra * sin((angulo - 180) * M_PI / 180));
    modulo_y = abs(longitud_sombra * cos((angulo - 180) * M_PI / 180));
    punto.x = pos_gnomon.x - modulo_x;
    punto.y = pos_gnomon.y - modulo_y;
  } else if (angulo >= 270 && angulo < 360) {
    modulo_x = abs(longitud_sombra * sin((360 - angulo) * M_PI / 180));
    modulo_y = abs(longitud_sombra * cos((360 - angulo) * M_PI / 180));
    punto.x = pos_gnomon.x - modulo_x;
    punto.y = pos_gnomon.y + modulo_y;
  }
  return punto;
}

int main() {
  std::cout << "**PROGRAMA QUE MUESTRA LOS ÁNGULOS SOLARES PARA UNA LAT, LON**\n";
  std::cout << "Introduce la latitud y longitud del lugar en formato: x.xx x.xx\n";
  double latitud, longitud;
  std::cin >> latitud >> longitud;
  std::cout << "Introduce el huso horario (-12/+12)\n";
  int huso_horario;
  std::cin >> huso_horario;
  int lstm{Lstm(huso_horario)}, hra;
  double eot, tc, lst, dec, altitud, acimut;
  // Comienza a calcular los ángulos
  for (int i{0}; i < 365; ++i) {
    if (i == 171) std::cout << "\nSolsticio de verano -> " << "DIA " << i << "\n";
    else if (i == 266) std::cout << "\nEquinoccio de otoño -> " << "DIA " << i << "\n";
    else if (i == 355) std::cout << "\nSolsticio de invierno -> " << "DIA " << i << "\n";
    else if (i == 79) std::cout << "\nEquinoccio de primavera -> " << "DIA " << i << "\n";
    else continue;
    eot = Eot(i);
    tc = Tc(longitud, lstm, eot);
    dec = Dec(i);
    for (int j{Salida(latitud, dec, tc)}; j <= Puesta(latitud, dec, tc); ++j) {
      lst = Lst(j, tc);
      hra = Hra(lst);
      altitud = Altitud(dec, latitud, hra);
      acimut = Acimut(dec, latitud, hra, altitud);
      std::cout << j << ":00 -> Altitud: " << altitud << "º, Azimut: " << acimut << "º\n";
    }
  }
  return 0;
}