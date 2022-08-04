/*
  ----TABELLE ALLGEMEIN----
  ADR. HEX DEZ
  6804 4D ; 80 SPALTEN (spalten-3)
  6805 0F ; 24 ZEILEN (zeilen-1)
  6806 00 ; ZEITKONSTANTE FUER HOME
  6807 00

  ----TABELLE AUSGABE-WERTE----
  ADRESSE HEX
  6808 08 ; (OUT)-CURSOR LINKS
  6809 09 ; " " RECHTS
  680A 0A ; " " UNTEN
  680B 0B ; " " OBEN .
  680C 0C ; LOESCHE BILDSCHIRM (HOME)
  680D 12 ; LOESCHEN ZEILENREST
  680E 00 ;  + CARRIAGE RETURN
  680F 0D ; CARRIAGE-RETURN (OHNE LOESCHEN DES ZEILENRESTS)

  ----TABELLE EINGABE-WERTE----
  ADRESSE HEX BEZ                             TASTE
  6810 08 ; CURSOR LINKS                      CURSOR LINKS
  6811 09 ; CURSOR RECHTS                     CURSOR RECHTS
  6812 0A ; CURSOR UNTEN                      CURSOR UNTEN
  6813 0B ; CURSOR OBEN                       CURSOR OBEN
  6814 0D ; CARRIAGE-RETURN                   RETURN
  6815 15 ; CTRL-U = SEITE UNTEN              BILD UNTEN
  6816 0F ; CTRL-O = SEITE OBEN               BILD OBEN
  6817 05 ; CTRL-E = EINFUEGEN EIN/AUS        EINFUEGEN
  6818 12 ; CTRL-R = RADIERE ZEICHEN          ENTFERNEN
  6819 7F ; DEL = DELETE ZEICHEN              DELETE
  681A 1A ; CTRL-Z = ZEILEN-BEFEHLE
  681B 14 ; CTRL-T = TABULATOR                TABULATOR
  68IC 03 ; CTRL-C = ERWEITERTE CURSOR-BEFEHLE
            CTRL_CA = CURSOR ZUM TEXTANFANG   POS1
            CTRL_CE = CURSOR ZUM TEXTANFANG   ENDE
  68ID 17 ; CTRL-W = CURSOR NAECHSTES WORT
  681E 0E ; CTRL-N = NEUSTART
  681F 18 ; CTRL-X = HILFS-MENUE
  6820 01 ; CTRL-A = ASSEMBLIEREN
  6821 04 ; CTRL-D = DRUCKER-MENUE
  6822 06 ; CTRL-F = FIND-MODUS
  6823 02 ; CTRL-B = BLOCK-BEFEHLE
  6824 13 ; CTRL-S = SICHERN
*/

#include "MFA.h"
#define LED_RX PB0
#define LED_TX PD5

void setup() {
  pinMode(LED_BUILTIN, OUTPUT);
  pinMode(LED_RX, OUTPUT);
  pinMode(LED_TX, OUTPUT);

  Serial.begin(9600);
  while (!Serial);

  Serial.println(F(__FILE__));
  Serial.println(F(__TIME__));
  Serial.println(F(__DATE__));
  Serial.println("");

  Serial.print("Open MFA connection ...");
  Serial1.begin(9600);
  while (!Serial1);
  Serial.println("iO");
  Serial.println("");

  digitalWrite(LED_BUILTIN, HIGH);
}

void loop() {

  if (Serial1.available()) {
    MAT_To_PuTTY();
  } else {
    PuTTY_To_MAT();

    // vintage hardware delay
    if (Serial.available() && !Serial1.available()) {
      delay(15);
    }
  }
}

void MAT_To_PuTTY() {
  // Serial1 (pins 0 & 1)
  if (Serial1.available()) {
    digitalWrite(LED_TX, HIGH);
    char c_serial1 = Serial1.read();

    // ----TABELLE AUSGABE-WERTE----
    switch (c_serial1) {
      case BS:  // 08 ; CURSOR LINKS
        Serial.print(VT_CURSOR_LEFT);
        break;
      case TAB: // 09 ; CURSOR RECHTS
        Serial.print(VT_CURSOR_RIGHT);
        break;
      case LF:  // 0A ; CURSOR UNTEN
        // normal LF here, for scrolling
        Serial.write(LF);
        Serial.print(VT_FOREGROUND_DEFAULT);
        break;
      case VT:  // 0B ; CURSOR OBEN
        Serial.print(VT_CURSOR_UP);
        break;
      case FF:  // 0C ; LOESCHE BILDSCHIRM (HOME)
        Serial.print(ESC_FF);
        break;
      case DC2:  // 12 00 ; LOESCHEN ZEILENREST + CARRIAGE-RETURN
        // only Cursor, prevents scrolling
        Serial.print(VT_CLR_LINE_AFTER_CURSOR);
        Serial.print(VT_CURSOR_CR);
        c_serial1 = Serial1.read(); // discard 2nd command byte
        break;
      case CR:  // 0D ; CARRIAGE-RETURN (OHNE LOESCHEN DES ZEILENRESTS)
        // normal CR
        Serial.write(CR);
        break;
        
      case ';':  // comment begin
        Serial.print(VT_FOREGROUND_GREEN);
        Serial.write(c_serial1);
        break;
      case '<':  // comment begin
        Serial.print(VT_FOREGROUND_GREEN);
        Serial.write(c_serial1);
        Serial.print(VT_FOREGROUND_DEFAULT);
        break;
      case '>':  // comment begin
        Serial.print(VT_FOREGROUND_GREEN);
        Serial.write(c_serial1);
        Serial.print(VT_FOREGROUND_DEFAULT);
        break;
        
      default:  // nothing special, just pass through
        Serial.write(c_serial1);
        break;
    }
  }
  digitalWrite(LED_TX, LOW);
}

void PuTTY_To_MAT() {
  // Serial (USB)
  if (Serial.available()) {
    digitalWrite(LED_RX, HIGH);
    char c_serial [4];

    c_serial[0] = Serial.read();  // ESC
    if (c_serial[0] == ESC) {
      // ESC sequence
      c_serial[1] = Serial.read();  // ESC[
      if (c_serial[1] == '[') {
        // ESC[
        c_serial[2] = Serial.read();

        // ----TABELLE EINGABE-WERTE----
        switch (c_serial[2]) {
          case 'A':                       // ESC[A "Cursor up"
            Serial1.write(VT);            // 0B ; CURSOR OBEN
            break;
          case 'B':                       // ESC[B "Cursor down"
            Serial1.write(LF);            // 0A ; CURSOR UNTEN
            break;
          case 'C':                       // ESC[C "Cursor right"
            Serial1.write(TAB);
            break;
          case 'D':                       // ESC[D "Cursor left"
            Serial1.write(BS);
            break;
          case '1':                       // ESC[1^ "Pos1"
            Serial1.write(CTRL_C);        // CTRL-C = ERWEITERTE CURSOR-BEFEHLE
            Serial1.write('A');           // CTRL_CA = CURSOR ZUM TEXTANFANG
            c_serial[3] = Serial.read();  // discard ^
            break;
          case '2':                       // ESC[2^ "Einfügen"
            Serial1.write(CTRL_E);        // CTRL-E = EINFUEGEN EIN/AUS
            c_serial[3] = Serial.read();  // discard ^
            break;
          case '3':                       // ESC[3^ "Entfernen"
            Serial1.write(CTRL_R);        // CTRL-R = RADIERE ZEICHEN
            c_serial[3] = Serial.read();  // discard ^
            break;
          case '4':                       // ESC[4^ "Ende"
            Serial1.write(CTRL_C);        // CTRL-C = ERWEITERTE CURSOR-BEFEHLE
            Serial1.write('E');           // CTRL_CE = CURSOR ZUM TEXTANFANG
            c_serial[3] = Serial.read();  // discard ^
            break;
          case '5':                       // ESC[5^ "Seite Oben"
            Serial1.write(CTRL_O);        // CTRL-O = SEITE OBEN
            c_serial[3] = Serial.read();  // discard ^
            break;
          case '6':                       // ESC[6^ "Seite Unten"
            Serial1.write(CTRL_U);        // CTRL-U = SEITE UNTEN
            c_serial[3] = Serial.read();  // discard ^
            break;
          default:
            // ESC[ , but following char isn't special, so, just pass through
            Serial1.write(c_serial[0]);
            Serial1.write(c_serial[1]);
            Serial1.write(c_serial[2]);
            break;
        }

      } else {
        // ESC without '['
        // nothing to do, pass through
        Serial1.write(c_serial[0]);
        Serial1.write(c_serial[1]);
      }

    } else {
      // normal transmission
      switch (c_serial[0]) {
        case TAB: // exchange TAB-key '0x09' with CTRL_T
          Serial1.write(CTRL_T);
          break;
        default:
          // no interrest in that, at all
          Serial1.write(c_serial[0]);
          break;
      }
    }
  }
  digitalWrite(LED_RX, LOW);
}
