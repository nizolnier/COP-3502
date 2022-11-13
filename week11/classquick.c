int partition(int arr[], int left, int right) {
    int pi = left + rand()%(right-left+1);

    swap(&arr[left], &arr[pi]);
    pi = left;

    left++;

    while(arr[left] <= arr[pi]) left++;

    while(arr[right] >= arr[pi]) right--;

    if(left < right)
        swap(&arr[left], &arr[right]);

    swap(&arr[right], &arr[pi]);
    
    return right;

}

void quickSort(int arr[], int left, int right) {
    if(left < right) {
        int k = partition(arr, left, right);

        quickSort(arr, left, k-1);
        quickSort(arr, k+1, right);
    }
}