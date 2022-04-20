#include <stdio.h>
#include <stdlib.h> // malloc, rand
#include <time.h> // time

#define MAX_ELEM	20

typedef struct
{
	int *heapArr;
	int	last;
	int	capacity;
} HEAP;

/* Allocates memory for heap and returns address of heap head structure
if memory overflow, NULL returned
*/
HEAP *heapCreate( int capacity);

/* Free memory for heap
*/
void heapDestroy( HEAP *heap);

/* Inserts data into heap
return 1 if successful; 0 if heap full
*/
int heapInsert( HEAP *heap, int data);

/* Reestablishes heap by moving data in child up to correct location heap array
*/
static void _reheapUp( HEAP *heap, int index);

/* Deletes root of heap and passes data back to caller
return 1 if successful; 0 if heap empty
*/
int heapDelete( HEAP *heap, int* dataOut);

/* Reestablishes heap by moving data in root down to its correct location in the heap
*/
static void _reheapDown( HEAP *heap, int index);

/* Print heap array */
void heapPrint( HEAP *heap)
{
	int i;
	int last = heap->last;
	
	for( i = 0; i <= last; i++) 
	{
		printf("%6d", heap->heapArr[i]);
	}
	printf( "\n");
}

int main(void)
{
	HEAP *heap;
	int data;
	int i;
	
	heap = heapCreate(MAX_ELEM);
	
	srand( time(NULL));
	
	for (i = 0; i < MAX_ELEM; i++)
	{
		data = rand() % (MAX_ELEM * 3) + 1; // 1 ~ MAX_ELEM*3 random number
				
		fprintf( stdout, "Inserting %d: ", data);
		
		// insert function call
		heapInsert( heap, data);
		
		heapPrint( heap);
 	}
    
	while (heap->last >= 0)
	{
		// delete function call
		heapDelete( heap, &data);

		printf( "Deleting %d: ", data);

		heapPrint( heap);
 	}
	
	heapDestroy( heap);
	
	return 0;
}


/* Allocates memory for heap and returns address of heap head structure
if memory overflow, NULL returned
*/
HEAP *heapCreate( int capacity){
    HEAP* newHeap = (HEAP*)malloc(sizeof(HEAP));
    int* newArr = (int*)malloc(sizeof(int) * capacity);
    if(newHeap == NULL) return NULL;
    
    newHeap->heapArr = newArr;
    newHeap->last = -1;
    newHeap->capacity = capacity;
    
    return newHeap;
}

/* Free memory for heap
*/
void heapDestroy( HEAP *heap){
    if(heap){
        free(heap->heapArr);
    }
    free(heap);
}

/* Inserts data into heap
return 1 if successful; 0 if heap full
*/
int heapInsert( HEAP *heap, int data){
    if( heap->last == heap->capacity) return 0;
    (heap->last)++;
    heap->heapArr[heap->last] = data;
    _reheapUp( heap, heap->last);
    return 1;
}

/* Reestablishes heap by moving data in child up to correct location heap array
*/
static void _reheapUp( HEAP *heap, int index){
    int parent;
    int temp;
    
    if(!index) return;
    else{
        parent = (index-1)/2;
        if(heap->heapArr[index] > heap->heapArr[parent]){
            temp = heap->heapArr[parent];
            heap->heapArr[parent] = heap->heapArr[index];
            heap->heapArr[index] = temp;
            _reheapUp( heap, parent);
        }
    }
}

/* Deletes root of heap and passes data back to caller
return 1 if successful; 0 if heap empty
*/
int heapDelete( HEAP *heap, int* dataOut){
    if(heap->last == -1) return 0;
    *dataOut = heap->heapArr[0];
    heap->heapArr[0] = heap->heapArr[heap->last];
    (heap->last)--;
    _reheapDown( heap, 0);
    return 1;
}

/* Reestablishes heap by moving data in root down to its correct location in the heap
*/
static void _reheapDown( HEAP *heap, int index){
    int left, right;
    int leftKey, rightKey;
    int lrgSub;
    int temp;
    
    left = 2*index+1;
    right = 2*index+2;
    
    if(&(heap->heapArr[left]) == NULL) return;
    else{
        leftKey = heap->heapArr[left];
        if(&(heap->heapArr[right]) != NULL) rightKey = heap->heapArr[right];
        else rightKey = -1;
        
        if(leftKey > rightKey) lrgSub = left;
        else lrgSub = right;
        
        if(heap->heapArr[index] < heap->heapArr[lrgSub]){
            temp = heap->heapArr[lrgSub];
            heap->heapArr[lrgSub] = heap->heapArr[index];
            heap->heapArr[index] = temp;
            _reheapDown( heap, lrgSub);
        }
    }
    return;
}
