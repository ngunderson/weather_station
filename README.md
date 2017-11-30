# Setting Up a Station Node

## PREREQUISIT TO UPLOAD CODE: The SFE_BMP180 library

a.) The Zip file is located in the reposiry called "BMP180_Breakout_Arduino_Library-master"  
b.) Download this and save it to a temporary location  
c.) To Add the library to the IDE:  
  - Goto Sketch->Include Library->Add .Zip Library  
  - When prompted select the .Zip folder, the IDE should automaticlly add the library to be used  

1.) Aquire the "StationNode.ino" code  
2.) Open the code up in the Arduino IDE  
3.) Register your device on the website http://137.104.120.150:5000  
4.) Set the DeviceID in the code to the Device ID on the web site  
5.) You may change the MAXCOUNT in the code to change the number of trys if an ACK is not recived (Default = 5)  
6.) You may Change the TIMEOUT in the code to change the wait time between each re-try (Default = 5000; 5 seconds)  
7.) You may Change the sWait in the code to change the time the device sleeps before recording and sending (Default = 10000; 10 seconds)  
8.) If you were to have your own sensor and not a BMP 180 then you would interface it with the arduino yourself and set the writeBuffer to the output  
	of collectData(). As well as updating collectData() to work with you device  


## Reference:
-For BMP LIb: https://learn.sparkfun.com/tutorials/bmp180-barometric-pressure-sensor-hookup-/installing-the-arduino-library  
-HC12 Example: https://www.allaboutcircuits.com/projects/understanding-and-implementing-the-hc-12-wireless-transceiver-module/  
