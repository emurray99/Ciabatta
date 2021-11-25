
/*Hardware connections:
 * Connect TMP36 output to pin A0 on the Arduino.
 * Connect to 3.3V pin
 * Connect ground pin
 * Connect SD card reader to low voltage side of logic level converter
 * Connect arduino to high voltage side of logic level convertor
 * ON ARDUINO:
 *  13 - CLK
 *  12 - MOSI
 *  11 - MISO
 *  10 - CSN
 *  6 - red LED
 *  5 - green LED
*/

#include <SPI.h>
#include <SD.h>

File tmpDataFile;

//pin assignments
int tmp_input = 0;
int chip_select = 10;
int red_led = 6;
int green_led = 5;

//initialize variables
int analog_input;
float voltage;
float tmp;


void setup() {
  pinMode(red_led, OUTPUT);
  pinMode(green_led, OUTPUT);

  Serial.begin(9600);
  while (!Serial);
  
  if (!SD.begin(10)) {
    digitalWrite(red_led, HIGH);
    Serial.println("initialization failed!");
    while (1);
  }

  tmpDataFile = SD.open("data.txt", FILE_WRITE);
  digitalWrite(green_led, HIGH);
  Serial.println("initialization done.");
}


void loop() {
  //Step 1: Measure
  //read the analog input, convert to voltage value, convert to a temperature value
   analog_input = analogRead(tmp_input);
   voltage = analog_input * (5.0/1024.0); 
   tmp = (voltage - 0.5) * 100;

  //Step 2: Record
  //open and create file, print temperature value to file
  tmpDataFile = SD.open("data.txt", FILE_WRITE);
  if (tmpDataFile) {
    Serial.println("File created");
    digitalWrite(red_led, LOW);
    digitalWrite(green_led, HIGH);
    tmpDataFile.println(tmp);
    // close the file:
    tmpDataFile.close();
  } else {
    Serial.println("File NOT created");
    digitalWrite(red_led, HIGH);
    digitalWrite(green_led, LOW);
  }

  //Step 3: Delay
  delay(3000);
}
