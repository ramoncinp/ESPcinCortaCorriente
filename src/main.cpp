#include <Arduino.h>

#define RELE 5
#define SENSOR_IN 14
#define LED 2
#define EVALUATION_TIME 45 //Segundos

bool count = true;
byte currentSensorState;
int noZeroCounter = 0;
unsigned long debounceTimeRef;

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

  //Tiempo de estabilizacion
  Serial.println("Tiempo de estabilizacion");
  delay(10000); //10 segundos
  Serial.println("Iniciando programa!");

  //Asignar valor de "count" en base a estado actual e sensor
  count = !(digitalRead(SENSOR_IN) == LOW);  
}

void loop()
{
  // Contar tiempo si no hay presencia de sensor
  if (count)
    countEvaluationTime();

  // Evaluar valor del sensor
  handleSensor();

  yield();
}

void countEvaluationTime()
{
  static unsigned long startTime;

  // Ejecutar cada segundo
  if (millis() - startTime >= 1000)
  {
    // Aumentar contador
    noZeroCounter++;

    // Mostrar tiepo actual
    Serial.println("Tiempo -> " + String(noZeroCounter) + " segundos");

    // Evaluar valor del contador
    if (noZeroCounter == EVALUATION_TIME)
    {
      // Cortar corriente!
      digitalWrite(RELE, HIGH);
      // Dejar de contar
      count = false;
    }

    // Tomar referencia de tiempo otra vez
    startTime = millis();
  }
}

void handleSensor()
{
  // Validar tiempo de debounce
  if (millis() - debounceTimeRef > 500)
  {
    // Si no esta en bajo
    if (digitalRead(SENSOR_IN) != LOW)
    {
      //Si el estado anterior era diferente, tomar referencia de debounce
      if (currentSensorState == LOW)
      {
        //Comenzar a contar
        Serial.println("Empezar a contar 45 segundos");
        count = true;
        debounceTimeRef = millis();
      }
    }
    else
    {
      //No cortar corriente
      digitalWrite(RELE, LOW);

      //Si el estado anterior era diferente, tomar referencia de debounce
      if (currentSensorState == HIGH)
      {
        Serial.println("Reinicar contador para corta-corriente");
        //Reiniciar contador
        noZeroCounter = 0;
        //Indicar que no se debe contar
        count = false;
        debounceTimeRef = millis();
      }
    }

    // Definir valor actual
    currentSensorState = digitalRead(SENSOR_IN);
  }
}