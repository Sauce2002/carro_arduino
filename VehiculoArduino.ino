#include <Servo.h>

//infrarojo seguidor de linea
int L = 8;
int C = 11;
int R = 12;

int pelota=400;
int caja =500;
//servos
Servo servo1;
Servo servo2;

//sensor LDR 
int senLDR = A1;

//motores
int in1 = 6;
int in2 = 7;
int enA = 5;

int in3 = 2;
int in4 = 4;
int enB = 3;


void setup() {
  // put your setup code here, to run once:
  
  Serial.begin(9600);
  //servos
  servo1.attach(9);
  servo2.attach(10);

  //seguidor de linea
  pinMode(L,INPUT);
  pinMode(C,INPUT);
  pinMode(R,INPUT);

  //motores
  pinMode(in1,OUTPUT);
  pinMode(in2,OUTPUT);
  pinMode(in3,OUTPUT);
  pinMode(in4,OUTPUT);
  pinMode(enA,OUTPUT);
  pinMode(enB,OUTPUT);
  //LDR
  pinMode(senLDR,INPUT);

}

void loop() {
Serial.println(analogRead(senLDR));
servo2.write(0);
servo1.write(0);

//Serial.println(luz);
int lecturaIzq = digitalRead(L);
int lecturaCen = digitalRead(C);
int lecturaDer = digitalRead(R);

if((lecturaIzq == LOW && lecturaCen == HIGH && lecturaDer == HIGH)||(lecturaIzq == LOW && lecturaCen == LOW && lecturaDer == HIGH) ){
  Serial.println("ROTAR IZQUIERDA");
  rotarIzquierda(150);
  //avanzar(50,50,155);
  }
if(lecturaIzq == HIGH && lecturaCen == LOW && lecturaDer == HIGH){
  avanzar(100,155,155);
  Serial.println("AVANZAR");}
if((lecturaIzq == HIGH && lecturaCen == HIGH && lecturaDer == LOW)||(lecturaIzq == HIGH && lecturaCen == LOW && lecturaDer == LOW)) {
  rotarDerecha(150);
  //avanzar(50,155,50);
  Serial.println("ROTAR DERECHA");}



if(lecturaIzq == LOW && lecturaCen == LOW && lecturaDer == LOW) {
  frenar();
  delay(2000);
  int luz = analogRead(senLDR);
  if (luz > 700){
    servo1.write(90);
    delay(2000);
    servo1.write(0);
    rotarIzquierda(1500);
    avanzar(500,150,150);
    Serial.println("linea negra sin luz");
  }
  if(luz < 700){
  Serial.println(luz);

  if(luz < pelota){
    servo2.write(50);
    delay(2000);
    retroceder(50);
    rotarDerecha(1500);
    avanzar(500,130,130);
  }
  if (luz< caja && luz > pelota){
    servo1.write(90);
    delay(2000);
    servo1.write(0);
    retroceder(50);
    //rotarDerecha(1500);
    //avanzar(2000,130,130);
    delay(2000);

  }
  servo2.write(90);
  servo1.write(0);
  delay(2000);

  Serial.println("lINEA GRANDE con luz");}


}

if(lecturaIzq == HIGH && lecturaCen == HIGH && lecturaDer == HIGH) 
{
  Serial.println("blanco");
  //rotarDerecha(50);
  avanzar(150,150,150);}
else avanzar(50,50,50);


}
//digitalWrite(in1,HIGH); lado izq acelera 
//digitalWrite(in2,HIGH); lado izq reversa
//digitalWrite(in3,HIGH); lado der acelera
//digitalWrite(in4,HIGH); lado der reversa
void rotarDerecha(int tiempo){
  digitalWrite(in1,HIGH);
  digitalWrite(in2,LOW);
  digitalWrite(in3,LOW);
  digitalWrite(in4,HIGH);
  
  analogWrite(enA,120);
  analogWrite(enB,120);
  delay(tiempo);
  frenar();
}
void rotarIzquierda(int tiempo){
  digitalWrite(in1,LOW);
  digitalWrite(in2,HIGH);
  digitalWrite(in3,HIGH);
  digitalWrite(in4,LOW);

  analogWrite(enA,120);
  analogWrite(enB,120);
  delay(tiempo);
  frenar();
}

void frenar(){
  analogWrite(enA,0);
  analogWrite(enB,0);
}

void desacelerar(int t){
  for(int i= 130;i > 0; i-=10){
    analogWrite(enA,i);
    analogWrite(enB,i);
    delay(t);
  }
}

void avanzar(int tiempo,int izq, int der){
  digitalWrite(in1,HIGH);
  digitalWrite(in2,LOW);
  digitalWrite(in3,HIGH);
  digitalWrite(in4,LOW);
  analogWrite(enA,izq);
  analogWrite(enB,der);
  delay(tiempo);
}

void retroceder(int tiempo){

  digitalWrite(in1,LOW);
  digitalWrite(in2,HIGH);
  digitalWrite(in3,LOW);
  digitalWrite(in4,HIGH);
  analogWrite(enA,130);
  analogWrite(enB,130);
  delay(tiempo);

}


