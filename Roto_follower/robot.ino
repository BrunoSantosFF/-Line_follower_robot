
//declaracao dos pinos utilizados para controlar a velocidade de rotacao
const int PINO_ENA = 6; 
const int PINO_ENB = 5;

//declaracao dos pinos utilizados para controlar o sentido do motor
const int PINO_IN1 = 4; 
const int PINO_IN2 = 3;
const int PINO_IN3 = 8;
const int PINO_IN4 = 7;

//sensores infravermelhos
int sensor_direita = 9;
int sensor_centro = 10;
int sensor_esquerda = 11;

float erro = 0;
int setPoint = 2;
float current_value = 0;
float P = 0,Kp = 20,output_1 = 0,output_2 = 0;


void setup() {
  Serial.begin(9600);
  
  //configuração dos pinos como saida
  pinMode(PINO_ENA, OUTPUT); 
  pinMode(PINO_ENB, OUTPUT);
  pinMode(PINO_IN1, OUTPUT);
  pinMode(PINO_IN2, OUTPUT);
  pinMode(PINO_IN3, OUTPUT);
  pinMode(PINO_IN4, OUTPUT);

  //sensores
  pinMode(sensor_direita, INPUT); //Pino ligado ao coletor do infravermelho direita
  pinMode(sensor_centro, INPUT); //Pino ligado ao coletor do infravermelho centro
  pinMode(sensor_esquerda, INPUT); //Pino ligado ao coletor do infravermelho esquerda

  //inicia o codigo com os motores parados
  digitalWrite(PINO_IN1, LOW); 
  digitalWrite(PINO_IN2, LOW);
  digitalWrite(PINO_IN3, LOW);
  digitalWrite(PINO_IN4, LOW);
  digitalWrite(PINO_ENA, LOW);
  digitalWrite(PINO_ENB, LOW);

  /*
  
  const int ldr = A0;
  pinMode(ldr, INPUT); 
  int analogValue = analogRead(ldr);
  Serial.println(analogValue);  
  delay(300); 
  */

}

void loop() {
  
  //valores lidos dos sensores
  int sr = digitalRead(sensor_direita);
  int sc = digitalRead(sensor_centro);
  int sl = digitalRead(sensor_esquerda);

  Serial.print(sr);
  Serial.print(sc);
  Serial.println(sl);
  
  if ((sr + sc + sl) != 0){
    current_value = (3*sr + 2*sc + 1*sl)/(sr+sc+sl);
  }

  erro = setPoint - current_value;
  
  P = erro * Kp;
  
  output_1 =  100 + P;
  output_2 =  100 - P;

  if (sc == 0 && sl == 0 && sr == 0){
      stop_car();
  }
  else {
    if (erro == 0){ //andar para frente
      go_ahead_car(output_1,output_2);
    }
    else if (erro < 0){
      turn_left(output_1,output_2);
    }
    else if (erro > 0){
      turn_right(output_1,output_2);
    }
  }
  
  delay(200);

}

void turn_left(int a, int b){
  
  digitalWrite(PINO_IN1, HIGH);
  digitalWrite(PINO_IN2, LOW);
  digitalWrite(PINO_IN3, LOW);
  digitalWrite(PINO_IN4, HIGH);

  analogWrite(PINO_ENA, a);
  analogWrite(PINO_ENB, b);
}

void go_ahead_car(int a, int b){
  
  digitalWrite(PINO_IN1, HIGH);
  digitalWrite(PINO_IN2, LOW);
  digitalWrite(PINO_IN3, HIGH);
  digitalWrite(PINO_IN4, LOW);

  analogWrite(PINO_ENA, a);
  analogWrite(PINO_ENB, b);
}

void turn_right(int a, int b){

  digitalWrite(PINO_IN1, LOW);
  digitalWrite(PINO_IN2, HIGH);
  digitalWrite(PINO_IN3, HIGH);
  digitalWrite(PINO_IN4, LOW);

  analogWrite(PINO_ENA, a);
  analogWrite(PINO_ENB, b);
}

void stop_car(){
  
  digitalWrite(PINO_IN1, LOW);
  digitalWrite(PINO_IN2, LOW);
  digitalWrite(PINO_IN3, LOW);
  digitalWrite(PINO_IN4, LOW);
  
}
