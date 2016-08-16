//Finding maximum and minimum elements of an array recursively and iterarively
#include<iostream>
#include<stdlib.h>
#include<time.h>
#include<fstream> //for file
using namespace std;

void maxmin(int a[], int low,int high, int &max, int &min) //Recursive Search
{ //a[] - array of elements
  //low- lowest index in an array
  // high is the highes index in an array
  //max - maximum element in array
  //min - minimum element in array

    int min1, max1;
	if(low==high) //only one element in an array
	     { min=max=a[low];
	       return;
		 }
    if(low==high-1) //only 2 elements in an array
	   {
	   	if(a[low]<a[high])
	   	   { min=a[low];
	   	     max=a[high];
	   	     return;
		   }
		 else
		 {
		   max=a[low];
		  min=a[high];
		  return;
		}
    }

    int mid=(low+high)/2; //mid element of an array

    maxmin(a,low,mid,max,min); // recursive call

    maxmin(a,mid+1,high,max1,min1); // recursive call

    if(max1>max)
       max=max1;
    if(min1<min)
       min=min1;
}

void l_maxmin(int a[],int sizei, int &l_max, int &l_min) // Linear Search
{  //a[] - array of elements
   //sizei - size of elements
   //l_max - maximum value of array
   //l_min - minimum element of array
for(int j=1;j<sizei;j++)
    {
        if(a[j]>l_max)
        {
            l_max=a[j];
        }
        if(a[j]<l_min)
        {
            l_min=a[j];
        }
    } return;
}

int main()
{
  ofstream f_r("recursion.txt");
  ofstream f_b("brute-force.txt");

  int low, high;
  low=0;
  double total,l_total; // total - total time to search in recursive search
  total=l_total=0.0;    //l_total - total time to search in linear search
  int run=100000;

  srand(time(NULL)); //TO Generate different values in rand()

  for(int n=500;n<10000;n+=300)
  { for(int k=0;k<run;k++)
    {
        high=n;
        int a[high];
        int sizei=high;
        int max,min,l_min,l_max;

        for(int i=0;i<sizei;i++) //radnombly giving values
        {
         a[i]=rand()%10000;

        }

         l_min=l_max=min=max=a[0];

    //calculating time for finding maximum and minimum recursively
    time_t starting=clock();
    maxmin(a,low,high-1,max,min);
    time_t ending=clock();

    double duration=(ending-starting);//(double) CLOCKS_PER_SEC; //converting time from tic to seconds
    total+=duration;

    //calculating time for finding maximum and minimum through brute force

    time_t start=clock();
    l_maxmin(a,sizei,l_max,l_min);
    time_t end=clock();

    double l_duration=(end-start);//(double) CLOCKS_PER_SEC;
    l_total+=l_duration;

     }

     f_b<<endl<<n<<'\t'<<total/5000<<'\t'<<total/5000;
	 f_r<<endl<<n<<'\t'<<total/5000<<'\t'<<l_total/5000;
	 cout<<endl<<n<<'\t'<<total/5000<<'\t'<<l_total/5000;

 total=l_total=0;
}
f_b.close();
f_r.close();
    return 0;

}

