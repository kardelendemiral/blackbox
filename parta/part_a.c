/* Author:    Kardelen Demiral
	Aim of the project: Using fork() and exec() funcitons, 
	executing an unknown executable binary file redirecting it's parameters and output.

*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <string.h>

int main(int argc, char *argv[]){

	int fderr[2], fdout[2], fdin[2], nbytes;
	pipe(fderr); //pipes are created
	pipe(fdout); //fderr: error pipe, fdout: outputpipe, fdin: input pipe
	pipe(fdin);

	pid_t pid = fork();	//child is created



	if(pid < 0){
		perror("fork failed");
		exit(1);
	}
	else if (pid == 0){ //child process
		close(fderr[0]); //unused pipes are closed
		close(fdout[0]);
		close(fdin[1]);
		
		close(STDOUT_FILENO);
    	close(STDERR_FILENO);
    	close(STDIN_FILENO);

		dup2(fdout[1],STDOUT_FILENO); //child process's stdout stderr and stdin file descriptors are closed to be redirected
		dup2(fderr[1],STDERR_FILENO);
		dup2(fdin[0], STDIN_FILENO);

		close(fderr[1]);
		close(fdout[0]);
		close(fdin[0]);

		char* args[] = {argv[1], NULL};
		execv(args[0], args); //blackbox is executed
	} else {

		FILE *fp = fopen(argv[2], "a"); //output file is created
		int file = open(argv[2], O_WRONLY | O_APPEND, 0777);
		if (file == -1) {
			return 2;
		}

		char writeBuffer[1024];

		int a;
		int b;

		scanf("%d", &a); //inputs are received from the user
		scanf("%d", &b);


		sprintf(writeBuffer, "%d\n%d", a, b);

		write(fdin[1], writeBuffer, strlen(writeBuffer)); //inputs are directed to the stdin of blackbox

		char buffer1[1024];
		char buffer2[1024];
		int count1;
		int count2;

		close(fderr[1]); //pipes are closed
		close(fdout[1]);
		close(fdin[0]);
		close(fdin[1]);

		wait(NULL);  //wait for the child process to end

		count1 = read(fderr[0], buffer1, sizeof(buffer1)-1);  //read the error pipe
    	if (count1 > 0) {  //if the length of the information in the error, there is an error
      		buffer1[count1] = 0;
      		fprintf(fp, "%s\n", "FAIL:");
      		fprintf(fp, "%s", buffer1);  //result is the error


 	  	} else {
 	  		count2 = read(fdout[0], buffer2, sizeof(buffer2)-1); //if there isn't any error, read the output from the output pipe
 	  		buffer2[count2] = 0;
      		fprintf(fp, "%s\n", "SUCCESS:");
      		fprintf(fp, "%s", buffer2); //result is the output
   	 }

	}

	

	return 0;
}