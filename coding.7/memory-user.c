#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <memory-in-megabytes>\n", argv[0]);
        return 1;
    }

    long megabytes = strtol(argv[1], NULL, 10);
    long bytes = megabytes * 1024 * 1024;

    char *memory = (char *)malloc(bytes);

    if (memory == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        return 1;
    }

    // Initialized the memory to prevent it from being optimized away
    memset(memory, 0, bytes);

    printf("Allocated %ld megabytes of memory\n", megabytes);

    // Touch each entry in the array
    while (1) {
        for (long i = 0; i < bytes; i += 4096) {
            memory[i] = 0;
        }
        usleep(10000); // Sleep for 10ms to reduce CPU usage
    }

    // This code is unreachable because the program runs indefinitely
    free(memory);
    return 0;
}
