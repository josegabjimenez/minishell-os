#include <assert.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include "leercadena.h"

int main(int argc, char* argv[]) {
    	char command[256];
    	char **comando;
        int largoMatriz;
        int procesos[] = {};
        int largoProcesos = 1;

    	while (1) {
            	printf("> ");
            	int largo = leer_de_teclado(256, command);
            	comando = de_cadena_a_vector(command);

                for (int i = 0; 1; i++) {
                    if (comando[i] == NULL) {
                        largoMatriz = i;
                        break;
                    }
                    // printf("%s\n", comando[i]);
                }

                // printf("Largo de caracteres: %d\n", largo);
                // printf("Largo de matriz: %d\n", largoMatriz);
                // printf("Última palabra de matriz: %s\n", comando[largoMatriz-1]);

                if(strcmp(comando[largoMatriz -1], "&") == 0) {
                    procesos[largoProcesos] = 20;
                    largoProcesos++;
                }

            	if (strcmp(command,"tareas") == 0){
                    for(int i = 0; i < largoProcesos; i++){
                        printf("%d\n", procesos[i]);
                    }
                }

                if (strcmp(command,"largo") == 0){
                    printf("%d\n", largoProcesos);
                }

                if (strcmp(command,"salir") == 0) break;
            	int rc = fork();
                assert(rc >= 0);
            	if (rc == 0){
                    if(command[largo - 1] == 38){
                        procesos[largoProcesos] = 10;
                        int largoPalabra = strlen(comando[largoMatriz - 1]);
                        if(largoPalabra == 1){
                            comando[largoMatriz -1] = '\0';
                        } else {
                            
                            comando[largoMatriz -1][largoPalabra - 1] = '\0';
                        }
                        
                        // printf("%d\n", getpid()); 
                        execvp(comando[0], comando);
                    } else {
                        execvp(comando[0], comando);
                    }
                }
            	else {
                    if(command[largo - 1] != 38) {
                        wait(NULL);
                    }
                }

    	}
    	return 0;
}
