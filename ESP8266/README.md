# Código ESP8266

Este directorio contiene el código para el microcontrolador ESP8266 que controla la matriz LED.

## 🔧 Componentes Necesarios

- ESP8266 (NodeMCU)
- Matriz LED MAX7219
- Cables de conexión

## 📌 Conexiones

| ESP8266 | Matriz LED |
|---------|------------|
| D7      | DIN       |
| D5      | CLK       |
| D6      | CS        |
| 3.3V    | VCC       |
| GND     | GND       |

## ⚙️ Configuración

1. Modificar las credenciales WiFi:

cpp
const char ssid = "tu-wifi";
const char password = "tu-contraseña";

2. Ajustar la URL del servidor:

cpp
const char* serverUrl = "http://192.168.1.100:3000/mensaje";

## 📦 Dependencias

- `ESP8266WiFi.h`
- `ESP8266HTTPClient.h`
- `ArduinoJson.h`
- `MD_MAX72XX.h`
- `MD_Parola.h`
