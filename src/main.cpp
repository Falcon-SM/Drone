#include <Arduino.h>
#include <ESP32Servo.h>

#define MIN_PULSE_WIDTH 1148
#define MAX_PULSE_WIDTH 1832
#define PWM_FREQUENCY 50

// put function declarations here:
Servo esc; 

//モーターのピンの設定
const int escPin_A = 5;
const int escPin_B = 12;
const int escPin_C = 13;
const int escPin_D = 4;

int throttle = MIN_PULSE_WIDTH;
int throttleSerial = MIN_PULSE_WIDTH;

void setup() {
  Serial.begin(115200);
  Serial.println("プロペラを外していることを確認してください。確認できたら、シリアルモニタから何かを送信してください。");

  //何か受信するまで待機
  while(!(Serial.available()));
  Serial.println("Starting ESP32 ESC Calibration...");

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

  //Hzの設定
  esc.setPeriodHertz(PWM_FREQUENCY);
  esc.attach(escPin_A, MIN_PULSE_WIDTH, MAX_PULSE_WIDTH);
  //esc.attach(escPin_B, MIN_PULSE_WIDTH, MAX_PULSE_WIDTH);
  //esc.attach(escPin_C, MIN_PULSE_WIDTH, MAX_PULSE_WIDTH);
  //esc.attach(escPin_D, MIN_PULSE_WIDTH, MAX_PULSE_WIDTH);
  Serial.println("Attached");

  esc.writeMicroseconds(MAX_PULSE_WIDTH);
  Serial.println("Throttle max");
  Serial.println("ESCの電源を入れてください。");

  delay(500);

  Serial.println("Sending Minimum throttle...");
  esc.writeMicroseconds(MIN_PULSE_WIDTH);
  
  delay(3000);
  Serial.println("Calibrated");
  }

void loop() {
  if(Serial.available() > 0){
    int newThrottle = Serial.parseInt();
    if (newThrottle <= MAX_PULSE_WIDTH && newThrottle >= MIN_PULSE_WIDTH){
      throttle = newThrottle;
      Serial.print("Throttle: ");
      Serial.println(throttle);
    }else{
      Serial.println("Invalid throttle value. Must be 1148-1832");
    }
  }
  esc.writeMicroseconds(throttle);

  delay(10);
}