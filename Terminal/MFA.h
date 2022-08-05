
#define NUL 0x00  // null
#define SOH 0x01  // start of heading
#define STX 0x02  // start of text
#define ETX 0x03  // end of text
#define EOT 0x04  // end of transmission
#define ENQ 0x05  // enquiry
#define ACK 0x06  // acknowledge
#define BEL 0x07  // bell
#define BS  0x08  // backspace        cursor left
#define TAB 0x09  // horizontal tab   cursor right
#define LF  0x0A  // line feed        cursor down
#define VT  0x0B  // vertical tab     cursor up
#define FF  0x0C  // form feed        home
#define CR  0x0D  // carriage return  
#define SO  0x0E  // shift out
#define SI  0x0F  // shift in

#define DLE 0x10  // data line escape  
#define DC1 0x11  // device control 1
#define DC2 0x12  // device control 2
#define DC3 0x13  // device control 3
#define DC4 0x14  // device control 4
#define NAK 0x15  // negative acknowledge
#define SYN 0x16  // synchronous idel
#define ETB 0x17  // end of xmit block
#define CAN 0x18  // cancel
#define EM  0x19  // end of medium
#define SUB 0x1A  // substitute
#define ESC 0x1B  // escape
#define FS  0x1C  // file separator
#define GS  0x1D  // group seperator
#define RS  0x1E  // record seperator
#define US  0x1F  // unit seperator
#define SP  0x20  // space
#define DEL 0x7F  // delete

#define CTRL_@  0x00
#define CTRL_A  0x01
#define CTRL_B  0x02
#define CTRL_C  0x03
#define CTRL_D  0x04
#define CTRL_E  0x05
#define CTRL_F  0x06
#define CTRL_G  0x07
#define CTRL_H  0x08
#define CTRL_I  0x09
#define CTRL_J  0x0A
#define CTRL_K  0x0B
#define CTRL_L  0x0C
#define CTRL_M  0x0D
#define CTRL_N  0x0E
#define CTRL_O  0x0F

#define CTRL_P  0x10
#define CTRL_Q  0x11
#define CTRL_R  0x12
#define CTRL_S  0x13
#define CTRL_T  0x14
#define CTRL_U  0x15
#define CTRL_V  0x16
#define CTRL_W  0x17
#define CTRL_X  0x18
#define CTRL_Y  0x19
#define CTRL_Z  0x1A
//  #define CTRL_[  0x1B
//  #define CTRL_\  0x1C
//  #define CTRL_]  0x1D
//  #define CTRL_^  0x1E
//  #define CTRL__  0x1F


// ESC[C == "\x1b[C" == "\e[C" 

//General
#define ESC_BEL   "\a"  // Terminal Bell
#define ESC_BS    "\b"  // Backspace
#define ESC_TAB   "\t"  // Horizontal TAB
#define ESC_LF    "\n"  // Linefeed
#define ESC_VT    "\v"  // Vertical TAB
#define ESC_FF    "\f"  // Formfeed (new Page)
#define ESC_CR    "\r"  // Carriage Return

//Cursor
#define VT_CURSOR_OFF       "\e[?25l"
#define VT_CURSOR_ON        "\e[?25h"
#define VT_CURSOR_HOME      "\e[H"
#define VT_CURSOR_SAVE      "\e7"
#define VT_CURSOR_RESTORE   "\e8"
#define VT_CURSOR_UP        "\e[A"
#define VT_CURSOR_DOWN      "\e[B"
#define VT_CURSOR_RIGHT     "\e[C"
#define VT_CURSOR_LEFT      "\e[D"
#define VT_CURSOR_CR        "\e[G"

//Erasing
#define VT_CLR_LINE_AFTER_CURSOR    "\e[K"
#define VT_CLR_LINE_TO_CURSOR       "\e[1K"
#define VT_CLR_LINE                 "\e[2K"
#define VT_CLR_SCREEN               "\e[2J"
#define VT_CLR_ALL                  "\e[1;1H\e[2J"

//Text colors
#define VT_FOREGROUND_BLACK     "\e[30m"
#define VT_FOREGROUND_RED       "\e[31m"
#define VT_FOREGROUND_GREEN     "\e[32m"
#define VT_FOREGROUND_YELLOW    "\e[33m"
#define VT_FOREGROUND_BLUE      "\e[34m"
#define VT_FOREGROUND_MAGNETA   "\e[35m"
#define VT_FOREGROUND_CYAN      "\e[36m"
#define VT_FOREGROUND_WHITE     "\e[37m"
#define VT_FOREGROUND_DEFAULT   "\e[39m"
