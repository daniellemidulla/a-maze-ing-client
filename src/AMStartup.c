/*	AMStartup.c  client side maze 


	Project name: Maze Project
	Component name:  Client startup

	This file contains client side startup to communiate with server
	
	Primary Author:	Pritika Vig
	Date Created:	Aug 2015

	Special considerations:  
		(e.g., special compilation options, platform limitations, etc.) 
	
======================================================================*/

// do not remove any of these sections, even if they are empty
//
// ---------------- Open Issues 

// ---------------- System includes e.g., <stdio.h>
#include <sys/socket.h>				//socket funtions
#include <stdlib.h>           //exit, atoi
#include <stdio.h>            //printf
#include <sys/types.h>
#include <netinet/in.h>
#include <string.h>
#include <arpa/inet.h>
#include <getopt.h>           //getopt_long, struct option
#include <string.h>           //strlen
#include <ctype.h>            //isdigit
#include <errno.h>            // get ip address
#include <netdb.h>            // get ip address
#include <unistd.h>           // close()
#include <time.h>
#include <pthread.h>            //pthread_create

// ---------------- Local includes  e.g., "file.h"

#include "amazing.h"

// ---------------- Constant definitions 

// ---------------- Macro definitions

// ---------------- Structures/Types 

// ---------------- Private variables 

// ---------------- Private prototypes 
int get_ip(char *  , char *);
FILE* initLog(int difficulty, int nAvatars);

/*====================================================================*/


int
main(int argc, char **argv) 
{
	int sockfd;
  struct sockaddr_in servaddr;
	int c;
  int i;
  int nAvatars;
  int difficulty;
  char * hostname;
  char ip[100];
  int MazePort;
  int MazeWidth;
  int MazeHeight;


/////////////////////////////////////////// argument checks ///////////////////////////////////////////////



	static struct option long_options[] =
    {
      {"nAvatars",     required_argument,       0, 'n'},
      {"difficulty",  required_argument,       0, 'd'},
      {"hostname",  required_argument, 0, 'h'},
      {0, 0, 0, 0}
    };
    
  int option_index = 0;
  //Set the necessary variables from the given parameters
  while((c = getopt_long (argc, argv, "n:d:h:", long_options, &option_index)) != -1){  
    /* Break at the end of options */
    switch (c)
      {
      case 0:
        if (long_options[option_index].flag != 0) break;
        
        if (optarg)
          
        printf("\n");
        break;

      // flags: 
      case 'n':
        for(i = 0; i < strlen(optarg); i++){
          if (isdigit(optarg[i]) == 0){
            printf("nAvatars must be a number.\n%s is not a decimal number.\n", optarg);
            exit(EXIT_FAILURE);
          }
        }
        nAvatars = atoi(optarg);
        break;

      case 'd':
        for(i = 0; i < strlen(optarg); i++){
          if (isdigit(optarg[i]) == 0){
            printf("Difficulty must be a number.\n%s is not a decimal number.\n", optarg);
            exit(EXIT_FAILURE);
          }
        }
        difficulty = atoi(optarg);
        break;

      case 'h':
        hostname = optarg;
        break;

      case '?':
        /* getopt_long already printed an error message. */
        break;

      default:
        abort();
      }
    }

    //make sure that all the options were present and that all the necessary variables were set
    // NOTE-We can check that all arguments are present based on argument count,it will check the argument contents first for additional user info and then at the end if there aren't even 4 parameters it will exit. 
    // Also note- when I run it with maze 4 2 pierce.cs.dartmouth.edu, I get back a message complaining about an nAvatars value. 
   
    if(!nAvatars || nAvatars < 1 || nAvatars > AM_MAX_AVATAR){
      printf("There must be between 1 and %d Avatars. You entered: %i\n", AM_MAX_AVATAR, nAvatars);
      exit(EXIT_FAILURE);
    }
    if(!difficulty || (difficulty < 0) || (difficulty > AM_MAX_DIFFICULTY)){
      printf("The difficulty level must be on the scale of 0(easy) to %d(extremely difficult).\n", AM_MAX_DIFFICULTY);
      exit(EXIT_FAILURE);
    }
    if(!hostname || strcmp(hostname, "pierce.cs.dartmouth.edu") != 0){
      printf("The hostname must be pierce.cs.dartmouth.edu.\n");
      exit(EXIT_FAILURE);
    }

    if (argc != 4){
    printf("You don't have the proper number of arguments. Please enter [AVATARS 0-10] [    DIFFICULTY 0-50] [HOST NAME \"pierce.cs.dartmouth.edu\"]\n You entered %d arguments.", argc);
     }
    //////////////////////////////////////////////////////////Socket Stuff///////////////////////////////////////////////////////////

     //Socket  stuff - modelled after code from lecture 23
	   
     // get IP address
      get_ip(hostname, ip);
      printf("\n\n%s resolved to %s\n", hostname, ip);


     //Create a socket for the client
     //If sockfd<0 there was an error in the creation of the socket
     if ((sockfd = socket (AF_INET, SOCK_STREAM, 0)) <0) {
          perror("Problem in creating the socket");
          exit(2);
     }
	
     //Creation of the socket
     memset(&servaddr, 0, sizeof(servaddr));
     servaddr.sin_family = AF_INET;
     servaddr.sin_addr.s_addr= inet_addr(ip);
     servaddr.sin_port =  htons(AM_SERVER_PORT); //convert to big-endian order
	
     //Connection of the client to the socket 
     if (connect(sockfd, (struct sockaddr *) &servaddr, sizeof(servaddr))<0) {
          perror("Problem in connecting to the server");
          exit(3);
     }
	
     // send and recieve stuff here
     // create a message
     AM_Message *init_message = malloc(sizeof(AM_Message));
     if(!init_message){
        perror("No memory\n");
        exit(4);
     }

     printf("Building message\n");
     init_message->type = htonl(AM_INIT);
     init_message->init.nAvatars = htonl(nAvatars);
     init_message->init.Difficulty = htonl(difficulty);
  
     // send init message to server
     send(sockfd, init_message, AM_MAX_MESSAGE, 0);
     free(init_message);

     // recieve AM_INIT_OK <- contains unique mazePort, which is the TCP/IP 
     // port number to communicate with server, server begins listening on the new port immediately
     // INIT message also has mazeWidth and mazeHeight

     // Recvd
     AM_Message *rec_message = malloc(sizeof(AM_Message));
     if(!rec_message){
      perror("\nNo memory");
      exit(4);
     }

      if (recv(sockfd, rec_message, AM_MAX_MESSAGE,0) == 0){
               //error: server terminated prematurely
               perror("The server terminated prematurely"); 
               exit(4);
      }

      printf("\nParsing server reply.");

      // TODO : set global variables from these values? 

      if(ntohl(rec_message->type) == AM_INIT_OK){
        printf("\nReturned AM_INIT_OK");
        MazePort = ntohl(rec_message->init_ok.MazePort);
        MazeWidth = ntohl(rec_message->init_ok.MazeWidth);
        MazeHeight = ntohl(rec_message->init_ok.MazeHeight);

      }
      if(ntohl(rec_message->type) == AM_INIT_FAILED){
        printf("\nInitialization failed.");
        exit(5);
      }
      // use nohtl on message to parse

      free(rec_message);
      

//////////////////////////////////////////////////// Create logfile ///////////////////////////////////////////////////
      

      // start up log file and throw in initial information
      printf("\nCreating logfile - check out log directory for further information on this run.\n\n");
      FILE *pLog = initLog(difficulty, nAvatars);
      fprintf(pLog, "\n\nMazeport: %i", MazePort);
      fprintf(pLog, "\nMaze width: %i", MazeWidth);
      fprintf(pLog, "\nMaze height: %i", MazeHeight);


//////////////////////////////////////////////////////// Start Avatars ////////////////////////////////////////////////////
     

     // TODO : start up N threads/processes running the main client software : input =  avatarID, No of avatars, difficulty, ip address, mazeport, logfile,

     // on exit, stop all thread/processes, free memory, close port, close logfile, exit
     // exit conditions: 
          // an Avatar's socket connection to the server is broken,
          // the maximum number of moves (a function of AM_MAX_MOVES and Difficulty) is exceeded,
          // the server's AM_WAIT_TIME timer expires, or
          // the server determines that all of the Avatars are located at the same (x,y) position, meaning the maze has been solved.
    printf("*******THREADS*******");
    //Allocate N avatar threads
    pthread_t threads[nAvatars];   
    /*pthread_t threads = malloc(sizeof(pthread_t) * nAvatars); 
     if (threads == NULL){
         printf("No Memory allocated for avatar threads");
         exit (1);
     }
     */
     int a;
     //For each avatar, creating a thread. each 0-n avatar will run on thread[0-n]. Working out logistics
     for (a = 0; a < nAvatars; a++){
     if ((pthread_create(&threads[i], NULL, createAvatar, i, nAvatars, diffculty, ip, MazePort, plog)) != 0){
        fprintf(pLog, "\nNew Thread: %i", threads[i]);
        printf("\nNew Thread: %i", threads[i]);
        }
    }

     close(MazePort);
     close(sockfd);
     fprintf(pLog, "\n\nCleared Memory");
     fclose(pLog);

     exit(0);
}


//////////////////////////////////////////////// Helper Functions /////////////////////////////////////////////////


// helper function taken from: https://srishcomp.wordpress.com/2013/01/15/a-c-program-to-get-ip-address-from-the-hostname/
int get_ip(char * hostname , char* ip) 
{  struct hostent *he;     
   struct in_addr **addr_list;     
   int i;     
   if ( (he = gethostbyname( hostname ) ) == NULL)     
   { perror("Error in gethostbyname. ");         
     return 1;}     
   addr_list = (struct in_addr **) he->h_addr_list;
    for(i = 0; addr_list[i] != NULL; i++)
    {   strcpy(ip , inet_ntoa(*addr_list[i]) );
        return 0;}
    return 1;
}


/// Helper function to start up logfile 
FILE* initLog(int difficulty, int nAvatars){
// get date for name
  FILE *pLog;
  char str[200];
  char buff[100];
  time_t mytime;
  mytime = time(NULL);
  strftime (buff, 100, "%a_%d_'%y:%H:%M", localtime(&mytime));
  sprintf(str, "./logs/%s_%i_%i.log", buff, difficulty, nAvatars);


// open log up in a log folder to append 
  pLog = fopen(str, "a");
  if(pLog){
    char date[100];
    strftime(date, 100, "%a %d %Y, %H:%M", localtime(&mytime));
    fprintf(pLog, "Log: %s\n", date);
    fprintf(pLog, "Difficulty: %i\nNumber of Avatars: %i\n", difficulty, nAvatars);
  }

  return(pLog);

}









