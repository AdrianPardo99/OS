/*Creado por Adrian González Pardo & Melani Betsabee Valdez Esquivel
  Fecha de modificaciótam: 02/04/2019
  Correo electronico:gozapaadr@gmail.com & betsabi100198@gmail.com*/

/*Funcion que suma dos matrices*/
void sumMat(int tam,double **mat,double **mat1,double **des){
  int i,j;
  for(i=0;i!=tam;i++){
    for(j=0;j!=tam;j++){
      des[i][j]=mat[i][j]+mat1[i][j];
    }
  }
}

/*Funcion que resta dos matrices*/
void resMat(int tam,double **mat,double **mat1,double **des){
  int i,j;
  for(i=0;i!=tam;i++){
    for(j=0;j!=tam;j++){
      des[i][j]=mat[i][j]-mat1[i][j];
    }
  }
}

/*Funcion que multiplica dos matrices*/
void mulMat(int tam,double **mat,double **mat1,double **des){
  int i,j,k;
  for(i=0;i!=tam;i++){
    for(j=0;j!=tam;j++){
      des[i][j]=0;
      for(k=0;k!=tam;k++){
        des[i][j]+=mat[i][k]*mat1[k][j];
      }
    }
  }
}

/*Funcion que hace la transpuesta de una matriz*/
void transMat(int tam,double **mat,double **des){
  int i,j;
  for(i=0;i!=tam;i++){
    for(j=0;j!=tam;j++){
      des[j][i]=mat[i][j];
    }
  }
}

/*Funcion que hace la inversa de una matriz*/
void invMat(int tam, double **mat, double **des, double *determ) {
	int i, j, k;
	double factor;
	double **L, *D, *X;
	X =(double*)malloc(sizeof(double)*tam);
  D = (double*)malloc(sizeof(double)*tam);
	L = (double**)malloc(sizeof(double*)*tam);
	for (j = 0; j < tam; j++)
	L[j] = (double*)malloc(sizeof(double)*tam);
	for (k = 0; k < tam - 1; k++) {
		for (i = k+1; i < tam;  i++) {
			factor = mat[i][k]/mat[k][k];
			for (j = k+1; j < tam + 1; j++) {
				mat[i][j] = mat[i][j] - factor * mat[k][j];
			}
		}
	}
  *determ = 1.;
	for (i = 0; i < tam; i++) {
		*determ = *determ * mat[i][i];
	}
	if (*determ != 0) {
		for (i = 0; i < tam; i++) {
			for (j = 0; j < tam; j++) {
				if (i > j) {
					L[i][j] = mat[i][j]/mat[j][j];
					mat[i][j] = 0;
				}
			}
		}
		for (i = 0; i < tam; i++) {
			for (j = 0; j < tam; j++) {
				L[j][j] = 1;
			}
		}
		for (k = 0; k < tam; k++) {
			for (i = 0; i < tam; i++) {
				if (i == k){ L[i][tam] = 1;}
				else{  L[i][tam] = 0;}
			}
			double sum;
			D[0] = L[0][tam];
  		for (i = 1; i < tam; i++) {
       	sum = 0;
       	for (j = 0; j < i; j++) {
				 	sum = sum + L[i][j]*D[j];
       	}
			 	D[i] = L[i][tam] - sum;
		 	}
			for (i = 0; i < tam; i++) {
				mat[i][tam] = D[i];
			}
			X[tam-1] = mat[tam-1][tam]/mat[tam-1][tam-1];
		 	for (i = tam - 2; i > -1; i--) {
				sum = 0;
			 	for (j = i+1; j < tam; j++) {
					sum = sum + mat[i][j]*X[j];
				}
				X[i] = (mat[i][tam] - sum)/mat[i][i];
			}
			for (i = 0; i < tam; i++) {
				des[i][k] = X[i];
			}
		}
	}
}

/*Funcion que imprime una matriz*/
void printMat(int tam,double **mat,int des){
  int i,j;
  for(i=0;i!=tam;i++){
    for(j=0;j!=tam;j++){
      if(des==0){
        printf("%d\t",(int)mat[i][j]);
      }else{
        printf("%.2lf\n",mat[i][j]);
      }
    }
    printf("\n");
  }
}

/*Funcion que libera la memoria de la matriz*/
void freeMem(double **m,double **m1,double **m2){
  free(m);
  free(m1);
  free(m2);
}
