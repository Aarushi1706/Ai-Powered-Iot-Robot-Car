void setup() {
  // put your setup code here, to run once:
  pinMode(8, INPUT);
  pinMode(10, INPUT);
  Serial.begin(9600);

}

void loop() {
  // put your main code here, to run repeatedly:
  bool leftSensor = digitalRead(8);
  bool rightSensor = digitalRead(10);

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
  delay(100);
}
