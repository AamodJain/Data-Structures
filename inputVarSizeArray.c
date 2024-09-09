void inputUserarray(int **arr, int *n)
{
    char buffer[1024];
    printf("Please input an integer array with space-separator and press Enter when done: ");

    // Reading the entire line of input
    fgets(buffer, sizeof(buffer), stdin);

    // intialize the array with 10 elements
    *arr = (int *)malloc(10 * sizeof(int)); // Start with space for 10 elements
    *n = 0;
    int capacity = 10;

    // Parsing the input line
    char *token = strtok(buffer, " ");
    while (token != NULL)
    {
        // Resizing the array if needed
        if (*n >= capacity)
        {
            capacity *= 2;
            *arr = (int *)realloc(*arr, capacity * sizeof(int));
        }

        (*arr)[*n] = atoi(token);
        (*n)++;

        token = strtok(NULL, " ");
    }
}
