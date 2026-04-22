/*
  Smart Helmet System - Transmitter (Helmet Side)
  Components: Arduino Uno, NRF24L01, MQ3, IR Sensor x2, LED, Buzzer
  Developed by: Ashish & Sneha
*/

#include <SPI.h>
#include <RF24.h>

RF24 radio(7, 8); // CE=D7, CSN=D8
const byte address[6] = "00001";

// Sensor Pins
#define MQ3_PIN     A0
#define DROWSY_PIN  A1
#define HELMET_PIN  A2

// Output Pins
#define LED_PIN     3
#define BUZZER_PIN  6

// Threshold
#define ALCOHOL_THRESHOLD 200

// Drowsiness timing
unsigned long drowsyStart = 0;
bool drowsyActive = false;

struct DataPacket {
  int alcohol;
  byte helmetWorn;
  byte drowsy;
};

void setup() {
  Serial.begin(9600);

  pinMode(HELMET_PIN, INPUT);
  pinMode(DROWSY_PIN, INPUT);
  pinMode(LED_PIN, OUTPUT);
  pinMode(BUZZER_PIN, OUTPUT);

  radio.begin();
  radio.setPALevel(RF24_PA_HIGH);
  radio.setDataRate(RF24_250KBPS);
  radio.setChannel(76);
  radio.openWritingPipe(address);
  radio.stopListening();

  Serial.println("Transmitter Ready!");
}

void loop() {
  DataPacket data;

  // MQ3 - Alcohol
  data.alcohol = analogRead(MQ3_PIN);

  // IR - Helmet Worn (LOW = worn)
  data.helmetWorn = (digitalRead(HELMET_PIN) == LOW) ? 1 : 0;

  // IR - Drowsiness (5 sec continuous detection)
  if (digitalRead(DROWSY_PIN) == LOW) {
    if (!drowsyActive) {
      drowsyStart = millis();
      drowsyActive = true;
    }
    if (millis() - drowsyStart >= 5000) {
      data.drowsy = 1;
    } else {
      data.drowsy = 0;
    }
  } else {
    drowsyActive = false;
    drowsyStart = 0;
    data.drowsy = 0;
  }

  // LED + Buzzer on helmet side
  if (data.alcohol > ALCOHOL_THRESHOLD || data.helmetWorn == 0 || data.drowsy == 1) {
    digitalWrite(LED_PIN, HIGH);
    digitalWrite(BUZZER_PIN, HIGH);
  } else {
    digitalWrite(LED_PIN, LOW);
    digitalWrite(BUZZER_PIN, LOW);
  }

  // Send data wirelessly
  bool sent = radio.write(&data, sizeof(data));

  // Debug
  Serial.print("Alcohol: "); Serial.print(data.alcohol);
  Serial.print(" | Helmet: "); Serial.print(data.helmetWorn);
  Serial.print(" | Drowsy: "); Serial.print(data.drowsy);
  Serial.print(" | Sent: "); Serial.println(sent ? "OK" : "FAIL");

  delay(100);
}
