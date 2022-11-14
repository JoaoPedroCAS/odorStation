#include <WiFi.h>



const char* ssid = "local1"; //Nome da rede
const char* password = "Jpthlusa1uc14N4"; //Senha da rede


//Parametros do sensor de H2S
float gainH2S = 0.8;
int weoH2S = 36;
int aeoH2S = 348;
int weH2S = 1876;
float senseH2S = 1.501;
int weeH2S = 338;
int aeeH2S = 350;
float aeuH2S = 0;
float weuH2S = 0;
float wec1H2S = 0;
float wec2H2S = 0;
float ntH2S = 0;
float ktH2S = 0;
//--------------------------


void setup(){
    Serial.begin(9600); //Inicia o leitor serial
    WiFi.begin(ssid, password); //Inicia a conexão wifi

    while(WiFi.status() != WL_CONNECTED){ //TentH2Sa conectar a rede wifi até conseguir.
      delay(500);
      Serial.println("TentH2Sando conectar ao WiFi...");
    }
    Serial.println("Conectado a rede WiFi!");
}

void loop(){
  aeuH2S = analogRead(13);
  weuH2S = analogRead(12);
  
  float temp = 24;
  if(temp <= -20){
    ntH2S = -0.6;
    ktH2S = 0.2;
  }
  if(temp <= -10 && temp > -20){
    ntH2S = 0.1;
    ktH2S = 0;
  }
  if(temp <= 0 && temp > -10){
    ntH2S = 0.8;
    ktH2S = -0.3;
  }
  if(temp <= 10 && temp > 0){
    ntH2S = -0.7;
    ktH2S = 0.3;
  }
  if(temp <= 30 && temp > 10){
    ntH2S = -2.5;
    ktH2S = 1;
  }
  if(temp <= 40 && temp > 30){
    ntH2S = -2.2;
    ktH2S = 0.9;
  }
  if(temp >= 50){
    ntH2S = -1.8;
    ktH2S = 0.7;
  }
  
  wec1H2S = (weuH2S - weeH2S) - (ntH2S*(aeuH2S - aeeH2S));
  wec2H2S = (weuH2S - weeH2S) - (ktH2S*(weoH2S/aeoH2S)*(aeuH2S - aeeH2S));
  Serial.print(wec1H2S);
  Serial.print(" ");
  Serial.println(wec2H2S);  
}
