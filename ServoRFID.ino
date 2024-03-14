#include <SPI.h>
#include <MFRC522.h>
#include <ESP32Servo.h> // Incluimos la biblioteca ESP32Servo

#define SS_PIN    5       // Pin Slave Select (SS) para el módulo RFID
#define RST_PIN   22      // Utilizamos otro pin para el reset, por ejemplo, el pin 21

MFRC522 mfrc522(SS_PIN, RST_PIN);   // Crear instancia de MFRC522
Servo myServo;                      // Crear instancia de Servo

#define SERVO_PIN 13     // Pin del servo

void setup() {
  Serial.begin(115200);     // Iniciar comunicación serial
  SPI.begin();            // Iniciar comunicación SPI
  mfrc522.PCD_Init();     // Inicializar el MFRC522
  myServo.attach(SERVO_PIN); // Inicializar el servo
}

void loop() {
  // Verificar si hay una tarjeta presente
  if (mfrc522.PICC_IsNewCardPresent() && mfrc522.PICC_ReadCardSerial()) {

    // Leer el UID de la tarjeta
    String uid = "";
    String key = "7C64EBC"; // Llave que servirá para mover el Servo
    for (byte i = 0; i < mfrc522.uid.size; i++) {
      uid.concat(String(mfrc522.uid.uidByte[i], HEX));
    }
    uid.toUpperCase();

    // Verificar si el UID coincide
    if (uid.equals(key)) {
      Serial.println("Acceso concedido. Moviendo el servo a la izquierda.");
      moveServo();
      delay(5000); // Esperar 5 segundos
      moveServoCenter(); // Volver el servo a la posición central
    } else {
      Serial.println("Acceso denegado.");
    }
  }
}

void moveServo() {
  myServo.write(0); // Ángulo para mover el servo a la dirección deseada (ajusta según sea necesario)
}

void moveServoCenter() {
  myServo.write(90); // Ángulo para mover el servo a la posición central (ajusta según sea necesario)
}
