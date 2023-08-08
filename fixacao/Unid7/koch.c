#include <stdio.h>

void koch(int nivel, int larg) {
    if (nivel == 1) {
        desenhar(larg);
        girar(60);
        desenhar(larg);
        girar(-120);
        desenhar(larg);
        girar(60);
        desenhar(larg);
    } else {
        koch(nivel - 1, larg - 1);
        girar(60);
        koch(nivel - 1, larg - 1);
        girar(-120);
        koch(nivel - 1, larg - 1);
        girar(60);
        koch(nivel - 1, larg - 1);
    }
}
