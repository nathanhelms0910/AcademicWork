#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <signal.h>


int global = 0;
int work(FILE *in, FILE *out)
{
  int num;
  while((!feof(in)))
  {
    if(global == 1)
    {
      fprintf(out, "Error in other interaction\n");
      exit(0);
    }
    if(fscanf(in, "%d", &num) <= 0)
    {
      exit(1);
    }
    else if(num == 0) {
      exit(0);
    }
    else if(num < 0) {
      fprintf(out, "Error\n");
      exit(1);
    }
    else {
      sleep(1);
      num = num * 2;
      fprintf(out, "%d\n", num);
    }
  }
}

void something(int n) {
  global = 1;


}



int main(int argc, char *argv[])
{
  struct sigaction action;
  action.sa_handler = something;
  
  sigaction(SIGTERM, &action, NULL);
  char outfilename[25];
  char infilename[24];
  int num;

  if(argc < 2)
  {
    printf("Missing filename\n");
    return(1);
  }
  else
  {
    strcpy(infilename, argv[1]);
    strcpy(outfilename, infilename);
    strcat(infilename, ".in");

  }
  int child = fork();
  if(child == 0)
  {
     
    FILE *fp = fopen(infilename, "r");
    if(fp)
    {
      strcat(outfilename, ".out");
      FILE *out = fopen(outfilename, "w");
      work(fp, out);
      fclose(out);
    }

    else
    {
      printf("Failed to open file\n");
    }

  }

  else {
    int child2 = fork();
    if(child2 == 0)
    {
      work(stdin,stdout);
    }
    else {
      int status;
      int waitVal = wait(&status);
      int waitVal2;
      if(WIFEXITED(status)) {
	if(WEXITSTATUS(status) == 0) {
	  if(waitVal == child)
	  {
	    waitVal2 = wait(&status);
	    if(WIFEXITED(status)) {
	      if(WEXITSTATUS(status) == 0) {
	        printf("Both interactions normal\n");
	      }
	      else {
		kill(child, SIGTERM);
		printf("User interaction ended with error\n");
	      }
	    }
	  }
	  else
	  {
	    waitVal2 = wait(&status);
	    if(WIFEXITED(status)) {
	      if(WEXITSTATUS(status) == 0) {

	        printf("Both interactions normal\n");
	      }
	      else {
		work(stdin,stdout);
		kill(child2, SIGTERM);
		printf("File Interaction ended with error\n");
	      }
	    }
	  }
	}
	else {
	  if(waitVal == child)
	  {
	    kill(child2, SIGTERM);
	    wait(NULL);
	    printf("File Interaction ended with error\n");
	  }
	  else {
	    {
	      kill(child, SIGTERM);
	      printf("User interaction ended with error\n");
	    }



	  }

	}
	//wait(NULL);
      }

      return(0);
    }
  }
}
