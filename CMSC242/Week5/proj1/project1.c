#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <assert.h>
#include <sys/wait.h>
#include <dirent.h>
#include <string.h>
#include <stdbool.h>
#include <signal.h>

int inCmp(char filename[]) {
  int index = strlen(filename) - 3;
  if(index < 0) {
    return 0;
  }
  else if(strcmp(&filename[index], ".in") == 0) {
    return 1;
  }
  else {
    return 0;
  }
}

int expectCmp(char filename1[], char *directory) {
  DIR *dir2 = opendir(directory);
  struct dirent *expect;
  char filename2[30];
  while((expect = readdir(dir2)) != NULL) {
    strncpy(filename2, expect->d_name, 29);
    if(strncmp(filename1, filename2, strlen(filename1)-3) == 0) {
      int ext = strlen(filename2) - 7;
      if(strcmp(&filename2[ext], ".expect") == 0) {
	printf("%s matches up to %s\n", filename1, filename2);
      }
    }
    else {
      printf("%s does not match this file\n", filename1);
    }
  }
}

int do_infile(char filename[],char *directory, char testProgram[]) {
  char *path = malloc(strlen(directory)+strlen(filename)+2);
  strcpy(path, directory);
  strcat(path, "/");
  strcat(path, filename);
  int testCase = open(path, O_RDONLY);
  if(testCase == -1) {
    exit(1);
  }
  else {
    int programRun = fork();
    if(programRun == 0) {
      printf("Running %s\n", filename);
      dup2(testCase, 0); // 0 means stdin right? of course it does!
      execl(testProgram, testProgram, NULL);
      exit(0);
    }
    else {
      int status;
      int childVal = wait(&status);
      if(WIFEXITED(status)) {
	if(WIFEXITED(status) == 1) {
	  printf("%s passed testing\n", filename);
	}
	else {
	  printf("Auto testing failed\n");
	}
      }
      close(testCase);
      free(path);
    }
  }
}

int main(int argc, char *argv[])
{
  int ret;
  struct dirent *dirent;
  int iterations;
  DIR *dir;
  char filename[30];
  if(argc < 3)
  {
    printf("Missing Arguments\n");
    return(0);
  }
  char program[25];
  strcpy(program, argv[1]);  
  char success[] = "Execution went smoothly!\n";
  int child = fork();
  if(child == 0)
  {
    char *directory = argv[2];
    dir = opendir(directory);
    if(dir == NULL) {
      printf("Cannot open directory: tests\n");
      return 1;
    }
    while((dirent = readdir(dir)) != NULL) { 
      strncpy(filename, dirent->d_name, 29);

      if(inCmp(filename) == 1) {
	printf("\n");
	printf("Expect file comparisons starting...\n");
	expectCmp(filename, directory);
	do_infile(filename, directory, program);
      }
      else {
	printf("%s is not a .in\n", filename);
      }
    }
    closedir(dir);
    exit(1);
  }
  else {

    wait(NULL);
    int child2 = fork();
    if(child2 == 0) {
      int num;
      bool user = true;
      while(user) {
	printf("Enter an integer. Enter 0 to close: ");
	scanf("%d", &num);
	if(num == 0)
	{
	  printf("Terminated safely\n");
	  user = false;
	}
	else if(num > 0) {
	  num = num / 2;
	  printf("Number halved is: %d\n", num);
	}
	else {
	  printf("Error in execution\n");
	  user = false;
	}
      }
      exit(1);
    }
    else {
      int status;
      int childVal = wait(&status);
      if(WIFEXITED(status)) {
	if(WIFEXITED(status) == 1) {
	  printf("Program Ended\n");
	}
	else {
	  printf("Error\n");
	}
      }
    }
  }
}



