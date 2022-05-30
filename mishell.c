#include <assert.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include "leercadena.h"

int main(int argc, char* argv[]) {
    	char command[256];
    	char **comando;
        int largoMatriz;

    	while (1) {
            	printf("> ");
            	int largo = leer_de_teclado(256, command);
            	comando = de_cadena_a_vector(command);

                for (int i = 0; 1; i++) {
                    if (comando[i] == NULL) {
                        largoMatriz = i;
                        break;
                    }
                    printf("%s\n", comando[i]);
                }
   
                printf("Largo de caracteres: %d\n", largo);
                // printf("Largo del vector%d\n", (int)(sizeof(comando) / sizeof(comando[0])));
                printf("Largo de matriz: %d\n", largoMatriz);
                printf("Última palabra de matriz: %s\n", comando[largoMatriz-1]);
                // printf("String: %s\n", comando[0]);
                // printf("%ld\n", sizeof(&command));
            	if (strcmp(command,"salir") == 0) break;
            	int rc = fork();
                assert(rc >= 0);
            	if (rc == 0){
                    if(command[largo - 1] == 38){
                        int largoPalabra = strlen(comando[largoMatriz - 1]);
                        if(largoPalabra == 1){
                            comando[largoMatriz -1] = '\0';
                        } else {
                            comando[largoMatriz -1][largoPalabra - 1] = '\0';
                        }
                        
                        // printf("%s\n", comando[largoMatriz - 1]);
                        // printf("El ampersand");
                        // command[largo] = '\x0';
                        // printf("%d\n", command[largo - 1]);
                        // comando = de_cadena_a_vector(command);
                        // puts(command);
                        execvp(comando[0], comando);
                    } else {
                        execvp(comando[0], comando);
                    }
                }
            	else {
                    if(command[largo - 1] == 38) {
                        // comando[strlen(comando) - 1] = NULL;
                        // execvp(comando[0], comando);
                    }
                    else {
                        wait(NULL);
                    }
                }
    	}
    	return 0;
}
