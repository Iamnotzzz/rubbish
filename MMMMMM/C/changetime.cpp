#include"head.h"

int time_to_seconds(int hour, int minute, int second) {
    return hour * 3600 + minute * 60 + second;
}

void seconds_to_time(int seconds, int* hour, int* minute, int* second) {
    *hour = seconds / 3600;
    *minute = (seconds % 3600) / 60;
    *second = seconds % 60;
}

