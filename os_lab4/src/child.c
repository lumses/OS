#include <semaphore.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/mman.h>
#include <unistd.h>

#include "shrmem.h"


int main() {
    double a;
    char c;
    double res;
    int k = 1;
    int y = 0;
    int map_fd = shm_open(BackingFile, O_RDWR, AccessPerms);
    if (map_fd == -1) {
        perror("SHM_OPEN");
	    exit(EXIT_FAILURE);
    }
    char* memptr = mmap(NULL, getpagesize(), PROT_READ | PROT_WRITE, MAP_SHARED, map_fd, 0);
    if (memptr == MAP_FAILED) {
        perror("MMAP");
	    exit(EXIT_FAILURE);
    }
    sem_t *semptr = sem_open(SemaphoreName, O_CREAT, AccessPerms, 2);
    if (semptr == SEM_FAILED) {
        perror("SEM_OPEN");
	    exit(EXIT_FAILURE);
    }
    char *empty_string = (char *)malloc(sizeof(char) * getpagesize());
    memset(empty_string, '\0', getpagesize());
    while(scanf("%lf%c", &a, &c) != EOF) {
        if (y == 0) {
            res = a;
            y = 1;
        } else {
            if (a!= 0) {
                res/=a;
                } else {
                    k = -1;
                }
            }
            if(c == '\n') {
                while (true) {
                    if ((sem_wait(semptr)) == 0) {
                        if (strcmp(memptr, empty_string) != 0) {
                            sem_post(semptr);
                            continue;
                        }
                        if (k!=-1) {
                            sprintf(memptr, "%lf\n", res);
                        } else {
                            sprintf(memptr,"%c\n",'z');
                        }
                        sem_post(semptr);
	                    break;
                        }
                    }
                    y = 0;
                    k = 1;
                }
   } 
   free(empty_string);
   close(map_fd);
   usleep(00150000);
   memptr[0] = EOF;
   sem_close(semptr);
   munmap(memptr, getpagesize());
   return EXIT_SUCCESS;
}