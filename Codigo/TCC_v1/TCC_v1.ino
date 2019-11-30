
//pendencias: investigar pq sensor presenca nao ta funcionando.
//o jarvis ativa, mas nao consegue desativar, por exemplo

/*
  Projeto de TCC - Bruno Niffa
  Automação Residencial
  Arduino: Mega 2560 !
*/

#include <SoftwareSerial.h>
#include <elapsedMillis.h>   // Lib para piscar Leds a cada 1 segundo durante Sirene

SoftwareSerial SerialBluetooth(10, 11); // Conectar pino10 e pino11 nas saídas TX e RX do módulo HC-06, respectivamente!
elapsedMillis timeElapsed;

// Definindo Leds dos cômodos da casa:
int led_sala = 9;
int led_quarto = 8;
int led_escritorio = 7;
int led_cozinha = 5;
int led_banheiro = 4;
int led_garagem = 3;
int led_rua = 2;
int pinBuzzer = 23;
int pinSensorPIR = 14;
int valorSensorPIR = 0;
int sensorAlarme = 0;   // 0 - Alarme desativado, 1 - Alarme ativado
unsigned int interval = 1000;   // 1 segundo

void setup()
{
  Serial.begin(9600);
  SerialBluetooth.begin(9600);  // Módulo HC-06 trabalha em 9600

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

  // Garantir que todos os Leds começarão desligados:
  digitalWrite(led_sala, LOW);
  digitalWrite(led_quarto, LOW);
  digitalWrite(led_escritorio, LOW);
  digitalWrite(led_cozinha, LOW);
  digitalWrite(led_banheiro, LOW);
  digitalWrite(led_garagem, LOW);
  digitalWrite(led_rua, LOW);

  desligarAlarme(); // Inicializar com Alarme off
}

void loop()
{
  valorSensorPIR = digitalRead(pinSensorPIR);
  Serial.println(valorSensorPIR);

  char comando;
  if (SerialBluetooth.available() > 0) // Serial utilizada pelo Bluetooth
  {
    comando = SerialBluetooth.read();  // Recebe comando do Bluetooth
  }
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
  if (comando == 'R')
  {
    digitalWrite(led_garagem, HIGH);
  }
  if (comando == 'r')
  {
    digitalWrite(led_garagem, LOW);
  }
  if (comando == 'T')
  {
    ligarTudo();
  }
  if (comando == 't')
  {
    desligarTudo();
  }

  // Ações sobre os alarmes:

  if (comando == 'H')
  {
    sensorAlarme = 1;   // Vai ativar a detecção de movimentos
  }
  if (comando == 'h')
  {
    sensorAlarme = 0;   // Vai desativar a detecção de movimentos
  }
  if (comando == 'A')
  {
    ligarAlarme();      // Liga manualmente o Alarme
  }
  else if (comando == 'a')
  {
    desligarAlarme();   // Desliga manualmente o Alarme
  }

  if (valorSensorPIR == 1 && sensorAlarme == 1)   // Verifica se ocorreu movimentos e se o alarme deve tocar
  {
    ligarAlarme();
  }
  else
  {
    desligarAlarme();
  }

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
  while ((Serial.read() != 'a') || (SerialBluetooth.read() != 'a'))   // Enquanto ninguém mandar parar, vai ficar tocando o alarme
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
