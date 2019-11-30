
## O trabalho passou por 8 principais versões/funcionalidades, sendo validadas conforme descrito a seguir.

### v1 - Acionamento das luzes LED:

Foram utilizados 7 super leds, representando diferentes ambientes da casa: rua (2x), banheiro, garagem, escritório, cozinha e quarto.

### v2 - Acionamento do alarme (sensor buzzer)

O sensor de som foi testado e colocado dentro de um 'laço' de programação com uma biblioteca própria, de maneira que fosse emitido um som característico de sirene (como uma ambulância), visando chamar atenção. Enquanto o alarme estiver tocando, os Leds da casa piscarão a cada 1 segundo, para potencializar o aviso.

### v3 - Sensor de presença

Com o som funcionando, foi instalado e testado o sensor de presença. Na detecção de qualquer tipo de movimento diante do sensor, o alarme é disparado.

### v4 - Sensor de luminosidade

Sensor que realiza a função de ligar as luzes da rua no momento em que ele detecta a perda de luminosidade externa. Obs: o usuário poderá ativar ou desativar essa função.
Durante as aulas, foi testado o sensor e capturado o melhor valor de luminosidade ambiente, para então ser setado na programação. Isso evita que o sensor forneça alarme falso durante as apresentações. 

### v5 - Acionamento do mini ventilador

Foi testado a função de ligar/desligar de um mini ventilador, para tornar mais dinâmca e diversificada a apresentação.

### v6 - Comandos de Infra vermelho

Para simular os comandos de Infra vermelho, que poderiam ser utilizados em televisões, ar condicionados, janelas, etc, utilizaremos na apresentação uma simples Fita Led, que terá suas cores trocadas por Infra vermelho, apenas para simular a funcionalidade de maneira mais prática.

### v7 - Ligar/desligar uma lâmpada real (Radio frequência)

Com o objetivo de apresentar o projeto de maneira mais próxima da realidade, será executado comandos de voz para ligar e desligar uma lâmpada real, à distância. Essa comunicação entre o arduino principal (da maquete) e o arduino remoto (da lâmpada) ocorrerá entre sensores Nrf24l01, por Radio frequência. Essa ação também comprovará que não há obrigatoriedade do uso de Wifi ou internet entre os equipamentos.

### v8 - Controle das janelas

Será utilizado um motor de passo para realizar a abertura e fechamento das janelas da maquete, mostrando que é possível todos os componentes trabalharem simultâneamente de maneira organizada.

Ou seja, cada sensor era testado e programado individualmente em um ambiente de laboratório: com um protoboard pequeno + arduino uno. 
Após o sensor ser testado e homologado, ele e seu respectivo código era então levado ao ambiente do projeto final: composto por um protoboard grande + arduino mega.
