# ClasificadorColoresESP32
Códigos del proyecto de Arduino UNO de un clasificador de colores, incorporando un sensor RGB TCS34725 y un motor WANTAI 2.5A

DESCRIPCIÓN DEL PROYECTO
Este proyecto implementa un sistema capaz de detectar el color de objetos (bolas de plastilina) y clasificarlos automáticamente mediante el movimiento controlado de un motor paso a paso.
Se utilizan los siguientes componentes:

ESP32-WROOM-32D
Sensor de color TCS34725
Motor paso a paso Wantai 2.5 A
Driver DRV8825
ENDSTOP mecánico
LED indicador


ESTRUCTURA DEL REPOSITORIO
El repositorio contiene tres códigos principales:


1 -> Código base del motor
Control del motor paso a paso con el driver DRV8825.

2 -> Código base del motor con final de carrera
Control del motor paso a paso con el driver DRV8825 y calibración mediante ENDSTOP.


3 -> Código base del sensor TCS34725
Lectura de valores RGB y detección del color predominante.


4 -> Código final del proyecto
Integración completa: detección de color + movimiento del motor + señalización LED.



REQUISITOS

Arduino IDE instalado.
Librerías necesarias:
-Adafruit_TCS34725
-Wire
-AccelStepper




COMO USAR

Clona el repositorio:
Shellgit clone https://github.com/TU-USUARIO/ClasificadorColoresESP32.gitMostrar más líneas

Abre el código en Arduino IDE.
Selecciona la placa ESP32-WROOM-32D.
Instala las librerías indicadas.
Carga el código final en la placa.
