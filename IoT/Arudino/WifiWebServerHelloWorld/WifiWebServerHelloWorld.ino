#include <ESP8266WiFi.h>

const char* ssid = "AndroidHotspot2910";
const char* password = "12345678";

WiFiServer server(80);

void setup() {
  Serial.begin(9600);
  delay(10);

  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);

  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("WiFi Connected");

  server.begin();
  Serial.println("Server started");

  Serial.println(WiFi.localIP());
}

void loop() {
  WiFiClient client = server.available();
  if (!client) {
    return ;
  }

  Serial.println("new client");

  String req = client.readStringUntil('\r');
  Serial.println(req);
  client.flush();

  String s="<html>";
  s=s+"<meta name='viewport' content='width=device-width, initial-scale=1.0'/>"; //s=s+"<meta http-equiv='refresh' content='5'/>";
  s=s+"<meta http-equiv='Content-Type' content='text/html;charset=utf-8' />"; s=s+"<head></head><body>안녕하세요!</body></html>";
  // Send the response to the client
  client.print(s);
  delay(1);
  Serial.println("Client disonnected");
  // The client will actually be disconnected
  // when the function returns and 'client' object is detroyed
}
