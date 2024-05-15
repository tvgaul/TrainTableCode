# TrainTableCode
At home I have a HO scale train table that I work on with my older brother. We wanted to add more interesting parts to it. To do so we added an Arduino nano to control various LED throughout the train table and a small .96 in LCD screen.

The LEDs are as follows:
Fire LEDs: we have a burning building and this causes the fire to flicker realstically
Witch's Hut LED: there is a small cabin in some woods that randomly flickers green as if a witch is casting a spell in it
Water Tower LED: there is a single LED on top of a water tower we wanted to have blink
Ghost LED: there is a ghost train conductor on the table and this LED fads in and out

Finally as mentioned earlier there is a small LCD screen. This screen projects its image onto a peice of plastic to look ghostlike image. This is placed in at the end of a mineshaft which is the 3d files included in the poject. The arduino needs to get image data from the SD card. These images are BMP files that need to be changed from GBR format to RBG. Most of the images are from scooby doo that we loved watching as kids as a easter egg.

All this hardware was put on a custom PCB with an arduino nano but the hardware design files were lost.