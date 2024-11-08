#define _CRT_SECURE_NO_WARNINGS

#include"head.h"

int W1, W2;
Food foods[MAX_FOOD];
Combo combos[MAX_COMBO];
Order orders[MAX_ORDERS];
OrderResult results[MAX_ORDERS];
OrderState order_states[MAX_ORDERS]; // 全局数组，存储每个订单的需求状态
int food_count = 0, combo_count = 0, order_count = 0;
int system_closed = 0, current_time = 0;
int pending_orders = 0;
int order_queue[MAX_QUEUE];
int queue_head = 0, queue_tail = 0;
int speed = 0;
int finallytime[54001] = {0};
int booltime[54001] = { -1 };
char finallytype[54001][51] = { '0' };

int main() {//主函数
    load();
    parse_menu_file("./res/dict.dic");
    //parse_orders();
    simulate();
    output_results();
    outputfile("./res/output.txt");
    return 0;
}

