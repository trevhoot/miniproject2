from Tkinter import *
import serial

ser = serial.Serial('/dev/ttyUSB0', 19200)
ser.open()
ser.isOpen()

class slider():
	def __init__(self):
		self.pan = 0.5*65536
		self.tilt = 0.5*65536

	def set_pan(pan):
		self.pan = pan

	def set_tilt(tilt):
		self.tilt = tilt

	def get_pan():
		return self.pan

	def get_tilt():
		return self.tilt

def sel():
   selection = "Value = " + str(ping)
   label.config(text = selection)

def update():
	ser.write("%d %d", self.pan, self.tilt)

root = Tk()
val1 = DoubleVar()
val2 = DoubleVar()
ping = 0 #This will be the value returned in miniproject 3.
scale1 = Scale( root, variable = val1 , length = 65536, orient = HORIZONTAL, label = "pan", command = update)
scale1.pack(anchor=CENTER)
scale2 = Scale( root, variable = val2 , length = 65536, orient = HORIZONTAL, label = "tilt", command = update)
scale2.pack()

button = Button(root, text="Ping", command=sel)
button.pack(anchor=CENTER)

label = Label(root)
label.pack()

root.mainloop()
