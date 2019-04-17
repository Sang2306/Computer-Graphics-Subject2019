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
void bresenham(Point p1, Point p2, int color, bool solid=true);
void draw2DCoor();
void draw3DCoor();
void realToMachine(int& x, int& y);
void chooseCoorSystem();
void chooseObject2Draw();
/////////////////////////////////
int width = 1200, height = 600;
int midX = (int)width/2;
int midY = (int)height/2;
//////////////////////////////////////MAIN FUNC////////////////////////////////////////////////////
int main(int argc, char* argv[]){
    initwindow(width, height, "KYTHUATDOHOA");
    chooseCoorSystem();
    chooseObject2Draw();
    getch();
    closegraph();
    return EXIT_SUCCESS;
}
//////////////////////////////////////END MAIN////////////////////////////////////////////////////
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

void bresenham(Point p1, Point p2, int color, bool solid)
{
     int x, y, dx, dy, dx1, dy1, px, py, xe, ye, count=5;

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
               count = count==0 ? 5 : count-1;
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
               count = count==0 ? 5 : count-1;
          }
     }
}

void draw2DCoor()
{
    bresenham(Point(0, midY), Point(width, midY), WHITE, false);//X
    bresenham(Point(midX, 0), Point(midX, height), WHITE, false);//Y
}

void draw3DCoor()
{
    bresenham(Point(midX, 0), Point(midX, midY), WHITE, false);     //Y
    bresenham(Point(0, height), Point(midX, midY), WHITE, false);   //Z
    bresenham(Point(width, height), Point(midX, midY), WHITE, false);//X
}
