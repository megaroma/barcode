#include <sys/ioctl.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <termios.h>
#include <sys/time.h>
#include "screen.h" 

long getMicrotime(){
	struct timeval currentTime;
	gettimeofday(&currentTime, NULL);
	return currentTime.tv_sec * (int)1e6 + currentTime.tv_usec;
}

int mygetch ( void ) 
{
  int ch;
  struct termios oldt, newt;
  
  tcgetattr ( STDIN_FILENO, &oldt );
  newt = oldt;
  newt.c_lflag &= ~( ICANON | ECHO );
  tcsetattr ( STDIN_FILENO, TCSANOW, &newt );
  ch = getchar();
  tcsetattr ( STDIN_FILENO, TCSANOW, &oldt );
  
  return ch;
}

void clearScreen()
{
	system("@cls||clear");
}

void printHeader(int w, const char *text) {
	int total,i;
	total = strlen(text);
    printf("╔═══[");
    printf("%s]" , text);
    for(i=0;i< w -7 - total;i++){
        printf("═");
    }
    printf("╗");
    putchar('\n');		
}

void printFooter(int w) {
	int i;
    printf("╚");
    for(i=0;i< w - 2;i++){
        printf("═");
    }
    printf("╝");
    putchar('\n');		
}


void printLine(int w, const char *text) {
	int total,i;
	total = strlen(text);
    printf("║  ");
    printf("%s" , text);
    for(i=0;i< w -4 - total;i++){
        printf(" ");
    }
    printf("║");
    putchar('\n');	
}

void printMessageLine(int w, const char *reason) {
	char *message;
	int total,i;
	message = strstr(reason,"\"message\":");
	total = strlen(message) - 2 - 11;
    printf("║  ");
    printf("%.*s",total, message + 11);
    for(i=0;i< w -4 - total;i++){
        printf(" ");
    }
    printf("║");
    putchar('\n');	
}

void printCenterText(int w,int l, const char *text) {
	int space,i;
    printf("║");
    space = (w - 2 - l) / 2;
    for(i=0;i< space;i++){
        printf(" ");
    }
    printf("%s",text);
    space = w - 2 - l - space;
    for(i=0;i< space;i++){
        printf(" ");
    }
    printf("║");    
}

void readyScreen() {
	int i;
	struct winsize w;
	ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);
	clearScreen();
	printf(ANSI_COLOR_WHITE);
	printf(ANSI_BGCOLOR_BLUE);

	printHeader(w.ws_col,"Status");
	printLine(w.ws_col," ");
	printLine(w.ws_col," "); 
	printLine(w.ws_col," ");

	printCenterText(w.ws_col,29, "█████ █████ █████ ████  █   █");	
	printCenterText(w.ws_col,29, "█   █ █     █   █ █   █ █   █");	
	printCenterText(w.ws_col,29, "█████ ████  █████ █   █ █████");	
	printCenterText(w.ws_col,29, "█  █  █     █   █ █   █     █");	
	printCenterText(w.ws_col,29, "█   █ █████ █   █ ████  █████");	

	printLine(w.ws_col," ");
	printLine(w.ws_col," "); 
	printLine(w.ws_col," ");

	printFooter(w.ws_col);


	printf(ANSI_BGCOLOR_BLACK);
	printHeader(w.ws_col,"Message");
	printLine(w.ws_col," ");
	printLine(w.ws_col," "); 
	printLine(w.ws_col," ");
	printLine(w.ws_col," ");
	printLine(w.ws_col," ");
	printLine(w.ws_col," ");
	printLine(w.ws_col," ");
	printFooter(w.ws_col);

	printHeader(w.ws_col,"Action");
    printLine(w.ws_col," ");
    printLine(w.ws_col," Begin Scan");
    printLine(w.ws_col," ");
    printLine(w.ws_col," ");
    printLine(w.ws_col," ");
    printLine(w.ws_col," ");

	printFooter(w.ws_col);

	printf(ANSI_COLOR_RESET);
}

void sendingScreen(const char *cart_id) {
	int i;
	struct winsize w;
	char buff[200];

	ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);
	clearScreen();
	printf(ANSI_COLOR_WHITE);
	printf(ANSI_BGCOLOR_BLUE);
	snprintf(buff, sizeof buff,"  Sending Cart ID - %s", cart_id);

	printHeader(w.ws_col,"Status");
	printLine(w.ws_col," ");
	printLine(w.ws_col," "); 
	printLine(w.ws_col," ");

	printCenterText(w.ws_col,29, "█████ █████ █████ ████  █   █");	
	printCenterText(w.ws_col,29, "█   █ █     █   █ █   █ █   █");	
	printCenterText(w.ws_col,29, "█████ ████  █████ █   █ █████");	
	printCenterText(w.ws_col,29, "█  █  █     █   █ █   █     █");	
	printCenterText(w.ws_col,29, "█   █ █████ █   █ ████  █████");	

	printLine(w.ws_col," ");
	printLine(w.ws_col," "); 
	printLine(w.ws_col," ");

	printFooter(w.ws_col);


	printf(ANSI_BGCOLOR_BLACK);
	printHeader(w.ws_col,"Message");
	printLine(w.ws_col," ");
	printLine(w.ws_col,buff); 
	printLine(w.ws_col," ");
	printLine(w.ws_col," ");
	printLine(w.ws_col," ");
	printLine(w.ws_col," ");
	printLine(w.ws_col," ");
	printFooter(w.ws_col);



	printHeader(w.ws_col,"Action");


    printLine(w.ws_col," ");
    printLine(w.ws_col," ...");
    printLine(w.ws_col," ");
    printLine(w.ws_col," ");
    printLine(w.ws_col," ");
    printLine(w.ws_col," ");

	printFooter(w.ws_col);

	printf(ANSI_COLOR_RESET);

}


void successScreen(const char *cart_id) {

	int i;
	struct winsize w;
	char buff[200];

	ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);
	clearScreen();
	printf(ANSI_COLOR_BLACK);
	printf(ANSI_BGCOLOR_GREEN);
	snprintf(buff, sizeof buff," Cart ID - %s", cart_id);


	printHeader(w.ws_col,"Status");
	printLine(w.ws_col," ");
	printLine(w.ws_col," "); 
	printLine(w.ws_col," ");

	printCenterText(w.ws_col,41, "█████ █   █ █████ █████ █████ █████ █████");	
	printCenterText(w.ws_col,41, "█     █   █ █     █     █     █     █    ");	
	printCenterText(w.ws_col,41, "█████ █   █ █     █     ████  █████ █████");	
	printCenterText(w.ws_col,41, "    █ █   █ █     █     █         █     █");	
	printCenterText(w.ws_col,41, "█████ █████ █████ █████ █████ █████ █████");	

	printLine(w.ws_col," ");
	printLine(w.ws_col," "); 
	printLine(w.ws_col," ");

	printFooter(w.ws_col);

	printf(ANSI_COLOR_WHITE);
	printf(ANSI_BGCOLOR_BLACK);
	printHeader(w.ws_col,"Message");
	printLine(w.ws_col," ");
	printLine(w.ws_col,buff); 
	printLine(w.ws_col," ");
	printLine(w.ws_col," ");
	printLine(w.ws_col," ");
	printLine(w.ws_col," ");
	printLine(w.ws_col," ");
	printFooter(w.ws_col);


	printHeader(w.ws_col,"Action");


    printLine(w.ws_col," ");
    printLine(w.ws_col," ");
    printLine(w.ws_col," ");
    printLine(w.ws_col," ");
    printLine(w.ws_col," ");
    printLine(w.ws_col," ");

	printFooter(w.ws_col);

	printf(ANSI_COLOR_RESET);

}


void errorScreen(const char *cart_id,const char *reason) {

	int i;
	struct winsize w;
	char buff[200];


	ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);
	clearScreen();
	printf(ANSI_COLOR_BLACK);
	printf(ANSI_BGCOLOR_RED);
	snprintf(buff, sizeof buff,"Cart ID - %s", cart_id);

	printHeader(w.ws_col,"Status");
	printLine(w.ws_col," ");
	printLine(w.ws_col," "); 
	printLine(w.ws_col," ");

	printCenterText(w.ws_col,35, "█████ █████ █████ █     █████ ████ ");	
	printCenterText(w.ws_col,35, "█     █   █   █   █     █     █   █");	
	printCenterText(w.ws_col,35, "████  █████   █   █     ████  █   █");	
	printCenterText(w.ws_col,35, "█     █   █   █   █     █     █   █");	
	printCenterText(w.ws_col,35, "█     █   █ █████ █████ █████ ████ ");	

	printLine(w.ws_col," ");
	printLine(w.ws_col," "); 
	printLine(w.ws_col," ");

	printFooter(w.ws_col);

	printf(ANSI_COLOR_WHITE);
	printf(ANSI_BGCOLOR_BLACK);
	printHeader(w.ws_col,"Message");
	printLine(w.ws_col," ");
	printLine(w.ws_col,buff); 
	printMessageLine(w.ws_col,reason);
	printLine(w.ws_col," ");
	printLine(w.ws_col," ");
	printLine(w.ws_col," ");
	printLine(w.ws_col," ");
	printFooter(w.ws_col);




	printHeader(w.ws_col,"Action");

    printLine(w.ws_col," ");
    printLine(w.ws_col," Press Any key to Continue");
    printLine(w.ws_col," ");
    printLine(w.ws_col," ");
    printLine(w.ws_col," ");
    printLine(w.ws_col," ");

	printFooter(w.ws_col);

	printf(ANSI_COLOR_RESET);
	//getchar();
	system("aplay sound.wav");
	mygetch(); 
}

void testScreen(const char *cart_id,const char *reason) {

	struct winsize w;
	ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);
	clearScreen();






/*
	printCenterText(w.ws_col,35, "█████ █████ █████ █     █████ ████ ");
	printCenterText(w.ws_col,35, "█     █   █   █   █     █     █   █");
	printCenterText(w.ws_col,35, "████  █████   █   █     ████  █   █");
	printCenterText(w.ws_col,35, "█     █   █   █   █     █     █   █");
	printCenterText(w.ws_col,35, "█     █   █ █████ █████ █████ ████ ");
*/


}