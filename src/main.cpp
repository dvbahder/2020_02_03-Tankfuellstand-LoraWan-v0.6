/*
// Füllhöhe messen mit VL53L0X-
//
*/
#include <Arduino.h>

#include <SPI.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#define OLED_RESET LED_BUILTIN  //4
Adafruit_SSD1306 display(OLED_RESET);
// Reset pin # (or -1 if sharing Arduino reset pin)

//---Konfiguration RCW0001------------
int i= 1;
int trigger = 13; //  D7 GPIO 13
int echo = 12;    //  D6 GPIO 12
long dauer = 0;
long entfernung = 0;

//---Konfiguration DS18B20------------
#include <OneWire.h>
#include <DallasTemperature.h> 
#define ONE_WIRE_BUS 0 //PIN D3 GPIO 0
#define Sensor_Aufloesung 12
DeviceAddress Sensor_Adressen;
OneWire oneWire(ONE_WIRE_BUS);
DallasTemperature sensors(&oneWire);
float TempIn = 999.99;
float Temperatur[2] = {999.99,999.99};

//--- void DS18B20 -----------------------
void Sensor_DS18B20() {
sensors.requestTemperatures();
Temperatur[0] = sensors.getTempCByIndex(0);
  // Serial.print("Messung TempIn...");
    // delay(100);
    if ((Temperatur[0] < 60) and (Temperatur[0] > -40)); // Werte für Fehlererkennung
    else {
    Temperatur[0] = 999.99;  
    }
TempIn = Temperatur[0];
  // Serial.println(TempIn);
} // void Sensor_DS18B20 END

void setup() {
  Serial.begin(115200);
  Serial.println("HX711 Demo - Initializing the OLED");
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);
  display.clearDisplay(); // Clear the buffer
  display.display();
  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.setCursor(10,10);
  display.println("Füllstand Test");
  display.display();
  //--- SETUP RCW0001 -----------------------
  Serial.println ("Initialisierung Ultraschallsensor");
  pinMode(trigger, OUTPUT);
  pinMode(echo, INPUT);
  //--- SETUP DS18B20 -----------------------
  Serial.println("Initialisiere DS18B20...");
  sensors.begin();
  sensors.getAddress(Sensor_Adressen, 0);
  sensors.setResolution(Sensor_Adressen, Sensor_Aufloesung);
  delay(100);
}

void loop() {
  i += 1;
  Serial.print("Messung: ");
  Serial.println(i);  
  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.setCursor(10,0);
  display.print("Messung: ");
  display.println(i);
  digitalWrite(trigger, LOW);
  delay(5);
  digitalWrite(trigger, HIGH);
  delay(10);
  digitalWrite(trigger, LOW);
  dauer = pulseIn(echo, HIGH);
  entfernung = (dauer / 2) / 29.1;
  Serial.print("Wert Entfernung: ");
  Serial.println(entfernung);
  display.setTextSize(2);
  display.println(" ");
  display.print(entfernung);
  display.println(" cm");
  display.display();
  display.clearDisplay();
  if (entfernung >= 200 || entfernung <= 0)
  {
    entfernung = 0;
  }
  else
  {
  entfernung = 180 - entfernung;
  entfernung = entfernung * 84.7457;
  }
  Sensor_DS18B20();
  delay(10);
  Serial.print ("Temperatur: ");
  Serial.println (TempIn);
  delay(100);

}