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




void exit_current_directory() {
  
}
