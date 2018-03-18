
#define IR1 2 //white
#define IR2 3 //blue
#define IR3 4 //light green
#define IR4 5 //orange
#define IR5 6 //dark green
#define IRsensor 9

//Send noTone to all IR Pins
void ResetDiodes() {
  //Set all IR diodes to Off
  for(int IRPin=2; IRPin<7; IRPin++) {
    noTone(IRPin);
  }
}

//Returns the number of successful reads out of 100
int GetIRData(int IRPin) {
  int IRResult;
  IRResult = 0;
  
  //Make 100 readings
  for(int i=0; i < 100; i++) {
    if (digitalRead(IRsensor)==LOW){ //See if we get a signal
     IRResult++; //Increment counter
    }
  } 
  return IRResult;
}


void setup(){

  ResetDiodes(); //Set all diodes to off
      
  Serial.begin(9600); //Initialize serial interface
}

//MAIN LOOP STARTS HERE
 void loop(){

  int IRResult;
  int TotalResult;

  IRResult = 0;
  TotalResult = 0;
  
  //Make 100 reading for each diode
  for(int IRPin=2; IRPin<7; IRPin++) {
    
    //Set current diode to on 38kHz
    tone (IRPin, 38000);

    //Read the pin and add to total
    IRResult = GetIRData(IRPin); 
    TotalResult = TotalResult + IRResult;

    //Set pin to off
    noTone(IRPin); 
  }

//  Serial.println(IRResult);

  //Get IR sensor data with all diodes set to off. 
  ResetDiodes(); 
  //Read the pins without any IR signal
  //if at least one pin detects a signal assume somethings wrong
  for(int IRPin=2; IRPin<7 && TotalResult > 0; IRPin++) {
    if (GetIRData(IRPin) > 10) { 
      TotalResult = 0;
    }
  }
  
  if(IRResult<80) {
    Serial.println("You've got mail");
 } else {
    //do nothing. Either no mail or error source
//    Serial.println("No mail");
 }
  

}
