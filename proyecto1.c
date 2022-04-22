#include<stdio.h>
#include<stdlib.h>
#include<math.h>

#define dL 5

int main(void){
	
	int ask;
in:
	printf("\nSELECCIONE EL METODO PARA GENERAR EL MODELO: ");
	printf("\nINTERPOLACION DE LAGRANGE(0)-------------REGRESION POLINOMIAL(1)\n");
	scanf("%d",&ask);
	
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
	
	//ZOOM DE DATOS
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
	if(ask == 0){
		
	//LAGRANGE
	printf("INTERPOLACION DE LAGRANGE: \n");
	double Xm[dL-1][n]; //coeficientes de Lagrange
	double Es[n]; //Error estandar de cada coeficiente
	
while(L<floor(n/2)){
	
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
//			printf("\n x = %lf | y = %lf |ye[%d] = %lf",matrix1[y][0],matrix1[y][1],y,ye[y]);
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
	for(x=0;x<floor(n/2);x++){
		printf("\nINTENTO %d = %Lf",x,Es[x]);
	}	

	//DETERMINAR EL MODELO MAS PRECISO
	x = y = 0;
	double menor;
	for(x=0;x<floor(n/2);x++){
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
		
	}
	
	if (ask == 1){
		
		//POLINOMIAL
		printf("\nREGRESION POLINOMIAL:\n");
		int i = 2; int j = 0;
		double Es[9]; //Error estandar
		double Xm[10][9]; //coeficientes de modelos
		
		while(i<=10){

	int m = i; 	// orden del polinomio
	double xs[2*m]; //array para almacenar valores x,y,x2,x3,x4,etc
	double ys[m+1]; //array para almacenar xy,x2y,x3y,etc
	double gjmatrix[m+1][m+2]; //matriz pa reduccion gauss jordan
	x = y = 0;	//contadores

	double s = 0;
	while(x<=n && y<2*m){ //ciclo while para las sumatorias de potencias
		
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

/*	printf("\nVALORES DE SUMATORIA X\n\n");
	for(x=0;x<2*m;x++){
		printf(" %Lf |",xs[x]);
	}
	printf("\n\n");
	
	printf("\nVALORES DE SUMATORIA Y\n\n");
	for(x=0;x<1+m;x++){
		printf(" %Lf |",ys[x]);
	}
	printf("\n\n");
*/
	
	x = y = 0;
	while(x<m+1 && y<=m+2){ //ciclo while para la formula de sumatorias
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
		
/*	printf("\n\nMATRIZ PARA REGRESION \n\n");
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
*/

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

	//DETERMINAR EL ERROR
	x = y = 0;
	double ye[n];	//Y del modelo
	while(y<n && x<=m+1){	//determinar valores Y del modelo para las X respectivas de los datos.
		
		ye[y] = ye[y] + pow(matrix1[y][0],x)*xi[x][j];
		x++;
		if(x == m+1){
//			printf("\n x = %lf | y = %lf |ye[%d] = %lf",matrix1[y][0],matrix1[y][1],y,ye[y]);
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
		
	}
//////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////
		
	fclose(fp);
	system("pause");
	return 0;
}