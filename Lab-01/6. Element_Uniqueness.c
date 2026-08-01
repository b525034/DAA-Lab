#include<stdio.h>

int main(){
    int n, i, j;

    printf("How many numbers would you like to enter? ");
    scanf("%d", &n);

    int arr[n];

    printf("Enter %d random numbers: ", n);
    
    for(i=0; i<n; i++){
        scanf("%d", &arr[i]);           
    }  

    for(i=0; i<n; i++){

        int alreadyCounted = 0;
        for(j=0; j<i; j++){
            if(arr[i] == arr[j]){
                alreadyCounted = 1;
                break;
            }
        }

        if(alreadyCounted)
           continue;
        
        int freq = 1;

        for(j = i + 1; j < n; j++) {
            if(arr[i] == arr[j]) {
                freq++;
            }
        }

        if(freq > 1) {
            printf("%d is duplicated %d time(s).\n", arr[i], freq - 1);
        }
    }
    
    return 0;
}


    