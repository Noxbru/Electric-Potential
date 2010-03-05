/* Este programa ha sido creado por Bruno Jiménez
 * bajo licencia GPL, por tanto, puedes modificar
 * libremente el programa, pero no puedes obtener
 * un beneficio económico de él y tienes que
 * decir que el programa original es mío.
 *
 * Cualquier duda, consejo o mejora para el
 * programa, enviarla por favor a 
 * brunojimen(at)gmail(dot)com
 * Gracias
 */

#include <stdio.h>
#include <math.h>
#include <stdlib.h>

#define TRUE 1
#define FALSE 0

int main(int argc, const char *argv[])
{
	int i,j,n=0;
	int columnas,filas;
	int fin=FALSE;
	char c;
	double aux;
	double precision=0.001;
	double nuevo_potencial;

	printf("Introduce el número de filas\n");
	scanf("%i",&filas);
	printf("Introduce el número de columnas\n");
	scanf("%i",&columnas);
	double potenciales[filas][columnas];
	int usar_fijo[filas][columnas][2];

	/*Trabajamos con "3 capas" en la variable potencial para:
	 * en la primera tenemos los potenciales en el array double
	 * en la segunda tenemos un boolean para saber si hay que actuar sobre la primera o no
	 * en la tercera tenemos el control sobre si tenemos que seguir trabajando */ 

	for(i=0;i<filas;i++) //Con esto iniciamos la red de potenciales a 0
	{
		for(j=0;j<columnas;j++)
		{
			potenciales[i][j]=0;
			usar_fijo[i][j][0]=FALSE;
			usar_fijo[i][j][1]=FALSE;
		}
	}

	printf("¿Quieres dar un potencial a la parte superior? (Y/N)  "); //Podemos dar o no dar potencial a la parte superior
	scanf("%c",&c);
	scanf("%c",&c);
	if(c=='Y' || c=='y')
	{
		printf("Introduce el potencial de la parte superior  ");
		scanf("%lf",&aux);
		for(i=0,j=1;j<columnas-1;j++)
		{
			potenciales[i][j]=aux;
			usar_fijo[i][j][0]=TRUE;
			usar_fijo[i][j][1]=TRUE;
		}
	}

	printf("¿Quieres dar un potencial a la parte inferior? (Y/N)  "); //Podemos dar o no dar potencial a la parte inferior
	scanf("%c",&c);
	scanf("%c",&c);
	if(c=='Y' || c=='y')
	{
		printf("Introduce el potencial de la parte inferior  ");
		scanf("%lf",&aux);
		for(i=filas-1,j=1;j<columnas-1;j++)
		{
			potenciales[i][j]=aux;
			usar_fijo[i][j][0]=TRUE;
			usar_fijo[i][j][1]=TRUE;
		}
	}

	printf("¿Quieres dar un potencial a la parte derecha? (Y/N)  "); //Podemos dar o no dar potencial a la parte derecha
	scanf("%c",&c);
	scanf("%c",&c);
	if(c=='Y' || c=='y')
	{
		printf("Introduce el potencial de la parte derecha  ");
		scanf("%lf",&aux);
		for(i=1,j=columnas-1;i<filas-1;i++)
		{
			potenciales[i][j]=aux;
			usar_fijo[i][j][0]=TRUE;
			usar_fijo[i][j][1]=TRUE;
		}
	}

	printf("¿Quieres dar un potencial a la parte izquierda? (Y/N)  "); //Podemos dar o no dar potencial a la parte izquierda
	scanf("%c",&c);
	scanf("%c",&c);
	if(c=='Y' || c=='y')
	{
		printf("Introduce el potencial de la parte izquierda  ");
		scanf("%lf",&aux);
		for(i=1,j=0;i<filas-1;i++)
		{
			potenciales[i][j]=aux;
			usar_fijo[i][j][0]=TRUE;
			usar_fijo[i][j][1]=TRUE;
		}
	}

	printf("¿Quieres dar un potencial a un punto en particular? (Y/N)  "); //Podemos dar o no dar potencial aun punto
	scanf("%c",&c);
	scanf("%c",&c);
	if(c=='Y' || c=='y')
	{
		printf("Introduce la fila del punto  ");
		scanf("%i",&i);
		printf("Introduce la columna del punto  ");
		scanf("%i",&j);
		printf("Introduce el potencial del punto  ");
		scanf("%lf",&aux);
		potenciales[i][j]=aux;
		usar_fijo[i][j][0]=TRUE;
		usar_fijo[i][j][1]=TRUE;
	}

	printf("Introduce la precisión con la que quieres trabajar (Por defecto 0.001)  ");
	scanf("%lf",&precision);

	while(fin==FALSE)
	{

		for(i=0;i<filas;i++)
		{
			for(j=0;j<columnas;j++)
			{
				if(usar_fijo[i][j][0]==FALSE) usar_fijo[i][j][1]=FALSE;
			}
		}

		for(i=0;i<filas;i++)
		{
			for(j=0;j<columnas;j++)
			{
				if (usar_fijo[i][j][0]==FALSE)			//Aquí empieza el baile de posiciones y medias
				{
					if(i==0)		//Si estamos en la primera fila
					{
						if(j==0)		//Primera fila, primera columna
						{
							nuevo_potencial=(potenciales[i+1][j]+potenciales[i][j+1])/2.;
						}
						else if(j!=0 && j!=columnas-1)		//Primera fila entre la primera y la última columna
						{
							nuevo_potencial=(potenciales[i+1][j]+potenciales[i][j+1]+potenciales[i-1][j])/3.;
						}
						else		//Primera fila, última columna
						{
							nuevo_potencial=(potenciales[i+1][j]+potenciales[i][j-1])/2.;
						}
					}

					else if(i==filas-1)		//Si estamos en la última fila
					{
						if(j==0)		//Última fila, primera columna
						{
							nuevo_potencial=(potenciales[i-1][j]+potenciales[i][j+1])/2.;
						}
						else if(j!=0 && j!=columnas-1)		//Última fila, entre la primera y la última columna
						{
							nuevo_potencial=(potenciales[i-1][j]+potenciales[i][j+1]+potenciales[i-1][j])/3.;
						}
						else		//Última fila, última columna
						{
							nuevo_potencial=(potenciales[i-1][j]+potenciales[i][j+1])/2.;
						}
					}

					else if(j==0 && i!=0 && i!=filas-1)		//Entre la primera y la última fila en la primera columna
					{
						nuevo_potencial=(potenciales[i-1][j]+potenciales[i+1][j]+potenciales[i][j+1])/3.;
					}
					else if(j==columnas-1 && i!=0 && 1!=filas-1)		//Entre la primera y la última fila en la última columna
					{
						nuevo_potencial=(potenciales[i-1][j]+potenciales[i+1][j]+potenciales[i][j-1])/3.;
					}

					else nuevo_potencial=(potenciales[i-1][j]+potenciales[i+1][j]+potenciales[i][j+1]+potenciales[i][j-1])/4.;		//En el resto

					if(fabs(potenciales[i][j]-nuevo_potencial)<precision)
					{
						usar_fijo[i][j][1]=TRUE;
					}

					potenciales[i][j]=nuevo_potencial;
				}
			}
		}

		//Comprobamos si usar_fijo[1]=TRUE para todos, en ese caso fin=TRUE

		fin=TRUE;

		for(i=0;i<filas && fin==TRUE;i++)
		{
			for(j=0;j<columnas && fin==TRUE;j++)
			{
				fin=usar_fijo[i][j][1];
			}
		}
		n++;

		/*
		for(i=0;i<filas;i++)
		{
			for(j=0;j<columnas;j++)
			{
				printf("%.3lf\t",potenciales[i][j]);
			}
			printf("\n\n");
		}
		getchar();
		*/

	}

	for(i=0;i<filas;i++)
	{
		for(j=0;j<columnas;j++)
		{
			printf("%.3lf\t",potenciales[i][j]);
		}
		printf("\n");
	}

	/*
	for(i=0;i<filas;i++)
	{
		for(j=0;j<columnas;j++)
		{
			printf("%i\t",usar_fijo[i][j][0]);
		}
		printf("\n");
	}

	for(i=0;i<filas;i++)
	{
		for(j=0;j<columnas;j++)
		{
			printf("%i\t",usar_fijo[i][j][1]);
		}
		printf("\n");
	}

	printf("%i",n);
	*/

	return 0;
}
