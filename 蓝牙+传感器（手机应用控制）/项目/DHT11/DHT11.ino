//接线:
int data_pin = 9;
int vcc_pin=8;
int gnd_pin=10;

boolean result[41]; //holds the result
int interval=2000; //Sample every 2 seconds
unsigned int temp; //in celcius
unsigned int humidity; //in %RH

void setup() {

  //Supply power to DHT11 (Uses upto 2.5mA)
    pinMode(gnd_pin, OUTPUT);
    pinMode(vcc_pin, OUTPUT);
    digitalWrite(gnd_pin,LOW);
    digitalWrite(vcc_pin,HIGH);
    
  //Initiate Serial for Bluetooth Communication
    Serial.begin(9600); 
}

void loop() {
  //Pause before taking next measurement
    delay(interval); 
 
  //Trigger reading by holding data pin low for 18ms
    pinMode(data_pin, OUTPUT);
    digitalWrite(data_pin,LOW);
    delay(18);
    digitalWrite(data_pin,HIGH);
    pinMode(data_pin, INPUT_PULLUP); 
  
  //read 41 bits of signal
    for(int i=0;i<=40;i++){
      result[i]=(pulseIn(data_pin, HIGH)>40);
    }

  //Extract Humidity (from byte 1)
    humidity=0;
    for (int i=1;i<=8;i++){
      humidity=humidity<<1;
      if (result[i]) humidity|=1;
    }
      
  //Extract Temperature (from Byte 3)
    temp=0;
    for (int i=17;i<=24;i++){
      temp=temp<<1;
      if (result[i]) temp|=1;
    }
    
   //Send data over Bluetooth
    Serial.print("*T"+String(temp)+"*");
    Serial.print("*H"+String(humidity)+"*");

}
