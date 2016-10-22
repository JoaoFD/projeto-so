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
