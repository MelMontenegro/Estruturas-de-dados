#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <string.h>

int main() {
    setlocale (LC_ALL, "Portuguese");
    Usuario usuarios[100];
    int user = 0;
    int op;

    exibirMensagemBoasVindas();
    system("pause");
    system("cls");
    carregarUsuarios(usuarios, &user);

    Jogo *lista = NULL;

    do {
        menu();
        scanf("%d", &op);

        switch(op) {
            case 1:
                cadastrarUsuario(usuarios, &user);
                break;
            case 2:
                if (user == 0) {
                    printf("Nenhum usuário cadastrado. Por favor, cadastre-se primeiro.\n");
                } else {
                    realizarLogin(usuarios, &user);
                }
                break;
            case 0:
                printf("Saindo do programa.\n");
                salvarUsuarios(usuarios, user);
                return 0;
            default:
                printf("Opção inválida. Tente novamente.\n");
                break;
        }
    } while (1);
