//CODIGO PARA REGRESION POLINOMIAL GRADOS 2 A 10.

#include<stdio.h>
#include<stdlib.h>
#include<math.h>

int main(void){
	
	int i = 2; int j = 0;
	int x; int y; //contadores
	double Es[9]; //Error estandar
	double Xm[10][9]; //coeficientes de modelos
	
while(i<=10){
	
	FILE * fp = fopen("data1e.csv","r");
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
//	printf("%d\n",n);
	rewind(fp);

	int m = i; 	// orden del polinomio
	double matrix1[n][2]; //matriz de datos
	double xs[2*m]; //array para almacenar valores x,y,x2,x3,x4,etc
	double ys[m+1]; //array para almacenar xy,x2y,x3y,etc
	double gjmatrix[m+1][m+2]; //matriz pa reduccion gauss jordan
	x = y = 0;	//contadores
		
	while(x<n && y<=2){		//ciclo while para guardar los datos del csv a nuestra matriz
		fscanf(fp, "%Lf", &matrix1[x][y]); 	
		if(!feof(fp)){ 
			fscanf(fp,","); 
		} 
		y++;
		if(y == 2){
			
			if(matrix1[x][0]<9.023 || matrix1[x][0]>9.027 || matrix1[x][1]<79.530 || matrix1[x][1]>79.535){
			matrix1[x][0] = matrix1[x-1][0];
			matrix1[x][1] = matrix1[x-1][1];
			}
			
			x++;
			y = 0;
		}
	}
		
	//NORMALIZACION DE DATOS
	x = y = 0 ;
	float z[2] = {9.02,79.53};
	while (x<=n && y<2){
//		printf("matrix[%d][%d] = %Lf; ",x,y,matrix1[x][y]);
		matrix1[x][y] = (matrix1[x][y] - z[y])*1000;	
//		printf("matrix[%d][%d] = %Lf; z = %d\n",x,y,matrix1[x][y],z[y]);	
		x++;
		if(x == n){
			y++;
			x = 0;
		}	
	}
	
	x = y = 0;
	double s = 0;
	while(x<=n && y<2*m){ //ciclo while genera las sumatorias de potencias
		
		xs[y] = xs[y] + pow(matrix1[x][0],y+1); //sumatoria de potencias de x
//		printf("\nxs[%d] = %lf",y,xs[y]);
		if(y<=m+1) {
			ys[y] = ys[y] + pow(matrix1[x][0],y)*matrix1[x][1]; //sumatoria de potencias de xy
		}
			if(y < m){
				s = xs[0];
			}
			if(y>=m && xs[0] != s){
				xs[0] = s;
			}
//		printf("\n%lf\n",xs[0]);
		x++;
		if(x == n){
			y++;
			x = 0;
//			printf("\n");
		}
	}
	
	x = y = 0;
	while(x<m+1 && y<=m+2){ //ciclo while genera matriz de sumatorias
		//aumenta el grado de la variable a medida que aumenta la fila
		//crea la matriz del sistema de ecuaciones.
		
		if(x == 0 && y == 0){
			gjmatrix[x][y] = n;
			y++;
		} else if(y<m+1){
			gjmatrix[x][y] = xs[y+x-1];
			y++;
		} else if(y == m+1){
			gjmatrix[x][y] = ys[x];
			y++;
		}
		if(y == m+2){
			x++;
			y = 0;
		}
	}
		
	printf("\n\nMATRIZ PARA REGRESION \n\n");
	x = y = 0 ; 	
	while (x<m+1 && y<=m+2){ // impresion del sistema de ecuaciones
		
		printf("%Lf | ", gjmatrix[x][y]);		
		y++;
		if(y == m+2){
			x++;
			y = 0;
			printf("\n");
		}	
	}
	printf("\n"); 


	//GAUSS JORDAN
	printf("\n");
	x = y = 0;
	int k;
	double xi[m+1][9];
	double ratio;
	
	for(x=0;x<m+1;x++)
		 {
			  if(gjmatrix[x][x] == 0.0)
			  {
				   printf("Mathematical Error!");
				   exit(0);
			  }
			  for(y=0;y<m+1;y++)
			  {
				   if(x!=y)
				   {
					    ratio = gjmatrix[y][x]/gjmatrix[x][x];
//					    printf("\n\nratio = %lf",ratio);
					    for(k=0;k<=m+1;k++)
					    {
					     	gjmatrix[y][k] = gjmatrix[y][k] - ratio*gjmatrix[x][k];
//					     	printf("\ngjmatrix[%d][%d]=%lf",j,k,gjmatrix[j][k]);
					    }
				   }
			  }
		 }
		 /* Obtaining Solution */
		 for(x=0;x<m+1;x++)
		 {
		  	xi[x][j] = gjmatrix[x][m+1]/gjmatrix[x][x];
		 }

		 printf("\nCOEFICIENTES DE LA REGRESION POLINOMIAL:\n");
		 for(x=0;x<m+1;x++) {
		  	printf("x[%d] = %Lf\n",x, xi[x][j]);
		  	Xm[x][j] = xi[x][j];
		 }
	
		printf("\n y = ");
		for(x=0;x<m+1;x++) {
			if(xi[x][j]>= 0){
				printf("+");
			}
		  	printf(" %lf*x^%d ",xi[x][j],x);
		 }
	printf("\n");

	//DETERMINAR EL ERROR
	x = y = 0;
	double ye[n];	//Y del modelo
	while(y<n && x<=m+1){	//determinar valores Y del modelo para las X respectivas de los datos.
		
		ye[y] = ye[y] + pow(matrix1[y][0],x)*xi[x][j];
		x++;
		if(x == m+1){
			y++;
			x = 0;
		}
	} 
	printf("\n");
	
	x = y = 0;
	double ds[n];	//desviaciones
	while(x<n){		//determinar las desviaciones respectivas para cada valor X de los datos.
		ds[x] = ye[x]-matrix1[x][1];
//		printf("ds[%d] = %lf\n",x,ds[x]);
		x++;
	}
	
	printf("\n");
	for(x=0;x<n;x++){	//determinar el error estandar Es
		Es[j] = Es[j] + pow(ds[x],2);
	}
	Es[j] = sqrt(Es[j]/(n-1));
	
	printf("ERROR ESTANDAR = %Lf\n\n",Es[j]);
		
	fclose(fp);
	i++;
	j++;
//	system("pause");
}

	printf("\n Errores Estandar: \n");
	for(x=0;x<=8;x++){
		printf("\nx^%d = %Lf",x+2,Es[x]);
	}	

	//DETERMINAR EL MODELO MAS PRECISO
	x = y = 0;
	double menor;
	for(x=0;x<=8;x++){
		if(Es[x]<menor || x ==0){
			menor = Es[x];
			j = x;
//			printf("menor = %Lf; j = %d",menor,j);
		}
	}
	x = 0;
	printf("\n\nMODELO [%d] MAS PRECISO:\n",j+2);
	while(x<=j+2){
		printf("x^%d = %Lf\n",x,Xm[x][j]);
		x++;
	}
	
	printf("\n y = ");
		for(x=0;x<=j+2;x++) {
			if(Xm[x][j]>= 0){
				printf("+");
			}
		  	printf(" %lf*x^%d ",Xm[x][j],x);
		 }
	printf("\n");	
		
	return 1;
}
