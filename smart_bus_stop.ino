#include <SPI.h>
#include <MFRC522.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include "SoftwareSerial.h"
#include "DFRobotDFPlayerMini.h"

// RFID
#define SS_PIN 10
#define RST_PIN 9
MFRC522 rfid(SS_PIN, RST_PIN);

// DFPlayer
SoftwareSerial mySerial(7, 8); // RX, TX for DFPlayer (no conflict)
DFRobotDFPlayerMini myDFPlayer;

// LCD
LiquidCrystal_I2C lcd(0x27, 16, 2);

void setup() {
  Serial.begin(9600);

  // RFID setup
  SPI.begin();
  rfid.PCD_Init();
  Serial.println("RFID ready");

  // DFPlayer setup
  mySerial.begin(9600);
  if (!myDFPlayer.begin(mySerial)) {
    Serial.println("DFPlayer Mini init failed!");
    while (true);
  }
  Serial.println("DFPlayer ready");
  myDFPlayer.volume(30);

  // LCD setup
  lcd.init();
  lcd.backlight();
  lcd.setCursor(0, 0);
  lcd.print("Waiting for bus...");
}

void loop() {
  if (!rfid.PICC_IsNewCardPresent() || !rfid.PICC_ReadCardSerial()) {
    return;
  }

  Serial.print("Card UID: ");
  for (byte i = 0; i < rfid.uid.size; i++) {
    Serial.print(rfid.uid.uidByte[i] < 0x10 ? " 0" : " ");
    Serial.print(rfid.uid.uidByte[i], HEX);
  }
  Serial.println();

  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("The bus 245");
  lcd.setCursor(0, 1);
  lcd.print("has arrived");

  myDFPlayer.play(1);

  delay(3000);
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Waiting for bus...");

  rfid.PICC_HaltA();
  rfid.PCD_StopCrypto1();
}
