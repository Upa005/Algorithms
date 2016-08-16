#ifndef __MOUSE_H
#define __MYMOUSE_H
#endif
#include<math.h>
#include<stdio.h>
#include<conio.h>
#include<stdlib.h>
#include<graphics.h>
#include<dos.h>
#include<string.h>
#define MAX_EDGE 100
#define MAX_VERT 10
#define MAX_NUM 30000

union REGS i,o;
void InitMouse()    //change the mode and give the status of mouse
{
	i.x.ax=0x00;
	int86(0x33,&i,&i);

	if(i.x.ax==0)
	exit(0);
}
void ShowMouse()      //display mouse on screen
{
    i.x.ax=0x01;
	int86(0x33,&i,&i);
}
void HideMouse()  //hide mouse
{
	i.x.ax=0x02;
	int86(0x33,&i,&i);
}
enum boolean { FALSE, TRUE};
typedef enum boolean boolfun;

boolfun IsClick()
{
	i.x.ax=0x03;
	int86(0x33,&i,&o);

	if(o.x.bx)
	{
		delay(400);
	       //	getch();
	       return TRUE;
	}
	else
	      return FALSE;
}
