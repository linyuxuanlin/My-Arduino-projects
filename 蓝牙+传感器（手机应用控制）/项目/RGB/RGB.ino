//接线:
int Red_LED_Pin = 9; // R--9
int Green_LED_Pin = 10; // G--10
int Blue_LED_Pin = 11; // B--11

//Varibles to hold brightness values ranging from 0 (off) to 255 (fully on)
int Red_value=0;
int Green_value=0;
int Blue_value=0;

char BluetoothData; // the data received from bluetooth serial link

void setup() {
  
  // Initialise LED pins as outputs
  pinMode(Red_LED_Pin, OUTPUT);
  pinMode(Green_LED_Pin, OUTPUT);
  pinMode(Blue_LED_Pin, OUTPUT);

  //initialsie serial communication
  Serial.begin(9600);
}

void loop() {

  //Process any info coming from the bluetooth serial link
  if (Serial.available()){
    BluetoothData=Serial.read(); //Get next character from bluetooth
    if(BluetoothData=='R') Red_value=Serial.parseInt(); //Read Red value
    if(BluetoothData=='G') Green_value=Serial.parseInt(); //Read Green Value
    if(BluetoothData=='B') Blue_value=Serial.parseInt(); //Read Blue Value
  }
  
  //update LED Brightness
  analogWrite(Red_LED_Pin, Red_value);
  analogWrite(Green_LED_Pin, Green_value);
  analogWrite(Blue_LED_Pin, Blue_value);
  delay(10);
  
}

