#include<Adafruit_BMP280.h>
#include<SD.h>
#include<sd_diskio.h>

#define PIN_LED 32

Adafruit_BMP280 bmp;
File datosBMP;
File read_me;
char payload [50]; //datos que se escriben en la sd y serial

void setup() {
  Serial.begin(115200); //inicializar serial
  bmp.begin(0x76); //Inicializa la comunicacion I2C con el sensor barometrico
  SD.begin();

  pinMode(PIN_LED, OUTPUT);

  read_me = SD.open("/README.txt",FILE_WRITE);
  read_me.print("Datos tomados por el sensor BMP280, Temperatura [°C], Presion [Pa]");
  read_me.close();
  
}

void loop() {
  //Imprima en columna 1: la temperatura y columna 2:Presión
  //Manera rudimentaria:
  //Serial.print(bmp.readPressure());
  //Serial.print(",");
  //Serial.println(bmp.readTemperature());

//Lee e imprime Temperatura y presion del BMP280 en serial
  sprintf(payload,"%.2f,%.2f",bmp.readTemperature(),bmp.readPressure());
  Serial.println(payload);

//Para escribir a la tarjeta (abrir, escribir y cerrar)

digitalWrite(PIN_LED,HIGH); //Prender led cuando escriba
  datosBMP=SD.open("/datosBMP.csv",FILE_APPEND);
  datosBMP.println(payload);
  datosBMP.close();
digitalWrite(PIN_LED,LOW); //Apagarlo cuando acabe
  
  delay(500);
  

}
