#include <stdio.h>
#include <stdbool.h>
#include <limits.h>

typedef struct {
    char nome[10];
    int tempoChegada;
    int tempoExecucao;
    int tempoRestante;
    bool finalizado;
} Processo;

void limparBuffer() {
    int ch;
    while ((ch = getchar()) != '\n' && ch != EOF);
}

int lerInteiro(const char* mensagem) {
    int valor;
    char linha[256];

    while (1) {
        printf("%s", mensagem);
        if (fgets(linha, sizeof(linha), stdin) && sscanf(linha, "%d", &valor) == 1) {
            return valor;
        }
        printf("Entrada invalida! Tente novamente.\n");
    }
}

int main() {
    Processo processos[15];
    int n, tempoAtual = 0;
    bool todosFinalizados;

    do {
        n = lerInteiro("Quantos processos voce deseja inserir (1-15)? ");
    } while (n < 1 || n > 15);

    for(int i = 0; i < n; i++) {
        printf("Nome do processo (ex: A): ");
        scanf("%s", processos[i].nome);
        limparBuffer();

        do {
            processos[i].tempoExecucao = lerInteiro("Tempo de uso da CPU: ");
        } while (processos[i].tempoExecucao <= 0);

        do {
            processos[i].tempoChegada = lerInteiro("Tempo de chegada do processo: ");
        } while (processos[i].tempoChegada < 0);

        processos[i].tempoRestante = processos[i].tempoExecucao;
        processos[i].finalizado = false;
    }

    do {
        int idx = -1;
        int menorTempoRestante = INT_MAX;
        todosFinalizados = true;

        for(int i = 0; i < n; i++) {
            if(processos[i].tempoChegada <= tempoAtual && !processos[i].finalizado && processos[i].tempoRestante < menorTempoRestante) {
                menorTempoRestante = processos[i].tempoRestante;
                idx = i;
            }

            if(!processos[i].finalizado) {
                todosFinalizados = false;
            }
        }

        if(idx != -1) {
            processos[idx].tempoRestante -= 1;
            printf("%d-%s ", tempoAtual, processos[idx].nome);
            tempoAtual++;
            if(processos[idx].tempoRestante == 0) {
                processos[idx].finalizado = true;
            }
        } else {
            tempoAtual++;
        }
    } while(!todosFinalizados);

    return 0;
}
