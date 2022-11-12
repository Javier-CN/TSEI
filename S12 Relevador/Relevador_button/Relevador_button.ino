#define PIN_Button 33
#define PIN_Rel 15

//inicializar el statusdel relevador
int rel_status = 0;

// Debouncing
unsigned long lastDebounceTime = 0;
unsigned long debounceDelay = 250;

void IRAM_ATTR isr_button(){

  if ((millis() - lastDebounceTime) > debounceDelay){
     rel_status++; 
     if (rel_status >= 2) rel_status = 0;

     lastDebounceTime = millis();
  }
  
}

void setup() {

  Serial.begin(115200);
  // Interrupción
  
  pinMode(PIN_Button, INPUT);
  attachInterrupt(PIN_Button, isr_button, RISING);

  
  pinMode(PIN_Rel, OUTPUT);

}

void loop() {

  switch(rel_status){
    case 0: // OFF
      digitalWrite(PIN_Rel, LOW);
    break;

    case 1: // ON
      digitalWrite(PIN_Rel, HIGH);
    break;
  }
  
}
