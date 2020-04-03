# Arduino MP3 Player
### Alex Bahner and Daniel Connolly
#### Goal
We planned to make an MP3 player using an Arduino, along the lines of this project: https://www.youtube.com/watch?v=UodfePdNfg8. The linked project uses an SD card reader, arduino, and simple circuit elements to create an MP3 player that can read MP3 files and play them over a speaker via an Arduino. We intended to begin our project by building a module similar to this before extending further. Our initial extension included an LCD screen capable of displaying the song currently playing, and potentially other songs in the current playlist. We view this project as easily extensible in the realms of display capabilities and/or digital signal processing. A stretch goal for this project would be to make a hardware system on a breadboard that does all the same features of a basic MP3 player. Depending on our progress at the beginning of the project and how long it takes to acquire parts, we may use the SD card readers built into our computer and learn how to process, modify, and output audio files to an Arduino or audio.

#### Learning Goals
Our learning goals include gaining a deeper understanding of the C language and its interaction with the Arduino specifically. We hope to gain some embedded systems experience in the process as well.

#### Results
We set out to create an Arduino MP3 player. In the end, we built a module similar to the one we linked in the goals section with the ability to read MP3 files from an SD card and play them via a headphone jack before extending further. After completing this initial module, we added in the ability to create different playlists to allow users to more easily navigate through all of the songs they had loaded onto the SD card. Additionally, we improved upon the functionality of the push buttons in the linked project by adding in new capabilities. Finally, we developed an LCD screen extension capable of displaying the song currently playing along with several other songs in the current playlist. To reiterate, some of the functionalities of our project include the following:

1. The ability to start, stop, and play songs through the use of push buttons.

2. Display capabilities, allowing users to view the song currently playing as well as several other songs in the current directory.

3. Navigation through the playlists (directories) on the SD card with either the serial monitor or push buttons.

##### Design Decision

##### Implementation Details

One key feature of our MP3 player is the ability to navigate through playlists on the SD card. Below, we show how we create the playlists in our `setPlaylist()` function:
```
void setPlaylist() {
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
    entry.close();
    idx++;
    maxSongs++;
  }
  for (int i =0; i< idx; i++) {
     Serial.println(myPlaylist[i])
  };
 }
```
After opening up the directory, we iterate through it, creating an array of all of the songs in the playlist. It is important that we allocate space on the heap to store the location and name of the function in our array with the `strdup()` function, which calls `malloc()` in the background. With this playlist setup, we can navigate through and play various songs with our push button and Arduino MP3 player. This data structure provides a simple way for us to track the playlist the user has navigated to at any given time as well as the songs in that playlist without much overhead.

#### Reflection
We were somewhat successful in achieving our personal learning goals. Over the course of our project, we iterated through several implementations of various aspects of our MP3 player in C, debating the pros and cons of each along the way. This workflow allowed us to make progress individually while also contributing to our goal as a team, allowing us to struggle both on our own and as a team with difficult implementation details. Moreover, we both gained valuable experience in simply working with the C language, practicing and refining our skills whenever we worked on the project. Nevertheless, we got off to a somewhat slow start before running into a massive barrier with the Covid-19 pandemic. This disruption not only meant that we could no longer both work with and test our code on the Arduino-MP3-LCD setup, but it also prevented us from investing as much time as we planned on the project as we neared its end. Overall, while we fell short of some our post-MVP goals and are disappointed about how the Covid disruption impacted our project, we both feel we made solid progress towards our learning goals through the project.

##### Possible Extensions
We believe there are many ways to extend the foundation we have built in this project. For instance, we had hoped to dedicate more time to signal processing capabilities, like the ability to fade in and out from one song to the next. Moreover, we think that we could have turned this into a more intensive EE project by focusing on designing all of the hardware for an MP3 player on our own, perhaps even with a custom PCB. Finally, we can easily see an extension wherein one uses a more advanced LCD screen and designs more interesting graphics for the MP3 player, perhaps even with animations and art (like an album cover) to represent each song.

#### Resources
Throughout the course of this project, we found the following resources useful:

Purdue Computer Science Project Listen/JListen: https://www.cs.purdue.edu/homes/apm/listen.html

U8Glib graphics library documentation: https://github.com/olikraus/u8glib/wiki

Nokia 5110 LCD Screen Menu Example: http://educ8s.tv/arduino-nokia-5110-menu/

The project off which our initial idea was based: https://www.youtube.com/watch?v=UodfePdNfg8

GFX library documentation: https://github.com/adafruit/Adafruit-GFX-Library
