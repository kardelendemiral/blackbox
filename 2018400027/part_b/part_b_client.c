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


char*
part_b_prog_1(int num1, int num2, char *path, char *host) //function to send the parameters to the server
{
	CLIENT *clnt;
	char * *result_1;
	arguments  part_b_1_arg;

#ifndef	DEBUG
	clnt = clnt_create (host, PART_B_PROG, PART_B_VERS, "udp");
	if (clnt == NULL) {
		clnt_pcreateerror (host);
		exit (1);
	}
#endif	/* DEBUG */

	part_b_1_arg.num1 = num1; //arguments are initialized
	part_b_1_arg.num2 = num2;
	strcpy(part_b_1_arg.path, path);
	result_1 = part_b_1(&part_b_1_arg, clnt); //result is received from the server
	if (result_1 == (char **) NULL) {
		clnt_perror (clnt, "call failed");
	} else {
		return *result_1; //the result is returned to the main
	}
#ifndef	DEBUG
	clnt_destroy (clnt);
#endif	 /* DEBUG */
}


int
main (int argc, char *argv[])
{
	char *host;

	FILE *fp = fopen(argv[2], "a"); //output file is created
	int file = open(argv[2], O_WRONLY | O_APPEND, 0777);
	if (file == -1) {
		return 2;
	}

	char *result;


	int a;
	int b;

	scanf("%d", &a); //inputs are received from the user
	scanf("%d", &b);

	if (argc < 4) {
		printf ("usage: %s path1 path2 server_host\n", argv[0]);
		exit (1);
	}
	host = argv[3];
	result = part_b_prog_1 (a, b, argv[1], host); //server is called

	fprintf(fp, "%s", result); //received output is printed to the file
exit (0);
}
