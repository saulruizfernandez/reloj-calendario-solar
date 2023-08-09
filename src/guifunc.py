from tkinter import *
import subprocess
import os
import pandas as pd
import matplotlib.pyplot as plt
import matplotlib.image as image
from matplotlib.offsetbox import (OffsetImage, AnnotationBbox)

# Función que comprueba que los datos introducidos por el usuario son correctos
def ComprobarDatos(latitud, longitud, altura_gnomon):
  if ((latitud < -90.0) or (latitud > 90)):
    return False
  if ((longitud < -180.0) or (longitud > 180)):
    return False
  if (altura_gnomon < 0):
    return False
  return True

# Función que indica el comienzo de cada curva de proyección de la sombra
def EncontrarEstaciones(horas):
  delimitadores = []
  hora_ant = horas[0]
  for i in range(1, len(horas)):
    if hora_ant > horas[i]:
      delimitadores.append(i - 1)
    hora_ant = horas[i]
  return delimitadores

# Función que obtiene la gráfica a partir de los cálculos y la inserta en la ventana
def ObtenerGrafica(huso, latitud, longitud, altura_gnomon):
  direccion_abs = os.getcwd()
  comando = "cd " + direccion_abs + "; cd ../build; ./reloj " + str(latitud) + " " + str(longitud) + " " + str(huso) + " " + str(altura_gnomon)
  proceso = subprocess.Popen(comando, shell = True)
  proceso.wait() # Espera a que se cree el fichero
  df = pd.read_csv("../build/datos_reloj.csv", delimiter = ' ', usecols = ['Hora', 'X', 'Y'])
  df_variaciones = pd.read_csv("../build/datos_variaciones.csv", delimiter = ' ')
  # Guardo las coordenadas en dos arrays de numpy
  x = df['X'].values
  y = df['Y'].values
  horas = df['Hora'].values
  delimitadores = EncontrarEstaciones(horas)
  plt.figure(figsize = (15, 9))
  # Equinoccio de primavera
  plt.scatter(x[:delimitadores[0] + 1], y[:delimitadores[0] + 1], color = 'r')
  plt.plot(x[:delimitadores[0] + 1], y[:delimitadores[0] + 1], 'r', label = "Equinoccio primavera")
  # Solsticio de verano
  plt.scatter(x[delimitadores[0] + 1:delimitadores[1] + 1], y[delimitadores[0] + 1:delimitadores[1] + 1], color = 'g')
  plt.plot(x[delimitadores[0] + 1:delimitadores[1] + 1], y[delimitadores[0] + 1:delimitadores[1] + 1], 'g', label = "Solsticio verano")
  # Equinoccio de otoño
  plt.scatter(x[delimitadores[1] + 1:delimitadores[2] + 1], y[delimitadores[1] + 1:delimitadores[2] + 1], color = 'b')
  plt.plot(x[delimitadores[1] + 1:delimitadores[2] + 1], y[delimitadores[1] + 1:delimitadores[2] + 1], 'b', label = "Equinoccio otoño")
  # Solsticio de invierno
  plt.scatter(x[delimitadores[2] + 1:], y[delimitadores[2] + 1:], color = 'tab:purple')
  plt.plot(x[delimitadores[2] + 1:], y[delimitadores[2] + 1:], 'tab:purple', label = "Solsticio invierno")
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
  rosa_vientos = OffsetImage(image.imread('Rosa_de_los_vientos.png'), zoom = 0.2)
  ann_box = AnnotationBbox(rosa_vientos, (altura_gnomon * 6, altura_gnomon * 5.3), frameon = False)
  ax = plt.subplot()
  ax.add_artist(ann_box)
  plt.show()

# Función que se ejecuta al pulsar el botón "Calcular reloj"
def CalcularReloj(huso_boton_drop, entrada_lat, entrada_lon, entrada_alt, error_label):
  huso = huso_boton_drop.get()
  try:
    latitud = float(entrada_lat.get())
    longitud = float(entrada_lon.get())
    altura_gnomon = float(entrada_alt.get())
  except:
    latitud = -1
    longitud = -1
    altura_gnomon = -1
  if (ComprobarDatos(latitud, longitud, altura_gnomon) == False):
    error_label.place(relx = 0.5, rely = 0.6, anchor = "w")
  else:
    error_label.place_forget()
    ObtenerGrafica(huso, latitud, longitud, altura_gnomon)
