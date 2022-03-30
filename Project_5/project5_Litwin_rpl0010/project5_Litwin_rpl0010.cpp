// Project 5
// author Ryan Litwin
// version 11/19/20
// compile with project5_Litwin_rpl0010.cpp -lpthread
// run with ./a.out

// Please change the following comment part into your name
// #0#BEGIN# DO NOT MODIFY THIS COMMENT LINE!
// Ryan
// Litwin
// #0#END# DO NOT MODIFY THIS COMMENT LINE!

#include <stdio.h>
#include <pthread.h>
#include <iostream>
using namespace std;

// Defines how many units of data will be generated in total(10 integers)
#define MAX 10

// Adds the mutex
pthread_mutex_t the_mutex;

// Tells the thread whether the job is done and resource, and tells if the buffer is available or not.
pthread_cond_t condc, condp;

// Uses an integer variable as the buffer
int buffer = 0;

void *producer(void *ptr) {
    int i;
    for(i=1; i<=MAX; i++) {
        // Locks the mutex
        pthread_mutex_lock(&the_mutex);

        // If buffer is not empty, that means buffer holds some data
        while(buffer !=0) pthread_cond_wait(&condp, &the_mutex);

        // The producer generates one integer, one unit of data is assigned to the buffer
        buffer = i*7;

        // prints out message to tell what item the producer generates.
        cout << "producer produce item " << buffer << endl;

        // Buffer is full now, stop producer thread and notify the consumer.
        pthread_cond_signal(&condc);

        // Unlocks the mutex because the other thread is done
        pthread_mutex_unlock(&the_mutex);

    }

    // exits the thread and return with 0
    pthread_exit(0);
}

void *consumer(void *ptr) {
    int i;
    int get_data;

    for (i=1; i<=MAX; i++) {
        // Lock mutex before start
        // #1#BEGIN# DO NOT MODIFY THIS COMMENT LINE!
        pthread_mutex_lock(&the_mutex);
        // #1#END# DO NOT MODIFY THIS COMMENT LINE!

        // When buffer is empty, nothing to consume, have to wait
        // #2#BEGIN# DO NOT MODIFY THIS COMMENT LINE!
        while(buffer ==0) pthread_cond_wait(&condc, &the_mutex);
        // #2#END# DO NOT MODIFY THIS COMMENT LINE!

        // Assign the buffer data to the variable get_data
        // #3#BEGIN# DO NOT MODIFY THIS COMMENT LINE!
        get_data = buffer;
        // #3#END# DO NOT MODIFY THIS COMMENT LINE!

        // Prints out the content of what you get in get_data
        cout << "consumer consume item " << get_data << endl;

        // Clear the buffer by assigning value 0 to buffer
        // #4#BEGIN# DO NOT MODIFY THIS COMMENT LINE!
        buffer = 0;
        // #4#END# DO NOT MODIFY THIS COMMENT LINE!

        // Notify the condition variable of producer that it is ready to go
        // #5#BEGIN# DO NOT MODIFY THIS COMMENT LINE!
        pthread_cond_signal(&condp);
        // #5#END# DO NOT MODIFY THIS COMMENT LINE!

        // Unlocks the mutex
        // #6#BEGIN# DO NOT MODIFY THIS COMMENT LINE!
        pthread_mutex_unlock(&the_mutex);
        // #6#END# DO NOT MODIFY THIS COMMENT LINE!
    }
    // exits the thread and returns with 0
    // #7#BEGIN# DO NOT MODIFY THIS COMMENT LINE!
    pthread_exit(0);
    // #7#END# DO NOT MODIFY THIS COMMENT LINE!
}

int main(int argc, char *argv[]) {
    // change your the following id into your banner id
    // #8#BEGIN# DO NOT MODIFY THIS COMMENT LINE!
    int banner_id = 903960304;
    // #8#END# DO NOT MODIFY THIS COMMENT LINE!
    cout << "Banner id: " << banner_id << endl;

    pthread_t pro, con;
    pthread_mutex_init(&the_mutex,0);       // create the mutex used by thread
    pthread_cond_init(&condc,0);            // initialize the condition variable for consumer
    pthread_cond_init(&condp,0);            // initialize the condition variable for producer
    pthread_create(&con, 0, consumer, 0);   // create thread map to function consumer
    pthread_create(&pro, 0, producer, 0);   // create thread map to function producer
    pthread_join(pro,0);                    // put the producer thread into the system
    pthread_join(con,0);                    // put the consumer thread into the system

    // clean up, destroy the mutex and two threads
    pthread_cond_destroy(&condc);
    pthread_cond_destroy(&condp);
    pthread_mutex_destroy(&the_mutex);

    return 0;
}