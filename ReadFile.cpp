void readFile(char *filename, int **arr, int *n)
{
    FILE *file = fopen(filename, "r");
    // check if the file was opened successfully
    if (!file)
    {
        printf("Unable to open file\n");
        exit(1);
    }

    // calculate the number of integers in the file
    int temp;
    *n = 0;
    while (fscanf(file, "%d", &temp) == 1)
    {
        (*n)++;
    }

    // Allocating memory for the array
    *arr = (int *)malloc(*n * sizeof(int));
    if (*arr == NULL) // Check if the memory allocation was successful
    {
        printf("Memory allocation failed\n");
        fclose(file);
        exit(1);
    }

    // read the integers into the array
    rewind(file); // Reset the file pointer to the beginning of the file
    for (int i = 0; i < *n; i++)
    {
        fscanf(file, "%d", &(*arr)[i]);
    }
    // close the file
    fclose(file);
}

