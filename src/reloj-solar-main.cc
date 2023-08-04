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
  std::fstream fichero_datos;
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

  RelojSolar mireloj{latitud, longitud, huso_horario, altura_gnomon};

  int lstm{mireloj.Lstm(huso_horario)}, hra;
  double eot, tc, lst, dec, altitud, acimut, longitud_sombra, x, y;
  Punto punto;

  fichero_datos.open("./datos_reloj.txt", std::ios_base::trunc);
  // Comienza a calcular los ángulos
  for (int i{0}; i < 365; ++i) {
    if (i == 171) std::cout << "Solsticio de verano\n";
    else if (i == 266) fichero_datos << "Equinoccio de otoño\n";
    else if (i == 355) fichero_datos << "Solsticio de invierno\n";
    else if (i == 79) fichero_datos << "Equinoccio de primavera\n";
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
      fichero_datos << j << " " << altitud << " " << acimut << "\n";
      longitud_sombra = mireloj.LongitudSombra(altitud, altura_gnomon);
      punto = mireloj.CalculaPunto(longitud_sombra, acimut);
      // Escribo la coordenada 'x' y la 'y'
      fichero_datos << punto.x << " " << punto.y << "\n";
      //std::cout << "Longitud de la sombra: " << longitud_sombra << "\n";
    }
  }
  fichero_datos.close();
  return 0;
}