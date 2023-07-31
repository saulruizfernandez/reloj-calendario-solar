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

int main() {
  //std::cout << "**PROGRAMA QUE MUESTRA LOS ÁNGULOS SOLARES PARA UNA LAT, LON**\n";
  //std::cout << "Introduce la latitud y longitud del lugar en formato: x.xx x.xx\n";
  double latitud, longitud;
  std::cin >> latitud >> longitud;
  //std::cout << "Introduce el huso horario (-12/+12)\n";
  int huso_horario;
  std::cin >> huso_horario;
  //std::cout << "Introduce la altura del gnomon en metros\n";
  double altura_gnomon;
  std::cin >> altura_gnomon;

  RelojSolar mireloj{latitud, longitud, huso_horario, altura_gnomon};

  int lstm{mireloj.Lstm(huso_horario)}, hra;
  double eot, tc, lst, dec, altitud, acimut, longitud_sombra, x, y;
  Punto punto;

  // Comienza a calcular los ángulos
  for (int i{0}; i < 365; ++i) {
    if (i == 171) std::cout << "Solsticio de verano\n";
    else if (i == 266) std::cout << "Equinoccio de otoño\n";
    else if (i == 355) std::cout << "Solsticio de invierno\n";
    else if (i == 79) std::cout << "Equinoccio de primavera\n";
    else continue;
    eot = mireloj.Eot(i);
    tc = mireloj.Tc(longitud, lstm, eot);
    dec = mireloj.Dec(i);
    for (int j{mireloj.Salida(latitud, dec, tc)}; j <= mireloj.Puesta(latitud, dec, tc); ++j) {
      lst = mireloj.Lst(j, tc);
      hra = mireloj.Hra(lst);
      altitud = mireloj.Altitud(dec, latitud, hra);
      acimut = mireloj.Acimut(dec, latitud, hra, altitud);
      // Escribo la hora, altitud, acimut
      std::cout << j << " " << altitud << " " << acimut << "\n";
      longitud_sombra = mireloj.LongitudSombra(altitud, altura_gnomon);
      punto = mireloj.CalculaPunto(longitud_sombra, acimut);
      // Escribo la coordenada 'x' y la 'y'
      std::cout << punto.x << " " << punto.y << "\n";
      //std::cout << "Longitud de la sombra: " << longitud_sombra << "\n";
    }
  }
  return 0;
}