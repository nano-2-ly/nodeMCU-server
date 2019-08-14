#include <ESP8266WiFi.h>
 
#ifndef STASSID
#define STASSID "LOAD_2.4G"
#define STAPSK  "loadthefuture"
#endif
 
const char* ssid     = STASSID;
const char* password = STAPSK;
 
const char* host = "192.168.0.66";
const uint16_t port = 8000;
 
void setup() {
  Serial.begin(115200);
  
  Serial.println();
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);
 
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);
 
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
 
  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
}
 
void loop() {
  Serial.print("connecting to ");
  Serial.print(host);
  Serial.print(':');
  Serial.println(port);
 
  // Use WiFiClient class to create TCP connections
  WiFiClient client;
  if (!client.connect(host, port)) {
    Serial.println("connection failed");
    delay(5000);
    return;
  }
 
  // This will send a string to the server
  Serial.println("sending data to server");
  if (client.connected()) {
    client.println("hello from ESP8266");
  }
 
  // wait for data to be available
  unsigned long timeout = millis();
  while (client.available() == 0) {
    if (millis() - timeout > 5000) {
      Serial.println(">>> Client Timeout !");
      client.stop();
      delay(60000);
      return;
    }
  }
 
  // Read all the lines of the reply from server and print them to Serial
  Serial.println("receiving from remote server");
  // not testing 'client.connected()' since we do not need to send data here
  while (client.available()) {
    char ch = static_cast<char>(client.read());
    Serial.print(ch);
  }
 
  // Close the connection
  Serial.println();
  Serial.println("closing connection");
  client.stop();
 
  delay(5000); // execute once every 5 minutes, don't flood remote service
}
