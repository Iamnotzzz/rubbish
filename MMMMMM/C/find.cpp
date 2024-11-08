#include"head.h"
int find_combo_index(const char* name) {
    for (int i = 0; i < combo_count; i++) {
        if (strcmp(combos[i].name, name) == 0) {
            return i;
        }
    }
    return -1;
}

int find_food_index(const char* name) {
    for (int i = 0; i < food_count; i++) {
        if (strcmp(foods[i].name, name) == 0) {
            return i;
        }
    }
    return -1;
}