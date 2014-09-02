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

boolean running = false;

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
    
    if(newRight > 198) {
      newRight = 198;
      knobRight.write(198);
    }
    
    positionLeft = newLeft;
    positionRight = newRight;  
    
    //sprintf(buff, "%ld.%ld", newLeft/2, newRight/2);
    //Serial.println(buff);
  }

  //Drive stepper motor
  
  digitalWrite(dirpin, HIGH);     // Set the direction.
  
  unsigned long currentMillis = millis();
  if(running) {
    if(currentMillis - previousMillis > (timeBetweenSteps-positionLeft)) {
      // save the last time you blinked the LED 
      previousMillis = currentMillis;
    
      for (int i = 0; i<10; i++)     // number of microsteps at one time  
      {
        digitalWrite(steppin, LOW); 
        digitalWrite(steppin, HIGH); // Creates 'rising edge'
        delayMicroseconds(500); //motor speed     
      }
    }
  }
  
  // Graphics
    
  //GD.ClearColorRGB(0x103000);
  GD.get_inputs();
  GD.Clear();
  //GD.cmd_text(240, 68, 31, OPT_RIGHTX, buff);
  //GD.cmd_text(240, 75, 28, OPT_,"mL/hr");
  plotRate(100,68,positionLeft/2,positionRight/2);
  
  /*
  GD.Begin(POINTS); // draw 50-pixel wide green circles
  GD.ColorRGB(20, 91, 71);
  GD.PointSize(50 * 16);
  GD.BlendFunc(SRC_ALPHA, ONE);
  // additive blending
  for (int x = 100; x <= 380; x += 40)
  GD.Vertex2ii(x, 200);
  */
  
  //GD.cmd_button(20,150,190,50,28,OPT_FLAT,"Button");
  
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
  
  int offset1, offset2=0;
  
  GD.Tag(1);
  if(pressed == 1) {
    GD.Vertex2ii(20,174,BUTTON1_HANDLE);
    offset1=4;
    running = true;
  }else{
    GD.Vertex2ii(20,170,BUTTON0_HANDLE);
    offset1=0;
  }
  GD.Vertex2ii(35,175+offset1,START_HANDLE);
  GD.cmd_text(140,175+offset1, 31, OPT_CENTERX,"Start");
  
  GD.Tag(2);
  GD.ColorRGB(0xff2e18);
  if(pressed == 2) {
    GD.Vertex2ii(230,174,BUTTON1_HANDLE);
    offset2=4;
    running = false;
  }else{
    GD.Vertex2ii(230,170,BUTTON0_HANDLE);
    offset2=0;
  }
  GD.ColorRGB(0xffffff);
  GD.Vertex2ii(245,175+offset2,STOP_HANDLE);
  GD.cmd_text(345, 175+offset2, 31, OPT_CENTERX,"Stop");
  
  if(running)
    GD.cmd_spinner(240,136,1,0);
    
  GD.swap();
}

static void plotRate(int x, int y, int decimal, int fractional)
{
  int font = 31;
  
  GD.cmd_text(x,y-25,font-4,OPT_CENTER,"Rate:");
  GD.cmd_number(x - 8, y, font, OPT_RIGHTX | OPT_CENTERY, decimal);
  //GD.cmd_text(  x,     y, font, 0 | OPT_CENTERY, ".");
  
  GD.cmd_number(x + 8, y, font, 2 | OPT_CENTERY, fractional);
  GD.cmd_text(x+60,    y, font-2,OPT_CENTERY, "mL/hr");
  
  GD.PointSize(16 * 5); // means 30 pixels 
  GD.Begin(POINTS);
  GD.Vertex2ii(x, y);
}
