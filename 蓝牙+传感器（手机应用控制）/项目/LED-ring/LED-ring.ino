//接线:DIN--D8

int red = 10; // Red part of LED colour 0 to 256
int green = 10; // Green part of LED colour 0 to 256
int blue = 0; // Blue part of LED colour 0 to 256
int no_of_leds = 16; //set this to the number of LEDs on your Ring
int mode = 0; //0 = all leds lit, 1 = spin  
int led_pos = 1; //position of led to be lit (used in spin mode)

char BluetoothData; // the data received from bluetooth serial link
int interval=40; //in milliseconds.  Determines speed of updates & spin effect,
unsigned long lastUpdateTime=0;

void setup() {
    pinMode(2, OUTPUT); //Pin 8 used for led data line
    digitalWrite(2,LOW);
      
  //Initiate Serial for Bluetooth Communication
    Serial.begin(9600); 
}

void loop() {
  
  //Process any info coming from the bluetooth serial link
  if (Serial.available()){
    BluetoothData=Serial.read(); //Get next character from bluetooth
    if(BluetoothData=='R') red=Serial.parseInt(); //Read Red value
    if(BluetoothData=='G') green=Serial.parseInt(); //Read Green Value
    if(BluetoothData=='B') blue=Serial.parseInt(); //Read Blue Value
    if(BluetoothData=='A') mode=1; //Spin Mode
    if(BluetoothData=='a') mode=0; //All Leds On Mode
    if(BluetoothData=='S') interval=150-Serial.parseInt(); //Read Interval
    if(BluetoothData=='N') no_of_leds=Serial.parseInt(); //Read Number of LEDs
  }

  //See if its time to update the LEDs
  unsigned long t=millis();
  if ((t-lastUpdateTime)>interval){
    colorRing(); //update the LED colors
    lastUpdateTime=millis();
    led_pos++; //point to next led for spin effect
    if (led_pos>no_of_leds) led_pos=1; //go back to the first led when the end is reached
  }
  
}


void colorRing(){
  // Assembly code to update LED colors
  // Loops though all LEDs in order
  // For each LED,  8 Green bits are sent first, followed by the 8 red bits and finally the 8 blue bits
  // The Most Signifiacnt Bit (MSB) is sent first
  
  cli(); //dissable interupts whilst we update LEDs
  
  asm("mov R17,%0 \n\t":  "+r" (no_of_leds)); //Store number of leds in Register 17
  asm("mov R22,%0 \n\t":  "+r" (led_pos));    //Store LED lit position in Register 22
  asm("mov R21,%0 \n\t":  "+r" (mode));       //Store mode in Register 21
  
  asm("LedLoop:\n\t"); //Start of Loop for each LED

  //Set color for LED
    asm("cpi R21,0x00 \n\t"); //See if we are in 'all on' mode
    asm("breq on\n\t");       //if so, all LEDs are lit -> jump to LED on code
    asm("cp R22,R17 \n\t");   //else we see if this LED is the one to be lit
    asm("brne off\n\t");      //if not, we jump to the LED off code.
    asm("on: \n\t"); // LED on
      asm("mov R18,%0 \n\t":  "+r" (red));   //Store Red part of Color in Register 18
      asm("mov R19,%0 \n\t":  "+r" (green)); //Store Green part of Color in Register 19
      asm("mov R20,%0 \n\t":  "+r" (blue));  //Store Blue part of Color in Register 20
      asm("jmp cont \n\t");
    asm("off: \n\t"); // LED off 
      asm("ldi R18,0x00 \n\t"); // Red = 0
      asm("ldi R19,0x00 \n\t"); // Green = 0
      asm("ldi R20,0x00 \n\t"); // Blue = 0
   asm("cont: \n\t");  
   
   
  ///// GREEN - Send green bits out to Pin 8  
    asm("ldi R16,0x08 \n\t"); // Number of green bits (8) to send put in Register R16 
    asm("GreenLoop: \n\t");   // Start of Loop for green bits
      asm("sbrs R19,7 \n\t");    //Test bit 7 of the green byte, Skip next command if a 1
      asm("jmp GreenZero \n\t"); //jump over the write 'one' code
      
      //write a 'one' to the Leds data line
      asm("sbi 5,0 \n\t");  //Set Port B Bit 0 (aka Output Pin 8) to High 
      asm("nop\n\t""nop\n\t""nop\n\t""nop\n\t""nop\n\t""nop\n\t""nop\n\t""nop\n\t""nop\n\t""nop\n\t");
      asm("cbi 5,0 \n\t"); //Set Port B Bit 0 to Low 
      asm("nop\n\t""nop\n\t""nop\n\t""nop\n\t""nop\n\t"); //Wait a few clock cycles
      asm("jmp GreenCont \n\t");  //jump over the write 'zero' code
     
      //write a 'zero' to the Leds data line
      asm("GreenZero:\n\t");
      asm("sbi 5,0\n\t"); //Set Port B Bit 0 (aka Output Pin 8) to High 
      asm("nop\n\t""nop\n\t""nop\n\t""nop\n\t""nop\n\t"); //Wait a few clock cycles
      asm("cbi 5,0\n\t"); //Set Port B Bit 0 to Low 
      asm("nop\n\t""nop\n\t""nop\n\t""nop\n\t""nop\n\t""nop\n\t""nop\n\t""nop\n\t");
     
      asm("GreenCont:\n\t");
      asm("lsl R19\n\t"); //Rotate the green Byte so that we point to next bit
      asm("dec R16\n\t"); //Decrease the count of green bits left to do 
      asm("cpi R16,0x00\n\t"); //See if we have counted down to zero
      asm("brne GreenLoop\n\t"); //If not zero, Loop back and do the next green bit


  ///// RED - Send red bits out to Pin 8  
    asm("ldi R16,0x08 \n\t"); // Number of red bits (8) to send put in Register R16 
    asm("RedLoop: \n\t"); // Start of Loop for Red bits
      asm("sbrs R18,7 \n\t"); //Test bit 7 of the Red byte, Skip next command if a 1
      asm("jmp RedZero \n\t"); //jump over the write 'one' code
      
      //write a 'one' to the Leds data line
      asm("sbi 5,0 \n\t");  //Set Port B Bit 0 (aka Output Pin 8) to High 
      asm("nop\n\t""nop\n\t""nop\n\t""nop\n\t""nop\n\t""nop\n\t""nop\n\t""nop\n\t""nop\n\t""nop\n\t");
      asm("cbi 5,0 \n\t"); //Set Port B Bit 0 to Low 
      asm("nop\n\t""nop\n\t""nop\n\t""nop\n\t""nop\n\t");
      asm("jmp RedCont \n\t");  //jump over the write 'zero' code
     
      //write a 'zero' to the Leds data line
      asm("RedZero:\n\t");
      asm("sbi 5,0\n\t"); //Set Port B Bit 0 (aka Output Pin 8) to High 
      asm("nop\n\t""nop\n\t""nop\n\t""nop\n\t""nop\n\t");
      asm("cbi 5,0\n\t"); //Set Port B Bit 0 to Low 
      asm("nop\n\t""nop\n\t""nop\n\t""nop\n\t""nop\n\t""nop\n\t""nop\n\t""nop\n\t");
     
      asm("RedCont:\n\t");
      asm("lsl R18\n\t"); //Rotate the Red Byte so that we point to next bit
      asm("dec R16\n\t"); //Decrease the count of red bits left to do 
      asm("cpi R16,0x00\n\t"); //See if we have counted down to zero
      asm("brne RedLoop\n\t"); //If not zero, Loop back and do the next Red bit


  ///// BLUE - Send blue bits out to Pin 8  
    asm("ldi R16,0x08 \n\t"); // Number of Blue bits (8) to send put in Register R16 
    asm("BlueLoop: \n\t"); // Start of Loop for Blue bits
      asm("sbrs R20,7 \n\t"); //Test bit 7 of the Blue byte, Skip next command if a 1
      asm("jmp BlueZero \n\t"); //jump over the write 'one' code
      
      //write a 'one' to the Leds data line
      asm("sbi 5,0 \n\t");  //Set Port B Bit 0 (aka Output Pin 8) to High 
      asm("nop\n\t""nop\n\t""nop\n\t""nop\n\t""nop\n\t""nop\n\t""nop\n\t""nop\n\t""nop\n\t""nop\n\t");
      asm("cbi 5,0 \n\t"); //Set Port B Bit 0 to Low 
      asm("nop\n\t""nop\n\t""nop\n\t""nop\n\t""nop\n\t");
      asm("jmp BlueCont \n\t");  //jump over the write 'zero' code
     
      //write a 'zero' to the Leds data line
      asm("BlueZero:\n\t");
      asm("sbi 5,0\n\t"); //Set Port B Bit 0 (aka Output Pin 8) to High 
      asm("nop\n\t""nop\n\t""nop\n\t""nop\n\t""nop\n\t");
      asm("cbi 5,0\n\t"); //Set Port B Bit 0 to Low 
      asm("nop\n\t""nop\n\t""nop\n\t""nop\n\t""nop\n\t""nop\n\t""nop\n\t""nop\n\t");
     
      asm("BlueCont:\n\t");
      asm("lsl R20\n\t"); //Rotate the Blue Byte so that we point to next bit
      asm("dec R16\n\t"); //Decrease the count of blue bits left to do 
      asm("cpi R16,0x00\n\t"); //See if we have counted down to zero
      asm("brne BlueLoop\n\t"); //If not zero, Loop back and do the next Blue bit
  
  // See if we have more LEDs to update
    asm("dec R17\n\t");      //Decrease the count of LEDs left to update 
    asm("cpi R17,0x00\n\t"); //See if we have counted down to zero
    asm("breq Done\n\t");    //If zero, jump to Done
    asm("jmp LedLoop\n\t");  //Else, send the data for the next LED in the chain
    asm("Done:\n\t");        //Done, awesome!
    
    sei(); //enable interupts again
}
