#ifndef SRC__SHRMEM_H_
#define SRC__SHRMEM_H_

#include <fcntl.h>
//const int map_size = 4096;
const char *BackingFile = "lab_4.back";
const char *SemaphoreName = "lab4.semaphore";
unsigned AccessPerms = S_IWUSR | S_IRUSR | S_IRGRP | S_IROTH;

#endif//SRC__SHRMEM_H_