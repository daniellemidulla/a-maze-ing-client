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

// ---------------- Local includes  e.g., "file.h"

#include "amazing.h"

// ---------------- Constant definitions 

// ---------------- Macro definitions

// ---------------- Structures/Types 

// ---------------- Private variables 

// ---------------- Private prototypes 
int get_ip(char *  , char *);

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


	// get set opt to validate args/switches?
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
        printf("nAvatars = %d\n", nAvatars);
        break;

      case 'd':
        for(i = 0; i < strlen(optarg); i++){
          if (isdigit(optarg[i]) == 0){
            printf("Difficulty must be a number.\n%s is not a decimal number.\n", optarg);
            exit(EXIT_FAILURE);
          }
        }
        difficulty = atoi(optarg);
        printf("difficulty = %d\n", difficulty);
        break;

      case 'h':
        hostname = optarg;
        printf("hostname = %s\n", hostname);
        break;

      case '?':
        /* getopt_long already printed an error message. */
        break;

      default:
        abort();
      }
    }

    //make sure that all the options were present and that all the necessary variables were set
    // NOTE - right now we are not checking that all options are present. idk how to
    if(!nAvatars || nAvatars < 1 || nAvatars > AM_MAX_AVATAR){
      printf("There must be between 1 and 10 Avatars. You entered: %i\n", nAvatars);
      exit(EXIT_FAILURE);
    }
    if(!difficulty || (difficulty < 1) || (difficulty > AM_MAX_DIFFICULTY)){
      printf("The difficulty level must be on the scale of 1(easy) to 9(extremely difficult).\n");
      exit(EXIT_FAILURE);
    }
    if(!hostname || strcmp(hostname, "pierce.cs.dartmouth.edu") != 0){
      printf("The hostname must be pierce.cs.dartmouth.edu.\n");
      exit(EXIT_FAILURE);
    }



/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

     //Socket  stuff - modelled after code from lecture 23
	   
     // get IP address
      get_ip(hostname, ip);
      printf("%s resolved to %s\n", hostname, ip);


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
     init_message->type = AM_INIT;
     init_message->init.nAvatars = nAvatars;
     init_message->init.Difficulty = difficulty;
     //htonl(init_message);

     send(sockfd, init_message, AM_MAX_MESSAGE, 0);

     // recieve AM_INIT_OK <- contains unique mazePort, which is the TCP/IP 
     // port number to communicate with server, server begins listening on the new port immediately
     // INIT message also has mazeWidth and mazeHeight

     // Recvd
     char recvline[AM_MAX_MESSAGE];
      if (recv(sockfd, recvline, AM_MAX_MESSAGE,0) == 0){
               //error: server terminated prematurely
               perror("The server terminated prematurely"); 
               exit(4);
      }
      printf("%s", "String received from the server: ");
      fputs(recvline, stdout);



     // extract MazePort from message, and start up N threads/processes running the main client software

     exit(0);
}


//////////////////////////// Helper Functions /////////////////////////////


// helper function taken from: https://srishcomp.wordpress.com/2013/01/15/a-c-program-to-get-ip-address-from-the-hostname/
int get_ip(char * hostname , char* ip) 
{  struct hostent *he;     
   struct in_addr **addr_list;     
   int i;     
   if ( (he = gethostbyname( hostname ) ) == NULL)     
   { perror("gethostbyname");         
     return 1;}     
   addr_list = (struct in_addr **) he->h_addr_list;
    for(i = 0; addr_list[i] != NULL; i++)
    {   strcpy(ip , inet_ntoa(*addr_list[i]) );
        return 0;}
    return 1;
}
