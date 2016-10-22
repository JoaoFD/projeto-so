#include <string.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <semaphore.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h> 
#include <unistd.h>
#include <ctype.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <signal.h>
#include <pthread.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <fcntl.h>
#include <sys/shm.h>
#include <time.h>
#include <sys/mman.h>
#define DEBUG

#include "funcoes.h"

#define MAX 1000


//----------------------------GESTOR DE CONFIGURAÇÕES----------------------------------------------
sem_t *mem; //Controla o acesso à memoria partillhada com semáforos

void le_config(){

	FILE *fp = fopen("config.txt","r");
	char linha[100];

	//void mapear_memoria();
	//void associa_zona_memoria();

	if (fp == NULL)
		printf("Erro ao gerar o ficheiro");
	else{
		sem_wait(mem);
		while(fgets(linha,MAX,fp) != NULL){
			//COMPLETAR
		}
		sem_post(mem);
	}
	fclose(fp);
}


//Criacao e mapeamento da memória partilhada
/*inicia memória partilhada*/

  

void mapear_memoria(){
	shmid = shmget(IPC_PRIVATE, sizeof(config), IPC_CREAT|0700);
	if (shmid == -1){
		perror("Erro na criação de espaço de memória.\n");
		exit(1);
	}

	shmem=(config*)shmat(shm_id,NULL,0)
	  	if(shmem == (config*)-1){
		    perror("Erro na memoria partilhada");
		    exit(1);
  		}
}

//Associar uma zona de memória partilhada, que retorna -1 em caso de erro
//parametro do meio, é o parâmetro onde começa a memória partilhada

void associa_zona_memoria(){
	conf = (config*)shmat(shmid,NULL,0);
	if (conf == (config*)-1){
		perror("Erro ao associar a zona de memória.\n");
		exit(1);
	}
}
	

void mapear_ficheiro(){
	int fp; 
	char* f_ip;

	fp = open("localdns.txt", O_WRONLY, S_IWRITE);

	if (fp == -1){
		printf("Erro ao gerar ficheiro.\n");
		exit(-1);
	}

	f_ip = mmap(NULL, TAMMSG, PROT_READ, MAP_SHARED, fp, 0);

	if (f_ip < (char*) 0){
		printf("Erro no mapeamento de memória.\n");
		exit(-1);
	}
}