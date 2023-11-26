#define BLYNK_TEMPLATE_ID ""
#define BLYNK_TEMPLATE_NAME ""
#define BLYNK_AUTH_TOKEN ""

#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>

// WiFi credentials
char ssid[] = "codewithriza";
char password[] = "typeyourpassword";

// Blynk authentication token
char auth[] = "";

// Virtual pins for the ultrasonic sensors in Blynk
#define ULTRASONIC_PIN_1 V1
#define ULTRASONIC_PIN_2 V2

// Define trigger and echo pins for the ultrasonic sensors
const int trigPin_1 = D3; // Trig Pin for sensor 1
const int echoPin_1 = D4; // Echo Pin for sensor 1
const int trigPin_2 = D5; // Trig Pin for sensor 2
const int echoPin_2 = D6; // Echo Pin for sensor 2

// Variables for distance calculation
long duration_1, distance_1;
long duration_2, distance_2;

void setup() {
  Serial.begin(9600);

  // Initialize ultrasonic sensor pins
  pinMode(trigPin_1, OUTPUT);
  pinMode(echoPin_1, INPUT);
  pinMode(trigPin_2, OUTPUT);
  pinMode(echoPin_2, INPUT);

  // Connect to Wi-Fi
  Blynk.begin(auth, ssid, password);
}

void loop() {
  // Measure distance for sensor 1
  digitalWrite(trigPin_1, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin_1, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin_1, LOW);
  duration_1 = pulseIn(echoPin_1, HIGH);
  distance_1 = (duration_1 * 0.034) / 2;

  // Measure distance for sensor 2
  digitalWrite(trigPin_2, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin_2, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin_2, LOW);
  duration_2 = pulseIn(echoPin_2, HIGH);
  distance_2 = (duration_2 * 0.034) / 2;

  // Print distances to serial monitor
  Serial.print("Distance Sensor 1: ");
  Serial.print(distance_1);
  Serial.println(" cm");
  Serial.print("Distance Sensor 2: ");
  Serial.print(distance_2);
  Serial.println(" cm");

  // Send distances to Blynk app
  Blynk.virtualWrite(ULTRASONIC_PIN_1, distance_1);
  Blynk.virtualWrite(ULTRASONIC_PIN_2, distance_2);

  delay(1000); // Adjust delay as needed for reading frequency
  Blynk.run();
}

