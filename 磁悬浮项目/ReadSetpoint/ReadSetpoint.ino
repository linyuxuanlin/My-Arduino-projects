int Setpoint_X, Setpoint_Y;
void setup() {
  Serial.begin(9600);
  Serial.print("Hello, This is program to get X Y setpoint value!\r\n");
}

void loop() {
  // read the value from the sensor:
  Serial.print("Setpoint_X: ");
  Serial.print(analogRead(A1));
  Serial.print("      ");
  Serial.print("Setpoint_Y: ");
  Serial.print(analogRead(A0));
  Serial.print("\r\n");
  delay(100);
}
