#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <string.h>

#define login 100
#define mail 80

typedef struct {
    int id;
    char nome[50];
    float valor;
} jogo;

typedef struct {
    char email[mail];
    char senha[50];
} Usuario;

void menu();
void realizarLogin(Usuario usuarios[], int *user);
void cadastrarUsuario(Usuario usuarios[], int *user);
void menuJogo();
void cadastrarJogo();
void buscarJogo(int id);
void listarJogos();
void excluirJogo(int id);
void editarJogo(int id);
int tamanhoJogos();
void aplicarPromocao();
void salvarUsuarios(Usuario usuarios[], int user);
void carregarUsuarios(Usuario usuarios[], int *user);
int verificarEmail(char email[], Usuario usuarios[], int user);
void exibirMensagemBoasVindas();

int main() {
    setlocale (LC_ALL, "Portuguese");
    Usuario usuarios[login];
    int user = 0;
    int op;

    exibirMensagemBoasVindas();
    system("pause");
    system("cls");
    carregarUsuarios(usuarios, &user);

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
                cadastrarJogo();
                break;
            case 2:
                listarJogos();
                break;
            case 3: {
                int id;
                printf("Informe o id:\n");
                scanf("%d", &id);
                buscarJogo(id);
                break;
            }
            case 4: {
                int id;
                printf("Informe o id do jogo para a exclusão:\n");
                scanf("%d", &id);
                excluirJogo(id);
                system("pause");
                system("cls");
                break;
            }
            case 5: {
                int id;
                printf("Informe o id do jogo para a edição:\n");
                scanf("%d", &id);
                editarJogo(id);
                system("pause");
                system("cls");
                break;
            }
            case 6:
                aplicarPromocao();
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

void cadastrarJogo() {
    FILE* file = fopen("jogo.b", "ab");
    if (file == NULL) {
        printf("Erro ao abrir o arquivo.\n");
        return;
    }
    jogo a;
    printf("Informe o id, nome e valor do jogo:\n");
    scanf("%d %s %f", &a.id, a.nome, &a.valor);
    fwrite(&a, sizeof(jogo), 1, file);
    fclose(file);
    system("pause");
    system("cls");
}

void buscarJogo(int id) {
    FILE* file = fopen("jogo.b", "rb");
    if (file == NULL) {
        printf("Erro ao abrir o arquivo.\n");
        return;
    }
    jogo a;
    int entrou = 0;
    while (fread(&a, sizeof(jogo), 1, file)) {
        if (a.id == id) {
            printf("%d: %s %.2f\n", a.id, a.nome, a.valor);
            entrou = 1;
        }
    }
    if (entrou == 0) {
        printf("Jogo não encontrado\n");
    }
    fclose(file);
    system("pause");
    system("cls");
}


void listarJogos() {
    FILE* file = fopen("jogo.b", "rb");
    if (file == NULL) {
        printf("Erro ao abrir o arquivo.\n");
        return;
    }
    jogo a;
    while (fread(&a, sizeof(jogo), 1, file)) {
        printf("%d %s %.2f\n", a.id, a.nome, a.valor);
    }
    fclose(file);
    system("pause");
    system("cls");
}

int tamanhoJogos() {
    FILE* file = fopen("jogo.b", "rb");
    if (file == NULL) {
        printf("Arquivo não encontrado.\n");
        return 0;
    }
    jogo a;
    int cont = 0;
    while (fread(&a, sizeof(jogo), 1, file)) {
        cont++;
    }
    fclose(file);
    return cont;
}

void excluirJogo(int id) {
    int n = tamanhoJogos();
    if (n == 0) {
        printf("Nenhum jogo cadastrado.\n");
        return;
    }
   jogo *v = (jogo*)malloc(n * sizeof(jogo));
    if (v == NULL) {
        printf("Erro de alocação de memória.\n");
        return;
    }
    FILE* file = fopen("jogo.b", "rb");
    if (file == NULL) {
        printf("Erro ao abrir o arquivo.\n");
        free(v);
        return;
    }
    int i = 0;
    while (fread(&v[i], sizeof(jogo), 1, file)) {
        i++;
    }
    fclose(file);

    file = fopen("jogo.b", "wb");
    if (file == NULL) {
        printf("Erro ao abrir o arquivo.\n");
        free(v);
        return;
    }
    for (i = 0; i < n; i++) {
        if (v[i].id != id) {
            fwrite(&v[i], sizeof(jogo), 1, file);
        }
    }
    fclose(file);
    free(v);
    system("pause");
    system("cls");
}

void editarJogo(int id) {
    FILE *file = fopen("jogo.b", "rb+");
    if (file == NULL) {
        printf("Erro ao abrir o arquivo.\n");
        return;
    }

    jogo temp;
    int encontrado = 0;
    long posicao;
    while (fread(&temp, sizeof(jogo), 1, file)) {
        if (temp.id == id) {
            float novo_preco;
            printf("Informe o novo preço: ");
            scanf("%f", &novo_preco);
            temp.valor = novo_preco;

            posicao = ftell(file);
            fseek(file, posicao - sizeof(jogo), SEEK_SET);
            fwrite(&temp, sizeof(jogo), 1, file);

            encontrado = 1;
            break;
        }
    }

    fclose(file);
    system("pause");
    system("cls");

    if (!encontrado) {
        printf("Jogo com ID %d não encontrado.\n", id);
    }
}

void aplicarPromocao() {
    FILE *file = fopen("jogo.b", "rb+");
    if (file == NULL) {
        printf("Erro ao abrir o arquivo.\n");
        return;
    }

    jogo temp;
    long posicao;
    int encontrou = 0;

    while (fread(&temp, sizeof(jogo), 1, file)) {
        if (temp.valor <= 50.0) {
            encontrou = 1; 
            float novo_valor = temp.valor * 0.9; 
            temp.valor = novo_valor;

            posicao = ftell(file);
            fseek(file, posicao - sizeof(jogo), SEEK_SET);
            fwrite(&temp, sizeof(jogo), 1, file);
        }
    }

    fclose(file);

    if (encontrou) {
        printf("Promoção aplicada com sucesso.\n");
    } else {
        printf("Não há jogos elegíveis para promoção.\n");
    }
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

    *user = fread(usuarios, sizeof(Usuario), login, file);

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
