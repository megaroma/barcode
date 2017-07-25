#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <string.h>
#include <time.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <dirent.h>
#include <fcntl.h>
#include <linux/input.h>
#include <signal.h>
#include <stdbool.h>
#include "screen.h"

#define DEBUG_OUT true

#define VENDORID 0x05f9
#define PRODUCTID 0x221c
#define SCN_BCD_SZ 15

void handler(int sig)
{
    printf(ANSI_COLOR_RESET);
    printf("\nBye.\n");
    exit(0);
}




int scan_fd = -1;
long last_scan_time = 0;


int initScanner(){
	int count;
	char path[32];
	struct dirent **files;
	struct input_id id;

	count = scandir("/dev/input", &files, NULL, alphasort);
	while( count>0 ){
		count--;
		if( scan_fd==-1 && strncmp(files[count]->d_name,"event",5)==0 ){
  			sprintf(path,"/dev/input/%s",files[count]->d_name);
            if(DEBUG_OUT) {
                printf("Checking %s \n",path);
            }
  			scan_fd = open(path,O_RDONLY);
  			if( scan_fd>=0 ){
    			if( ioctl(scan_fd,EVIOCGID,(void *)&id)<0 ) {
      				perror("ioctl EVIOCGID");
    			}
    			else{
      				if( id.vendor==VENDORID && id.product==PRODUCTID ) {
        				printf("scanner attached to %s\n",path);
      				} else{
                        if(DEBUG_OUT) {
                            printf("It is not a scanner %d:%d\n",id.vendor, id.product);
                        }
        				close(scan_fd);
        				scan_fd = -1;
      				}
    			}
  			} else{
    			fprintf(stderr,"Error opening %s",path);
    			perror("");
			}
		}
		free(files[count--]);
	}
	free(files);

	if( scan_fd>=0 ) ioctl(scan_fd,EVIOCGRAB);
	else{ printf(ANSI_COLOR_RED  "scanner not found or couldn't be opened" ANSI_COLOR_RESET "\n"); return 0;}
	return 1;
}


int closeScanner(){
	close(scan_fd);
	scan_fd = -1;
	return 1;
}


char keycodelist(int scancode){
char ret = '-';
//return (unsigned char)scancode;
switch(scancode){
case 0x02: ret ='1';break;
case 0x03: ret ='2';break;
case 0x04: ret ='3';break;
case 0x05: ret ='4';break;
case 0x06: ret ='5';break;
case 0x07: ret ='6';break;
case 0x08: ret ='7';break;
case 0x09: ret ='8';break;
case 0x0a: ret ='9';break;
case 0x0b: ret ='0';break;
case 0x0c: ret ='-';break;

case 0x10: ret ='q';break;
case 0x11: ret ='w';break;
case 0x12: ret ='e';break;
case 0x13: ret ='r';break;
case 0x14: ret ='t';break;
case 0x15: ret ='y';break;
case 0x16: ret ='u';break;
case 0x17: ret ='i';break;
case 0x18: ret ='o';break;
case 0x19: ret ='p';break;

case 0x1e: ret ='a';break;
case 0x1f: ret ='s';break;
case 0x20: ret ='d';break;
case 0x21: ret ='f';break;
case 0x22: ret ='g';break;
case 0x23: ret ='h';break;
case 0x24: ret ='j';break;
case 0x25: ret ='k';break;
case 0x26: ret ='l';break;

case 0x2c: ret ='z';break;
case 0x2d: ret ='x';break;
case 0x2e: ret ='c';break;
case 0x2f: ret ='v';break;
case 0x30: ret ='b';break;
case 0x31: ret ='n';break;
case 0x32: ret ='m';break;
default: break;
}
return ret;
}



char* readScanner(int *loopcond){
    static char barcode[SCN_BCD_SZ];
    char code[SCN_BCD_SZ];
    int i=0;
    struct input_event ev;

    while( loopcond==NULL?1:*loopcond ){
        read(scan_fd,&ev,sizeof(struct input_event));
        if( ev.type==1 && ev.value==1 ){
            if( ev.code==28 ){ //carriage return
                printf("Carriage Return Read \n");
                code[i] = 0;
                strcpy(barcode,code);
                return barcode;
            } else{
                if( ev.code!=0 ){
                    code[i++] = keycodelist(ev.code);
                    //printf("Char: %i-%i \n", keycodelist(ev.code), ev.code);
                    if( i==SCN_BCD_SZ-1 ){ 
	                   printf("Barcode buffer full\n"); 
	                   return NULL;
                    }
                }
            }
        }
    }
    return NULL;
}



void send_http(const char *bar_code) {

	int portno = 80;
	//char *host = "localhost";
	//char *message_fmt = "GET /test.php?code=%s HTTP/1.0\r\n\r\n";
	//"GET / HTTP/1.1\r\nHost: %s\r\n\r\n";
	//http://fcvpn.impactfax.com/pactel/ipics/ipics_label_print.php
	char *host = "fcvpn.impactfax.com";
	char *message_fmt = "GET /pactel/ipics/ipics_label_print.php?action=print&code=%s HTTP/1.1\r\nHost: %s\r\n\r\n";


 

    struct hostent *server;
    struct sockaddr_in serv_addr;
    int sockfd, bytes, sent, received, total;
    char message[1024],response[4096];
    char *response_body;


    sprintf(message,message_fmt,bar_code,host);


    /* create the socket */
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd < 0) { 
    	errorScreen(bar_code,"ERROR opening socket\n");
    	return;
    }

    /* lookup the ip address */
    server = gethostbyname(host);
    if (server == NULL) {
    	errorScreen(bar_code,"ERROR, no such host\n");
    	return;
    }

    /* fill in the structure */
    memset(&serv_addr,0,sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(portno);
    memcpy(&serv_addr.sin_addr.s_addr,server->h_addr,server->h_length);

    /* connect the socket */
    if (connect(sockfd,(struct sockaddr *)&serv_addr,sizeof(serv_addr)) < 0) {
        errorScreen(bar_code,"ERROR connecting\n");
        return;
    }

    /* send the request */
    total = strlen(message);
    sent = 0;
    do {
        bytes = write(sockfd,message+sent,total-sent);
        if (bytes < 0) {
            errorScreen(bar_code,"ERROR writing message to socket\n");
            return;
        }
        if (bytes == 0)
            break;
        sent+=bytes;
    } while (sent < total);

    /* receive the response */
    memset(response,0,sizeof(response));
    total = sizeof(response)-1;
    received = 0;
    do {
        bytes = read(sockfd,response+received,total-received);
        if (bytes < 0){
            errorScreen(bar_code,"ERROR reading response from socket\n");
            return;
        }
        if (bytes == 0)
            break;
        received+=bytes;
    } while (received < total);

    if (received == total) {
        errorScreen(bar_code,"ERROR storing complete response from socket\n");
        return;
    }

    /* close the socket */
    close(sockfd);

    response_body = strstr(response, "\r\n\r\n");

    if(strstr(response_body, ":2,") != NULL) {
        errorScreen(bar_code,response_body);
        last_scan_time = getMicrotime();
   	} else {
   		successScreen(bar_code);
        sleep(2);
        last_scan_time = getMicrotime();
   	}

    //printf("Response Body:\n%s\n",response_body);


}



int main(int argc, char* argv[]) {


    long cur_scan_time;

    signal (SIGTERM, handler);
    signal (SIGINT, handler);
	char bar_code[200];
	clearScreen();
	printf("Starting\n");
	printf("Connecting to scanner:\n");

	if(initScanner() != 1) {
		exit(1);
	}


	while (1) {
		readyScreen();
		snprintf(bar_code, sizeof bar_code,"%s", readScanner(NULL));
        cur_scan_time = getMicrotime();
        if((cur_scan_time - last_scan_time) > 500000) {
            sendingScreen(bar_code);
		    send_http(bar_code);
        }

	}

}