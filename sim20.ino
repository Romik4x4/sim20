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

SoftwareSerial mySerial(3,2); // RX-3, TX-2

long previousMillis = 0;        
long interval = 100;            

void setup() {

  pinMode(8,INPUT); // Главная кнопка
  pinMode(5,INPUT);
  pinMode(4,INPUT);

  display.begin(SSD1306_SWITCHCAPVCC, 0x3D);
  display.clearDisplay();
  display.display();

  mySerial.begin(115200);
  // mySerial.println("AT+SRDUART=2,0");

  display.setTextSize(2);
  display.setTextColor(WHITE);
  display.setCursor(0,0);
  display.print("SIM20 Module.");
  display.display();

}

void loop()
{

  unsigned long currentMillis = millis();

  if (currentMillis - previousMillis > interval) {
    previousMillis = currentMillis;

    mySerial.print("AT+SRDSEND=255,\"X:");
    mySerial.print(analogRead(A7));
    mySerial.print(":Y:");
    mySerial.print(analogRead(A6));
    mySerial.println("\"");

    display.clearDisplay();
    display.setCursor(0,5);
    display.print("X: ");

    display.print(analogRead(A7));
    display.setCursor(0,25);
    display.print("Y: ");
    display.print(analogRead(A6));

    display.setCursor(0,45);
    display.print("D8/5/4: ");
    display.print(digitalRead(8));
    display.print("/");
    display.print(digitalRead(5));
    display.print("/");
    display.print(digitalRead(4));


    display.display();

  }
}





