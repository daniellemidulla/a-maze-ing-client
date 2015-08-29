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
#include <pthread.h>



// ---------------- Local includes  e.g., "file.h"
#include "avatar.h"
#include "graphics.h"

// ---------------- Constant definitions 

// ---------------- Macro definitions

// ---------------- Structures/Types 

// ---------------- Private variables 
XYPos *final_destination;
pthread_mutex_t turn_lock;
pthread_mutex_t solved_lock;

// ---------------- Private prototypes 


/*====================================================================*/
// function to test threads
// This function will run concurrently.
void* avatar(void* ptr) {

  // Initial variables 
  int sockfd = 0;
  struct sockaddr_in servaddr;
  avatarInfo a = *((avatarInfo *) ptr);
  fprintf(a.pLog, "\n\nTHREAD FOR %i", a.avID);
  


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
  printf("connected to socket: %i\n", connected);
  

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
  printf("Avatar ready message sent: %i, for av %i\n", sent, a.avID);
  free(ready);
  sleep(1);

  ////////////////////////// initialize a move message and a rec message
   
  AM_Message *rec_message = calloc(1, sizeof(AM_Message));
  if(!rec_message){
    perror("\nNo memory");
    exit(4);
  }

  ////////////////////////////////// listen to server

  while (1) {
    memset(rec_message, 0, sizeof(AM_Message)); 
    //printf("\n thread %i, socket %i", a.avID, sockfd);
    int x = recv(sockfd, rec_message, sizeof(AM_Message), 0);
    if ( x== 0){
      //error: server terminated prematurely
      //printf("\n server error");
      return NULL;
    }

    ///////////////////////////////////////// if turnID matches avID, make a move
    if(ntohl(rec_message->type) == AM_AVATAR_TURN){
      pthread_mutex_lock(&turn_lock);
      // if turn id is my id 
      int move = -1;
      if(ntohl(rec_message->avatar_turn.TurnId) == a.avID){
        // write board to the log
        fprintf(a.pLog, "\n\nits my turn: %i", a.avID);
        fprintf(a.pLog, "\nCurrent board:");
        XYPos pos;
        //look through the positions received from the server and add them to the Avatars, if they aren't there, or use them to update the maze based on the last move 
        for(int b = 0; b < a.nAvatars; b++){
          pos.x = ntohl(rec_message->avatar_turn.Pos[b].x);
          pos.y = ntohl(rec_message->avatar_turn.Pos[b].y);
          fprintf(a.pLog, "\nPosition of avatar %i - x: %i y: %i", b,pos.x, pos.y);
          //printf("\nCurrent position of avatar %i - x: %i y: %i", b,pos.x, pos.y);
          //printf("\nAvatar %d: pos.x: %i, pos.y: %i, direction: %d, last_move: %d \n", b, Avatars[b].pos.x, Avatars[b].pos.y, Avatars[b].direction, Avatars[b].last_move);
          if (Avatars[b].last_move == -1){//if the avatar doesn't have a position yet
            Avatars[b].pos = pos;
            Avatars[b].last_move = M_NULL_MOVE;
          }
          else if (Avatars[b].last_move != M_NULL_MOVE){
            if ((pos.x == Avatars[b].pos.x) && (pos.y == Avatars[b].pos.y)){
              fprintf(a.pLog, "Avatar %d encountered a wall and did not move.", b);
              AddWall(Avatars[b].pos.y, Avatars[b].pos.x, Avatars[b].last_move, 1);
              Avatars[b].last_move = M_NULL_MOVE;
            }
            else {
              fprintf(a.pLog, "Avatar %d moved successfully.", b);
              switch(Avatars[b].last_move){
                case M_NORTH:
                  if (maze->maze[Avatars[b].pos.y][Avatars[b].pos.x].north_wall != 2){
                    AddWall(Avatars[b].pos.y, Avatars[b].pos.x, Avatars[b].last_move, 0);      
                  }
                  break;
                case M_SOUTH:
                  if (maze->maze[Avatars[b].pos.y][Avatars[b].pos.x].south_wall != 2){
                    AddWall(Avatars[b].pos.y, Avatars[b].pos.x, Avatars[b].last_move, 0);      
                  }
                  break;
                case M_EAST:
                  if (maze->maze[Avatars[b].pos.y][Avatars[b].pos.x].east_wall != 2){
                    AddWall(Avatars[b].pos.y, Avatars[b].pos.x, Avatars[b].last_move, 0);      
                  }
                  break;
                case M_WEST:
                  if (maze->maze[Avatars[b].pos.y][Avatars[b].pos.x].west_wall != 2){
                    AddWall(Avatars[b].pos.y, Avatars[b].pos.x, Avatars[b].last_move, 0);      
                  }
                  break;
                default:
                  AddWall(Avatars[b].pos.y, Avatars[b].pos.x, Avatars[b].last_move, 0);
                  break;
              }
              Avatars[b].pos = pos;
              Avatars[b].direction = Avatars[b].last_move;
              Avatars[b].last_move = M_NULL_MOVE;
            }
          }
          
        }

	////////////////graphics////////////////
	initscr();	
	clear();
	raw();
	start_color();
	create_border(maze->num_col, maze->num_row);
     	draw_inside(maze);
	draw_fakes(maze);       
      	int f;
      	for (f = 0; f<a.nAvatars; f++){
       	              draw_avatar(2*Avatars[f].pos.y+1, 2*Avatars[f].pos.x+1);
      	}
	//attroff(COLOR_PAIR(3));
      	refresh();
            
        /* Determine the direction of the move for the current Avatar */

        /* Avatar 0 has a fixed location - it never moves */
        if (a.avID == 0){
          if(!final_destination){
            final_destination = (XYPos *) calloc(1, sizeof(XYPos));
            final_destination->x = Avatars[a.avID].pos.x;
            final_destination->y = Avatars[a.avID].pos.y;
          }
          move = M_NULL_MOVE;
        }
        // if(!final_destination){
        //   for(int i = 0; i < a.nAvatars; i++){
        //     if (i == a.avID) continue;
        //     //if the Avatar is in the same place as another Avatar, save position as final_destination
        //     if((Avatars[i].pos.x == Avatars[a.avID].pos.x) && (Avatars[i].pos.y == Avatars[a.avID].pos.y)){
        //       final_destination = (XYPos *) calloc(1, sizeof(XYPos));
        //       final_destination->x = Avatars[a.avID].pos.x;
        //       final_destination->y = Avatars[a.avID].pos.y;
        //       move = M_NULL_MOVE;
        //       break;
        //     }
        //   }
        // }
        /* Determine the direction of the move for Avatars that aren't Avatar 0 */
        //if Avatar is at final_destination, it should not move
        if((final_destination) && (Avatars[a.avID].pos.x == final_destination->x) && (Avatars[a.avID].pos.y == final_destination ->y)){
          move = M_NULL_MOVE;
        }
        else { //if the Avatar is alone, use the rightHandRule to determine the next move
          move = rightHandRule(Avatars[a.avID]);
        }

        //temporary fix to diagnose the initial -1 rightHandRule return
        if(move == -1){
          exit(EXIT_FAILURE);
        }
        Avatars[a.avID].last_move = move;
        //int move = rand() % 4;
        // write move to the log
        fprintf(a.pLog, "\nMove: %i", move);
        //printf("\nMove: %i", move);

        //send a move message for the current avatar
        AM_Message *ready = calloc(1, sizeof(AM_Message));
        if (!ready){
          perror("No memory\n");
          exit(4);
        }
        ready->type = htonl(AM_AVATAR_MOVE);
        ready->avatar_move.AvatarId = htonl(a.avID);
        ready->avatar_move.Direction =htonl(move);

        //send ready message to server 
        int sent = send(sockfd, ready, sizeof(AM_Message), 0);
        fprintf(a.pLog, "\nAvatar move message sent: %i, for av %i", sent, a.avID);
        free(ready);
        //sleep(1);
      }
      pthread_mutex_unlock(&turn_lock);
    }

    // else if the message is success, break
    else if(ntohl(rec_message->type) == AM_MAZE_SOLVED){
        if (a.avID == 0){
            char buff[100];
            time_t myTime;
            myTime = time(NULL);
            strftime(buff, 100, "%a %d %Y, %H:%M", localtime(&myTime));
            printf("%s", buff);
            fprintf(a.pLog, "\nMaze Solved on %s!", buff);;
        }
      pthread_mutex_lock(&solved_lock);
      //printf("\nSolved!\n");
      free(rec_message);
      free(ptr);
  	
    	//stop at solution, wait for an input to end graphics     
      refresh();
      sleep(1);
      clear();
      printw("Maze solved!");    
      getch();
      clear();
      endwin();
      break;
      pthread_mutex_lock(&solved_lock);
    }

    else if(ntohl(rec_message->type) == AM_TOO_MANY_MOVES){
      printf("\nToo many moves! You lose.\n");
      free(rec_message);
      free(ptr);
      break;
    }
        
    else if(IS_AM_ERROR(ntohl(rec_message->type))){
      printf("\nReceived Error code\n");
      free(rec_message);
      free(ptr);
      break;
    }
  }
  CleanupMaze();
  exit(EXIT_SUCCESS);
}

