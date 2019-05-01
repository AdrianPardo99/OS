#include <stdio.h>
#include <pthread.h>
char *mensaje[]={"Hola a todos desde el hilo 1","Hola a todos desde el hilo 2"
  ,"Hola a todos desde el hilo 3"};
void *hilo(void *arg);

int main(void){
  int i;
  pthread_t idHilo;
  int devolucionHilo;
  for(i=0;i!=3;i++){
    pthread_create(&idHilo,NULL,hilo,(void*)mensaje[i]);
  }
  pthread_exit(NULL);
  return 0;
}
void *hilo(void *arg){
  char* men;
  long unsigned int resultadoHilo=0;
  men=(char*)arg;
  printf("%s\n",men);
  resultadoHilo=100;
}
