// select function to find the kth smallest element through median of medians algorithm
int select(int *arr, int n, int K) {
    // base case
    if (n == 1) {
        return arr[0];
    }
    // calculating the size of array b which contains the elements of each segment of 5 elements
    int b_size = (n + 4) / 5;
    int *b = (int *)malloc(b_size * sizeof(int)); // intialising array b

    if (b == NULL) { // handling exception/error while intialising b
        perror("Memory allocation failed");
        exit(EXIT_FAILURE);
    }
    // updating array b;
    for (int i = 0; i < n; i += 5) {
        // creating temporary array temp to hold a segment of 5 elements
        int temp_size = (i + 5 <= n) ? 5 : (n - i);
        int *temp = (int *)malloc(temp_size * sizeof(int));
        if (temp == NULL) { // handling exception/error while intialising temp
            perror("Memory allocation failed");
            free(b);
            exit(EXIT_FAILURE);
        }
        // updating temp
        for (int j = 0; j < temp_size; j++) {
            temp[j] = arr[i + j];
        }

        qsort(temp, temp_size, sizeof(int), cmp); // sorting temp
        b[i / 5] = temp[temp_size / 2]; // finding the median and storing it in b

        free(temp); // deallocating the memory allocated to temp
    }
 
    int m = select(b, b_size, b_size / 2); // finding the median of medians 
    free(b); // deallocating the memory allocated to b

    int q = 0; // storing the number of elements smaller than m in q
    for (int i = 0; i < n; i++) {
        if (arr[i] < m) {
            q++;
        }
    }
    // case : when the median of medains is the Kth smallest element
    if (K == q + 1) {
        return m;
    }

    // intialising two arrays left and right to hold the elements smaller and larger than m respectively
    int *left = (int *)malloc(q * sizeof(int));
    int *right = (int *)malloc((n - q - 1) * sizeof(int));
    if (left == NULL || right == NULL) { // handling exception/error while intialising left or right
        perror("Memory allocation failed");
        exit(EXIT_FAILURE);
    }

    // updating left and right array 
    int left_index = 0, right_index = 0;
    for (int i = 0; i < n; i++) {
        if (arr[i] < m) {
            left[left_index++] = arr[i];
        } else if (arr[i] > m) {
            right[right_index++] = arr[i];
        }
    }
    // finding the Kth smallest element recursively
    int result;
    if (K <= q) {
        result = select(left, q, K);
    } else {
        result = select(right, n - q - 1, K - q - 1);
    }

    // deallocating the memory allocated to left and right
    free(left);
    free(right);

    return result; // returning the result
} 
