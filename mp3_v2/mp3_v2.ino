/*************************************************** 
  This is an example for the Adafruit VS1053 Codec Breakout

  Designed specifically to work with the Adafruit VS1053 Codec Breakout 
  ----> https://www.adafruit.com/products/1381

  Adafruit invests time and resources providing this open source code, 
  please support Adafruit and open-source hardware by purchasing 
  products from Adafruit!

  Written by Limor Fried/Ladyada for Adafruit Industries.  
  BSD license, all text above must be included in any redistribution
 ****************************************************/

// include SPI, MP3 and SD libraries
#include <SPI.h>
#include <Adafruit_VS1053.h>
#include <SD.h>

// These are the pins used for the breakout example
#define BREAKOUT_RESET  9      // VS1053 reset pin (output)
#define BREAKOUT_CS     10     // VS1053 chip select pin (output)
#define BREAKOUT_DCS    8      // VS1053 Data/command select pin (output)
// These are the pins used for the music maker shield
#define SHIELD_RESET  -1      // VS1053 reset pin (unused!)
#define SHIELD_CS     7      // VS1053 chip select pin (output)
#define SHIELD_DCS    6      // VS1053 Data/command select pin (output)

// These are common pins between breakout and shield
#define CARDCS 4     // Card chip select pin
// DREQ should be an Int pin, see http://arduino.cc/en/Reference/attachInterrupt
#define DREQ 3       // VS1053 Data request, ideally an Interrupt pin

Adafruit_VS1053_FilePlayer musicPlayer = Adafruit_VS1053_FilePlayer(BREAKOUT_RESET, BREAKOUT_CS, BREAKOUT_DCS, DREQ, CARDCS);

int change = 0;
int sys_state = 0; // 0 = stopped, 1 = playing, 2 = paused
char curr_dir[20];
char *myPlaylist[20];
int currSong = 1;
int maxSongs = 0;


const byte numChars = 32;
char receivedChars[numChars]; // an array to store the received data

boolean newData = false;

void setup() {
  
  // Setup Music Player
  Serial.begin(9600);
  Serial.println("Adafruit VS1053 Library Test");

  // initialise the music player
  if (! musicPlayer.begin()) { // initialise the music player
     Serial.println(F("Couldn't find VS1053, do you have the right pins defined?"));
     while (1);
  }
  Serial.println(F("VS1053 found"));

  musicPlayer.sineTest(0x44, 500);    // Make a tone to indicate VS1053 is working
 
  if (!SD.begin(CARDCS)) {
    Serial.println(F("SD failed, or not present"));
    while (1);  // don't do anything more
  }
  Serial.println("SD OK!");


  // Setup MP3
  curr_dir[0] = '/';
  //currDirSetup();
  setPlaylist();
  
//  curr_dir[1] = '9';
  Serial.println("\nWelcome to Dan & Alex's MP3 Player!\n");
  listCommands();
  
  // Set volume for left, right channels. lower numbers == louder volume!
  musicPlayer.setVolume(20,20);
  
  // This option uses a pin interrupt. No timers required! But DREQ
  // must be on an interrupt pin. For Uno/Duemilanove/Diecimilla
  // that's Digital #2 or #3
  // See http://arduino.cc/en/Reference/attachInterrupt for other pins
  // *** This method is preferred
  if (! musicPlayer.useInterrupt(VS1053_FILEPLAYER_PIN_INT))
    Serial.println(F("DREQ pin is not an interrupt pin"));
}


void loop() {  
  // Alternately, we can just play an entire file at once
  // This doesn't happen in the background, instead, the entire
  // file is played and the program will continue when it's done!
//  musicPlayer.playFullFile("happymaybe.ogg");


  // Blink Test to see if the program gets stuck
  digitalWrite(13, HIGH);
  delay(1000);
  digitalWrite(13, LOW);
  delay(900);

  
//  printNextFile(SD.open("/"), 0);
  
  // Start playing a file, then we can do stuff while waiting for it to finish
//  if (! musicPlayer.startPlayingFile("/happym~1.mp3")) {
//    Serial.println("Could not open file happymaybe.mp3");
//    while (1);
//  }

  
//  Serial.println(F("Started playing"));
  recvWithStartEndMarkers();
//  Serial.println(receivedChars);
//  while (Serial.available()) {
  char op_code = receivedChars[0];
  switch (op_code) {
    case 'l':
//        Serial.println("listing");
      list_current_directory();
      break;
    case 'b':
//        char song_number = Serial.read();
//        Serial.println(song_number);
      if(change == 1){
        play_song();
        change = 0;
      }
      //Serial.println(curr_dir);
      break;
    case 'p':
      pause_song(1);
      break;
    case 's':
      stop_song();
      break;
    case 'r':
      pause_song(0);
      break;
    case 'f':
      if(change == 1){
        currDirForward();
        change = 0;
      } 
      break;
    case 'd':
      if(change == 1){
        currDirBackward();
        change = 0;
      } 
      break;
    case 'e':
////        exit_current_directory();
      break;
  }
  newData = false;
}
