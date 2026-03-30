#define DECODE_NEC   
#define trigPin 7
#define echoPin 4

#include <IRremote.hpp>

int globalSpeed = 255;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  IrReceiver.begin(11, true);
  // Connected to motor A
  pinMode(3, OUTPUT);
  pinMode(5, OUTPUT);
  // Connected to motor B
  pinMode(6, OUTPUT);
  pinMode(9, OUTPUT);
  // Ultrasonic sensor pins
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  // IR proximity sensor pins
  pinMode(8, INPUT);
  pinMode(10, INPUT);

  stop();
}

void loop() {
  // put your main code here, to run repeatedly:
  if (IrReceiver.decode()) { // If the IR receiver is receiving data, then continue
    IrReceiver.resume();
    //IrReceiver.printIRResultShort(&Serial);
    switch(IrReceiver.decodedIRData.command) {
      case 0x18:
        forwards(globalSpeed);
      break;
      case 0x1C:
        stop();
      break;
      case 0x52:
        backwards(globalSpeed);
      break;
      case 0x8:
        left(globalSpeed);
      break;
      case 0x5A:
        right(globalSpeed);
      break;
      case 0x15: // Minus
      globalSpeed = globalSpeed - 10;

      if (globalSpeed < 0) 
        globalSpeed = 0;

      Serial.println(globalSpeed);
      break;
      case 0x9: // Plus
      globalSpeed = globalSpeed + 1;

      if (globalSpeed > 255)
        globalSpeed = 255;
      
      Serial.println(globalSpeed);
      break;
    }
  }
  // Read ultrasonic sensor
  float distance;
  readUltrasonicSensor(distance);
  // Read IR proximity sensor
  bool leftSensor, rightSensor;
  readIRPRoximitySensor(leftSensor, rightSensor);

  if(!leftSensor) {
    right(globalSpeed);
    delay(500);
    forwards(globalSpeed);
  }

  if(!rightSensor) {
    left(globalSpeed);
    delay(500);
    forwards(globalSpeed);
  }

  if(distance < 8) {
    stop();
  }
  
  delay(100);

}


void backwards(int speed) {
  Serial.println("Moving backwards");
  // Motor A
  analogWrite(3, speed);
  digitalWrite(5, LOW);

  // Motor B
  analogWrite(6, speed);
  digitalWrite(9, LOW);
}

void forwards(int speed) {
  Serial.println("Moving forwards");
  // Motor A
  digitalWrite(3, LOW);
  analogWrite(5, speed);

  // Motor B
  digitalWrite(6, LOW);
  analogWrite(9, speed);
}

void left(int speed) {
  Serial.println("Turning left");
  // Motor A
  digitalWrite(3, LOW);
  analogWrite(5, speed);

  // Motor B
  analogWrite(6, speed);
  digitalWrite(9, LOW);
}

void right(int speed) {
  Serial.println("Turning right");
  // Motor A
  analogWrite(3, speed);
  digitalWrite(5, LOW);

  // Motor B
  digitalWrite(6, LOW);
  analogWrite(9, speed);
}

void stop() {
  Serial.println("Stopping");
  // Motor A
  digitalWrite(3, LOW);
  digitalWrite(5, LOW);

  // Motor B
  digitalWrite(6, LOW);
  digitalWrite(9, LOW);
}

float readDistance(){
  float duration, distance;
  // Send out a pulse from the ultrasonic sensor
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  // Receiving the pulse, converting to cm
  duration = pulseIn(echoPin, HIGH);
  distance = ((duration * 0.0343) / 2);

  return distance;
}

void readUltrasonicSensor(float &distance) {
  distance = readDistance();
  Serial.print("Distance: ");
  Serial.println(distance);
}

void readIRPRoximitySensor(bool &leftSensor, bool &rightSensor) {
  leftSensor = digitalRead(8);
  rightSensor = digitalRead(10);
  Serial.print("Left sensor reading: ");
  if(leftSensor == false) {
    Serial.println("OBSTACLE");
  } else {
    Serial.println("NO OBSTACLE");
  }
  Serial.print("Right sensor reading: ");
  if(rightSensor == false) {
    Serial.println("OBSTACLE");
  } else {
    Serial.println("NO OBSTACLE");
  }
}
