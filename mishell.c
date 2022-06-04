#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include "leercadena.h"

int main(int argc, char* argv[]) {
    	char command[256];
    	char **comando;
        int largoMatriz;
        int procesos[30];
        int largoProcesos = 0;
        int esBg = 0;

    	while (1) {
            	printf("> ");
            	printf("%d\n", largoProcesos);
            	int largo = leer_de_teclado(256, command); // Lee los comandos de la consola
            	comando = de_cadena_a_vector(command);

                for (int i = 0; 1; i++) {
                    if (comando[i] == NULL) {
                        largoMatriz = i;
                        break;
                    }
                }

                if(command[largo - 1] == 38) {
                    int largoPalabra = strlen(comando[largoMatriz - 1]);
                    if(largoPalabra == 1){
                        comando[largoMatriz -1] = '\0';
                    } else {
                        comando[largoMatriz -1][largoPalabra - 1] = '\0';
                    }
                    esBg = 1;
                }

            	if (strcmp(command,"tareas") == 0){
                    for(int i = 0; i < largoProcesos; i++){
                        if(procesos[i] != 0){
                            printf("[%d] %d\n", i+1, procesos[i]);
                        }
                    }
                    continue;
                }

                if (strcmp(command,"largo") == 0){
                    printf("%d\n", largoProcesos);
                    continue;
                }

                if(strcmp(command, "detener") == 0){
                    int i = atoi(comando[1]);
                    kill(procesos[i-1], SIGSTOP);
                    procesos[i-1] = 0;
                }

                if (strcmp(command,"salir") == 0) break;
            	int rc = fork();
                assert(rc >= 0);
            	if (rc == 0){
                    execvp(comando[0], comando);
                }
            	else {
                    if(esBg == 1) {
                        procesos[largoProcesos] = rc;
                        largoProcesos++;
                        esBg = 0;
                        continue;
                    } else {
                        wait(NULL);
                    }
                }

    	}
    	return 0;
}
