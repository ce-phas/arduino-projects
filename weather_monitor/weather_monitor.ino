#include "DHT.h"
#include "U8glib.h"

#define DHTPIN A1
#define DHTTYPE DHT11

DHT dht(DHTPIN, DHTTYPE);
U8GLIB_SSD1306_128X64 u8g(U8G_I2C_OPT_NO_ACK);

void setup() {
  // Serial.begin(9600);
  dht.begin();
}

void draw(float temp, float hum) {
  u8g.setFont(u8g_font_helvB10);
  u8g.setPrintPos(38, 15);
  u8g.print(temp);
  u8g.setPrintPos(77, 15);
  u8g.print("C");
  u8g.setPrintPos(38, 35);
  u8g.print(hum);
  u8g.setPrintPos(77, 35);
  u8g.print("%");
}

void loop() {
  u8g.firstPage();
  do
  {
    float hum = dht.readHumidity();
    float temp = dht.readTemperature();
    if (isnan(hum) || isnan(temp)) {
      Serial.println("Failed to read from DHT");
    } else {
      // Serial.print(temp);
      // Serial.print("C -- ");
      // Serial.print(hum);
      // Serial.println("%");
      draw(temp, hum);
    }
  } while(u8g.nextPage());
  delay(5000);
}
