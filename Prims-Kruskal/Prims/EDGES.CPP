//prim's algorithm
#include<mymouse.h>

int adj[MAX_VERT][MAX_VERT];
int extra[MAX_VERT][MAX_VERT]; // to print final matrix
int near1[MAX_VERT];
int t[MAX_VERT][2];

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
int mincost;

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
	setcolor(BLUE);  //set the current drawing jor

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

void  Edge_fill(Vertex *u, Vertex  *v, int color, boolfun weight)   //fill the edges
{ int xw,yw;
	char ch[10];
		setcolor(color);
	line(u->x,u->y,v->x,v->y);
	vertex_fill(u,YELLOW);
	vertex_fill(v,YELLOW);

	      if(weight)
	    {	xw= -((u->x -v->x)/2);
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
			if(mat[i][j]!=MAX_NUM&& tempmat[j][i]&&mat[i][j]!=0)
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

	setcolor(WHITE);
	outtextxy(50,250,"MINIMUM COST SPANNING TREE...(PRESS ENTER TO CONTINUE)") ;
       getch();

       cleardevice;
	setcolor(BLACK);
		outtextxy(50,250,"MINIMUM COST SPANNING TREE...(PRESS ENTER TO CONTINUE)") ;
	setcolor(LIGHTGREEN);
	outtextxy(4,1,"Click with mouse and press enter to add vertex");
       outtextxy(4,10,"Press 1 if creation of vertices are done");
	 InitMouse();
	ShowMouse();

	do
      //	      while(!kbhit())
	{
	   if(IsClick())
		{
			sprintf(vert[vcount].name,"%c",name_v++);
			vert[vcount].x=o.x.cx;
			vert[vcount].y=o.x.dx;
			vert[vcount].i=vcount;
			vert[vcount].number=vcount+1;
			vertex_fill(&vert[vcount],YELLOW);
			vcount++;
		   //	getch();

	    //   if(kbhit())
	      //	     break;
		       if(getch()=='1')
			break;
			}
	}while(vcount<MAX_VERT); //TOTAL VERTEX

	HideMouse();
}
void GetEdges()   //take weight from user
{        getch();
    //  cleardevice;
	setcolor(BROWN);
	outtextxy(4,1,"Point with mouse and press enter to add vertex");
       outtextxy(4,10,"Press 1 if creation of vertices are done");
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

	outtextxy(10,20,"Create edges");
	outtextxy(4,30,"Presss right mouse click to select first vertex");
       outtextxy(4,40,"Press left mouse click to select other vertex.");
       outtextxy(4,50,"Press any keyboard key when done ");

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

		     Edge_fill(&vert[first_v],&vert[second_v],RED,FALSE);
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


	setcolor(BROWN);

	outtextxy(4,20,"Create edges");
	outtextxy(4,30,"Press right mouse click to select first vertex");
       outtextxy(4,40,"Press left mouse click to select other vertex.");
       outtextxy(4,50,"Press any keyboard key when done ");
 int cost;
// char str[20];
 for(int k=0;k<vcount;k++)
 {
  for(int j=0;j<vcount;j++)
  {

     if(adj[k][j]==-1)
    {
     printf("Enter the cost for edge (%s %s) ",vert[k].name,vert[j].name);
   scanf("%d",&cost);
     adj[j][k]=adj[k][j]=cost;
     //printf("%d %d",adj[j][k], adj[k][j]);

						edge[ecount].u=&vert[k];
						edge[ecount].v=&vert[j];
						edge[ecount].wt=adj[k][j];
						 Edge_fill(&vert[k],&vert[j],LIGHTBLUE,TRUE);
						ecount++;

    }
   }
  }
}






int main()
{
	int gd=DETECT,gm;
	initgraph(&gd,&gm,"c://TC/bgi");
	setbkcolor(BROWN);
	setlinestyle(SOLID_LINE,1,3);
	GetVertices();
	GetEdges();
      //	getch();
	edgecost();
       getch();
	Redraw(adj);
   //PRIMS ALGO
    Vertex *v;
	int min_edge=MAX_NUM;
   int min_x, min_y,k,l,z;

   for(z=0;z<vcount;z++) //create near
	 near1[z]=-1;

   for(k=0;k<vcount;k++) //near array fill
     {
	for(l=0;l<vcount;l++)
	  {
		if(adj[k][l]<min_edge)
		    {min_edge=adj[k][l];
		      min_x=k;
		      min_y=l;
		     }
	    }
	}

    mincost=0;
   mincost+=min_edge;
  // int m=MAX_VERT;
   //int t[m][2];
   t[0][0]=min_x;
   t[0][1]=min_y;

   Edge_fill(&v[min_x],&v[min_y],RED,TRUE);
   getch();
    extra[min_x][min_y]=1;
    extra[min_y][min_x]=1;

   for(z=0;z<vcount;z++)   //near array update
   {
	if(adj[z][min_x]<adj[z][min_y])
	       near1[z]=min_x;
	else
		 near1[z]=min_y;
   }

   near1[min_x]=near1[min_y]=-1;
  // int k;
   int min_j;
   //prims algorithm
   for( z =1;z<vcount-1;z++)
   {  min_j=MAX_NUM;

	     for(int j=0;j<vcount;j++) //choose nearest vertex
	      {
		if(adj[j][near1[j]]<min_j && near1[j]!=-1)
		    min_j=j;
		    }

	t[z][0]=min_j;
	   t[z][1]=near1[min_j];

	 mincost+=adj[min_j][near1[min_j]];

	 extra[min_j][near1[min_j]]=1;
	  extra[near1[min_j]][min_j]=1;

	 near1[min_j]=-1;

	 for(k=0;k<vcount;k++)
	 {
		if(near1[k]!=-1 && adj[k][near1[k]]>adj[k][min_j])
		    near1[k]=min_j;

	}
}
      getch();
	Redraw(extra);
	gotoxy(2,4);

	printf("Minimum Cost of this spaning tree is : %d",mincost);

	getch();

	closegraph();
	return 0;
}






