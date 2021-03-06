/*  
 *  Sistemas Operativos
 *  Grado en Ingeniería Informática
 * 
 *  2013 © Copyleft - All Wrongs Reserved
 *
 *  Ernesto Serrano <erseco@correo.ugr.es>
 *
 *	Implementa un programa que lance cinco procesos hijo. Cada uno de ellos se 
 *	identificará en la salida estándar, mostrando un mensaje del tipo Soy el 
 *	hijo PID. El proceso padre simplemente tendrá que esperar la finalización 
 *	de todos sus hijos y cada vez que detecte la finalización de uno de sus 
 *	hijos escribirá en la salida estándar un mensaje del tipo:
 *	  Acaba de finalizar mi hijo con <PID>
 *	  Sólo me quedan <NUM_HIJOS> hijos vivos
 *	 
 *	Implementa una modificacion sobre el anterior programa en la que el proceso 
 *	padre espera primero a los hijos creados en orden impar (1o,3o,5o) y despues 
 *	a los hijos pares (2o y 4o).
 */
#include <sys/types.h>
#include <unistd.h>		
#include <stdio.h>
#include <errno.h>
#include <stdlib.h>
#include <sys/wait.h>

int main(int argc, char *argv[]) {
	
	const int NUM_HIJOS = 5;
	pid_t pid[NUM_HIJOS];

	switch (pid[0] =fork()){

		case 0: //Hijo
			printf("Soy el hijo %d\n", getpid());
			break;
		default: //Padre
			switch (pid[1] =fork()){

				case 0: //Hijo
					printf("Soy el hijo %d\n", getpid());
					break;
				default: //Padre
					switch (pid[2] =fork()){

						case 0: //Hijo
							printf("Soy el hijo %d\n", getpid());
							break;
						default: //Padre
							switch (pid[3] =fork()){

								case 0: //Hijo
									printf("Soy el hijo %d\n", getpid());
									break;
								default: //Padre
									switch (pid[4] =fork()){

										case 0: //Hijo
											printf("Soy el hijo %d\n", getpid());
											break;
									} 
									break;
							} 
							break;

					}
					break; 
			} 
			break;

	}

	//Esperamos a que se cierren primero los impares
	for (int i = 0;i<NUM_HIJOS;i = i + 2) {
		if (waitpid(pid[i],0,0) > 0) {                  
	    	printf("Acaba de finalizar mi hijo con PID:%d\n",pid[i]);
	    	printf("Solo me quedan %d hijos vivos\n",NUM_HIJOS - i);
    	}
	}
	//Esperamos a que se cierren despues los pares
	for (int i = 1;i<NUM_HIJOS;i = i + 2) {
		if (waitpid(pid[i],0,0) > 0) {                  
	    	printf("Acaba de finalizar mi hijo con PID:%d\n",pid[i]);
	    	printf("Solo me quedan %d hijos vivos\n",NUM_HIJOS - i);
    	}
	}
		
	exit(0);

}