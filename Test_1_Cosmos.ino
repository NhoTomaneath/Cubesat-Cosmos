
/* Created: 06/09/2021
 * Modified:  
 - 07/09/2021 Panha
 * E2stem Cubesat
   By Teacher oudom && Panha 12.2
*/
//Problem 01: 06-09-2021 sensor did not write Data after plug with power bank 


#include <Arduino_MKRENV.h>
#include <SD.h>
//#include <DS3232RTC.h>


const int cs = 4; //SD Card
//DS3231  rtc(SDA, SCL);
//int rtc;
//DS3231  rtc(11,12); // date && Time Sensor


void setup() {
  
  Serial.begin(9600);
  //rtc.begin();
  ENV_Shield();
  Initialize_SDcard();
  // Problem 01 Solved using this //
  pinMode(cs,OUTPUT); // <- 
  digitalWrite(cs,HIGH); // <-
  /////////////////////////////////
  //Serial.println("Temperature,Humidity,Pressure");
 
}
 

void ENV_Shield(){
 //while (!Serial); 
  if (!ENV.begin()) {
    Serial.println("Failed to initialize MKR ENV shield!"); 
    while (1); //True // False 0
  }
}

void Initialize_SDcard()
{
  // see if the card is present and can be initialized:
  if (!SD.begin(cs)) {
    Serial.println("SD Card failed");
    // don't do anything more:
    return;
  }
   // open the file. note that only one file can be open at a time,
  // so you have to close this one before opening another.
  File dataFile = SD.open("CubeSat.txt", FILE_WRITE);
  // if the file is available, write to it:
  if (dataFile) {
    dataFile.println("Date,Time,Temperature,Humidity,Pressure"); //Write the first row of the excel file
    dataFile.close();
  }
}


// function write SD card -> file.csv

void Write_SDcard()
{

  float temperature = ENV.readTemperature(); 
  float humidity    = ENV.readHumidity();
  float pressure    = ENV.readPressure();
  // send data to SD card
  File dataFile = SD.open("CubeSat.txt", FILE_WRITE);

  // if the file is available, write to it:
  if (dataFile) {
    /*dataFile.print(rtc.getDateStr()); //Store date on SD card
    dataFile.print(","); //Move to next column using a ","

    dataFile.print(rtc.getTimeStr()); //Store date on SD card
    dataFile.print(","); //Move to next column using a ","*/

    dataFile.print(temperature); //Store date on SD card
    dataFile.print(","); //Move to next column using a ","

    dataFile.print(humidity); //Store date on SD card
    dataFile.print(","); //Move to next column using a ","

    dataFile.print(pressure); //Store date on SD card
    dataFile.print(","); //Move to next column using a ","

    dataFile.println(); //End of Row move to next row
    dataFile.close(); //Close the file
  }
  else
  Serial.println("OOPS!! SD card writing failed");
}

/*void Initialize_RTC()
{
   // Initialize the rtc object
  rtc.begin();

rtc.setDOW(FRIDAY);     // Set Day-of-Week to SUNDAY
rtc.setTime(16, 05, 45);     // Set the time to 12:00:00 (24hr format)
rtc.setDate(9, 07, 2021);   // Set the date to January 1st, 2014 

}*/

void loop() {

  
  float temperature = ENV.readTemperature(); 
  float humidity    = ENV.readHumidity();
  float pressure    = ENV.readPressure();
  ENV_Shield();
  //Initialize_RTC();
  Write_SDcard();
  
  
  // Print Sensor Values
  Serial.println(" ");
  Serial.print(temperature);
  Serial.print("  ||  ");
  Serial.print(humidity);
  Serial.print("  ||  ");
  Serial.print(pressure);
  Serial.println("  ||  ");
  Serial.println(); 

  delay(500);
}
