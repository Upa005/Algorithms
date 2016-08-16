 #include<conio.h> //for getch
 #include<iostream>
 #include<math.h> //for abs
 using namespace std;
  
  int k,x[20],c,n;
  void printing();
  int place(int,int);
  int nqueen(); 
  
  
   void nqueen(int k,int n)
    {  int i;
      for(i=1;i<=n;i++)
       { if(place(k,i))
        {    x[k]=i;
           if(k==n)
            {  c++;
             getch();
              printing();
            }
          else
		    nqueen(k+1,n);
        }
       }
    }
  

  int place(int k,int i)
  {  for(int j=1;j<=k-1;j++)
   if (x[j]==i || (abs(x[j]-i)==abs(j-k)))
        return 0;
   return 1;
   }
  void printing()
  { for(int i=1;i<=n;i++)
      {    for(int j=1;j<=n;j++)
      {    if(x[i]==j) 
	         cout<<" Q " ;
            else
		     cout<<" _ ";    
	  }
          cout<<"\n"; 
       }
          cout<<"\n\n";
   }
         int main()
         {      	   
         cout<<"\n Enter the  number of Queen's: ";
         cin>>n;
	    nqueen(1,n);
	    //cout<<"\n Enter any key to continue ";
         cout<<"\n\n Total number of solutions are : "<<c;
         getch();
	    }
