/*
* Author: Francisco Cabrera
* Date: 20/09/2022
* Description: In this file, we can find the calls to commands.
*			
*
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "../include/externprogram.h"
#include "../include/executecommands.h"
#include "../include/commands/exit.h"
#include "../include/commands/cd.h"
#include "../include/commands/clr.h"
#include "../include/commands/echo.h"


/*
* This function takes the first token to the command and call the corresponding
* command with the corresponding arguments.
* If it cannot find the command, it interprets it as an external program
*
*/
void executeCommand(char* command){
	int back = 0;

	command[strcspn(command,"\n")] = '\0';

	if(strrchr(command,'&')){
		back = 1;
	}

	command[strcspn(command,"&")] = '\0';


	command = strtok(command," "); 

	if(command!=NULL){
		if(!strcmp(command, "quit")){
			exitShell();
			return;
		}

		else if(!strcmp(command, "cd")){
			cd(command);	
			return;
		}

		else if(!strcmp(command, "clr")){
			clr(command);
			return;
		}

		else if(!strcmp(command, "echo")){
			echo(command);
			return;
		}

		else		
			programInvocation(command, back);
	}
}