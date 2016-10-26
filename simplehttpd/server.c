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

//Variáveis globais
sem_t *mem; //Controla o acesso à memoria partillhada com semáforos
int buff_id;
buffer *buff;
configuracoes *config;
thread* pool; //cria uma pool de threads
//variaveis para a pool
sem_t *empty;
sem_t *full;


//Inicializar buffer
void init(){
	if((buff_id=shmget(IPC_PRIVATE,sizeof(buff),IPC_CREAT|0777))==-1){
	    perror("Erro na criação do buffer");
	    exit(0);
	}

	if((buff=(buff*)shmat(buff_id,NULL,0))==(buff*)-1){
	    perror("Erro!!");
	    exit(0);
	}
	buff->in=0;
	buff->out=0;

}

//Função estatisticas
void funcEstatisticas(){

}

//Criacao e mapeamento da memória partilhada
///Inicia memória partilhada/
void mapear_memoria(){
	shmid = shmget(IPC_PRIVATE, sizeof(config), IPC_CREAT|0700);
	if (shmid == -1){
		perror("Erro na criação de espaço de memória.\n");
		cleanup();
		exit(1);
	}

	shmem=(config*)shmat(shm_id,NULL,0)
	  	if(shmem == (config*)-1){
		    perror("Erro na memoria partilhada");
		    cleanup();
		    exit(1);
  		}
}

void terminaProcessos(){
	cleanup(){

//Remove processos
		kill(pid[0], SIGKILL);
		kill(pid[1], SIGKILL);

		//Remove memoria partilhada
		shmdt(config);
		shmctl(shmid, IPC_RMID, NULL);

		EXIT(0);
	}
}


//Função ler ficheiro
void le_config(){

	FILE *fp = fopen("config.txt","r");
	char linha[100];

	//void mapear_memoria();
	//void associa_zona_memoria();

	if (fp == NULL)
		printf("Erro ao gerar o ficheiro\n");
	else{
		sem_wait(mem);
		while(fgets(linha,MAX,fp) != NULL){
			if (strcmp(token, "SERVERPORT") == 0){
			fflush(stdin);
			token = strtok(NULL, " ");
			config->porto_servidor = atoi(token);
		} else if (strcmp(token, "SCHEDULING") == 0){
			fflush(stdin);
			token = strtok(NULL, " ");
			strcpy(config->scheduling, token);
			config->scheduling[strlen(config->scheduling)-1] = '\0';
		} else if (strcmp(token, "THREADPOOL") == 0){
			fflush(stdin);
			token = strtok(NULL, " ");
			config->threadpool = atoi(token);
		} else if (strcmp(token, "AlLLOWED") == 0){
			fflush(stdin);
			token = strtok(NULL, ",");
			while (token != NULL){
				strcpy(config->allowed[i], token);
				i++;
				token = strtok(NULL, ",");
			}
			config->allowed[i-1][strlen(config->allowed[i-1])-1] = '\0';

		}
		sem_post(mem);
	}
	fclose(fp);
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