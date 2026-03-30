#define trigPin 7
#define echoPin 4

void setup() {
  // put your setup code here, to run once:
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  Serial.print("Distance: ");
  Serial.println(readDistance());
  delay(100);
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
