RTC_DATA_ATTR int bootCount = 0; //sE GUARDA EN EL rtc QUE SI SE MANTIENE ACTIVO


#define uS_TO_S_FACTOR 1000000 // factor de conversion micro seg a seg
#define TIME_TO_SLEEP 5       // tiempo en el que el ESP se va a mimir en seg
#define LED_PIN 32
#define BUTTON_PIN 33

void setup() {

  Serial.begin(115200);
  delay(1000);
  pinMode (LED_PIN, OUTPUT);

  bootCount ++;
  Serial.println("Numero de veces iniciado: " + String(bootCount));

  print_wakeup_reason();
  
  esp_sleep_enable_ext0_wakeup ((gpio_num_t)BUTTON_PIN,HIGH); //Si el boton esta en high despierta
  esp_sleep_enable_timer_wakeup (TIME_TO_SLEEP*uS_TO_S_FACTOR);  //Si pasa este tiempo despierta
  Serial.println("Configurando ESP32 para dormir por" + String(TIME_TO_SLEEP) + "segundos");

  if(bootCount%2 == 0){
    Serial.println("ESP32 se va adormir ahora");
    esp_deep_sleep_start();  
  }
  Serial.println("Esta linea solo se imprimira en inicios impares");
}

void loop() {

  digitalWrite (LED_PIN, LOW);  //cuando se duerma se apaga
  esp_light_sleep_start();

  digitalWrite (LED_PIN, HIGH); //cuando se despierte enciende el led por un momento
  delay(500);

  print_wakeup_reason();
  
  }

void print_wakeup_reason () {

   esp_sleep_wakeup_cause_t wakeup_reason;

   wakeup_reason = esp_sleep_get_wakeup_cause();

   switch (wakeup_reason){

    case ESP_SLEEP_WAKEUP_EXT0:
      Serial.println("Inicio causado por señal en el RTC_IO (Periferiocos del RTC)");
    break;

    case ESP_SLEEP_WAKEUP_EXT1:
      Serial.println("Inicio causado por señal en el CNTL");
    break;

    case ESP_SLEEP_WAKEUP_TIMER:
      Serial.println("Inicio causado por señal en un Timer");
    break;

    case ESP_SLEEP_WAKEUP_TOUCHPAD:
      Serial.println("Inicio causado por señal en un PIN Touch");
    break;

    case ESP_SLEEP_WAKEUP_ULP:
      Serial.println("Inicio causado por señal lanzada por el ULP");
    break;

    default:
      Serial.printf("El inicio no fue causado por ninguna razón conocida $d\n", wakeup_reason);
   }
}
