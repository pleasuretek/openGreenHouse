/*
gardenControl is part of the openGreenHouse package of software sources.

this code is in public domain...

for use with arduino > 1.0 

Written by: Travis McCann
Copywrite GPL 2010-2012

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.
You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#include <SD.h>
#include <DallasTemperature.h>
#include <OneWire.h>
#include <DHT.h>
#include <Ethernet.h>
#include <EthernetUdp.h>
#include <EthernetServer.h>
#include <EthernetClient.h>
#include <util.h>
#include <SPI.h>
#include <Wire.h>
#include <RTClib.h>

#define ONE_WIRE_BUS 52    //PIN0
#define TEMPERATURE_PRECISION 9
#define DHTPIN 1     //PIN 1
#define DHTTYPE DHT22
#define RELAY01 53   //PIN2
#define RELAY02 51   //PIN3
#define RELAY03 49   //PIN5
#define RELAY04 47   //PIN6
#define RELAY05 45   //PIN7
#define RELAY06 43   //PIN8
#define RELAY07 41
#define RELAY08 39
#define SDCS 4   // sd card chip select pin on ethernet shield

//SDCard stuff
const int RecordLimit = 1000;  //limit number of records kept on SD card
const unsigned long TI = 10000;  //Timer Increment, number of milliseconds to write sensor data at


//ehternet stuff
const int BufferSize = 100;   //client read buffer size for normal server

byte mac[]     = {0x90, 0xA2, 0xDA, 0x01, 0x00, 0xEF};  //MAC for my ethernet shield
IPAddress ip(192,168,1,25);
IPAddress subnet(255,255,255,0);
char rootFileName[] = "index.htm";        //file to return if request was empty
EthernetServer server(723);              //open server on port 723 (random port)

//rtc stuff
const int NTP_PACKET_SIZE = 48;          //NTP timestamp is in first 48bytes of responce
const int NTP_PORT = 8888;               //UDP server listens on port 8888
byte packetBuffer[ NTP_PACKET_SIZE ];    //buffer to hold ntp packet
IPAddress timeServer(192, 43, 244, 18);  //time.nist.ov ntp server

RTC_DS1307 rtc;    //realtime clock for timestamp
EthernetUDP Udp;   //UPD is needed for ntp

//Temp sensor stuff

OneWire oneWire(ONE_WIRE_BUS);             // Setup a oneWire instance to communicate with any OneWire devices (not just Maxim/Dallas temperature ICs)
DallasTemperature owSensors(&oneWire);     // Pass our oneWire reference to Dallas Temperature. 
DeviceAddress thermometerA, thermometerB, thermometerC;  // arrays to hold device addresses.  You must create one for each DX18B20 you have connected


//humid sensor stuff
DHT dht(DHTPIN, DHTTYPE);    //humidity sensor


unsigned long timer = millis();        //timer to time sensor readings, part 1
unsigned long targetTime = millis();   //timer part 2


void setup(void)
{
  //set relay pins to output mode
  pinMode(RELAY01,OUTPUT);
  pinMode(RELAY02,OUTPUT);
  pinMode(RELAY03,OUTPUT);
  pinMode(RELAY04,OUTPUT);
  pinMode(RELAY05,OUTPUT);
  pinMode(RELAY06,OUTPUT);
  pinMode(RELAY07,OUTPUT);
  pinMode(RELAY08,OUTPUT);
  
  
  pinMode(18,OUTPUT);      //connected to rtc gnd  (if rtc is plugged directly into arduino shield
  digitalWrite(18,LOW);    //set to low 
  pinMode(19,OUTPUT);      //connected to rtc vcc
  digitalWrite(19,HIGH);   //give rtc power
  
  Ethernet.begin(mac, ip);
  server.begin();
  SD.begin(SDCS);
  owSensors.begin();      // Start up the dallas one wire library
  dht.begin();            // Start up the dht library
  Wire.begin();           //get rtc readay to begin
  rtc.begin();            //start realtime clock
  
  Serial.begin(9600);     //debugging use
  
  
  delay(500);  //delay to let ethernet setup
  owSensors.getAddress(thermometerA, 0);
  owSensors.getAddress(thermometerB, 1);
  owSensors.getAddress(thermometerC, 2);
  owSensors.setResolution(thermometerA, TEMPERATURE_PRECISION);
  owSensors.setResolution(thermometerB, TEMPERATURE_PRECISION);
  owSensors.setResolution(thermometerC, TEMPERATURE_PRECISION);
}

//print address string
String printAddress(DeviceAddress deviceAddress)
{
  String addy;
  for (uint8_t i = 0; i < 8; i++)
  {
    // zero pad the address if necessary
    if (deviceAddress[i] < 16) addy +="0";
    addy +=(deviceAddress[i], HEX);
    return addy;
  }
}

//return string of entire temp responce
String printTemp(DeviceAddress deviceAddress)
{
  Serial.println("enter printTemp function");
  String temp = printAddress(deviceAddress);    
  temp += ",";          //Delimter
  float tempC = owSensors.getTempC(deviceAddress);   //get temp from sensor
  temp += char(DallasTemperature::toFahrenheit(tempC));   // convert Celsius to F  
  Serial.print("about to return: ");  
  Serial.println(temp);
  return temp;
}


//create timesatamp to put in log
String createTimeStamp() {
  DateTime now = rtc.now();
  String stamp = String(now.year()) + "-" + String(now.month()) + "-" + String(now.day()) + " " + String(now.hour()) + ":" + String(now.minute()) + ":" + String(now.second());  //timestamp
  Serial.print("");
  Serial.println("");
  return stamp;
}


// send an NTP request to the time server at the given address 
unsigned long sendNTPpacket(IPAddress& address)
{
  // set all bytes in the buffer to 0
  memset(packetBuffer, 0, NTP_PACKET_SIZE); 
  // Initialize values needed to form NTP request
  // (see URL above for details on the packets)
  packetBuffer[0] = 0b11100011;   // LI, Version, Mode
  packetBuffer[1] = 0;     // Stratum, or type of clock
  packetBuffer[2] = 6;     // Polling Interval
  packetBuffer[3] = 0xEC;  // Peer Clock Precision
  // 8 bytes of zero for Root Delay & Root Dispersion
  packetBuffer[12]  = 49; 
  packetBuffer[13]  = 0x4E;
  packetBuffer[14]  = 49;
  packetBuffer[15]  = 52;

  // all NTP fields have been given values, now
  // you can send a packet requesting a timestamp: 		   
  Udp.beginPacket(address, 123); //NTP requests are to port 123
  Udp.write(packetBuffer,NTP_PACKET_SIZE);
  Udp.endPacket(); 
}

//update rtc from ntp
void updateNTP() {
  sendNTPpacket(timeServer);  //send ntp packet to timeserver
  delay(1000);                //wait to see if reply is available
  if (Udp.parsePacket() ) {   //check if packet recieved
    Udp.read(packetBuffer,NTP_PACKET_SIZE);  //read packet into the buffer
    
    //the timestamp starts at byte 40 of the received packet and is four bytes,
    // or two words, long. First, esxtract the two words:
    unsigned long highWord = word(packetBuffer[40], packetBuffer[41]);
    unsigned long lowWord = word(packetBuffer[42], packetBuffer[43]);  
    // combine the four bytes (two words) into a long integer
    // this is NTP time (seconds since Jan 1 1900):
    unsigned long secsSince1900 = highWord << 16 | lowWord;    
    //Serial.print("Seconds since Jan 1 1900 = " );
    //Serial.println(secsSince1900);             
    
    
    // now convert NTP time into everyday time:
    // Unix time starts on Jan 1 1970. In seconds, that's 2208988800:
    const unsigned long seventyYears = 2208988800UL;     
    // subtract seventy years:
    unsigned long epoch = secsSince1900 - seventyYears;  //unix time
    
   
    
    Serial.println("about to adjust rtc...");
    rtc.adjust(epoch);  //adjust rtc time - sample input: date = "Dec 26 2009", time = "12:34:56"
    
    //debugging output only
    DateTime now = rtc.now();
    Serial.println("End of updateNTP function- unixtime is: ");
    Serial.println(now.unixtime());
    
  }
}

//check for client request...
void listenForEthernetClients() {
  
  //listen for ethernet client
  EthernetClient client = server.available();
  if (client) {    
    //client has sent request -> send recent temp and humid data
    
    Serial.println("Request recieved");
    
    boolean currentLineIsBlank = true;  //http request ends in blank line
    char clientLine[BufferSize];
    char *filename;
    File file;
    int index = 0;
    
    
    while (client.connected()) {
      if (client.available()) {
        char c = client.read();
        if (c != '\n' && currentLineIsBlank) {  //newline means request is done
          clientLine[index] = c;
          index++;
          if (index >= BufferSize) {
            index = BufferSize - 1;
          }
          continue;
        }
        clientLine[index] = 0; //string is done, finish him!
      
        if (strstr(clientLine, "GET / ") != 0) {
          filename = rootFileName;
        }
        if (strstr(clientLine, "GET /") != 0) {
          // this time no space after the /, so a sub-file
          
          if (!filename) filename = clientLine + 5; // look after the "GET /" (5 chars)
          // a little trick, look for the " HTTP/1.1" string and
          // turn the first character of the substring into a 0 to clear it out.
          (strstr(clientLine, " HTTP"))[0] = 0; 
          
          file = SD.open(filename, FILE_READ);
          if (!file) {
            client.println("HTTP/1.1 404 Not Found");
            client.println("Content-Type: text/html");
            client.println();
            client.println("<h2>File Not Found!</h2>");
            break;
          }
          
          client.println("HTTP/1.1 200 OK");
         if (strstr(filename, ".htm") != 0)
           client.println("Content-Type: text/html");
         else
           client.println("Content-Type: text");
         client.println();
         
         int16_t c;
          while ((c = file.read()) >= 0) {
              // uncomment the serial to debug (slow!)
              //Serial.print((char)c);
              client.print((char)c);
          }
          file.close();
          
        }
      }
    }
    delay(1);    //give client time to recieve data
    client.stop();
  }
}


void updateTempsFile(String ts) {
  Serial.println("attempting to open TEMP.CSV");
  File tempFile = SD.open("TEMP.CSV", FILE_WRITE);
    if (tempFile) {
      //TODO: limit lines in file to const RecordLimit
      Serial.println("TEM.CSV is open");
      
      tempFile.print(printTemp(thermometerA));
      tempFile.println(ts);
      tempFile.print(printTemp(thermometerB));
      tempFile.println(ts);
      tempFile.print(printTemp(thermometerC));
      tempFile.println(ts);
    }
    tempFile.close();
    Serial.println("tempFile closed");        //dbg
}

void updateHumidFile(String ts) {
  Serial.println("attempting to open HUMID.CSV");
  File humidFile = SD.open("HUMID.CSV", FILE_WRITE);
  if (humidFile) {
    Serial.println("HUMID.CSV is open");
    //humidFile.print(dht.readHumidity());
    humidFile.println(ts);
  }
  humidFile.close();
  Serial.println("humidFile closed");
}

void loop() {
  
  Serial.println("loopin");
  listenForEthernetClients();   //server client 
  
  //Check Sensors------------------------
  
  if(timer > targetTime) {
    
    //NOTES:
    //ERR happens here, either in timestamp stuff or going to updateTempsFile()
    //also the SD.open() is not written correctly...
    
    Serial.println("timestamps stuff");     //dbg
    String ts = createTimeStamp(); // timestamp from rtc
    //check sensors and write data to csv file
    updateTempsFile(ts);
    updateHumidFile(ts);
    targetTime = millis() + TI;
  }
  timer = millis();
  
}

