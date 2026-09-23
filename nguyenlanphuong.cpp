#include <stdio.h>
int main(){
    int n;
    printf("Enter the number of elements: ");
    scanf("%d", &n);
    int array[n];
    for(int i = 0; i < n; i++){
        printf("Enter number %d: ", i + 1);
        scanf("%d", &array[i]);
    }
    for(int i=0; i<n;i++){
        printf("%d ", array[i]);
    }
    return 0;
} 
//compute* : ham tra ve 1 con tro toi compute
/*
storage s; // object s cua class storage
storage* p = &s // con tro p tro toi object s
p->capacity = 100 // truy cap thanh vien cua object ma p tro toi

*/