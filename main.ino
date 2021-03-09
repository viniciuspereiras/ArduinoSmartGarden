/*
  Programado por Vinicius Pereira 

 Monitoramento de uma planta através de um sensor de umidade de solo.
 No modelo do tinkercad foi usado um potenciometro no lugar do sensor de umidade.
 Utiliza um ldr então segue abaixo as ligações dele:

 * LCD RS pin to digital pin 12
 * LCD Enable pin to digital pin 11
 * LCD D4 pin to digital pin 5
 * LCD D5 pin to digital pin 4
 * LCD D6 pin to digital pin 3
 * LCD D7 pin to digital pin 2
 * LCD R/W pin to ground
 * LCD VSS pin to ground
 * LCD VCC pin to 5V
 * 10K resistor:
 * ends to +5V and ground
 * wiper to LCD VO pin (pin 3)

 o sketch utiliza uma biblioteca do LCD.
 */

#include <LiquidCrystal.h>                                                //incuindo a biblioteca 
int valoran = 0;                                                          //declarando valor analógico para o sensor
int funcpisca = 1;                                                        //variavel para função conjunta 
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);                                    //configurando e setando portas digitais do lcd
void setup() {
  pinMode(7, OUTPUT);                                                     //led vermelho porta d7
  pinMode(8, OUTPUT);                                                     //led amarelo porta d8
  pinMode(9, OUTPUT);                                                     //led verde porta d9
  pinMode(6, OUTPUT);                                                     //led azul porta d6
  lcd.begin(16, 2);                                                       //setando numero de colunas e linhas
  lcd.print("Monitorando...");                                            //escrever no lcd
  pinMode(A0, INPUT);                                                     //declarando porta analógica do sensor
  Serial.begin(9600);                                                     //iniciando comunicação com a serial 
  delay(1000);                                                            //aguarda 1 segundo
  lcd.clear();                                                            //limpa a tela do lcd
}
void loop() {
 valoran = analogRead(A0);                                               //le o valor recebido na porta analógica
 valoran = map(valoran, 1023, 0, 99, 0);                                 //transforma o valor para 0 a 99               
 Serial.println(valoran);                                                //manda o vallor para a serial 
   if (valoran > 0) {                                                    //laço para leds
     if (valoran < 25) {
       digitalWrite(7, HIGH);                                            //comando de leds
       digitalWrite(8, LOW);
       digitalWrite(9, LOW);
       lcd.setCursor(4, 0);                                              //escrevendo letras "fantasmas" para resolver bug do "zero á esquerda"
       lcd.write(B00100000);
       lcd.setCursor(5, 0);
       lcd.write(B00100000);
       lcd.setCursor(10, 0);
       lcd.write(B00100000);
       lcd.setCursor(11, 0);
       lcd.write(B00100000);
       lcd.setCursor(6, 0);
       lcd.print("SECO");                                               //para valores menores de 25% acender led vermelho e escrever "seco" no lcd
     }
     if (valoran > 25 && valoran < 75) {
       digitalWrite(7, LOW);
       digitalWrite(8, HIGH);
       digitalWrite(9, LOW);
       digitalWrite(6, LOW);
       lcd.setCursor(4, 0);
       lcd.print("MODERADO");                                          //para valores entre 25 e 75 acender led amarelo e escrever "moderado" no lcd
     }
     if (valoran > 75) {
       digitalWrite(7, LOW);
       digitalWrite(8, LOW);
       digitalWrite(9, HIGH);
       digitalWrite(6, LOW);
       lcd.setCursor(4, 0);                                            //escrevendo letras "fantasmas" para resolver bug do "zero á esquerda"
       lcd.write(B00100000);
       lcd.setCursor(5, 0);
       lcd.write(B00100000);
       lcd.setCursor(11, 0);
       lcd.write(B00100000);
       lcd.setCursor(6, 0);
       lcd.print("UMIDO");                                            //para valores maiores de 75 acender led verde e escrever "umido" no lcd                                      
     }
   }
  lcd.setCursor(0, 1);                                                //escreve "Solo:" na 2° linha
  lcd.print("Solo:");
  if (valoran > 10); {
  lcd.setCursor(6, 2);
  lcd.print(valoran);                                                 //escreve o valor lido do sensor (0 a 99) 
  lcd.setCursor(8, 2);      
  lcd.print("%");                                                    //coloca o simbolo de porcentagem
  }
  if (valoran < 10){                                                 //resolvendo bug "0 a esquerda"
  lcd.setCursor(7, 2);
  lcd.write(B00100000);
  lcd.setCursor(6, 2);
  lcd.print(valoran);
  }
  if (funcpisca == 1){                                             //fazer o led azul piscar quando o solo estiver seco (-25)
    if (valoran < 25){
      digitalWrite(6, LOW);
      delay(500);
      digitalWrite(6, HIGH);
    }
  }

delay(250);                                                      
}
