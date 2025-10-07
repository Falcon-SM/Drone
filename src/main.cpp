#include <Arduino.h>
#include <ESP32Servo.h>

#define MIN_PULSE_WIDTH 1148
#define MAX_PULSE_WIDTH 1832

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
  esc.attach(escPin_A, MIN_PULSE_WIDTH, MAX_PULSE_WIDTH);
  esc.attach(escPin_B, MIN_PULSE_WIDTH, MAX_PULSE_WIDTH);
  esc.attach(escPin_C, MIN_PULSE_WIDTH, MAX_PULSE_WIDTH);
  esc.attach(escPin_D, MIN_PULSE_WIDTH, MAX_PULSE_WIDTH);
  Serial.println("Attached");

  //スピードアップしている信号を送る
  for(int i = 0; i < 10; i++){
    Serial.print("Throttle: ");
    Serial.println(throttle);
    esc.writeMicroseconds(throttle);
    throttle += 50;
    delay(100);
  }
  Serial.println("Throttle up done");
  delay(1000);

  //スロットルを0にする（最小ということでいいはず）
  esc.writeMicroseconds(MIN_PULSE_WIDTH);
  Serial.println("Throttle min");
  delay(1000);
  Serial.println("Calibrated");
  }

void loop() {
  // put your main code here, to run repeatedly:
  delay(100);
  esc.writeMicroseconds(throttleSerial);
  Serial.print("Throttle: ");
  Serial.println(throttleSerial);
  if(Serial.available() > 0){
    delay(20);
    byte data_size = Serial.available();
    byte buf[data_size];
    Serial.print("Data size:");
    Serial.println(data_size);

    for (byte i = 0; i < data_size; i++){
      buf[i] = Serial.read() - '0';
    }
    Serial.println();

    int dub = 1;
    throttleSerial = 0;
    for (byte i = 0; i < data_size; i++){
      throttleSerial += buf[data_size - 1 - i] * dub;
      dub *= 10;
    }
    Serial.print(throttleSerial);
  }
  throttleSerial = min(MAX_PULSE_WIDTH, throttleSerial);
  throttleSerial = max(MIN_PULSE_WIDTH, throttleSerial);

}