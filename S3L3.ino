void setup() {
  // put your setup code here, to run once:
  // Connected to motor A
  pinMode(3, OUTPUT);
  pinMode(5, OUTPUT);

  // Connected to motor B
  pinMode(6, OUTPUT);
  pinMode(9, OUTPUT);

  Serial.begin(9600);

}

void loop() {
  // put your main code here, to run repeatedly:
  for(int i = 130; i < 255; i++){
    Serial.print("Speed: ");
    Serial.println(i);
    forwards(i);
    delay(100);
  }
  stop();
  delay(3000);
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
