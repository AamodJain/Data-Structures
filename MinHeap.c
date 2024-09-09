// implement min heap
struct MinHeap{
    int* arr;
    int array_size;
    int heap_size;
};

// min heapify
void MinHeapify(struct MinHeap* minHeap, int idx){
    int smallest = idx;
    int left = 2*idx + 1;
    int right = 2*idx + 2;

    if(left < minHeap->heap_size && minHeap->arr[left] < minHeap->arr[smallest]){
        smallest = left;
    }

    if(right < minHeap->heap_size && minHeap->arr[right] < minHeap->arr[smallest]){
        smallest = right;
    }

    if(smallest != idx){
        int temp = minHeap->arr[smallest];
        minHeap->arr[smallest] = minHeap->arr[idx];
        minHeap->arr[idx] = temp;
        MinHeapify(minHeap, smallest);
    }
}

// build min heap
void BuildMinHeap(struct MinHeap* minHeap){
    int n = minHeap->heap_size;
    for(int i = n/2 - 1; i >= 0; i--){
        MinHeapify(minHeap, i);
    }
}

// extract min element
int ExtractMin(struct MinHeap* minHeap){
    if(minHeap->heap_size == 0){
        return -1;
    }

    int root = minHeap->arr[0];
    if(minHeap->heap_size > 1){
        minHeap->arr[0] = minHeap->arr[minHeap->heap_size - 1];
        minHeap->heap_size--;
        MinHeapify(minHeap, 0);
    }
    return root;
}

// get min element
int GetMin(struct MinHeap* minHeap){
    if(minHeap->heap_size == 0){
        return -1;
    }
    return minHeap->arr[0];
}
