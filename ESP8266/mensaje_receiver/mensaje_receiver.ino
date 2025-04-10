#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include <ArduinoJson.h>
#include <MD_Parola.h>
#include <MD_MAX72XX.h>
#include <SPI.h>

// 📡 Configuración de WiFi
const char* ssid = "Red-a-trabajar"; // Nombre de la red WiFi
const char* password = "contraseña"; // Contraseña de la red WiFi
const char* serverUrl = "http://172.20.10.3:3000/mensaje"; // URL del servidor backend

// 🖥️ Configuración de la matriz LED MAX7219
#define DATA_PIN   D7  // MOSI
#define CLK_PIN    D5  // SCK
#define CS_PIN     D6  // SS
#define NUM_MATRICES 2  // ✅ Asegúrate de que es el número correcto

MD_Parola matriz = MD_Parola(MD_MAX72XX::FC16_HW, DATA_PIN, CLK_PIN, CS_PIN, NUM_MATRICES);

String mensajeActual = "";  // Guardar el mensaje para evitar repeticiones

void setup() {
  Serial.begin(115200);
  
  // 🔗 Conectar a WiFi
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Conectando a WiFi...");
  }
  Serial.println("Conectado a WiFi");

  // 🔲 Inicializar la matriz LED
  matriz.begin();
  matriz.setIntensity(5);  // Brillo (0-15)
  matriz.displayClear();
  matriz.displayText("", PA_CENTER, 100, 3000, PA_SCROLL_LEFT, PA_SCROLL_LEFT); // Inicialización
}

void loop() {
  if (WiFi.status() == WL_CONNECTED) {
    HTTPClient http;
    WiFiClient client;
    
    http.begin(client, serverUrl);
    int httpCode = http.GET();
    
    if (httpCode > 0) {
      String payload = http.getString();
      DynamicJsonDocument doc(1024);
      deserializeJson(doc, payload);
      
      const char* mensaje = doc["mensaje"];
      Serial.println(mensaje);  // Para depuración

      // 🟢 Solo actualiza si el mensaje es diferente al anterior
      if (mensajeActual != String(mensaje)) {
        mensajeActual = String(mensaje);
        matriz.displayClear();
        matriz.displayText(mensajeActual.c_str(), PA_CENTER, 100, 3000, PA_SCROLL_LEFT, PA_SCROLL_LEFT);
      }
    }
    
    http.end();
  }

  // 🔄 Ejecutar la animación constantemente
  if (matriz.displayAnimate()) {
    matriz.displayReset();
  }
  
  delay(100);  // Reducimos el delay para que la animación fluya mejor
}
