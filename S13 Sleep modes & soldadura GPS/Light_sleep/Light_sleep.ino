#define uS_TO_S_FACTOR 1000000 // factor de conversion micro seg a seg
#define TIME_TO_SLEEP 10       // tiempo en el que el ESP se va a mimir en seg
#define LED_PIN 32

void setup() {

  Serial.begin(115200);
  pinMode (LED_PIN, OUTPUT);
  esp_sleep_enable_timer_wakeup (TIME_TO_SLEEP*uS_TO_S_FACTOR);  //Le pasamos el tiempo en seg a la funcion
  Serial.println("Configurando ESP32 para dormir por" + String(TIME_TO_SLEEP) + "segundos");

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
