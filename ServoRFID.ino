#include <SPI.h>
#include <MFRC522.h>

#define SS_PIN 5        // Pin Slave Select (SS)
#define RST_PIN 22      // Pin de reset

MFRC522 mfrc522(SS_PIN, RST_PIN);   // Crear instancia de MFRC522

void setup() {
  Serial.begin(115200);   // Iniciar comunicación serial
  SPI.begin();            // Iniciar comunicación SPI
  mfrc522.PCD_Init();     // Inicializar el MFRC522

  Serial.println("Acerca una tarjeta RFID para probar...");
}

void loop() {
  // Verificar si hay una tarjeta presente
  if (mfrc522.PICC_IsNewCardPresent() && mfrc522.PICC_ReadCardSerial()) {
    Serial.println("Tarjeta detectada!");

    // Mostrar UID de la tarjeta
    Serial.print("UID de la tarjeta: ");
    String content = "";
    byte letter;
    for (byte i = 0; i < mfrc522.uid.size; i++) {
      Serial.print(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " ");
      Serial.print(mfrc522.uid.uidByte[i], HEX);
      content.concat(String(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " "));
      content.concat(String(mfrc522.uid.uidByte[i], HEX));
    }
    Serial.println();
    Serial.print("Mensaje: ");
    content.toUpperCase();
    Serial.println(content);
  }

  delay(1000);  // Pequeña pausa antes de volver a buscar una tarjeta
}