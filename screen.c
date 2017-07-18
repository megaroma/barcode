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
	    printf(ANSI_COLOR_BLACK  );

printf(ANSI_BGCOLOR_CYAN);

	printHeader(w.ws_col,"Status");


    printLine(w.ws_col," ");
    printLine(w.ws_col," ");

    printLine(w.ws_col,"Scanner");
    printLine(w.ws_col,"Ready");

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
	    printf(ANSI_COLOR_BLACK  );

printf(ANSI_BGCOLOR_CYAN);

	printHeader(w.ws_col,"Status");


    printLine(w.ws_col," ");
    printLine(w.ws_col," ");

    printLine(w.ws_col,"Scanner");

    snprintf(buff, sizeof buff,"Sending Cart ID - %s", cart_id);

    printLine(w.ws_col,buff);

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
	    printf(ANSI_COLOR_BLACK  );

printf(ANSI_BGCOLOR_GREEN);

	printHeader(w.ws_col,"Status");


    printLine(w.ws_col," ");
    printLine(w.ws_col," ");

    printLine(w.ws_col,"Scan");
    printLine(w.ws_col,"Successful");

    snprintf(buff, sizeof buff,"Cart ID - %s", cart_id);

    printLine(w.ws_col,buff);

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
	    printf(ANSI_COLOR_BLACK  );

printf(ANSI_BGCOLOR_RED);

	printHeader(w.ws_col,"Status");


    printLine(w.ws_col," ");
    printLine(w.ws_col," ");

    printLine(w.ws_col,"Scan");
    printLine(w.ws_col,"Failed");

    snprintf(buff, sizeof buff,"Cart ID - %s", cart_id);

    printLine(w.ws_col,buff);

    printLine(w.ws_col,reason);

    printLine(w.ws_col," ");

    printf("╚══[Press ENTER key to Continue]");
    for(i=0;i< w.ws_col - 33;i++){
        printf("═");
    }
    printf("╝");
    putchar('\n');
printf(ANSI_COLOR_RESET);

	getchar(); 
}
