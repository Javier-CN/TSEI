#define LED_R 14
#define LED_G 27 
#define LED_B 12
#define PIN_BUTTON 33

//para llevar el status (color) del LED
int led_status = 0;

//debouncing
unsigned long lastDebounceTime = 0;
unsigned long debounceDelay = 300; 


void IRAM_ATTR isr_button(){  //isr= interupt service rutine
  
  if ((millis() - lastDebounceTime) > debounceDelay) //milis cuenta el tiempo que ha pasado desde que se inicio el sistema
   
  {  
     led_status++; 
     
     if (led_status >= 8)
     {
          led_status = 0;
     }
     lastDebounceTime = millis();
  }
}

void setup() {  
  //Boton
  pinMode(PIN_BUTTON, INPUT);
  attachInterrupt(PIN_BUTTON, isr_button, RISING);

  //LEDS
  pinMode(LED_R,OUTPUT);
  pinMode(LED_G,OUTPUT);
  pinMode(LED_B,OUTPUT);

  Serial.begin(115200);
}

void loop() {    
  
  //Menú de colores
  switch (led_status) {
    
        case 1: //red
          digitalWrite(LED_R,LOW);
          digitalWrite(LED_G,HIGH);
          digitalWrite(LED_B,HIGH); 
        break;
        
        case 2: //green
          digitalWrite(LED_R,HIGH);
          digitalWrite(LED_G,LOW);
          digitalWrite(LED_B,HIGH); 
        break;
        
        case 3: //blue
          digitalWrite(LED_R,HIGH);
          digitalWrite(LED_G,HIGH);
          digitalWrite(LED_B,LOW); 
        break;
        
        case 4: //cyan
          digitalWrite(LED_R,HIGH);
          digitalWrite(LED_G,LOW);
          digitalWrite(LED_B,LOW); 
        break;    
              
        case 5: //yellow
          digitalWrite(LED_R,LOW);
          digitalWrite(LED_G,LOW);
          digitalWrite(LED_B,HIGH); 
        break;
        
        case 6: //magenta
          digitalWrite(LED_R,LOW);
          digitalWrite(LED_G,HIGH);
          digitalWrite(LED_B,LOW); 
        break;
        
        case 7: //white
          digitalWrite(LED_R,LOW);
          digitalWrite(LED_G,LOW);
          digitalWrite(LED_B,LOW); 
        break;  
                          
        default: //off
          digitalWrite(LED_R,HIGH);
          digitalWrite(LED_G,HIGH);
          digitalWrite(LED_B,HIGH); 
      }
}
