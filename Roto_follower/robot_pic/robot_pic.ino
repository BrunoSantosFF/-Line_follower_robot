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
float velocidadeBase = 75;

int ldr = A3;

int flag = 0;


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

  pinMode(ldr, INPUT);
}

void loop(){
  //Serial.println(analogRead(ldr));

 
  float sensor_ldr;
 
  int direita_ = digitalRead(sensor_direita);
  int centro_ = digitalRead(sensor_centro);
  int esquerda_ = digitalRead(sensor_esquerda);

  while (direita_ == 1 && centro_ == 1 && esquerda_ == 1){
    stop_car();
    
    
    sensor_ldr = analogRead(ldr);

    while (1){
      stop_car();
      sensor_ldr = analogRead(ldr);
      if (return_flag( sensor_ldr) == 1){
        delay(3000);
        break;
      }
    }
    
    if (flag == 1){
      delay(300);
      go_car(velocidadeA,  80, velocidadeB, 80 );
      delay(650);
      break;
    }
  }

  while (1){
    float direita = analogRead(sensor_direita);
    float centro = analogRead(sensor_centro);
    float esquerda = analogRead(sensor_esquerda);
  
    float erro = (direita - esquerda);
  
    float ajuste = erro * kp;
  
    float velocidadeEsquerda = velocidadeBase - ajuste;
    float velocidadeDireita = velocidadeBase + ajuste;

    direita_ = digitalRead(sensor_direita);
    centro_ = digitalRead(sensor_centro);
    esquerda_ = digitalRead(sensor_esquerda);

    
    go_car(velocidadeA,  velocidadeEsquerda, velocidadeB, velocidadeDireita );

    if (direita_ == 1 && centro_ == 1 && esquerda_ == 1){
      stop_car();
      flag = 0;
      break;
    }

    
  }
 

 delay(50);

}


int return_flag(float sensor_ldr){
 if (sensor_ldr > 700){
   flag = 1;
   return 1;
 }

 flag = 0;
 return 0;
}

void stop_car(){
  digitalWrite(IN1,LOW);
  digitalWrite(IN2,LOW);
  digitalWrite(IN3,LOW);
  digitalWrite(IN4,LOW);
}

void go_car (float velocidadeA, float velocidadeEsquerda, float velocidadeB, float velocidadeDireita ){
  digitalWrite(IN1,HIGH);
  digitalWrite(IN2,LOW);
  digitalWrite(IN3,LOW);
  digitalWrite(IN4,HIGH);
  analogWrite(velocidadeA,velocidadeEsquerda);
  analogWrite(velocidadeB,velocidadeDireita);
}
