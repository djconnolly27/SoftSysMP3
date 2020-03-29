#include <Adafruit_GFX.h>
#include <Adafruit_PCD8544.h>

boolean backlight = true;
int contrast=50;

int menuitem = 1;

volatile boolean up = false;
volatile boolean down = false;
volatile boolean middle = false;

int downButtonState = 0;
int upButtonState = 0;
int selectButtonState = 0;
int lastDownButtonState = 0;
int lastSelectButtonState = 0;
int lastUpButtonState = 0;

Adafruit_PCD8544 display = Adafruit_PCD8544( 5, 4, 3);

void setup() {

  pinMode(2, INPUT_PULLUP);
  pinMode(1, INPUT_PULLUP);
  pinMode(0, INPUT_PULLUP);
  pinMode(7,OUTPUT);

  digitalWrite(7,LOW); //Turn Backlight ON

  Serial.begin(9600);

  display.begin();
  display.setContrast(contrast); //Set contrast to 50
  display.clearDisplay();
  display.display();
}

void loop() {
  char* song1 = "Renegade";
  char* song2 = "Roar";
  char* song3 = "Firestone";
  drawMenu(song1, song2, song3);

  downButtonState = digitalRead(2);
  selectButtonState = digitalRead(1);
  upButtonState =   digitalRead(0);

  checkIfDownButtonIsPressed();
  checkIfUpButtonIsPressed();
  checkIfSelectButtonIsPressed();

  if (up) {
    up = false;
    menuitem--;
    if (menuitem==0)
    {
      menuitem=3;
    }
  }


  if (down) {
    down = false;
    menuitem++;
    if (menuitem==4)
    {
      menuitem=1;
    }
  }


  if (middle) {
    middle = false;

    if (menuitem==2)
    {
      if (backlight)
      {
        backlight = false;
        turnBacklightOff();
        }
      else
      {
        backlight = true;
        turnBacklightOn();
       }
    }

    if(menuitem ==3)
    {
      resetDefaults();
    }

   }

}

void checkIfDownButtonIsPressed()
{
  if (downButtonState != lastDownButtonState)
{
  if (downButtonState == 0)
  {
    down=true;
  }
  delay(50);
}
 lastDownButtonState = downButtonState;
}

void checkIfUpButtonIsPressed()
{
  if (upButtonState != lastUpButtonState)
  {
    if (upButtonState == 0) {
      up=true;
    }
    delay(50);
  }
   lastUpButtonState = upButtonState;
}

void checkIfSelectButtonIsPressed()
{
   if (selectButtonState != lastSelectButtonState)
  {
    if (selectButtonState == 0) {
      middle=true;
    }
    delay(50);
  }
   lastSelectButtonState = selectButtonState;
}


void drawMenu(char* s1, char* s2, char* s3) {
  display.setTextSize(1);
  display.clearDisplay();
  display.setTextColor(BLACK, WHITE);
  display.setCursor(15, 0);
  display.print("MENU");
  display.drawFastHLine(0,10,83,BLACK);

  display.setCursor(0, 15);
  if (menuitem==1)
  {
    display.setTextColor(WHITE, BLACK);
  }
  else
  {
    display.setTextColor(BLACK, WHITE);
  }
  display.print(s1);

  display.setCursor(0, 25);
  if (menuitem==2)
  {
    display.setTextColor(WHITE, BLACK);
  }
  else
  {
    display.setTextColor(BLACK, WHITE);
  }
  display.print(s2);
  display.display();

  if (menuitem==3)
  {
    display.setTextColor(WHITE, BLACK);
  }
  else
  {
    display.setTextColor(BLACK, WHITE);
  }
  display.setCursor(0, 35);
  display.print(s3);
  display.display();

}

void resetDefaults() {
  contrast = 50;
  setContrast(contrast);
  backlight = true;
  turnBacklightOn();
}

void setContrast()
{
  display.setContrast(contrast);
  display.display();
}

void turnBacklightOn() {
  digitalWrite(7,LOW);
}

void turnBacklightOff() {
  digitalWrite(7,HIGH);
}
