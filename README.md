# MFCMediaPlayer ![built](https://img.shields.io/badge/build-completed-green) ![Development](https://img.shields.io/badge/development-pause-yellow)

MFCMediaPlayer is an application that allows users to open video or audio files and play them. The application is built mainly on the provided APIs.

## Application Structure
MFCMediaPlayer consists of 3 main dialogs:

Controller Dialog: Information Display, Application Control.

![image](https://github.com/EnnHnahK/MFCMediaPlayer/assets/93930691/c2a9241a-188e-4b87-947c-599559212816)

Playlist Dialog: Media list has been added.

![image](https://github.com/EnnHnahK/MFCMediaPlayer/assets/93930691/c2567264-1d2e-46ca-a1bc-0b7447b3c176)

Video Dialog: Video Screen.

![image](https://github.com/EnnHnahK/MFCMediaPlayer/assets/93930691/17ac1f5c-416c-4fbd-a997-d05656ae37ff)


## Usage
MFCMediaPlayer provides 7 basic buttons and 2 controller sliders:
### Button
- [Open]: Open a media file.
- [Pause]: Pause/Resume media.
- [Play]: Play media.
- [Stop]: Stop media.
- [Close]: Close the application.
- [PlayList]: Open Playlist Dialog (More files can be added here)
- [>>]: Move 15s.
### Slider
- [Time Slider]: Fast forward or rewind media.
- [Volume Slider]: Volume controller (Default value is 0).

## Install
**Attention**: Please link below libraries in this project before Debug.
- strmiids.lib.
- strmbasd.lib.
- winmm.lib (Available in Visual Code versions)


If you have the first 2 libraries available, you can link by: 

      Right click on Project -> Properties -> Linker -> Input -> Additional Dependencies. 
      
Here you need to change the path only to the above 2 libraries. If you don't have the above 2 libraries don't worry, you can find these 2 libraries in the project inside the **lib** folder.
