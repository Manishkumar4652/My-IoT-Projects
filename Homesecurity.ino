#include <ESP8266WiFi.h>
#include <WiFiClientSecure.h>

// ==== WiFi Credentials ====
const char* ssid = "YOUR_WIFI_SSID";
const char* password = "YOUR_WIFI_PASSWORD";

// ==== Telegram Credentials ====
String BOT_TOKEN = "YOUR_BOT_TOKEN";  // Example: "123456789:ABCdefGhIJKlmNoPQRstuVWxyZ"
String CHAT_ID = "YOUR_CHAT_ID";      // Example: "123456789"

// ==== Sensor Pins ====
#define TRIG D5
#define ECHO D6
#define BUZZER D7

WiFiClientSecure client;

void setup() {
  Serial.begin(115200);
  pinMode(TRIG, OUTPUT);
  pinMode(ECHO, INPUT);
  pinMode(BUZZER, OUTPUT);

  digitalWrite(BUZZER, LOW);

  Serial.println();
  Serial.println("Connecting to WiFi...");
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("\nConnected to WiFi!");
  Serial.print("IP Address: ");
  Serial.println(WiFi.localIP());

  client.setInsecure(); // Ignore SSL certificate
}

void loop() {
  long duration, distance;
  digitalWrite(TRIG, LOW);
  delayMicroseconds(2);
  digitalWrite(TRIG, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG, LOW);

  duration = pulseIn(ECHO, HIGH);
  distance = (duration / 2) / 29.1;  // Convert time to distance (cm)

  Serial.print("Distance: ");
  Serial.print(distance);
  Serial.println(" cm");

  if (distance < 20) {  // Motion Detected
    digitalWrite(BUZZER, HIGH);
    sendTelegramMessage("⚠️ Motion Detected! Someone is near the sensor!");
    delay(2000);  // Alert delay
  } else {
    digitalWrite(BUZZER, LOW);
  }

  delay(1000);
}

void sendTelegramMessage(String message) {
  if (!client.connect("api.telegram.org", 443)) {
    Serial.println("Connection to Telegram failed!");
    return;
  }

  String url = "/bot" + BOT_TOKEN + "/sendMessage?chat_id=" + CHAT_ID + "&text=" + message;
  client.print(String("GET ") + url + " HTTP/1.1\r\n" +
               "Host: api.telegram.org\r\n" +
               "Connection: close\r\n\r\n");

  delay(500);
  Serial.println("Telegram message sent!");
}
