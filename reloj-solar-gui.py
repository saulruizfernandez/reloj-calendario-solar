from tkinter import *

# Configuración de ventana  2
ventana = Tk()
ventana.geometry("1500x700")

# Opciones para los dropdown
husos_op = [-12, -11, -10, -9, -8, -7, -6, -5, -4, -3, -2, -1, 0,
            1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12]
digitos_op = [0, 1, 2, 3, 4, 5, 6, 7, 8, 9]

titulo = Label(
  ventana,
  text = "\u2600RELOJ SOLAR\u2600",
  font=('Helvetica bold', 40)
)
titulo.place(relx = 0.5, rely = 0.1, anchor = "center")

# Dropdown huso horario
huso_label = Label(ventana, text = "Huso horario:")
huso_label.place(relx = 0.15, rely = 0.25, anchor = "center")


huso_boton_drop = IntVar()
huso_boton_drop.set("0")
huso_drop_menu = OptionMenu(ventana, huso_boton_drop, *husos_op)
huso_drop_menu.place(relx = 0.2, rely = 0.25, anchor = "center")


ventana.mainloop()