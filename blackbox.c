#include <stdio.h>
#include <unistd.h>
#include <limits.h>

int main() {
    int a;
    int b;
    int result;
    
    scanf("%d %d", &a, &b);

    if (a < 0 || b < 0) {
        fprintf(stderr ,"Negative numbers are not accepted for this blackbox\n");
        return 1;
    }
    
    result = a + b;
    if (result < 0) {
        fprintf(stderr ,"Result is greater than an integer\n");
        return 1;
    }

    printf("%d\n", (int)result);
    return 0;
}
