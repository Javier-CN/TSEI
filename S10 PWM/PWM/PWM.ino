#define PWM_PIN 32
#define PWM_FREQ 10000 //[Hz]       Frecuencia <1kHz poca eficiencia; >5kHz buena eficiencia
#define PWM_CHANNEL 0
#define PWM_RESOLUTION 8 //Profundidad de bits
#define BUTTON_PIN 33

float t; //tiempo
int  waveform = 0;  //Menu de formas de onda
float dutyCycle = 0 ; //Que tan grande es el pulso - 100% Prendido todo el tiempo y 0% Apagado todo el tiempo

void setup() {
  Serial.begin(115200);
  pinMode(BUTTON_PIN,INPUT_PULLDOWN);


  //Configuracion de PWM  
  ledcSetup(PWM_CHANNEL, PWM_FREQ , PWM_RESOLUTION); // Configuracion del canal PWM
  ledcAttachPin(PWM_PIN, PWM_CHANNEL); // Asignación del canal a un pin
}

void loop() {  
  
if(digitalRead(BUTTON_PIN)){

  waveform++;
  if(waveform > 7){
    waveform = 0;
  }
  Serial.println(waveform);
  delay(500);
}  

//Tiempo del ciclo
  t++; if(t>=256){t=0;} 

  //Menú de formas de onda 
  switch (waveform){    
    case 0:
      dutyCycle = 0; //dutycycle va de 0 a 1
      break;    
    case 1:
      dutyCycle = 0.3;
      break;        
    case 2:
      dutyCycle = 0.5;
      break;    
    case 3:
      dutyCycle = 0.8;
      break;
    case 4:
      dutyCycle = 1;
      break;
    case 5:
      dutyCycle = (t+0.1)/256;
      delay(2.5);
      break;
    case 6:    
      dutyCycle = 0.5*sin(2*PI*t/256)+0.5;
      delay(0.5);
      break;
    case 7:    
      dutyCycle = pow(2.71828,((t/255)-1)*2);
      delay(4);
      break;
  }

  Serial.println(dutyCycle*100);
  
  ledcWrite(PWM_CHANNEL, dutyCycle*255);  
}
