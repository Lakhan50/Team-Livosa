#define BLYNK_TEMPLATE_ID "TMPL3z8wJ19rp"
#define BLYNK_TEMPLATE_NAME "Team Livosa"
#define BLYNK_AUTH_TOKEN "jLvy8K6HDGYX-85OGNC0seSPEa7Suq2z"

#include <WiFi.h>
#include <BlynkSimpleEsp32.h>
#include <DHT.h>

// WiFi
char ssid[] = "LAKHAN";
char pass[] = "asdfghjkl";

// Pin definitions
#define MQ2_PIN 34
#define MQ135_PIN 35
#define DHTPIN 4
#define DHTTYPE DHT22
#define RELAY_PIN 19
#define BUZZER_PIN 18

DHT dht(DHTPIN, DHTTYPE);
BlynkTimer timer;

// Send sensor data to Blynk
void sendSensorData()
{
  int gas = analogRead(MQ2_PIN);
  int voc = analogRead(MQ135_PIN);

  float temperature = dht.readTemperature();
  float humidity = dht.readHumidity();

  // Send to Blynk datastreams
  Blynk.virtualWrite(V0, gas);          // Gas sensor
  Blynk.virtualWrite(V1, voc);          // VOC sensor
  Blynk.virtualWrite(V2, temperature);  // Temperature
  Blynk.virtualWrite(V3, humidity);     // Humidity

  // Gas alert buzzer
  if (gas > 2000)
  {
    digitalWrite(BUZZER_PIN, HIGH);
  }
  else
  {
    digitalWrite(BUZZER_PIN, LOW);
  }
}

// Fan control from Blynk (V4)
BLYNK_WRITE(V4)
{
  int fanState = param.asInt();
  digitalWrite(RELAY_PIN, fanState);
}

void setup()
{
  Serial.begin(115200);

  pinMode(MQ2_PIN, INPUT);
  pinMode(MQ135_PIN, INPUT);
  pinMode(RELAY_PIN, OUTPUT);
  pinMode(BUZZER_PIN, OUTPUT);

  dht.begin();

  // Connect to Blynk
  Blynk.begin(BLYNK_AUTH_TOKEN, ssid, pass);

  // Send data every 2 seconds
  timer.setInterval(2000L, sendSensorData);
}

void loop()
{
  Blynk.run();
  timer.run();
} 