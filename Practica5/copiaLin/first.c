#include <stdio.h>
#include <stdio.h>
#include <pthread.h>

void *hilo(void *arg);
int main(void){
  pthread_t idHilo;
  pthread_create(&idHilo,NULL,(void*)hilo,NULL);
  pthread_join(idHilo,NULL);
  return 0;
}

void *hilo(void *arg){
  printf("Hola mundo desde un Hilo en UNIX\n");
  return NULL;
}
