#include <Adafruit_TCS34725.h>

Adafruit_TCS34725 tcs = Adafruit_TCS34725(TCS34725_INTEGRATIONTIME_50MS, TCS34725_GAIN_4X);

void setup() {
  Serial.begin(115200);
  if (tcs.begin()) {
    Serial.println("Sensor TCS34725 detectado.");
  } else {
    Serial.println("Error: no se detecta el sensor TCS34725.");
    while (1);
  }
}

void loop() {
  float red, green, blue;
  tcs.getRGB(&red, &green, &blue);
  int R = int(red);
  int G = int(green);
  int B = int(blue);
  String color = "";

  // Detectar fondo del canal (sin bola) con tolerancia más estricta
  if (abs(R - 141) < 5 && abs(G - 76) < 5 && abs(B - 46) < 5) {
    color = "Sin bola";
  }
  // Rojo
  else if (R > 180 && G < 50 && B < 50) {
    color = "Rojo";
  }
  // Verde
  else if (G > 100 && R < 100 && B < 80) {
    color = "Verde";
  }
  // Azul
  else if (G > 90 && B > 85 && R < 70) {
    color = "Azul";
  }
  // Amarillo
  else if (R >= 110 && R <= 145 && G >= 75 && G <= 90 && B <= 40) {
    color = "Amarillo";
  }
  else {
    color = "Desconocido";
  }

  Serial.print("R: "); Serial.print(R);
  Serial.print("   G: "); Serial.print(G);
  Serial.print("   B: "); Serial.print(B);
  Serial.print("   Color detectado: "); Serial.println(color);

  delay(1000);
}