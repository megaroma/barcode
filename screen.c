#include <sys/ioctl.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include "screen.h" 

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

void readyScreen() {
	int i;
	struct winsize w;
	ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);
	clearScreen();
	printf(ANSI_COLOR_WHITE);
	printf(ANSI_BGCOLOR_BLUE);


	printf(ANSI_BGCOLOR_BLUE "╔═══[Status]══════════════════════════════════╗" ANSI_BGCOLOR_BLACK );printHeader(w.ws_col - 47,"Message");
	printf(ANSI_BGCOLOR_BLUE "║                                             ║" ANSI_BGCOLOR_BLACK );printLine(w.ws_col-47," ");
	printf(ANSI_BGCOLOR_BLUE "║        █████ █████ █████ ████  █   █        ║" ANSI_BGCOLOR_BLACK );printLine(w.ws_col-47," "); 
	printf(ANSI_BGCOLOR_BLUE "║        █   █ █     █   █ █   █ █   █        ║" ANSI_BGCOLOR_BLACK );printLine(w.ws_col-47," ");
	printf(ANSI_BGCOLOR_BLUE "║        █████ ████  █████ █   █ █████        ║" ANSI_BGCOLOR_BLACK );printLine(w.ws_col-47," ");
	printf(ANSI_BGCOLOR_BLUE "║        █  █  █     █   █ █   █     █        ║" ANSI_BGCOLOR_BLACK );printLine(w.ws_col-47," ");
	printf(ANSI_BGCOLOR_BLUE "║        █   █ █████ █   █ ████  █████        ║" ANSI_BGCOLOR_BLACK );printLine(w.ws_col-47," ");
	printf(ANSI_BGCOLOR_BLUE "║                                             ║" ANSI_BGCOLOR_BLACK );printLine(w.ws_col-47," ");
	printf(ANSI_BGCOLOR_BLUE "╚═════════════════════════════════════════════╝" ANSI_BGCOLOR_BLACK );printFooter(w.ws_col-47);



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

	printf(ANSI_BGCOLOR_BLUE "╔═══[Status]══════════════════════════════════╗" ANSI_BGCOLOR_BLACK );printHeader(w.ws_col - 47,"Message");
	printf(ANSI_BGCOLOR_BLUE "║                                             ║" ANSI_BGCOLOR_BLACK );printLine(w.ws_col-47," ");
	printf(ANSI_BGCOLOR_BLUE "║        █████ █████ █████ ████  █   █        ║" ANSI_BGCOLOR_BLACK );printLine(w.ws_col-47,buff); 
	printf(ANSI_BGCOLOR_BLUE "║        █   █ █     █   █ █   █ █   █        ║" ANSI_BGCOLOR_BLACK );printLine(w.ws_col-47," ");
	printf(ANSI_BGCOLOR_BLUE "║        █████ ████  █████ █   █ █████        ║" ANSI_BGCOLOR_BLACK );printLine(w.ws_col-47," ");
	printf(ANSI_BGCOLOR_BLUE "║        █  █  █     █   █ █   █     █        ║" ANSI_BGCOLOR_BLACK );printLine(w.ws_col-47," ");
	printf(ANSI_BGCOLOR_BLUE "║        █   █ █████ █   █ ████  █████        ║" ANSI_BGCOLOR_BLACK );printLine(w.ws_col-47," ");
	printf(ANSI_BGCOLOR_BLUE "║                                             ║" ANSI_BGCOLOR_BLACK );printLine(w.ws_col-47," ");
	printf(ANSI_BGCOLOR_BLUE "╚═════════════════════════════════════════════╝" ANSI_BGCOLOR_BLACK );printFooter(w.ws_col-47);



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

	printf(ANSI_COLOR_BLACK ANSI_BGCOLOR_GREEN "╔═══[Status]══════════════════════════════════╗" ANSI_COLOR_WHITE ANSI_BGCOLOR_BLACK );printHeader(w.ws_col - 47,"Message");
	printf(ANSI_COLOR_BLACK ANSI_BGCOLOR_GREEN "║                                             ║" ANSI_COLOR_WHITE ANSI_BGCOLOR_BLACK );printLine(w.ws_col-47," ");
	printf(ANSI_COLOR_BLACK ANSI_BGCOLOR_GREEN "║  █████ █   █ █████ █████ █████ █████ █████  ║" ANSI_COLOR_WHITE ANSI_BGCOLOR_BLACK );printLine(w.ws_col-47,buff); 
	printf(ANSI_COLOR_BLACK ANSI_BGCOLOR_GREEN "║  █     █   █ █     █     █     █     █      ║" ANSI_COLOR_WHITE ANSI_BGCOLOR_BLACK );printLine(w.ws_col-47," ");
	printf(ANSI_COLOR_BLACK ANSI_BGCOLOR_GREEN "║  █████ █   █ █     █     ████  █████ █████  ║" ANSI_COLOR_WHITE ANSI_BGCOLOR_BLACK );printLine(w.ws_col-47," ");
	printf(ANSI_COLOR_BLACK ANSI_BGCOLOR_GREEN "║      █ █   █ █     █     █         █     █  ║" ANSI_COLOR_WHITE ANSI_BGCOLOR_BLACK );printLine(w.ws_col-47," ");
	printf(ANSI_COLOR_BLACK ANSI_BGCOLOR_GREEN "║  █████ █████ █████ █████ █████ █████ █████  ║" ANSI_COLOR_WHITE ANSI_BGCOLOR_BLACK );printLine(w.ws_col-47," ");
	printf(ANSI_COLOR_BLACK ANSI_BGCOLOR_GREEN "║                                             ║" ANSI_COLOR_WHITE ANSI_BGCOLOR_BLACK );printLine(w.ws_col-47," ");
	printf(ANSI_COLOR_BLACK ANSI_BGCOLOR_GREEN "╚═════════════════════════════════════════════╝" ANSI_COLOR_WHITE ANSI_BGCOLOR_BLACK );printFooter(w.ws_col-47);



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
	snprintf(buff, sizeof buff," Cart ID - %s", cart_id);

	printf(ANSI_COLOR_BLACK ANSI_BGCOLOR_RED "╔═══[Status]══════════════════════════════════╗" ANSI_COLOR_WHITE ANSI_BGCOLOR_BLACK );printHeader(w.ws_col - 47,"Message");
	printf(ANSI_COLOR_BLACK ANSI_BGCOLOR_RED "║                                             ║" ANSI_COLOR_WHITE ANSI_BGCOLOR_BLACK );printLine(w.ws_col-47," ");
	printf(ANSI_COLOR_BLACK ANSI_BGCOLOR_RED "║     █████ █████ █████ █     █████ ████      ║" ANSI_COLOR_WHITE ANSI_BGCOLOR_BLACK );printLine(w.ws_col-47,buff); 
	printf(ANSI_COLOR_BLACK ANSI_BGCOLOR_RED "║     █     █   █   █   █     █     █   █     ║" ANSI_COLOR_WHITE ANSI_BGCOLOR_BLACK );printLine(w.ws_col-47,reason + 4);
	printf(ANSI_COLOR_BLACK ANSI_BGCOLOR_RED "║     ████  █████   █   █     ████  █   █     ║" ANSI_COLOR_WHITE ANSI_BGCOLOR_BLACK );printLine(w.ws_col-47," ");
	printf(ANSI_COLOR_BLACK ANSI_BGCOLOR_RED "║     █     █   █   █   █     █     █   █     ║" ANSI_COLOR_WHITE ANSI_BGCOLOR_BLACK );printLine(w.ws_col-47," ");
	printf(ANSI_COLOR_BLACK ANSI_BGCOLOR_RED "║     █     █   █ █████ █████ █████ ████      ║" ANSI_COLOR_WHITE ANSI_BGCOLOR_BLACK );printLine(w.ws_col-47," ");
	printf(ANSI_COLOR_BLACK ANSI_BGCOLOR_RED "║                                             ║" ANSI_COLOR_WHITE ANSI_BGCOLOR_BLACK );printLine(w.ws_col-47," ");
	printf(ANSI_COLOR_BLACK ANSI_BGCOLOR_RED "╚═════════════════════════════════════════════╝" ANSI_COLOR_WHITE ANSI_BGCOLOR_BLACK );printFooter(w.ws_col-47);



	printHeader(w.ws_col,"Action");


    printLine(w.ws_col," ");
    printLine(w.ws_col," Press ENTER key to Continue");
    printLine(w.ws_col," ");
    printLine(w.ws_col," ");
    printLine(w.ws_col," ");
    printLine(w.ws_col," ");

	printFooter(w.ws_col);

	printf(ANSI_COLOR_RESET);
	getchar(); 
}

void testScreen(const char *cart_id,const char *reason) {

}