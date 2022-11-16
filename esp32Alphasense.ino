#include <WiFi.h>
#include <WiFi.h>
#include "WiFiClientSecure.h"
#include "Adafruit_MQTT.h"
#include "Adafruit_MQTT_Client.h" 

//Configuração WiFi
const char* ssid = "local1"; //Nome da rede
const char* password = "Jpthlusa1uc14N4"; //Senha da rede
//--------------------

//Configuração Adafruit IO
#define AIO_SERVER      "io.adafruit.com"

// Using port 8883 for MQTTS
#define AIO_SERVERPORT  8883

// Adafruit IO Account Configuration
// (to obtain these values, visit https://io.adafruit.com and click on Active Key)
#define AIO_USERNAME "jpcas1101"
#define AIO_KEY      "aio_JiXH90E0TvKNhBRpeitDA0Duwi5G"
//-------------------------------------------

//Definições Globais
// WiFiFlientSecure for SSL/TLS support
WiFiClientSecure client;

// Setup the MQTT client class by passing in the WiFi client and MQTT server and login details.
Adafruit_MQTT_Client mqtt(&client, AIO_SERVER, AIO_SERVERPORT, AIO_USERNAME, AIO_KEY);

// io.adafruit.com root CA
const char* adafruitio_root_ca = \
    "-----BEGIN CERTIFICATE-----\n" \
    "MIIDrzCCApegAwIBAgIQCDvgVpBCRrGhdWrJWZHHSjANBgkqhkiG9w0BAQUFADBh\n" \
    "MQswCQYDVQQGEwJVUzEVMBMGA1UEChMMRGlnaUNlcnQgSW5jMRkwFwYDVQQLExB3\n" \
    "d3cuZGlnaWNlcnQuY29tMSAwHgYDVQQDExdEaWdpQ2VydCBHbG9iYWwgUm9vdCBD\n" \
    "QTAeFw0wNjExMTAwMDAwMDBaFw0zMTExMTAwMDAwMDBaMGExCzAJBgNVBAYTAlVT\n" \
    "MRUwEwYDVQQKEwxEaWdpQ2VydCBJbmMxGTAXBgNVBAsTEHd3dy5kaWdpY2VydC5j\n" \
    "b20xIDAeBgNVBAMTF0RpZ2lDZXJ0IEdsb2JhbCBSb290IENBMIIBIjANBgkqhkiG\n" \
    "9w0BAQEFAAOCAQ8AMIIBCgKCAQEA4jvhEXLeqKTTo1eqUKKPC3eQyaKl7hLOllsB\n" \
    "CSDMAZOnTjC3U/dDxGkAV53ijSLdhwZAAIEJzs4bg7/fzTtxRuLWZscFs3YnFo97\n" \
    "nh6Vfe63SKMI2tavegw5BmV/Sl0fvBf4q77uKNd0f3p4mVmFaG5cIzJLv07A6Fpt\n" \
    "43C/dxC//AH2hdmoRBBYMql1GNXRor5H4idq9Joz+EkIYIvUX7Q6hL+hqkpMfT7P\n" \
    "T19sdl6gSzeRntwi5m3OFBqOasv+zbMUZBfHWymeMr/y7vrTC0LUq7dBMtoM1O/4\n" \
    "gdW7jVg/tRvoSSiicNoxBN33shbyTApOB6jtSj1etX+jkMOvJwIDAQABo2MwYTAO\n" \
    "BgNVHQ8BAf8EBAMCAYYwDwYDVR0TAQH/BAUwAwEB/zAdBgNVHQ4EFgQUA95QNVbR\n" \
    "TLtm8KPiGxvDl7I90VUwHwYDVR0jBBgwFoAUA95QNVbRTLtm8KPiGxvDl7I90VUw\n" \
    "DQYJKoZIhvcNAQEFBQADggEBAMucN6pIExIK+t1EnE9SsPTfrgT1eXkIoyQY/Esr\n" \
    "hMAtudXH/vTBH1jLuG2cenTnmCmrEbXjcKChzUyImZOMkXDiqw8cvpOp/2PV5Adg\n" \
    "06O/nVsJ8dWO41P0jmP6P6fbtGbfYmbW0W5BjfIttep3Sp+dWOIrWcBAI+0tKIJF\n" \
    "PnlUkiaY4IBIqDfv8NZ5YBberOgOzW6sRBc4L0na4UU+Krk2U886UAb3LujEV0ls\n" \
    "YSEY1QSteDwsOoBrp+uvFRTp2InBuThs4pFsiv9kuXclVzDAGySj4dzp30d8tbQk\n" \
    "CAUw7C29C79Fv1C5qfPrmAESrciIxpg0X40KPMbp1ZWVbd4=\n" \
    "-----END CERTIFICATE-----\n";
//--------------------------------------------------------------------------
Adafruit_MQTT_Publish h2sM1 = Adafruit_MQTT_Publish(&mqtt, AIO_USERNAME "/feeds/h2sm1");
Adafruit_MQTT_Publish h2sM2 = Adafruit_MQTT_Publish(&mqtt, AIO_USERNAME "/feeds/h2sm2");

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

    while(WiFi.status() != WL_CONNECTED){ //Tenta conectar a rede wifi até conseguir.
      delay(500);
      Serial.println("Tentando conectar ao WiFi...");
    }
    Serial.println("Conectado a rede WiFi!");
    client.setCACert(adafruitio_root_ca);
}

void loop(){
  MQTT_connect();
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
  
  wec1H2S = ((weuH2S - weeH2S) - (ntH2S*(aeuH2S - aeeH2S)))/1000;
  wec2H2S = ((weuH2S - weeH2S) - (ktH2S*(weoH2S/aeoH2S)*(aeuH2S - aeeH2S)))/1000;
  Serial.print(weuH2S, 5);
  Serial.print(" ");
  Serial.println(aeuH2S, 5);  
  if (! h2sM1.publish(wec1H2S)) {
    Serial.println("Failed");
  } else {
    Serial.println("OK!");
  }
  if (! h2sM2.publish(wec2H2S)) {
    Serial.println("Failed");
  } else {
    Serial.println("OK!");
  }
  delay(60000);
}

void MQTT_connect() {
  int8_t ret;

  // Stop if already connected.
  if (mqtt.connected()) {
    return;
  }

  Serial.print("Connecting to MQTT... ");

  uint8_t retries = 3;
  while ((ret = mqtt.connect()) != 0) { // connect will return 0 for connected
       Serial.println(mqtt.connectErrorString(ret));
       Serial.println("Retrying MQTT connection in 5 seconds...");
       mqtt.disconnect();
       delay(5000);  // wait 5 seconds
       retries--;
       if (retries == 0) {
         // basically die and wait for WDT to reset me
         while (1);
       }
  }

  Serial.println("MQTT Connected!");
}
