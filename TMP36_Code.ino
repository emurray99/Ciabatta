
/*Hardware connections:
 * Connect TMP36 output to pin A0 on the Arduino.
 * Connect to 3.3V pin
 * Connect ground pin
 */

#include <SPI.h>
#include <SD.h>

File temperatureDataFile;

int temperature_sensor_input_pin = 0;
int analog_input;
float voltage_reading;
float temperature;
int chip_select_pin = 10;
int red_led_pin = 6;
int green_led_pin = 5;

void setup() {
  // put your setup code here, to run once:

  pinMode(red_led_pin, OUTPUT);
  pinMode(green_led_pin, OUTPUT);

   Serial.begin(9600);
    while (!Serial) {
    ;
  }
  
   if (!SD.begin(10)) {
    digitalWrite(red_led_pin, HIGH);
    Serial.println("initialization failed!");
    while (1);
  }
  Serial.println("initialization done.");

  temperatureDataFile = SD.open("data.txt", FILE_WRITE);

  digitalWrite(green_led_pin, HIGH);
}

void loop() {
  // put your main code here, to run repeatedly:
  
  //Step 1: Measure
  
  // read the analog input
   analog_input = analogRead(temperature_sensor_input_pin);
  
   // convert analog input to a voltage value
   voltage_reading = analog_input * (5.0/1024.0); 
  
   // convert voltage value to a temperature value
   temperature = (voltage_reading - 0.5) * 100;

  //Step 2: Record

  temperatureDataFile = SD.open("data3.txt", FILE_WRITE);
  if (temperatureDataFile) {
    Serial.println("File created");
    digitalWrite(red_led_pin, LOW);
    digitalWrite(green_led_pin, HIGH);
    temperatureDataFile.println(temperature);
    // close the file:
    temperatureDataFile.close();
  } else {
    Serial.println("File NOT created");
    digitalWrite(red_led_pin, HIGH);
    digitalWrite(green_led_pin, LOW);
  }

  //Step 3: Delay
  delay(3000);
}
