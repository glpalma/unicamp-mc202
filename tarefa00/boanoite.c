#include <stdio.h>

int main() {
    int n, i;
    char nome[50];
    scanf("%d", &n);
    for (i = 0; i < n; i++) {
        scanf("%s", nome);
        printf("Boa noite, %s.\n", nome);
    }

}