/* Program NodeMCU Material Rak PLN
 * Code By : Jasa Pembuatan Program Arduino IOT
 * Made By : Agung Sidiq Santoso
 * Address : Grabag, Magelang, Jawa Tengah
 */
 
#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include <DNSServer.h>
#include <ESP8266WebServer.h>
#include <SoftwareSerial.h>
#include <Arduino_JSON.h>

SoftwareSerial arduino(D5, D6);

const char* ssid = "Redmi 5 Plus"; // Write here your router's username
const char* password = "Robot123";

String kode_api = "2404222253KRJGRBMGL";

String semuaData;
boolean pecah = false;
int i;
String dt[3];

String jumlah, perintah, id_barang;

String payload;

void setup() {
  Serial.begin(9600);
  arduino.begin(115200);

  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
     delay(500);
     Serial.print(".");
  }
  
  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println(WiFi.localIP());

  semuaData = "";
}

void loop() {
  if(arduino.available()){
    char data = (char)arduino.read();
    semuaData += data;
    if(data == '\n') pecah = true;
  }

  if(pecah) {
    //Serial.println(semuaData);
    input_web(kode_api, semuaData);
    pecah = false;
    semuaData = "";
  }
}

void input_web(String api, String perintah) {
  JSONVar doc;
  String url = "http://192.168.43.186/rakpln/mcu.php";
  
  doc["api"] = String(api);
  doc["perintah"] = String(perintah);
  
  if(WiFi.status() == WL_CONNECTED) {
    HTTPClient http;
    http.begin(url);
    http.addHeader("Content-Type", "application/json");

    String dataKirim = JSON.stringify(doc);
    
    int httpCode = http.POST(dataKirim);
    //Serial.println(httpCode);
    if (httpCode > 0) {
      payload = http.getString();
      Serial.print(payload);
      arduino.print(payload);
    }
    http.end();
  }
}
