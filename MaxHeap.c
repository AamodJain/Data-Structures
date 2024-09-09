// implement max heap 

struct MaxHeap{
    int* arr;
    int array_size;
    int heap_size;
};

// max heapify
void MaxHeapify(struct MaxHeap* maxHeap, int idx){
    int largest = idx;
    int left = 2*idx + 1;
    int right = 2*idx + 2;

    if(left < maxHeap->heap_size && maxHeap->arr[left] > maxHeap->arr[largest]){
        largest = left;
    }

    if(right < maxHeap->heap_size && maxHeap->arr[right] > maxHeap->arr[largest]){
        largest = right;
    }

    if(largest != idx){
        int temp = maxHeap->arr[largest];
        maxHeap->arr[largest] = maxHeap->arr[idx];
        maxHeap->arr[idx] = temp;
        MaxHeapify(maxHeap, largest);
    }
}

// build max heap  
void BuildMaxHeap(struct MaxHeap* maxHeap){
    int n = maxHeap->heap_size;
    for(int i = n/2 - 1; i >= 0; i--){
        MaxHeapify(maxHeap, i);
    }
}

// extract max element
int ExtractMax(struct MaxHeap* maxHeap){
    if(maxHeap->heap_size == 0){
        return -1;
    }

    int root = maxHeap->arr[0];
    if(maxHeap->heap_size > 1){
        maxHeap->arr[0] = maxHeap->arr[maxHeap->heap_size - 1];
        maxHeap->heap_size--;
        MaxHeapify(maxHeap, 0);
    }
    return root;
}
