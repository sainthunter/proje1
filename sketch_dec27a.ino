#include <DHT.h>
#include <LiquidCrystal.h>
#include "DHT.h"
#define DHTPIN 22
#define DHTTYPE DHT11


LiquidCrystal lcd(8, 9, 4, 5, 6, 7);
int gelenVeri = 0;   // genel veriyi tutacak değişken
char gelenKarakter;
int trigPin = 31;
int echoPin = 33;
DHT sicaklik(DHTPIN, DHTTYPE);
long uzaklik;
long sure;
long uzaklik2;

int hareket;
void setup() {
    // Seri haberleşmeyi başlatıyoruz (9600 bps hızında)
    Serial.begin(9600);
    pinMode(trigPin, OUTPUT); 
    pinMode(echoPin, INPUT); 
    lcd.begin(16, 2);               
    lcd.setCursor(0,0);
    lcd.println("Sicaklik:              ");
    
   
}

void loop() {
  delay(1000);
  float isi = sicaklik.readTemperature();
  //int isiC = isi;
  lcd.setCursor(9,0);
  lcd.println(isi,0);
  lcd.setCursor(11,0);
  lcd.println("                ");
 

  int hareket = 1;
  Serial.print("Sıcaklık:");
  Serial.println(isi);
  if(isi>20){
  digitalWrite(trigPin, LOW); 
  delayMicroseconds(5);
  digitalWrite(trigPin, HIGH); 
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);  
  sure = pulseIn(echoPin, HIGH); 
  uzaklik = sure / 29.1 / 2;
  delay(2000);
  digitalWrite(trigPin, LOW); 
  delayMicroseconds(5);
  digitalWrite(trigPin, HIGH); 
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);  
  sure = pulseIn(echoPin, HIGH); 
  uzaklik2 = sure / 29.1 / 2;
  
  if(uzaklik==uzaklik2){
    hareket=0;
  }
  }
  
  
  

        // Veri gelmiş mi?
        if (Serial.available() > 0) {
                // gelen veriyi oku
                gelenVeri = Serial.read();
                gelenKarakter = gelenVeri;
                
                
                if(gelenKarakter==49){
                  Serial.println("ÇALIŞTI");
                  lcd.setCursor(0,1);
                  lcd.println("CALISIYOR");
                  lcd.setCursor(9,1);
                  lcd.println("                ");
                  pinMode(13, LOW);
                  delay(1000);
                  if(hareket==0){
                     Serial.println("arıza");
                      lcd.setCursor(0,1);
                      lcd.println("ARIZA");
                      pinMode(13 , LOW);
                      lcd.setCursor(5,1);
                      lcd.println("                ");
                      while(true);
                     }
                  }
                if(gelenKarakter==50){
                  Serial.println("DURDU");
                  lcd.setCursor(0,1);
                  lcd.println("DURDU");
                  lcd.setCursor(5,1);
                  lcd.println("                ");
                  pinMode(13 , HIGH);
                  delay(200);
                  
                }
                }
        
        if(isi>20){
          if(hareket==0){
            Serial.println("arıza");
            lcd.setCursor(0,1);
            lcd.println("ARIZA");
            pinMode(13 , LOW);
            lcd.setCursor(5,1);
            lcd.println("                ");
            while(true);
          }
          Serial.println("ÇALIŞTI");
          lcd.setCursor(0,1);
          lcd.println("CALISIYOR");
          lcd.setCursor(9,1);
          lcd.println("                ");
          pinMode(13 , LOW);
          delay(5000);
          if(isi<=20){
          Serial.println("DURDU");
          lcd.setCursor(0,1);
          lcd.println("DURDU");
          lcd.setCursor(5,1);
          lcd.println("                ");
          pinMode(13, HIGH);
          delay(5000);
        }
        }
        
}
