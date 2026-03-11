#include <Arduino.h>

const uint8_t buttonPin = 2;      // pulsador conectado a pin 2
const uint8_t outputPin = 4;      // LED en pin 4

// debouncing
unsigned long lastDebounceTime = 0;
const unsigned long debounceDelay = 50; // ms

int buttonState = LOW;        // estado estable actual del botón
int lastButtonReading = LOW;  // última lectura del pin

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  pinMode(outputPin, OUTPUT);

  // asumo un pulsador que lleva el pin a HIGH al presionar
  // (usa una resistencia pull‑down externa o modifica según tu circuito)
  pinMode(buttonPin, INPUT);
}

void loop() {
  int reading = digitalRead(buttonPin);

  // detecta cambios y reinicia temporizador
  if (reading != lastButtonReading) {
    lastDebounceTime = millis();
  }

  // si ha pasado el tiempo de rebote, toma el nuevo estado estable
  if ((millis() - lastDebounceTime) > debounceDelay) {
    if (reading != buttonState) {
      buttonState = reading;
      if (buttonState == HIGH) {
        // flanco de subida limpio: alternar estado del LED
        int newState = !digitalRead(outputPin);
        digitalWrite(outputPin, newState);
        Serial.print("Pin 2 accionado, LED cambia a... ");
        Serial.println(newState == HIGH ? "ENCENDIDO" : "APAGADO");
      }
    }
  }

  lastButtonReading = reading;
}
