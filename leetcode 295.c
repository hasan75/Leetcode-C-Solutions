
#define MAX_SIZE 100002

int maxHeap[MAX_SIZE];
int minHeap[MAX_SIZE];

typedef struct MedianFinder{
    int maxHeapSize, minHeapSize;
} MedianFinder;

//// MAX Heap Push Pop
void maxHeapPush(MedianFinder *obj, int value)
{
    int heapSize = obj->maxHeapSize;
	maxHeap[heapSize] = value;

	int current = heapSize;
	while (current > 0 && maxHeap[current] > maxHeap[(current - 1) / 2]) 
	{
		int temp = maxHeap[(current - 1) / 2];
		maxHeap[(current - 1) / 2] = maxHeap[current];
		maxHeap[current] = temp;
		current = (current - 1) / 2;
	}

	obj->maxHeapSize++;

	
}

void maxHeapPop(MedianFinder *obj,int *value)
{

	*value = maxHeap[0];
	obj->maxHeapSize--;
    int heapSize = obj->maxHeapSize;
	maxHeap[0] = maxHeap[heapSize];

	int current = 0;
	while (current * 2 + 1 < heapSize)
	{
		int child;
		if (current * 2 + 2 == heapSize)
		{
			child = current * 2 + 1;
		}
		else
		{
			child = maxHeap[current * 2 + 1] > maxHeap[current * 2 + 2] ? current * 2 + 1 : current * 2 + 2;
		}

		if (maxHeap[current] > maxHeap[child])
		{
			break;
		}

		int temp = maxHeap[current];
		maxHeap[current] = maxHeap[child];
		maxHeap[child] = temp;

		current = child;
	}
	
}
////////////////

///// MIN Heap push pop

void minHeapPush(MedianFinder *obj, int value)
{
    int heapSize = obj->minHeapSize;
	minHeap[heapSize] = value;

	int current = heapSize;
	while (current > 0 && minHeap[current] < minHeap[(current - 1) / 2]) 
	{
		int temp = minHeap[(current - 1) / 2];
		minHeap[(current - 1) / 2] = minHeap[current];
		minHeap[current] = temp;
		current = (current - 1) / 2;
	}

	obj->minHeapSize++;

	
}

void minHeapPop(MedianFinder *obj, int *value)
{

	*value = minHeap[0];
	obj->minHeapSize--;
    
    int heapSize = obj->minHeapSize;
	minHeap[0] = minHeap[heapSize];

	int current = 0;
	while (current * 2 + 1 < heapSize)
	{
		int child;
		if (current * 2 + 2 == heapSize)
		{
			child = current * 2 + 1;
		}
		else
		{
			child = minHeap[current * 2 + 1] < minHeap[current * 2 + 2] ? current * 2 + 1 : current * 2 + 2;
		}

		if (minHeap[current] < minHeap[child])
		{
			break;
		}

		int temp = minHeap[current];
		minHeap[current] = minHeap[child];
		minHeap[child] = temp;

		current = child;
	}
	
}
///////////////


/** initialize your data structure here. */

MedianFinder* medianFinderCreate() {
    MedianFinder* newM = (MedianFinder*) malloc(sizeof(MedianFinder));
    newM->minHeapSize = newM->maxHeapSize = 0;
    return newM;
}

void medianFinderAddNum(MedianFinder* obj, int num) {
    if(obj->minHeapSize == 0 && obj->maxHeapSize == 0){
		/// if both heap is empty then push this number into any of them 
        maxHeapPush(obj, num);
    }
    else if(obj->minHeapSize == 0){
		// if minHeap is empty but maxHeap contains some data
        if(num <= maxHeap[0]){
			//if current num is less than max value of maxHeap, then push it into maxHeap
            maxHeapPush(obj, num);
        }
        else{
            minHeapPush(obj, num);
        }
    }
    
    else if(obj->maxHeapSize == 0){
		//if current num is greater than min value of minHeap, then push it into minHeap
        if(num >= minHeap[0]){
            minHeapPush(obj, num);
        }
        else{
            maxHeapPush(obj, num);
        }
    }
    
    else{
		// push current num into heap accordingly
        if(num <= maxHeap[0]){
            maxHeapPush(obj, num);
        }
        else{
            minHeapPush(obj, num);
        }
    }
    
	//below steps are called balancing -> absolute difference of number of elements between two heap is <= 1
	// reason: suppose current elements is: [19, 10, 5, 2, 7, 13 ]
	// so suppose after above steps maxheap contains [5 2 7 10] & minHeap contains [13, 19]
	// after balancing, maxHeap contains [5 2 7]  & minheap contains [10 19 13]
	// as median is only associated with middle two values, so we only concern about top elements of both heap to calculate median. 
	// ordering of other values in two heaps doesn't matter.  
    if(obj->maxHeapSize > obj->minHeapSize + 1){
        int value;
        maxHeapPop(obj, &value);
        minHeapPush(obj, value);
    }
    else if(obj->maxHeapSize + 1 < obj->minHeapSize ){
        int value;
        minHeapPop(obj, &value);
        maxHeapPush(obj, value);
    }
}

double medianFinderFindMedian(MedianFinder* obj) {
    double now = 0;
	
    if(obj->minHeapSize == obj->maxHeapSize){
		// total number of current elements is even
        now += minHeap[0] + maxHeap[0];
        now /= 2;
    }
    else{
		// total number of current elements is odd, so choose accordingly.
        if(obj->minHeapSize > obj->maxHeapSize){

            now += minHeap[0];
        }
        else{
            now += maxHeap[0];
        }
    }
    
    return now;
}

void medianFinderFree(MedianFinder* obj) {
    free(obj);
}

/**
 * Your MedianFinder struct will be instantiated and called as such:
 * MedianFinder* obj = medianFinderCreate();
 * medianFinderAddNum(obj, num);
 
 * double param_2 = medianFinderFindMedian(obj);
 
 * medianFinderFree(obj);
*/