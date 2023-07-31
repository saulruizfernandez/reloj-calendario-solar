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

/*
int main() {
  std::cout << "**PROGRAMA QUE MUESTRA LOS ÁNGULOS SOLARES PARA UNA LAT, LON**\n";
  std::cout << "Introduce la latitud y longitud del lugar en formato: x.xx x.xx\n";
  double latitud, longitud;
  std::cin >> latitud >> longitud;
  std::cout << "Introduce el huso horario (-12/+12)\n";
  int huso_horario;
  std::cin >> huso_horario;
  std::cout << "Introduce la altura del gnomon en metros\n";
  double altura_gnomon;
  std::cin >> altura_gnomon;

  int lstm{Lstm(huso_horario)}, hra;
  double eot, tc, lst, dec, altitud, acimut, longitud_sombra, x, y;
  Punto punto;

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
      longitud_sombra = LongitudSombra(altitud, altura_gnomon);
      punto = CalculaPunto(longitud_sombra, acimut);
      std::cout << "x: " << punto.x << ", y: " << punto.y << "\n";
      std::cout << "Longitud de la sombra: " << longitud_sombra << "\n";
    }
  }
  return 0;
}
*/