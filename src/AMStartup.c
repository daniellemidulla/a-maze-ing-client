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
/*	file.c	one-line description

	Copyright 2015 (if any)

	License (if any)

	Project name:
	Component name:

	This file contains ...
	
	Primary Author:	
	Date Created:	

	Special considerations:  
		(e.g., special compilation options, platform limitations, etc.) 
	
======================================================================*/
// do not remove any of these sections, even if they are empty
//
// ---------------- Open Issues 

// ---------------- System includes e.g., <stdio.h>
/*	file.c	one-line description

	Copyright 2015 (if any)

	License (if any)

	Project name:
	Component name:

	This file contains ...
	
	Primary Author:	
	Date Created:	

	Special considerations:  
		(e.g., special compilation options, platform limitations, etc.) 
	
======================================================================*/
// do not remove any of these sections, even if they are empty
//
// ---------------- Open Issues 

// ---------------- System includes e.g., <stdio.h>
#include <sys/socket.h>				// socket funtions
#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <string.h>
#include <arpa/inet.h>
#include <getopt.h>
#include <string.h>
// ---------------- Local includes  e.g., "file.h"

#include "amazing.h"

// ---------------- Constant definitions 

// ---------------- Macro definitions

// ---------------- Structures/Types 

// ---------------- Private variables 

// ---------------- Private prototypes 

/*====================================================================*/

#define SERV_PORT 3000 /*port*/


int
main(int argc, char **argv) 
{
	 // int sockfd;
     // struct sockaddr_in servaddr;
	int c;

	printf("\ncompiled\n");

	// get set opt to validate args/switches?
	printf("arg checking \n");

	while (1)
    {
	static struct option long_options[] =
        {
          {"nAvatars",     required_argument,       0, 'n'},
          {"difficulty",  required_argument,       0, 'd'},
          {"hostname",  required_argument, 0, 'h'},
          {0, 0, 0, 0}
        };
      
      
         int option_index = 0;
         c = getopt_long (argc, argv, "n:d:h:",
                       long_options, &option_index);  

      /* Break at the end of options */
      if (c == -1)
        break;

      switch (c)
        {
        case 0:
          if (long_options[option_index].flag != 0)
            break;
          
          if (optarg)
            
          printf("\n");
          break;

        // flags: 

        case 'n':
          // TODO : check and assign var
          printf("\nnAvatars = %s", optarg);
          break;

        case 'd':
          
          printf("\ndifficulty = %s", optarg);
          break;

        case 'h':
          
          printf("\nhostname = %s", optarg);
          break;

        case '?':
          /* getopt_long already printed an error message. */
          break;

        default:
          abort();
        }
    }

     
     //TODO : basic check of the arguments
     //additional checks can be inserted
     //if (argc !=2) {
     //     perror("Usage: TCPClient <IP address of the server"); 
     //     exit(1);
     //}
	
     //Create a socket for the client
     //If sockfd<0 there was an error in the creation of the socket
     // if ((sockfd = socket (AF_INET, SOCK_STREAM, 0)) <0) {
     //      perror("Problem in creating the socket");
     //      exit(2);
     // }
	
     // //Creation of the socket
     // memset(&servaddr, 0, sizeof(servaddr));
     // servaddr.sin_family = AF_INET;
     // servaddr.sin_addr.s_addr= inet_addr(argv[1]);
     // servaddr.sin_port =  htons(SERV_PORT); //convert to big-endian order
	
     // //Connection of the client to the socket 
     // if (connect(sockfd, (struct sockaddr *) &servaddr, sizeof(servaddr))<0) {
     //      perror("Problem in connecting to the server");
     //      exit(3);
     // }
	
     // send and recieve stuff here

     // send nAvatars, Difficulty
     // recieve AM_INIT_OK <- contains unique mazePort, which is the TCP/IP 
     // port number to communiat with server, server begins listening on the new port immediately
     // INIT message also has mazeWidth and mazeHeight

     // extract MazePort from message, and start up N threads/processes running the main lient software

     exit(0);
}
