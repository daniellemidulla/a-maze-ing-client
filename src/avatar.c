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


// ---------------- Local includes  e.g., "file.h"

#include "amazing.h"

// ---------------- Constant definitions 

// ---------------- Macro definitions

// ---------------- Structures/Types 

// ---------------- Private variables 

// ---------------- Private prototypes 
int initializeMazeport(char* ip, int MazePort, int id, int sockfd, struct sockaddr_in servaddr);
int createAvatar(int id);

/*====================================================================*/
// function to test threads
// This function will run concurrently.
void* print_i(void* ptr) {
    int sockfd = 0;
    struct sockaddr_in servaddr;
    avatarInfo a = *((avatarInfo *) ptr);
    AM_Message *rec_message = calloc(1, sizeof(AM_Message));
    if(!rec_message){
        perror("\nNo memory");
        exit(4);
    }
    printf("\nTHREAD FOR %i", a.avID);

    sockfd = initializeMazeport(a.ip, a.MazePort, a.avID, sockfd, servaddr);
    printf("\nsock: %i", sockfd);
    while(1){
       
        // listen to message
        // v0: print message back out
        // Recvd


        // create a message to be received 
        
        memset(rec_message, 0, sizeof(AM_Message));
        int rec = recv(sockfd, rec_message, sizeof(AM_Message), 0);
        printf("%i", rec);
        if (rec == 0){
                           //error: server terminated prematurely
               perror("The server terminated prematurely"); 
               exit(4);
        }


        // if we received a message, decode it
        
            printf("\nmessage type %i", ntohl(rec_message->type));
            printf("\ngot a message");

            // if it is a turn message


                 // if avatar id matches turn id

                    // get a turn from the rule
                    // update maze knowledge
                    // write to log

        

      printf("\nlooped");
      sleep(1);


    }
  
    return NULL;
        
}



int initializeMazeport(char* ip, int MazePort, int id, int sockfd, struct sockaddr_in servaddr){

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
     servaddr.sin_port =  htons(MazePort); //convert to big-endian order
    
     //Connection of the client to the socket 
     int connected = connect(sockfd, (struct sockaddr *) &servaddr, sizeof(servaddr));
     if (connected <0) {
          perror("Problem in connecting to the server");
          exit(3);
     }
     printf("\nconnected to socket: %i", connected);

    AM_Message *ready = malloc(sizeof(AM_Message));
    if (!ready){
        perror("No memory\n");
        exit(4);
    }
    
    ready->type = htonl(AM_AVATAR_READY);
    ready->avatar_ready.AvatarId = htonl(id);

    //send ready message to server 
    int sent = send(sockfd, ready, sizeof(AM_Message), 0);
    printf("\nAvatar ready message sent: %i", sent);
    free(ready);
    

     return sockfd;
    
}



