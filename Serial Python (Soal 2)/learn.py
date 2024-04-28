import serial
import time

arduino = serial.Serial('COM2', 9600)
time.sleep(2)

print("Tekan 1 untuk menghidupkan LED, tekan 0 untuk mematikan")

while 1:
    data = input()
    if data == '1':
        arduino.write(b'1')
        print('LED Hidup')
    elif data == '0':
        arduino.write(b'0')
        print('LED Mati')