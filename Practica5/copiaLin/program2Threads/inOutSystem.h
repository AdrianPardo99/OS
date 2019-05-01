/*Creado por Adrian González Pardo & Melani Betsabee Valdez Esquivel
  Fecha de modificación: 29/04/2019
  Correo electronico:gozapaadr@gmail.com & betsabi100198@gmail.com*/
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include <pthread.h>
#include <time.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/time.h>
#include "matriz.h"


mode_t Users=(S_IRUSR|S_IWUSR|S_IXUSR|S_IRGRP|S_IWGRP
  |S_IXGRP|S_IROTH|S_IWOTH|S_IXOTH);

char buffer[2500],lines[2500];;

int con=1;

/*Funcion que analiza si hay un error en la llamada al sistema*/
int isAnError(int a){return a==-1;}

/*Funcion que cuenta la cantidad de caracteres en una cadena de caracteres*/
int lenChar(char *c){return *c?(1+lenChar(c+1)):0;}

/*Funcion que limpia el buffer de la lectura de datos*/
void clearBufferChar(){
  int i;
  for(i=0;i!=2500;i++){
    buffer[i]='\0';
  }
}

/*Funcion que limpia el buffer de la lectura de datos*/
void clearLinesChar(){
  int i;
  for(i=0;i!=2500;i++){
    lines[i]='\0';
  }
}

/*Funcion que lee el contenido de un archivo con llamadas al sistema*/
void readMathFile(char *nameFile){
  int fd;
  if((fd=open(nameFile,O_RDONLY))==-1){
    perror("Error al abrir");
    exit(1);
  }
  read(fd,&lines,2500);
  puts(lines);
  clearLinesChar();
  close(fd);
}

/*Funcion que crea un archivo de texto y le añade el contenido de la
  operacion de la matriz con llamadas al sistema*/
void createMathFile(char *nameFile,double **mat,int des,int tam){
  char *fileChar,***matChar;
  fflush(stdin);
  if(tam==-1){
    fileChar=(char*)malloc(sizeof(char)*3);
    memcpy(fileChar+0,"-0",lenChar("-0"));
    *(fileChar+lenChar(fileChar))='\0';
  }else{
    int i,j;
    matChar=(char***)malloc(sizeof(char**)*tam);
    fileChar=(char*)malloc(sizeof(char)*1500);
    for(i=0;i!=tam;i++){
      matChar[i]=(char**)malloc(sizeof(char*)*tam);
      for(j=0;j!=tam;j++){
        matChar[i][j]=(char*)malloc(sizeof(char)*50);
      }
    }
    for(i=0;i!=tam;i++){
      for(j=0;j!=tam;j++){
        if(des){
          sprintf(matChar[i][j],"%.2f",mat[i][j]);
        }else{
          sprintf(matChar[i][j],"%d",(int)mat[i][j]);
        }
      }
    }
    *(fileChar+0)='\0';
    for(i=0;i!=tam;i++){
      for(j=0;j!=tam;j++){
        memcpy(fileChar+lenChar(fileChar),matChar[i][j],lenChar(matChar[i][j]));
        if(j<tam-1){
          memcpy(fileChar+lenChar(fileChar),"\t",lenChar("\t"));
        }
      }
      memcpy(fileChar+lenChar(fileChar),"\n",lenChar("\n"));
    }
    *(fileChar+lenChar(fileChar))='\0';
    free(matChar);
  }

  int id,ban;
  id=open(nameFile,(O_CREAT | O_WRONLY | O_TRUNC),Users);
  if(isAnError(id)){
    perror("No se pudo crear el archivo: ");
    free(fileChar);
    free(matChar);
    exit(1);
  }else{
    ban=write(id,fileChar,lenChar(fileChar));
    if(isAnError(ban)){
      perror("Error al escribir el archivo: ");
      free(fileChar);
      free(matChar);
      exit(1);
    }else{
      if(isAnError(close(id))){
        perror("Error al cerrar el archivo: ");
        free(fileChar);
        free(matChar);
        exit(1);
      }
    }
  }
}

/*Funcion que crea un archivo de texto y le añade el contenido de una
  matriz con llamadas al sistema*/
void createPrinMat(char *nameFile,double **mat,int des,int tam){
  char *fileChar,***matChar;
  fflush(stdin);
  int i,j;
  matChar=(char***)malloc(sizeof(char**)*tam);
  fileChar=(char*)malloc(sizeof(char)*1500);
  for(i=0;i!=tam;i++){
    matChar[i]=(char**)malloc(sizeof(char*)*tam);
    for(j=0;j!=tam;j++){
      matChar[i][j]=(char*)malloc(sizeof(char)*50);
    }
  }
  for(i=0;i!=tam;i++){
    for(j=0;j!=tam;j++){
      if(des){
        sprintf(matChar[i][j],"%.2f",mat[i][j]);
      }else{
        sprintf(matChar[i][j],"%d",(int)mat[i][j]);
      }
    }
  }
  *(fileChar+0)='\0';
  for(i=0;i!=tam;i++){
    for(j=0;j!=tam;j++){
      memcpy(fileChar+lenChar(fileChar),matChar[i][j],lenChar(matChar[i][j]));
      if(j<tam-1){
        memcpy(fileChar+lenChar(fileChar),",",lenChar(","));
      }
    }
    memcpy(fileChar+lenChar(fileChar),",\n",lenChar(",\n"));
  }
  *(fileChar+lenChar(fileChar))='\0';
  free(matChar);
  int id,ban;
  id=open(nameFile,(O_CREAT | O_APPEND| O_WRONLY | O_TRUNC),Users);
  if(isAnError(id)){
    perror("No se pudo crear el archivo: ");
    free(fileChar);
    free(matChar);
    exit(1);
  }else{
    ban=write(id,fileChar,lenChar(fileChar));
    if(isAnError(ban)){
      perror("Error al escribir el archivo: ");
      free(fileChar);
      free(matChar);
      exit(1);
    }else{
      if(isAnError(close(id))){
        perror("Error al cerrar el archivo: ");
        free(fileChar);
        free(matChar);
        exit(1);
      }
    }
  }
}

/*Funcion que lee un archivo de texto por llamada al sistema*/
void getMatPrin(char *nameFile){
  int fd;
  if((fd=open(nameFile,O_RDONLY))==-1){
    perror("Error al abrir");
    exit(1);
  }
  read(fd,&buffer,2500);
  *(buffer+lenChar(buffer)-1)='\0';
  close(fd);
}

/*Funcion que convierte el texto del buffer al array de la matriz*/
double **stringToArrDouble(double **mat){
  int i,j=lenChar(buffer);
  con=1;
  for(i=0;i!=j;i++){
    if(*(buffer+i)=='\n' || *(buffer+i)=='\0'){
      break;
    }else if(*(buffer+i)==','){
      con++;
    }
  }
  mat=(double**)malloc(sizeof(double*)*con);
  for(i=0;i!=con;i++){
    mat[i]=(double*)malloc(sizeof(double)*con);
  }
  char cen[100];
  int k=0,l=0,s=0;
  i=0;
  while(*(buffer+i)){
    if(*(buffer+i)==','){
      cen[s]='\0';
      mat[k][l]=atof(cen);
      if(l+1==con){
        l=0;
        k++;
      }else{
        l++;
      }
      s=0;
    }else if(*(buffer+i)>='0'||*(buffer+i)<='9'){
      cen[s]=buffer[i];
      s++;
    }
    i++;
  }
  return mat;
}
