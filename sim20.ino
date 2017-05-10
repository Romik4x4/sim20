// Arduino 1.0.6.Work

#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

// If using software SPI (the default case):
#define OLED_MOSI   9
#define OLED_CLK   10
#define OLED_DC    11
#define OLED_CS    12
#define OLED_RESET 13
Adafruit_SSD1306 display(OLED_MOSI, OLED_CLK, OLED_DC, OLED_RESET, OLED_CS);
#include <SoftwareSerial.h>
#include "U8glib.h"

U8GLIB_SSD1306_128X64 u8g(10,9,12,11,13); // Arduino Fio

SoftwareSerial mySerial(3, 2); // RX, TX

const int ledPin =  13;      // the number of the LED pin

int ledState = LOW;             // ledState used to set the LED
long previousMillis = 0;        // will store last time LED was updated
long interval = 100;            // interval at which to blink (milliseconds)

void setup() {

  pinMode(ledPin, OUTPUT);
  mySerial.begin(9600);
  mySerial.print("AT+SRDSEND=255,\"");
  mySerial.print("Start ... SIM20 Module ... 9600");
  mySerial.println("\"");
 
}

void loop()
{

  unsigned long currentMillis = millis();

  if (currentMillis - previousMillis > interval) {
    previousMillis = currentMillis;

  u8g.firstPage();  
  do {
    draw();
  } while( u8g.nextPage() );
  
    mySerial.print("AT+SRDSEND=255,\"");
    mySerial.print(analogRead(A7));
    mySerial.println("\"");
     
    if (ledState == LOW)
      ledState = HIGH;
    else
      ledState = LOW;

    digitalWrite(ledPin, ledState);
  }
}

void draw(void) {
  // graphic commands to redraw the complete screen should be placed here  
  u8g.setFont(u8g_font_unifont);
  //u8g.setFont(u8g_font_osb21);
  u8g.drawStr( 0, 22, "Hello World!");
}
