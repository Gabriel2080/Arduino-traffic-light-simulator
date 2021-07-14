const int X = 2000;
const int Y = 2000;
const int G_Total = 10000; //10s
const int semaferoPedestre = 10000;

const int VERMELHO_PEDESTRE_PRINCIPAL = 12;
const int VERDE_PEDESTRE_PRINCIPAL = 13;
const int VERMELHO_PEDESTRE_SEGUNDARIA = 10;
const int VERDE_PEDESTRE_SEGUNDARIA = 11;

const int VERMELHO_RUA_PRINCIPAL = 7;
const int AMARELHO_RUA_PRINCIPAL = 8;
const int VERDE_RUA_PRINCIPAL = 9;

const int VERDE_RUA_SEGUNDARIA = 6; //
const int AMARELHO_RUA_SEGUNDARIA = 5;
const int VERMELHO_RUA_SEGUNDARIA = 4;


float b,n;

float VERDE_SEMAFERO_PRINCIPAL;
float VERDE_SEMAFERO_SEGUNDARIO;

bool botao_apertado = false;
int esperabotao = 1;



void setup(){
  
  Serial.begin(9600);
  
  pinMode(A0, INPUT);
  
  pinMode(VERDE_RUA_SEGUNDARIA, OUTPUT);
  pinMode(AMARELHO_RUA_SEGUNDARIA, OUTPUT);
  pinMode(VERMELHO_RUA_SEGUNDARIA, OUTPUT);
  
  pinMode(VERMELHO_RUA_PRINCIPAL, OUTPUT);
  pinMode(AMARELHO_RUA_PRINCIPAL, OUTPUT);
  pinMode(VERDE_RUA_PRINCIPAL, OUTPUT);
  
  attachInterrupt(0, parar, RISING);
  attachInterrupt(1, parar, RISING);
  
  pinMode(VERDE_PEDESTRE_PRINCIPAL, OUTPUT);
  pinMode(VERMELHO_PEDESTRE_PRINCIPAL, OUTPUT);
  
  pinMode(VERDE_PEDESTRE_SEGUNDARIA, OUTPUT);
  pinMode(VERMELHO_PEDESTRE_SEGUNDARIA, OUTPUT);
}

void loop(){
  int potencia = analogRead(A0);
  Serial.println(potencia);
  
  if(potencia < 342){
    b = map( potencia, 0, 341, 200, 500);
  	n = b/1000;
  }else{
    b = map( potencia, 342, 1023, 500, 667);
  	n = b/1000;
  }
  
  Serial.println(n);
  
  VERDE_SEMAFERO_PRINCIPAL = G_Total*n;
  VERDE_SEMAFERO_SEGUNDARIO = G_Total - VERDE_SEMAFERO_PRINCIPAL;
  
  Serial.println(VERDE_SEMAFERO_PRINCIPAL); 
  Serial.println(VERDE_SEMAFERO_SEGUNDARIO);
  
  digitalWrite(VERMELHO_PEDESTRE_PRINCIPAL,HIGH);
  digitalWrite(VERMELHO_PEDESTRE_SEGUNDARIA,HIGH); 
  
  digitalWrite(VERDE_RUA_PRINCIPAL, HIGH);
  digitalWrite(VERMELHO_RUA_SEGUNDARIA, HIGH);
  delay(VERDE_SEMAFERO_PRINCIPAL);
  digitalWrite(VERDE_RUA_PRINCIPAL, LOW);
  digitalWrite(AMARELHO_RUA_PRINCIPAL, HIGH);
  delay(Y);
  digitalWrite(AMARELHO_RUA_PRINCIPAL, LOW);
  digitalWrite(VERMELHO_RUA_PRINCIPAL, HIGH);
  delay(X);
  
  digitalWrite(VERMELHO_RUA_SEGUNDARIA, LOW);
  digitalWrite(VERDE_RUA_SEGUNDARIA, HIGH);
  delay(VERDE_SEMAFERO_SEGUNDARIO);
  digitalWrite(VERDE_RUA_SEGUNDARIA, LOW);
  digitalWrite(AMARELHO_RUA_SEGUNDARIA, HIGH);
  delay(Y);
  digitalWrite(AMARELHO_RUA_SEGUNDARIA, LOW);
  digitalWrite(VERMELHO_RUA_SEGUNDARIA, HIGH);
  delay(X);
  
  if (botao_apertado == true & esperabotao >=2){
    digitalWrite(VERMELHO_PEDESTRE_PRINCIPAL,LOW);
    digitalWrite(VERMELHO_PEDESTRE_SEGUNDARIA,LOW);
    digitalWrite(VERDE_PEDESTRE_PRINCIPAL,HIGH);
    digitalWrite(VERDE_PEDESTRE_SEGUNDARIA,HIGH);
    delay(semaferoPedestre*0.6);
    digitalWrite(VERDE_PEDESTRE_PRINCIPAL,LOW);
    digitalWrite(VERDE_PEDESTRE_SEGUNDARIA,LOW);
    for (int i = 0; i <= ((semaferoPedestre*0.4)/1000); i++) {
      digitalWrite(VERDE_PEDESTRE_PRINCIPAL,HIGH);
      digitalWrite(VERDE_PEDESTRE_SEGUNDARIA,HIGH);
      delay(500);
      digitalWrite(VERDE_PEDESTRE_PRINCIPAL,LOW);
      digitalWrite(VERDE_PEDESTRE_SEGUNDARIA,LOW);
      delay(500);
    }
    digitalWrite(VERMELHO_PEDESTRE_PRINCIPAL,HIGH);
    digitalWrite(VERMELHO_PEDESTRE_SEGUNDARIA,HIGH);
    delay(5000);
    
    esperabotao = 0;
    botao_apertado = false;
  }
  
  digitalWrite(VERMELHO_RUA_PRINCIPAL, LOW);
  
  esperabotao++;
  
}

void parar()
{
  Serial.println("botao apertado");
  botao_apertado = true;
}