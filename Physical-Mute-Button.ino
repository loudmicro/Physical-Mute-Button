
#include "M5Atom.h"
#include "BleKeyboard.h"

BleKeyboard bleKeyboard("Mute Button", "M5Stack Atom Matrix", 100);
unsigned long long time1 = 0;
unsigned long long time2 = 0;

void setup()
{
    M5.begin(false, false, true); //starts the matrix
    delay(10);
    M5.dis.fillpix(CRGB::Black); //paints it black
    bleKeyboard.begin(); //starts the ble keyboard
    time1 = millis();
}

bool muted = false;
int brightness = 0;
int increment = 0;


void loop()
{

  if(bleKeyboard.isConnected()) {

    time2 = millis();
    if(time2 > (time1 + 240000)){
      bleKeyboard.press(KEY_F14);//sends f14 to keep teams from going idle (thanks to Caffeine for the idea)
      time1 = millis();
    }
    
    if (M5.Btn.wasPressed()) { //sends ctr + shift + m on button press
      muted = !muted;
      bleKeyboard.press(KEY_LEFT_CTRL);
      bleKeyboard.press(KEY_LEFT_SHIFT);
      bleKeyboard.press('M');
      delay(100);
      bleKeyboard.releaseAll();
    }
    M5.dis.setBrightness(100); //switch colours
    if (muted) {
      M5.dis.fillpix(CRGB::Green);
    } else {
      M5.dis.fillpix(CRGB::Black);
    }
  } else {
    muted = false; 
    //M5.dis.fillpix(CRGB::Blue);
    //blue heart bluetooth
    M5.dis.drawpix(23, 0x0000FF);
    M5.dis.drawpix(21, 0x0000FF);
    M5.dis.drawpix(15, 0x0000FF);
    M5.dis.drawpix(16, 0x0000FF);
    M5.dis.drawpix(17, 0x0000FF);
    M5.dis.drawpix(18, 0x0000FF);
    M5.dis.drawpix(19, 0x0000FF);
    M5.dis.drawpix(10, 0x0000FF);
    M5.dis.drawpix(11, 0x0000FF);
    M5.dis.drawpix(12, 0x0000FF);
    M5.dis.drawpix(13, 0x0000FF);
    M5.dis.drawpix(14, 0x0000FF);
    M5.dis.drawpix(6, 0x0000FF);
    M5.dis.drawpix(7, 0x0000FF);
    M5.dis.drawpix(8, 0x0000FF);
    M5.dis.drawpix(2, 0x0000FF);
    
    
    
    if (brightness <= 0) {
      increment = 2;
    } else if (brightness >= 100) {
      increment = -2;
    }
    brightness += increment;
    M5.dis.setBrightness(brightness);
  }

  M5.update();
  delay(50);
}
