typedef struct Jogo { }
typedef struct { }

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
int verificarEmail(char email[], Usuario usuarios[], int user) {}
void exibirMensagemBoasVindas() {}