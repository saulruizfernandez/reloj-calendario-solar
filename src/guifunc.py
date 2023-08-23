from tkinter import *
import subprocess
import os
import pandas as pd
import matplotlib.pyplot as plt
import matplotlib.image as image
from matplotlib.offsetbox import (OffsetImage, AnnotationBbox)
import tkintermapview

# Función que comprueba que los datos introducidos por el usuario son correctos
def ComprobarDatos(latitud, longitud, altura_gnomon, rot):
  if ((latitud < -90.0) or (latitud > 90)):
    return False
  if ((longitud < -180.0) or (longitud > 180)):
    return False
  if (altura_gnomon < 0):
    return False
  if ((rot > 360.0) or (rot < 0.0)):
    return False
  return True

# Función que obtiene la gráfica a partir de los cálculos y la inserta en la ventana
def ObtenerGrafica(huso, latitud, longitud, altura_gnomon, tipo, rot):
  direccion_abs = os.getcwd()
  comando = "cd " + direccion_abs + "; cd ../build; ./reloj " + str(latitud) + " " + str(longitud) + " " + str(huso) + " " + str(altura_gnomon) + " " + str(tipo) + " " + str(rot)
  proceso = subprocess.Popen(comando, shell = True)
  proceso.wait() # Espera a que se cree el fichero
  df = pd.read_csv("../build/datos_reloj.csv", delimiter = ' ', usecols = ['Id', 'Hora', 'X', 'Y'])
  df_variaciones = pd.read_csv("../build/datos_variaciones.csv", delimiter = ' ')
  # Guardo las coordenadas en dos arrays de numpy
  x = df['X'].values
  y = df['Y'].values
  horas = df['Hora'].values
  id_estaciones = df['Id'].values
  # Creo un array por cada solsticio/equinoccio
  equinoccio_primavera_x = []
  equinoccio_primavera_y = []
  solsticio_verano_x = []
  solsticio_verano_y = []
  equinoccio_otonio_x = []
  equinoccio_otonio_y = []
  solsticio_invierno_x = []
  solsticio_invierno_y = []
  for i in range(len(horas)):
    if id_estaciones[i] == 79:
      equinoccio_primavera_x.append(x[i])
      equinoccio_primavera_y.append(y[i])
    elif id_estaciones[i] == 171:
      solsticio_verano_x.append(x[i])
      solsticio_verano_y.append(y[i])
    elif id_estaciones[i] == 266:
      equinoccio_otonio_x.append(x[i])
      equinoccio_otonio_y.append(y[i])
    elif id_estaciones[i] == 355:
      solsticio_invierno_x.append(x[i])
      solsticio_invierno_y.append(y[i])

  plt.figure(figsize = (15, 9))
  # Equinoccio de primavera
  plt.scatter(equinoccio_primavera_x, equinoccio_primavera_y, color = 'r')
  plt.plot(equinoccio_primavera_x, equinoccio_primavera_y, 'r', label = "Equinoccio primavera")
  # Solsticio de verano
  plt.scatter(solsticio_verano_x, solsticio_verano_y, color = 'g')
  plt.plot(solsticio_verano_x, solsticio_verano_y, 'g', label = "Solsticio verano")
  # Equinoccio de otoño
  plt.scatter(equinoccio_otonio_x, equinoccio_otonio_y, color = 'b')
  plt.plot(equinoccio_otonio_x, equinoccio_otonio_y, 'b', label = "Equinoccio otoño")
  # Solsticio de invierno
  plt.scatter(solsticio_invierno_x, solsticio_invierno_y, color = 'tab:purple')
  plt.plot(solsticio_invierno_x, solsticio_invierno_y, 'tab:purple', label = "Solsticio invierno")
  plt.legend(loc = "lower right")
  for i in range(len(x)): plt.annotate(str(horas[i]), (x[i], y[i]))
  plt.ylim(altura_gnomon * -7.5, altura_gnomon * 7.5)
  plt.xlim(altura_gnomon * -7.5, altura_gnomon * 7.5)
  plt.ylabel("Posición en el eje Y")
  plt.xlabel("Posición en el eje X")
  plt.title("RELOJ SOLAR")
  # Mustro las variaciones en la proyección de la sombra a lo largo del año
  plt.scatter(df_variaciones['X'], df_variaciones['Y'], color = 'k', s = 0.1)
  # Imagen de la rosa de los vientos
  if tipo == 1:
    rosa_vientos = OffsetImage(image.imread('Rosa_de_los_vientos.png'), zoom = 0.2)
  else:
    rosa_vientos = OffsetImage(image.imread('flechas.png'), zoom = 0.1)
  ann_box = AnnotationBbox(rosa_vientos, (altura_gnomon * 6, altura_gnomon * 5.3), frameon = False)
  ax = plt.subplot()
  ax.add_artist(ann_box)
  plt.show()

# Función que se ejecuta al pulsar el botón "Calcular reloj"
def CalcularReloj(huso_boton_drop, entrada_lat, entrada_lon, entrada_alt, error_label, tipo_drop, rotacion_norte, mapa_wid, marcador):
  huso = huso_boton_drop.get()
  tipo = 0
  if (tipo_drop.get() == "Horizontal"): tipo = 1
  try:
    latitud = float(entrada_lat.get())
    longitud = float(entrada_lon.get())
    altura_gnomon = float(entrada_alt.get())
    rot = float(rotacion_norte.get())
    CoordenadasAMapa(mapa_wid, marcador, latitud, longitud)
  except:
    latitud = -1
    longitud = -1
    altura_gnomon = -1
    rot = -1
  if (ComprobarDatos(latitud, longitud, altura_gnomon, rot) == False):
    error_label.place(relx = 0.5, rely = 0.6, anchor = "w")
  else:
    error_label.place_forget()
    ObtenerGrafica(huso, latitud, longitud, altura_gnomon, tipo, rot)

# Función que marca y enfoca en el mapa el lugar que ha seleccionado el usuario
def CoordenadasAMapa(mapa_wid, marcador, lat, lon):
  mapa_wid.set_position(lat, lon)
  mapa_wid.set_zoom(6)
  marcador.set_position(lat, lon)
  direccion = tkintermapview.convert_coordinates_to_country(28.4261300, -16.48876)
  marcador.set_text(direccion)