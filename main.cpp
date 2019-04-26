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
/*Thuc hien cac phep bien doi cho diem*/
void translateCompute(Point2D& point, float tr_x, float tr_y);
void scaleCompute(Point2D& point, float sx, float sy);
void rotateCompute(Point2D& point, float alpha);
void chooseCoorSystem();
void chooseObject2Draw();
//ham ve den tin hieu giao thong
void VeDenGiaoThong()
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
    setfillstyle(SOLID_FILL, RED);
    floodfill(redLight.x, redLight.y, WHITE);

    Point2D yellowLight (55, 36);
    realToMachine(yellowLight);
    bresenhamCircle(yellowLight, 3*5, WHITE);
    setfillstyle(SOLID_FILL, YELLOW);
    floodfill(yellowLight.x, yellowLight.y, WHITE);

    Point2D blueLight (55, 28);
    realToMachine(blueLight);
    bresenhamCircle(blueLight, 3*5, WHITE);
    setfillstyle(SOLID_FILL, BLUE);
    floodfill(blueLight.x, blueLight.y, WHITE);
}
//////////////////////////////////////GLOBAL VAR///////////////////////////////////////////////////
int width = 1280, height = 680;
const float midX = width/2;
const float midY = height/2;
//////////////////////////////////////MAIN FUNC////////////////////////////////////////////////////
int main(int argc, char* argv[]){
    initwindow(width, height, "KYTHUATDOHOA");
    chooseCoorSystem();
    /*Point2D boobs(20, 20);
    realToMachine(boobs);
    bresenhamCircle(boobs, 10*5, LIGHTCYAN);
    setfillstyle( XHATCH_FILL, YELLOW );
    floodfill( boobs.x, boobs.y, LIGHTCYAN );*/
    VeDenGiaoThong();
    chooseObject2Draw();
    getch();
    closegraph();
    return EXIT_SUCCESS;
}
//////////////////////////////////////END MAIN////////////////////////////////////////////////////
//////////////////////////////////////START BASIC FUNCTION////////////////////////////////////////
void chooseCoorSystem()
{
    Point2D origin(0, 0);               //goc toa do
    realToMachine(origin);              //chuyen sang toa do machine
    again:
    Print_at(0, 0, "---CHON HE TOA DO---");
    Print_at(5, 1, "1: 2D");
    Print_at(5, 2, "2: 3D");
    Print_at(0, 3, ">>>");
    short choice;
    std::cin >> choice;
    if(choice != 1 && choice !=2)
    {
        Clear_at(0, 0, 10, 10);
        goto again;
    }
    if(choice == 1)
        draw2DCoor(origin);
    else if (choice == 2)
        draw3DCoor();
}

void chooseObject2Draw()
{
    Clear_at(0, 0, 10, 10);
    Print_at(0, 0, "---CHON VAT THE DE VE 2D---");
    Print_at(5, 1, "1: TRAFFIC LIGHTS");
    Print_at(5, 2, "2: DRAGON BALLS");
    Print_at(0, 3, ">>>");
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
    /**float points[][2] = {
        {center.x + x, center.y + y},
        {center.x - x, center.y + y},
        {center.x + x, center.y - y},
        {center.x - x, center.y - y},
        {center.x + y, center.y + x},
        {center.x - y, center.y + x},
        {center.x + y, center.y - x},
        {center.x - y, center.y - x},
    };

    realToMachine(points[0][0], points[0][1]);realToMachine(points[1][0], points[1][1]);
    realToMachine(points[2][0], points[2][1]);realToMachine(points[3][0], points[3][1]);
    realToMachine(points[4][0], points[4][1]);realToMachine(points[5][0], points[5][1]);
    realToMachine(points[6][0], points[6][1]);realToMachine(points[7][0], points[7][1]);

    putpixel(points[0][0], points[0][1], color);
    putpixel(points[1][0], points[1][1], color);
    putpixel(points[2][0], points[2][1], color);
    putpixel(points[3][0], points[3][1], color);
    putpixel(points[4][0], points[4][1], color);
    putpixel(points[5][0], points[5][1], color);
    putpixel(points[6][0], points[6][1], color);
    putpixel(points[7][0], points[7][1], color);**/
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
    bresenhamLine(Point2D(midX, 0), Point2D(midX, midY), WHITE, false); outtextxy(midX, 0, "Y");                   //Y
    bresenhamLine(Point2D(0, height), Point2D(midX, midY), WHITE, false); outtextxy(8, height-24, "Z");            //Z
    bresenhamLine(Point2D(width, height), Point2D(midX, midY), WHITE, false); outtextxy(width-12, height-24, "X"); //X
}
//////////////////////////////////////END BASIC FUNCTION//////////////////////////////////////////
