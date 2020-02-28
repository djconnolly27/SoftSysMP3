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


int sys_state = 0; // 0 = stopped, 1 = playing, 2 = paused
char curr_dir[20];

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
  curr_dir[1] = '9';
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


  // Blink Test
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

  while (Serial.available()) {
    char op_code = Serial.read();
    switch (op_code) {
      case 'l':
        list_current_directory();
        break;
      case 'b':
//        char song_number = Serial.read();
//        Serial.println(song_number);
        play_song();
        Serial.println(curr_dir);
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
      case 'e':
////        exit_current_directory();
        break;
    }
  }

//  while (musicPlayer.playingMusic) {
//    // file is now playing in the 'background' so now's a good time
//    // to do something else like handling LEDs or buttons :)
//    Serial.print(".");
//    delay(1000);
//    char c = Serial.read();
//    Serial.println(c);
//    
//    // if we get an 's' on the serial console, stop!
//    if (c == 's') {
//      musicPlayer.stopPlaying();
//    }
//    
//    // if we get an 'p' on the serial console, pause/unpause!
//    if (c == 'p') {
//      if (! musicPlayer.paused()) {
//        Serial.println("Paused");
//        musicPlayer.pausePlaying(true);
//      } else { 
//        Serial.println("Resumed");
//        musicPlayer.pausePlaying(false);
//      }
//    }
//  }
//  Serial.println("Done playing music");
}

void stop_song() {
  if (sys_state != 0) {
    if (musicPlayer.playingMusic) {
      Serial.println("Song Stopped");
      musicPlayer.stopPlaying();
    }
    sys_state = 0;
  }
}

void pause_song(int stat) {
  if (musicPlayer.playingMusic) {
    if (stat) {
      Serial.println("Song Paused");
      sys_state = 2;
    } else {
      Serial.println("Song Resumed");
      sys_state = 1;
    }
    musicPlayer.pausePlaying(stat);
  }
}

void listCommands() {
  Serial.println("Options: ");
  Serial.println("\tl -> list current directory");
  Serial.println("\tb -> play song / enter directory");
  Serial.println("\ts -> stop song");
  Serial.println("\tp -> pause song");
  Serial.println("\tr -> resume song");
  Serial.println("\te -> exit current directory\n");
}

int startSong(char* song_name) {
  if (! musicPlayer.startPlayingFile(song_name)) {
    Serial.println("Could not start song: \n");
//    while (1);
  }
  sys_state = 1;
  return sys_state;
}

void list_current_directory() {
  File dir = SD.open(curr_dir);
  int idx = 0;
  while(true) {
    File entry = dir.openNextFile();
    if (!entry) {
      break;
    }
    Serial.print(String(idx) + ": ");
    if (entry.isDirectory()) {
      Serial.print("/");
    }
    Serial.println(entry.name());
    entry.close();
    idx++;
  }
}

void play_song() {
  Serial.println("Test");
  int num = 2;
  File dir = SD.open(curr_dir);
  Serial.println(curr_dir);
  File entry;
  for(int i = 0; i <= num; i++) {
    entry = dir.openNextFile();
    if (!entry) {
      Serial.println("No file located at the provided address");
      entry.close();
      break;
    }
    if (i != num) {
      entry.close();
    }
  }
  Serial.println(curr_dir);
  Serial.println(entry.name());
  Serial.println(strlen(entry.name()));
  if (entry.isDirectory()) {
    char* arr = entry.name();
    while(*curr_dir != '9') {
      *curr_dir = *curr_dir + 1;
    }
    for (int j = 0; j <= strlen(arr); j++) {
      *curr_dir = arr[j];
      *curr_dir = *curr_dir + 1;
    }
    *curr_dir = '9';
  }
  entry.close();
  Serial.println("Hi");
  Serial.println(curr_dir);
}

void exit_current_directory() {
  
}

/// File listing helper
void printDirectory(File dir, int numTabs) {
   while(true) {
     
     File entry =  dir.openNextFile();
     if (! entry) {
       // no more files
       //Serial.println("**nomorefiles**");
       break;
     }
     for (uint8_t i=0; i<numTabs; i++) {
       Serial.print('\t');
     }
     Serial.print(entry.name());
     if (entry.isDirectory()) {
       Serial.println("/");
       printDirectory(entry, numTabs+1);
     } else {
       // files have sizes, directories do not
       Serial.print("\t\t");
       Serial.println(entry.size(), DEC);
     }
     entry.close();
   }
}
