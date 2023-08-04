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
  // Constructor por defecto
  RelojSolar() {
    latitud = 0;
    longitud = 0;
    huso_horario = 0;
    altitud_gnomon = 0;
  }
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
  double Altitud(const double dec, const double latitud,
                 const double hra) const;
  double Acimut(const double dec, const double latitud, const double hra,
                const double altitud) const;
  int Salida(const double latitud, const double declinacion,
             const double tc) const;
  int Puesta(const double latitud, const double declinacion,
             const double tc) const;
  double LongitudSombra(const double altitud, const double altura_gnomon) const;
  Punto CalculaPunto(const double longitud_sombra, const double acimut) const;

 private:
  double latitud;         // Latitud donde se encuentra el reloj solar
  double longitud;        // Longitud donde se encuentra el reloj solar
  int huso_horario;       // Huso horario del reloj solar
  double altitud_gnomon;  // Altura del gnomon en metros
};

#endif