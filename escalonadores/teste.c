#include <stdio.h>
#include <stdlib.h>

typedef struct processo {
  int identificador;
  int tempoProcessador;
  int tempoExec;
} Processo;

void roundRobin(int numDeProcessos, int janelaTempo) {
  Processo *processos = malloc(numDeProcessos * sizeof(Processo));
  Processo *processosOrdenados = malloc(numDeProcessos * sizeof(Processo));
  int numDeProcessosOrdenados = 0;

  // Preenchendo o vetor de processos com os processos do usuário
  for (int i = 0; i < numDeProcessos; i++) {
    scanf("%d %d", &processos[i].identificador, &processos[i].tempoExec);
    processos[i].tempoExec = processos[i].tempoExec * 1000;
    processos[i].tempoProcessador = 0;
  }
  
  int indiceOrdenado = 0; // Índice para processosOrdenados
  int i = 0; // Índice para percorrer os processos
  
  // Executando o escalonamento em round robin
  while (numDeProcessos > 0) {
    if (processos[i].tempoExec > 0) {
      if (processos[i].tempoExec > janelaTempo) {
        processos[i].tempoExec -= janelaTempo;
        processos[i].tempoProcessador += janelaTempo;
      } else {
        processos[i].tempoProcessador += processos[i].tempoExec;
        processos[i].tempoExec = 0;
        
        processosOrdenados[indiceOrdenado] = processos[i];
        indiceOrdenado++;
        numDeProcessos--;
      }
    }
    
    i = (i + 1) % numDeProcessos;
  }

  // Imprimindo os processos ordenados
  for (int i = 0; i < numDeProcessosOrdenados; i++) {
    printf("%d %.2f\n", processosOrdenados[i].identificador, processosOrdenados[i].tempoProcessador / 1000.0);
  }
  
  free(processos);
  free(processosOrdenados);
}

int main() {
  int numProcessos;
  scanf("%d", &numProcessos);

  int janelaTempo;
  scanf("%d", &janelaTempo);

  roundRobin(numProcessos, janelaTempo);
  
  return 0;
}