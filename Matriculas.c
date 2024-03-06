#include <stdio.h>
#include <locale.h>
struct Aluno {
    int mat;
    char nome[10];
    float media;

};

int buscaBinaria(struct Aluno v[], int n, int mat){
    int i = 0;
    int f = n - 1;
    while (i <= f) {
        int meio = (i + f)/2;
        if (v[meio].mat == mat) {
            return meio;
        }
        else if (v[meio].mat < mat){
            i = meio  + 1;
        } else {
            f = meio - 1;
        }
    }
    return -1;
}    
int main(void){
    setlocale (LC_ALL, "Portuguese");
    int n;
    int i;
    printf("Informe a quantidade de alunos:\n");
    scanf("%d", &n);
    struct Aluno v[n];
    printf("informe o nome dos alunos");
    for(i = 0; i <n; i++) {
    scanf("%d %s %f", &v[i].mat, v[i].nome, &v[i].media);
    }
    int mat;
    printf("informe a matricula dos alunos");
    scanf("%d", &mat);
    int r = buscaBinaria(v, n, mat);
    if (r != -1) {
        printf("Alunos: %s\n", v[r].nome);
    }
    else {
        printf("Aluno não encontrado\n");
    }
}