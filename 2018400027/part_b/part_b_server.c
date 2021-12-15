/* @author Kardelen Demiral
	Aim of the project: Using remote process call, 
	executing an unknown binary file giving the parameters through the server 
	and receiving the output of the unknown program. 
	Conclusion: We can execute binary files that are in a remote machine without knowing anything about the source code using parallel programming
	and remote process call. The only thing we should know is the program's input and output types so that we can capture them and the port number of the remote machine. 
*/
#include "part_b.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <string.h>

char **
part_b_1_svc(arguments *argp, struct svc_req *rqstp)
{
	static char * result;

	/*
	 * insert server code here
	 */

	int num1 = argp->num1; //argument to be used are initialized 
	int num2 = argp->num2; //num1 and num2 are the parameters to pass to the blackbox
	char *path = argp->path; //path is the path of the blackbox


	int fderr[2], fdout[2], fdin[2], nbytes;
	pipe(fderr); //pipes are created
	pipe(fdout); //fderr: error pipe, fdout: outputpipe, fdin: input pipe
	pipe(fdin);


	char rslt[500]; //result string

	pid_t pid = fork(); //child created



	if(pid < 0){
		perror("fork failed");
		exit(1);
	}
	else if (pid == 0){ //child process

		close(fderr[0]);  //unused pipe ends are closed
		close(fdout[0]);
		close(fdin[1]);
		
		close(STDOUT_FILENO); //child process's stdout stderr and stdin file descriptors are closed to be redirected
    	close(STDERR_FILENO);
    	close(STDIN_FILENO);

		dup2(fdout[1],STDOUT_FILENO); //error, input and output are redirected to the pipes
		dup2(fderr[1],STDERR_FILENO);
		dup2(fdin[0], STDIN_FILENO);

		close(fderr[1]);
		close(fdout[0]);
		close(fdin[0]);

		char* args[] = {path, NULL};
		execv(args[0], args); //blackbox is executed
	} else { //parent process


		char writeBuffer[10000];


		sprintf(writeBuffer, "%d\n%d", num1, num2);


		write(fdin[1], writeBuffer, strlen(writeBuffer)); //inputs are directed to the stdin of blackbox


		char buffer1[10000];
		char buffer2[10000];
		int count1;
		int count2;

		close(fderr[1]); //pipes are closed
		close(fdout[1]);
		close(fdin[0]);
		close(fdin[1]);

		wait(NULL); //wait for the child process to end


		count1 = read(fderr[0], buffer1, sizeof(buffer1)-1); //read the error pipe

    	if (count1 > 0) { //if the length of the information in the error, there is an error
      		buffer1[count1] = 0;
      		strcpy(rslt, "FAIL:\n"); 
      		strcat(rslt, buffer1); //result is the error


 	  	} else {
 	  		
 	  		count2 = read(fdout[0], buffer2, sizeof(buffer2)-1); //if there isn't any error, read the output from the output pipe

 	  		buffer2[count2] = 0;
 	  		
      		strcpy(rslt, "SUCCESS:\n");
      		strcat(rslt, buffer2); //result is the output
   	 }

	}

	result = rslt;

	return &result;
}

