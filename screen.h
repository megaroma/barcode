#ifndef DDSCREEN_LIB_
#define DDSCREEN_LIB_

#define ANSI_COLOR_BLACK     "\x1b[30m"
#define ANSI_COLOR_RED     "\x1b[31m"
#define ANSI_COLOR_GREEN   "\x1b[32m"
#define ANSI_COLOR_YELLOW  "\x1b[33m"
#define ANSI_COLOR_BLUE    "\x1b[34m"
#define ANSI_COLOR_MAGENTA "\x1b[35m"
#define ANSI_COLOR_CYAN    "\x1b[36m"
#define ANSI_COLOR_WHITE    "\x1b[37m"
#define ANSI_COLOR_RESET   "\x1b[0m"
#define ANSI_BGCOLOR_BLACK     "\x1b[40m"
#define ANSI_BGCOLOR_RED     "\x1b[41m"
#define ANSI_BGCOLOR_GREEN   "\x1b[42m"
#define ANSI_BGCOLOR_YELLOW  "\x1b[43m"
#define ANSI_BGCOLOR_BLUE    "\x1b[44m"
#define ANSI_BGCOLOR_MAGENTA "\x1b[45m"
#define ANSI_BGCOLOR_CYAN    "\x1b[46m"
#define ANSI_BGCOLOR_WHITE    "\x1b[47m"
#define ANSI_BRIGHT  "\x1b[1m"



void clearScreen();
void printHeader(int w, const char *text);
void printFooter(int w);
void printLine(int w, const char *text);
void readyScreen();
void sendingScreen(const char *cart_id);
void successScreen(const char *cart_id);
void errorScreen(const char *cart_id,const char *reason);
void testScreen(const char *cart_id,const char *reason);

#endif 