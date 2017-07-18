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
	    printf(ANSI_COLOR_WHITE  );

printf(ANSI_BGCOLOR_BLUE);

	printHeader(w.ws_col,"Status");


    printLine(w.ws_col," ");
    printLine(w.ws_col," ");

    printLine(w.ws_col,"Scanner");
    printLine(w.ws_col,"Ready");

    printLine(w.ws_col," ");
    printLine(w.ws_col," ");

    printFooter(w.ws_col);
printf(ANSI_COLOR_RESET);

}