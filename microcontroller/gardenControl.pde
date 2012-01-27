//Garden Controller, made for arduino by Travis McCann
#include <DHT.h>
#include <OneWire.h>
#include <DallasTemperature.h>


#define ONE_WIRE_BUS 2  // dallas onewire Data wire is plugged into port 2 on the Arduino
#define TEMPERATURE_PRECISION 9
#define DHTPIN 3      //dht-22 is on pin 3
#define DHTTYPE DHT22  //working with a dht-22  (vs dht-11 or dht-21)
#define RELAY01 4     // relay01 is on pin 5   low power relay
#define RELAY02 5     // relay02 is on pin 6   low power relay
#define RELAY03 6     // relay03 is on pin 7   low power relay
#define RELAY04 7     // relay04 is on pin 8   high power relay
#define RELAY05 8     // relay05 is on pin 9   high power relay
#define RELAY06 9     // relay06 is on pin 9   high power relay

OneWire oneWire(ONE_WIRE_BUS);             // Setup a oneWire instance to communicate with any OneWire devices (not just Maxim/Dallas temperature ICs)

DallasTemperature owSensors(&oneWire);     // Pass our oneWire reference to Dallas Temperature. 

DeviceAddress thermometerA, thermometerB, thermometerC;  // arrays to hold device addresses

DHT dht(DHTPIN, DHTTYPE);
unsigned long counter = 0;    //use to instead of delay()  must check read every cycle too..

String command = "";        //string to hold command
boolean hasCommand = false; //bool to test if command is present

void setup(void)
{
  pinMode(RELAY01,OUTPUT);
  pinMode(RELAY02,OUTPUT);
  pinMode(RELAY03,OUTPUT);
  pinMode(RELAY04,OUTPUT);
  pinMode(RELAY05,OUTPUT);
  pinMode(RELAY06,OUTPUT);
  
  Serial.begin(9600);     // start serial port

  owSensors.begin();      // Start up the dallas one wire library
  dht.begin();            // Start up the dht library

  // locate devices on the bus
  Serial.print("Locating devices...");
  Serial.print("Found ");
  Serial.print(owSensors.getDeviceCount(), DEC);
  Serial.println(" devices.");

  // report parasite power requirements
  Serial.print("Parasite power is: "); 
  if (owSensors.isParasitePowerMode()) Serial.println("ON");
  else Serial.println("OFF");

  // search for devices on the bus and assign based on an index.  ideally,
  // you would do this to initially discover addresses on the bus and then 
  // use those addresses and manually assign them (see above) once you know 
  // the devices on your bus (and assuming they don't change).
  // 
  // method 1: by index
  if (!owSensors.getAddress(thermometerA, 0)) Serial.println("Unable to find address for Device 0"); 
  if (!owSensors.getAddress(thermometerB, 1)) Serial.println("Unable to find address for Device 1"); 
  if (!owSensors.getAddress(thermometerC, 2)) Serial.println("Unable to find address for Device 2"); 


  // show the addresses we found on the bus
  Serial.print("Device 0 Address: ");
  printAddress(thermometerA);
  Serial.println();
  Serial.print("Device 1 Address: ");
  printAddress(thermometerB);
  Serial.println();
  Serial.print("Device 2 Address: ");
  printAddress(thermometerC);
  Serial.println();

  // set the resolution
  owSensors.setResolution(thermometerA, TEMPERATURE_PRECISION);
  owSensors.setResolution(thermometerB, TEMPERATURE_PRECISION);
  owSensors.setResolution(thermometerC, TEMPERATURE_PRECISION);


}

// function to print a device address
void printAddress(DeviceAddress deviceAddress)
{
  for (uint8_t i = 0; i < 8; i++)
  {
    // zero pad the address if necessary
    if (deviceAddress[i] < 16) Serial.print("0");
    Serial.print(deviceAddress[i], HEX);
  }
}

// main function to print information about a device, formatted for software parsing on the other end
void printData(DeviceAddress deviceAddress)
{
  Serial.print("T:");        // command for type, T=temp H=humid
  printAddress(deviceAddress);
  Serial.print(":");          //Delimter
  float tempC = owSensors.getTempC(deviceAddress);   //get temp from sensor
  Serial.print(DallasTemperature::toFahrenheit(tempC));   // convert Celsius to F       
  Serial.println();
}

void printHumid()
{
  Serial.print("H:");
  Serial.print(dht.readHumidity());
  Serial.println();
}

void reply(String command) {
  //send recieved data back to host.  
  //TODO: add crc (add binary data to send back and host does same conversion to check against)
  Serial.print("recieved:");
  Serial.println(command);
}
void loop(void)
{   
  //see if there is a command to process
  while(Serial.available()) {
    char inChar = Serial.read(); //get the new byte
    command += inChar; //add it to command String
    
    if(inChar == 46) {  //test for "." delimiter for end sequence (had trouble picking up new line..)
      hasCommand = true;
    }
  }
 
  if (hasCommand) {
    //command should be formatted like "1:on," or "2:off,"    
    
    int delimPos = command.indexOf(":");
    int len = command.length();
    String cmd = command.substring(0,delimPos);
    String relayPos = command.substring(delimPos+1,len-1);    //start after delim, remove the "," delim at end
    
    switch (cmd.charAt(0)) {
      case 49:     //ascii '1'
        //relay01
        if( relayPos == "on"){
          digitalWrite(RELAY01, HIGH);
          reply(command);
        } else  if (relayPos == "off"){
          digitalWrite(RELAY01, LOW);
          reply(command);
        }
        break;
      case 50:   //ascii '2'
        //relay02
        if( relayPos == "on"){
          digitalWrite(RELAY02, HIGH);
          reply(command);
        } else if (relayPos == "off"){
          digitalWrite(RELAY02, LOW);
          reply(command);
        }
        break;
      case 51:     //ascii '3'
        //relay03
        if( relayPos == "on"){
          digitalWrite(RELAY03, HIGH);
          reply(command);
        } else if (relayPos == "off"){
          digitalWrite(RELAY03, LOW);
          reply(command);
        }
        break;
      case 52: //ascii '4'
        if( relayPos == "on"){
          digitalWrite(RELAY04, HIGH);
          reply(command);
        } else if (relayPos == "off"){
          digitalWrite(RELAY04, LOW);
          reply(command);
        }
        break;
      case 53:   //ascii '5'
        if( relayPos == "on"){
          digitalWrite(RELAY05, HIGH);
          reply(command);
        } else if (relayPos == "off"){
          digitalWrite(RELAY05, LOW);
          reply(command);
        }
        break;
      case 54:  //ascii '6'
        if( relayPos == "on"){
          digitalWrite(RELAY05, HIGH);
          reply(command);
        } else if (relayPos == "off"){
          digitalWrite(RELAY05, LOW);
          reply(command);
        }
        break;
      case 84:    //ascii 'T'
         owSensors.requestTemperatures();  // request to all devices on the bus
  
        // print the device information
        printData(thermometerA);
        printData(thermometerB);
        printData(thermometerC);
        break;
      case 72:    //ascii 'H'
        printHumid();
        break;
    }
    
    //cleanup
    command = "";
    hasCommand = false;
  }
  
 
  
}


