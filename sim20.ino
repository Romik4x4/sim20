// Arduino 1.0.6.Work

#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define OLED_MOSI   9
#define OLED_CLK   10
#define OLED_DC    11
#define OLED_CS    12
#define OLED_RESET 13

Adafruit_SSD1306 display(OLED_MOSI, OLED_CLK, OLED_DC, OLED_RESET, OLED_CS);

#include <SoftwareSerial.h>

SoftwareSerial sSerial(3,2); // RX-3, TX-2

long previousMillis = 0;        
long interval = 100;            

boolean startXY = false;
boolean d8 = false;

void setup() {

  pinMode(8,INPUT); // Главная кнопка
  pinMode(5,INPUT);
  pinMode(4,INPUT);

  display.begin(SSD1306_SWITCHCAPVCC, 0x3D);
  display.clearDisplay();
  display.display();

  sSerial.begin(9600);

  display.setTextSize(2);
  display.setTextColor(WHITE);
  display.setCursor(0,0);
  display.display();

}

void loop()
{

  unsigned long currentMillis = millis();

  if (currentMillis - previousMillis > interval) {
    previousMillis = currentMillis;

    if (digitalRead(5) == 1) {
      startXY = true;
    } 

    if (digitalRead(8) == 1) {
      d8 = !d8;
    } 

    if (digitalRead(4) == 1) {
      startXY = false;
    } 

    if (startXY) {
      sSerial.print("AT+SRDSEND=255,\"X:");
      sSerial.print(analogRead(A7));
      sSerial.print(":Y:");
      sSerial.print(analogRead(A6));
      sSerial.print(":D:");
      if (d8) sSerial.print("1");
      if (!d8) sSerial.print("0");
      sSerial.println("\"");        
    }

    display.clearDisplay();
    display.setTextSize(2);
    display.setTextColor(WHITE);
    display.setCursor(0,5);
    display.print("X: ");

    display.print(analogRead(A7));
    display.setCursor(0,25);
    display.print("Y: ");
    display.print(analogRead(A6));

    display.setTextSize(1);
    display.setTextColor(WHITE);
    display.setCursor(0,50);
    if (startXY) {
      display.print("Sending...");
    } 
    else {
      display.print("Wait to start.");
    }

    display.display();

  }
}








