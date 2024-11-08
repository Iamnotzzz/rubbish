#define _CRT_SECURE_NO_WARNINGS
#include"head.h"
void parse_menu_file(const char* filename) {//ÎÄ¼þ¶ÁÐ´º¯Êý
    FILE* file = fopen(filename, "r");
    if (!file) {
        perror("Failed to open menu file");
        exit(EXIT_FAILURE);
    }

    fscanf(file, "%d %d", &food_count, &combo_count);

    for (int i = 0; i < food_count; i++) {
        fscanf(file, "%s", foods[i].name);
    }

    for (int i = 0; i < food_count; i++) {
        fscanf(file, "%d", &foods[i].prep_time);
        foods[i].current_capacity = 0;
        foods[i].is_producing = 0;
    }

    for (int i = 0; i < food_count; i++) {
        fscanf(file, "%d", &foods[i].max_capacity);
    }

    fscanf(file, "%d %d", &W1, &W2);

    for (int i = 0; i < combo_count; i++) {
        fscanf(file, "%s", combos[i].name);
        combos[i].food_count = 0;
        char food_name[MAX_NAME_LEN];
        while (fscanf(file, "%s", food_name) == 1) {
            strcpy(combos[i].foods[combos[i].food_count++], food_name);
            if (getc(file) == '\n') break;
        }
    }

    fclose(file);
}