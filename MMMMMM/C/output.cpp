#include"head.h"
void output_results() {
    for (int i = 0; i < order_count; i++) {
        //printf("final:%d,%d,%d\n", i, order_count, results[i].end_time);
        if (booltime[i] == 0) {
            printf("Fail\n");
        }
        else {
            int hour, minute, second;
            seconds_to_time(finallytime[i], &hour, &minute, &second);
            printf("%02d:%02d:%02d\n", hour, minute, second);
        }
    }
}