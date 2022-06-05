#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include "leercadena.h"

int main(int argc, char* argv[]) {
    	char command[256];
    	char **comando;
        int largoMatriz; // Tamaño del vector comando
        int procesos[30]; // Array que guarda PIDS en background
        int largoProcesos = 0; //Tamaño del array procesos
        int esBg = 0; // Saber si un proceso esta en background o no

    	while (1) {
            	printf("> ");
            	int largo = leer_de_teclado(256, command); // Lee los comandos de la consola
            	comando = de_cadena_a_vector(command);

                // Se calcula el tamaño del vector comando
                for (int i = 0; 1; i++) {
                    if (comando[i] == NULL) {
                        largoMatriz = i;
                        break;
                    }
                }

                // Se verifica que al final del comando ingresado en la terminal haya un ampersand
                if(command[largo - 1] == 38) {
                    int largoPalabra = strlen(comando[largoMatriz - 1]);
                    if(largoPalabra == 1){
                        comando[largoMatriz -1] = '\0';
                    } else {
                        comando[largoMatriz -1][largoPalabra - 1] = '\0';
                    }
                    esBg = 1;
                }

                //Enlista los procesos en bg
            	if (strcmp(command,"tareas") == 0){
                    for(int i = 0; i < largoProcesos; i++){
                        if(procesos[i] != 0){
                            printf("[%d] %d\n", i+1, procesos[i]);
                        }
                    }
                    continue;
                }

                //Detiene un proceso en especifico que recibe como argumento su indicador en la lista de procesos en bg
                if(strcmp(command, "detener") == 0){
                    
                    int i = atoi(comando[1]);
                    if(i > largoProcesos){
                        printf("El proceso %d no existe", i );
                    }
                    else{
                    kill(procesos[i-1], SIGSTOP);
                    procesos[i-1] = 0;
                    }
                }

                //Se sale del interprete de comandos
                if (strcmp(command,"salir") == 0) break;
            	int rc = fork();
                assert(rc >= 0);
            	if (rc == 0){
                    //Proceso hijo
                    execvp(comando[0], comando);
                }
            	else {
                    //Proceso padre
                    if(esBg == 1) {
                        procesos[largoProcesos] = rc; //Se agrega el PID de un proceso en bg al array procesos
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
