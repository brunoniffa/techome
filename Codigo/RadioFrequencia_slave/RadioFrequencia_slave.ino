#include <RF24.h>

RF24 radio(6,8);

byte enderecos[][6] = {"1node","2node"};
int dadosRecebidos;
int led = 3;

void setup() {
  
  pinMode(led, OUTPUT);
  digitalWrite(led, HIGH);

  radio.begin();
  
  radio.openWritingPipe(enderecos[1]);
  radio.openReadingPipe(1, enderecos[0]);

  radio.startListening();  

/*  #if radioID == 0
      radio.openWritingPipe(enderecos[0]);
      radio.openReadingPipe(1, enderecos[1]);
  #else
      radio.openWritingPipe(enderecos[1]);
      radio.openReadingPipe(1, enderecos[0]);
  #endif

  //Solicita os dados do outro aparelho, se ele estiver ligado. Tenta a comunicação por 2 segundos.
  radio.stopListening();                                   
  long tempoInicio = millis();
  while ( !radio.write( &dadosRF, sizeof(tipoDadosRF) ) ) {
     if ((millis() - tempoInicio) > 2000) {
        break;
     }   
  }
  radio.startListening();  
}
*/
}

void loop() {
   
  if (radio.available()) {                                   
     radio.read( &dadosRecebidos, sizeof(int) ); 

  if (dadosRecebidos == 1) {
      digitalWrite(led, LOW);
      delay(50);
     }
  if (dadosRecebidos == 0) {
      digitalWrite(led, HIGH);
      delay(50);
     } 
  }
}
  
