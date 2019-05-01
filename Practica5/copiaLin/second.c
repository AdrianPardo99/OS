#include <stdio.h>
#include <pthread.h>

void *hilo(void *arg);

int main(void){
  pthread_t idHilo;
  char* mensaje="Hola a todos desde el hilo";
  int devolucionHilo;
  pthread_create(&idHilo,NULL,hilo,(void*)mensaje);
  pthread_join(idHilo,(void*)&devolucionHilo);
  printf("Valor de retorno: %d\n",devolucionHilo);
  return 0;
}

void *hilo(void *arg){
  char* men;
  long unsigned int resultadoHilo=0;
  men=(char*)arg;
  printf("%s\n",men);
  resultadoHilo=100;
  pthread_exit((void*)resultadoHilo);
}
