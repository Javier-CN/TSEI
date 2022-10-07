//const int PIN = 33

//creamos una variable con otras dentro
struct Button {
  const int PIN;
  int numTimeButtonPressed;
  bool pressed;  
};

Button button1 = {33,0,false}; //inicializar la variable

void IRAM_ATTR isr_button () {

  button1.numTimeButtonPressed += 1;
  button1.pressed = true;
  
}

void setup() {
 Serial.begin(9600);
 pinMode(button1.PIN,INPUT);
 attachInterrupt(button1.PIN,isr_button,RISING); 

}

void loop() {

  if(button1.pressed == true){
    Serial.printf("El Botón se ha presionado %u veces \n ",button1.numTimeButtonPressed);
    button1.pressed = false;  
  }
    delay(100);
}    
