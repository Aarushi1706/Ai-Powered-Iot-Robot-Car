#define DECODE_NEC   
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
