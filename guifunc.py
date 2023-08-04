from tkinter import *

# Función que comprueba que los datos introducidos por el usuario son correctos
def ComprobarDatos(latitud, longitud, altura_gnomon):
  if ((latitud < -90.0) or (latitud > 90)): return False
  if ((longitud < -180.0) or (longitud > 180)): return False
  if (altura_gnomon < 0): return False
  return True

# Función que se ejecuta al pulsar el botón "Calcular reloj"
def CalcularReloj(huso_boton_drop, entrada_lat, entrada_lon, entrada_alt, error_label, error_label_bool):
  huso = huso_boton_drop.get()
  latitud = entrada_lat.get()
  longitud = entrada_lon.get()
  altura_gnomon = entrada_alt.get()
  if (not(ComprobarDatos(latitud, longitud, altura_gnomon))):
    if not error_label_bool:
      error_label.place(relx = 0.5, rely = 0.6, anchor = "w")
      error_label_bool = True
  else:
    if error_label_bool:
      error_label.place_forget()

    ObtenerGrafica(huso, latitud, longitud, altura_gnomon)
