#include <assert.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include "leercadena.h"

int main(int argc, char* argv[]) {
    	char command[256];
    	char **comando;
    	while (1) {
                int i;
            	printf("> ");
            	leer_de_teclado(256, command);
            	if (strcmp(command,"salir") == 0) break;
            	comando = de_cadena_a_vector(command);

                i = 0;
                while(comando[i]){
                    i++;
                }

            	int rc = fork();
            	assert(rc >= 0);
            	if (rc == 0){
                	execvp(comando[0], comando);
                } else {
                    if(strcmp(comando[i-1], "&") != 0){
                        wait(NULL);
                    }
                }

                if(strcmp(comando[i-1], "&") == 0){
                    comando[i-1] = NULL;
                    i--;
                }
                    
                    	
    	}
    	return 0;
}

