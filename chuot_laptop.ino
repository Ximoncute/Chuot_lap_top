#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>

const char* ssid = "P502";
const char* password = "88888888";

const char* serverIP = "192.168.52.47";   // IP máy tính

#define BUTTON_PIN 13

int clickCount = 0;
unsigned long lastPressTime = 0;

void sendURL(String url)
{
  WiFiClient client;
  HTTPClient http;

  http.begin(client, url);
  http.GET();
  http.end();
}

void clickMouse()
{
  sendURL("http://" + String(serverIP) + ":5000/click");
}

void moveMouse(int dx, int dy)
{
  String url = "http://" + String(serverIP) +
               ":5000/move?dx=" + String(dx) +
               "&dy=" + String(dy);

  sendURL(url);
}

void setup()
{
  pinMode(BUTTON_PIN, INPUT_PULLUP);

  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED)
  {
    delay(500);
  }
}

void loop()
{
  static bool lastState = HIGH;

  bool state = digitalRead(BUTTON_PIN);

  if (lastState == HIGH && state == LOW)
  {
    clickCount++;
    lastPressTime = millis();
    delay(50); // chống dội
  }

  lastState = state;

  if (clickCount > 0 && millis() - lastPressTime > 500)
  {
    switch (clickCount)
    {
      case 1:
        clickMouse();
        break;

      case 2:
        moveMouse(5, 0);      // phải
        break;

      case 3:
        moveMouse(-5, 0);     // trái
        break;

      case 4:
        moveMouse(0, -5);     // lên
        break;

      case 5:
        moveMouse(0, 5);      // xuống
        break;

      case 6:
        moveMouse(0, 0);      // dừng
        break;
    }

    clickCount = 0;
  }
}