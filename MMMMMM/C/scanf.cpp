#define _CRT_SECURE_NO_WARNINGS

#include"head.h"
void parse_orders() {
    scanf("%d", &order_count);

    for (int i = 0; i < order_count; i++) {
        scanf("%d:%d:%d %s", &orders[i].hour, &orders[i].minute, &orders[i].second, orders[i].type);
    }
}