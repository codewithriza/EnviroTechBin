#include <Servo.h>

// Define servo and sensor pins
Servo myservo;
int servoPin = 9;       // Connect servo to digital pin 9
int sensorPin = A0;     // Connect soil moisture sensor to analog pin A0
int irSensorPin = A1;   // Connect IR sensor to analog pin A1

// Define threshold values for dry and wet waste
int dryThreshold = 600; // Adjust this value based on your sensor readings
int wetThreshold = 550; // Adjust this value based on your sensor readings
int irThreshold = 120;  // Adjust this value based on your IR sensor readings

bool wasteDetected = false; // Flag to track waste detection

void setup() {
  myservo.attach(servoPin); // Attach the servo to the servo pin
  pinMode(sensorPin, INPUT);    // Set sensor pin as an input
  pinMode(irSensorPin, INPUT);  // Set IR sensor pin as an input
  Serial.begin(9600);           // Initialize serial communication
}

void loop() {
  int moistureLevel = analogRead(sensorPin); // Read soil moisture level
  int irValue = analogRead(irSensorPin);     // Read IR sensor value

  Serial.print("Moisture Level: ");
  Serial.println(moistureLevel);
  Serial.print("IR Sensor Value: ");
  Serial.println(irValue);

  // Check for object detection
  if (irValue < irThreshold) {
    wasteDetected = true;
    delay(1500); // Delay for 3 seconds if object detected by IR sensor
  } else {
    wasteDetected = false;
  }

  // If waste is detected, take action
  if (wasteDetected) {
    if (moistureLevel > dryThreshold) {
      turnServoRight(3); // Turn servo 30 degrees right for 3 seconds
    } else if (moistureLevel < wetThreshold) {
      turnServoLeft(3); // Turn servo 30 degrees left for 3 seconds
    }
  }

  delay(1000); // Delay for a moment to avoid rapid servo movement
}

void turnServoRight(int seconds) {
  myservo.write(0);     // Turn servo 30 degrees right
  delay(seconds * 1000); // Delay for the specified duration (in seconds)
  myservo.write(90);     // Return servo to the center position
  delay(1000);           // Delay to stabilize before further readings
}

void turnServoLeft(int seconds) {
  myservo.write(180);    // Turn servo 30 degrees left
  delay(seconds * 1000); // Delay for the specified duration (in seconds)
  myservo.write(90);     // Return servo to the center position
  delay(1000);           // Delay to stabilize before further readings
}
