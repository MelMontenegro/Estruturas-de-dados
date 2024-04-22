#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <string.h>
#include "lojadejogos.h"
#define mail 80

typedef struct Jogo {
    int id;
    char nome[50];
    float valor;
    struct Jogo* proximo;
} Jogo;

typedef struct {
    char email[mail];
    char senha[50];
} Usuario;

void menu();
void realizarLogin(Usuario usuarios[], int *user);
void cadastrarUsuario(Usuario usuarios[], int *user);
void menuJogo();
void cadastrarJogo(Jogo **lista);
void buscarJogo(Jogo *lista, int id);
void listarJogos(Jogo *lista);
void excluirJogo(Jogo **lista, int id);
void editarJogo(Jogo *lista, int id);
void aplicarPromocao(Jogo *lista);
void salvarUsuarios(Usuario usuarios[], int user);
void carregarUsuarios(Usuario usuarios[], int *user);
int verificarEmail(char email[], Usuario usuarios[], int user);
void exibirMensagemBoasVindas();

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

    return 0;
}

void menu() {
    printf("============================\n");
    printf("Escolha uma opção:\n");
    printf("1 - Cadastrar novo usuário\n");
    printf("2 - Realizar Login\n");
    printf("0 - Sair\n");
    printf("============================\n");
}

void realizarLogin(Usuario usuarios[], int *user) {
    char email[mail];
    char senha[50];
    int i;

    printf("=== Realizar Login ===\n");
    printf("E-mail: ");
    scanf("%s", email);
    printf("Senha: ");
    scanf("%s", senha);

    for (i = 0; i < *user; i++) {
        if (strcmp(email, usuarios[i].email) == 0 && strcmp(senha, usuarios[i].senha) == 0) {
            printf("Login bem-sucedido.\n");
            system("pause");
            system("cls");
            menuJogo();
            return;
        }
    }

    printf("E-mail ou senha incorretos. Tente novamente.\n");
    system("pause");
    system("cls");
}

void cadastrarUsuario(Usuario usuarios[], int *user) {
    printf("=== Cadastrar Novo Usuário ===\n");
    char email[mail];
    printf("E-mail (deve conter '@'): ");
    scanf("%s", email);

    if (!strchr(email, '@')) {
        printf("Formato de e-mail inválido. O e-mail deve conter '@'.\n");
        system("pause");
        system("cls");
        return;
    }

    if (verificarEmail(email, usuarios, *user)) {
        printf("Este e-mail já está cadastrado. Tente novamente.\n");
        system("pause");
        system("cls");
        return;
    }

    strcpy(usuarios[*user].email, email);

    printf("Senha: ");
    scanf("%s", usuarios[*user].senha);

    (*user)++;
    printf("Usuário cadastrado com sucesso.\n");
    salvarUsuarios(usuarios, *user);
    system("pause");
    system("cls");
}

void menuJogo() {
    int op;

    Jogo *lista = NULL;

    do {
        printf("============================\n");
        printf("Escolha uma opção:\n");
        printf("1 - Cadastrar Jogo\n");
        printf("2 - Listar Jogos\n");
        printf("3 - Buscar Jogo\n");
        printf("4 - Excluir Jogo\n");
        printf("5 - Editar Preço do Jogo\n");
        printf("6 - Promoções\n");
        printf("0 - Sair\n");
        printf("============================\n");

        scanf("%d", &op);

        switch(op) {
            case 1:
                cadastrarJogo(&lista);
                break;
            case 2:
                listarJogos(lista);
                break;
            case 3: {
                int id;
                printf("Informe o id:\n");
                scanf("%d", &id);
                buscarJogo(lista, id);
                break;
            }
            case 4: {
                int id;
                printf("Informe o id do jogo para a exclusão:\n");
                scanf("%d", &id);
                excluirJogo(&lista, id);
                system("pause");
                system("cls");
                break;
            }
            case 5: {
                int id;
                printf("Informe o id do jogo para a edição:\n");
                scanf("%d", &id);
                editarJogo(lista, id);
                system("pause");
                system("cls");
                break;
            }
            case 6:
                aplicarPromocao(lista);
                system("pause");
                system("cls");
                break;
            case 0:
                printf("Saindo do programa.\n");
                exit(0);
            default:
                printf("Opção inválida. Tente novamente.\n");
                break;
        }
    } while (1);
}

void cadastrarJogo(Jogo **lista) {
    Jogo* novoJogo = (Jogo*)malloc(sizeof(Jogo));
    if (novoJogo == NULL) {
        printf("Erro ao alocar memória para novo jogo.\n");
        return;
    }
    novoJogo->proximo = *lista;

    printf("Informe o id, nome e valor do jogo:\n");
    scanf("%d %s %f", &novoJogo->id, novoJogo->nome, &novoJogo->valor);

    *lista = novoJogo;

    printf("Jogo cadastrado com sucesso.\n");
}

void buscarJogo(Jogo *lista, int id) {
    Jogo* atual = lista;
    while (atual != NULL) {
        if (atual->id == id) {
            printf("%d: %s %.2f\n", atual->id, atual->nome, atual->valor);
            return;
        }
        atual = atual->proximo;
    }
    printf("Jogo não encontrado\n");
}

void listarJogos(Jogo *lista) {
    Jogo* atual = lista;
    while (atual != NULL) {
        printf("%d %s %.2f\n", atual->id, atual->nome, atual->valor);
        atual = atual->proximo;
    }
}

void excluirJogo(Jogo **lista, int id) {
    Jogo* atual = *lista;
    Jogo* anterior = NULL;

    while (atual != NULL) {
        if (atual->id == id) {
            if (anterior == NULL) {
                *lista = atual->proximo;
            } else {
                anterior->proximo = atual->proximo;
            }
            free(atual);
            printf("Jogo removido com sucesso.\n");
            return;
        }
        anterior = atual;
        atual = atual->proximo;
    }

    printf("Jogo não encontrado\n");
}

void editarJogo(Jogo *lista, int id) {
    Jogo* atual = lista;
    while (atual != NULL) {
        if (atual->id == id) {
            float novo_preco;
            printf("Informe o novo preço: ");
            scanf("%f", &novo_preco);
            atual->valor = novo_preco;
            printf("Preço do jogo atualizado com sucesso.\n");
            return;
        }
        atual = atual->proximo;
    }
    printf("Jogo não encontrado\n");
}

void aplicarPromocao(Jogo *lista) {
    Jogo* atual = lista;
    while (atual != NULL) {
        if (atual->valor <= 50.0) {
            float novo_valor = atual->valor * 0.9;
            atual->valor = novo_valor;
        }
        atual = atual->proximo;
    }
    printf("Promoção aplicada com sucesso.\n");
}

void salvarUsuarios(Usuario usuarios[], int user) {
    FILE* file = fopen("usuarios.b", "wb");
    if (file == NULL) {
        printf("Erro ao abrir o arquivo de usuários para salvar.\n");
        return;
    }

    fwrite(usuarios, sizeof(Usuario), user, file);

    fclose(file);
}

void carregarUsuarios(Usuario usuarios[], int *user) {
    FILE* file = fopen("usuarios.b", "rb");
    if (file == NULL) {
        printf("Arquivo de usuários não encontrado. Criando novo arquivo.\n");
        return;
    }

    *user = fread(usuarios, sizeof(Usuario), 100, file);

    fclose(file);
}

int verificarEmail(char email[], Usuario usuarios[], int user) {
    int i;
    for (i = 0; i < user; i++) {
        if (strcmp(email, usuarios[i].email) == 0) {
            return 1;
        }
    }
    return 0;
}

void exibirMensagemBoasVindas() {
    printf("=============================================================\n");
    printf("Bem-vindo ao sistema de cadastro e gerenciamento de jogos!\n");
    printf("=============================================================\n");
}
