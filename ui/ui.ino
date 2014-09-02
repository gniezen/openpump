#include <EEPROM.h>
#include <SPI.h>
#include <GD2.h>
#include <Encoder.h>

//#include "spinner_assets.h"
#include "default_assets.h"

int dirpin = 30;
int steppin = 32;

//   Best Performance: both pins have interrupt capability
//   Good Performance: only the first pin has interrupt capability
//   Low Performance:  neither pin has interrupt capability
Encoder knobLeft(18, 19);
Encoder knobRight(20, 21);

int i = 0;
int pressed = 0;
long positionLeft  = -999;
long positionRight = -999;
char buff[24];

long timeBetweenSteps = 1000;  // in ms
long previousMillis = 0;

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
  Serial.begin(9600);
  
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
    
    positionLeft = newLeft;
    positionRight = newRight;  
    
    sprintf(buff, "%ld.%ld", newLeft/2, newRight/2);
    Serial.println(buff);
  }

  //Drive stepper motor
  
  digitalWrite(dirpin, HIGH);     // Set the direction.
  
  unsigned long currentMillis = millis();
 
  if(currentMillis - previousMillis > timeBetweenSteps) {
    // save the last time you blinked the LED 
    previousMillis = currentMillis;
  
    for (int i = 0; i<10; i++)     // number of microsteps at one time  
    {
      digitalWrite(steppin, LOW); 
      digitalWrite(steppin, HIGH); // Creates 'rising edge'
      delayMicroseconds(5000); //motor speed     
    }
  }
  
  // Graphics
    
  //GD.ClearColorRGB(0x103000);
  GD.get_inputs();
  GD.Clear();
  GD.cmd_text(240, 68, 31, OPT_CENTER, buff);
  
  /*
  GD.Begin(POINTS); // draw 50-pixel wide green circles
  GD.ColorRGB(20, 91, 71);
  GD.PointSize(50 * 16);
  GD.BlendFunc(SRC_ALPHA, ONE);
  // additive blending
  for (int x = 100; x <= 380; x += 40)
  GD.Vertex2ii(x, 200);
  */
  
  GD.cmd_button(20,150,190,50,28,OPT_FLAT,"Button");
  
  GD.Begin(BITMAPS);
  /*
  GD.Vertex2ii(240, 110, SPINNER_HANDLE, i);
  i += 1;
  if(i>11)
    i = 0;
  */
  //GD.cmd_spinner(50,50,1,0);

  //GD.Vertex2ii(240,110,GREY_PANEL_HANDLE);
  
  
  
  pressed = GD.inputs.tag;
  
  GD.Tag(1);
  if(pressed == 1) {
    GD.Vertex2ii(250,124,BUTTON1_HANDLE);
  }else{
    GD.Vertex2ii(250,120,BUTTON0_HANDLE);
  }
 
  
  
  GD.swap();
}
