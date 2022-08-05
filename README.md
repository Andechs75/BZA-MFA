# BZA-MFA
Vintage 8085 computer for educational purpose

Hi there!
... currently it's just setting up this Git-Hub. A lot of content is under construction.
CMDR Andechs

## Terminal Interface
Arduino Micro VT100 Interface for the MFA and a Terminal program.
- Uses serial pass through between USB at any Serial(TTL-Level) port of the MFA
- Replacement for the Video-Keyboard-Interface
- Supports the original BZA-Editor
- Provides original keyboard-shortcuts
- Modern keyboard use, by macro those keys
- ESC[-sequences (yes, it can colour!)
- Copy-Paste programs between MFA and PC

### Terminal: Preview
![KMD](https://github.com/Andechs75/BZA-MFA/blob/main/Terminal/KMD.png)
![Editor](https://github.com/Andechs75/BZA-MFA/blob/main/Terminal/Editor.png)

### Terminal: Application requirements
- MFA CPU, RAM, ROM, (Serial Card)
- RS232-TTL Level connection (MC1488/89 removed !!) 
- ArduinoMicro
- e.g. PuTTY
- for the BZA-Editor u need to modify the ROM! Nothin hacky! That was original supposed to be a lesson unit ;o) 

### Terminal: Setup hardware
- Remove the Video and Keybord Card.
- Remove the +/-12V driver and receiver. That's the MC1488/89.
- Connect the TTL Rx, Tx, 5V and GND to the Micro D1/Tx, D0/RX, VIN and GND.
- modify the ROM: MAT32kT for Serial Card, MAT32kS for Serial on CPU:
  ![Editor](https://github.com/Andechs75/BZA-MFA/blob/main/Terminal/Rom.png)
  The Editor uses a Key-Table. So we only modify this as it was intended to be modified. 
- Burn the Arduino (TTL, if you remember...)

### Terminal: How to use


## Documents
  Collection of BZA-MFA documents
  ROM-Files
  Some Datasheets you always need for reairs

## Attributions
- [www.oldcomputers-ddns.org](https://oldcomputers-ddns.org/public/pub/rechner/mfa_mikrocomputer_fuer_ausbildung/index.html), origin of the documents-folder.
