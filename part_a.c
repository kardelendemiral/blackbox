#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <string.h>

int main(int argc, char *argv[]){

	int fderr[2], fdout[2], fdin[2], nbytes;
	pipe(fderr);
	pipe(fdout);
	pipe(fdin);
	//char buffer[100];

	pid_t pid = fork();	



	//printf("pid: %d\n", pid);

	if(pid < 0){
		perror("fork failed");
		exit(1);
	}
	else if (pid == 0){
		close(fderr[0]);
		close(fdout[0]);
		close(fdin[1]);
		
		close(STDOUT_FILENO);
    	close(STDERR_FILENO);
    	close(STDIN_FILENO);

		dup2(fdout[1],STDOUT_FILENO);
		dup2(fderr[1],STDERR_FILENO);
		dup2(fdin[0], STDIN_FILENO);

		close(fderr[1]);
		close(fdout[0]);
		close(fdin[0]);

		char* args[] = {argv[1], NULL};
		execv(args[0], args);
	} else {

		FILE *fp = fopen(argv[2], "a");
		int file = open(argv[2], O_WRONLY | O_APPEND, 0777);
		if (file == -1) {
			return 2;
		}

		char writeBuffer[1024];

		int a;
		int b;

		scanf("%d", &a);
		scanf("%d", &b);


		sprintf(writeBuffer, "%d\n%d", a, b);

		write(fdin[1], writeBuffer, strlen(writeBuffer));

		char buffer1[1024];
		char buffer2[1024];
		int count1;
		int count2;

		close(fderr[1]);
		close(fdout[1]);
		close(fdin[0]);
		close(fdin[1]);

		wait(NULL);

		count1 = read(fderr[0], buffer1, sizeof(buffer1)-1);
		//printf("%d\n", count1);
    	if (count1 > 0) {
      		buffer1[count1] = 0;
      		//printf("%s", "fail");
      		//printf("%s", buffer1);
      		fprintf(fp, "%s\n", "FAIL:");
      		fprintf(fp, "%s", buffer1);
      		//write(file, "FAILED:", sizeof("FAILED:")+1);
      		//write(file, buffer1, count1+1);


 	  	} else {
 	  		//printf("%s", "success");
 	  		//write(file, "SUCCESS:", sizeof("SUCCESS:")+1);
 	  		count2 = read(fdout[0], buffer2, sizeof(buffer2)-1);
 	  		buffer2[count2] = 0;
 	  		//printf("%d\n", count2);
 	  		//printf("%s", buffer2);
      		//write(file, buffer2, count2+1);
      		fprintf(fp, "%s\n", "SUCCESS:");
      		fprintf(fp, "%s", buffer2);
   	 }

	}

	

	return 0;
}