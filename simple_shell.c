#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>
#include <unistd.h>

#define MAX_LEN 100 /* The maximum length command */

int main(void) {
	char *args[MAX_LEN / 2 + 1]; /* command line arguments */
	int should_run = 1;          /* flag to determine when to exit program */
	int background = 0;
	int pid;
	while (should_run) {
		printf("music5tand>> ");
		fflush(stdout);

		/* (A) get the command from a user.*/
		char *input = (char*)malloc(MAX_LEN*sizeof(char));	// allocate memory for input.
		fgets(input, MAX_LEN, stdin);				// get through fgets().

		/* (B) check the case "no input" */
		if (strcmp(input,"\n")==0){				
			goto no_input;					// go to the end of the "while{}".
		}

		/* (B) chop the string chopchopchop */
		int i = 0;
		args[i] = strtok(input," \n");
		while(args[i] != NULL){	
			/* (C) check the case "&"(background process)*/
			if(strcmp(args[i],"&")==0){
				args[i-1] = NULL;			// !!! delete the ampersand.
				background = 1;
			}
			args[++i] = strtok(NULL, " \n");
		}
		
		/* (C) plz let me out!! 도움!!!!!! */
		if(strcmp(input,"exit") == 0){
			break;
		}


		/* (D) finally fork() */
		pid = fork();

		if(pid<0){
        		fprintf(stderr, "pork error");
        		return 1;
    		}else if(pid==0){
			execvp(args[0],args);
		}else{
			if(!background){				// it is not a background process.
				printf("%s PID = %d\n", "waiting for a child process, not a background process.",pid);
				waitpid(pid,NULL,0);
			}else{
				printf("backgorund process.\n");	// it is a background process.
				background = 0;				// change it for another process.
			}
		}
		free(input);
		no_input:;
	}
	return 0;
}
