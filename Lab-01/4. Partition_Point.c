#include<Stdio.h>

int main(){
    int n;
    printf("Enter the number of elements in the array: ");
    scanf("%d", &n);

    printf("Enter the sequence of 0's then 1's: ");
    int arr[n];

    for(int i = 0; i < n; i++){
        scanf("%d", &arr[i]);
    }
    
    int low = 0;
    int high = n - 1;

    while(low < high){
        int mid = low + (high - low) / 2;

        if(arr[mid] == 0){
            low = mid + 1;
        } else {
            high = mid;
        }
    }
    printf("The partition point is at index: %d\n", low);
}
    
