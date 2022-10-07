#include "FS.h"
#include "SPIFFS.h"
#include <ArduinoJson.h>

//funcion parecida las que habia en los ejemplos de SPIFFS

void JsonRead(fs::FS &fs, const char * filename) {
  Serial.printf("Reading file: %s\r\n", filename);
  
  File file = fs.open(filename, "r");

  if(!file || file.isDirectory()){
        Serial.println("- failed to open file for reading");
        return;
    }
  StaticJsonDocument<200> doc;

  // Deserializar el archivo y verificar por errores//
  DeserializationError error = deserializeJson(doc, file);

   if (error) {
    Serial.print(F("deserialización fallida"));
    Serial.println(error.f_str());
    return;
   }

  // Seleccionamos el campo que queremos que imprima, en este caso solo hay uno //
  Serial.println(doc["nombre_alumno"].as<const char*>());
}

void setup() {
  
  Serial.begin(9600);
  if(!SPIFFS.begin(true)){
        Serial.println("SPIFFS Mount Failed");
        return;
    }

}

void loop() {

  JsonRead(SPIFFS, "/json_test.txt");
  delay(5000);
  
}
