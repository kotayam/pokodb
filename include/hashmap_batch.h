#ifndef BATCH_H
#define BATCH_H

#include "errors.h"
#include "hashmap.h"
#include <pthread.h>
#include <stdlib.h>
#include <string.h>

#define BATCH "batch"

short run_batch(int num_operations, int num_threads, hashmap *map);

#endif
