from tkinter import *
import subprocess
import os
import pandas as pd
import matplotlib.pyplot as plt

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
  # Guardo las coordenadas en dos arrays de numpy
  x = df['X'].values
  y = df['Y'].values
  delimitadores = EncontrarEstaciones(df['Hora'].values)
  # Equinoccio de primavera
  plt.scatter(x[0:delimitadores[0]], y[0:delimitadores[0]], color = 'r')
  plt.plot(x[0:delimitadores[0]], y[0:delimitadores[0]], 'r')
  # Solsticio de verano
  plt.scatter(x[delimitadores[0] + 1:delimitadores[1]], y[delimitadores[0] + 1:delimitadores[1]], color = 'g')
  plt.plot(x[delimitadores[0] + 1:delimitadores[1]], y[delimitadores[0] + 1:delimitadores[1]], 'g')
  # Equinoccio de otoño
  plt.scatter(x[delimitadores[1] + 1:delimitadores[2]], y[delimitadores[1] + 1:delimitadores[2]], color = 'b')
  plt.plot(x[delimitadores[1] + 1:delimitadores[2]], y[delimitadores[1] + 1:delimitadores[2]], 'b')
  # Solsticio de invierno
  plt.scatter(x[delimitadores[2] + 1:], y[delimitadores[2] + 1:], color = 'tab:purple')
  plt.plot(x[delimitadores[2] + 1:], y[delimitadores[2] + 1:], 'tab:purple')
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
