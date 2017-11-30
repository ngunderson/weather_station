#include <SFE_BMP180.h>
#include <Wire.h>
#include <SoftwareSerial.h>

/////Edit if need be:///////////////

const int MAXCOUNT = 5;
const int DEVICEID = 1;
const long TIMEOUT = 5000;
const int sWait = 10000;
SFE_BMP180 sens1;
/////////////////////////////////////

//Pin A5 --> SCL
//Pin A4 --> SDA
int HC12Tx = 3;
int HC12Rx = 4;
int set = 5;

String cmd = "";
String readBuffer = "";
String writeBuffer = "";
bool serialCMD = false;
bool HC12CMD = false;
SoftwareSerial HC12(HC12Tx, HC12Rx);

void setup() {
  pinMode(set,OUTPUT);
  digitalWrite(set,HIGH);
  HC12.setTimeout(TIMEOUT);
  HC12.begin(9600);
  Serial.begin(9600);
  writeBuffer.reserve(64);
  readBuffer.reserve(64);
  cmd.reserve(64);

  if(!sens1.begin())
    Serial.println("ERROR SENSOR");           //Error device not detected
}

void loop() {
  while(Serial.available())
  {
     cmd = Serial.readString();
     cmd.trim();
  }

  if(cmd == "send")
  {
    int Temp = collectData();
    writeBuffer = (String)Temp;
    
    if(sendWeather())                     //calls the function to send the weather data
      Serial.println("ACK RECIVED");
    else
      Serial.println("ACK FAILED");
      
    writeBuffer = "";                     //Clear the write buffer
    cmd = "";
  }
}

//Would edit if different sensor used//
double collectData()
{
  double T;
  char status;
  status = sens1.startTemperature();
  if(status != 0)
  {
    delay(status);
    status = sens1.getTemperature(T);
    if(status != 0)
    {
      T = ((9.0/5.0)*T+32.0);
      return int(T);
    } 
  }
  return -99;
}

//No Need to Edit//
bool  sendWeather()
{
  String msg = (String)"{\"id\":" + DEVICEID + ",\"temp\":" + writeBuffer + "}\n";        //Create the message to send to the Host node
  Serial.print(msg);//Debug purpose
  readBuffer = "";                                          //Clear the Read buffer
  int count = 0;
  unsigned long curTime = millis();
  HC12.print(msg);
  while(count < MAXCOUNT)                       //Set up for a 5 count and stop when something is recived Todo:Check what was recived and set the flag if its the ACK
  {
    if((millis() - curTime) >= TIMEOUT)                     //Checking the time (set up as a running timer instead of dela())
    {
      curTime = millis();                                   //Set Current Time
      ++count;                                              //Increment Counter
      Serial.println((String)"Try: " + count);
      char input = ' ';
      while(HC12.available() && input != '\n')             //Check if data was recived
      {
        input = HC12.read();
        readBuffer += char(input);
      }
      readBuffer.trim();
      if(readBuffer.equals((String)DEVICEID + ":ACK")) {   //Checks to see if the readBuffer equals the correct expected ACK from the host 
        return true;
      }
      HC12.print(msg);                                    //Sends the message to the Host node
    }
  }
  return false;
}

