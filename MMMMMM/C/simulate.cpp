#include"head.h"

void simulate()
{
    order_count = 0;
    int start_time = time_to_seconds(7, 0, 0);
    int end_time = time_to_seconds(22, 0, 0);
    int i = 0;
    int lastI = 0;
    int x1 = 0, x2 = 0, y1 = 0, y2 = 0;
    ExMessage msg;
    char maybe[51] = { '0' };
    int num = 0;

    int hour, minute, second;
    current_time = start_time;
    setbkcolor(WHITE);

    // 初始化订单结果

    BeginBatchDraw();

    do
    {
        setup();
        if (peekmessage(&msg) == true)
        {

            switch (msg.message)
            {
            case WM_LBUTTONDOWN:
                for (int a = 0; a < 5; a++)
                {
                    for (int b = 0; b <= 3; b++)
                    {
                        if (msg.x >= 410 + (b * 195) && msg.y >= 55 + (80 * a) && msg.x <= 600 + (b * 195) && msg.y <= 125 + (80 * a))
                        {
                            strcpy(maybe, foods[num].name);
                            x1 = 420 + (b * 195);
                            x2 = 590 + (b * 195);
                            y1 = 60 + (80 * a);
                            y2 = 120 + (80 * a);
                            //rectangle(420 + (b * 195), 60 + (80 * a), 590 + (b * 195), 120 + (80 * a));
                        }
                        num++;
                    }
                }
                num = 0;
                for (int a = 0; a <= 1; a++)
                {
                    for (int b = 0; b <= 3; b++)
                    {

                        if (msg.x >= 410 + (b * 195) && msg.y >= 510 + (80 * a) && msg.x <= 600 + (b * 195) && msg.y <= 580 + (80 * a))
                        {
                            strcpy(maybe, combos[num].name);
                            x1 = 420 + (b * 195);
                            x2 = 590 + (b * 195);
                            y1 = 515 + (80 * a);
                            y2 = 575 + (80 * a);
                            //rectangle(420 + (b * 195), 515 + (80 * a), 590 + (b * 195), 575 + (80 * a));
                            //fillcircle(600 + (b * 195), 125 + (80 * a), 20);
                        }
                        num++;
                    }
                }
                num = 0;
                //rectangle(690, 690, 890, 760);
                if (msg.x >= 690 && msg.y >= 690 && msg.x <= 890 && msg.y <= 760)
                {
                    seconds_to_time(current_time, &orders[order_count].hour, &orders[order_count].minute, &orders[order_count].second);
                    strcpy(orders[order_count].type, maybe);
                    //printf("%d:%d,%d,%d,%s", order_count,orders[order_count].hour, orders[order_count].minute, orders[order_count].second,orders[order_count].type);
                    strcpy(finallytype[order_count], maybe);
                    //printf("%d,%s", order_count, finallytype[order_count]);
                    maybe[0] = '0';
                    if (system_closed == 1)
                    {
                        booltime[order_count] = 0;
                    }
                    else
                    {
                        booltime[order_count] = 1;
                    }
                    order_count++;
                }
            }
            flushmessage();
        }
        if (maybe[0] != '0')
        {
            setlinecolor(LIGHTRED);
            rectangle(x1, y1, x2, y2);
        }
        printtime();
        
        if (timer(speed, 0) == 1)//定时器
        {
            //printf("第二次：%d:endtime:%d\n", 0, results[0].end_time);
            
            for (int n = 0; n < order_count; n++) {
                results[n].order_id = n;
                results[n].start_time = time_to_seconds(orders[n].hour, orders[n].minute, orders[n].second);
                results[n].end_time = -1;
                results[n].fulfilled = 0;
                //printf("%d,%d,%d\n", results[n].order_id, order_count, results[n].start_time);
            }
            if (queue_head == queue_tail && current_time > end_time) {
                break;
            }

            // 在工作时间内处理订单
            if (current_time >= start_time && current_time <= end_time)
            {
                for (i = lastI; i < order_count; i++)
                {
                    if (results[i].start_time == current_time)
                    {
                        //printf("true");
                        lastI = i;
                        if (!system_closed)
                        {
                            enqueue_order(i);
                            pending_orders++;
                        }
                        break;
                    }
                }
            }

            // 处理生产和订单
            process_production();
            process_orders();

            // 控制系统开关
            if (pending_orders > W1 && !system_closed)
            {
                int hour, minute, second;
                seconds_to_time(current_time, &hour, &minute, &second);
                system_closed = 1;//为1时关闭，为0时开启
            }

            if (pending_orders < W2 && system_closed && current_time <= end_time)
            {
                int hour, minute, second;
                seconds_to_time(current_time, &hour, &minute, &second);
                system_closed = 0;
            }
            current_time++;
            //printf("第一次：%d:endtime:%d\n", 0, results[0].end_time);
        }
        FlushBatchDraw();
    } while (current_time <= 86400);

    EndBatchDraw();
}
            
    

void process_orders() {
    int new_queue_tail = queue_head;

    for (int i = queue_head; i < queue_tail; i++) {
        int order_id = order_queue[i];
        int combo_index = find_combo_index(orders[order_id].type);
        int food_indices[5];
        int food_count = 0;
        int can_fulfill = 1;

        // 初始化订单状态，如果未初始化过
        if (!order_states[order_id].initialized) {
            memset(order_states[order_id].food_needed, 0, sizeof(order_states[order_id].food_needed));
            order_states[order_id].initialized = 1;
        }

        if (combo_index != -1) {
            //printf("成功,套餐\n");
            for (int j = 0; j < combos[combo_index].food_count; j++) {
                
                int food_index = find_food_index(combos[combo_index].foods[j]);
                if (food_index != -1 && foods[food_index].current_capacity > 0 && order_states[order_id].food_needed[food_index] == 0) {
                    food_indices[food_count] = food_index;
                    order_states[order_id].food_needed[food_index] = 1;
                    food_count++;
                    foods[food_index].current_capacity--;
                }
                else if (food_index != -1 && order_states[order_id].food_needed[food_index] == 1) {
                    continue; // 跳过已分配的食物
                }
                else {
                    can_fulfill = 0;
                    break;
                }
            }
        }
        else {
            int food_index = find_food_index(orders[order_id].type);
            //printf("%d,food\n", food_index);
            if (food_index != -1 && foods[food_index].current_capacity > 0 && order_states[order_id].food_needed[food_index] == 0) {
                food_indices[food_count] = food_index;
                order_states[order_id].food_needed[food_index] = 1;
                food_count++;
                foods[food_index].current_capacity--;
            }
            else if (food_index != -1 && order_states[order_id].food_needed[food_index] == 1) {
                continue; // 跳过已分配的食物
            }
            else {
                can_fulfill = 0;
            }
        }

        if (can_fulfill) {
            
            results[order_id].end_time = current_time;
            results[order_id].fulfilled = 1;
            results[order_id].food_count = food_count;
            memcpy(results[order_id].food_indices, food_indices, food_count * sizeof(int));
            pending_orders--;
            finallytime[order_id] = results[order_id].end_time;
            //printf("%d:endtime:%d\n", order_id,results[order_id].end_time);
        }
        else {
            results[order_id].fulfilled = 0;
            order_queue[new_queue_tail++] = order_queue[i];
            //printf("endtime:fail");
        }
    }

    queue_tail = new_queue_tail;

    check_and_start_production();
}

void process_production() {
    for (int i = 0; i < food_count; i++) {
        if (foods[i].is_producing && current_time - foods[i].start_time == foods[i].prep_time) {
            foods[i].current_capacity++;
            foods[i].is_producing = 0;
        }
    }

    for (int i = 0; i < food_count; i++) {
        if (foods[i].current_capacity < foods[i].max_capacity && !foods[i].is_producing) {
            foods[i].is_producing = 1;
            foods[i].start_time = current_time;
        }
    }
}

void check_and_start_production() {
    for (int i = 0; i < food_count; i++) {
        if (foods[i].current_capacity < foods[i].max_capacity && !foods[i].is_producing) {
            foods[i].is_producing = 1;
            foods[i].start_time = current_time;
        }
    }
}

void enqueue_order(int order_id) {
    order_queue[queue_tail++] = order_id;
}

int dequeue_order() {
    if (queue_head == queue_tail) return -1;
    return order_queue[queue_head++];
}
void setup()
{
    setbkcolor(WHITE);
    //setlinecolor(RED);
    //setfillcolor(RED);
    //fillrectangle(0, 0, 30, 30);
    RECT r = { 0, 0, 639, 479 };
    char s1[50];
    char s2[] = "确定点单";
    char s3[] = "暂无数据";
    char s4[] = "当前订单状态：制作中";
    char s5[] = "当前订单状态：已完成";
    char s6[] = "单点";
    char s7[] = "套餐";

    char zzz[] = "当前系统状态: 正常^w^";
    char ryr[] = "当前系统状态: 爆单qwq";
    char food1[] = "BigMac";
    char order[50];
    char cap[11];
    int i=0;
    int hour, minute, second;
    cleardevice();

    setlinecolor(RED);
    setfillcolor(RED);
    fillrectangle(0, 0, 400, 150);

    settextcolor(RED);
    settextstyle(40, 0, _T("Consolas"));
    seconds_to_time(current_time, &hour, &minute, &second);
    sprintf(s1, "当前时间：%02d:%02d:%02d", hour, minute, second);
    outtextxy(10, 30, s1);
    settextstyle(30, 0, _T("Consolas"));

    if (system_closed == 1)
        outtextxy(10, 110, ryr);
    else if (system_closed == 0)
        outtextxy(10, 110, zzz);
    settextstyle(20, 0, _T("Consolas"));
    setlinecolor(RED);
    settextcolor(BLACK);
    setlinestyle(PS_SOLID , 2);

    for (int a = 0; a < 5; a++)
    {
        for (int b = 0; b <= 3; b++)
        {
            setfillcolor(RED);
            rectangle(410+(b*195), 55+(80*a), 600+(b*195), 125+(80*a));
            if (i < food_count)
            {
                outtextxy(415+ (b * 195), 65+ (80 * a), foods[i].name);
                sprintf(cap, "%d", foods[i].current_capacity);
                outtextxy(415 + (b * 195), 90 + (80 * a), cap);
            }
            else
                outtextxy(415 + (b * 195), 65 + (80 * a), s3);
            i++;

        }
    }
    i = 0;
    setlinecolor(RGB(240, 155, 89));
    for (int a = 0; a <= 1; a++)
    {
        for (int b = 0; b <= 3; b++)
        {
            rectangle(410 + (b * 195), 510 + (80 * a), 600 + (b * 195), 580 + (80 * a));
            if (i < combo_count)
            {
                outtextxy(415 + (b * 195), 520 + (80 * a), combos[i].name);
            }
            else
                outtextxy(415 + (b * 195), 520 + (80 * a), s3);
            i++;

        }
    }

    setlinecolor(YELLOW);
    setlinestyle(PS_DASH | PS_ENDCAP_FLAT, 3);
    settextstyle(50, 0, _T("Consolas"));
    rectangle(690, 690, 890, 760);
    rectangle(685, 685, 895, 765);
    setlinecolor(LIGHTRED);
    rectangle(680, 680, 900, 770);
    outtextxy(700, 700, s2);

    settextcolor(RED);
    settextstyle(45, 0, _T("Consolas"));
    outtextxy(755, 5, s6);

    settextcolor(RGB(240, 155, 89));
    settextstyle(45, 0, _T("Consolas"));
    outtextxy(755, 450, s7);

    setlinecolor(YELLOW);
    setlinestyle(PS_DASHDOT | PS_ENDCAP_ROUND, 6);
    rectangle(10, 160, 400, 780);
    rectangle(15, 165, 395, 775);
    rectangle(20, 170, 390, 770);
    setlinecolor(RGB(240, 155, 89));
    rectangle(9, 159, 401, 781);

}
