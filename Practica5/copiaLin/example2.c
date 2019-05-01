#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <pthread.h>

// Let us create a global variable to change it in threads
int g = 0;

void printProcess(){
  printf("[PPID]=%d\t[PID]=%d\t",getppid(),getpid());
}

// The function to be executed by all threads
void *myThreadFun(void *vargp){
  // Store the value argument passed to this thread
  // Let us create a static variable to observe its changes
  static int s = 0;
  // Change static and global variables
  ++s; ++g;
  // Print the argument, static and global variables
  printf("Thread ID: %ld, Static: %d, Global: %d,GETTID: %d\n", pthread_self(), ++s, ++g,0);
}

int main(){
  int i;
  pthread_t tid;
  // Let us create three threads
  for (i = 0; i < 5; i++)
    pthread_create(&tid, NULL, myThreadFun, (void *)&tid);
  pthread_exit(NULL);
  return 0;
}
