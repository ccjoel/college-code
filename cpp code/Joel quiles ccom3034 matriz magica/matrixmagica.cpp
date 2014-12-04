/******************************************************************************
* Name: Matrixmajica                                                          *
* Programmer:Joel M. Quiles Baker                                             *
* Date: 15 de febreo 2008                                                     *
* Description:Averigua si el file contiene una matriz magica.                 *
******************************************************************************/
#include <iostream>
#include <fstream>
using namespace std;

//Func. Prototypes
void matrizMag(int **, int);

//Inicia Main
int main()
{ 
  int **mPtr, n, i, j;
  ifstream entrada("entrada.txt");
  entrada>> n;
  mPtr = new int *[n];
  for (i=0; i<n; i++){
      mPtr[i] = new int [n];
      for (j=0; j<n;j++)
         entrada>>mPtr[i][j];
  }
  matrizMag(mPtr, n);   
  return 0;
}

//Function Definitions
//matrizMag: verifica si la matriz es magica y lo devuelve a salida.txt
void matrizMag(int **mPtr,int n) 
{ 
   int rowsum[n],colsum[n],
   sumdright = 0, sumdleft = 0,
   fila = 0, column = 0,
   diar = 0, dial = n-1; 
   
   //matriz para suma de columnas 
   for( int j=0; j<n; j++ ){
      colsum[j]=0;
      for( int i=0; i<n; i++ )
         colsum[j] += mPtr[j][i];  
   } 
   //matriz para suma de filas
   for ( int i=0; i<n; i++ ){
      rowsum[i]=0;
      for ( int j=0; j<n; j++ )
         rowsum[i] += mPtr[j][i];
   }
   //para comparar las filas/hileras
   for ( int i=0; i<n-1; i++ ){
      if ( rowsum [i] != rowsum [i+1] )
         fila = 1;
      else
         fila = 0;
   }
   // comparacion de columnas
   for ( int j=0; j<n-1; j++ ){
      if ( colsum [j] != colsum [j+1] )
         column = 2;
      else
         column = 0;
   }
   // determinacion de la suma de las diagonales
   for ( int i=0; i<n; i++,diar++ )
      sumdright += mPtr[diar][i];
   for ( int i = 0; i<n; i++,dial-- )
      sumdleft += mPtr[dial][i];
      
   ofstream salida ("salida.txt");
   if ( fila == column ){
      if ( (sumdright == sumdleft) && (sumdright == colsum[0]) && (sumdright == rowsum[0]) )
         salida << "La matrix es magica.\n";
      else
         salida << "La matriz no es magica.\n";
   }
   else
         salida << "La matriz no es magica.\n";
}
