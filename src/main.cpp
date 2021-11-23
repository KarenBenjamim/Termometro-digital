#include <Arduino.h>
#include <Adafruit_Sensor.h> // Biblioteca DHT Sensor Adafruit
#include <DHT.h>
#include <DHT_U.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>

//Inicializa o display no endereco 0x27
LiquidCrystal_I2C lcd(0x27,16,2);

#define DHTTYPE DHT11 // Sensor DHT11
#define DHTPIN 14 // Pino do Arduino no Sensor (Data)
DHT_Unified dht(DHTPIN, DHTTYPE); // configurando o Sensor DHT - pino e tipo
uint32_t delayMS = 3000; // variável para atraso no tempo
float Temp1, Temp2, Temp3, Temp4;

#define Button1 26
#define Button2 27
#define Button3 33

void LCD(){
   lcd.backlight();
   lcd.clear();
   lcd.setCursor(0, 0);
   lcd.print(Temp4);
   lcd.setCursor(0, 1);
   lcd.print(Temp3);
   lcd.setCursor(4, 1);
   lcd.print("  ");
   lcd.setCursor(6, 1);
   lcd.print(Temp2);
   lcd.setCursor(10, 1);
   lcd.print("  ");
   lcd.setCursor(12, 1);
   lcd.print(Temp1);
   delay(10000);
   lcd.noBacklight();
   lcd.clear();
   delay(10000);
}

void Temp(){
    sensors_event_t event; // inicializa o evento da Temperatura
    dht.temperature().getEvent(&event); // faz a leitura da Temperatura

    if (isnan(event.temperature)) // se algum erro na leitura
    {
        Serial.println("Erro na leitura da Temperatura!");
    }
    else // senão
    {
        Serial.print("1º Temperatura: "); // imprime a Temperatura
        Temp1 = 00.0;
        Serial.print(Temp1);
        Serial.println(" *C");
        delay(delayMS);
        Serial.print("2º Temperatura: ");
        Temp2 = 00.0;
        Serial.print(Temp2);
        Serial.println(" *C");
        delay(delayMS);
        Serial.print("3º Temperatura: ");
        Temp3 = 00.0;
        Serial.print(Temp3);
        Serial.println(" *C");
        delay(delayMS);
        Serial.print("4º Temperatura: ");
        Temp4 = event.temperature;
        Serial.print(Temp4);
        Serial.println(" *C");

        LCD();
        Serial.println("----------------------------------");
    }
}

void setup(){
  Serial.begin(9600); // monitor serial 9600 bps
  dht.begin(); // inicializa a função
  Serial.println("Usando o Sensor DHT");
  lcd.init();

  Temp();
  LCD();  
}
 
void loop(){
  sensors_event_t event; // inicializa o evento da Temperatura
  dht.temperature().getEvent(&event); // faz a leitura da Temperatura
  Serial.println("------------------LOOP----------------");
  Temp1 = Temp2;
  delay(delayMS);
  Temp2 = Temp3;
  delay(delayMS);
  Temp3 = Temp4;
  delay(delayMS);
  Temp4 = event.temperature;
  
  Serial.print("1º Temperatura: "); // imprime a Temperatura
  Serial.print(Temp1);
  Serial.println(" *C");
  
  Serial.print("2º Temperatura: ");
  Serial.print(Temp2);
  Serial.println(" *C");
  
  Serial.print("3º Temperatura: ");
  Serial.print(Temp3);
  Serial.println(" *C");
  
  Serial.print("4º Temperatura: ");
  Serial.print(Temp4);
  Serial.println(" *C");
  Serial.println("---------------------------------------");
  LCD();
}