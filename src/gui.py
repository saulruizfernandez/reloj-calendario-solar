from guifunc import *

# Configuración de ventana
ventana = Tk()
ventana.geometry("1500x700")
# ventana.configure(background = '#f2dd22')

# Opciones para los dropdown
husos_op = [-12, -11, -10, -9, -8, -7, -6, -5, -4, -3, -2, -1, 0,
            1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12]
tipo_op = ["Horizontal", "Vertical"]

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

# Dropdown para seleccionar el tipo de reloj
tipo_label = Label(ventana, text = "Tipo de reloj: ")
tipo_label.place(relx = 0.15, rely = 0.65, anchor = "w")
tipo_boton_drop = StringVar()
tipo_boton_drop.set("Horizontal")
tipo_drop_menu = OptionMenu(ventana, tipo_boton_drop, *tipo_op)
tipo_drop_menu.place(relx = 0.25, rely = 0.65, anchor = "w")

# Entry rotación con respecto al norte
rot_label = Label(ventana, text = "Rotación N(xx.xº)")
rot_label.place(relx = 0.15, rely = 0.75, anchor = "w")
entrada_rot = Entry(ventana)
entrada_rot.place(relx = 0.25, rely = 0.75, anchor = "w")

# Botón "Calcular reloj"
boton_calcular = Button(ventana, text = "Calcular Reloj", command=lambda: CalcularReloj(huso_boton_drop, entrada_lat,
                                                                                        entrada_lon, entrada_alt,
                                                                                        error_label, tipo_boton_drop,
                                                                                        entrada_rot),
                        background = "blue", foreground = "white")
boton_calcular.place(relx = 0.25, rely = 0.85, anchor = "center")

# Salida de texto para indicar las instrucciones de uso del programa
texto_instrucciones_numeros = '''
1.
2.

3.


4. 

5.


6.

7.

8.



9.
10.
11.

12.
13.
'''
texto_instrucciones = '''
Selecciona tu huso horario mediante el menú desplegable
Ingresa tu latitud y longitud en grados decimales (usar
punto en lugar de coma)
Ingresa la altura del gnomon en metros (por altura se
entiende la distancia mínima de separación entre la superficie
plana del reloj y el extremo más alejado del gnomon)
Selecciona el tipo de reloj (vertical u horizontal) según el
tipo de pared en la que se vaya a situar
Indica (sólo en el caso de que el reloj se vaya a situar en una
pared vertical) la orientación de la pared como grados de
desviación con respecto al norte, medidos en sentido horario
Presiona el botón de <<Calcular Reloj>> para obtener las medidas
de tu reloj solar
Una vez abierta la gráfica puedes navegar por los ejes con
la opción (2) seleccionada
Puedes ampliar o alejar la vista con la opción (3) seleccionada.
Para ampliar selecciona con el click izquierdo del ratón la región
de interés, y para alejar lleva a cabo la misma operación pero con
el click derecho en lugar del izquierdo
Puedes restaurar la vista original en la opción (1)
Puedes configurar las dimensiones de la gráfica en la opción (4)
Es importante que guardes en tu equipo la gráfica para poder
conservarla/imprimirla con la opción (5)
Se asume que el gomon está situado en el punto (0, 0)
Para obtener la información de cada punto, mueve el cursor hacia el
punto y mira sus coordenadas en la pante inferior derecha de la
gráfica, o en su defecto, consulta las medidas directamente en el
archivo dir_programa/build/datos_reloj.csv (medidas en metros)
'''
instrucciones_numeros = Label(ventana, text = texto_instrucciones_numeros, justify = LEFT)
instrucciones_numeros.place(relx = 0.40, rely = 0.18, anchor = "nw")
instrucciones = Label(ventana, text = texto_instrucciones, justify = LEFT)
instrucciones.place(relx = 0.42, rely = 0.18, anchor = "nw")

# Pongo números a las opciones del menú de la gráfica
numeros_opciones = Label(ventana, text = "(1)                    (2)    (3)   (4)    (5)", foreground = 'red',justify = LEFT)
numeros_opciones.place(relx = 0.40, rely = 0.9, anchor = 'nw')

# Cargo la imagen de las opciones de la gráfica
frame = Frame(ventana, width = 200, height = 50)
frame.pack()
frame.place(anchor = "nw", relx = 0.40, rely = 0.93)
imagen_opciones = PhotoImage(file = "./opciones.png")
label_opciones = Label(frame, image = imagen_opciones)
label_opciones.pack()

ventana.mainloop()
