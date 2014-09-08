#include <EEPROM.h>
#include <SPI.h>
#include <GD2.h>
#include <Encoder.h>

//#include "spinner_assets.h"
#include "default_assets.h"

int dirpin = 30;
int steppin = 32;

// Rotoary encoder best performance: both pins have interrupt capability
Encoder knobLeft(18, 19);
Encoder knobRight(20, 21);

int i = 0;
int pressed = 0;
long positionLeft  = -999;
long positionRight = -999;
//char buff[24];

long timeBetweenSteps = 1000;  // in ms
long previousMillis = 0;

boolean running, reversing = false;

void setup()
{
  // Set up stepper motor driver
  pinMode(dirpin, OUTPUT);     
  pinMode(steppin, OUTPUT);
  
  //Set up graphics
  GD.begin();
  LOAD_ASSETS();
}

void loop()
{
  // Read rotary encoder
  long newLeft, newRight;
  newLeft = knobLeft.read();
  newRight = knobRight.read();
  if (newLeft != positionLeft || newRight != positionRight) {

    if(newLeft <= 0) {
      newLeft = 0;
      knobLeft.write(0);
    }
    if(newRight <= 0) {
      newRight = 0;
      knobRight.write(0);  
    }
    
    if(newRight > 198) {
      newRight = 198;
      knobRight.write(198);
    }
    
    positionLeft = newLeft;
    positionRight = newRight;  

  }

  //Drive stepper motor
  
  if(reversing) {
    digitalWrite(dirpin, LOW);     // Set the direction backward
    
    for(int i=0;i<1000;i++) {
      digitalWrite(steppin, LOW);
      delayMicroseconds(2); //motor speed  
      digitalWrite(steppin, HIGH); // Creates 'rising edge'
      delayMicroseconds(1000); //motor speed 
    }
  } 
  
  unsigned long currentMillis = millis();
  if(running && !reversing) {
    
    digitalWrite(dirpin, HIGH);     // Set the direction forward
    
    if(currentMillis - previousMillis > (timeBetweenSteps-positionLeft)) {

      previousMillis = currentMillis;
    
      for (int i = 0; i<20; i++)     // number of microsteps at one time  
      {
        digitalWrite(steppin, LOW);
        delayMicroseconds(2);   
        digitalWrite(steppin, HIGH); // Creates 'rising edge'
        delayMicroseconds(1000); //motor speed     
      }
    }
  }
  
  // Graphics
  
  GD.get_inputs();
  GD.Clear();
  plotRate(110,68,positionLeft/2,positionRight/2);
    
  //GD.cmd_button(20,150,190,50,28,OPT_FLAT,"Button");
  
  GD.Begin(BITMAPS);
  
  pressed = GD.inputs.tag;
  
  int offset1, offset2,offset3=0;
  
  //Start button
  GD.Tag(1);
  if(pressed == 1) {
    GD.Vertex2ii(70,174,BUTTON1_HANDLE);
    offset1=4;
    running = true;
  }else{
    GD.Vertex2ii(70,170,BUTTON0_HANDLE);
    offset1=0;
  }
  GD.Vertex2ii(85,175+offset1,START_HANDLE);
  GD.cmd_text(185,185+offset1, 29, OPT_CENTERX,"Start");
  
  //Stop button
  GD.Tag(2);
  GD.ColorRGB(0xff2e18);
  if(pressed == 2) {
    GD.Vertex2ii(280,174,BUTTON1_HANDLE);
    offset2=4;
    running = false;
  }else{
    GD.Vertex2ii(280,170,BUTTON0_HANDLE);
    offset2=0;
  }
  GD.ColorRGB(0xffffff);
  GD.Vertex2ii(295,175+offset2,STOP_HANDLE);
  GD.cmd_text(395, 185+offset2, 29, OPT_CENTERX,"Stop");
  
  //Reverse button
  GD.Tag(3);
  GD.ColorRGB(0x0000ff);
  if(pressed == 3) {
    GD.Vertex2ii(280,34,BUTTON1_HANDLE);
    offset3=4;
    reversing = true;
  }else{
    GD.Vertex2ii(280,30,BUTTON0_HANDLE);
    offset3=0;
    reversing=false;
  }  
  GD.ColorRGB(0xffffff);
  GD.cmd_text(370, 45+offset3, 29, OPT_CENTERX,"Reverse");
  
  if(running)
    GD.cmd_spinner(130,110,1,0);
    
  GD.swap();
}

static void plotRate(int x, int y, int decimal, int fractional)
{
  int font = 31;
  
  GD.cmd_text(x,y-30,font-4,OPT_CENTER,"Rate:");
  GD.cmd_number(x - 8, y, font, OPT_RIGHTX | OPT_CENTERY, decimal);
  //GD.cmd_text(  x,     y, font, 0 | OPT_CENTERY, ".");
  
  GD.cmd_number(x + 8, y, font-1, 2 | OPT_CENTERY, fractional);
  GD.cmd_text(x+60,    y, font-2,OPT_CENTERY, "mL/hr");
  
  GD.PointSize(16 * 5); // means 30 pixels 
  GD.Begin(POINTS);
  GD.Vertex2ii(x, y);
}
