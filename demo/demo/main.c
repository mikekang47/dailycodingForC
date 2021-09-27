#include <stdio.h>
#include <string.h>


int recursive(int n)
{
    if(n==0)
        return 3;
    else
        return (n+recursive(n-1));
}




int main() {
    int n;
    char *p = "hello world";
    p[1] = NULL;
    printf("%c", p[1]);
}
