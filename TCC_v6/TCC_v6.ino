/*
  Projeto de TCC - Bruno Niffa
  Automação Residencial
  Arduino: Mega 2560 !
  Versões:
    v1 - Luzes OK
    v2 - Alarme OK
    v3 - Sensor presença OK
    v4 - Sensor luminosidade OK
    v5 - Ventilador - OK
    v6 - Comandos LED IR - OK
*/

#include <SoftwareSerial.h>
#include <elapsedMillis.h>   // Lib para piscar Leds a cada 1 segundo durante Sirene
#include <IRremote.h>

IRsend irsend;
elapsedMillis timeElapsed;

// Definindo Leds dos cômodos da casa:
int led_sala = 12;
int led_quarto = 11;
int led_escritorio = 5;
int led_cozinha = 8;
int led_banheiro = 9;
int led_garagem = 7;
int led_rua = 6;

int pinBuzzer = 22;
int ventilador = 25;
int pinSensorPIR = 10;
unsigned int interval = 1000;   // 1 segundo
int StatusSensorPIR = 0;
int pinSensorLum = A0;
int StatusSensorLum = 0;      

void setup()
{
  Serial.begin(9600);

  // Inicializa os pinos dos Leds como tipo saída:
  pinMode(led_sala, OUTPUT);
  pinMode(led_quarto, OUTPUT);
  pinMode(led_escritorio, OUTPUT);
  pinMode(led_cozinha, OUTPUT);
  pinMode(led_banheiro, OUTPUT);
  pinMode(led_garagem, OUTPUT);
  pinMode(led_rua, OUTPUT);
  pinMode(pinBuzzer, OUTPUT);
  pinMode(pinSensorPIR, INPUT);
  pinMode(ventilador, OUTPUT);
        

  // Garantir que todos 'output' começarão desligados:
  digitalWrite(led_sala, LOW);
  digitalWrite(led_quarto, LOW);
  digitalWrite(led_escritorio, LOW);
  digitalWrite(led_cozinha, LOW);
  digitalWrite(led_banheiro, LOW);
  digitalWrite(led_garagem, LOW);
  digitalWrite(led_rua, LOW);
  digitalWrite(ventilador, LOW);

  
  desligarAlarme();       // Inicializar com Alarme off
}

void loop()
{
  int valorPIR = digitalRead(pinSensorPIR);
  int valorLum = analogRead(pinSensorLum); 
  //Serial.println(valorLum);

  char comando;
  if (Serial.available() > 0)          // Serial utilizada pelo Jarvis
  {
    comando = Serial.read();           // Recebe comando de voz do Jarvis
  }

  // Ações sobre os cômodos:

  if (comando == 'S')
  {
    digitalWrite(led_sala, HIGH);
  }
  if (comando == 's')
  {
    digitalWrite(led_sala, LOW);
  }
  if (comando == 'Q')
  {
    digitalWrite(led_quarto, HIGH);
  }
  if (comando == 'q')
  {
    digitalWrite(led_quarto, LOW);
  }
  if (comando == 'E')
  {
    digitalWrite(led_escritorio, HIGH);
  }
  if (comando == 'e')
  {
    digitalWrite(led_escritorio, LOW);
  }
  if (comando == 'C')
  {
    digitalWrite(led_cozinha, HIGH);
  }
  if (comando == 'c')
  {
    digitalWrite(led_cozinha, LOW);
  }
  if (comando == 'B')
  {
    digitalWrite(led_banheiro, HIGH);
  }
  if (comando == 'b')
  {
    digitalWrite(led_banheiro, LOW);
  }
  if (comando == 'G')
  {
    digitalWrite(led_garagem, HIGH);
  }
  if (comando == 'g')
  {
    digitalWrite(led_garagem, LOW);
  }
  if (comando == 'R')
  {
    digitalWrite(led_rua, HIGH);
  }
  if (comando == 'r')
  {
    digitalWrite(led_rua, LOW);
  }
  if (comando == 'T')
  {
    ligarTudo();
  }
  if (comando == 't')
  {
    desligarTudo();
  }
  if (comando == 'W')
  {
    digitalWrite(ventilador, HIGH);
  }
  if (comando == 'w')
  {
    digitalWrite(ventilador, LOW);
  }
  if (comando == 'O')
  {
    // IR ON
    irsend.sendNEC(0xF7C03F, 32);
    delay(50);
    irsend.sendNEC(0xF7C03F, 32);
    delay(50);
    irsend.sendNEC(0xF7C03F, 32);    
  }
  if (comando == 'o')
  {
    // IR OFF
    irsend.sendNEC(0xF740BF, 32);
    delay(50);
    irsend.sendNEC(0xF740BF, 32); 
    delay(50);
    irsend.sendNEC(0xF740BF, 32);           
  }
  if (comando == 'V')
  {
    // IR verde
    irsend.sendNEC(0xF7A05F, 32);
    delay(50);
    irsend.sendNEC(0xF7A05F, 32);
    delay(50);
    irsend.sendNEC(0xF7A05F, 32);        
  }
  if (comando == 'v')
  {
    // IR vermelho
    irsend.sendNEC(0xF720DF, 32);
    delay(50);
    irsend.sendNEC(0xF720DF, 32);
    delay(50);
    irsend.sendNEC(0xF720DF, 32);          
  }

  // Ações sobre os alarmes:

  if (comando == 'H')
  {
    delay(5);
    StatusSensorPIR = 1;   // Vai ativar a detecção de movimentos
  }
  if (comando == 'h')
  {
    StatusSensorPIR = 0;   // Vai desativar a detecção de movimentos
  }
  if (comando == 'L')
  {
    StatusSensorLum = 1;   // Vai ativar sensor de luminosidade
  }
  if (comando == 'l')
  {
    StatusSensorLum = 0;   // Vai desativar sensor de luminosidade
    digitalWrite(led_rua, LOW);

  }
  if (comando == 'A')
  {
    ligarAlarme();      // Liga manualmente o Alarme
  }
  if (comando == 'a')
  {
    desligarAlarme();   // Desliga manualmente o Alarme
  }
  if (valorPIR == 1 && StatusSensorPIR == 1)   // Verifica se ocorreu movimentos e se o alarme deve tocar
  {
    ligarAlarme();
  }
  if ((valorLum>700) && (StatusSensorLum == 1))   
  // Verifica se escureceu e se a luz da rua deve ligar. 
  // quanto menor o valor, mais claridade permite. Precisará ficar mais escuro para acionar o led
  {
    digitalWrite(led_rua, HIGH);
  }
  if ((valorLum<600) && (StatusSensorLum == 1))   
  // Verifica se escureceu e se a luz da rua deve ligar. 
  // quanto menor o valor, mais claridade permite. Precisará ficar mais escuro para acionar o led
  {
    digitalWrite(led_rua, LOW);
  }
  //  else 
  //  {
  //    digitalWrite(led_rua, LOW);
  //  }
}

//------------------ Funções:

void ligarTudo()
{
  digitalWrite(led_sala, HIGH);
  digitalWrite(led_quarto, HIGH);
  digitalWrite(led_escritorio, HIGH);
  digitalWrite(led_cozinha, HIGH);
  digitalWrite(led_banheiro, HIGH);
  digitalWrite(led_garagem, HIGH);
  digitalWrite(led_rua, HIGH);
}
void desligarTudo()
{
  digitalWrite(led_sala, LOW);
  digitalWrite(led_quarto, LOW);
  digitalWrite(led_escritorio, LOW);
  digitalWrite(led_cozinha, LOW);
  digitalWrite(led_banheiro, LOW);
  digitalWrite(led_garagem, LOW);
  digitalWrite(led_rua, LOW);
}
void ligarAlarme()
{
  if (Serial.read() != 'a')   // Enquanto ninguém mandar parar, vai ficar tocando o alarme
  {
    pinMode(pinBuzzer, HIGH);     // Ativando pino da sirene
    desligarTudo();    // Garante que todas as luzes estão LOW para ficar em sincronia ao fazer a inversão ^1 abaixo
    timeElapsed = 0;   // Vai iniciar a contagem de 0 até interval (1 segundo) para o while abaixo

    while (timeElapsed < interval) {   // While que dura 1 segundo, para piscar os Leds enquanto toca a sirene
      digitalWrite(led_sala, digitalRead(led_sala) ^ 1);   // O ^1 inverte o estado dos Leds para ligar/desligar
      digitalWrite(led_quarto, digitalRead(led_quarto) ^ 1);
      digitalWrite(led_escritorio, digitalRead(led_escritorio) ^ 1);
      digitalWrite(led_cozinha, digitalRead(led_cozinha) ^ 1);
      digitalWrite(led_banheiro, digitalRead(led_banheiro) ^ 1);
      digitalWrite(led_garagem, digitalRead(led_garagem) ^ 1);
      digitalWrite(led_rua, digitalRead(led_rua) ^ 1);
      for (int x = 0; x < 180; x++) {   // Laço FOR para simular uma sirene
        float seno = (sin(x * 3.1416 / 180));
        int frequencia = 2000 + (int(seno * 1000));
        tone(pinBuzzer, frequencia);
        delay(2);
      }
    }
  }
  desligarAlarme();
}
void desligarAlarme() {
  desligarTudo();   // Desliga todas as luzes
  // Desliga o Buzzer:
  noTone(pinBuzzer);
  pinMode(pinBuzzer, LOW);
}
