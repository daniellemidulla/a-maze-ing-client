/*	avatar.c  avatar client


	Project name: Maze Project
	Component name:  Avatar Client

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


// ---------------- Local includes  e.g., "file.h"

#include "amazing.h"

// ---------------- Constant definitions 

// ---------------- Macro definitions

// ---------------- Structures/Types 

// ---------------- Private variables 

// ---------------- Private prototypes 


/*====================================================================*/
int main(int argc, char * argv[]){


	// set up communication with port
	mazeport = argv[1];
	ip = argv[2];
    int sockfd;
    struct sockaddr_in servaddr;

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
     servaddr.sin_port =  htons(mazeport); //convert to big-endian order
	
     //Connection of the client to the socket 
     if (connect(sockfd, (struct sockaddr *) &servaddr, sizeof(servaddr))<0) {
          perror("Problem in connecting to the server");
          exit(3);
     }
	
     // send and recieve stuff here
     // sending an init message now for sample
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

     if (recv(sockfd, rec_message, AM_MAX_MESSAGE,0) == 0){
               //error: server terminated prematurely
        perror("The server terminated prematurely"); 
        exit(4);
      }

	
}
