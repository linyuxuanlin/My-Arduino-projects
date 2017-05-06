//by lin
//接线:
int voice=A0;

float voltage;
void setup() {
  Serial.begin(9600); 
}

void loop() {
  Serial.print("*G");
  
  voltage=analogRead(voice)*0.0048828;
      Serial.print(String(voltage)+",");
      Serial.print("*");
      delay(10);

}
