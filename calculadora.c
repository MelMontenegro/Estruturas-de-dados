#include <stdio.h>
int main() {
    float n1, n2, resultado;
    char operacao;
    
    printf("Digite dois numeros:\n");
    scanf("%f%f", &n1, &n2);
    printf("Digite uma operacao: soma (s), subtracao (u), divisao (d), multiplicacao (m): ");
    scanf(" %c", &operacao);  

    switch (operacao) {
        case 's':
            resultado = (n1 + n2);
            break;
        case 'd':
            resultado = (n1 / n2);
            break;
        case 'm':
            resultado = (n1 * n2);
            break;
        case 'u':
            resultado = (n1 - n2);
            break;
        default:
            printf("Operacao invalida.\n");
    }

    printf("Resultado: %.2f\n", resultado);
    return 0;
}
