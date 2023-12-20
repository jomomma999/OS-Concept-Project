#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <stdio.h>
#include <iostream>
#include <string>
using namespace std;


int main()
{
	/* The command buffer */
	string cmdBuff;
	
	/* The ID of the child process */
	pid_t pid;

	int execlpRetVal;
	int waitReturn; 
	int childEventInfo;
	
	/* Keep running until the user has typed "exit" */
	do 
	{
		/* Prompt the user to enter the command */
		cerr << "cmd>";
		cin >> cmdBuff;
		
		/* If the user wants to exit */
		if(cmdBuff != "exit")
		{
			/* TODO: Create a child */
			pid = fork();
			
			/* TODO: Error check to make sure the child was successfully created */
			if(pid < 0)
				{
					perror("fork");
					exit(1);
				}	
			/*** TODO: If I am child, I will do this: ****/
			/* Call execlp() to replace my program with that specified at the command line.
			 * PLEASE NOTE: YOU CANNOT PASS cmdBuff DIRECTLY to execlp(). It is because 
			 * cmdBuff is an object of type string (i.e., a class) and execlp() expects
 			 * an array of characters.  However, you can pass cmdBuff.c_str(), which will
			 * return an array of characters representation of the string object.
			 * 
			 * Also, please do not forget to error check your exelp() system calls.
			 */
			 if(pid == 0) //  This the child
				{
					// Let's print the process id of the child and the parent
					// gepid() returns the process id of the current process
					// getppid() returns the process id of the parent
					fprintf(stderr, "Child: I am a child. My process id is %d\n", getpid());
					fprintf(stderr, "Child: The process id of my parent is %d\n", getppid());
					
					// Replace the child's code with the code of the program
					// located at "/usr/bin/ls".  ls will be passed the following
					// arguments: 
					// argv[0] -- "ls"
					// argv[1] -- "-l"
					// The NULL argument is necessary
					// On success, there is no return value -- the entire program
					// replaced with the new program and the new program starts 
					// executing starting with the first instruction
					// On faliure, returns -1 and the current program continues 
					execlpRetVal = execlp("/usr/bin/ls", "ls", "-l", NULL);

					// This code is unreachable unless execlp has failed 
					if(execlpRetVal < 0)
					{
						perror("execlp");
						exit(1);
					}
				}
			
			/*** TODO: If I am a parent, I will do the following ***?
			/* Wait for the child process to terminate */
			else // This is the parent
			{
				// Wait for the child to finish
				// waitReturn will store the process
				// id of the recently terminated child
				// childExitStatus will store information
				// about child termination (as a bitmap). 
				// We need to use a few macros to extract 
				// the actual exit code
				waitReturn = wait(&childEventInfo);

				// Sanity checks -- wait failed?
				if(waitReturn < 0)
				{
					perror("wait");
					exit(1);
				}
				
				// If the reason why wait has stopped waiting
				// was child termination (could be other reasns
				// in practice!), let's print the child's exit status
				// WIFEXITED macro checks the bits in the childEventInfo
				// to see if the reason why the wait has stopped waiting
				// was child termination
				if(WIFEXITED(childEventInfo))
				{
					// Print the terminated child's process id
					fprintf(stderr, "Parent: The child with pid=%d has terminated\n", waitReturn);
					
					// WEXITSTATUS extracts the child's exit code from the childEventInfo
					fprintf(stderr, "Paent: The child's exit code is %d\n", WEXITSTATUS(childEventInfo));	
				}
			}
		}
	}
	while(cmdBuff != "exit");
	
	return 0;	
}
