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

    


    // Initial variables 
    int sockfd = 0;
    struct sockaddr_in servaddr;
    avatarInfo a = *((avatarInfo *) ptr);
    printf("\nTHREAD FOR %i", a.avID);



    ///////////////////////// create socket

      //Create a socket for the client
     //If sockfd<0 there was an error in the creation of the socket
     if ((sockfd = socket (AF_INET, SOCK_STREAM, 0)) <0) {
          perror("Problem in creating the socket");
          exit(2);
     }
    
     //Creation of the socket
     memset(&servaddr, 0, sizeof(servaddr));
     servaddr.sin_family = AF_INET;
     servaddr.sin_addr.s_addr= inet_addr(a.ip);
     servaddr.sin_port =  htons(a.MazePort); //convert to big-endian order

    //Connection of the client to the socket 
     int connected = connect(sockfd, (struct sockaddr *) &servaddr, sizeof(servaddr));
     if (connected <0) {
          perror("Problem in connecting to the server");
          exit(3);
     }
     printf("\nconnected to socket: %i", connected);



     //////////////////////////// send initial message 


    AM_Message *ready = calloc(1, sizeof(AM_Message));
    if (!ready){
        perror("No memory\n");
        exit(4);
    }
    
    ready->type = htonl(AM_AVATAR_READY);
    ready->avatar_ready.AvatarId = htonl(a.avID);

    //send ready message to server 
    int sent = send(sockfd, ready, sizeof(AM_Message), 0);
    printf("\nAvatar ready message sent: %i, for av %i", sent, a.avID);
    free(ready);
    sleep(1);


    ////////////////////////// initialize a move message and a rec message
   

    AM_Message *rec_message = calloc(1, sizeof(AM_Message));
    if(!rec_message){
        perror("\nNo memory");
        exit(4);
    }

    // AM_Message *move = calloc(1, sizeof(AM_Message));
    // if(!move){
    //     perror("\nNo memory");
    //     exit(4);
    // }
    // move->type = htonl(AM_AVATAR_MOVE);


    ////////////////////////////////// listen to server


    
    while (1){

        memset(rec_message, 0, sizeof(AM_Message)); 
        printf("\nsocket: %i", sockfd);
        int x = recv(sockfd, rec_message, sizeof(AM_Message), 0);
        printf("%i", x);
        if ( x== 0){
            //error: server terminated prematurely
            printf("\n server error");
            return NULL;
        }

        

        // if turnID matches avID
        if(ntohl(rec_message->type) == AM_AVATAR_TURN){
            // parse and print message 
            printf("\nTurnId: %i, XYPos x: %i, y: %i", ntohl(rec_message->avatar_turn.TurnId), ntohl(rec_message->avatar_turn.Pos[a.avID].x), ntohl(rec_message->avatar_turn.Pos[a.avID].y));

            // if turn id is my id 
            if(ntohl(rec_message->avatar_turn.TurnId) == a.avID){
                printf("\nits my turn: %i", a.avID);



                AM_Message *ready = calloc(1, sizeof(AM_Message));
                if (!ready){
                     perror("No memory\n");
                     exit(4);
                }
    
                ready->type = htonl(AM_AVATAR_MOVE);
                ready->avatar_move.AvatarId = htonl(a.avID);
                ready->avatar_move.Direction =htonl(2);

                 //send ready message to server 
                int sent = send(sockfd, ready, sizeof(AM_Message), 0);
                printf("\nAvatar ready message sent: %i, for av %i", sent, a.avID);
                free(ready);
                sleep(1);


            }
        }

        // else if the message is success, break
        else if(ntohl(rec_message->type) == AM_MAZE_SOLVED){
            printf("\nSolved!");
            break;
        }

                
    }


 
  
    return NULL;
        
}





