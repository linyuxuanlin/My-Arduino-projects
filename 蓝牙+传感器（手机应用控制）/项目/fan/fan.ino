//by lin
//接线:
int A_Pin = 9;
int B_Pin = 10;

int A_value = 0;
int B_value = 0;



void setup() {


  pinMode(A_Pin, OUTPUT);
  pinMode(B_Pin, OUTPUT);



  Serial.begin(9600);
}

void loop() {


  if (Serial.available()) {
    
    if (Serial.read() == 'A') A_value = Serial.parseInt();
  }
  analogWrite(A_Pin, A_value);
  delay(10);

}
