void setup() {
  Serial.begin(9600);
}

void loop() {
  float lumen = analogRead(0);
  Serial.println(lumen);
}
