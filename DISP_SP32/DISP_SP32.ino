
//int pinLDR = 34;
//const int pinLDR =34;
#define PIN_LDR 34
#define PIN_LM35 35
void setup() {
  Serial.begin(9600);

}

void loop() {

//int m = analogRead(PIN_LDR);
//serial.println(m)
  //Serial.println(analogRead(PIN_LDR));
  //7delay(100);


//5000/(10*4095) = 0.1221 -> conversion a grados C
  Serial.println(analogRead(PIN_LM35)*0.1221);
  delay(250);

}
