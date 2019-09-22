/*
	Affiliation:
		Federal university of Amazon - Computer Institute (Bachelor degree in Computer Science)
		Fluminense Federal University - Computer Institute (Master's degree student)
	Author(s): 
		Willian Soares Girão
*/

#define MAX 4

#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include "matrix_temp.h"    

int main(int argc, char *argv[]) 
{
	FILE* inputFile;	
	inputFile = fopen(argv[1],"r");
	int a;
	int b;
	char ch;

	/* initializing */
	initiateMatrix(matrix);
	initiateRemoved(removed);
	initiateQueue(queue);
	initiateCompCount(components);

	/* crating adjacency matrix */
	if (inputFile) 
	{
		ch = getc(inputFile);
		printf("Adjacency Matrix: \n");
		while( (ch = getc(inputFile)) != EOF ) 
		{	
			while(!isdigit(ch) && ch != EOF) 
			{
				ch = getc(inputFile);					
			}
			if (isdigit(ch))
			{
				a = ch - '0';
				ch = getc(inputFile);					
				while(!isdigit(ch) && ch != EOF) 
				{
					ch = getc(inputFile);					
				}
				if (isdigit(ch))
				{
					b = ch - '0';
					makeAdjacencyMatrix(a,b,matrix);
				}					
			}			
  		}  
	} else 
	{
		printf("An input file containing a graph was not provided.\n");
		printf("Provide a file with .txt extension as an argument.\n");
		exit(0);
	}
	fclose(inputFile);
	printf("========================================\n");
	printMatrix(matrix);
	printf("========================================\n");

	/* insert vertices into array used in printCombination function */
	for (int i = 0; i < MAX; ++i)
	{
		arr[i] = i;
	}

	for (int r = 0; r < (MAX-1); ++r)
	{
		printCombination(arr, n, r, matrix, removed, components, queue);
	}	

	if (perfectMatching == 0)
	{
		printf("Result: G HAS a Perfect Matching M.\n");
	}
	else
	{
		printf("Result: G DOES NOT have a Perfect Matching M.\n");
	}

	return 0;
}
