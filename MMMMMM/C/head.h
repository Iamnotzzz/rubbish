#define _CRT_SECURE_NO_WARNINGS
#define MAX_FOOD 101
#define MAX_COMBO 101
#define MAX_ORDERS 54001
#define MAX_NAME_LEN 51
#define MAX_QUEUE 54001

#include <graphics.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include<time.h>

typedef struct {
    char name[MAX_NAME_LEN];//ʳ������
    int prep_time;//����ʱ��
    int max_capacity;//������
    int current_capacity;//��ǰ����
    int is_producing;//����Ƿ���������
    int start_time;//��ʼ������ʱ��
} Food;

typedef struct {
    char name[MAX_NAME_LEN];//�ײ�����
    int food_count;//����ʳ������
    char foods[5][MAX_NAME_LEN];//����ʳ������
} Combo;

typedef struct {
    int hour;
    int minute;
    int second;
    char type[MAX_NAME_LEN];
} Order;

typedef struct {
    int order_id;
    int start_time;
    int end_time;
    int food_count;
    int food_indices[5];
    int fulfilled;
} OrderResult;

typedef struct {
    int food_needed[MAX_FOOD]; // ��¼ÿ��ʳ�����������
    int initialized;           // ����Ƿ��ѳ�ʼ��
} OrderState;


//ȫ�ֱ�������


extern int W1, W2;
extern Food foods[MAX_FOOD];
extern Combo combos[MAX_COMBO];
extern Order orders[MAX_ORDERS];
extern OrderResult results[MAX_ORDERS];
extern OrderState order_states[MAX_ORDERS]; // ȫ�����飬�洢ÿ������������״̬
extern int food_count , combo_count , order_count ;
extern int system_closed , current_time ;
extern int pending_orders;
extern int order_queue[MAX_QUEUE];
extern int queue_head , queue_tail;
extern int speed;
extern int finallytime[54001];
extern int booltime[54001];
extern char finallytype[54001][51];



void parse_menu_file(const char* filename);
void parse_orders();
int time_to_seconds(int hour, int minute, int second);
void seconds_to_time(int seconds, int* hour, int* minute, int* second);
void simulate();
void process_orders();
void process_production();
void enqueue_order(int order_id);
void check_and_start_production();
int find_combo_index(const char* name);
int find_food_index(const char* name);
void seconds_to_time(int seconds, int* hour, int* minute, int* second);
int dequeue_order();
void output_results();
int timer(int fast, int id);
void load();
void setup();
void outputfile(const char* filename);
void printtime();
