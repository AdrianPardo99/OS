/*Creado por Adrian González Pardo & Melani Betsabee Valdez Esquivel
  Fecha de modificación: 01/05/2019
  Correo electronico:gozapaadr@gmail.com & betsabi100198@gmail.com*/
#include <stdio.h>
#include <stdlib.h>
#define _SVID_SOURCE
#include <dirent.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <pthread.h>
#include <sys/stat.h>
#include <sys/sendfile.h>


char dest[5000]="",source[5000]="",sourceFile[5000]="";
int tamDest;
mode_t Users=(S_IRUSR|S_IWUSR|S_IXUSR|S_IRGRP|S_IWGRP|S_IXGRP|
  S_IROTH|S_IWOTH|S_IXOTH);

int isAnError(int funct){return funct==-1;}

int lenghChar(char *x){return *x?(1+lenghChar(x+1)):(0);}

/*Funcion que copia un archivo a otra direccion o genera una copia simplemente*/
void copyFile(char* source, char* destination){
  int input, output;
  if ((input = open(source, O_RDONLY)) == -1){
    printf("Error al abrir archivo fuente\n");
     exit(-1);
  }
  if ((output = creat(destination, 0660)) == -1){
    printf("Error al abrir path/archivo destino\n");
    close(input);
    exit(-1);
  }
  off_t bytesCopied = 0;
  struct stat fileinfo = {0};
  fstat(input, &fileinfo);
  int result = sendfile(output, input, &bytesCopied, fileinfo.st_size);
  close(input);
  close(output);
}
//Aqui
void *hiloCP(void *arg){
  char *source=(char *)arg;
  int leng=lenghChar(dest),j,i;
  memcpy(dest+leng,"/",1);
  memcpy(dest+leng+1,source+0,lenghChar(source));
  i=lenghChar(dest);
  copyFile(sourceFile,dest);
  for(j=leng;j!=i;j++){*(dest+j)='\0';}
  return NULL;
}

void *hiloMkdir(void *arg){
  char *desti=(char *)arg;
  if(isAnError(chdir(dest))){
    perror("Error al cambiar de directorio destino ");
    exit(1);
  }
  if(isAnError(mkdir(desti,Users))){
    perror("Error al realizar el directorio en el path ");
    exit(1);
  }else{
    printf("Exito al crear el directorio en el path: %s\n",dest);
  }
  if(isAnError(chdir(source))){
    perror("Error al cambiar de directorio origen ");
    exit(1);
  }
  return NULL;
}


void scanDirectory(char *dir){
  struct dirent **namelist;
  char dir2[2000]="";
  pthread_t thread;
  memcpy(dir2+0,dir+0,lenghChar(dir));
  *(dir2+lenghChar(dir2))='/';
  memcpy(source+0,dir2+0,lenghChar(dir2));
  int n,tam=lenghChar(dir2),i,j;
  n=scandir(dir, &namelist, NULL, alphasort);
  if (n < 0){
    perror("Error scandir: ");
  }else{
    int type;
    while (n--){
      type=(unsigned)namelist[n]->d_type;
      if(type==4){
        if(((!memcmp("..",namelist[n]->d_name+0,2))&&
          lenghChar(namelist[n]->d_name)==2)||
          ((!memcmp(".",namelist[n]->d_name+0,1))&&
          lenghChar(namelist[n]->d_name)==1)){
          printf("\n");
        }else{
          memcpy(dir2+tam,namelist[n]->d_name+0,
            lenghChar(namelist[n]->d_name));
          printf("Copia de directorio %s Creado en: %s\n",
            namelist[n]->d_name,dest);
          j=lenghChar(dir2);
          pthread_create(&thread,NULL,hiloMkdir,(void *)namelist[n]->d_name);
          pthread_join(thread,NULL);
          memcpy(dest+tamDest,namelist[n]->d_name+0,
            lenghChar(namelist[n]->d_name));
          *(dest+lenghChar(dest))='/';
          scanDirectory(dir2);
          for(i=tam;i!=j;i++){*(dir2+i+1)='\0';}
          j=lenghChar(dest);
          for(i=tamDest;i!=j;i++){*(dest+i)='\0';}
        }
      }else{
        printf("Copia de archivo: %s Copia en: %s\n",
          namelist[n]->d_name,dest);
        memcpy(dir2+tam,namelist[n]->d_name+0,lenghChar(namelist[n]->d_name));
        memcpy(sourceFile+0,dir2+0,lenghChar(dir2));
        pthread_create(&thread,NULL,hiloCP,(void *)namelist[n]->d_name);
        pthread_join(thread,NULL);
        j=lenghChar(dir2);
        for(i=tam;i!=j;i++){*(dir2+i+1)='\0';}
        for(i=0;i!=5000;i++){*(sourceFile+i)='\0';}
      }
      free(namelist[n]);
    }
    free(namelist);
  }
}

int main(int argc, char *argv[]) {
  if(argc>2){
    memcpy(dest+0,argv[2]+0,lenghChar(argv[2]));
    printf("Source directory: %s\nDestination directory: %s\n"
      "Por favor presiona enter para continuar",argv[1],dest);
    tamDest=lenghChar(dest);
    getchar();
    scanDirectory(argv[1]);
  }else{
    printf("Error por favor ingresa 2 parametros de la"
      " siguiente forma: >_$ %s foo1 foo2\nDonde foo1 es el directorio"
      " origen y foo2 es el directorio destino\n",argv[0]);
    exit(1);
  }
  return 0;
}
