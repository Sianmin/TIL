#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>

const char* ssid = "AndroidHotspot2910";
const char* password = "12345678";

ESP8266WebServer server(80);
String s, s_head;

void handleRoot() {
  digitalWrite(LED_BUILTIN, HIGH);   // turn the LED on (HIGH is the voltage level)
  s = s_head + "<h1>켜짐</h1><br>";
  server.send(200, "text/html", s);
}

void handleNotFound() {
  digitalWrite(LED_BUILTIN, 1);
  String message = "File Not Found\n\n";
  message += "URI: ";
  message += server.uri();
  message += "\nMethod: ";
  message += (server.method() == HTTP_GET)?"GET":"POST"; message += "\nArguments: ";
  message += server.args();
  message += "\n";
  for (uint8_t i=0; i<server.args(); i++){
  message += " " + server.argName(i) + ": " + server.arg(i) + "\n"; }
  server.send(404, "text/plain", message);
  digitalWrite(LED_BUILTIN, 0);
}

void setupWifi() {
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password); Serial.println("");
  // Wait for connection
  while (WiFi.status() != WL_CONNECTED) {
  delay(500);
  Serial.print("."); }
  Serial.println(""); Serial.print("Connected to "); Serial.println(ssid); Serial.print("IP address: "); Serial.println(WiFi.localIP());
}

void setup(void) {
  pinMode(LED_BUILTIN, OUTPUT);
  digitalWrite(LED_BUILTIN, LOW);
  Serial.begin(115200);

  setupWifi();

  // 스마트폰에 맟게 크기 조정, html에서 한글 출력하게 설정
  s_head="<meta name='viewport' content='width=device-width, initial-scale=1.0'/>";
  //s=s+"<meta http-equiv='refresh' content='5'/>";
  s_head=s_head+"<meta http-equiv='Content-Type' content='text/html;charset=utf-8' />";
  server.on("/on", handleRoot); server.on("/off", [](){
  //server.send(200, "text/plain", "this works as well");
  digitalWrite(LED_BUILTIN, LOW);
  s=s_head+"<h1>꺼짐</h1><br>";
  server.send(200, "text/html", s);
  });

  server.onNotFound(handleNotFound);
  server.begin();
  Serial.println("HTTP server started");
}

void loop(void){
server.handleClient();
}
