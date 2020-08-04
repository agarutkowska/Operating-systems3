//SO2 IS1 213B LAB03
//Agnieszka Rutkowska
//ra41497@zut.edu.pl
//
//

#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>

int main(int argc, char* argv[]){
	char* path;
	if(argc == 1){
		printf("ERROR. Nie podano argumentu\n");
		exit(1);
	}
	else if(argc==2){
		path = malloc(sizeof(char)*strlen(argv[1]+1));
		strcpy(path, argv[1]);
	}
	else if(argc==3){
		path = malloc(sizeof(char)*(strlen(argv[2]+1)+strlen(argv[1])));
		strcat(path, argv[1]);
	}
	
	int len_arg=strlen(argv[1]);
	if (len_arg==1){
		exit(0);
	}
	
	char* new_arg;
	if(((len_arg-1)&len_arg)!=0){
		while(((len_arg-1)&len_arg)!=0){
			len_arg--;
		}
		new_arg=malloc(sizeof(char)*len_arg);
		strncpy(new_arg, argv[1], len_arg);
	}
	else{
		new_arg=malloc(sizeof(char)*len_arg);
		strncpy(new_arg, argv[1], len_arg);
	}
	
	char* arg1, arg2;
	arg1=malloc(sizeof(char)*(len_arg)/2);
	arg2=malloc(sizeof(char)*(len_arg)/2);
	strncpy(arg1, new_arg, (len_arg)/2);
	strcpy(arg2, &new_arg[len_arg/2]);
	pid_t my_pid=getpid();
	
	pid_t pid_check=fork();
	if(pid_check==0){
		execl("./41497.so2.lab03.main.c", "program1", arg1, path);
	}
	else if (pid_check==-1){
		printf("Blad w forku 1\n");
		exit(1);
	}
	
	pid_t pid_check2=fork();
	if(pid_check2==0){
		execl("./41497.so2.lab03.main.c", "program2", arg2, path);
	}
	else if (pid_check2==-1){
		printf("Blad w forku2\n");
		exit(1);
	}
	
	int status;
	pid_t pid_dead = wait(&status);
	if(pid_dead==NULL){
		printf("Brak procesow potomnych\n");
	}
	else{
		if(status!=WIFEXITED){
			printf("Blad. Potomek nie zakonczyl pracy poprawnie\n");
		}
	}
	
	pid_dead = wait(&status);
	if(pid_dead==NULL){
		printf("Brak procesow potomnych\n");
	}
	else{
		if(status!=WIFEXITED){
			printf("Blad. Potomek nie zakonczyl pracy poprawnie\n");
		}
	}
	
	printf("%d %s", my_pid, path);
	
	free (arg1);
	free (arg2);
	free (path);
	free (new_arg);
	
	exit(0);	
}