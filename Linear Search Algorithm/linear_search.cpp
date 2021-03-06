#include<iostream>
#include<ctime> //for time
#include<stdlib.h> //random ()
#include<fstream> //for file
using namespace std;
int main()
{ int best, avg, worst;
  best=avg=worst=0;

    ofstream f("graph.txt");
    ofstream f1("graph_best.txt"); //store number of best cases in linear search
    ofstream f2("graph_avg.txt"); //store number of average cases in linear search
    ofstream f3("graph_worst.txt"); //store number of worst cases in linear search

    int size_array=50;
    double sum_array=0;
    int num_case=10000;

    while(size_array<=5000)                 //Loop till array size reaches 5000
    {


        for(int z=0;z<num_case;z++) // Run for 10,000 cases
        {
            int a[size_array];
            int key=rand(); //random key selected
            for(int i=0;i<size_array;i++) // To enter random values in array
            {
                a[i]=rand();
            }

            clock_t start, endi;
            start=clock();
            int flag=0; // if key is not found, then flag = 0 else flag = 1

        for(int k=0;k<size_array;k++)  //To search key in array
        {
            if(a[k]==key)
            { flag=1;
                 if(k<=0.25*size_array)
                  {
                      best++;
                  }
                if(k<=0.75*size_array && k>0.25*size_array)
                  {
                      avg++;
                  }
                  if(k>0.75*size_array)
                    {
                      worst++;
                    }
                break;
            }
        }

        if(flag==0)
            worst++;

        endi=clock();

        double duration=endi-start/(double) CLOCKS_PER_SEC; //converting time unit to second
        sum_array+=duration;
        }
    cout<<"size: "<<size_array<<'\t'<<"Time: "<<sum_array/100000<<'\t'<<'\t'<<"best: "<<best<<'\t'<<"avg: "<<avg<<'\t'<<"worst: "<<worst<<endl;

    //storing values in file
    f<<size_array<<'\t'<<sum_array/100000<<endl;
    f1<<size_array<<'\t'<<best<<endl;
     f2<<size_array<<'\t'<<avg<<endl;
     f3<<size_array<<'\t'<<worst<<endl;
    size_array+=50;

    sum_array=best=avg=worst=0;
    }

return 0;

}
