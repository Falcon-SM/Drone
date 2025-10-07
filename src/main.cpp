#include <Arduino.h>
#include <ESP32Servo.h>

// put function declarations here:
Servo esc;

//モーターのピンの設定
const int escPin_A = 5;
const int escPin_B = 12;
const int escPin_C = 13;
const int escPin_D = 4;

int myFunction(int, int);

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  while(!(Serial.available() && Serial.read() == 'G'));
  Serial.println("Start");

  //pinModeの設定
  pinMode(escPin_A, OUTPUT);
  pinMode(escPin_B, OUTPUT);
  pinMode(escPin_C, OUTPUT);
  pinMode(escPin_D, OUTPUT);

  //まずはLOWを入力
  digitalWrite(escPin_A, LOW);
  digitalWrite(escPin_B, LOW);
  digitalWrite(escPin_C, LOW);
  digitalWrite(escPin_D, LOW);

//500ms待機
  delay(500);

  //Hzの設定
  esc.setPeriodHertz(50);
  esc.attach(escPin_A, 1148, 1832);
  esc.attach(escPin_B, 1148, 1832);
  esc.attach(escPin_C, 1148, 1832);
  esc.attach(escPin_D, 1148, 1832);

  esc.writeMicroseconds(1832);
  Serial.println("Full throttle");
  delay(1000);
  esc.writeMicroseconds(1148);
  Serial.println("Stop");
  delay(1000);
  Serial.println("Calibrated");
}

void loop() {
  // put your main code here, to run repeatedly:
}