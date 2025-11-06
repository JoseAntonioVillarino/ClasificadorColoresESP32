// Pines del driver DRV8825
const int STEP_PIN = 18;
const int DIR_PIN  = 19;
const int EN_PIN   = 23;

// Pin del ENDSTOP
const int ENDSTOP_PIN = 4;

// Pin del LED azul del ESP32
const int LED_PIN = 2;

// Full Step → 200 pasos por vuelta
const int angleSteps[] = {40, 38, 40, 42}; // pasos que hay entre una posición de color y otra

void setup() {
  pinMode(STEP_PIN, OUTPUT);
  pinMode(DIR_PIN, OUTPUT);
  pinMode(EN_PIN, OUTPUT);
  pinMode(ENDSTOP_PIN, INPUT_PULLUP);
  pinMode(LED_PIN, OUTPUT);

  Serial.begin(115200);

  // Activar el driver
  digitalWrite(EN_PIN, LOW);

  // Buscar punto cero (ENDSTOP) en sentido horario
  digitalWrite(DIR_PIN, HIGH); // Giro horario

  Serial.println("Buscando punto cero...");

  while (digitalRead(ENDSTOP_PIN) == HIGH) {
    digitalWrite(STEP_PIN, HIGH);
    delayMicroseconds(5000);
    digitalWrite(STEP_PIN, LOW);
    delayMicroseconds(5000);
  }

  Serial.println("Punto cero encontrado.");

  // Encender LED azul indicando que está listo para recibir bola
  digitalWrite(LED_PIN, HIGH);

  // Desactivar el driver para evitar calentamiento
  digitalWrite(EN_PIN, HIGH);
  delay(5000); // Esperar 5 segundos
}

void loop() {
  // Apagar LED azul antes de iniciar movimiento
  digitalWrite(LED_PIN, LOW);

  // Activar el driver
  digitalWrite(EN_PIN, LOW);

  // Giro antihorario para avanzar por los ángulos
  digitalWrite(DIR_PIN, LOW);

  // Barrido por los ángulos donde se sitúan los colores
  for (int i = 0; i < 4; i++) {
    for (int j = 0; j < angleSteps[i]; j++) {
      digitalWrite(STEP_PIN, HIGH);
      delayMicroseconds(3000);
      digitalWrite(STEP_PIN, LOW);
      delayMicroseconds(3000);
    }

    // Desactivar el driver durante la pausa en posición fija
    digitalWrite(EN_PIN, HIGH);
    delay(3000); // Esperar 3 segundos
    digitalWrite(EN_PIN, LOW); // Reactivar para siguiente movimiento
  }

  // Volver al punto cero (ENDSTOP) en sentido horario
  digitalWrite(DIR_PIN, HIGH); // Giro horario

  while (digitalRead(ENDSTOP_PIN) == HIGH) {
    digitalWrite(STEP_PIN, HIGH);
    delayMicroseconds(5000);
    digitalWrite(STEP_PIN, LOW);
    delayMicroseconds(5000);
  }

  // Encender LED azul indicando que está listo para recibir bola
  digitalWrite(LED_PIN, HIGH);

  // Desactivar el driver durante la pausa en posición cero
  digitalWrite(EN_PIN, HIGH);
  delay(5000); // Esperar 5 segundos antes de repetir
}