/*Pinagem do arduino*/

//motor_A
int IN1 = 5 ;
int IN2 = 4 ;
int velocidadeA = 9;

//motor_B
int IN3 = 3 ;
int IN4 = 2 ;
int velocidadeB = 10;

//variavel auxiliar
int velocidade = 0;

int sensor_direita = A0;
int sensor_centro = A1;
int sensor_esquerda = A2;

float kp = 0.05;
float velocidadeBase = 73;

//Inicializa Pinos
void setup(){
pinMode(IN1,OUTPUT);
pinMode(IN2,OUTPUT);
pinMode(IN3,OUTPUT);
pinMode(IN4,OUTPUT);
pinMode(velocidadeA,OUTPUT);
pinMode(velocidadeB,OUTPUT);

pinMode(sensor_direita, INPUT); 
  pinMode(sensor_centro, INPUT); 
  pinMode(sensor_esquerda, INPUT);
}

void loop(){


  Serial.print(analogRead(sensor_direita));
  Serial.print(" - ");
  Serial.print(analogRead(sensor_centro));
  Serial.print(" - ");
  Serial.println(analogRead(sensor_esquerda));

  float direita = analogRead(sensor_direita);
  float centro = analogRead(sensor_centro);
  float esquerda = analogRead(sensor_esquerda);

  float erro = (direita - esquerda);

  float ajuste = erro * kp;

  float velocidadeEsquerda = velocidadeBase - ajuste;
  float velocidadeDireita = velocidadeBase + ajuste;

  analogWrite(velocidadeA,velocidadeEsquerda);
    analogWrite(velocidadeB,velocidadeDireita);

  Serial.print("Ajuste: ");
  Serial.println(ajuste);

  Serial.print("Esquerda: ");
  Serial.print(velocidadeEsquerda);
  Serial.print(" -- Direita: ");
  Serial.println(velocidadeDireita);

  int direita_ = digitalRead(sensor_direita);
  int centro_ = digitalRead(sensor_centro);
  int esquerda_ = digitalRead(sensor_esquerda);

  if (direita_ == 0 && centro_ == 0 && esquerda_ == 0 || direita_ == 1 && centro_ == 1 && esquerda_ == 1 ){
    
    digitalWrite(IN1,LOW);
    digitalWrite(IN2,LOW);
    digitalWrite(IN3,LOW);
    digitalWrite(IN4,LOW);
  }
  else {
    test();
    analogWrite(velocidadeA,velocidadeEsquerda);
    analogWrite(velocidadeB,velocidadeDireita);
  }

  delay(80);




}

void test (){
  digitalWrite(IN1,HIGH);
  digitalWrite(IN2,LOW);
  digitalWrite(IN3,LOW);
  digitalWrite(IN4,HIGH);
}
