#include <SD.h>
#include <ctype.h>
File myFile;
struct parameters {
  int interval;
  boolean co2;
  boolean temp;
  boolean rh;
  boolean lux;
  boolean valid;
  boolean heater;
  String lokaal;
} settings;
// Setting for SD-card reader
const int chipSelect = 10;
void getSettings()
{
 // Open the settings file for reading:
  myFile = SD.open("settings.txt");
  char character;
  String description = "";
  String value = "";
  boolean valid = true;
    // read from the file until there's nothing else in it:
    while (myFile.available()) {
      character = myFile.read();
             if(character == '/')         {
               // Comment - ignore this line
               while(character != '\n'){
                 character = myFile.read();
               };
      } else if(isalnum(character))      {  // Add a character to the description
        description.concat(character);
      } else if(character =='=')         {  // start checking the value for possible results
      // First going to trim out all trailing white spaces
      do {
        character = myFile.read();
      } while(character == ' ');
        if(description == "interval") {
          value = "";
          while(character != '\n') {
            if(isdigit(character)) {
              value.concat(character);
            } else if(character != '\n') {
              // Use of invalid values
              valid = false;
            }
            character = myFile.read();            
          };
          if (valid) { 
            // Convert string to array of chars
            char charBuf[value.length()+1];
            value.toCharArray(charBuf,value.length()+1);
            // Convert chars to integer
            settings.interval = atoi(charBuf);
          } else {
            // revert to default value for invalid entry in settings
            settings.interval = 60;
          }
        } else if(description == "co2") {
           if (character=='1') {
             settings.co2 = true;
           } else {
             settings.co2 = false;
           }
        } else if(description == "rh") {
           if (character=='1') {
             settings.rh = true;
           } else {
             settings.rh = false;
           }        
        } else if(description == "temp") {
           if (character=='1') {
             settings.temp = true;
           } else {
             settings.temp = false;
           }
        } else if(description == "lux") {
           if (character=='1') {
             settings.lux = true;
           } else {
             settings.lux = false;
           }        
        } else if(description == "heater") {
           if (character=='1') {
             settings.heater = true;
           } else {
             settings.heater = false;
           }        
        } else if(description == "location") {
           value = "";
           do {
             value.concat(character);
             character = myFile.read();
           } while(character != '\n');
           settings.lokaal = value;
        
        }else { // unknown parameter
          while(character != '\n')
          character = myFile.read();
        }
        description = "";
      } else {
        // Ignore this character (could be space, tab, newline, carriage return or something else)
      }
    
    }
    // close the file:
    myFile.close();
}
void setup()
{
 // Open serial communications and wait for port to open:
  Serial.begin(9600);
   while (!Serial) {
    ; // wait for serial port to connect. Needed for Leonardo only
  }
  Serial.println("Starting...");
  pinMode(10, OUTPUT);
  
  if (!SD.begin(chipSelect)) {
    Serial.println("initialization failed!");
    return;
  }
  getSettings();
  Serial.print("Interval: ");
  Serial.println(settings.interval);
  Serial.print("CO2: ");
  if(settings.co2) { Serial.println("YES"); } else { Serial.println("NO"); }
  Serial.print("TEMP:");
  if(settings.temp) { Serial.println("YES"); } else { Serial.println("NO"); }
  Serial.print("RH:  ");
  if(settings.rh) { Serial.println("YES"); } else { Serial.println("NO"); }
  Serial.print("lux: ");
  if(settings.lux) { Serial.println("YES"); } else { Serial.println("NO"); }
  Serial.print("htr: ");
  if(settings.heater) { Serial.println("YES"); } else { Serial.println("NO"); }
  Serial.print("Lokaal: ");
  Serial.println(settings.lokaal);
  
}
void loop()
{
	// nothing happens after setup
}
