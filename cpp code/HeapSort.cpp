#include<iostream>
using namespace std;

void percolate_down(int A[], int r, int n)
{
     int c = 2* r;
     while (r<=n)
     {
           if (c<n && A[c]<A[c+1])
              c++;
           if (A[r]<A[c]) 
           {
              swap(A[r], A[c]);
              r = c;
              c = 2*c;
              if (c>n) break;
           }
           else break;
     }
}

void heapify(int A[], int n)
{
     for (int r = n/2; r>=1; r--)
         percolate_down(A, r, n);
}

void heapsort(int A[], int n)
{
     if (n!=0)
     {
         heapify(A, n);
         swap(A[1], A[n]);
         heapsort(A, n-1);
         }
}
        
int main()
{
    int A[14]={0, 4, 7, 3, 1, 8, 9, 2, -2, 6, 12, -4, 5, 23};
    int n=13;
    heapsort(A, n);
    
    cout<<"Los elementos ordenados son:";
    for (int i=1; i<=n; i++)
        cout<<A[i]<<" ";
    system("PAUSE");
    return 0;
}


