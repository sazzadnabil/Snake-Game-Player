#include  "config.h"
#include  "lcddrv.h"
#include  <string.h>

/*********ASCII ****/
TCOLOR disp_color;
TCOLOR back_color;

int dir[9][2]={0,-1,0,1,-1,0,1,0,-1,1,-1,-1,1,1,1,-1,0,0};
int  snake_length, snake_dir = 3,food_x,food_y,gameover;
int keyvalue[16]={
                  -1, 0,-1,-1,
                   2,-1, 3,-1,
                  -1, 1,-1,-1,
                  -1,-1,-1,-1};
////////////////
struct Snake
{ 
   int x,y;
}snake[1000];

void delayMs(int n)
{
   int i;
   for(i = 0;i < 1000;i++)
      for(;n>0;n--);   
}

/*Akram MD Asim*/////Akram MD Asim/////ASCII color1//color2////
void GUI_SetColor(TCOLOR color1, TCOLOR color2)
 {
    GUI_CopyColor(&disp_color,color1);
    GUI_CopyColor(&back_color,color2);
 }
 
 //////////0<x<127,0<y<63
 void  Big_Point(uint8 x,uint8 y,TCOLOR  color)
 {
    int i;
    for (i=0;i < 9;i++)
    {
       GUI_Point(x+dir[i][0],y+dir[i][1],color);
    }
 }
 
 /////////////////////Akram MD Asim//////////////
 void snake_init(int x,int y)
 {
 int i ;
 snake_length = 0;
 for (i = 0;i < 10;i++)
     {
            Big_Point(x,y,LCD_DISP_COLOR);
            snake[snake_length].x = x;
            snake[snake_length].y = y;
            snake_length++;
	x-=3;
      }
}

///////////////////
void creat_food()
{
     int i,flag = 1;
      Big_Point(food_x,food_y,LCD_BACK_COLOR);
     do
     {
	//stand((unsigned)time(NULL));
       food_x = rand() % 127;
       food_y = rand() % 63;
       for( i= 0;i  < snake_length-1;i++)
       {
             if(snake[i].x+2 <= food_x || food_x <= snake[i].x-2 || snake[i].y+2 <= food_y || food_y <= snake[i].y-2)
		flag = 0;
            }
       }while(flag);
       Big_Point(food_x,food_y,LCD_DISP_COLOR);
}

/////////////////////////
void snake_move(int direction)
{
    int i;
    struct Snake last;
last = snake[snake_length-1];
    /////////////////////////////////////////////
for(i = snake_length - 1;i>0;i--)
{
    snake[i]=snake[i-1];
}
////////// diraction/////////////////
  snake[0].x += dir[direction][0] * 3;
  snake[0].y += dir[direction][1] * 3;
///////////////
  if(snake[0].x>= 127)snake[0].x = 1;
  else if(snake[0].x <= 0)snake[0].x = 126;
  else if(snake[0].y <= 0)snake[0].y = 62;
  else if(snake[0].y >= 63)snake[0].y = 1;
///////////////////
  for(i = 1; i< snake_length -1; i++)
  {
    if(snake[i].x + 2>= snake[0].x && snake[0].x>= snake[i].x-2 && snake[i].y+2 >= snake[0].y && snake [0].y >= snake[i].y-2)
    {
        gameover =1;
        return;
      }
   }
   ////////////
  if(snake[0].x +2 >= food_x && food_x >= snake[0].x-2 &&snake[0].y+2 >= food_y && food_y >= snake[0].y-2)
  {
    snake[snake_length]=last;
    creat_food();
    snake_length++;
    }
     else
    {
          Big_Point(last.x,last.y,LCD_BACK_COLOR);
}
//////////
Big_Point(snake[0].x,snake[0].y,LCD_DISP_COLOR);
}


//////////////
int GetDir()
{
   int temp,temp1,temp2;
   IO0DIR |=0x0000F;
   IO0SET |=0x0000F;
   temp1= IO0PIN& 0X000F0000;
   /////////////
switch(temp1)
{
   case 0X0010000:temp1 = 0;break;
   case 0X0020000:temp1 = 1;break;
   case 0X0040000:temp1 = 2;break;
   case 0X0080000:temp1 = 3;break;
   default:temp1 = 4;
}
   if(temp1 != 4)
   {
IO0DIR &= 0xFFFFFFF0;
IO0DIR |= 0x000F0000;
IO0CLR |= 0x0000000F;
IO0SET |= 0x000F0000;
temp2 = IO0PIN & 0x0000000F;
      ///////////////////////////
switch(temp2)
{
case 0x001:temp = temp1*4 + 0;break;
case 0x002:temp = temp1*4 + 1;break;
case 0x004:temp = temp1*4 + 2;break;
case 0x008:temp = temp1*4 + 3;break;
default:temp = 0;
}
IO0CLR |= 0xF0000;
IO0DIR &= 0x0FFFF;
}
return temp;
}

int main (void)
{
   
   int dir = 3; 
   GUI_Initialize();
   GUI_SetColor(LCD_DISP_COLOR,LCD_BACK_COLOR);
   snake_init(64,32);
   creat_food();
 while (!gameover)
 {
 dir = keyvalue[GetDir()];
 if(dir == -1)
dir = snake_dir;
 if(snake_dir + dir != 1 && snake_dir + dir !=5)
 {
 snake_dir = dir;
 }
 snake_move(snake_dir);
 delayMs(100000);
   }
}
