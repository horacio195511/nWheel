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
  myDisplay.print(modeList.length());
  stringStart = 0;
  stringEnd = stringStart + 15;
}
void loop() {
  int but = button(analogRead(buttonIn)) ;
  while (but == RIGHT) {
    if (stringStart >= 0 || (stringEnd - 16) >= 0 ) {
      myDisplay.setCursor(0, 1);
      myDisplay.print(modeList.substring(stringStart, stringEnd));
      stringStart--;
      stringEnd--;
    }
    /*Case the stringEnd &StringStart over boundary*/
    if (stringEnd < 0) stringEnd = modeList.length();
    if (stringStart < 0) stringStart = modeList.length();

    if (stringStart < 0 || (stringEnd - 16) < 0 ) {
      myDisplay.setCursor(0, 1);
      myDisplay.print(modeList.substring(stringStart, modeList.length()) + modeList.substring(0, stringEnd));
      stringStart--;
      stringEnd--;
    }
    myDisplay.setCursor(3, 0);
    myDisplay.print(stringStart);
    myDisplay.setCursor(6, 0);
    myDisplay.print(stringEnd);
    delay(250);
  }


  while (but == LEFT ) {
    if (stringEnd <= modeList.length() || ((stringStart + 16) <= modeList.length())) {
      myDisplay.setCursor(0, 1);
      myDisplay.print(modeList.substring(stringStart, stringEnd));
      stringStart++;
      stringEnd++;
    }

    /*Case the stringEnd &StringStart over boundary*/
    if (stringStart > modeList.length()) stringStart = 0;
    if (stringEnd > modeList.length())  stringEnd = 0;

    if ((stringEnd > modeList.length()) || ((stringStart + 16) > modeList.length())) {
      myDisplay.setCursor(0, 1);
      myDisplay.print( modeList.substring(stringStart, modeList.length()) + modeList.substring(0, stringEnd) );
      stringStart++;
      stringEnd++;
    }
    myDisplay.setCursor(3, 0);
    myDisplay.print(stringStart);
    myDisplay.setCursor(6, 0);
    myDisplay.print(stringEnd);
    delay(250);
  }
}
