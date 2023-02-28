#include <ESP8266WiFi.h>

// Configuração da rede wifi
const char* ssid = "CYBERDYNE";
const char* senha = "put your pass here";

//const byte LED_Green = D4;
const byte LED_Verde = 2;  // both can be used, 2 (gpio) or D4 (board)
const byte LED_Amarelo = D7;
const byte LED_Vermelho = D3;
const byte tecla = D0;
#define LDR A0

void setup() {
  // put your setup code here, to run once:

  // Configura serial para monitorar conexão via terminal
  Serial.begin(74880);
  delay(100);

  Serial.print("\r\n"); // new line and carriage return
  Serial.print("Conectando a rede ");
  Serial.println(ssid);

  WiFi.begin(ssid, senha);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println(" ");
  Serial.println("WiFi Conectado");
  Serial.println("Endereço de IP:");
  Serial.println(WiFi.localIP());
}

void loop() {
  // put your main code here, to run repeatedly:
}
