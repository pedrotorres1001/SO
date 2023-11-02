#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <pthread.h>
#include <errno.h>



void* child(void* arg) {
    
    int *n1 = (int *)malloc(sizeof(int)); // estamos a dar malloc da variável que foi passada. tem de ser passada a int pq vem um endereço

    if (arg != NULL){ // aqui simplesmente verificamos se recebemos algo no argumento de entrada
        n1 = ((int *)arg); // se sim, então convertemos em int e atualizamos o valor para depois a main utilizar.
    }

    int n2 = 0;

    while (n2 < 10 || n2 > 20) { // verificação se o input pedido está nos valores correspondentes.
        printf("Enter a value between 10 and 20: ");
        scanf("%d", &n2);
    }

    while(*n1 != n2) { // não esquecer que aqui ainda estamos a considerar o *n1 e não n1 pois guardámos em *n1 o valor inteiro do endereço.
        usleep(10000);
        *n1 = *n1 + 1; // aqui incrementamos o valor do endereço (em int)
        printf("[Thread] Value: %d\n", *n1);
    }
    return NULL;
}

int main() {
    pthread_t t1;
    int n1 = 0;
    while(n1 < 1 || n1 > 9) {
        printf("Enter a value between 1 and 9: ");
        scanf("%d", &n1);
    }

    if (pthread_create(&t1, NULL, &child, (void *)&n1) != 0) { // única coisa aqui a rever é a passagem do argumento para as threads.
        perror("Can not create thread"); // mesmo assim verificamos se a thread foi criada com sucesso. (opcional)
    }

    if (pthread_join(t1, NULL) != 0) {
        perror("Can not join thread");
    }

    while (n1 != 1) { // aqui já não precisamos de verificar o endereço, pois já estamos a trabalhar com o valor inteiro.
        usleep(10000);
        n1--;
        printf("[main] Value: %d\n", n1);
    }
}