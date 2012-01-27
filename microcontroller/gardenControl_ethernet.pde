
#include <SD.h>
#include <DallasTemperature.h>
#include <OneWire.h>
#include <DHT.h>
#include <Udp.h>
#include <Ethernet.h>
#include <Client.h>
#include <Server.h>
#include <SPI.h>

#define ONE_WIRE_BUS 0    //PIN0
#define TEMPERATURE_PRECISION 9
#define DHTPIN 1     //PIN 1
#define DHTTYPE DHT22
#define RELAY01 2   //PIN2
#define RELAY02 3   //PIN3
#define RELAY03 5   //PIN5
#define RELAY04 6   //PIN6
#define RELAY05 7   //PIN7
#define SDCS 4   // sd card chip select pin on ethernet shield

const int RecordLimit = 1000;  //limit number of records kept on SD card
const unsigned long TI = 10000;  //Timer Increment, number of milliseconds to write sensor data at
const int BufferSize = 100;   //client read buffer size

OneWire oneWire(ONE_WIRE_BUS);             // Setup a oneWire instance to communicate with any OneWire devices (not just Maxim/Dallas temperature ICs)

DallasTemperature owSensors(&oneWire);     // Pass our oneWire reference to Dallas Temperature. 

DeviceAddress thermometerA, thermometerB, thermometerC;  // arrays to hold device addresses.  You must create one for each DX18B20 you have connected

DHT dht(DHTPIN, DHTTYPE);

byte mac[]     = {0x90, 0xA2, 0xDA, 0x01, 0x00, 0xEF};  
byte ip[]      = {192,168,1,25};
byte gateway[] = {192,168,1,1};
byte subnet[]  = {255,255,255,0};
char rootFileName[] = "temp.csv";
Server server(723); //open server on port 723 (random port)

unsigned long timer = millis();        // timer to time sensor readings
unsigned long targetTime = millis();   //


void setup(void)
{
  pinMode(RELAY01,OUTPUT);
  pinMode(RELAY02,OUTPUT);
  pinMode(RELAY03,OUTPUT);
  pinMode(RELAY04,OUTPUT);
  pinMode(RELAY05,OUTPUT);
  
  Ethernet.begin(mac, ip);
  server.begin();
  SD.begin(SDCS);
  owSensors.begin();      // Start up the dallas one wire library
  dht.begin();            // Start up the dht library
  
  
  delay(500);  //delay to let ethernet setup
  owSensors.getAddress(thermometerA, 0);
  owSensors.getAddress(thermometerB, 1);
  owSensors.getAddress(thermometerC, 2);
  owSensors.setResolution(thermometerA, TEMPERATURE_PRECISION);
  owSensors.setResolution(thermometerB, TEMPERATURE_PRECISION);
  owSensors.setResolution(thermometerC, TEMPERATURE_PRECISION);
  
}

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

String printTemp(DeviceAddress deviceAddress)
{
  String temp = printAddress(deviceAddress);    
  
  temp += ",";          //Delimter
  float tempC = owSensors.getTempC(deviceAddress);   //get temp from sensor
  temp += char(DallasTemperature::toFahrenheit(tempC));   // convert Celsius to F       
  return temp;
}

void loop() {
  
  
  
  //listen for ethernet client
  Client client = server.available();
  if (client) {    
    //client has sent request -> send recent temp and humid data
    
    boolean currentLineIsBlank = true;  //http request ends in blank line
    char clientLine[BufferSize];
    char *filename;
    File file;
    int index = 0;
    
    
    while (client.connected()) {
      if (client.available()) {
        char c = client.read();
        if (c != '\n' && c != '\r') {  //newline means request is done
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
  
  //Done with server stuff---------------
  //Check Sensors------------------------
  
  if(timer > targetTime) {
    //check sensors and write data to csv file
    File tempFile = SD.open("temp.csv", FILE_WRITE);
    if (tempFile) {
      //TODO: limit lines in file to const RecordLimit
      
      
      tempFile.println(printTemp(thermometerA));
      tempFile.println(printTemp(thermometerB));
      tempFile.println(printTemp(thermometerC));
      
    }
    tempFile.close();
    File humidFile = SD.open("humid.csv", FILE_WRITE);
    if (humidFile) {
      humidFile.println(dht.readHumidity());
      
      
    }
    humidFile.close();
    targetTime = millis() + TI;
  }
  timer = millis();
  
}
