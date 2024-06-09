const int analogPin = A0;
int sensorValue = 0;

void setup() {
  Serial.begin(115200);
}

void loop() {
  sensorValue = analogRead(analogPin);
  Serial.print("Sensor Value: ");
  Serial.println(sensorValue);
  delay(1000);
}
