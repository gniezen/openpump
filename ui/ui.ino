#include <EEPROM.h>
#include <SPI.h>
#include <GD2.h>

//#include "spinner_assets.h"
#include "default_assets.h"

int dirpin = 30;
int steppin = 32;

int i = 0;
  int pressed = 0;

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
  //Drive stepper motor
  
  digitalWrite(dirpin, HIGH);     // Set the direction.
  delay(1000); //time between steps in ms
  
  for (int i = 0; i<10; i++)     // number of microsteps at one time  
  {
    digitalWrite(steppin, LOW); 
    digitalWrite(steppin, HIGH); // Creates 'rising edge'
    delayMicroseconds(5000); //motor speed     
  }
    
  //GD.ClearColorRGB(0x103000);
  GD.get_inputs();
  GD.Clear();
  GD.cmd_text(240, 68, 31, OPT_CENTER, "56.7 mL/h");
  
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
