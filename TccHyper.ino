//Variaveis da portas de saida
  //declarando os buzzers
    #define buzzerB 7
    #define buzzerA 8

  //declarando o led de modo
    #define ledR1 11
    #define ledG1 10
    #define ledB1 9

  //declarando o led de status
    #define ledR2 6
    #define ledG2 5
    #define ledB2 3
//----------------------------------------------------

//Variavel para receber infos do bluetooth
  char valApp;
//----------------------------------------------------

//Varaiaveis para ajudar no funcionamento
  int qualBuzzer = true;
  int modoFoco = false;
  int modoPomo = false;
//----------------------------------------------------

//Funcao para Ligar os leds rgb
  void ledRGB(int led, int R, int G, int B) {
    if(led == 1){
      analogWrite(ledR1, R);
      analogWrite(ledG1, G);
      analogWrite(ledB1, B);
    } else if(led == 2) {
      analogWrite(ledR2, R);
      analogWrite(ledG2, G);
      analogWrite(ledB2, B);
    }
  }
//----------------------------------------------------

//Funcao para apitar o buzzer
  void buzzerApito(int buzzer) {
    tone(buzzer, 500, 250);
    delay(1000);
  }
//----------------------------------------------------

//Declaradno as portas usadas como saida/entrada e Iniciando o monitor serial
  void setup() {
    //declarando todoas as portas de saida
    pinMode(buzzerB, OUTPUT);
    pinMode(buzzerA, OUTPUT);
    
    pinMode(ledR1, OUTPUT);
    pinMode(ledG1, OUTPUT);
    pinMode(ledB1, OUTPUT);

    pinMode(ledR2, OUTPUT);
    pinMode(ledG2, OUTPUT);
    pinMode(ledB2, OUTPUT);
    
    //Iniciando o monitor serial
    Serial.begin(9600);
  }
//----------------------------------------------------

void loop() {
  /*Valores recebidos

    - Qual buzzer
    'A' = Buzzer alto
    'a' = Buzzer baixo

    - Modo Foco
    'O' = Ligar modo Foco
    'o' = Desligar modo Foco
    
    - Modo Pomo
    'T' = Ligar modo Pomo
    't' = Desligar modo Pomo
  */

  //Lingando o led de status
    ledRGB(1, 20, 150, 50);
  //--------------------------------------------------

  //Receber e imprimir o valor vindo do bluetooth
    valApp = Serial.read();
    Serial.println(valApp);
  //--------------------------------------------------

  //If's com as infos do bluetooth
    //Qual Buzzer
      if(valApp == 'A') {
        qualBuzzer = true;
        Serial.println("Buzer Alto");
      } else if(valApp == 'a') {
        qualBuzzer = false;
        Serial.println("Buzer Baixo");
      } 
    //------------------------------------------------
    //Modo Foco
      else if (valApp == 'O') {
        modoFoco = true;
        Serial.println("Modo Foco ligado");
      } else if (valApp == 'o') {
        modoFoco = false;
        Serial.println("Modo Foco desligado");
      }
    //------------------------------------------------
    //Modo Pomo
      else if (valApp == 'T') {
        modoPomo = true;
        Serial.println("Modo Pomo ligado");
      } else if (valApp == 't') {
        modoPomo = false;
        Serial.println("Modo Pomo desligado");
      }   
  //--------------------------------------------------
  
  //Modo Foco
    if (modoFoco) {
      if(qualBuzzer) {
        Serial.println("Modo Foco ligado com buzzer alto");
        for(int y = true; y; y) {
          buzzerApito(buzzerA);

          valApp = Serial.read();
          Serial.println(valApp);

          if (valApp == 'o') {
            modoFoco = false;
            y = false;
            Serial.println("Modo Foco desligado");
          }
        }
      } else {
        Serial.println("Modo Foco ligado com buzzer baixo");
        for(int x = true; x; x) {
          buzzerApito(buzzerB);

          valApp = Serial.read();
          Serial.println(valApp);

          if (valApp == 'o') {
            modoFoco = false;
            x = false;
            Serial.println("Modo Foco desligado");
          }
        }
      }
    }
  //Fim Modo Foco
  
  //Modo Pomodoro
    if (modoPomo) {
      if(qualBuzzer) {
        Serial.println("Modo Foco ligado com buzzer alto");
        for(int v = true; v; v) {
          buzzerApito(buzzerA);

          valApp = Serial.read();
          Serial.println(valApp);

          if (valApp == 't') {
            modoPomo = false;
            v = false;
            Serial.println("Modo Pomo desligado");
          }
        }
      } else {
        Serial.println("Modo Foco ligado com buzzer baixo");
        for(int z = true; z; z) {
          buzzerApito(buzzerA);

          valApp = Serial.read();
          Serial.println(valApp);

          if (valApp == 't') {
            modoPomo = false;
            z = false;
            Serial.println("Modo Pomo desligado");
          }
        }
      }
    }
  //Fim Modo Pomodoro

  delay(500);
}
