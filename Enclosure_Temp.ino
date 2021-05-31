/*
  AUTHOR: Jordan Anderson
  DESCRIPTION: 
  This program is a prototype for a 3D printer encloser tempreture control.
  It uses a DHT11 temperature and humidity sensor to determine the speed of
  a DC fan motor.
  GITHUB: https://github.com/Jordan-M-Anderson
*/

// dht libraries 
#include "DHT.h"
// input from digital pin 2
#define DHTPIN 2
#define DHTTYPE DHT11

// object refrence to the DHT library
DHT dht(DHTPIN, DHTTYPE);

float temp;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  Serial.println("Start:");
  // dht sensor wake up
  dht.begin();
  dht.read();
  // set pins 8, 9, and 10 to send output
  pinMode(8, OUTPUT);
  pinMode(9, OUTPUT);
  // control pin
  pinMode(10, OUTPUT);
  
}

void loop() {
  // put your main code here, to run repeatedly:
  // variable to control the power of the motor
  int powerValue;
  
  // variable to set the min start temp of the motor 
  int minStartTemp = 25;
  
  // max motor speed at maxTemp
  int maxTemp = 40; 
  
  // assigns temp to the input from dht
  temp = dht.convertCtoF(dht.readTemperature());

  // creates a corresponding value from the temp to the speed of the motor
  powerValue = map(temp, minStartTemp, maxTemp, 100, 255);

  if(temp >= minStartTemp - 1){
    digitalWrite(8, HIGH);
    digitalWrite(9, LOW);
    
    // sets the motor speed to the powerValue
    analogWrite(10, powerValue);
  } else{
      // sets the motor speed to 0
      analogWrite(10, 0);
  }

  //***DEBUG***
  Serial.print("Temperature = ");
  Serial.print(temp);
  Serial.print(" Degrees C\t");
  
  Serial.print("Speed = "); 
  Serial.print(powerValue);
  Serial.println("\t");
  //**DEBUG***

  // deley of loop in milliseconds
  delay(1000);
}
