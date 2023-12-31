/**
 * @file reloj-solar.h
 * @author Saúl Ruiz Fernández (ruizfernandezsaul@gmail.com)
 * @brief Clase que implementa los métodos para los cálculos del reloj solar
 * @version 0.1
 * @date 2023-07-30
 *
 * @copyright Copyright (c) 2023
 *
 */

#ifndef RELOJ_SOLAR_H
#define RELOJ_SOLAR_H

#include <cmath>
#include <iostream>

// Estructura que representa un punto en el plano cartesiano
struct Punto {
  double x;
  double y;
};

class RelojSolar {
 public:
  // Constructor con parámetros
  RelojSolar(const double latitud, const double longitud,
             const int huso_horario, const double altitud_gnomon)
      : latitud(latitud),
        longitud(longitud),
        huso_horario(huso_horario),
        altitud_gnomon(altitud_gnomon) {}

  // Métodos de la clase
  int Lstm(const int utc) const;
  double Eot(const int dias_desde_inicio_de_year) const;
  double Tc(const double longitud, const int lstm, const double eot) const;
  double Lst(const int lt, const double tc) const;
  double Hra(const double lst) const;
  double Dec(const int d) const;
  long double Altitud(const double dec, const double latitud,
                      const double hra) const;
  long double Acimut(const double dec, const double latitud, const double hra,
                     const long double altitud) const;
  int Salida(const double latitud, const double declinacion,
             const double tc) const;
  int Puesta(const double latitud, const double declinacion,
             const double tc) const;
  double LongitudSombra(const double altitud, const double altura_gnomon) const;
  Punto CalculaPunto(const double longitud_sombra, const double acimut) const;
  // Métodos para el reloj solar vertical
  double ObtenerAnguloVertical(const double altitud, const double acimut) const;
  Punto CalculaPuntoVertical(const double longitud_sombra,
                             const double angulo_vertical) const;

 private:
  double latitud{0.0};         // Latitud donde se encuentra el reloj solar
  double longitud{0.0};        // Longitud donde se encuentra el reloj solar
  int huso_horario{0};         // Huso horario del reloj solar
  double altitud_gnomon{0.0};  // Altura del gnomon en metros
};

#endif