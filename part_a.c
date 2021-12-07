#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <fcntl.h>

int main(int argc, char *argv[]){

	pid_t pid = fork();

	//printf("pid: %d\n", pid);

	if(pid < 0){
		perror("fork failed");
		exit(1);
	}
	else if (pid == 0){
		FILE *fp = fopen(argv[2], "a");
		int file = open(argv[2], O_WRONLY | O_APPEND, 0777);
		if (file == -1) {
			return 2;
		}

		int file2 = dup2(file,1);
		int file3 = dup2(file,2);

		char* args[] = {argv[1], NULL};
		execv(args[0], args);
	}

	wait(NULL);

	return 0;
}