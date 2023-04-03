/* 
	$ssdlinux: tcpdwl.c,v 1.2 2003/04/08 08:27:23 kanoh Exp $

tcp download program for OpenBlockS 50 Micro Linux Server.
run this program to update Micro Linux Server's Flash ROM.

usage: tcpdwl [-v] ip_address download_filename 

   option
     -v display the progress of TCP downloader.

This program is distributed in the hope that it will be useful,
but without any warranty; Please use this program at your own risk. 
The author disclaims responsibility for any damages that might 
result from the use of this program, even if they result from 
negligence on the part of the author. This program should be replaced
by ftp or tftp program in the future. -- Century Systems Inc. 
                                                           2000.7.24
*/

#include <arpa/inet.h>
#include <netdb.h>
#include <netinet/in.h>
#include <stdio.h>
#include <sys/socket.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>
#include <signal.h>

#define IDLE             0x00000001
#define SWITCH           0x00000002
#define SPECIFY          0x00000003
#define STARTDOWN        0x00000004
#define DOWNLOAD         0x00000005
#define FINISHED         0x00000006

/* #define BASE_ADDRESS     0x88888888   beginning of server memory address  */

#define DEFAULT_PORT     "2222"     /* default port number. do NOT change*/    
#define DEFAULT_RUNFILE  "tcpdwl"    //  default executable file name 

#define FLASH_SIZE	     (0x10000 * 31)
#define BUFF_SIZE        0x400
#define TRUE             1
#define FALSE            0

//  define the normal messages

#define NORMAL_MESSAGE_BEGIN         "Changing into download mode..."  // Message number 1
#define NORMAL_MESSAGE_IF_START      "Ready  to start ? (y or n)  "       // Message number 2
#define NORMAL_MESSAGE_IN_PROGRESS   "Now sending 64K..."                 // Message number 3
#define NORMAL_MESSAGE_END           "Complete!"                       // Message number 4

#define DISPLAY_INIT_MESSAGE       1
#define DISPLAY_READY_MESSAGE      2
#define DISPLAY_PROGRESS_MESSAGE   3
#define DISPLAY_END_MESSAGE        4

  

struct sockaddr_in server;
unsigned long State, FileSize, Inc;
int SentFlag;
int DisplayFlag;
unsigned char *fary;
FILE *f1, *f2;
int fd_dl;
char buffer[BUFF_SIZE];
unsigned long highest_address;
unsigned long base_address;
int sock;
char DLFile[128];
unsigned char FileBuf[1024]; // Download Data Array Frame Size
unsigned char RBuf[8];
char display_end_bytes[20];
 
void TestMode();
void SwitchMode();
void StartDownLoad();

long jhtoi(char *s);
int jfgets();
int mprocess(char *pnt);
int ConvertFile(char *FileNameToConvert, char *NewFileName);

int ChooseDLFile(char *pFile, char *pDLFile);
void DownLoad();
void Dl_tcp();
void show(int num);




int main(int argc, char **argv) 
{

  char *pcHostIP;
  char *pcHostPort;
  char *pcFileName;
  char *pcDisplayMode;

  struct hostent *hp;
  struct in_addr inaddr;
  unsigned short port;
  int result;
  char def_port[5] = DEFAULT_PORT; 	
  char startFlag;
  
  struct   sigaction ignorehd;
  struct   sigaction defaulthd;
  
  /* Two parameters are needed in this program */ 

  DisplayFlag = 0;
  if (argc == 3){
    pcHostIP = argv[1]; 
    pcFileName = argv[2];
  }else if (argc == 4) {
    pcDisplayMode = argv[1]; 
    pcHostIP = argv[2];
    pcFileName = argv[3];
	if ((pcDisplayMode[1] == 'v') || (pcDisplayMode[1] == 'V')){
	    DisplayFlag = 1;	
	}else{
		printf("\n%s: usage error \nUsage: %s [-v] ip_address download_filename\n",DEFAULT_RUNFILE, DEFAULT_RUNFILE);
		printf("      -v display the progress of TCP downloader.\n");
		exit(-1);
	}
  }else{
    printf("\n%s: usage error \nUsage: %s [-v] ip_address download_filename\n",DEFAULT_RUNFILE, DEFAULT_RUNFILE);
    printf("      -v display the progress of TCP downloader.\n");
    exit(-1);
  }
  pcHostPort = def_port;  //  default value

  
  show(DISPLAY_INIT_MESSAGE);   //  display the start message
  //  if it is ready to start, type 'y' or type 'n' to exit.
  show(DISPLAY_READY_MESSAGE);

  if ((DisplayFlag) && (((startFlag = getchar()) == 'n') || ((startFlag = getchar()) == 'N'))){
    printf("\n%s: The TCP downloader exits by user's commmand.\n\n\n", DEFAULT_RUNFILE);
    exit(0);	  
  }
  
  /*  choose the download file */
  fary = (unsigned char *)malloc(FLASH_SIZE); 
  if (ChooseDLFile(pcFileName, DLFile) < 0){
      free(fary);	  
	  exit(-1);	
  }
 
  State = IDLE;

 // set up the handlers for prompt and default
  ignorehd.sa_handler = SIG_IGN;
  sigemptyset(&ignorehd.sa_mask);
  ignorehd.sa_flags = 0;
  defaulthd.sa_handler = SIG_DFL;
  sigemptyset(&defaulthd.sa_mask);
  defaulthd.sa_flags = 0;

  if ((sigaction(SIGINT, &ignorehd, NULL) < 0) ||
      (sigaction(SIGQUIT, &ignorehd, NULL) < 0)){
  
    printf("\n%s: Failed to install signal handlers\n", DEFAULT_RUNFILE);
    free(fary);	  
    exit(-1);
  
  } 

  sock = socket(PF_INET,SOCK_STREAM,0); /* Open a socket */
  
  if (sock < 0 ) {
    printf("\n%s: Error Opening socket \n", DEFAULT_RUNFILE);
    free(fary);	  
    exit(-1);
  }

  /* Copy the resolved information into the sockaddr_in structure */
  
  memset(&server,0,sizeof(server));

  server.sin_family = AF_INET;
  port = atoi(pcHostPort);
  server.sin_port = htons(port);
  server.sin_addr.s_addr = inet_addr(pcHostIP);

  if (server.sin_addr.s_addr == INADDR_NONE){
    printf("\n%s: Cannot resolve address [%s]\n", DEFAULT_RUNFILE, pcHostIP);
    free(fary);	  
    exit(-1);
  }

  if (connect(sock,(struct sockaddr *) &server, sizeof(server))){
    printf("\n%s: Cannot connect with server [%s] \n", DEFAULT_RUNFILE, pcHostIP);
    free(fary);	  
    exit(-1);
  }
  
  Dl_tcp();

  if ((sigaction(SIGINT, &defaulthd, NULL) < 0) ||
      (sigaction(SIGQUIT, &defaulthd, NULL) < 0)){
  
    printf("\n%s: Cannot restore default handlers\n", DEFAULT_RUNFILE);
    free(fary);	  
    exit(-1);
  
  } 
  	
  free(fary);	  
	
}

int jfgets()
{
	long i, j;
	char temp;

	for(i = 0, j = sizeof(buffer) - 1; j > 0; j--) {
		temp = fgetc(f1);
		if(temp != (char)EOF) {
			if((temp == '\n') || (temp == '\t') ||
				(temp == '\r')) {
				buffer[i++] = '\0';
				break;
			}
			else {
				buffer[i++] = temp;
			}
		}
	}
	if(i > 0) {
		return(i);
	}
	else {
		return(0);
	}
}
long jhtoi(char *s)
{
	int n;

	n = 0;
	while(*s != '\0') {
		if(*s >= '0' && *s <= '9') {
			n = (0x10 * n) + (*s++ - '0');
		}
		else if(*s >= 'a' && *s <= 'f') {
			n = (0x10 * n) + (*s++ - 'W');
		}
		else if(*s >= 'A' && *s <= 'F') {
			n = (0x10 * n) + (*s++ - '7');
		}
		else {
			break;
		}
	}
	return(n);

}
int mprocess(char *pnt)
{
		long byte_count;
		unsigned long address;
		char tbuff[BUFF_SIZE];
		char *fpnt;
		unsigned char cdata;
		
		printf("\n mprocess: buffer = %s\n",buffer);		
		// Check to see if first character is 'S'
		if(pnt[0] != 'S') {
			return(-1);
		}

		// Throw away S0, S7, S8, and S9 records
		switch(pnt[1]) {
			case	'0'	:
			case	'7'	:
			case	'8'	:
			case	'9'	:	return(0); break;
			// Error on S4, S5 and S6 records
			case	'4'	:
			case	'5'	:
			case	'6'	:	return(-2); break;
			// Process S1, S2, and S3 recores
			case	'1'	:
			case	'2'	:
			case	'3'	:	break;
			// Anything else, error
			default		:	return(-3); break;
		}

		// Got here, must be a good line
		// Get the byte count from pnt[2] and pnt[3]
		tbuff[0] = pnt[2];
		tbuff[1] = pnt[3];
		tbuff[2] = 0x00;

		// Convert to int
		byte_count = jhtoi(tbuff);
		printf("mprocess byte count %08X %d\n", byte_count, byte_count);

		// Now get the address, 3 forms, S1 (4 bytes), S2 (6 bytes), and S3 (8 bytes)
		switch(pnt[1]) {
			case	'1'	:	tbuff[0] = pnt[4];
							tbuff[1] = pnt[5];
							tbuff[2] = pnt[6];
							tbuff[3] = pnt[7];
							tbuff[4] = 0x00;
							fpnt	 = &pnt[8];
							byte_count -= 3;	// 2 for address, 1 for checksum
							break;

			case	'2'	:	tbuff[0] = pnt[4];
							tbuff[1] = pnt[5];
							tbuff[2] = pnt[6];
							tbuff[3] = pnt[7];
							tbuff[4] = pnt[8];
							tbuff[5] = pnt[9];
							tbuff[6] = 0x00;
							fpnt	 = &pnt[10];
							byte_count -= 4;	// 3 for address, 1 for checksum
							break;
			default		:	tbuff[0] = pnt[4];
							tbuff[1] = pnt[5];
							tbuff[2] = pnt[6];
							tbuff[3] = pnt[7];
							tbuff[4] = pnt[8];
							tbuff[5] = pnt[9];
							tbuff[6] = pnt[10];
							tbuff[7] = pnt[11];
							tbuff[8] = 0x00;
							byte_count -= 5;	// 4 for address, 1 for checksum
							fpnt	 = &pnt[12];
							break;
		}

		// Convert to int
		address = jhtoi(tbuff);
		
		// cal the highest_address
		highest_address = address + byte_count;

		// Now convert the address to an offset
		
		base_address = address;      /*  added by sou  */ 
		
		address -= base_address;	// base address of the FLASH

		if(address < 0 || address > FLASH_SIZE) 
		{
			return(-4);
		}
		if(address < 0) 
		{
			return(-4);
		}
		
		while(byte_count > 0) {
			// Nov convert data and write in the memory array
			// tpnt address was setup in the above case statement
			tbuff[0] = *fpnt++;
			tbuff[1] = *fpnt++;
			tbuff[2] = 0x00;
	
			// Now convert the data
			cdata = (unsigned char) jhtoi(tbuff);
			// Now write to memory array
			fary[address++] = cdata;
			byte_count--;
		}

		// Got here, no errors
		return(0);
}


int ConvertFile(char *FileNameToConvert, char *NewFileName)
{
	int i, j, quit, r_code;


	if((f1 = fopen(FileNameToConvert, "rt")) == NULL) {
		printf("\n%s: Can't open input file [%s] \n", DEFAULT_RUNFILE, FileNameToConvert);
		return (-1);
	}
	
	if((f2 = fopen(NewFileName, "wb")) == NULL) {
		printf("\n%s: Can't open output file [%s] \n", DEFAULT_RUNFILE, NewFileName);
		fclose(f1);
		return (-1);
	}

	// clear the array
	for(i = 0, j = sizeof(fary); j > 0; i++, j--) {
		fary[i] = 0x00;
	}
	quit = 0;
	do {
		// Get one line at a time and process
		r_code = jfgets();
		if(r_code != 0) {
			r_code = mprocess(buffer);
			if(r_code == 0) {
				;
			}
			else {
				printf("\n%s: Download ERROR, r_code = %d \n", DEFAULT_RUNFILE, r_code);
				fclose(f1);
				fclose(f2);
				return (-1);
			}
		}
		else {
			r_code = fwrite(fary, sizeof(char), highest_address - base_address, f2);
			quit = 1;
		}
	} while(quit == 0);

	fclose(f1);
	fclose(f2);
	return (0);

}


int ChooseDLFile(char *pFile, char *pDLFile)
{
  char str_img[5] = ".img";
  char str_mot[5] = ".mot";
  char file[9] = "inter.img";
  char *p_ext;
  int  fd;
  char buf[5];
  char NewFileName[128];
  struct stat sbuf;

  int n;
  int ret;

  unsigned char jumpaddr[17] = {  0x3c, 0x00, 0x00, 0x21,
                                  0x60, 0x00, 0x00, 0x00,
                                  0x7c, 0x08, 0x03, 0xa6,
                                  0x4e, 0x80, 0x00, 0x20 };
   
  if ((fd = open(pFile, O_RDONLY)) < 0){
    printf("\n%s: No such file [%s] \n", DEFAULT_RUNFILE, pFile);
    return -1;
  }
  strcpy(NewFileName, pFile);
  p_ext = strstr(NewFileName, str_mot);
  if ((p_ext != NULL) && (strlen(p_ext) == 4)){ 
             /* if it has the file extension "mot"*/
             /* 4 is the number of the rest chars from dot '.' */
             /* convert it to "img" */

     strcpy(p_ext, str_img);
	 ret = ConvertFile(pFile, NewFileName);
	 if (ret < 0){
         return -1;   
	 }
	 strcpy(pDLFile, NewFileName); 

  }else if (strcmp(pDLFile, file) != 0){ /* if it is not  the file "inter.img"*/
    strcpy(pDLFile, pFile);
	if ((fd = open(pDLFile, O_RDONLY)) < 0){
      printf("\n%s: Can't open file [%s] \n", DEFAULT_RUNFILE, pDLFile);
      return -1;
    }
    n = read(fd, buf, 4);
    if (n != 4){
      printf("\n%s: Read error [%s] \n", DEFAULT_RUNFILE, pDLFile);
      close(fd);
      return -1;
    }
    else
      buf[n] = '\0';
    close(fd);
    if ((buf[0] == 0x7F) &&
        (buf[1] == 0x45) &&
	    (buf[2] == 0x4C) &&
	    (buf[3] == 0x46)){
      if  ((fd = open(pDLFile, O_WRONLY)) < 0){
          printf("\n%s: Can't open file [%s] \n", DEFAULT_RUNFILE, pDLFile);
	      return -1;
      }
      lseek(fd, 0x100, SEEK_SET);
      write(fd, jumpaddr, 16);
      close(fd);
    }

  }else{
	strcpy(pDLFile, pFile);	
  }
  		
  ret = stat(pDLFile, &sbuf);	
  if (ret != 0){
      printf("\n%s: Function error [stat()] \n", DEFAULT_RUNFILE);
	  return -1;
  }else{
      FileSize = sbuf.st_size;
  }
  return 0;
}

void TestMode()
{

  unsigned char SInq[8]={0x51,0x21,0x0,0x0,0x0,0x0,0x0,0x0};
  int retval; 
  // printf("Linux TestMode\n");
  retval = write(sock, SInq, sizeof(SInq));
  if (retval < 0) {
    printf("\n%s: Function error [write()] \n", DEFAULT_RUNFILE);
  }

}

void SwitchMode()
{
	unsigned char chgMode[8]={0x51,0x20,'S','W','I','T','C','H'};
    int retval; 
	// printf(" Linux SwitchMode\n");

	State = SWITCH;
    retval = write(sock, chgMode, sizeof(chgMode));
    if (retval < 0) {
    printf("\n%s: Function error [write()] \n", DEFAULT_RUNFILE);
	}
}


void StartDownLoad()
{
    int retval; 
	unsigned char StartDown[8];
	StartDown[0] = 0x51;
	StartDown[1] = 0x22;
	StartDown[2] = (unsigned char)((FileSize & 0xFF000000) >> 24);
	StartDown[3] = (unsigned char)((FileSize & 0x00FF0000) >> 16);
	StartDown[4] = (unsigned char)((FileSize & 0x0000FF00) >> 8);
	StartDown[5] = (unsigned char)(FileSize & 0x000000FF);
	StartDown[6] = 0x00;
	StartDown[7] = 0x00;

	State = STARTDOWN;
	SentFlag = FALSE;
    retval = write(sock, StartDown, sizeof(StartDown));
    if (retval < 0) {
        printf("\n%s: Function error [write()] \n", DEFAULT_RUNFILE);
	}


}

void DownLoad()
{
	// Read the down load file
	// and send the read part
	unsigned long sFileBuf;
	static unsigned long position = 0;
	int retval;

	for (Inc = 0; Inc < 64; Inc++)
	{
		memset(FileBuf,0x00,sizeof(FileBuf));
        sFileBuf = read(fd_dl, FileBuf,sizeof(FileBuf));

        retval = write(sock, FileBuf, sFileBuf);
		if (retval < 0) {
	        printf("send() error\n");
			break;
		}
        position = position + sFileBuf;
		if (position >= FileSize)
		{
			sprintf(display_end_bytes,"Now sending %ldK + %ld bytes", Inc, sFileBuf);
			SentFlag = TRUE;
			break;
		}
	}
	show(DISPLAY_PROGRESS_MESSAGE);
	return;
}
void Dl_tcp()
{
	unsigned short rec_code;
	unsigned short Err_Tst;
	int sRec;

	unsigned char RInq1[8]={0x52,0x05,0x1,0x0,0x0,0x0,0x0,0x0};
	unsigned char RInq2[8]={0x52,0x05,0x0,0x1,0x0,0x0,0x0,0x0};
	unsigned char RInq3[8]={0x52,0x05,0x2,0x0,0x0,0x0,0x0,0x0};
	unsigned char RInq4[8]={0x52,0x05,0x0,0x2,0x0,0x0,0x0,0x0};
	unsigned char RInq5[8]={0x52,0x05,0x3,0x0,0x0,0x0,0x0,0x0};
	unsigned char chgMode[8]={0x51,0x20,'S','W','I','T','C','H'};
	unsigned char StillRec[50];

    TestMode();
	for (;;){
		sRec = read(sock, RBuf,sizeof(RBuf));	
		rec_code = ntohs(*(unsigned short*)(&RBuf[0]));

		if (sRec == 8)
		{
			if (rec_code == 0x5203)	
			{
				if (State == SWITCH)
				{
					/* Switching into download mode*/
					/* Close connection  */
					
					
					shutdown(sock, SHUT_RDWR);
					close(sock);
					/* Wait for the server */
					sleep(3);
    				sock = socket(PF_INET,SOCK_STREAM,0); /* Open a socket */
  				    if (sock < 0 ) {
                        printf("\n%s: Error Opening socket \n", DEFAULT_RUNFILE);
					    return;
					}
					if (connect(sock,(struct sockaddr *) &server, sizeof(server))){
                        printf("\n%s: Cannot connect with server in switch mode\n", DEFAULT_RUNFILE);
						return;
					}
					TestMode();
					continue;
					
				}
				else if (State == STARTDOWN)
				{
					/* Start download command sent */
					/* Open the down load file     */
					State = DOWNLOAD;
					if ((fd_dl = open(DLFile, O_RDONLY)) < 0){
                      printf("\n%s: Can't open file [%s] \n", DEFAULT_RUNFILE, DLFile);
					  break;
					}
					DownLoad();
					continue;
				}
				else if (State == DOWNLOAD)
				{
					/* Check the report and sector bytes */
					if (SentFlag)
					{
						/* This was the last acknowledge  */
						/* Close the connection   */
						close(fd_dl);
						break;
					}
					else
					{
						DownLoad();
						continue;
					} 
				}
				else
				{
					/* Error inform user and terminate  */
					printf("\n%s: Error state \n", DEFAULT_RUNFILE);
					break;
				}
			}
			else if (rec_code == 0x5206)	
			{
				Err_Tst = *((unsigned short *)(&RBuf[2]));
				Err_Tst = ntohs(Err_Tst);
				if (Err_Tst&0x8000)	/* command error   */
				{
					printf("\n%s: Error in command state \n", DEFAULT_RUNFILE);
					break;
				}
				else if (Err_Tst&0x0020)	/* download bytes error  */
				{
					printf("\n%s: Error in download bytes \n", DEFAULT_RUNFILE);
					break;
				}
				else if (Err_Tst&0x0010)	/* dial-in dial-out error  */
				{
					printf("\n%s: Dial-in dial-out error \n", DEFAULT_RUNFILE);
					break;
				}
				else if (Err_Tst&0x0008)	/* telnet error  */
				{
					printf("\n%s: Telnet error \n", DEFAULT_RUNFILE);
					break;
				}
				else if (Err_Tst&0x0004)	/* flash ROM erase error  */
				{
					printf("\n%s: Flash ROM erase error \n", DEFAULT_RUNFILE);
					break;
				}
				else if (Err_Tst&0x0002)	/* download in progress  */
				{
					printf("\n%s: Download in progress \n", DEFAULT_RUNFILE);
					break;
				}
				else if (Err_Tst&0x0001)	/* flash ROM write error  */
				{
					printf("\n%s: Flash ROM write error \n", DEFAULT_RUNFILE);
					break;
				}
				else 
				{
					printf("\n%s: Other errors \n", DEFAULT_RUNFILE);
					break;
				}
			}
			else if (rec_code == 0x5205)	
			{
				/* Return code from TestMode  */
				if ((memcmp(RBuf,RInq1,sizeof(RInq1))==0) || 
					(memcmp(RBuf,RInq2,sizeof(RInq2))==0))
				{
					/* Normal mode         */
					/* switch to download  */
					SwitchMode();
					continue;
				}
				else if ((memcmp(RBuf,RInq3,sizeof(RInq3))==0) || 
					     (memcmp(RBuf,RInq4,sizeof(RInq4))==0) || 
						 (memcmp(RBuf,RInq5,sizeof(RInq5))==0))
				{
					/* Download mode    */
					/*   Begin download / if appropriate  */
					StartDownLoad();
					continue;
				}
				else
				{
					// Error inform user and terminate
					printf("\n%s: Error state \n", DEFAULT_RUNFILE);
					break;
				}
			}
			else
			{
				printf("\n%s: Error state \n", DEFAULT_RUNFILE);
				break;
			}
		}
		else
		{
			printf("\n%s: Error record from server \n", DEFAULT_RUNFILE);
			break;
		}
	}
	shutdown(sock, SHUT_WR);
	while((sRec = read(sock, StillRec,sizeof(StillRec))) > 0);
    close(sock);
}

void show(int num)
{
	
	if (DisplayFlag){
		switch (num){
		case 1:
		    printf("\n%s: %s\n", DEFAULT_RUNFILE, NORMAL_MESSAGE_BEGIN);  
			break;
		case 2:
		    printf("\n%s: %s ", DEFAULT_RUNFILE, NORMAL_MESSAGE_IF_START);  
			break;
		case 3:
			if (SentFlag){
				printf("\n%s: %s\n", DEFAULT_RUNFILE, display_end_bytes);  
			    printf("\n%s: Download Complete! \n\n\n", DEFAULT_RUNFILE);
			}else{
				printf("\n%s: %s\n", DEFAULT_RUNFILE, NORMAL_MESSAGE_IN_PROGRESS);  
			}
			break;
		case 4:
		    printf("\n%s: %s\n", DEFAULT_RUNFILE, NORMAL_MESSAGE_END);  
			break;
		default:
			break;
		}
	}
}
