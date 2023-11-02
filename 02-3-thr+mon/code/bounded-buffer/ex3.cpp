#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <pthread.h>
#include <errno.h>

pthread_mutex_t mutex; // mutex para proteger a variável n1
int n1 = 0;

pthread_cond_t cond_zero, cond_um; // condições para as threads esperarem que seja a sua vez de imprimir

static pthread_cond_t cond[2] = { PTHREAD_COND_INITIALIZER, PTHREAD_COND_INITIALIZER};

void* child(void* arg) {

    int index = *(int *)arg; // index é o valor do argumento que foi passado para a thread (convertido para int)

    pthread_mutex_lock(&mutex);

    while (n1 > 2) { // o valor final será então 1
        while (n1 % 2 != index) // como index só pode ser 0 ou 1, este ciclo estará sempre a verificar se o n1 é par ou ímpar
            pthread_cond_wait(&cond[index], &mutex);

        printf("[TID: %d; thread] %d\n", gettid(), n1); // um simples print com o tid da thread que realizou o incremento e o valor de n1
        n1--;
        pthread_cond_broadcast(&cond[n1 % 2]); // broadcast para acordar a outra thread que está à espera de imprimir o seu valor
    }       
    pthread_mutex_unlock(&mutex);
    return NULL;
}

int main() {
    pthread_t t1, t2;
    pthread_mutex_init(&mutex, NULL);
    
    while (n1 < 10 || n1 > 20) {
        printf("Enter a value between 10 and 20: ");
        scanf("%d", &n1);
    }

    int zero = 0;
    int one = 1;

    if (pthread_create(&t1, NULL, &child, (void *)&zero) != 0) {
        perror("Can not create thread");
    }

    if (pthread_create(&t2, NULL, &child, (void *)&one) != 0) {
        perror("Can not create thread2");
    }
    
    if (pthread_join(t1, NULL) != 0) {
        perror("Can not join thread");
    }
    
    if (pthread_join(t2, NULL) != 0) {
        perror("Can not join thread2");
    }

    printf("[TID: %d; main] Valor final: %d\n", gettid(), n1);
}