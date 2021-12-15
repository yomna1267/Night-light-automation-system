#include <Servo.h> 
Servo myservo; // Create servo object to control a servo
int pos = 0;   // Variable to store the servo position
int led1 = 13; // LED connected to digital pin 13
int led2 = 12; // LED connected to digital pin 12
int led3 = 11; // LED connected to digital pin 11
int ledSensor = A0; // LDR connected to analog pin A0
int sensorValue = 0; 
int trig = 10; // Ultrasonic sonic's trigger pin connected to digital pin 10
int echo = 8; // Ultrasonic sonic's echo pin connected to digital pin 10
long duration; 
long distance;

void setup()
{
  pinMode(led1, OUTPUT); // Set led1 as output
  pinMode(led2, OUTPUT); // Set led2 as output
  pinMode(led3, OUTPUT); // Set led3 as output
  pinMode(ledSensor, INPUT); // Set ledSensor as input
  pinMode(trig, OUTPUT); // Set trig as output
  pinMode(echo, INPUT);  // Set echo as input
  myservo.attach(9); // Attach the servo on pin 9 
  Serial.begin(9600);
}
// Check if someone enters the room in the dark to turn on LEDs
void check()
{
  sensorValue = analogRead(ledSensor); //Store intensity of illumination using LDR as a sensor 
  digitalWrite(trig, LOW);  // Make sure that there are no ultrasonic signals  out of  the sensor
  delayMicroseconds(2); 
  digitalWrite(trig, HIGH); // Issuing some waves for a 10 microseconds
  delayMicroseconds(10); 
  digitalWrite(trig, LOW); // Stop waves
  duration = pulseIn(echo, HIGH); // Calculate how long the waves have taken to return 
  distance = (duration/2) / 29.1; // Calculate distanse in centimeters

  // Check if someone enters the room "near to Ultrasonic" in the dark "intensity of illumination is less than 300" to turn on LEDs
  Serial.print("ledSensor: ");
  Serial.println(sensorValue);
  Serial.print("distance: ");
  Serial.println(distance);
  if(sensorValue <= 400 && distance < 300) //you are free to change 300cm
  {
    digitalWrite(led1, HIGH);
    digitalWrite(led2, HIGH);
    digitalWrite(led3, HIGH);
  }  
  else 
  {
    digitalWrite(led1, LOW);
    digitalWrite(led2, LOW);
    digitalWrite(led3, LOW);
  }
  
}
// Start
void loop()
{
   // Go from 0 degrees to 180 degrees in steps of 1 degree     
  for (pos = 0; pos <= 180; pos += 1) 
       { 
        myservo.write(pos); // Tell servo to go to position in variable "pos"
        check();
        delay(15); // Waits 15ms
       } 
   // Go from 180 degrees to 0 degrees in steps of 1 degree     
    for (pos = 180; pos >= 0; pos -= 1) 
       { 
        myservo.write(pos);
        check();
        delay(15);
       } 
 
}