#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

int* sys_random(int size){
	int *buffer;
	buffer = malloc(sizeof(int) * size);
	int file = open("/dev/urandom",O_RDONLY);
	read(file, buffer, size * sizeof(int));
	close(file);
	return buffer;
}

int main(){
	int size = 8;
	int * buffer = sys_random(size);
	int i;
	printf("read from newly generated random intergers from buffer\n");	
	for(i = 0; i < size; i++){
        	printf("%d", buffer[i]);
	        printf("\n");
	}


	printf("write it to file and print the result\n");
	int des = open("virus.txt",O_RDWR,777);
        int whut = write(des,buffer,size * sizeof(int));
	close(des);


	des = open("virus.txt",O_RDWR);
	int * new_buff;
	new_buff = malloc(sizeof(int) *size);
	whut = read(des, new_buff,size * sizeof(int));        	
	//printf("?%d%s%d\n",whut,strerror(errno),errno);

	for(i = 0; i < size; i++){		
		printf("%d\n",new_buff[i]);
	}
	close(des);
	printf("for some reason, if you run it multiple times, the result of the last run will be erased from virus.txt. And you have to name the file \"virus.txt\" not simply as \"virus\" ¯\\_(ツ)_/¯\n");
        return 0;
}
