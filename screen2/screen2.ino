#include "U8glib.h"

U8GLIB_PCD8544 u8g(13, 11, 10, 9, 8);		// SPI Com: SCK = 13, MOSI = 11, CS = 10, A0 = 9, Reset = 8

void setup() {
}

void print_songs_to_screen(char* s1, char* s2, char* s3, char* s4) {
  u8g.firstPage();
  do {
    u8g.setContrast(128);
    u8g.drawRFrame(0, 0, 84, 11, 1);  // Song 1
    u8g.drawRFrame(0, 12, 84, 23, 1); // Song 2
    u8g.drawRFrame(0, 24, 84, 35, 1); // Song 3
    u8g.drawRFrame(0, 36, 84, 48, 1);  // Song 4
    u8g.setFont(u8g_font_7x14);
    u8g.drawStr(1, 10, s1);
    u8g.drawStr(1, 22, s2);
    u8g.drawStr(1, 34, s3);
    u8g.drawStr(1, 47, s4);
  } while( u8g.nextPage() );
}

void loop() {
  char* song1 = "Renegade";
  char* song2 = "Roar";
  char* song3 = "Firestone";
  char* song4 = "Mexicana en lele";

  print_songs_to_screen(song1, song2, song3, song4);
  delay(250);
}
