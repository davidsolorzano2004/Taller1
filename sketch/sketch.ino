#include "SensorTemp.h"

SensorTemp sensor(34, 3.3, 4095);
const int ledPin = 2;
unsigned long lastReadTime = 0; // linea feliz
const long readInterval = 2000;  // 2 segundos

void setup() {
    Serial.begin(115200);
    pinMode(ledPin, OUTPUT);
    digitalWrite(ledPin, LOW);
    delay(1000);
    Serial.println("Iniciando monitor de temperatura...");
}

void loop() {
    unsigned long currentTime = millis();
    
    if (currentTime - lastReadTime >= readInterval) {
        lastReadTime = currentTime;
        
        float temperatura = sensor.leerTemperatura();
        
        if (isnan(temperatura)) {
            Serial.println("[ERROR] Sensor no responde");
            digitalWrite(ledPin, LOW);
        } else {
            Serial.print("[INFO] Temp: ");
            Serial.print(temperatura, 1);
            Serial.print("°C | ");
            
            if (temperatura < 15.0) {
                digitalWrite(ledPin, HIGH);
                Serial.println("ALERTA: TEMP BAJA!");
            } 
            else if (temperatura > 30.0) {
                digitalWrite(ledPin, HIGH);
                Serial.println("ALERTA: TEMP ALTA!");
            }
            else {
                digitalWrite(ledPin, LOW);
                Serial.println("Normalito");
            }
        }
    }
    
    // Pequeña pausa para no saturar el procesador
    delay(100);
}