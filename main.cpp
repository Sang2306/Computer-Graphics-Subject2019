#include <iostream>
#include <cmath>
#include <cstdio>
#include <graphics.h>
#include "consolelib.h"
#define PI 3.141592654
struct Point2D{
    float x, y, h;
    Point2D();
    Point2D(float x, float y);
};

Point2D::Point2D()
{
    x = y = h = -1;
}

Point2D::Point2D(float x, float y)
{
    this->x = x;
    this->y = y;
    this->h = 1;
}
/*ham ve duong thang va duong tron*/
void bresenhamLine(Point2D p1, Point2D p2, int color, bool solid=true);
void drawCircle(Point2D center, int x, int y, int color);
void bresenhamCircle(Point2D center, float radius, int color);
/*he toa do 2D va 3D*/
void draw2DCoor(const Point2D& mid);
void draw3DCoor();
/*chuyen toa do the gioi thuc ve toa do may tinh*/
void realToMachine(Point2D& point);
Point2D getPointOz(int unit);
/*Thuc hien cac phep bien doi cho diem*/
void translateCompute(Point2D& point, float tr_x, float tr_y);
void scaleCompute(Point2D& point, float sx, float sy);
void rotateCompute(Point2D& point, float alpha);
void initMenuWindow(); //Menu hien thi tuy chon va hien thi thong tin cua doi tuong
void chooseCoorSystem();
void chooseObject2Draw();
//ham ve den tin hieu giao thong
void drawTrafficLight();
//ham ve hinh hop
void veHinhHop(int, int, int);
//////////////////////////////////////GLOBAL VAR///////////////////////////////////////////////////
int width = 1080, height = 600;
const float midX = width/2;
const float midY = height/2;
//////////////////////////////////////MAIN FUNC////////////////////////////////////////////////////
int main(int argc, char* argv[]){
    initwindow(width, height, "KYTHUATDOHOA");
    initMenuWindow();
    getch();
    closegraph();
    return EXIT_SUCCESS;
}
//////////////////////////////////////END MAIN////////////////////////////////////////////////////
//////////////////////////////////////START BASIC FUNCTION////////////////////////////////////////
void initMenuWindow()
{
    int width, height;
    GetWindowSize(width, height);
    //Separate main menu from information pannel
    for(int y = 0; y < height; y++)
        Print_at(width/2, y, (char)124);
    Print_at(width/2, 0, "< THONG TIN >");
    chooseCoorSystem();
}

void chooseCoorSystem()
{
    again:
    Print_at(0, 0, "---CHON HE TOA DO---");
    Print_at(5, 1, "1: 2D");
    Print_at(5, 2, "2: 3D");
    Print_at(0, 3, ">>>");
    short choice;
    std::cin >> choice;
    if(choice != 1 && choice !=2)
    {
        Clear_at(0, 0, 20, 20);
        goto again;
    }
    if(choice == 1)
    {
        cleardevice();
        Point2D origin(0, 0);               //goc toa do
        realToMachine(origin);              //chuyen sang toa do thuc sang toa do may
        draw2DCoor(origin);
        chooseObject2Draw();                //Menu hien thi chon do vat 2d de ve
    }
    else if (choice == 2)
    {
        cleardevice();
        draw3DCoor();
        Point2D pz = getPointOz(50);
        putpixel(pz.x, pz.y, YELLOW);
        veHinhHop(55, 55, 55);
    }
}

void chooseObject2Draw()
{
    again:
    Clear_at(0, 0, 20, 20);
    Print_at(0, 0, "---CHON VAT THE DE VE 2D---");
    Print_at(5, 1, "1: TRAFFIC LIGHTS");
    Print_at(5, 2, "2: EMOJI");
    Print_at(5, 3, "3: ...");
    Print_at(0, 4, ">>>");
    short choice;
    std::cin >> choice;
    if(choice != 1 && choice !=2 && choice !=3)
    {
        Clear_at(0, 0, 20, 20);
        goto again;
    }
    switch(choice)
    {
        case 1: drawTrafficLight(); break;
        case 2: veHinhHop(5, 5, 5); break;
        case 3: {
            Clear_at(0, 0, 20, 20);
            return chooseCoorSystem();
        }
    }
}

void realToMachine(Point2D& point)
{
    /*
        Chuyen diem x,y thanh toa do may tinh
        5 : don vi
    */
    point.x = point.x*5 + midX;
    if(point.y < 0)
        point.y = point.y*5*-1 + midY;
    else
        point.y = midY - point.y*5;
}

Point2D getPointOz(int unit)
{
    /*
        ham tra ve toa do cua don vi tren truc oz
    */
    Point2D point;
    //chuyen doi toa do cho truc z
    point.x = midX - unit*5*cos(45); //x = toa do tam.x - don vi * 5 px * cos(45)
    point.y = midY + unit*5*sin(45); //y = toa do tam.y + don vi * 5 px + sin(45)
    return point;
}

void translateCompute(Point2D& point, float tr_x, float tr_y)
{
    float vector[3] = {point.x, point.y, point.h};
    float translate[3][3] = {
        {1, 0, 0},
        {0, 1, 0},
        {tr_x, tr_y, 1},
    };
    point.x = vector[0]*translate[0][0] + vector[1]*translate[1][0] + vector[2]*translate[2][0];
    point.y = vector[0]*translate[0][1] + vector[1]*translate[1][1] + vector[2]*translate[2][1];
    point.h = vector[0]*translate[0][2] + vector[1]*translate[1][2] + vector[2]*translate[2][2];
}

void scaleCompute(Point2D& point, float sx, float sy)
{
    float vector[3] = {point.x, point.y, point.h};
    float scale[3][3] = {
        {sx, 0, 0},
        {0, sy, 0},
        {0, 0, 1},
    };
    point.x = vector[0]*scale[0][0] + vector[1]*scale[1][0] + vector[2]*scale[2][0];
    point.y = vector[0]*scale[0][1] + vector[1]*scale[1][1] + vector[2]*scale[2][1];
    point.h = vector[0]*scale[0][2] + vector[1]*scale[1][2] + vector[2]*scale[2][2];
}

void rotateCompute(Point2D& point, float alpha)
{
    float vector[3] = {point.x, point.y, point.h};
    float rotate[3][3] = {
        {cos(alpha * PI/ 180), sin(alpha * PI/ 180), 0},
        {sin(alpha * PI/ 180)*-1, cos(alpha * PI/ 180), 0},
        {0, 0, 1},
    };
    point.x = vector[0]*rotate[0][0] + vector[1]*rotate[1][0] + vector[2]*rotate[2][0];
    point.y = vector[0]*rotate[0][1] + vector[1]*rotate[1][1] + vector[2]*rotate[2][1];
    point.h = vector[0]*rotate[0][2] + vector[1]*rotate[1][2] + vector[2]*rotate[2][2];
}

void bresenhamLine(Point2D p1, Point2D p2, int color, bool solid)
{
     float x, y, dx, dy, dx1, dy1, px, py, xe, ye, count=5;

     dx = p2.x - p1.x;      //do thay doi x
     dy = p2.y - p1.y;      //do thay doi y
     dx1 = abs(dx);
     dy1 = abs(dy);
     px = 2*dy1 - dx1;  //px dau tien neu m < 1
     py = 2*dx1 - dy1;  //py dau tien neu m >= 1

     if(dy1 <= dx1)     //tim y theo x vi chieu doc nho hon (m < 1)
     {
          if(dx >= 0)   //diem cuoi ben phai hoac cung vi tri diem dau -> ve tu trai sang phai
          {
               x = p1.x;
               y = p1.y;
               xe = p2.x;
          }
          else          //diem cuoi ben trai -> ve tu phai sang trai
          {
               x = p2.x;
               y = p2.y;
               xe = p1.x;
          }
          while(x < xe) //loop tu x dau -> x cuoi, chon y trong qua trinh do
          {
                if(!solid)
                {
                    if (count==5)
                        putpixel(x, y, color);
                }
                else
                    putpixel(x, y, color);

               x = x + 1;
               if(px < 0)
                    px = px + 2*dy1;
               else
               {
                    if((dx < 0 && dy < 0) || (dx > 0 && dy > 0))
                        y = y + 1;
                    else
                        y = y - 1;
                    px = px + 2*(dy1 - dx1);
               }
               count = count==1 ? 5 : count-1;
          }
     }
     else //tim x theo y vi chieu ngang nho hon (m >= 1)
     {
          if(dy >= 0)
          {
               x = p1.x;
               y = p1.y;
               ye = p2.y;
          }
          else
          {
               x = p2.x;
               y = p2.y;
               ye = p1.y;
          }
          while(y < ye)
          {
                if(!solid)
                {
                    if (count==5)
                        putpixel(x, y, color);
                }
                else
                    putpixel(x, y, color);

               y = y + 1;
               if(py <= 0)
                    py = py + 2*dx1;
               else
               {
                    if((dx < 0 && dy < 0) || (dx > 0 && dy > 0))
                        x = x + 1;
                    else
                        x = x - 1;
                    py = py + 2*(dx1 - dy1);
               }
               count = count==1 ? 5 : count-1;
          }
     }
}

void drawCircle(Point2D center, int x, int y, int color)
{
    putpixel(center.x + x, center.y + y, color);
    putpixel(center.x - x, center.y + y, color);
    putpixel(center.x + x, center.y - y, color);
    putpixel(center.x - x, center.y - y, color);
    putpixel(center.x + y, center.y + x, color);
    putpixel(center.x - y, center.y + x, color);
    putpixel(center.x + y, center.y - x, color);
    putpixel(center.x - y, center.y - x, color);
}

void bresenhamCircle(Point2D center, float r, int color)
{
    int x = 0, y = r;
    int p = 3 - 2 * r;
    drawCircle(center, x, y, color);
    while (y >= x)
    {
        x++;
        if (p > 0)
        {
            y--;
            p = p + 4 * (x - y) + 10;
        }
        else
            p = p + 4 * x + 6;
        drawCircle(center, x, y, color);
    }
}

void draw2DCoor(const Point2D& mid)
{
    bresenhamLine(Point2D(0, mid.y), Point2D(width, mid.y), WHITE, false); outtextxy(width-12, mid.y, "X");   //X
    bresenhamLine(Point2D(mid.x, 0), Point2D(mid.x, height), WHITE, false); outtextxy(mid.x, 0, "Y");         //Y
}

void draw3DCoor()
{

    bresenhamLine(Point2D(width, midY), Point2D(midX, midY), WHITE, false); outtextxy(width-12, midY, "X");        //X
    bresenhamLine(Point2D(midX, 0), Point2D(midX, midY), WHITE, false); outtextxy(midX, 0, "Y");                   //Y
    int total_unit = 65; //tong so don vi
    for(int unit = 0; unit <= total_unit; unit++)
    {
        Point2D temp = getPointOz(unit); //lay diem toa do tai moi cham
        putpixel(temp.x, temp.y, WHITE); //va hien thi len man hinh
    }
    Point2D temp = getPointOz(total_unit); //lay diem toa do tai moi cham
    outtextxy(temp.x, temp.y, "Z");            //Z
}
//////////////////////////////////////END BASIC FUNCTION//////////////////////////////////////////

//////////////////////////////////////==================//////////////////////////////////////////
void drawTrafficLight()
{
    Point2D topLeft (45, 50);
    Point2D bottomRight (65, 20);

    Point2D bottomLeft(topLeft.x, bottomRight.y); //(45, 20)
    Point2D topRight(bottomRight.x, topLeft.y); //(65, 50)

    realToMachine(topLeft);
    realToMachine(bottomRight);
    realToMachine(bottomLeft);
    realToMachine(topRight);

    bresenhamLine(topLeft, topRight, WHITE);
    bresenhamLine(bottomRight, topRight, WHITE);
    bresenhamLine(bottomLeft, bottomRight, WHITE);
    bresenhamLine(topLeft, bottomLeft, WHITE);

    Point2D topLeftUp (49, 54);
    realToMachine(topLeftUp);
    bresenhamLine(topLeftUp, topLeft, WHITE);

    Point2D bottomRightUp (69, 24);
    realToMachine(bottomRightUp);
    bresenhamLine(bottomRightUp, bottomRight, WHITE);

    Point2D topRightUp (bottomRightUp.x, topLeftUp.y);
    bresenhamLine(topRightUp, topRight, WHITE);

    bresenhamLine(topRightUp, topLeftUp, WHITE);
    bresenhamLine(topRightUp, bottomRightUp, WHITE);

    Point2D redLight (55, 44);
    realToMachine(redLight);
    bresenhamCircle(redLight, 3*5, WHITE);
    setfillstyle(SOLID_FILL, LIGHTRED);
    floodfill(redLight.x, redLight.y, WHITE);

    Point2D yellowLight (55, 36);
    realToMachine(yellowLight);
    bresenhamCircle(yellowLight, 3*5, WHITE);
    setfillstyle(SOLID_FILL, YELLOW);
    floodfill(yellowLight.x, yellowLight.y, WHITE);

    Point2D greenLight (55, 28);
    realToMachine(greenLight);
    bresenhamCircle(greenLight, 3*5, WHITE);
    setfillstyle(SOLID_FILL, GREEN);
    floodfill(greenLight.x, greenLight.y, WHITE);
}

void veHinhHop(int dai, int rong, int cao)
{
    Point2D O(0, 0);
    realToMachine(O);

    Point2D A(dai, 0);
    realToMachine(A);

    bresenhamLine(O, A, WHITE, false);

    Point2D F(dai, cao);
    realToMachine(F);

    bresenhamLine(F, A, WHITE, true);

    Point2D E(0, cao);
    realToMachine(E);

    bresenhamLine(O, E, WHITE, false);

    bresenhamLine(E, F, WHITE, true);

    Point2D C = getPointOz(rong);

    bresenhamLine(O, C, WHITE, false);

    Point2D B(midX + dai*5*cos(45), midY + rong*5*sin(45));

    bresenhamLine(B, A, WHITE);

    bresenhamLine(B, C, WHITE);

    Point2D D(midX - rong*5*cos(45), midY - cao*5*cos(80));

    bresenhamLine(D, E, WHITE);

    bresenhamLine(D, C, WHITE);

    Point2D G(midX + dai*5*cos(45), midY - rong*5*cos(80));

    bresenhamLine(G, F, WHITE, true);

    bresenhamLine(G, B, WHITE, true);

    bresenhamLine(G, D, WHITE, true);
}
