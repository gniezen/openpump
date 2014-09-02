int dirpin = 8;
int steppin = 9;

void setup() {                
  pinMode(dirpin, OUTPUT);     
  pinMode(steppin, OUTPUT);
}

void loop() {
  
  digitalWrite(dirpin, LOW);     // Set the direction.
  delay(1000); //time between steps in ms
  
  for (int i = 0; i<10; i++)     // number of microsteps at one time  
  {
    digitalWrite(steppin, LOW); 
    digitalWrite(steppin, HIGH); // Creates 'rising edge'
    delayMicroseconds(5000); //motor speed     
  }                             
        
}
