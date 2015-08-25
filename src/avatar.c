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
    printf("\nTHREAD FOR %i", a.avID);

            printf("\nmazePort %i", a.MazePort);
            printf("\ndifficulty %i", a.difficulty);
            printf("\nnAvatars %i", a.nAvatars);
            printf("\nip %s", a.ip);

    printf("\ninitializing mazeport");
    sockfd = initializeMazeport(a.ip, a.MazePort, a.avID, sockfd, servaddr);

    while(1){
       
        // listen to message
        // v0: print message back out
        // Recvd
     AM_Message *rec_message = malloc(sizeof(AM_Message));
     if(!rec_message){
        perror("\nNo memory");
        exit(4);
     }
     printf("\n %i", sockfd);
     int help = recv(sockfd, rec_message, AM_MAX_MESSAGE,0);
     printf("\nmessage type %i", ntohl(rec_message->type));

     
      if (help == 0){
               //error: server terminated prematurely
               perror("The server terminated prematurely"); 
               exit(4);
      }
      else if (help == -1){
        int err = errno;
        printf("\n failure: %i", err);

      }





    }



    
    return NULL;
        
}


// create avatar pseudocode

        // while not exit conditions (given in lab notes)

            // if avatarID matches TurnID
                // make a turn from rule
                // update maze knowledge
                // write to log
        // close port with fclose(sockfd) 

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
    printf("Building avatars ready message to server");
    ready->type = htonl(AM_AVATAR_READY);
    ready->avatar_ready.AvatarId = htonl(id);

    //send ready message to server 
    int sent = send(sockfd, ready, AM_MAX_MESSAGE, 0);
    printf("\n message sent %i", sent);
    free(ready);
    

     return sockfd;
    
}




//Essentially this will send a message to the server from each avatar saying they are ready, and once we have heard from all of them the server will initialze Avatare structures with their turn ID and location. Right CreateAvatar is called for each avatar thread, and startup() will be too. 
// int createAvatar(int id){
//    //Prepare message for SENDING
//     AM_Message *ready = malloc(sizeof(AM_Message));
//     if (!ready){
//         perror("No memory\n");
//         exit(4);
//     }
//     sleep (1);
//     printf("Building avatars ready message to server");
//     ready->type = htonl(AM_AVATAR_READY);
//     ready->avatar_ready.AvatarId = htonl(id);

//     //send ready message to server 
//     send(sockfd, ready, AM_MAX_MESSAGE, 0);
//     free(ready);
//     return 1;

//     //Once the server has heard from each avatar, it will send each one it's location and it's turn ID.
    //inialize Avatar struct with XYPos based on message

//}
// int startup(int id){
//     //Prepare to RECEIVE message
//     AM_MESSAGE *rec_message = malloc(sizeof(AM_Message));
//     if(!rec_message){
//         perror("\nNo memory");
//         exit(4);
//     }

//     if (recv((sockfd, rec_message, AM_MAX_MESSAGE, 0)) == 0){
//             error: server terminated prematurely
//             perror("The server terminated prematurely");
//             exit(4);
//      }

//      printf("\n Parsing server reply");

//      if (ntohl(rec_message->type == AM_NO_SUCH_AVATAR)){
//          printf("Illegal avatar ID sent a ready to the server");
//         exit(5);
//         }

//     if (ntohl(rec_message->type == AM_AVATAR_TURN)){
//         Avatar *newAv = malloc(sizeof(Avatar));//Correct? Or is an Avatar instance already in existence?
//        newAv->pos = ntohl(rec_message->avatar_turn.Pos[id]);
//        uint32_t TurnId = ntohl(rec_message->avatar_turn.TurnId;
//         return TurnId;
//         }


//     if(ntohl(rec_message->type) == AM_INIT_FAILED){
//         printf("\nInitialization failed.");
//         exit(5);
//         }



//     return (-1);




// }
