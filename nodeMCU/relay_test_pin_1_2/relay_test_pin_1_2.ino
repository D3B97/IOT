void setup() {
  // put your setup code here, to run once:
 pinMode(0, OUTPUT);
 pinMode(2, OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly
  digitalWrite(0, HIGH);
  delay(2200);
  digitalWrite(2, HIGH);
  delay(2200);
  digitalWrite(0, LOW);
  delay(2200);
  digitalWrite(2, LOW);
  delay(2200);
  
  digitalWrite(0, HIGH);
  digitalWrite(2, HIGH);
  delay(2200);
  digitalWrite(0, LOW);
  digitalWrite(2, LOW);
  delay(2200);
}
