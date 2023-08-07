from guifunc import *

# Configuración de ventana
ventana = Tk()
ventana.geometry("1500x700")

# Opciones para el dropdown del huso horario
husos_op = [-12, -11, -10, -9, -8, -7, -6, -5, -4, -3, -2, -1, 0,
            1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12]

titulo = Label(ventana, text = "\u2600RELOJ SOLAR\u2600", font=('Helvetica bold', 40))
titulo.place(relx = 0.5, rely = 0.1, anchor = "center")

# Dropdown huso horario
huso_label = Label(ventana, text = "Huso horario:")
huso_label.place(relx = 0.15, rely = 0.25, anchor = "w")
huso_boton_drop = IntVar()
huso_boton_drop.set(0)
huso_drop_menu = OptionMenu(ventana, huso_boton_drop, *husos_op)
huso_drop_menu.place(relx = 0.25, rely = 0.25, anchor = "w")

# Entry latitud
lat_label = Label(ventana, text = "Latitud (\u00b1xx.xxº):")
lat_label.place(relx = 0.15, rely = 0.35, anchor = "w")
entrada_lat = Entry(ventana)
entrada_lat.place(relx = 0.25, rely = 0.35, anchor = "w")

# Entry longitud
long_label = Label(ventana, text = "Longitud (\u00b1xxx.xxº):")
long_label.place(relx = 0.15, rely = 0.45, anchor = "w")
entrada_lon = Entry(ventana)
entrada_lon.place(relx = 0.25, rely = 0.45, anchor = "w")

# Entry altura gnomon
alt_label = Label(ventana, text = "Altura gnomon (m):")
alt_label.place(relx = 0.15, rely = 0.55, anchor = "w")
entrada_alt = Entry(ventana)
entrada_alt.place(relx = 0.25, rely = 0.55, anchor = "w")

# Campo de texto para anunciar un error en la entrada de datos
error_label = Label(ventana, text = "Alguno/os de los datos introducidos no son correctos...", fg = "red")

# Botón "Calcular reloj"
boton_calcular = Button(ventana, text = "Calcular Reloj", command=lambda: CalcularReloj(huso_boton_drop, entrada_lat,
                                                                                        entrada_lon, entrada_alt,
                                                                                        error_label),
                        background = "blue", foreground = "white")
boton_calcular.place(relx = 0.25, rely = 0.65, anchor = "center")

ventana.mainloop()
