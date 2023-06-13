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
  int indiceOrdenados = 0;

  //preenchendo o vetor de processos com os processos do usuário
  for(int i = 0; i < numDeProcessos; i++) {
    scanf("%d %d", &processos[i].identificador, &processos[i].tempoExec);
    processos[i].tempoExec = processos[i].tempoExec * 1000;
    processos[i].tempoProcessador = 0;
  }
  
  for (int i = 0; ; i = (i + 1) % numDeProcessos) {
    if(processos[i].tempoExec > janelaTempo) {
      processos[i].tempoExec -= janelaTempo;
      processos[i].tempoProcessador += janelaTempo;
    } else {
      processos[i].tempoProcessador += processos[i].tempoExec;
      processos[i].tempoExec = 0;
    }
    if(processos[i].tempoExec == 0) {
      processosOrdenados[indiceOrdenados] = processos[i];
      indiceOrdenados++;
      numDeProcessos--;
    }
    if(numDeProcessos == 0) {
      break;
    }
  }

  for(int i = 0; i < indiceOrdenados; i++) {
    printf("%d %d\n", processosOrdenados[i].identificador, processosOrdenados[i].tempoProcessador);
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
  
}