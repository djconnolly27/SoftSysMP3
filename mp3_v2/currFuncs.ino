

/*
 *  this func right now plays a song we hit i switch make in the main loop 
*/
void play_song() {
  Serial.println("Test");
//  int num = 4;
//  File dir = SD.open(curr_dir);
//  Serial.println(curr_dir);
//  File entry = dir.openNextFile();
//  entry = dir.openNextFile();

//   if (! musicPlayer.startPlayingFile("/HAPPYM~1.MP3")) {
//    Serial.println("Could not open file happymaybe.mp3");
//    while (1);
//  }
  
   if (! musicPlayer.startPlayingFile(myPlaylist[currSong])) {
    Serial.println("Could not open file !!!");
    while (1);
  }
  
  Serial.println("song passed");
  Serial.println(myPlaylist[currSong]);

  //Serial.println(F("Started playing"));
//  Serial.println(entry.name());
  //delay(10000);
}

/*
 * 
 */
void setPlaylist(){
  File dir = SD.open(curr_dir);
  int idx = 0;
  while(true) {
    File entry = dir.openNextFile();
    if (!entry) {
      break;
    }
    char testscurr[20];
    strcpy(testscurr, curr_dir);
    strcat(testscurr, entry.name());
    myPlaylist[idx] = strdup(testscurr);
    //for (int i =0; i< idx; i++) Serial.println(myPlaylist[i]);
    entry.close();
    idx++;
    maxSongs++;
  }
  for (int i =0; i< idx; i++) Serial.println(myPlaylist[i]);
 } 

 
 /**/
void currDirSetup(){
  File dir = SD.open(curr_dir);
  Serial.println(curr_dir);
  File entry = dir.openNextFile();
  entry = dir.openNextFile();
  char testcurr[20];
  strcpy(testcurr, curr_dir);
  strcat(testcurr, entry.name());
  Serial.print("Updated   :"); 
  Serial.println(testcurr);
  strcat(curr_dir, entry.name());
  Serial.println(curr_dir);
  }
/*
*/
void currDirForward(){
  Serial.println("forward");
  if(currSong < maxSongs){
    currSong++;
    }  
  Serial.println(myPlaylist[currSong]);
  delay(100);
  play_song();
  }

void currDirBackward(){
  Serial.println("Back");
  if(currSong > 0){
    currSong--;
    }  
  Serial.println(myPlaylist[currSong]);
  delay(100);
  play_song();
  }

  
