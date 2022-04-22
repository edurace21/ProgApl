//METODO DE LAGRANGE

#include<stdio.h>
#include<stdlib.h>
#include<math.h>

#define dL 5

double factorial(int n){ //funcion para factorial
	int i;
	double fact = 1;  
    for(i=1;i<=n;i++){    
      fact=fact*i;    
  	} 
	return fact; 
}  

int main(void){
	
	int L = 0;
	
	// para leer los datos del .csv
	FILE * fp = fopen("data1.csv","r");
	
	if(!fp){ //si no abre el archivo.
		printf("\n ERROR! \n\n No se puede abrir el archivo. \n");
		return 0;
	}
	
	int ch = 0; int n = 0; //detectar el numero de lineas del archivo
	while(!feof(fp)){ 		//determinar el numero de datos.
		ch = fgetc(fp);
		if (ch == '\n'){
			n++;
		}
	}
	printf("%d\n",n);
	
	double Xm[dL-1][n]; //coeficientes de Lagrange
	double Es[n]; //Error estandar de cada coeficiente
	int x = 0; int y = 0; int j = 0; //contadores
	
	rewind(fp);
	double matrix1[n][2]; //matriz de datos
	
	while(x<n && y<=2){		//ciclo while para guardar los datos del csv a nuestra matriz
		fscanf(fp, "%lf", &matrix1[x][y]); 	
		if(!feof(fp)){ 
			fscanf(fp,","); 
		} 
		y++;
		if(y == 2){
			x++;
			y = 0;
		}
	}
	
	//IMPRESION DE DATOS
	printf("\nDATOS INGRESADOS: \n\n");
	x = y = 0 ; 	//ciclo while para imprimir los datos
	while (x<n && y<=2){
		
		printf("%.7lf | ", matrix1[x][y]);		//determino impresion con 2 valores decimales
		y++;
		if(y == 2){
			x++;
			y = 0;
			printf("\n");
		}	
	}
	
	//NORMALIZACION DE DATOS
	x = y = 0 ;
	float z1[2] = {9.02,79.53};
	float z2[2] = {0.000542,0.000221};
	while (x<=n && y<2){
//		printf("matrix[%d][%d] = %Lf; ",x,y,matrix1[x][y]);
		matrix1[x][y] = ((matrix1[x][y] - z1[y])*1000) - z2[y];	
//		printf("matrix[%d][%d] = %Lf; z = %d\n",x,y,matrix1[x][y],z[y]);	
		x++;
		if(x == n){
			y++;
			x = 0;
		}	
	}
	
	
while(L<n){
	
/*	//COMBINACIONES
	float comb;
	comb = factorial(n)/(factorial(n-dL)*factorial(dL));
	printf("\n%.0f\n",comb);
*/	
	printf("\n%d\n",L);
	
	//SELECCION DE DATOS AL AZAR
	int nsel = floor (n/dL);
	printf("%d\n\n",nsel);
	double matrix2[dL][2];
	int i = 0; x = y = 0;
	while(x<dL && y<= 2 && i<dL){
		
		matrix2[x][y] = matrix1[x+(nsel*i)+L][y];
		printf("%Lf | ",matrix2[x][y]);
		y++;
		
		if(y == 2){
			x++;
			i++;
			y = 0;
			printf("\n");
		}
		if(x+(nsel*i)+L>=n){
			i = 0;
		}
	}
		
	//MATRIZ DE VANDERMONDE
	double vmatrix[dL][dL+1];
	x = y = 0;
	printf("\n");
	while(x<dL && y<=dL){
		
		if(y<dL){
		vmatrix[x][y] = pow(matrix2[x][0],dL-1-y);
		printf("[%d][%d] = %lf | ",x,y,vmatrix[x][y]);
		} else if(y == dL){
			vmatrix[x][y] = matrix2[x][1];
			printf("[%d][%d] = %lf\n",x,y,vmatrix[x][y]);
		}
		y++;
		if(y==dL+1){
			x++;
			y=0;
		}
	}
	
	//GAUSS JORDAN
	int j, k; i = 0;
	double xi[dL-1];
	double ratio;
	
	for(i=0;i<dL;i++)
		 {
			  if(vmatrix[i][i] == 0.0)
			  {
				   printf("Mathematical Error!");
				   exit(0);
			  }
			  for(j=0;j<dL;j++)
			  {
				   if(i!=j)
				   {
					    ratio = vmatrix[j][i]/vmatrix[i][i];
//					    printf("\n\nratio = %lf",ratio);
					    for(k=0;k<=dL;k++)
					    {
					     	vmatrix[j][k] = vmatrix[j][k] - ratio*vmatrix[i][k];
//					     	printf("\ngjmatrix[%d][%d]=%lf",j,k,vmatrix[j][k]);
					    }
				   }
			  }
		 }
		 /* Obtaining Solution */
		 for(i=0;i<dL;i++)
		 {
		  	xi[i] = vmatrix[i][dL]/vmatrix[i][i];
		 }
		 /* Displaying Solution */
		 printf("\nCOEFICIENTES DE LA REGRESION POLINOMIAL:\n");
		 for(i=0;i<dL;i++) {
		  	printf("x[%d] = %lf\n",dL-1-i, xi[i]);
		  	Xm[i][L] = xi[i];
		 }
	
	//DETERMINAR EL ERROR
	x = y = 0;
	double ye[n];	//Y del modelo
	while(y<n-4 && x<=dL){	//determinar valores Y del modelo para las X respectivas de los datos.
		
		ye[y] = ye[y] + (pow(matrix1[y][0],dL-1-x)*xi[x]);
		x++;
		if(x ==dL){
			printf("\n x = %lf | y = %lf |ye[%d] = %lf",matrix1[y][0],matrix1[y][1],y,ye[y]);
			y++;
			x = 0;
		}
	} 
	printf("\n");
	
	x = y = 0;
	double ds[n];	//desviaciones
	while(x<n-4){		//determinar las desviaciones respectivas para cada valor X de los datos.
		ds[x] = ye[x]-matrix1[x][1];
//		printf("ds[%d] = %lf\n",x,ds[x]);
		x++;
	}
	
//	double Es;
	printf("\n");
	for(x=0;x<n;x++){	//determinar el error estandar Es
		Es[L] = Es[L] + pow(ds[x],2);
	}
	Es[L] = sqrt(Es[L]/(n-1));
	
	printf("ERROR ESTANDAR = %Lf\n\n",Es[L]);
	
	rewind(fp);
	L++;
}

	printf("\n Errores Estandar: \n");
	for(x=0;x<n;x++){
		printf("\nINTENTO %d = %Lf",x,Es[x]);
	}	

	//DETERMINAR EL MODELO MAS PRECISO
	x = y = 0;
	double menor;
	for(x=0;x<n;x++){
		if(Es[x]<menor || x ==0){
			menor = Es[x];
			j = x;
//			printf("\nmenor = %Lf; j = %d",menor,j);
		}
	}
	x = 0;
	printf("\n\nMODELO [%d] MAS PRECISO:\n",j);
	while(x<=dL-1){
		printf("x^%d = %Lf\n",dL-1-x,Xm[x][j]);
		x++;
	}	 
	fclose(fp);
	system("pause");
	return 0;	
}
