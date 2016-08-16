#include<iostream>
#include<algorithm>
#include<time.h>
#include<stdlib.h>
using namespace std;

int quicksort(int a[],int beg,int end)
{int i, j, v;
  i=beg; j=end; v=a[beg];
  while(i<j)
  {while(v>=a[i] && i<=end)
      i++;
      while(v<a[j])
             j--;
   if(i<j)
    {int temp=a[i];
      a[i]=a[j];
      a[j]=temp;
	}

  }
  int t=a[beg];
  a[beg]=a[j];
  a[j]=t;
  return j;
}
int r_quick(int a[],int beg,int end)   //for randomized quick sort
{
    int newbeg=beg+rand()%(end-beg+1);  //taking random number from the remaining list
        int temp;
        temp=a[beg];
        a[beg]=a[newbeg];
        a[newbeg]=temp;
        return quicksort(a,beg,end);  //calling quick sort after changing pivot value
}

void qsort(int a[],int beg,int end) //funtion to call quick sort in two parts
{if(beg<end)
  { 
    int j=quicksort(a,beg,end);
    qsort(a,beg,j-1);
    qsort(a,j+1,end);

  }
}
void r_qsort(int a[],int beg,int end) //fucntion to call randomized quick sort
{if(beg<end)
  { 
    int j=r_quick(a,beg,end);
    r_qsort(a,beg,j-1);
    r_qsort(a,j+1,end);

  }
}

int main()
{ int size=1000;
 srand(time(NULL)); //for getting random value every time

cout<<"Quick sort \t Randomized quick sort";

double t,r_t; //time 
r_t=t=0;
 int s=100; //array size which will increase 
 int k;
       int run=10000;         //for a particular array size the program will run for this given value
       
       for(int l=0;l<size;l++)
      {
          int a[s],b[s];     // a[] : for quick sort and b[] : for randomized quick sort

            
       for( k=0;k<run;k++)
          {
              for(int i=0;i<s;i++)
            {b[i]=a[i]=rand();
         
             }
            
            sort(b,b+s);

         clock_t start,endi,r_start,r_endi;
         
         
          start=clock();
               qsort(a,0,s-1);
          endi=clock();
          double duration=(endi-start);///(double) CLOCKS_PER_SEC;
          t+=duration;

     
            r_start=clock();
                   r_qsort(b,0,s-1);
            r_endi=clock();
              double r_duration=(r_endi-r_start);
              r_t+=duration;
         }

     s+=200; //array size increses
     
     cout<<"\n"<<t/run<<"\t\t"<<r_t/run;
     t=r_t=0;
     }
    
          return 0;
}
