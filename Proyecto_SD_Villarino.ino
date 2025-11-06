#include <Adafruit_TCS34725.h>

// Pines del driver DRV8825
const int STEP_PIN = 18;
const int DIR_PIN  = 19;
const int EN_PIN   = 23;

// Pin del ENDSTOP
const int ENDSTOP_PIN = 4;

// Pin del LED azul del ESP32
const int LED_PIN = 2;

// Sensor de color
Adafruit_TCS34725 tcs = Adafruit_TCS34725(TCS34725_INTEGRATIONTIME_50MS, TCS34725_GAIN_4X);

// Mapeo de colores a pasos desde 0º
const int pasosAmarillo = 40;
const int pasosAzul     = 78; // 40 + 38
const int pasosVerde    = 118; // 78 + 40
const int pasosRojo     = 160; // 118 + 42

String ultimoColor = "";
int contadorColor = 0;

void setup() {
  pinMode(STEP_PIN, OUTPUT);
  pinMode(DIR_PIN, OUTPUT);
  pinMode(EN_PIN, OUTPUT);
  pinMode(ENDSTOP_PIN, INPUT_PULLUP);
  pinMode(LED_PIN, OUTPUT);

  Serial.begin(115200);

  if (tcs.begin()) {
    Serial.println("Sensor TCS34725 detectado.");
  } else {
    Serial.println("Error: no se detecta el sensor TCS34725.");
    while (1);
  }

  buscarEndstop(); // Posicionar en 0º al iniciar
}

void loop() {
  String colorDetectado = detectarColor();

  if (colorDetectado == ultimoColor && colorDetectado != "Desconocido" && colorDetectado != "Sin bola") {
    contadorColor++;
  } else {
    contadorColor = 0;
    ultimoColor = colorDetectado;
  }

  if (contadorColor >= 3) { // cambiar el número para activar el motor con más o menos detecciones
    parpadearLedAzul();

    if (colorDetectado == "Amarillo") {
      moverAMarca(pasosAmarillo);
    } else if (colorDetectado == "Azul") {
      moverAMarca(pasosAzul);
    } else if (colorDetectado == "Verde") {
      moverAMarca(pasosVerde);
    } else if (colorDetectado == "Rojo") {
      moverAMarca(pasosRojo);
    }

    contadorColor = 0;
    ultimoColor = "";
  }

  delay(1000); // Espera entre lecturas
}

// ---------------- FUNCIONES ----------------

void buscarEndstop() {
  digitalWrite(EN_PIN, LOW);
  digitalWrite(DIR_PIN, HIGH); // Giro horario

  Serial.println("Buscando punto cero...");

  while (digitalRead(ENDSTOP_PIN) == HIGH) {
    digitalWrite(STEP_PIN, HIGH);
    delayMicroseconds(5000);
    digitalWrite(STEP_PIN, LOW);
    delayMicroseconds(5000);
  }

  Serial.println("Punto cero encontrado.");

  digitalWrite(LED_PIN, HIGH); // LED azul encendido
  digitalWrite(EN_PIN, HIGH);  // Desactivar driver
  delay(5000); // Espera en 0º
}

String detectarColor() {
  float red, green, blue;
  tcs.getRGB(&red, &green, &blue);
  int R = int(red);
  int G = int(green);
  int B = int(blue);
  String color = "";

  if (abs(R - 141) < 5 && abs(G - 76) < 5 && abs(B - 46) < 5) {
    color = "Sin bola";
  } else if (R > 180 && G < 50 && B < 50) {
    color = "Rojo";
  } else if (G > 100 && R < 100 && B < 80) {
    color = "Verde";
  } else if (G > 90 && B > 85 && R < 70) {
    color = "Azul";
  } else if (R >= 110 && R <= 145 && G >= 75 && G <= 90 && B <= 40) {
    color = "Amarillo";
  } else {
    color = "Desconocido";
  }

  Serial.print("R: "); Serial.print(R);
  Serial.print("   G: "); Serial.print(G);
  Serial.print("   B: "); Serial.print(B);
  Serial.print("   Color detectado: "); Serial.println(color);

  return color;
}

void parpadearLedAzul() {
  for (int i = 0; i < 4; i++) {
    digitalWrite(LED_PIN, HIGH);
    delay(250);
    digitalWrite(LED_PIN, LOW);
    delay(250);
  }
}

void moverAMarca(int pasos) {
  digitalWrite(LED_PIN, LOW); // Apagar LED azul
  digitalWrite(EN_PIN, LOW);  // Activar driver
  digitalWrite(DIR_PIN, LOW); // Giro antihorario

  for (int i = 0; i < pasos; i++) {
    digitalWrite(STEP_PIN, HIGH);
    delayMicroseconds(3000);
    digitalWrite(STEP_PIN, LOW);
    delayMicroseconds(3000);
  }

  digitalWrite(EN_PIN, HIGH); // Desactivar driver
  delay(5000); // Esperar 5 segundos en posición

  buscarEndstop(); // Volver a 0º
}