#include<WiFi.h>
#include<HTTPClient.h>

const char* ssid = "Krishan";
const char* pass = "password";
String serverName = "https://wqp.herokuapp.com/updateCSV/?data=";

void setup() {
  Serial.begin(9600);
  WiFi.begin(ssid, pass);
  Serial.println("Connecting");
  while(WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.print("Connected to WiFi network with IP Address: ");
  Serial.println(WiFi.localIP());
 
  Serial.println("Timer set to 5 seconds (timerDelay variable), it will take 5 seconds before publishing the first reading.");

}

void loop() {
  // put your main code here, to run repeatedly:
  if (WiFi.status() == WL_CONNECTED) {
    String data = "";
    if (Serial.available()) {
      data = Serial.readStringUntil('\n');
      HTTPClient http;
      data = (serverName + data.c_str()).c_str();
      data.replace("\n","");
      data.replace("\r", "");
      http.begin(data);
      int httpResponseCode = http.GET();
      if (httpResponseCode>0) {
        Serial.print("HTTP Response code: ");
        Serial.println(httpResponseCode);
        String payload = http.getString();
        Serial.println(payload);
      }
      else {
        Serial.print("Error code: ");
        Serial.println(httpResponseCode);
        String payload = http.getString();
        Serial.println(payload);
      }
      // Free resources
      http.end();
    }
  }
}
