/**
 * @file reloj-solar-main.cc
 * @author Saúl Ruiz Fernández (ruizfernandezsaul@gmail.com)
 * @brief 
 * @version 0.1
 * @date 2023-07-31
 * 
 * @copyright Copyright (c) 2023
 * 
 */

#include "reloj-solar.h"

#include <fstream>
#include <string>

int main(int argc, char* argv[]) {
  std::ofstream fichero_datos_1;
  std::ofstream fichero_datos_2;
  //std::cout << "**PROGRAMA QUE MUESTRA LOS ÁNGULOS SOLARES PARA UNA LAT, LON**\n";
  //std::cout << "Introduce la latitud y longitud del lugar en formato: x.xx x.xx\n";
  double latitud, longitud;
  latitud = std::stod(argv[1]);
  longitud = std::stod(argv[2]);
  //std::cout << "Introduce el huso horario (-12/+12)\n";
  int huso_horario;
  huso_horario = std::stoi(argv[3]);
  //std::cout << "Introduce la altura del gnomon en metros\n";
  double altura_gnomon;
  altura_gnomon = std::stod(argv[4]);
  int reloj_horizontal{std::stoi(argv[5])};
  double rotacion_norte{std::stod(argv[6])};

  RelojSolar mireloj{latitud, longitud, huso_horario, altura_gnomon};

  int lstm{mireloj.Lstm(huso_horario)}, hra;
  double eot, tc, lst, dec, altitud, acimut, longitud_sombra;
  Punto punto;

  fichero_datos_1.open("datos_reloj.csv", std::ios_base::trunc);
  fichero_datos_1 << "Id Hora Altitud Acimut X Y\n";
  // Comienza a calcular las curvas de proyección
  for (int i{0}; i < 365; ++i) {
    if (i != 171 && i != 266 && i != 355 && i != 79) continue;
    eot = mireloj.Eot(i);
    tc = mireloj.Tc(longitud, lstm, eot);
    dec = mireloj.Dec(i);
    for (int j{mireloj.Salida(latitud, dec, tc)}; j <= mireloj.Puesta(latitud, dec, tc); ++j) {
      lst = mireloj.Lst(j, tc);
      hra = mireloj.Hra(lst);
      altitud = mireloj.Altitud(dec, latitud, hra);
      if (altitud < 0) continue;
      acimut = mireloj.Acimut(dec, latitud, hra, altitud);
      acimut += rotacion_norte;
      // Escribo la etiqueta de estación, hora, altitud, acimut
      if (!reloj_horizontal && acimut > 90.0 && acimut < 270.0) continue;
      fichero_datos_1 << i << " " << j << " " << altitud << " " << acimut;
      if (!reloj_horizontal) {
        double angulo_long{(acimut >= 270.0 && acimut <= 360.0)? (acimut - 270.0):(90.0 - acimut)};
        longitud_sombra = mireloj.LongitudSombra(angulo_long, altura_gnomon);
        double angulo_vertical{mireloj.ObtenerAnguloVertical(altitud, acimut)};
        punto = mireloj.CalculaPuntoVertical(longitud_sombra, angulo_vertical);
      } else {
        longitud_sombra = mireloj.LongitudSombra(altitud, altura_gnomon);
        punto = mireloj.CalculaPunto(longitud_sombra, acimut);
      }
      // Escribo la coordenada 'x' y la 'y'
      fichero_datos_1 << " " << punto.x << " " << punto.y << "\n";
      //std::cout << "Longitud de la sombra: " << longitud_sombra << "\n";
    }
  }
  fichero_datos_1.close();

  // Calcula la variación de la sommbra por horas a lo largo del año
  fichero_datos_2.open("datos_variaciones.csv", std::ios_base::trunc);
  fichero_datos_2 << "X Y\n";
  // Comienza a calcular las curvas de proyección
  for (int i{0}; i < 365; i += 5) {
    if (i == 171 && i == 266 && i == 355 && i == 79) continue;
    eot = mireloj.Eot(i);
    tc = mireloj.Tc(longitud, lstm, eot);
    dec = mireloj.Dec(i);
    for (int j{mireloj.Salida(latitud, dec, tc)}; j <= mireloj.Puesta(latitud, dec, tc); ++j) {
      lst = mireloj.Lst(j, tc);
      hra = mireloj.Hra(lst);
      altitud = mireloj.Altitud(dec, latitud, hra);
      if (altitud < 0) continue;
      acimut = mireloj.Acimut(dec, latitud, hra, altitud);
      acimut += rotacion_norte;
      if (!reloj_horizontal) {
        if (acimut > 90 && acimut < 270) continue;
        double angulo_long{(acimut >= 270 && acimut <= 360)? (acimut - 270):(90 - acimut)};
        longitud_sombra = mireloj.LongitudSombra(angulo_long, altura_gnomon);
        double angulo_vertical{mireloj.ObtenerAnguloVertical(altitud, acimut)};
        punto = mireloj.CalculaPuntoVertical(longitud_sombra, angulo_vertical);
      } else {
        longitud_sombra = mireloj.LongitudSombra(altitud, altura_gnomon);
        punto = mireloj.CalculaPunto(longitud_sombra, acimut);
      }
      // Escribo la coordenada 'x' y la 'y'
      fichero_datos_2 << " " << punto.x << " " << punto.y << "\n";
    }
  }
  fichero_datos_2.close();
  return 0;
}