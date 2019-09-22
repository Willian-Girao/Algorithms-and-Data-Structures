int perfectMatching = 0;
int oddComponents = 0;


struct vertex* queue[MAX];
int adjacencyMatrix[MAX][MAX];
int neighbors[MAX];
int components[MAX];

/* fills lack of edge in adjacency matrix with 0s */
void initiateMatrix(int matrix[MAX][MAX])
{
	for (int i = 0; i < MAX; ++i)
	{
		for (int j = 0; j < MAX; ++j)
		{
			matrix[i][j] = 0;
		}
	}
}

/* structu representing vertex throughout the process */
struct vertex 
{
	int label;
	int visited;
	int component;
};

/* Add edges the form the graph - adjacency matrix */ 
void makeAdjacencyMatrix(int start,int end, int matrix[MAX][MAX])
{
	matrix[start][end] = 1;
	matrix[end][start] = 1;
}

/* adds vertex to queue */
struct vertex* addToQueue(int label, int comp)
{
	struct vertex* vertice = (struct vertex*)malloc(sizeof(struct vertex));
	vertice->label = label;
	vertice->visited = 0;
	vertice->component = comp;
	
	return vertice;
}

/* verifies if label x existis on queue already */
int verifies(int x, struct vertex* queueX[MAX])
{
	for (int i = 0; i < MAX; ++i)
	{
		if (queueX[i]->label == x)
		{
			return 1;
		}
	}

	return 0;
}

int find(struct vertex* queueX[MAX])
{
	int next;
	int flag = 0;
	for (int i = 0; i < MAX; ++i)
	{
		for (int j = 0; j < MAX; ++j)
		{
			
			if (queueX[j]->label == i)
			{
				flag = 1;
			}
			
		}

		if (flag == 0)
		{
			
			return i;
			
		}
		flag = 0;
	}
}

void BFS(int start_vertex, int comp, int matrix[MAX][MAX], struct vertex* queueX[MAX])
{	
	/* place current vertex X into the queue */
	while(matrix[start_vertex][start_vertex] == 5)
	{
		start_vertex++;		
		if (start_vertex == MAX)
		{
			return;
		}			
	}
	int h = 0;
	if (verifies(start_vertex,queueX) == 0)
	{				
		while(queueX[h]->label != -1)
		{		
			h++;
		}		
		queueX[h] = addToQueue(start_vertex, comp);		
	}

	/* finds vertex in queue that needs to have its neighboors explored */
	int w = 0;
	int label;
	while(queueX[w]->visited != 0)
	{		
		w++;
		if (w==MAX)
		{
			return;
		}
	}
	label = queueX[w]->label;

	/* find remaining vertices */
	if (label == -1)
	{
		label = find(queueX);

		if (matrix[label][label] == 5)
		{
			/* check if new label is a removed vertex */
			while(matrix[start_vertex][start_vertex] == 5)
			{
				start_vertex++;
				if (start_vertex == MAX)
				{
					return;
				}
				if (matrix[start_vertex][start_vertex] != 5)
				{
					int h = 0;
					if (verifies(start_vertex,queueX) == 0)
					{				
						while(queueX[h]->label != -1)
						{		
							h++;
						}		
						queueX[h] = addToQueue(start_vertex, comp);		
					}
				}		
			}
		}
		else
		{
			queueX[w]->label = label;				
			comp++;
			queueX[w]->component = comp;
		}		
	}	
	
	/* adds it neighboors to the queue */	
	for (int i = 0; i < MAX; ++i)
	{
		if (matrix[label][i] == 1)
		{	
			int a = 0;				
			/* verifies if label i existis on queue already - adds it to it if it doesnt */			
			if (verifies(i,queueX) == 0)
			{								
				while(queueX[a]->label != -1)
				{					
					a++;
					if(a == MAX)
					{
						a = 6;
						break;
					}
				}				
				queueX[a] = addToQueue(i, comp);				
			}
		}
	}
	
	/* finishes visiting current vertex's neighboors */
	queueX[w]->visited = 1;	

	//printf("label: %d\n", label);
	
	/* recursivelly calls BFS */	
	BFS(label, comp, matrix, queueX);
	
}

void initiateQueue(struct vertex* queueX[MAX])
{
	for (int i = 0; i < MAX; ++i)
	{
		queueX[i] = malloc(sizeof(struct vertex));
		queueX[i] = addToQueue(-1,0);	
	}
}

void countComponents(struct vertex* queueX[MAX])
{
	for (int i = 0; i < MAX; ++i)
	{
		for (int j = 0; j < MAX; ++j)
		{
			if (queueX[j]->component == i && queueX[j]->label != -1)
			{
				components[i]++;
			}
		}
	}

}

void initiateCompCount(int component[MAX])
{
	for (int i = 0; i < MAX; ++i)
	{
		component[i] = 0;
	}
}

//====================================================================================================

int matrix[MAX][MAX];
int removed[MAX];
int tempM[MAX][MAX];

void printMatrix(int matriX[MAX][MAX])
{
	for (int i = 0; i < MAX; ++i)
	{
		for (int j = 0; j < MAX; ++j)
		{
			printf("%d ", matriX[i][j]);
		}
		printf("\n");
	}
}

void initiateRemoved(int remove[MAX])
{
	for (int i = 0; i < MAX; ++i)
	{
		remove[i] = -1;
	}
}

int check(int remove[MAX], int x)
{
	for (int i = 0; i < MAX; ++i)
	{
		if (remove[i] != -1 && remove[i] == x)
		{
			return 1;
		}
	}

	return 0;
}


void matrixOper(int matriX[MAX][MAX], int remove[MAX], int component[MAX], struct vertex* queueX[MAX], int o)
{
	for (int i = 0; i < MAX; ++i)
	{
		for (int j = 0; j < MAX; ++j)
		{
			if (check(remove,i) == 0)
			{
				if (check(remove,j) == 0)
				{
					tempM[i][j] = matrix[i][j];
				}
				else
				{
					tempM[i][j] = 5;
				}
			}
			else
			{
				tempM[i][j] = 5;
			}
		}
	}

	BFS(0,0,tempM, queueX);
	

	countComponents(queueX);

	
	for (int i = 0; i < MAX; ++i)
	{
		if (component[i] % 2)
		{
			oddComponents++;
		}	
	}

	if (oddComponents > o)
	{
		perfectMatching = 1;
		return;
	}
	else
	{
		oddComponents = 0;
	}	

	initiateCompCount(component);
	initiateQueue(queueX);
}

//================================================================================================================

int arr[MAX] = {0}; //vertices
int n = sizeof(arr)/sizeof(arr[0]);

void combinationUtil(int arr[], int data[], int start, int end, 
                     int index, int r,int matrix[MAX][MAX], int removed[MAX], int component[MAX], struct vertex* queueX[MAX]);
 
void printCombination(int arr[], int n, int r,int matrix[MAX][MAX], int removed[MAX], int component[MAX], struct vertex* queueX[MAX])
{
    int data[r];
    
    combinationUtil(arr, data, 0, n-1, 0, r,matrix, removed, component, queueX);
}
 
void combinationUtil(int arr[], int data[], int start, int end,
                     int index, int r,int matrix[MAX][MAX], int removed[MAX], int component[MAX], struct vertex* queueX[MAX])
{    
    if (index == r)
    {
        for (int j=0; j<r; j++)
        {    
            removed[j] = data[j];
        }
        matrixOper(matrix, removed, component, queueX, r);
    
        return;
    }

    for (int i=start; i<=end && end-i+1 >= r-index; i++)
    {
        data[index] = arr[i];
        combinationUtil(arr, data, i+1, end, index+1, r, matrix, removed, component, queueX);
    }
}


//================================================================================================================


