#include <ESP32Servo.h>
#include <SPI.h>
#include <MFRC522.h>
#include <WiFi.h>
#include <HTTPClient.h>

// Pin Setup untuk Servo
const int servoPin = 27;  // Sekarang pakai GPIO 27

// Pin Setup untuk RFID
#define RST_PIN 22
#define SS_PIN 5
MFRC522 mfrc522(SS_PIN, RST_PIN);  // Instance untuk modul RFID

Servo myServo;

// Wi-Fi Setup
const char* ssid = "mangle";
const char* password = "Mangle03";

// Fungsi untuk membuka kunci pintu
void openLock() {
  myServo.write(90);  // Buka pintu
  delay(2000);        // Tahan 2 detik
  myServo.write(0);   // Tutup pintu
}

void setup() {
  Serial.begin(9600);
  
  // Inisialisasi Wi-Fi
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting to WiFi...");
  }
  Serial.println("Connected to WiFi");

  // Inisialisasi RFID
  SPI.begin();        // SPI default ESP32: MOSI=23, MISO=19, SCK=18
  mfrc522.PCD_Init();
  
  // Inisialisasi Servo
  myServo.attach(servoPin);
  myServo.write(0);  // Mulai dengan kunci pintu
  
  Serial.println("Scan your RFID tag");
}

void loop() {
  if (mfrc522.PICC_IsNewCardPresent() && mfrc522.PICC_ReadCardSerial()) {
    String rfid_uid = "";
    for (byte i = 0; i < mfrc522.uid.size; i++) {
      rfid_uid += String(mfrc522.uid.uidByte[i], HEX);
    }
    Serial.println("UID RFID: " + rfid_uid);
    
    // Panggil fungsi verifikasi ke backend atau blockchain
    if (checkUIDOnBlockchain(rfid_uid)) {
      Serial.println("Access granted");
      openLock();
    } else {
      Serial.println("Access denied");
    }
    
    mfrc522.PICC_HaltA();  // Hentikan pembacaan RFID
  }
}

// Fungsi untuk melakukan HTTP request untuk cek UID di blockchain
bool checkUIDOnBlockchain(String uid) {
  HTTPClient http;
  String serverPath = "http://localhost:3000/checkUID?uid=" + uid;
  
  http.begin(serverPath);
  int httpResponseCode = http.GET();
  
  if (httpResponseCode == 200) {
    String response = http.getString();
    Serial.println("Response: " + response);
    
    // Ganti logika sesuai respons dari backend
    if (response == "UID_VALID") {
      return true;
    }
  } else {
    Serial.println("Error in HTTP request");
  }

  http.end();
  return false;
}
