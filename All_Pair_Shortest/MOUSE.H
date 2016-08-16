#ifndef __MOUSE_H
#define __MOUSE_H
#endif
#include<stdio.h>
#include<conio.h>
#include<stdlib.h>
#include<graphics.h>
#include<dos.h>
#include<string.h>

union REGS i;
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
void HideMouse()
{
	i.x.ax=0x02;
	int86(0x33,&i,&i);
}
enum boolean { FALSE, TRUE};
typedef enum boolean boolfun;

boolfun IsClick()
{
	i.x.ax=0x03;
	int86(0x33,&i,&i);

	if(i.x.bx && 1)
	{
		delay(400);
	       //	getch();
		return TRUE;
	}
	else
		return FALSE;
}


