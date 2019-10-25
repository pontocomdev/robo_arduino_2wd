#include <Ultrasonic.h>
#include <Servo.h>
#include "musical_notes.h"

#define pinoServo 7
#define Trig 2
#define Echo 3
#define B1A 8
#define B1B 9
#define A1A 10
#define A1B 11

int distanciaD;
int distanciaE;
int buzzerPin = 6;

float distanciaObstaculo = 35;

Ultrasonic ultrasonico(Trig, Echo);

Servo servo;

void setup() {
  Serial.begin(9600);
  
  servo.attach(pinoServo);
  //pinos da ponte H
  pinMode(B1A, OUTPUT);
  pinMode(B1B, OUTPUT);
  pinMode(A1A, OUTPUT);
  pinMode(A1B, OUTPUT);
  pinMode(buzzerPin, OUTPUT); 
  
  servo.write(90);
  //Radar();
}

void loop() {

  Serial.println(ultrasonico.Ranging(CM));
  
  if (ultrasonico.Ranging(CM) <= distanciaObstaculo) {
    Andar(5);
      int statuss = Radar();
      delay(500);
      if (statuss == 1) {
        Andar(2);
        delay(600);
        Andar(4);
        delay(400);
        Andar(5);
      }
      if (statuss == 2) {
        Andar(2);
        delay(600);
        Andar(3);
        delay(400);
        Andar(5);
      }
      if (statuss == 0) {
        Andar(2);
        delay(500);
        Andar(4);
        delay(300);
        Andar(5);
      }
      delay(1000);
    }
  else {
    Andar(1);
  }
}

void Andar(int direcao) {
  if (direcao == 1) { // anda pra frente
    digitalWrite(B1A, HIGH);
    digitalWrite(B1B, LOW);
    digitalWrite(A1A, HIGH);
    digitalWrite(A1B, LOW);
  }

  if (direcao == 2) { // anda pra trás
    digitalWrite(B1A, LOW);
    digitalWrite(B1B, HIGH);
    digitalWrite(A1A, LOW);
    digitalWrite(A1B, HIGH);
  }

  if (direcao == 3) { // faz curva pra direita
    digitalWrite(B1A, HIGH);
    digitalWrite(B1B, LOW);
    digitalWrite(A1A, LOW);
    digitalWrite(A1B, HIGH);
  }

  if (direcao == 4) { // faz curva pra esquerda
    digitalWrite(B1A, LOW);
    digitalWrite(B1B, HIGH);
    digitalWrite(A1A, HIGH);
    digitalWrite(A1B, LOW);
  }

  if (direcao == 5) { // FREIA
    digitalWrite(B1A, LOW);
    digitalWrite(B1B, LOW);
    digitalWrite(A1A, LOW);
    digitalWrite(A1B, LOW);
    r2D2();
  }
}

int Radar() {
  delay(1000);
  servo.write(175);
  delay(1000);
  distanciaD = ultrasonico.Ranging(CM);

  delay(1000);
  servo.write(10);
  delay(1000);
  distanciaE = ultrasonico.Ranging(CM);

  delay(1000);
  servo.write(90);

  if (distanciaD > distanciaE) {
    return 1; // se tiver espaço na direita
  }
  if (distanciaD < distanciaE) {
    return 2; //se tiver espaço na esquerda
  }
  if (distanciaD == distanciaE) {
    return 0;
  }
}

// Emite o Som
void beep (int speakerPin, float noteFrequency, long noteDuration)
{    
  int x;
  
  float microsecondsPerWave = 1000000/noteFrequency;
  float millisecondsPerCycle = 1000/(microsecondsPerWave * 2);
  float loopTime = noteDuration * millisecondsPerCycle;
  for (x=0;x<loopTime;x++)   
          {   
              digitalWrite(speakerPin,HIGH); 
              delayMicroseconds(microsecondsPerWave); 
              digitalWrite(speakerPin,LOW); 
              delayMicroseconds(microsecondsPerWave); 
          } 
}     

void r2D2(){
          beep(buzzerPin, note_A7,100); //A 
          beep(buzzerPin, note_G7,100); //G 
          beep(buzzerPin, note_E7,100); //E 
          beep(buzzerPin, note_C7,100); //C
          beep(buzzerPin, note_D7,100); //D 
          beep(buzzerPin, note_B7,100); //B 
          beep(buzzerPin, note_F7,100); //F 
          beep(buzzerPin, note_C8,100); //C 
          beep(buzzerPin, note_A7,100); //A 
          beep(buzzerPin, note_G7,100); //G 
          beep(buzzerPin, note_E7,100); //E 
          beep(buzzerPin, note_C7,100); //C
          beep(buzzerPin, note_D7,100); //D 
          beep(buzzerPin, note_B7,100); //B 
          beep(buzzerPin, note_F7,100); //F 
          beep(buzzerPin, note_C8,100); //C 
}
