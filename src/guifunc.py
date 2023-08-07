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

# Función que obtiene la gráfica a partir de los cálculos y la inserta en la ventana
def ObtenerGrafica(huso, latitud, longitud, altura_gnomon):
  direccion_abs = os.getcwd()
  comando = "cd " + direccion_abs + "; cd ../build; ./reloj " + str(latitud) + " " + str(longitud) + " " + str(huso) + " " + str(altura_gnomon)
  proceso = subprocess.Popen(comando, shell = True)
  proceso.wait() # Espera a que se cree el fichero
  df = pd.read_csv("../build/datos_reloj.csv", delimiter = ' ')
  # print(df.head())
  plt.scatter(df['X'], df['Y'])
  plt.plot(df['X'], df['Y'])
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
