#include <WiFi.h>

const char* ssid = "yourSSID"; //Nome da rede
const char* password = "yourPassword"; //Senha da rede

void setup(){
    Serial.begin(9600); //Inicia o leitor serial
    WiFi.begin(ssid, password); //Inicia a conexão wifi

    while(WiFi.status() != WL_CONNECTED){ //Tenta conectar a rede wifi até conseguir.
      delay(500);
      Serial.println("Tentando conectar ao WiFi...");
    }
    Serial.println("Conectado a rede WiFi!");
    
}

void loop(){
  //
}
