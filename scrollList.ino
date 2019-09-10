#define buttonIn A0
#include<LiquidCrystal.h>
LiquidCrystal myDisplay(8, 9, 4, 5, 6, 7);
int buttonOut;
//note that I put some space at the end of each string, so the privious word will be cover.
String modeList = "Follow Explore Upload ShowOff Manual ";
int stringStart;
int stringEnd;
/*make a enumerating button list, so the code would be more readable*/
enum buttonFig
{
  UP = 0,
  DOWN,
  RIGHT,
  LEFT,
  SELECT,
  NONE
} ;

/*Detect which button is pressed, the return value is the button pressed.*/
int button(int i) {
  /*--------------------------Result:1.no button:1023-----------------------
         --------------------------2.select:723---------------------------
         --------------------------3.up:130-------------------------------
         --------------------------4.down:307-----------------------------
         --------------------------5.left:481-----------------------------
         --------------------------6.right:0------------------------------*/
  if (i >= 1000) {
    return NONE;
  }
  else if (i >= 700 && i <= 750) {
    return SELECT;
  }
  else if (i >= 120 && i <= 140) {
    return UP;
  }
  else if (i >= 300 && i <= 320) {
    return DOWN;
  }
  else if (i >= 470 && i <= 490) {
    return LEFT;
  }
  else                           {
    return RIGHT;
  }
}

void setup() {
  Serial.begin(9600);
  myDisplay.begin(16, 2);
  myDisplay.print("mode List   V");
  stringStart = 0;
  stringEnd = stringStart + 16;
}
void loop() {
  while (button(analogRead(buttonIn)) == RIGHT) {
    /***********************************************************************************/
    //Case the string not break limit
    if (stringEnd <= modeList.length() && stringStart > 0) {
      myDisplay.setCursor(0, 1);
      myDisplay.print(modeList.substring(stringStart, stringEnd));
    }

    /*Case the stringEnd & StringStart over boundary*/
    if (stringEnd > modeList.length()) {
      stringEnd = modeList.length();
      stringStart = stringEnd - 16;
    }
    /***************************************************************************************/

    /*Case the stringEnd & StringStart over boundary*/
    if (stringStart <= 0) {
      stringStart = 0;
      stringEnd = stringStart + 16;
      myDisplay.setCursor(0, 1);
      myDisplay.print(modeList.substring(stringStart, stringEnd));
    }

    /******************************************************************************************/

    //Decrement two parameter
    stringEnd--;
    stringStart--;
    delay(150);
  }


  while (button(analogRead(buttonIn)) == LEFT ) {
    /*************************************************************************************************/
    //Case the string not break limit
    if (stringEnd <= modeList.length() && stringStart > 0) {
      myDisplay.setCursor(0, 1);
      myDisplay.print(modeList.substring(stringStart, stringEnd));
    }

    /*Case the stringEnd &StringStart over boundary*/
    if (stringEnd > modeList.length()) {
      stringEnd = modeList.length();
      stringStart = stringEnd - 16;
    }
    /**********************************************************************************************************/

    /*Case the stringEnd &StringStart over boundary*/
    if (stringStart <= 0) {
      stringStart = 0;
      stringEnd = stringStart + 16;
      myDisplay.setCursor(0, 1);
      myDisplay.print(modeList.substring(stringStart, stringEnd));
    }

    /***********************************************************************************************************/
    //Increment two parameter
    stringStart++;
    stringEnd++;
    delay(150);
  }
}
