/*
 * This is sample code generated by rpcgen.
 * These are only templates and you can use them
 * as a guideline for developing your own functions.
 */

#include "blackbox.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <string.h>


char **
blackbox_1_svc(arguments *argp, struct svc_req *rqstp)
{
	static char * result;

	/*
	 * insert server code here
	 */

	int num1 = argp->num1;
	int num2 = argp->num2;
	char *path = argp->path;


	//printf("%d\n", num1);
	//printf("%d\n", num2);
	//printf("%s\n", path);

	int fderr[2], fdout[2], fdin[2], nbytes;
	pipe(fderr);
	pipe(fdout);
	pipe(fdin);
	//char buffer[100];

	//printf("%s\n", "geldim1");


	char rslt[200];
	//char* rslt2;

	pid_t pid = fork();




	//printf("pid: %d\n", pid);

	if(pid < 0){
		perror("fork failed");
		exit(1);
	}
	else if (pid == 0){

		//printf("%s\n", "geldim2");
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

		char* args[] = {path, NULL};
		execv(args[0], args);
	} else {

		/*FILE *fp = fopen(argv[2], "a");
		int file = open(argv[2], O_WRONLY | O_APPEND, 0777);
		if (file == -1) {
			return 2;
		}*/

		//printf("%s\n", "geldim4");

		char writeBuffer[1024];

		//int a;
		//int b;

		//scanf("%d", &a);
		//scanf("%d", &b);


		sprintf(writeBuffer, "%d\n%d", num1, num2);

		//printf("%s\n", "geldim5");

		write(fdin[1], writeBuffer, strlen(writeBuffer));

		//printf("%s\n", "geldim6");

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

		//printf("%s\n", "geldim7");
		//printf("%d\n", count1);
    	if (count1 > 0) {
    		//printf("%s\n", "geldim8");
      		buffer1[count1] = 0;
      		//printf("%s", "fail");
      		//printf("%s", buffer1);
      		//fprintf(fp, "%s\n", "FAIL:");
      		//fprintf(fp, "%s", buffer1);
      		strcpy(rslt, "FAIL:\n");
      		strcat(rslt, buffer1);
      		//result = strcat("FAIL:\n", buffer1);
      		//strcpy(rslt1, "FAIL:\n");
      		//strcpy(rslt2, buffer1);
      		//write(file, "FAILED:", sizeof("FAILED:")+1);
      		//write(file, buffer1, count1+1);
      		//printf("%s\n", "geldim9");


 	  	} else {
 	  		//printf("%s\n", "geldim10");
 	  		//printf("%s", "success");
 	  		//write(file, "SUCCESS:", sizeof("SUCCESS:")+1);
 	  		count2 = read(fdout[0], buffer2, sizeof(buffer2)-1);

 	  		//printf("%s\n", "geldim11");
 	  		buffer2[count2] = 0;
 	  		//printf("%d\n", count2);
 	  		//printf("%s", buffer2);
      		//write(file, buffer2, count2+1);
      		//fprintf(fp, "%s\n", "SUCCESS:");
      		//fprintf(fp, "%s", buffer2);
      		//strcpy(rslt1, "SUCCESS:\n");
      		//strcpy(rslt2, buffer2);
      		strcpy(rslt, "SUCCESS:\n");
      		strcat(rslt, buffer2);
      		//printf("%s\n", "geldim12");
   	 }

	}

	//rslt1 = strcat(rslt1, "\n");

	//result = strcat(rslt1, rslt2);

	//printf("%s\n", rslt );
	result = rslt;
	return &result;
}
