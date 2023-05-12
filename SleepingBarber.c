#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include <linux/kernel.h>
#include <sys/syscall.h>
#define MAX_CUSTOMERS 25
asmlinkage long sys_hello1(void)
{

    void *customer(void *num);
    void *barber(void *);
    sem_t waitingRoom;

    sem_t barberChair;

    sem_t barberPillow;

    sem_t seatBelt;

    int allDone = 0;
    int main(int argc, char *argv[])
    {
        pthread_t btid;
        pthread_t tid[MAX_CUSTOMERS];
        int i, x, numCustomers, numChairs;
        int Number[MAX_CUSTOMERS];
        printf("Maximum number of customers can only be 25. Enter number of customers and chairs.\n");
        scanf("%d", &x);
        numCustomers = x;
        scanf("%d", &x);
        numChairs = x;
        if (numCustomers > MAX_CUSTOMERS)
        {
            printk("The maximum number of Customers is %d.\n", MAX_CUSTOMERS);
            return 0;
        }
        printk("A solution to the sleeping barber problem using semaphores.\n");
        for (i = 0; i < MAX_CUSTOMERS; i++)
        {
            Number[i] = i;
        }

        sem_init(&waitingRoom, 0, numChairs);
        sem_init(&barberChair, 0, 1);
        sem_init(&barberPillow, 0, 0);
        sem_init(&seatBelt, 0, 0);

        pthread_create(&btid, NULL, barber, NULL);

        for (i = 0; i < numCustomers; i++)
        {
            pthread_create(&tid[i], NULL, customer, (void *)&Number[i]);
        }

        for (i = 0; i < numCustomers; i++)
        {
            pthread_join(tid[i], NULL);
        }

        allDone = 1;
        sem_post(&barberPillow);
        pthread_join(btid, NULL);
        return 0;
    }
    void *customer(void *number)
    {
        int num = *(int *)number;
        printk("Customer %d leaving for barber shop.\n", num);
        sleep(5);
        printk("Customer %d arrived at barber shop.\n", num);

        sem_wait(&waitingRoom);
        printk("Customer %d entering waiting room.\n", num);
        sem_wait(&barberChair);
        sem_post(&waitingRoom);
        printk("Customer %d waking the barber.\n", num);
        sem_post(&barberPillow);
        sem_wait(&seatBelt);
        sem_post(&barberChair);
        printk("Customer %d leaving barber shop.\n", num);
    }
    void *barber(void *junk)
    {

        while (!allDone)
        {
            printk("The barber is sleeping\n");
            sem_wait(&barberPillow);
            if (!allDone)
            {
                printk("The barber is cutting hair\n");
                sleep(3);
                printk("The barber has finished cutting hair.\n");
                sem_post(&seatBelt);
            }

            else
            {
                printk("The barber is going home for the day.\n");
            }
        }
    }
    return 0;
}
