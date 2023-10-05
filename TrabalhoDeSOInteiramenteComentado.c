// Inclus�o das bibliotecas necess�rias
#include <stdio.h>    // Usada para opera��es de entrada e sa�da (como printf e scanf)
#include <stdbool.h>  // Usada para usar tipos booleanos (true e false)
#include <limits.h>   // Usada para definir constantes, como INT_MAX

// Defini��o da estrutura de um processo
typedef struct {
    char nome[10];          // Nome do processo
    int tempoChegada;       // Tempo em que o processo chega � fila
    int tempoExecucao;      // Tempo total que o processo leva para executar
    int tempoRestante;      // Tempo restante para o processo finalizar
    bool finalizado;        // Flag indicando se o processo foi finalizado
} Processo;

// Fun��o para limpar o buffer de entrada
// Isso � necess�rio porque, �s vezes, o buffer cont�m caracteres indesejados que podem afetar a leitura subsequente
void limparBuffer() {
    int ch;
    while ((ch = getchar()) != '\n' && ch != EOF);
}

// Fun��o que l� um inteiro do usu�rio e trata erros
// Continua pedindo uma entrada at� que o usu�rio insira um n�mero inteiro v�lido
int lerInteiro(const char* mensagem) {
    int valor;             // Valor que ser� retornado
    char linha[256];       // Buffer para armazenar a entrada do usu�rio

    // Loop at� que uma entrada v�lida seja fornecida
    while (1) {
        printf("%s", mensagem);
        // fgets l� uma linha do stdin e sscanf tenta interpretar essa linha como um inteiro
        if (fgets(linha, sizeof(linha), stdin) && sscanf(linha, "%d", &valor) == 1) {
            return valor;  // Retorna o valor lido se for v�lido
        }
        // Mensagem de erro para o usu�rio
        printf("Entrada invalida! Tente novamente.\n");
    }
}

int main() {
    Processo processos[15];  // Array para armazenar at� 15 processos
    int n;                   // N�mero de processos que o usu�rio deseja inserir
    int tempoAtual = 0;      // Mant�m o controle do tempo atual durante a execu��o dos processos
    bool todosFinalizados;   // Flag para verificar se todos os processos foram finalizados

    // Ler o n�mero de processos
    do {
        n = lerInteiro("Quantos processos voce deseja inserir (1-15)? ");
    } while (n < 1 || n > 15);

    // Ler detalhes de cada processo
    for(int i = 0; i < n; i++) {
        printf("Nome do processo (ex: A): ");
        scanf("%s", processos[i].nome);
        limparBuffer();

        // Ler o tempo de execu��o do processo e garantir que seja positivo
        do {
            processos[i].tempoExecucao = lerInteiro("Tempo de uso da CPU: ");
        } while (processos[i].tempoExecucao <= 0);

        // Ler o tempo de chegada do processo e garantir que n�o seja negativo
        do {
            processos[i].tempoChegada = lerInteiro("Tempo de chegada do processo: ");
        } while (processos[i].tempoChegada < 0);

        // Inicializar os valores restantes
        processos[i].tempoRestante = processos[i].tempoExecucao;
        processos[i].finalizado = false;
    }

    // Loop principal do escalonador SRTF (Shortest Remaining Time First)
    do {
        int idx = -1;                           // �ndice do processo que ser� executado neste ciclo
        int menorTempoRestante = INT_MAX;       // Usado para encontrar o processo com o menor tempo restante
        todosFinalizados = true;                // Sup�e que todos os processos est�o finalizados e ajusta conforme necess�rio

        // Varre todos os processos para encontrar o que deve ser executado
        for(int i = 0; i < n; i++) {
            if(processos[i].tempoChegada <= tempoAtual && !processos[i].finalizado && processos[i].tempoRestante < menorTempoRestante) {
                menorTempoRestante = processos[i].tempoRestante;
                idx = i;
            }

            // Se algum processo n�o estiver finalizado, ajusta a flag
            if(!processos[i].finalizado) {
                todosFinalizados = false;
            }
        }

        // Se encontramos um processo para executar
        if(idx != -1) {
            processos[idx].tempoRestante -= 1;   // Reduz o tempo restante do processo
            printf("%d-%s ", tempoAtual, processos[idx].nome);  // Imprime o processo em execu��o
            tempoAtual++;                        // Avan�a o tempo

            // Se o tempo restante do processo for 0, ele foi conclu�do
            if(processos[idx].tempoRestante == 0) {
                processos[idx].finalizado = true;
            }
        } else {
            // Se nenhum processo pode ser executado neste ciclo, apenas avan�a o tempo
            tempoAtual++;
        }
    } while(!todosFinalizados);  // Continua o loop enquanto houver processos n�o finalizados

    return 0;  // Termina o programa
}

