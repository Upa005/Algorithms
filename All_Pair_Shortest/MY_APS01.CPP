#include<mouse.h>

#define MAX_EDGE 100
#define MAX_VERT 10
#define MAX_NUM 30000


int adj[MAX_VERT][MAX_VERT];
int A[MAX_VERT][MAX_VERT];

struct new_vertex
{  int x, y, number,i;  //number- display , i- index
	char name[2];  //character
 };
typedef struct new_vertex Vertex;
 int vcount;
 Vertex vert[MAX_VERT];
struct new_edge
{    Vertex *u, *v;
	int wtij;
	int wtji;
};
typedef struct new_edge Edge;
Edge edge[100];
int ecount;
int mstcost;
void vertex_fill(Vertex *v)
{
	char str[5];
	HideMouse();
	setcolor(YELLOW);  //set the current drawing jor
	setfillstyle(SOLID_FILL,YELLOW);  //set jor to fill in some object
	fillellipse(v->x,v->y,20,20);
	setcolor(MAGENTA);
	outtextxy(v->x-3,v->y-12,v->name);

	setcolor(RED);
     //		setcolor(BLINK);
	sprintf(str,"[%d]",v->number);

	outtextxy(v->x-14,v->y-3,str);

	ShowMouse();
}
void  Edge_fill(Vertex *u, Vertex  *v, int color)   //fill the edges
{ int xw,yw;
	char ch[10];
	char ch1[5];
		setcolor(color);
	line(u->x,u->y,v->x,v->y);
	vertex_fill(u);
	vertex_fill(v);


		xw= -((u->x -v->x)/2);
		yw= -((u->y -v->y)/2);
		sprintf(ch,"%d",adj[u->i][v->i]);
		sprintf(ch1,"%d",adj[v->i][u->i]);
		setcolor(WHITE);
		outtextxy(u->x+xw,u->y+yw,ch);
		outtextxy(u->x+xw,u->y+yw+10,ch1);

}
void  Edge_fill_new(Vertex *u, Vertex  *v, int color)   //fill the edges
{ int xw,yw;
	char ch[10];
    //	char ch1[5];
		setcolor(color);
	line(u->x,u->y,v->x,v->y);
	vertex_fill(u);
	vertex_fill(v);


		xw= -((u->x -v->x)/2);
		yw= -((u->y -v->y)/2);
		sprintf(ch,"%d",adj[u->i][v->i]);
	     //	sprintf(ch1,"%d",adj[v->i][u->i]);
		setcolor(WHITE);
		outtextxy(u->x+xw,u->y+yw,ch);
	      //	outtextxy(u->x+xw,u->y+yw+10,ch1);

}
void Redraw(const int mat[][MAX_VERT], int flag) //redraw graph when required
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
			if(mat[i][j]&& tempmat[j][i])
			{  if(flag==0)
			{
			  Edge_fill(&vert[i],&vert[j],MAGENTA);
				tempmat[i][j]=tempmat[j][i]=0;
			}
			else
			{  Edge_fill_new(&vert[i],&vert[j],MAGENTA);
				tempmat[i][j]=tempmat[j][i]=0;

			}}
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
	outtextxy(4,1,"Point with mouse and press enter to add vertex");
       outtextxy(4,10,"Press 1 if creation of vertices are done");
	 InitMouse();
	ShowMouse();
	do
	{
		if(IsClick())
		{
			sprintf(vert[vcount].name,"%c",name_v++);
			vert[vcount].x=i.x.cx;
			vert[vcount].y=i.x.dx;
			vert[vcount].i=vcount;
			vert[vcount].number=vcount+1;
			vertex_fill(&vert[vcount]);
			vcount++;
		   //	getch();

	       //	if(kbhit())
			if(getch()=='1')
			break;
			}
	}while(vcount<MAX_VERT); //TOTAL VERTEX

	HideMouse();
}
void GetEdges()   //take weight from user
{
	int i,j;

	for(i=0;i<vcount;i++)
		for(j=0;j<vcount;j++)
		{       if(i==j)
			    adj[i][j]=0;
		      else
			adj[i][j]=30000;
		     //	extra[i][j]=0;
		}

     //	gotoxy(35,12);

	printf("Enter weight of the vertices. Enter 0 if there is no edge\n");
	printf(" \n                                                        ");
	printf("                                                       ");

	for(i=0;i<vcount;i++)
	{
		printf("\n");
		for(j=0;j<vcount;j++)
		{
			if(adj[i][j]==30000)
				{
				      printf("(%s%s):",vert[i].name,vert[j].name);
					scanf("%d",&adj[i][j]);
					if(adj[i][j]==0)
					    adj[i][j]=1000;
					printf("(%s%s):",vert[j].name,vert[i].name);
					scanf("%d",&adj[j][i]);
					 if(adj[j][i]==0)
					    adj[j][i]=1000;
				    //	if(adj[i][j])
				       Edge_fill(&vert[i],&vert[j],LIGHTBLUE);
						edge[ecount].u=&vert[i];
						edge[ecount].v=&vert[j];
						edge[ecount].wtij=adj[i][j];
						edge[ecount].wtji=adj[j][i];
						ecount++;
					 }



				   //ecount++;

		   }
			//else adj[i][j]=0;
		}
	}



int min(int a, int b)
{

	if(a<b)
		return a;
	else
		return b;
}

void AllPath()
{ setcolor(WHITE);
      //	outtextxy(5,10,"Adjecny matrix is:") ;
       //	getch();
  printf("Adjecny matrix is:\n ");
 // gotoxy(5,20);
   printf("\n");
    for(int i =0;i<vcount;i++)
	   { for(int j=0;j<vcount;j++)
		{  printf("%d ",adj[i][j]);   }
		  printf("\n");
	   }
   for( i = 0; i<vcount;i++)
	  {
		for(int j=0;j<vcount;j++)
			 A[i][j]=adj[i][j];

	   }

	   for(int k=0; k<vcount;k++)
	   { for( i=0; i<vcount;i++)
		 {
			for(int j=0; j<vcount;j++)
				A[i][j]=min(A[i][j],A[i][k]+A[k][j]);
		 }


	   }
	     printf("\n\nMatrix of APSP problem:\n");
	   for(i =0;i<vcount;i++)
	   { for(int j=0;j<vcount;j++)
		{  printf("%d ",A[i][j]);   }
		  printf("\n");
	   }
}

int main()
{
	int gd=DETECT,gm;
	initgraph(&gd,&gm,"c://TC/bgi");
	setlinestyle(SOLID_LINE,1,3);
	GetVertices();
	GetEdges();
	Redraw(adj,0);
	AllPath();
       //	Redraw(A,0);
     //	Redraw(A);
	//gotoxy(2,4);

	//printf("Minimum Cost of this spaning tree is : %d",mstcost);

	getch();

	closegraph();
	return 0;
}





