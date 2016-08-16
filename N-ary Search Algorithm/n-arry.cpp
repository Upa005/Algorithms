//Program for n-ary search
#include<iostream>
#include<time.h>  //time
#include<stdlib.h> //rand()
#include<fstream>    //file
#include<algorithm>  //sorting
using namespace std;

void searching(int a[],int start, int endi, int sizei,int p, int key)
{ //a - array of elements
  // start - starting index of array
  //endi - end index of array
  //sizei - size of array elements
  // key is the element to search
  //p is p-ary search

  if((key<a[start]) || (key>a[endi]))
     {

         return ;
     }
   else if(sizei<=p)     //linear search
       {
	    for(int j=start;j<=endi;j++)
           {if(a[j]==key)
              {
                return;
              }
            }

         }
   else
     {
     int b[100];
     b[0]=start;
     int mid_p=(sizei/p)+1;
     int i;
     for(i=1;i<p;i++)
        {
          b[i]=(start+(mid_p*i)-1);   //finding partitioning indexes

        }
        b[i]=endi;
     for(int z=0;z<=i;z++)
        {
          if(key==a[b[z]])
             { //cout<<" found";
              return;
             }
          if(key<a[b[z]])
             {
                start=b[z-1]+1;
                endi=b[z]-1;
                sizei=endi-start+1;
                searching(a,start,endi,sizei,p,key); //recursive search
                  break;
              }
        }
  }
}

int main()
{ ofstream f("output.txt");
   int sizei=100;
   int start=0; int endi=99;
   int a[100] ,l;
   double tot=0.0; //total time to search
   double total;
   srand(time(NULL)); //TO Generate different values in rand()
   //array-random valued

    for(l=2;l<=100;l+=2)
        {
		    for(int y=0;y<500000;y++)
		   {

             for(int u=0;u<sizei;u++) //adding values in array
                a[u]=rand() %1000;


            for(int i=0;i<sizei;++i) //sorting-bubble sort
                {
                  for(int j=0;j<(sizei-i);++j)
                  if(a[j]>a[j+1])
                    {
                     int temp=a[j];
                    a[j]=a[j+1];
                     a[j+1]=temp;
                    }
               }

                   int k=rand() %100;
                int key=a[k];

				 time_t starting=clock();
	             searching(a,start,endi,sizei,l,key);
                 time_t ending=clock();
                 time_t duration=ending-starting;
                 total=duration/(double) CLOCKS_PER_SEC; //converting time from tic to seconds

                 tot+=total;

                }

    cout<<endl<<l<<'\t'<<tot;
     f<<l<<"\t"<<tot<<endl; //sending data to file
     tot=0;
    }
 f.close();
return 0;
}


