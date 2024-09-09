int getSum(int BITree[], int index)
{
    int sum = 0; // Initialize result

    // index in BITree[] is 1 more than the index in arr[]
    index = index + 1;

    // Traverse through the BITree and get the sum using responibility of indices 
    while (index > 0)
    {
        // Add current element of BITree to sum
        sum += BITree[index];

        // updating index 
        index -= index & (-index);
    }
    return sum;
}

void updateBIT(int BITree[], int n, int index, int val)
{
    // index in BITree[] is 1 more than the index in arr[]
    index = index + 1;

    // Traverse though BITree and update the nodes
    while (index <= n)
    {
        // Add 'val' to current node of BI Tree
        BITree[index] += val;

        // Update index 
        index += index & (-index);
    }
}
