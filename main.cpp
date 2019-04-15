#include <iostream>
#include <cmath>
#include <graphics.h>
#include "consolelib.h"
struct Point{
    int x;
    int y;
    Point();
    Point(int x, int y);
};
Point::Point()
{
    x = y = -1;
}
Point::Point(int x, int y)
{
    this->x = x;
    this->y = y;
}
void bresenham(Point p1, Point p2, bool solid = true);
void draw2DCoor();
void draw3DCoor();
void realToMachine(int& x, int& y);
void chooseCoorSystem();
void chooseObject2Draw();
/////////////////////////////////
int width = 1200, height = 600;
int midX = (int)width/2;
int midY = (int)height/2;
int main(int argc, char* argv[]){
    initwindow(width, height, "KYTHUATDOHOA");
    chooseCoorSystem();
    chooseObject2Draw();
    getch();
    closegraph();
    return EXIT_SUCCESS;
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
        Clear_at(0, 0, 10, 10);
        goto again;
    }
    if(choice == 1)
        draw2DCoor();
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

void realToMachine(int& x, int& y)
{
    /*
        Chuyen diem x,y thanh toa do may tinh
        5 : don vi
    */
    x = x*5 + midX;
    if(y < 0)
        y = y*5*-1 + midY;
    else
        y = midY - y*5;
}

void bresenham(Point p1, Point p2, bool solid)
{
    /*
        solid: neu dung thi ve lien net, nguoc lai ve ----
        thuat toan tren wikipedia
    */
   int x0 = p1.x, y0 = p1.y, x1 = p2.x, y1 = p2.y;
   int dx = abs(x1-x0);
   int dy = abs(y1-y0);
   int sx, sy;
   if(x0 < x1) sx = 1; else sx = -1;
   if(y0 < y1) sy = 1; else sy = -1;
   int err = dx - dy;
   int e2, count = 4;
   while(true)
   {
       if(!solid)
       {

           if(count == 4)
           {
               putpixel(x0, y0, WHITE);
           }
           count--;
           if (count == 0){
                count = 4;
           }
       }else
            putpixel(x0, y0, WHITE);

       if(x0 == x1 && y0 == y1) break;
       e2 = 2*err;
       if(e2 > -dy)
       {
           err = err - dy;
           x0 = x0 + sx;
       }
       if(e2 < dx)
       {
           err = err + dx;
           y0 = y0 + sy;
       }
   }
}

void draw2DCoor()
{
    bresenham(Point(0, midY), Point(width, midY), false);
    bresenham(Point(midX, 0), Point(midX, height), false);
}

void draw3DCoor()
{
    bresenham(Point(midX, 0), Point(midX, midY), false);
    ////////////////////////////////////////////////////
    bresenham(Point(0, height), Point(midX, midY), false);
    bresenham(Point(width, height), Point(midX, midY), false);
}
