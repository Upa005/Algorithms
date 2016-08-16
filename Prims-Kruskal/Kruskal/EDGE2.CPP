 //kruskal's algorithm
#include<mymouse.h>

int adj[MAX_VERT][MAX_VERT];
int extra[MAX_VERT][MAX_VERT];

struct new_vertex
{  int x, y, number,i;  //number- display , i- index
	char name[2];  //character
 };
typedef struct new_vertex Vertex;
 int vcount;
 Vertex vert[MAX_VERT];
struct new_edge
{    Vertex *u, *v;
	int wt;
};

typedef struct new_edge Edge;
Edge edge[100];
int ecount;
int mstcost;

int dist(int a,int b,int c,int d)
{
  int p;
  p=sqrt(pow(a-c,2)+pow(b-d,2));
  return p;
}

void vertex_fill(Vertex *v,int color)
{
	char str[5];
	HideMouse();
	setcolor(RED);  //set the current drawing jor
	setfillstyle(SOLID_FILL,color);  //set jor to fill in some object
	fillellipse(v->x,v->y,20,20);
	setcolor(MAGENTA);
	outtextxy(v->x-3,v->y-12,v->name);

	setcolor(RED);
     //		setcolor(BLINK);
	sprintf(str,"[%d]",v->number);

	outtextxy(v->x-14,v->y-3,str);

	ShowMouse();
}
void  Edge_fill(Vertex *u, Vertex  *v, int color,boolfun weight)   //fill the edges
{ int xw,yw;
	char ch[10];
		setcolor(color);
	line(u->x,u->y,v->x,v->y);
	vertex_fill(u,LIGHTGREEN);
	vertex_fill(v,LIGHTGREEN);

	    if(weight)
	   {
			xw= -((u->x -v->x)/2);
		yw= -((u->y -v->y)/2);
		sprintf(ch,"%d",adj[u->i][v->i]);
		setcolor(WHITE);
		outtextxy(u->x+xw,u->y+yw,ch);
   }
}
void Redraw(const int mat[][MAX_VERT]) //redraw graph when required
{
	int i,j;
	int tempmat[MAX_VERT][MAX_VERT];

	cleardevice();

		for(i=0;i<vcount;i++)
		for(j=0;j<vcount;j++)
		    tempmat[i][j]=1;

	for(i=0;i<vcount;i++)
	{
		for(j=0;j<vcount;j++)
		{
			if(mat[i][j]&& tempmat[j][i] && mat[i][j]!=MAX_NUM)
			{
			  Edge_fill(&vert[i],&vert[j],MAGENTA,TRUE);
				tempmat[i][j]=tempmat[j][i]=0;
			}
		}
	}
}
void GetVertices()      //initially take input in form of vertex
{
	char name_v='A';
	vcount=0;
     //	char c;

      //	cleardevice;
	setcolor(WHITE);
	outtextxy(50,250,"MINIMUM COST SPANNING TREE...(PRESS ENTER TO CONTINUE)") ;
       getch();

       cleardevice;
	setcolor(BLACK);
		outtextxy(50,250,"MINIMUM COST SPANNING TREE...(PRESS ENTER TO CONTINUE)") ;
	setcolor(LIGHTGREEN);
	outtextxy(20,1,"Click with mouse and press enter to add vertex");
       outtextxy(20,10,"Press 1 if creation of vertices are done");
	 InitMouse();
	ShowMouse();
		do
	  //   while(!kbhit())
	{   //    printf("hello there");
		if(IsClick())
		{                  //  printf("hello there");
			sprintf(vert[vcount].name,"%c",name_v++);
			vert[vcount].x=o.x.cx;
			vert[vcount].y=o.x.dx;
			vert[vcount].i=vcount;
			vert[vcount].number=vcount+1;
			vertex_fill(&vert[vcount],YELLOW);
			vcount++;
		   //	getch();

	       //	if(kbhit())
		     if(getch()=='1')
			break;
	       }
	// }
      }while(vcount<MAX_VERT); //TOTAL VERTEX

	HideMouse();
}

void GetEdges()   //take weight from user
{      //  getch();
      // printf("hwll");
      // getch();
	setcolor(LIGHTBLUE);
	outtextxy(20,1,"Click with mouse and press enter to add vertex");
       outtextxy(20,10,"Press 1 if creation of vertices are done");
	int i,j,p,q,p1,q1;
	int first_v,second_v,flag1,flag2;
  int count1=0,temp1=0;
  // flag1=flag2=0;
	for(i=0;i<vcount;i++)
		for(j=0;j<vcount;j++)
		{
			adj[i][j]=MAX_NUM;
			extra[i][j]=0;
		}
     InitMouse();
	ShowMouse();
		setcolor(LIGHTGREEN);

	outtextxy(30,20,"Create edges");
	outtextxy(20,30,"Presss right mouse click to select first vertex");
       outtextxy(20,40,"Press left mouse click to select other vertex.");
       outtextxy(20,50,"Press any keyboard key when done ");
       //	outtextxy(4,20,"Point with mouse and press enter to add vertex");
 while(!kbhit())
{   flag1=flag2=0;
   if(IsClick())
      {if(count1==0&&o.x.bx==2&&temp1==0) //right button is clicked
	{
	    p=o.x.cx;
	    q=o.x.dx;
	    count1=1;
	    o.x.bx=0;
	    temp1=1;
		for(int i=0;i<vcount;i++)
	     {
	       if((dist(vert[i].x,vert[i].y,p,q))<=20&& flag1==0)
	       {    first_v=i;
			 vertex_fill(&vert[first_v],WHITE);
		  //break;
		  flag1=1;
		}
	     }
	  }
	    }
	  //  getch();

	  if(IsClick())
     { if(o.x.bx==1&&count1==1&&temp1==1)
      {
       count1=0;
       p1=o.x.cx;
       q1=o.x.dx;
       temp1=0;


		 for(int j=0;j<vcount;j++)
		 {
		    if(dist(vert[j].x,vert[j].y,p1,q1)<=20&& flag2==0 && j!=first_v)
		    {       second_v=j;
				 vertex_fill(&vert[second_v],WHITE);
				 flag2=1;

		     Edge_fill(&vert[first_v],&vert[second_v],BROWN,FALSE);
		     adj[first_v][second_v]=adj[second_v][first_v]=-1;
		      //	break;
		    }
		 }
      }
     }


	   }


 }

void edgecost()
{

	setcolor(LIGHTBLUE);

	outtextxy(30,20,"Create edges");
	outtextxy(20,30,"Press right mouse click to select first vertex");
       outtextxy(20,40,"Press left mouse click to select other vertex.");
       outtextxy(20,50,"Press any keyboard key when done ");
ecount=0;
//cleardevice;

 int cost;
// char str[20];
 for(int k=0;k<vcount;k++)
 {
  for(int j=0;j<vcount;j++)
  {

     if(adj[k][j]==-1)
    {             setcolor(YELLOW);
     printf("Enter the cost for edge (%s %s) ",vert[k].name,vert[j].name);
   scanf("%d",&cost);
     adj[j][k]=adj[k][j]=cost;


						edge[ecount].u=&vert[k];
						edge[ecount].v=&vert[j];
						edge[ecount].wt=cost;
						 Edge_fill(&vert[k],&vert[j],RED,TRUE);

       ecount++;

    }

   }
  }
}




void SortMe()
{
    int i,j;
  Edge temp;

  for(i=0;i<ecount;i++)
  for(j=i+1;j<ecount;j++)
  {
	if(edge[i].wt<edge[j].wt)
	{
		temp=edge[i];
		edge[i]=edge[j];
		edge[j]=temp;
	}
  }
}

void Merge(int a,int b)
{         int i;
	for(i=0;i<vcount;i++)
	if(vert[i].number==b)
	{ vert[i].number=a;

	}
}

int main()
{
	int gd=DETECT,gm;
	initgraph(&gd,&gm,"c://TC/bgi");
	  setbkcolor(LIGHTBLUE);
	setlinestyle(SOLID_LINE,1,3);
	GetVertices();
 GetEdges();
 getch();
       edgecost();
       getch();
	Redraw(adj);
	getch();
	//KruskalsAlgo();

    int v_c,e_c;
Edge * e1;
v_c=vcount;
e_c=ecount;
mstcost=0;
SortMe();
gotoxy(1,1);

while(e_c>0)
{           printf("\n");
	e1=&edge[--e_c];
       //	printf("hello %d",v_c);
	printf("%s%s(%d)  ",e1->u->name,e1->v->name,e1->wt);
	if(e1->u->number!=e1->v->number)
	{
	     extra[e1->u->i][e1->v->i]=1;
		extra[e1->v->i][e1->u->i]=1;
		mstcost+=adj[e1->u->i][e1->v->i];
		Merge(e1->u->number,e1->v->number);
	  Edge_fill(e1->u,e1->v,YELLOW,FALSE);
		v_c--;
	}
		else
	Edge_fill(e1->u,e1->v,MAGENTA,FALSE);

      getch();
}
      // getch();
	Redraw(extra);
	gotoxy(2,4);

	printf("Minimum Cost of this spaning tree is : %d",mstcost);

	getch();

	closegraph();
	return 0;
}






