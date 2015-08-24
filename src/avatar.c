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
































































//Essentially this will send a message to the server from each avatar saying they are ready, and once we have heard from all of them the server will initialze Avatare structures with their turn ID and location. Right CreateAvatar is called for each avatar thread, and startup() will be too. 
int createAvatar(int id, int nAvatars, int diff, char ip, int MazePort, FILE *plog){
   //Prepare message for SENDING
    AM_Message *ready = malloc(sizeof(AM_Message));
    if (!ready){
        perror("No memory\n");
        exit(4);
    }
    sleep (1);
    printf("Building avatars ready message to server");
    ready->type = htonl(AM_AVATAR_READY);
    ready->avatar_ready.AvatarId = htonl(id);

    //send ready message to server 
    send(sockfd, ready, AM_MAX_MESSAGE, 0);
    free(ready);

    //Once the server has heard from each avatar, it will send each one it's location and it's turn ID.
    //inialize Avatar struct with XYPos based on message

}
int startup(int id){
    //Prepare to RECEIVE message
    AM_MESSAGE *rec_message = malloc(sizeof(AM_Message));
    if(!rec_message){
        perror("\nNo memory");
        exit(4);
    }

    if (recv((sockfd, rec_message, AM_MAX_MESSAGE, 0)) == 0){
            error: server terminated prematurely
            perror("The server terminated prematurely");
            exit(4);
     }

     printf("\n Parsing server reply");

     if (ntohl(rec_message->type == AM_NO_SUCH_AVATAR)){
         printf("Illegal avatar ID sent a ready to the server");
        exit(5);
        }

    if (ntohl(rec_message->type == AM_AVATAR_TURN)){
        Avatar *newAv = malloc(sizeof(Avatar));//Correct? Or is an Avatar instance already in existence?
       newAv->pos = ntohl(rec_message->avatar_turn.Pos[id]);
       uint32_t TurnId = ntohl(rec_message->avatar_turn.TurnId;
        return TurnId;
        }


    if(ntohl(rec_message->type) == AM_INIT_FAILED){
        printf("\nInitialization failed.");
        exit(5);
        }



    return (-1);




}
