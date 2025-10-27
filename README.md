🚌 Smart Bus Stop System

📖 Overview

The Smart Bus Stop System is an IoT-based project designed to improve the efficiency of public transport systems.
It detects the arrival of buses using RFID technology and provides real-time updates on an LCD display along with audio announcements using the DFPlayer Mini module.

This system helps passengers know exactly when their bus has arrived, making travel more convenient and smart.



⚙️ Hardware Used

Arduino Nano
RFID Reader (RC522)
RFID Tags (attached to buses)
LCD Display (16x2 or 20x4)
DFPlayer Mini (for audio announcements)
Speaker
Connecting Wires
Power Supply



🧠 Working Principle

Each bus is assigned a unique RFID tag.
When the bus approaches the bus stop, the RFID reader detects the tag.
The system identifies the bus and displays its arrival message on the LCD screen.
The DFPlayer Mini plays a pre-recorded audio file announcing the arrival of the bus.
After a short delay, the display resets to show “Waiting for bus...”



🧩 Features

✅ Real-time bus detection using RFID
✅ LCD display showing bus number and arrival status
✅ Audio announcement for bus arrival
✅ Compact design using Arduino Nano
✅ Low-cost, efficient IoT solution


💾 Arduino Code
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







👩‍💻 Team Members

Sanjana M (Project Lead)



📅 Developed For  
Smart Bus Stop – IoT Hackathon Project (2025)  
Department of Electrical and Electronics Engineering




---

🧾 **License**

This project is licensed under the [MIT License](LICENSE).



