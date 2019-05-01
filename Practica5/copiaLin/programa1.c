/*Creado por Adrian González Pardo & Melani Betsabee Valdez Esquivel
  Fecha de modificaciótam: 29/04/2019
  Correo electronico:gozapaadr@gmail.com & betsabi100198@gmail.com*/
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <time.h>
#include <sys/types.h>
#include <sys/wait.h>

char *msg[]={"1","2","3","4","5","6","7","8","9","10",
  "11","12","13","14","15"};



void *hilo3(void *arg){
  printf("\t\t\tValue in k: %s Practica 5\n",(char *)arg);
  return NULL;
}

void *hilo2(void *arg){
  printf("\t\tValue in j: %s Thread ID: %ld\n",(char *)arg,pthread_self());
  return NULL;
}

void *hilo1(void *arg){
  printf("\tValue in i: %s Thread ID: %ld\n",(char *)arg,pthread_self());
  return NULL;
}

void printProcess(){
  printf("[PPID]=%d\t[PID]=%d\n",getppid(),getpid());
}

int main(void){
  pid_t pid;
  printf("Main process: ");
  printProcess();
  if((pid=fork())==0){
    printf("Child process: ");
    printProcess();
    int i,j,k;
    pthread_t thread1;
    for(i=0;i!=15;i++){
      usleep(100);
      pthread_create(&thread1,NULL,hilo1,(void *)msg[i]);
      for(j=0;j!=10;j++){
        usleep(100);
        pthread_create(&thread1,NULL,hilo2,(void *)msg[j]);
        for(k=0;k!=5;k++){
          usleep(100);
          pthread_create(&thread1,NULL,hilo3,(void *)msg[k]);
        }
      }
    }
    exit(0);
  }else{
    wait(NULL);
  }
  return 0;
}
