#include <Arduino.h>

#define RELE 5
#define SENSOR_IN 14
#define LED 2
#define EVALUATION_TIME 45 //Segundos

bool evaluate = true;

void countEvaluationTime();
void handleSensor();

void setup()
{
  //Inicializar pines
  pinMode(LED, OUTPUT);
  pinMode(RELE, OUTPUT);
  pinMode(SENSOR_IN, INPUT);

  //Inicializar comunicacion serial
  Serial.begin(9600);
}

void loop()
{
  if (evaluate)
    countEvaluationTime();

  yield();
}

void countEvaluationTime()
{
  static int counter = 0;
  static unsigned long startTime;

  if (millis() - startTime >= 1000)
  {
    // Aumentar contador
    counter++;

    // Mostrar tiepo actual
    Serial.println("Tiempo -> " + String(counter) + " segundos");

    // Evaluar valor del contador
    if (counter == EVALUATION_TIME)
    {
      // Evaluar valor del sensor
      handleSensor();

      // Ya no evaluar ni contar
      evaluate = false;
      Serial.println("Termino el programa");
    }

    // Tomar referencia de tiempo otra vez
    startTime = millis();
  }
}

void handleSensor()
{
  // Si no esta en bajo...
  if (digitalRead(SENSOR_IN) != LOW)
  {
    // Cortar corriente!, o alarmar
    digitalWrite(RELE, HIGH);
    Serial.println("Cortar corriente!");
  }
  else
  {
    Serial.println("No cortar corriente");
  }
}