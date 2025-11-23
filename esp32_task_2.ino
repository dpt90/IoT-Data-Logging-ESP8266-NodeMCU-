#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>

const char* ssid = "Wifi_Name";
const char* password = "password";

ESP8266WebServer server(80);

float readTemperature() {
  int sensorValue = analogRead(A0);
  float voltage = sensorValue * (3.3 / 1024.0);
  float temperature = (voltage - 0.5) * 100.0;
  return temperature;
}

// ---- API Route to send temp value ----
void handleTemp() {
  float temp = readTemperature();
  server.send(200, "text/plain", String(temp));
}

// ---- Web Page with Graph ----
void handleRoot() {
  String html = "<!DOCTYPE html><html><head><meta charset='UTF-8'>";
  html += "<title>ESP8266 Live Temperature</title>";
  html += "<style>";
  html += "body{font-family:Arial;text-align:center;background:#f2f2f2;margin:0;padding:0;}";
  html += ".card{margin:20px auto;padding:20px;width:350px;background:#fff;border-radius:10px;box-shadow:0 0 10px gray;}";
  html += "h1{color:#333;} h2{color:#e63946;font-size:40px;margin:10px;}";
  html += "</style></head><body>";

  html += "<div class='card'><h1>TMP36 Temperature</h1>";
  html += "<h2 id='tempValue'>-- °C</h2>";
  html += "<p>Live Graph (updates every 5 seconds)</p></div>";

  html += "<canvas id='chartTemp' width='400' height='300'></canvas>";

  // Chart.js library (CDN)
  html += "<script src='https://cdn.jsdelivr.net/npm/chart.js'></script>";

  // JavaScript to fetch temp + update UI + chart
  html += "<script>";
  html += "let dataArray=[]; let timeArray=[];";
  html += "let chart=new Chart(document.getElementById('chartTemp'),{type:'line',data:{labels:timeArray,datasets:[{label:'Temperature °C',data:dataArray,borderColor:'red',borderWidth:2,fill:false}]},options:{scales:{y:{beginAtZero:false}}}});";

  html += "function fetchTemp(){fetch('/temp').then(r=>r.text()).then(temp=>{";
  html += "document.getElementById('tempValue').innerHTML=temp+' °C';";
  html += "let t=new Date().toLocaleTimeString();";
  html += "timeArray.push(t); dataArray.push(temp);";
  html += "if(timeArray.length>20){timeArray.shift();dataArray.shift();}";
  html += "chart.update(); });}";
  html += "setInterval(fetchTemp,5000); fetchTemp();";
  html += "</script></body></html>";

  server.send(200, "text/html", html);
}

void setup() {
  Serial.begin(9600);
  WiFi.begin(ssid, password);

  Serial.print("Connecting");
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("\nWiFi Connected!");
  Serial.print("IP Address: ");
  Serial.println(WiFi.localIP());

  server.on("/", handleRoot);
  server.on("/temp", handleTemp);  // API endpoint
  server.begin();
  Serial.println("Web Server Started");
}

void loop() {
  server.handleClient();
}

