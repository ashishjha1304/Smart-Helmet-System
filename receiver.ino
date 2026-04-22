/*
  Smart Helmet System - Receiver (Bike Side)
  Components: Arduino Uno, NRF24L01, LCD I2C 16x2, Relay, LED, Buzzer, Motor
  Developed by: Ashish & Sneha
*/

#include <SPI.h>
#include <RF24.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>

RF24 radio(7, 8); // CE=D7, CSN=D8
const byte address[6] = "00001";

LiquidCrystal_I2C lcd(0x27, 16, 2);

// Output Pins
#define RELAY_PIN   3
#define LED_PIN     5
#define BUZZER_PIN  6

// Thresholds
#define ALCOHOL_THRESHOLD 200
#define SIGNAL_TIMEOUT    500

unsigned long lastReceived = 0;

struct DataPacket {
  int alcohol;
  byte helmetWorn;
  byte drowsy;
};

void setup() {
  Serial.begin(9600);

  pinMode(RELAY_PIN, OUTPUT);
  pinMode(LED_PIN, OUTPUT);
  pinMode(BUZZER_PIN, OUTPUT);

  // Motor ON initially
  digitalWrite(RELAY_PIN, HIGH);

  lcd.init();
  lcd.backlight();
  lcd.setCursor(0, 0);
  lcd.print("Smart Helmet");
  lcd.setCursor(0, 1);
  lcd.print("Initializing...");

  radio.begin();
  radio.setPALevel(RF24_PA_HIGH);
  radio.setDataRate(RF24_250KBPS);
  radio.setChannel(76);
  radio.openReadingPipe(0, address);
  radio.startListening();

  Serial.println("Receiver Ready!");
  delay(2000);
  lcd.clear();
}

void loop() {
  DataPacket data;

  if (radio.available()) {
    radio.read(&data, sizeof(data));
    lastReceived = millis();

    Serial.print("Alcohol: "); Serial.print(data.alcohol);
    Serial.print(" | Helmet: "); Serial.print(data.helmetWorn);
    Serial.print(" | Drowsy: "); Serial.println(data.drowsy);

    if (data.helmetWorn == 0) {
      // Helmet not worn
      digitalWrite(RELAY_PIN, LOW);
      digitalWrite(LED_PIN, HIGH);
      digitalWrite(BUZZER_PIN, HIGH);
      lcd.setCursor(0, 0);
      lcd.print("Helmet Not Worn!");
      lcd.setCursor(0, 1);
      lcd.print("Please Wear It! ");

    } else if (data.alcohol > ALCOHOL_THRESHOLD) {
      // Alcohol detected
      digitalWrite(RELAY_PIN, LOW);
      digitalWrite(LED_PIN, HIGH);
      digitalWrite(BUZZER_PIN, HIGH);
      lcd.setCursor(0, 0);
      lcd.print("Alcohol Detected");
      lcd.setCursor(0, 1);
      lcd.print("Don't Drive!    ");

    } else if (data.drowsy == 1) {
      // Drowsiness detected
      digitalWrite(RELAY_PIN, LOW);
      digitalWrite(LED_PIN, HIGH);
      digitalWrite(BUZZER_PIN, HIGH);
      lcd.setCursor(0, 0);
      lcd.print("Drowsiness!     ");
      lcd.setCursor(0, 1);
      lcd.print("Take a Break!   ");

    } else {
      // All OK - Motor ON
      digitalWrite(RELAY_PIN, HIGH);
      digitalWrite(LED_PIN, LOW);
      digitalWrite(BUZZER_PIN, LOW);
      lcd.setCursor(0, 0);
      lcd.print("All OK!         ");
      lcd.setCursor(0, 1);
      lcd.print("Safe to Drive!  ");
    }
  }

  // Signal loss detection
  if (millis() - lastReceived > SIGNAL_TIMEOUT && lastReceived != 0) {
    digitalWrite(RELAY_PIN, LOW);
    digitalWrite(LED_PIN, HIGH);
    digitalWrite(BUZZER_PIN, HIGH);
    lcd.setCursor(0, 0);
    lcd.print("Signal Lost!    ");
    lcd.setCursor(0, 1);
    lcd.print("Check Helmet!   ");
  }
}
