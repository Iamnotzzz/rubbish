#include"head.h"

void outputfile(const char* filename) {
    FILE* file = fopen(filename, "w");
    char result[MAX_ORDERS][15];
    if (!file) {
        perror("Failed to open output file");
        exit(EXIT_FAILURE);
    }

    for (int i = 0; i < order_count; i++) {
        //fprintf(file, "i+1 ");
        if (booltime[i] == 0) {
            fprintf(file, "Fail\n");
        }
        else {
            int hour, minute, second;
            seconds_to_time(finallytime[i], &hour, &minute, &second);
            fprintf(file, "%d: %02d:%02d:%02d\n", i+1, hour, minute, second);
        }
    }

    fclose(file);
}