#include<iostream>
#include<graphics.h>
#include<math.h>

int Color = RED;

using namespace std;

void Bhm_line(int x1, int y1, int x2, int y2, int color)
{
     int x, y, dx, dy, dx1, dy1, px, py, xe, ye, i;

     dx = x2 - x1; //chieu ngang
     dy = y2 - y1; //chieu doc
     dx1 = fabs(dx); //tinh tri tuyet doi
     dy1 = fabs(dy);
     px = 2*dy1 - dx1; //cong thuc
     py = 2*dx1 - dy1;

     if(dy1 <= dx1) //tim y theo x vi chieu doc nho hon
     {
          if(dx >= 0) //diem cuoi ben phai or cung hang -> ve tu trai sang phai
          {
               x = x1;
               y = y1;
               xe = x2;
          }
          else //diem cuoi ben trai -> ve tu phai sang trai
          {
               x = x2;
               y = y2;
               xe = x1;
          }

          putpixel(x, y, color);

          for(i = 0; x < xe; i++) //loop tu x dau -> x cuoi, chon y trong qua trinh do
          {
               x = x + 1;

               if(px < 0)
               {
                    px = px + 2*dy1;
               }
               else
               {
                    if((dx < 0 && dy < 0) || (dx > 0 && dy > 0))
                    {
                        y = y+1;
                    }
                    else
                    {
                        y = y - 1;
                    }

                    px = px + 2*(dy1 - dx1);
               }

               putpixel(x, y, color);
          }
     }
     else //tim x theo y vi chieu ngang nho hon
     {
          if(dy >= 0)
          {
               x = x1;
               y = y1;
               ye = y2;
          }
          else
          {
               x = x2;
               y = y2;
               ye = y1;
          }

          putpixel(x, y, color);

          for(i = 0;y < ye; i++)
          {
               y = y + 1;

               if(py <= 0)
               {
                    py = py + 2*dx1;
               }
               else
               {
                    if((dx < 0 && dy < 0) || (dx > 0 && dy > 0))
                    {
                        x = x + 1;
                    }
                    else
                    {
                        x = x - 1;
                    }

                    py = py + 2*(dx1 - dy1);
               }

               putpixel(x, y, color);
          }
     }
}

int main()
{
     int ghdriver = DETECT, ghmode, x1, x2, y1, y2; //khai bao

     initgraph(&ghdriver, &ghmode, "..\\bgi"); //thu tuc thoi dung quan tam :V

     cout << "Enter the coordinates (x1,y1): "; //toa do diem dau
     cin >> x1 >> y1;

     cout << "Enter the coordinates (x2,y2): "; //toa do diem cuoi
     cin >> x2 >> y2;

     Bhm_line(x1, y1, x2, y2, Color);
     getch();

     return 0;
}
