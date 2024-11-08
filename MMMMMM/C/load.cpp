#include"head.h"
void load()
{
    IMAGE img;
    char s1[] = "麦当劳点餐系统ver5.0：desine by 赵振展 于航";
    char s2[] = "请选择时间流速";
    char s3[] = "1x";
    char s4[] = "100x";
    char s5[] = "200x";
    char s6[] = "500x";
    char s7[] = "1000x";
    char s8[] = "请重新选择";
    ExMessage msg;
    initgraph(1200, 800,EX_SHOWCONSOLE);
    setbkcolor(WHITE);
    cleardevice();
    loadimage(&img, "./res/logo.png", 1200, 800);
    putimage(0, 0, &img);//后期需要掩码图
    Sleep(700);

    setbkcolor(RED);
    cleardevice();
    settextcolor(WHITE);
    settextstyle(50, 0, _T("Consolas"));
    outtextxy(120, 400, s1);
    Sleep(1500);
    setbkcolor(RED);
    cleardevice();
    settextcolor(WHITE);
    settextstyle(60, 0, _T("Consolas"));
    outtextxy(400, 150, s2);
    setbkcolor(WHITE);
    settextcolor(BLACK);
    settextstyle(55, 0, _T("Consolas"));
    outtextxy(150, 350, s3);
    outtextxy(310, 350, s4);
    outtextxy(510, 350, s5);
    outtextxy(710, 350, s6);
    outtextxy(910, 350, s7);

    setlinecolor(YELLOW);
    setlinestyle(PS_SOLID | PS_JOIN_BEVEL, 60);
    ellipse(350, 500, 600, 1100);
    ellipse(600, 500, 850, 1100);
    setlinecolor(RED);
    fillrectangle(500, 790, 700, 800);
    fillrectangle(0, 799, 1200, 800);

    //Sleep(1500);
    while (1) 
    {

        flushmessage();
        getmessage(&msg);
        switch (msg.message)
        {
            case WM_LBUTTONDOWN:
            if (msg.x >= 150 && msg.x <= 220 && msg.y >= 350 && msg.y <= 405)
            {
                speed = 1000;
                return ;
            }
            else if (msg.x >= 310 && msg.x <= 420 && msg.y >= 350 && msg.y <= 405)
            {
                speed = 10;
                return;
            }
            else if (msg.x >= 510 && msg.x <= 620 && msg.y >= 350 && msg.y <= 405)
            {
                speed = 5;
                return;
            }
            else if (msg.x >= 710 && msg.x <= 820 && msg.y >= 350 && msg.y <= 405)
            {
                speed = 2;
                return;
            }
            else if (msg.x >= 910 && msg.x <= 1100 && msg.y >= 350 && msg.y <= 405)
            {
                speed = 1;
                return;
            }
            
        }
       
        
    }

    
}