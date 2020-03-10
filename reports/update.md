# MP3 Player
### Alex Bahner and Daniel Connolly
#### Goal
We plan to make an MP3 player using an Arduino, along the lines of this project: https://www.youtube.com/watch?v=UodfePdNfg8. The linked project uses an SD card reader, arduino, and simple circuit elements to create an MP3 player that can read MP3 files and play them over a speaker via an Arduino. We intend to begin our project by building a module similar to this before extending further. Our initial extension will include an LCD screen capable of displaying the song currently playing, and potentially other songs in the current playlist. We view this project as easily extensible in the realms of display capabilities and/or digital signal processing. A stretch goal for this project would be to make a hardware system on a breadboard that does all the same features of a basic MP3 player. Depending on our progress at the beginning of the project and how long it takes to acquire parts, we may use the SD card readers built into our computer and learn how to process, modify, and output audio files to an Arduino or audio.

#### Learning Goals
Our learning goals include gaining a deeper understanding of the C language and its interaction with the Arduino specifically. We hope to gain some embedded systems and signal processing experience in the process as well.

We are currently looking into different parts and have reviewed a variety of similar open-source projects online. The project seem to be easy scalable.

#### Status
Thus far, we have:

1. Ordered and received parts through the ECE stockroom. Because these parts were crucial to our progress, we had to wait to start until they came in to really get going with our project.

2. We wired up the main VS10538 Audio board we ordered and headphone jack and tested the setup with starter code. We were able to make our system play an audio file we loaded onto the SD card through the headphone jack on our headphones.

3. We investigated several libraries to use for our project. We ultimately settled on the Adafruit_VS1053 library that is built to work with the VS10538 board, the SD library for reading files from the SD card, the SPI library for communicating via the serial peripheral interface protocol with the breakout board, and the PCD8544 library for interfacing with the LCD screen. We plan to add any additional libraries we need as we continue to add to our project.

4. We added push buttons to our setup in order to start playing a song via push buttons.

5. We began to work on code that takes commands from the serial monitor in order to navigate through the directories on the SD card.

#### Next Steps
Our next steps include:

1. We intend to start working on manipulating the LCD screen to display songs in the current directory of the SD card. This task will be complete when we can use push buttons to scroll through a list of songs and select the one we want to play, with their titles being displayed on the screen.

2. We plan to add more button functionality. For instance, we will add buttons that can pause, un-pause, and stop songs. This task will be complete when these three functionalities work. We may choose to add more after.

3. We expect to be able navigate through different directories, which will be considered playlists, on the SD card. This task will be complete when we can switch between at least two directories on the SD card and play songs in each.

#### Additional Information
To see more about the current status of our project, you can visit our [Trello](https://trello.com/b/o5gpMv3L/mp3) or our [Github](https://github.com/djconnolly27/SoftSysMP3).
