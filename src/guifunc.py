from tkinter import *

# Función que comprueba que los datos introducidos por el usuario son correctos
def ComprobarDatos(latitud, longitud, altura_gnomon):
  if ((latitud < -90.0) or (latitud > 90)): return False
  if ((longitud < -180.0) or (longitud > 180)): return False
  if (altura_gnomon < 0): return False
  return True

# Función que obtiene la gráfica a partir de los cálculos y la inserta en la ventana
def ObtenerGrafica(huso, latitud, longitud, altura_gnomon):
  print("hola\n")

# Función que se ejecuta al pulsar el botón "Calcular reloj"
def CalcularReloj(huso_boton_drop, entrada_lat, entrada_lon, entrada_alt, error_label, error_label_bool):
  huso = huso_boton_drop.get()
  try:
    latitud = float(entrada_lat.get())
    longitud = float(entrada_lon.get())
    altura_gnomon = float(entrada_alt.get())
    print(f"latitud: {latitud}, longitud: {longitud}, alt_gnomon: {altura_gnomon}\n")
  except:
    latitud = -1
    longitud = -1
    altura_gnomon = -1
  if ComprobarDatos(latitud, longitud, altura_gnomon) == False:
    if error_label_bool == False:
      error_label.place(relx = 0.5, rely = 0.6, anchor = "w")
      error_label_bool = True
  else:
    if error_label_bool == True:
      error_label.place_forget()
      error_label_bool = False
      ObtenerGrafica(huso, latitud, longitud, altura_gnomon)
