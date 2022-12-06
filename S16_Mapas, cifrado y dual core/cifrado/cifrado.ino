#include "mbedtls/aes.h"

void encrypt(char * PlainText,char * key, unsigned char * outputBuffer){

 mbedtls_aes_context aes;

  mbedtls_aes_init(&aes); 
  mbedtls_aes_setkey_enc(&aes,(const unsigned char*)key,strlen(key) * 8);  //llave para la encriptación
  mbedtls_aes_crypt_ecb(&aes,MBEDTLS_AES_ENCRYPT , (const unsigned char*)PlainText , outputBuffer); //Hasta aqui ya de cifro el texto
  mbedtls_aes_free(&aes);
  
}


void decrypt(unsigned char * ChipherText,char * key, unsigned char * outputBuffer){

  mbedtls_aes_context aes;

  mbedtls_aes_init(&aes); 
  mbedtls_aes_setkey_dec(&aes,(const unsigned char*)key,strlen(key)*8);  //llave para la encriptación
  mbedtls_aes_crypt_ecb(&aes,MBEDTLS_AES_DECRYPT , (const unsigned char*)ChipherText , outputBuffer); //Hasta aqui ya de cifro el texto
  mbedtls_aes_free(&aes);
  
}


void setup() {

  Serial.begin(115200);

  
  unsigned char cipheredTextOutput[16];
  unsigned char decipheredTextOutput[16];
  char *texto = "Texto a encriptar";
  char *key = "dieciseisletras1";

  encrypt(texto,key, cipheredTextOutput); //encripta esto, con esta clave, y guardalo aqui
  decrypt(cipheredTextOutput ,key, decipheredTextOutput); //encripta esto, con esta clave, y guardalo aqui

  Serial.print("Texto cifrado: ");
  for(int i=0; i<16;i++){
    Serial.print(cipheredTextOutput[i]);
  }

   Serial.print("Texto decifrado: ");
  for(int i=0; i<16;i++){
    Serial.print((char)decipheredTextOutput[i]);
  }

}

void loop() {
  // put your main code here, to run repeatedly:

}
