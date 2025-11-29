#include <Wire.h>
#include <WiFi.h>
#include <DHT.h>
#include <PubSubClient.h>
#include <Arduino.h>
#include <LiquidCrystal_I2C.h>
#include <HTTPClient.h>

// Informations pour ThingSpeak
const char* WIFI_NAME = "Wokwi-GUEST";          // Nom du réseau WiFi
const char* WIFI_PASSWORD = "";                // Mot de passe WiFi
const int myChannelNumber = 2776514;           // Channel ID de ThingSpeak
const char* myApiKey = "VGUU8CD8C4IO6SPK";     // API Key de ThingSpeak
const char* server = "http://api.thingspeak.com"; // Serveur ThingSpeak

// Configuration de l'écran LCD
#define lcd_ADDR 0x27
#define lcd_COLUMNS 16
#define lcd_ROWS 2
LiquidCrystal_I2C lcd(lcd_ADDR, lcd_COLUMNS, lcd_ROWS);

// Définir les broches pour le capteur et les LEDs
#define PULSE_PIN 35
#define redLEDPin 12
#define greenLEDPin 14

// Limites de fréquence cardiaque
int minHeartRate = 60;
int maxHeartRate = 100;

// Variables pour gérer la fréquence cardiaque
int heartRate = 0;

void setup() {
  // Initialisation de l'écran LCD
  lcd.init();
  lcd.backlight();
  Wire.begin(23, 22);
  Serial.begin(115200);
  lcd.print("Heart Monitor");

  // Configurer les LEDs
  pinMode(redLEDPin, OUTPUT);
  pinMode(greenLEDPin, OUTPUT);

  // Connexion au WiFi
  connectToWiFi();
}

void loop() {
  // Lire la fréquence cardiaque
  int16_t pulseValue = analogRead(PULSE_PIN);
  float voltage = pulseValue * (3.3 / 4095.0);  // Conversion en tension
  heartRate = (voltage / 3.3) * 675;            // Calcul de la fréquence cardiaque

  // Afficher la fréquence cardiaque sur LCD
  displayHeartRate(heartRate);

  // Envoyer les données à ThingSpeak immédiatement (sans délai)
  sendToThingSpeak(heartRate);

  delay(600); // Délai léger pour éviter une surcharge inutile
}

void connectToWiFi() {
  WiFi.begin(WIFI_NAME, WIFI_PASSWORD);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting to WiFi...");
  }
  Serial.println("Connected to WiFi");
}

void displayHeartRate(int heartRate) {
  lcd.clear();
  if (heartRate < minHeartRate) {
    lcd.print("Heart rate low:");
    lcd.setCursor(0, 1);
    lcd.print(heartRate);
    lcd.print(" b/m");
    digitalWrite(redLEDPin, HIGH);
    digitalWrite(greenLEDPin, LOW);
  } else if (heartRate > maxHeartRate) {
    lcd.print("Heart rate high:");
    lcd.setCursor(0, 1);
    lcd.print(heartRate);
    lcd.print(" b/m");
    digitalWrite(redLEDPin, HIGH);
    digitalWrite(greenLEDPin, LOW);
  } else {
    lcd.print("Heart Monitor");
    lcd.setCursor(0, 1);
    lcd.print("Rate: ");
    lcd.print(heartRate);
    lcd.print(" b/m");
    digitalWrite(redLEDPin, LOW);
    digitalWrite(greenLEDPin, HIGH);
  }
}

void sendToThingSpeak(int heartRate) {
  if (WiFi.status() == WL_CONNECTED) {
    HTTPClient http;
    String url = String(server) + "/update?api_key=" + myApiKey + "&field1=" + String(heartRate);
    http.begin(url); // Initialiser la requête HTTP
    int httpResponseCode = http.GET(); // Envoyer la requête GET

    if (httpResponseCode > 0) {
      Serial.print("Data sent to ThingSpeak. HTTP Response code: ");
      Serial.println(httpResponseCode);
    } else {
      Serial.print("Error sending data to ThingSpeak. HTTP Response code: ");
      Serial.println(httpResponseCode);
    }
    http.end(); // Fermer la connexion
  } else {
    Serial.println("WiFi not connected");
  }
}
