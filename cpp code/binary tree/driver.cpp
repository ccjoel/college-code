//Just shut up and Drive!

#include <iostream>
using namespace std;
#define MAX_ARRAY 15
#include "BinTree.h"

int main()
{
    
   cout<<"Driver de prueba de las funciones LevelOrder, Similar, e Isomorphic";
   Arbol Claudio, Carmen; //Dos arboles para hacer pruebas
   
   int A[MAX_ARRAY] = {4,3,1,6,10,0,11,9,2,7,13,12,5,25,22};
   int B[MAX_ARRAY] = {4,3,1,6,10,0,11,9,2,7,13,12,5,25,22};
   
   for( int i = 0; i < MAX_ARRAY; i++){
      Claudio.Insertar(A[i]);
   }   
   for( int i = 0; i < MAX_ARRAY; i++){
      Carmen.Insertar(B[i]);
   }   
   
   cout<<endl<<endl;
   cout<<"El 1er arbol es:"<<endl;
   Claudio.Imprimir();
   Claudio.LevelOrder();   cout<<"<------------En level order";
   
   cout<<"\nEl segundo arbol es:"<<endl;
   Carmen.Imprimir();
   Carmen.LevelOrder(); cout<<"<------------En level order";
   cout<<endl<<endl;

   cout<<"Son ambos arboles similares?\n";
   Claudio.Similar(Carmen);
   
   cout<<"\n\nAhora se eliminara el elemento '11' del 2do arbol. El resultado es:\n";
   Carmen.Eliminar(11);
   Carmen.LevelOrder();    cout<<"<---------------En level order";
   cout<<"\n\nComparar visualmente con el primer arbol(ver que no son iguales)\n";
   Claudio.LevelOrder();    cout<<"<------------En level order\n";
   
   cout<<"\nNuevamente, son ambos arboles similares? (Llamada a la funcion)\n";
   Claudio.Similar(Carmen);
   
   cout<<"\n\nFuncion para verificar si ambos arboles son isomorficos\n";
   Claudio.Isomorphic(Carmen);
      
   cin.get();
   return 0;
}
