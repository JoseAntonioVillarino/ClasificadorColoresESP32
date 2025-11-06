// Pines del driver DRV8825
const int STEP_PIN = 18;
const int DIR_PIN  = 19;
const int EN_PIN   = 23;

// Full Step→ 200 pasos por vuelta
const int stepsPerRevolution = 200;

void setup() {
  pinMode(STEP_PIN, OUTPUT);
  pinMode(DIR_PIN, OUTPUT);
  pinMode(EN_PIN, OUTPUT);

  digitalWrite(DIR_PIN, HIGH); // Sentido horario
}

void loop() {
  digitalWrite(EN_PIN, LOW); // Activar el driver

  // Giro de 360° lento
  for (int i = 0; i < stepsPerRevolution; i++) {
    digitalWrite(STEP_PIN, HIGH);
    delayMicroseconds(3000); // Más lento
    digitalWrite(STEP_PIN, LOW);
    delayMicroseconds(3000);
  }

  digitalWrite(EN_PIN, HIGH); // Desactivar el driver para evitar ruido

  delay(3000); // Espera 3 segundos antes del siguiente giro
}