#include<stdio.h>
#include<stdlib.h>

int main(){

int val;
FILE *file;
file = fopen("COM5","w");  //Opening device file

printf("\nInsertar valor: ");
scanf("%d",&val);
printf("\n %d",val);
fprintf(file,"%d",val); //Writing to the file
return 0;
}