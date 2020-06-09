
 
int readpin = A0;  
int incoming = 0;
void setup ()
{
 
pinMode (readpin, INPUT) ;
//pinMode(DO, INPUT);
//pinMode (LED, OUTPUT);
 
Serial.begin(9600);
}
void loop ()
{
incoming = analogRead(readpin) ;
if(incoming > 500){
  Serial.print("nothing detected ");
  }
 if(incoming < 500){
  Serial.print("detecting something.");
  }
 
Serial.println(incoming);
delay(400);
}
