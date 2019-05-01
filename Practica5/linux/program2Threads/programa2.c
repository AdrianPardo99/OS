/*Creado por Adrian González Pardo & Melani Betsabee Valdez Esquivel
  Fecha de modificaciótam: 29/04/2019
  Correo electronico:gozapaadr@gmail.com & betsabi100198@gmail.com*/
#include "inOutSystem.h"

char *msgFunction[]={"suma","resta","multiplicacion","transpuesta",
  "inversa","lectura"};
double **mat1,**mat2,**matDes;
int i,j,tam;
struct timeval start,end;
long mtime=0,seconds=0,useconds=0;

/*Funcion que obtiene el tiempo en que se esta ejecutando*/
void getTime(){
  gettimeofday(&end,NULL);
  seconds = end.tv_sec - start.tv_sec;
  useconds = end.tv_usec - start.tv_usec;
  mtime = ((seconds)*1000 + useconds/1000.0)+0.5;
  printf("Tiempo transcurrido de la ejecucion del programa:"
    " %ld millisegundos\n", mtime);
}

/*Hilo que ejecuta las distintas funciones que realiza el programa*/
void *hilo(void *arg){
  printf("Function : %s Thread ID: %ld\n\t",(char *)arg,pthread_self());
  if(!memcmp("lectura",(char *)arg,lenChar("lectura"))){
    printf("Impresión de resultados: \nSuma:\n");
    readMathFile("suma.txt");
    printf("Resta:\n");
    readMathFile("resta.txt");
    printf("Multiplicación:\n");
    readMathFile("multiplicacion.txt");
    printf("Transpuesta:\n");
    readMathFile("transpuesta.txt");
    printf("Inversa:\n");
    readMathFile("inversa.txt");
  }else{
    if(!memcmp("suma",(char *)arg,lenChar("suma"))){
      printf("Suma de matrices\n");
      sumMat(tam,mat1,mat2,matDes);
      createMathFile("suma.txt",matDes,0,tam);
    }else if(!memcmp("resta",(char *)arg,lenChar("resta"))){
      printf("Resta de matrices\n");
      resMat(tam,mat1,mat2,matDes);
      createMathFile("resta.txt",matDes,0,tam);
    }else if(!memcmp("multiplicacion",(char *)arg,lenChar("multiplicacion"))){
      printf("Multiplicación de matrices\n");
      mulMat(tam,mat1,mat2,matDes);
      createMathFile("multiplicacion.txt",matDes,0,tam);
    }else if(!memcmp("transpuesta",(char *)arg,lenChar("transpuesta"))){
      printf("Transpuesta de la matriz 1\n");
      transMat(tam,mat1,matDes);
      createMathFile("transpuesta.txt",matDes,0,tam);
    }else if(!memcmp("inversa",(char *)arg,lenChar("inversa"))){
      double de;
      printf("Inversa de la matriz 1\n");
      invMat(tam,mat1,matDes,&de);
      if(de!=0){
        createMathFile("inversa.txt",matDes,0,tam);;
      }else{
        createMathFile("inversa.txt",matDes,0,-1);;
      }
    }
  }
  return NULL;
}

/*Funcion principal que trabajara con dos matrices previas en dos archivos
  diferentes para realizar las mismas tareas que la practica de procesos
  solo que en esta ocasion usara hilos para su trabajo*/
int main(void){
  gettimeofday(&start,NULL);
  getTime();
  pthread_t thread;
  int i;
  getMatPrin("matriz1.txt");
  mat1=stringToArrDouble(mat1);
  getMatPrin("matriz2.txt");
  mat2=stringToArrDouble(mat2);
  matDes=(double**)malloc(sizeof(double*)*con);
  for(i=0;i!=con;i++){
    matDes[i]=(double*)malloc(sizeof(double)*con);
  }
  tam=con;
  for(i=0;i!=7;i++){
    usleep(10000);
    pthread_create(&thread,NULL,hilo,(void *)msgFunction[i]);
  }

  getTime();
  return 0;
}
