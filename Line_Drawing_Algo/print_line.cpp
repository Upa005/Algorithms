#include<iostream.h>
#include<conio.h> //getch()
#include<graphics.h>
#include<math.h> //abs 
#include<dos.h> // mouse functions
#include<process.h> //exit(0) in init_mouse()

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

boolfun IsClick()  //check mouse click
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

// <<---------------simple dda algorithm-------------------------------------------------->>
 void dda(int x1,int y1,int x2,int y2,int color,int a[4], int t_select)
{  //x1,y1 are the coordinates of first point
   //x2,y2 are the coordinates of second point
   //color <int> color of pixel
   //t_select thickness of line
   //a[4] array of 1 and 0. If value is 1, print the pixel else skip.

	float dx=abs(x2-x1);
	float dy=abs(y2-y1);
	setcolor(WHITE);
  
	float e;
	if(dx > dy)
		{ e = 1/((dx));}   //e is epsilon here where e = 1/(max(dx or dy))
	else
	     {e = 1/((dy));}

	  float xinc,yinc;
	  xinc = e * dx;
	  yinc = e * dy;
	  float newx,newy;

	  int flag=1;
	if(y2>y1)
	    flag=0;
	newx = x1 + xinc+0.5;
	if(flag==0)
	  newy = y1+ yinc+0.5;
	else
	  newy = y1-yinc-0.5;


	putpixel(x1,y1,color); //Printing first pixel on screen

	float m =-(x2-x1)/(y2-y1); // point prependicular to line (x1,y1) and (x2,y2)
	float under = sqrt(1+m*m);
	int t_x,t_y;
     
	 int j=0;
	 
	    while(x2>newx)
       {
	    if(j==4)
	      j=0;
	     if(a[j]==1)
	     {
		 putpixel(newx,newy,color);
	     if(t_select >= 1) //  if thickness is greater than 1, then produce thick lines
	       { for(int k= t_select;k>=0;k--)
		  {
		   if(m>0)
		{
		  t_x= newx- k/under;
	       t_y= newy - m*(k/under);

	       putpixel(t_x,t_y,color); //pixels below the line
	       
	       t_x= newx + k/under;
	       t_y= newy + m*(k/under);
	       
	       putpixel(t_x,t_y,color); //pixel above the line
	     }
	       else
		{ t_x= newx + k/under;
		  t_y= newy + m*(k/under);
		
	       putpixel(t_x,t_y,color);
	         
	       t_x= newx - k/under;
	       t_y= newy - m*(k/under);
	       
	       putpixel(t_x,t_y,color);
	     }


		}
	   }
		
     }


		j++;

	 newx +=xinc;
	 if(flag==0)
		newy +=yinc;
	 else
	     newy -=yinc;

       }
	 putpixel(x2,y2,color)   ;

}

 //<<--------------   DDA ENDS ------------------------------------------->>
 
 //<<----------summetric DDA---------------------------------------------->>
 void symDDA(int x1,int y1,int x2,int y2,int color,int a[4],int t_select)
	 {
  
     float e,dx,dy,LLE;
	float m =-(x2-x1)/(y2-y1);
   
	float under = sqrt(1+m*m);
	int t_x,t_y;

	 dx=x2-x1;
	 if(dx<0)
	 dx=-(dx);

	 dy=y2-y1;
	 if(dy<0)
	 dy=-(dy);

     int var=1;
	 if(dx>dy)
	 {
		while(var<dx)
		{
			var=var*2;
		}
	 }

	 else
	{
		while(var<dy)
		{
			var=var*2;
		}
	}
	 LLE=var;
	 e=1.000/float(LLE);
	 float xi,yi;
	 xi=e*dx;
	 yi=e*dy;

	 float x=x1+0.5;
	 float y=y1+0.5;
	 int j=0;
	if(x1<=x2 && y1<=y2)   //m >0
	  {
	  for(int i=1;i<=LLE;i++)
			{
			x=x+xi;
			y=y+yi;
			 if(j==4)
		       j=0;
		if(a[j]==1)
				putpixel(x,y,color);
			if(t_select >= 1)
	       { for(int k= t_select;k>=0;k--)
		  {
		  t_x= x- k/under;
	       t_y= y - m*(k/under);
	       putpixel(t_x,t_y,color);

	       t_x= x + k/under;
	       t_y= y + m*(k/under);
	       putpixel(t_x,t_y,color);
	       }

		}
	}
    }
    else if(x1<x2 && y1>y2) //slope <0
    {
	for(int i=1;i<=LLE;i++)
    {
	x=x+xi;
	y=y-yi;
	if(j==4)
	   j=0;
	if(a[j]==1)
		{
		putpixel(x,y,color);
			if(t_select >= 1)
	       { for(int k= t_select;k>=0;k--)
		   {
		    t_x= x- k/under;
		 t_y= y - m*(k/under);
		 putpixel(t_x,t_y,color);

		 t_x= x + k/under;
		 t_y= y + m*(k/under);
		 putpixel(t_x,t_y,color);
	       }

		  }
		}

	j++;
    }
    }
    else if(x1>x2 && y1<y2) //slope <0
    {
	for(int i=1;i<=LLE;i++)
    {
	x=x-xi;
	y=y+yi;
	if(j==4)
	     j=0;
		if(a[j]==1)
		{
		putpixel(x,y,color);
			if(t_select >= 1)
	       { for(int k= t_select;k>=0;k--)
		   {
		    t_x= x- k/under;
		 t_y= y - m*(k/under);
		 putpixel(t_x,t_y,color);

		 t_x= x + k/under;
		 t_y= y + m*(k/under);
		 putpixel(t_x,t_y,color);
	       }

		  }
		}
	j++;
    }

    }
    else   //slope >0
    {
	for(int i=1;i<=LLE;i++)
    {
	x=x-xi;
	y=y-yi;
	if(j==4)
	     j=0;
	if(a[j]==1)
		{
		  putpixel(x,y,color);
			if(t_select >= 1)
	       { for(int k= t_select;k>=0;k--)
		  {

		  t_x= x- k/under;
	       t_y= y - m*(k/under);
	       putpixel(t_x,t_y,color);

	       t_x= x + k/under;
	       t_y= y + m*(k/under);
	       putpixel(t_x,t_y,color);
	       }

			}
		}
	j++;
    }
    }


	 }
 //<<------ -------SYMM DDA ENDS--------------------------------------------->>
 
 //<<----------------BRESEHNMAN ALGO----------------------------------------->>

 void lineBres(int x1, int y1, int x2, int y2,int color,int a[4], int t_select)//,int p_select);//, int t_select)
{  int dx,dy,p0,pg,ps;
	setcolor(WHITE);

	float m =-(x2-x1)/(y2-y1);
	int t_x,t_y;
	float under = sqrt(1+m*m);
     dx = abs(x2 - x1);
	dy = abs(y2 - y1);
	if(dx>dy)
     {
	p0 = 2 * dy - dx;
     ps  = 2 * dy;
     pg = 2 * (dy - dx);

     putpixel(x1, y1, color);
     int j =0;
     int flag =1;
     if(y2<y1)  // y1--;
       flag =0;
     while (x1 < x2)
     {  
	x1++;
	if (p0< 0)
	p0 = p0 + ps;
	else
	{ if(flag==1)
	   y1++;
	   else
	   y1--;
	p0 = p0 + pg;
	}
     if(j==4)
	   j=0;
	if(a[j]==1)
	{
	 putpixel(x1, y1, color);
	 	if(t_select >= 1)
	       { for(int k= t_select;k>=0;k--)
		  {   
		   if(m>0)
		  {
		  t_x= x1- k/under;
	       t_y= y1 - m*(k/under);
	       putpixel(t_x,t_y,color);

	       t_x= x1 + k/under;
	       t_y= y1 + m*(k/under);
	       putpixel(t_x,t_y,color);
	       }
	       else
		{ t_x= x1 + k/under;
		t_y= y1 + m*(k/under);

	      // delay(25);
	       putpixel(t_x,t_y,color);
	       t_x= x1 - k/under;
	       t_y= y1 - m*(k/under);
	       putpixel(t_x,t_y,color);
	       } //else loop ends

			} //for loop ends
	 
          } 
     }
	j++;
   
} }
  else
  {
	p0 = 2 * dx - dy;
     ps  = 2 * dx;
     pg = 2 * (dx - dy);


     putpixel(x1, y1, color);
     int j=0;
     int flag =1;
     if(x1>x2)    //x1--
      flag =0;
     while (y1 < y2)
     {
	y1++;
	if (p0< 0)
	p0 = p0 + ps;
	else
	{ if(flag==1)
	    x1++;
	  else
	    x1--;
	p0 = p0 + pg;
	}
	if(j==4)
	   j=0;
	if(a[j]==1)
	 {
	 putpixel(x1, y1, color);
	 if(t_select >= 1)
	       { for(int k= t_select;k>=0;k--)
		  {
		   if(m>0)
		  {
		  t_x= x1- k/under;
	       t_y= y1 - m*(k/under);
	       putpixel(t_x,t_y,color);

	       t_x= x1 + k/under;
	       t_y= y1 + m*(k/under);
	       putpixel(t_x,t_y,color);
	       }
	       else
		{ t_x= x1 + k/under;
		  t_y= y1 + m*(k/under);

	      // delay(25);
	       putpixel(t_x,t_y,color);
	       t_x= x1 - k/under;
	       t_y= y1 - m*(k/under);
	       putpixel(t_x,t_y,color);
	       } //else end

			} //for loop end


     } //if t_select >1
   }
	j++;
    
    }
  }
}
 
 //<<----------------------BRESHEMAN ALGO ENDS------------------------------->>
int main()
{   clrscr();
    int gd=DETECT,gm;
    initgraph(&gd,&gm,"c://TC/bgi")  ;
     
   //------------------------BUTTONS FOR ALGO SELECTION--------------   
	LOOP:  //label
	
	cleardevice();
     setbkcolor(LIGHTGREEN);
	setcolor(BLUE);

	//------------------------BUTTONS FOR ALGO SELECTION--------------
	int algobutton[4][5];  //for 4 algorithm storing left,right,top,bottom coordinates ,color of buttons
     setbkcolor(LIGHTGREEN);
	setcolor(BLUE);



	outtextxy(200,50,"Select algorithm for lines");
	//------------------------------------------
	setfillstyle(SOLID_FILL,WHITE);
	bar3d(80,150,200,200, 5, 1);
	algobutton[0][4]=WHITE;
	outtextxy(100,170,"Simple DDA");
      
	//------------------------------------------
	 setfillstyle(SOLID_FILL,GREEN);
	bar3d(250,150,370,200, 5, 1);
		algobutton[1][4]=GREEN;
	outtextxy(255,170,"Symmetric DDA");
      
	//---------------------------
	 setfillstyle(SOLID_FILL,11);
	bar3d(420,150,540,200, 5, 1);
		algobutton[2][4]=11;
	outtextxy(450,170,"Bresenham");
      
	//---------------------------------------------

	 setfillstyle(SOLID_FILL,YELLOW);
	bar3d(250,250,370,300, 5, 1);
		algobutton[3][4]=YELLOW;
	outtextxy(280,270,"Mid Point ");
	//---------------------------------------------
	int c_x1,c_x2,c_y1,c_y2;
     
	      algobutton[0][0]=80;  //x1,y1,x2,y2
		 algobutton[0][1]= 200;
		 algobutton[0][2]= 150;
		 algobutton[0][3]=200 ;

		 algobutton[3][0]=250;
		 algobutton[3][1]= 370;
		 algobutton[3][2]= 250;
		 algobutton[3][3]=300 ;
	for(int i =1;i<3;i++)
	    {
		 algobutton[i][0]= algobutton[i-1][1]+50;
		 algobutton[i][1]= algobutton[i][0]+120;
		 algobutton[i][2]= 150;
		 algobutton[i][3]=200 ;
	    }
//---------------------ALGO SELECTION CODE--------------------------
       InitMouse();
	ShowMouse();
	int a_x,a_y;
	int k=0;
	int a_select;
	while(k==0)
{   
   if(IsClick())
     { HideMouse();
    a_x=o.x.cx;
    a_y=o.x.dx;

    for(int i =0;i<4;i++)
	{
	   if(algobutton[i][0]<=a_x&&a_x<=algobutton[i][1] && algobutton[i][2]<=a_y&&a_y<=algobutton[i][3])
	      {     
	       a_select = i;
		 setfillstyle(SOLID_FILL,LIGHTGREEN);

		bar3d(algobutton[i][0],algobutton[i][2],algobutton[i][1],algobutton[i][2], 0, 1);
		delay(150);
		setfillstyle(SOLID_FILL,algobutton[i][4]);
		bar3d(algobutton[i][0],algobutton[i][2],algobutton[i][1],algobutton[i][2], 0, 1);
		outtextxy(100,170,"Simple DDA");
		outtextxy(255,170,"Symmetric DDA");
			outtextxy(450,170,"Bresenham");
			outtextxy(280,270,"Mid Point ");
		     HideMouse();
	    
	      k=1;
		break;
	      }

	      ShowMouse();


	}



	    }
}
HideMouse();
delay(200);
//---------------------MENU ENDS -------------------------


	cleardevice();
	

//------------------COLOR SELECT--------------------------
	outtextxy(200,20,"Select color for lines");
	int c_pick=1; //color of rectangal bar
	int c_button[12][3]	; //left, right, color
	int c_left,c_top,c_right,c_bottom;
	c_left =0, c_right = 50; c_top = 50, c_bottom = 100 ;
	for(int c =0;c<11;c++)
	{    c_left +=50, c_right+=50  ;
			setfillstyle(SOLID_FILL,c_pick);
			bar3d(c_left,c_top,c_right,c_bottom, 0, 1);
			//delay(150);
			c_button[c][0]=c_left;
			c_button[c][1]=c_right;
			c_button[c][2]=c_pick;
			c_pick+=1;
	}
	setfillstyle(SOLID_FILL,WHITE);
	 bar3d(	c_button[7][0],c_top,c_button[7][1],c_bottom, 0, 1);
	c_button[7][2]=WHITE;
	//-------------color ends-----------------------------

//---------------------color MENU SELECTION CODE ---------------------------
     InitMouse();
	ShowMouse();
	int c_x,c_y;
	  k=0;
	int c_select;
	while(k==0)
{
   if(IsClick())
     { HideMouse();
       c_x=o.x.cx;
       c_y=o.x.dx;

       for(int i =0;i<11;i++)
	  {
	   if(c_button[i][0]<=c_x&&c_x<=c_button[i][1] && c_top<=c_y&&c_y<=c_bottom)
	      {     
		   c_select = i;
		   setfillstyle(SOLID_FILL,LIGHTGREEN);
		   bar3d(c_button[i][0],c_top,c_button[i][1],c_bottom, 0, 1);
		   delay(150);
		   setfillstyle(SOLID_FILL,c_button[i][2]);
		   bar3d(c_button[i][0],c_top,c_button[i][1],c_bottom, 0, 1);
	
		   HideMouse();
	     
		k=1;
		   break;
	      }

	      ShowMouse();
       }

	  }


}

//-----------------color code ends --------------------------->>

// <<--------------------------patter buttons -------------------->>
outtextxy(200,150,"Select pattern for lines");
int p_pick=WHITE; //pattern of rectangal bar
	int p_button[6][2]	; //left, right
	
	int p_left,p_top,p_right,p_bottom;
	p_left =150, p_right = 200; p_top = 180, p_bottom = 230 ;
	for( c =0;c<6;c++)
	{    p_left +=50, p_right+=50  ;
			setfillstyle(SOLID_FILL,p_pick);
			bar3d(p_left,p_top,p_right,p_bottom, 0, 1);
			p_button[c][0]=p_left;
			p_button[c][1]=p_right;
			
		
	}
	outtextxy(p_button[0][0]+5,p_top+25,"1111");
	outtextxy(p_button[1][0]+5,p_top+25,"1110");
	outtextxy(p_button[2][0]+5,p_top+25,"1100");
	outtextxy(p_button[3][0]+5,p_top+25,"1010");
	outtextxy(p_button[4][0]+5,p_top+25,"1000");	
	outtextxy(p_button[5][0]+5,p_top+25,"Else");	
// <<-----------------------pattern buttons end --------------->>
//---------------------Pattern MENU SELECTION CODE ---------------------------
     InitMouse();
	ShowMouse();
	int p_x,p_y;
	 k=0;
	int p_select;
	while(k==0)
{
   if(IsClick())
     { HideMouse();
       p_x=o.x.cx;
       p_y=o.x.dx;

       for(int i =0;i<6;i++)
	  {
	   if(p_button[i][0]<=p_x&&p_x<=p_button[i][1] && p_top<=p_y&&p_y<=p_bottom)
	      {    
		   p_select = i;
		   setfillstyle(SOLID_FILL,LIGHTGREEN);
		   bar3d(p_button[i][0],p_top,p_button[i][1],p_bottom, 0, 1);
		   delay(150);
		   setfillstyle(SOLID_FILL,WHITE);
		   bar3d(p_button[i][0],p_top,p_button[i][1],p_bottom, 0, 1);
			outtextxy(p_button[0][0]+5,p_top+25,"1111");
   			outtextxy(p_button[1][0]+5,p_top+25,"1110");
			outtextxy(p_button[2][0]+5,p_top+25,"1100");
			outtextxy(p_button[3][0]+5,p_top+25,"1010");
			outtextxy(p_button[4][0]+5,p_top+25,"1000");
			outtextxy(p_button[5][0]+5,p_top+25,"Else");	
		   HideMouse();
	     
		k=1;
		   break;
	      }

	      ShowMouse();
       }

	  }


}

int a[4];
if(p_select==5)
   {  outtextxy(200,250,"Enter Pattern in");
   cin>>a[0]>>a[1]>>a[2]>>a[3];

  }


//-----------------color code ends --------------------------->>


//-------------------THICKNESS BUTTON------------------>>
outtextxy(200,280,"Select Thickness of lines");
int t_pick=YELLOW; //pattern of rectangal bar
	int t_button[5][2]	; //left, right

	int t_left,t_top,t_right,t_bottom;
	t_left =150, t_right = 200; t_top = 310, t_bottom = 340 ;
	for( c =0;c<5;c++)
	{    t_left +=50, t_right+=50  ;
			setfillstyle(SOLID_FILL,t_pick);
			bar3d(t_left,t_top,t_right,t_bottom, 0, 1);
		
			t_button[c][0]=t_left;
			t_button[c][1]=t_right;

	
	}
	outtextxy(t_button[0][0]+5,t_top+10,"1");
	outtextxy(t_button[1][0]+5,t_top+10,"3");
	outtextxy(t_button[2][0]+5,t_top+10,"5");
	outtextxy(t_button[3][0]+5,t_top+10,"7");
	outtextxy(t_button[4][0]+5,t_top+10,"Else");

// <<-----------------------Thickness buttons end --------------->>
//---------------------thickness MENU SELECTION CODE ---------------------------
     InitMouse();
	ShowMouse();
	int t_x,t_y;
	 k=0;
	int t_select;
	while(k==0)
{
   if(IsClick())
     { HideMouse();
       t_x=o.x.cx;
       t_y=o.x.dx;

       for(int i =0;i<5;i++)
	  {
	   if(t_button[i][0]<=t_x&&t_x<=t_button[i][1] && t_top<=t_y&&t_y<=t_bottom)
	      {     
		t_select = i;
		   setfillstyle(SOLID_FILL,LIGHTGREEN);
		   bar3d(t_button[i][0],t_top,t_button[i][1],t_bottom, 0, 1);
		   delay(150);
		   setfillstyle(SOLID_FILL,t_pick);
		   bar3d(t_button[i][0],t_top,t_button[i][1],t_bottom, 0, 1);
			outtextxy(t_button[0][0]+5,t_top+10,"1");
			outtextxy(t_button[1][0]+5,t_top+10,"3");
			outtextxy(t_button[2][0]+5,t_top+10,"5");
			outtextxy(t_button[3][0]+5,t_top+10,"7");
			outtextxy(t_button[4][0]+5,t_top+10,"Else");
		
		   HideMouse();
			
		k=1;
		   break;
	      }

	      ShowMouse();
       }

	  }


}

//-----------------thickness code ends --------------------------->>

if(t_select==4)
{
	outtextxy(200,350,"Enter thickness: ");

  cin>>t_select;
}
//--------------reflection----------------------->>
//-------------------Reflcetion BUTTON------------------>>
int r_pick=11; //pattern of rectangal bar
	int r_button[2][2]	; //left, right

	int r_left,r_top,r_right,r_bottom;
	r_left =200, r_right = 330; r_top = 390, r_bottom = 440 ;
	for( c =0;c<2;c++)
	{   
			setfillstyle(SOLID_FILL,r_pick);
			bar3d(r_left,r_top,r_right,r_bottom, 0, 1);
			r_button[c][0]=r_left;
			r_button[c][1]=r_right;
	      r_left+=130, r_right+=100;
	
	}
	outtextxy(r_button[0][0]+5,r_top+25,"No Reflection");
	outtextxy(r_button[1][0]+5,r_top+25,"Reflection");
	
// <<-----------------------REflection buttons end --------------->>
//---------------------Reflection MENU SELECTION CODE ---------------------------
     InitMouse();
	ShowMouse();
	int r_x,r_y;
	 k=0;
	int r_select;
	while(k==0)
{
   if(IsClick())
     { HideMouse();
       r_x=o.x.cx;
       r_y=o.x.dx;

       for(int i =0;i<2;i++)
	  {
	   if(r_button[i][0]<=r_x&&r_x<=r_button[i][1] && r_top<=r_y&&r_y<=r_bottom)
	      {   
		   r_select = i;
		   setfillstyle(SOLID_FILL,LIGHTGREEN);
		   bar3d(r_button[i][0],r_top,r_button[i][1],r_bottom, 0, 1);
		   delay(150);
		   setfillstyle(SOLID_FILL,r_pick);
		   bar3d(r_button[i][0],r_top,r_button[i][1],r_bottom, 0, 1);
			outtextxy(r_button[0][0],r_top+25,"No Reflection");
			outtextxy(r_button[1][0],r_top+25,"Reflection");
		
		   HideMouse();

		k=1;
		   break;
	      }

	      ShowMouse();
       }

	  }


}

//-----------------reflection code ends --------------------------->>


//---------------------
LABLE2: 
delay(100);
cleardevice();

 setcolor(12);                          //outer border
   rectangle(0,0,getmaxx(),getmaxy());

   setcolor(4);
      rectangle(5,5,getmaxx()-5,getmaxy()-5);
		     //inner border
 setbkcolor(BLACK);
 setcolor(WHITE);
	line(0,getmaxy()/2,getmaxx(),getmaxy()/2);
	line(getmaxx()/2,0,getmaxx()/2,getmaxy());
	outtextxy(getmaxx()/2+3,getmaxy()/2+3,"0");

	setfillstyle(SOLID_FILL,RED);
			bar3d(getmaxx()-50,getmaxy()-30,getmaxx(),getmaxy(), 0, 1);
			outtextxy(getmaxx()-45,getmaxy()-25,"Exit");

		setfillstyle(SOLID_FILL,LIGHTGREEN);
			bar3d(getmaxx()-100,getmaxy()-30,getmaxx()-50,getmaxy(), 0, 1);
			outtextxy(getmaxx()-98,getmaxy()-25,"Repeat");
     setfillstyle(SOLID_FILL,LIGHTBLUE);
			bar3d(getmaxx()-150,getmaxy()-30,getmaxx()-100,getmaxy(), 0, 1);
			outtextxy(getmaxx()-148,getmaxy()-25,"CLEAR");
	  
	     InitMouse();
	    ShowMouse();
	    //------------pattern sellection------------------

    if(p_select==0)
	{
			for(int z =0;z<4;z++)
		     a[z]=1;
     }

     else if(p_select==1)
     { a[0]=1;
       a[1]=1;
       a[2]=1 ;
       a[3]= 0;
	}
     //	a[]={1,1,1,0};
     else if(p_select==2)
     { a[0]=1;
       a[1]=1;
       a[2]=0 ;
       a[3]= 0;

	}
     //	a[]={1,1,0,0};
     else if(p_select==3)
     { a[0]=1;
       a[1]=0;
       a[2]=1 ;
       a[3]= 0;

	}

     //	a[]={1,0,1,0};
      else if(p_select ==4)
	{ a[0]=1;
       a[1]=0;
       a[2]=0 ;
       a[3]= 0;

	}

//----------------------DFS RUN-----------------------------
	if(a_select ==0)
	{

	    InitMouse();
	while(!kbhit())
    {
	ShowMouse();
     int count_points =0;
     int point[2][2];
	do
	{
	   if(IsClick())
		{
			point[count_points][0]=o.x.cx;
			point[count_points][1]=o.x.dx;
			int x,y;
			x=point[count_points][0];
				y=point[count_points][1];
			if(x>=getmaxx()-50 && x<=getmaxx() && y>= getmaxy()-30 && y<=getmaxy())
				exit(0);
			if(x>=getmaxx()-100 && x<=getmaxx()-50 && y>= getmaxy()-30 && y<=getmaxy())
				goto LOOP;
			if(x>=getmaxx()-150 && x<=getmaxx()-100 && y>= getmaxy()-30 && y<=getmaxy())
				goto LABLE2;
			HideMouse();
			 putpixel(o.x.cx,o.x.dx,WHITE);
		       //	 circle(o.x.cx,o.x.dx,4);
			 ShowMouse();

	       count_points++;

		       }

	}while(count_points<2);

	HideMouse();

	int x1,y1,x2,y2,x12q,x22q,y14q,y24q; //																																																																																										  x2,						y2;

      x1=point[0][0];
      y1=point[0][1];
      x2=point[1][0];
      y2=point[1][1];

      //	symDDA(x1+5,y1+5,x2+5,y2+5);
    if(x1<x2)
		dda(x1,y1,x2,y2,c_button[c_select][2],a,t_select);
	else
		dda(x2,y2,x1,y1,c_button[c_select][2],a,t_select);

	if(r_select==1) //want reflections
    {
	 x12q=getmaxx()-x1;
      x22q=getmaxx()-x2;

	if(x12q<x22q)
		dda(x12q,y1,x22q,y2,c_button[c_select][2],a,t_select);
     else
	dda(x22q,y2,x12q,y1,c_button[c_select][2],a,t_select);

     int tempy1= getmaxy()/2 - y1;
     y14q=getmaxy()/2 +tempy1;
     int tempy2= getmaxy()/2 - y2;
     y24q=getmaxy()/2 +tempy2;


	if(x1<x2)
		dda(x1,y14q,x2,y24q,c_button[c_select][2],a,t_select);
     else
	     dda(x2,y24q,x1,y14q,c_button[c_select][2],a,t_select);
	if(x12q<x22q)
		dda(x12q,y14q,x22q,y24q,c_button[c_select][2],a,t_select);
	else
		dda(x22q,y24q,x12q,y14q,c_button[c_select][2],a,t_select);

		
		delay(100);
	     
    }     //reflection loop ends

    if(kbhit())
	{ HideMouse() ;
		break;
	}  // ;


} }
///////////-------------BRESHNMAN RUN-----------------------
  else 	if(a_select ==2 || a_select==3)
  {
		while(!kbhit())
    {
	ShowMouse();
	       int count_points =0;
       int point[2][2];
	do
      //	      while(!kbhit())
	{
	   if(IsClick())
		{
			point[count_points][0]=o.x.cx;
			point[count_points][1]=o.x.dx;
				int x,y;
			x=point[count_points][0];
				y=point[count_points][1];
			if(x>=getmaxx()-50 && x<=getmaxx() && y>= getmaxy()-30 && y<=getmaxy())
				exit(0);
			if(x>=getmaxx()-100 && x<=getmaxx()-50 && y>= getmaxy()-30 && y<=getmaxy())
				goto LOOP;
			if(x>=getmaxx()-150 && x<=getmaxx()-100 && y>= getmaxy()-30 && y<=getmaxy())
				goto LABLE2;

			HideMouse();
			 putpixel(o.x.cx,o.x.dx,WHITE);
		    //	 circle(o.x.cx,o.x.dx,4);
			 ShowMouse();

	       count_points++;

		       }

	}while(count_points<2);

	HideMouse();

	int x1,y1,x2,y2,x12q,x22q,y14q,y24q; //																																																																																										  x2,						y2;

      x1=point[0][0];
      y1=point[0][1];
      x2=point[1][0];
      y2=point[1][1];
       int dx,dy;//,p0,pg,ps;

    x12q=getmaxx()-x1;
      x22q=getmaxx()-x2;
     dx = abs(x2 - x1);
	 dy = abs(y2 - y1);

	int tempy1= getmaxy()/2 - y1;
     y14q=getmaxy()/2 +tempy1;
     int tempy2= getmaxy()/2 - y2;
     y24q=getmaxy()/2 +tempy2;

	if(dx>dy)
	  {
		if(x1<x2)
		      {	lineBres(x1, y1, x2, y2,c_button[c_select][2],a,t_select);
		       if(r_select==1)
			    {lineBres(x22q, y2, x12q, y1,c_button[c_select][2],a,t_select);
				lineBres(x1, y14q, x2, y24q,c_button[c_select][2],a,t_select);
				lineBres(x22q, y24q, x12q, y14q,c_button[c_select][2],a,t_select);
			}
		      }
		else
		    {	lineBres(x2, y2, x1, y1,c_button[c_select][2],a,t_select);
		    if(r_select==1)
			    {	lineBres(x12q, y1, x22q, y2,c_button[c_select][2],a,t_select);
				lineBres(x2, y24q, x1, y14q,c_button[c_select][2],a,t_select);
				lineBres(x12q, y14q, x22q, y24q,c_button[c_select][2],a,t_select);
			}

		    }
	  }
	else
	{	if(y1<y2)
		     {	lineBres(x1, y1, x2, y2,c_button[c_select][2],a,t_select);
		     if(r_select==1)
			    {lineBres(x12q, y1, x22q, y2,c_button[c_select][2],a,t_select);
				lineBres(x2, y24q, x1, y14q,c_button[c_select][2],a,t_select);
				lineBres(x22q, y24q, x12q, y14q,c_button[c_select][2],a,t_select);
			}

			}
		else
		      {	lineBres(x2, y2, x1, y1,c_button[c_select][2],a,t_select);
			lineBres(x22q, y2, x12q, y1,c_button[c_select][2],a,t_select);
			 if(r_select==1)
			    {lineBres(x22q, y2, x12q, y1,c_button[c_select][2],a,t_select);
				lineBres(x1, y14q, x2, y24q,c_button[c_select][2],a,t_select);
				lineBres(x12q, y14q, x22q, y24q,c_button[c_select][2],a,t_select);
			}
			}
	}
  }
}

//------------------breshnman ends ------------------------

//--------------------------symmetric dda -----------------------

else if(a_select==1)
  {
		while(!kbhit())
    {
	ShowMouse();
	int count_points =0;
     int point[2][2];
	do

	{
	   if(IsClick())
		{
			point[count_points][0]=o.x.cx;
			point[count_points][1]=o.x.dx;
			int x,y;
			x=point[count_points][0];
				y=point[count_points][1];
			if(x>=getmaxx()-50 && x<=getmaxx() && y>= getmaxy()-30 && y<=getmaxy())
				exit(0);
			if(x>=getmaxx()-100 && x<=getmaxx()-50 && y>= getmaxy()-30 && y<=getmaxy())
				goto LOOP;
			if(x>=getmaxx()-150 && x<=getmaxx()-100 && y>= getmaxy()-30 && y<=getmaxy())
				goto LABLE2;
			HideMouse();
			 putpixel(o.x.cx,o.x.dx,WHITE);
		      //	 circle(o.x.cx,o.x.dx,4);
			 ShowMouse();

	       count_points++;

		       }

	}while(count_points<2);

	HideMouse();

	int x1,y1,x2,y2,x12q,x22q,y14q,y24q; //																																																																																										  x2,						y2;

      x1=point[0][0];
      y1=point[0][1];
      x2=point[1][0];
      y2=point[1][1];
       int dx,dy;//,p0,pg,ps;

    x12q=getmaxx()-x1;
      x22q=getmaxx()-x2;


	int tempy1= getmaxy()/2 - y1;
     y14q=getmaxy()/2 +tempy1;
     int tempy2= getmaxy()/2 - y2;
     y24q=getmaxy()/2 +tempy2;

     symDDA(x1,y1,x2,y2,c_button[c_select][2],a,t_select);
     if(r_select==1)
       {
	symDDA(x1,y1,x2,y2,c_button[c_select][2],a,t_select);
		symDDA(x12q,y1,x22q,y2,c_button[c_select][2],a,t_select);
		symDDA(x1,y14q,x2,y24q,c_button[c_select][2],a,t_select);
	symDDA(x12q,y14q,x22q,y24q,c_button[c_select][2],a,t_select);
	  }


	}
  }



//-------------------Breshenam algo ends--------------------->>

	  delay(60);

cleardevice();

	getch();
	closegraph();
	return 0;

}


