#include <HCSR04.h>
#include <Servo.h>

const int TRIG_PIN = 10;
const int ECHO_PIN = 11;

const int TRIG2 = 6;
const int ECHO2 = 7;

const int Red = 2;
const int Yellow = 3;
const int Green = 4;

const int SERVO = 12;
UltraSonicDistanceSensor distanceSensor(TRIG_PIN, ECHO_PIN);
UltraSonicDistanceSensor distanceSensor2(TRIG2, ECHO2);

double sensor1;
double sensor2;

Servo myServo;




void setup() {
  pinMode(TRIG_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT);
  pinMode(TRIG2, OUTPUT);
  pinMode(ECHO2, INPUT);
  pinMode(Red, OUTPUT);
  pinMode(Yellow, OUTPUT);
  pinMode(Green, OUTPUT);

  myServo.attach(SERVO);

  Serial.begin(9600);
}

void loop() {
  sensor1 = distanceSensor.measureDistanceCm();
  digitalWrite(TRIG_PIN, LOW);
  delayMicroseconds(2);
  digitalWrite(TRIG_PIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG_PIN, LOW);
  double duration1 = pulseIn(ECHO_PIN, HIGH);
  sensor1 = duration1 * 0.034 / 2;
  
  delay(500);

 //sensor 1 - entrance
  if (sensor1 < 14)
  {
      myServo.write(-90);
      delay(10000);
  }
  else if (sensor1 > 14)
  {
      myServo.write(90);
  }


  sensor2 = distanceSensor2.measureDistanceCm();
  digitalWrite(TRIG2, LOW);
  delayMicroseconds(2);
  digitalWrite(TRIG2, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG2, LOW);
  double duration2 = pulseIn(ECHO2, HIGH);
  sensor2 = duration2 * 0.034 / 2;
  Serial.print(sensor1);
  Serial.print("\n");
  Serial.print(sensor2);
  Serial.print("\n");

  
  delay(500);

   //sensor 2 - exit
  if (sensor2 < 7)
  {
    digitalWrite(Red, HIGH);
    digitalWrite(Yellow, LOW);
    digitalWrite(Green, LOW);
  }
  else if(sensor2 > 7 && sensor2 < 14)
  {
    digitalWrite(Yellow, HIGH);
    digitalWrite(Red, LOW);
    digitalWrite(Green, LOW);
  }
  else if(sensor2 > 14 && sensor2 < 25)
  {
    digitalWrite(Green, HIGH);
    digitalWrite(Yellow, LOW);
    digitalWrite(Red, LOW);
  }
  else if(sensor2 > 25)
  {
    digitalWrite(Green, LOW);
    digitalWrite(Yellow, LOW);
    digitalWrite(Red, LOW);
  }

}
