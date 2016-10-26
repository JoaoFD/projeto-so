#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <fcntl.h>
#include <errno.h>
#include <time.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <string.h>

#ifndef POOLTHREADS
#define POOLTHREADS


//Pedidos
typedef struct{
  char request_type[1024];
  char request_file[1024];
  int socket_id;
}request;


//Estrutura para buffer
typedef struct{
  request* request_list;
  int in, out, size;
}buffer;

//estrutura para criar a pool de THREADSPOOL
typedef struct pool_threads* thread;
typedef struct pool_threads{
  int max_pedidos; //
  int num_threads;

  pthread_t* my_threads;
  int* ip;
}poolthreads;
#endif

#ifndef CONFIG
#define CONFIG

//estrutura para criar memoria partilhada
//parametros obtidos pelo config.txt
typedef struct configuracoes* Config;
typedef struct configuracoes{
  int porto_servidor;
  char* scheduling;
  int threadpool;
  char* ficheiros_permitidos;


  Config next;
  thread pool;

}config;
#endif
