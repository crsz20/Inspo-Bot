#include <Arduino.h>

#include <ArduinoJson.h>

#include <ESP8266WiFi.h>
#include <ESP8266WiFiMulti.h>
#include <ESP8266HTTPClient.h>
#include <WiFiClientSecureBearSSL.h>
const uint8_t fingerprint[20] = {0x2e, 0x3b, 0xd8, 0xe7, 0x5a, 0x6d, 0xe3, 0xe3, 0xfb, 0x81, 0x1e, 0xa6, 0x4b, 0xa4, 0x00, 0x1c, 0x1b, 0xeb, 0xca, 0x2a};



ESP8266WiFiMulti WiFiMulti;

void setup() {

  Serial.begin(115200);
  // Serial.setDebugOutput(true);

  Serial.println();
  Serial.println();
  Serial.println();

  for (uint8_t t = 4; t > 0; t--) {
    Serial.printf("[SETUP] WAIT %d...\n", t);
    Serial.flush();
    delay(1000);
  }

  WiFi.mode(WIFI_STA);
  WiFiMulti.addAP("SSID", "PASSWORD");
}



void parseJson(String json) {
  
  // Allocate the JSON document
  const int capacity = JSON_OBJECT_SIZE(1)+JSON_OBJECT_SIZE(1)+JSON_OBJECT_SIZE(256);
  DynamicJsonDocument doc(capacity);

  //Parse
  DeserializationError error = deserializeJson(doc, json);
  
  if (error) {
    Serial.print(F("deserializeJson() failed: "));
    Serial.println(error.f_str());
    return;
  }

  String quote = doc["quote"]["quote"];
  String source = doc["quote"]["source"];

  Serial.print("Quote: ");
  Serial.println(quote);
  Serial.print("Source: ");
  Serial.println(source);
}




void loop() {
  // wait for WiFi connection
  if ((WiFiMulti.run() == WL_CONNECTED)) {

    std::unique_ptr<BearSSL::WiFiClientSecure>client(new BearSSL::WiFiClientSecure);

    client->setFingerprint(fingerprint);

    HTTPClient https;

    Serial.print("[HTTPS] begin...\n");
    if (https.begin(*client, "https://quotejoy.p.rapidapi.com/random")) {  // HTTPS

      Serial.println("Connected to API endpoint");
      Serial.print("[HTTPS] GET...\n");

      https.addHeader("x-rapidapi-key", "<INSERT_API_KEY>");
      https.addHeader("x-rapidapi-host", "quotejoy.p.rapidapi.com");
      
      // start connection and send HTTP header
      int httpCode = https.GET();

      // httpCode will be negative on error
      if (httpCode > 0) {
        // HTTP header has been send and Server response header has been handled
        Serial.printf("[HTTPS] GET... code: %d\n", httpCode);

        // file found at server
        if (httpCode == HTTP_CODE_OK || httpCode == HTTP_CODE_MOVED_PERMANENTLY) {
          String payload = https.getString();
          Serial.println(payload);
          parseJson(payload);
        }
      } else {
        Serial.printf("[HTTPS] GET... failed, error: %s\n", https.errorToString(httpCode).c_str());
      }

      https.end();
    } else {
      Serial.printf("[HTTPS] Unable to connect\n");
    }
  }

  Serial.println("Wait 10s before next round...");
  delay(10000);
}