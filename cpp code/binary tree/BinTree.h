//BinTree.h
#include<iostream>
using namespace std;
typedef int ElementType;

class Arbol
{
	private:
		class Nodo   // the node class to use
		{
		   public:
		          ElementType info;
		           Nodo * left;
	  	           Nodo * right;
		};
	    typedef Nodo * Nodeptr;
		void enorden(Nodeptr);  //funcion que ayuda a Imprimir en orden. Para imprimir en pre/post orden, cambiar esta funcion.

    public:
		Arbol();
		Arbol(ElementType);
		//funciones regulares de la clase arbol de ccom3034
		bool Empty() const;
		void Insertar(ElementType);
		void Eliminar(ElementType);
		void Imprimir();
		void Buscar(ElementType, Nodeptr &, Nodeptr &);
		//funciones para ccom5050 por mi
		void getRoot(Nodeptr & q);
        void LevelOrder();
		bool SimilarHelper(Nodeptr & p, Nodeptr & q);
		void Similar(Arbol & unArbol);
		bool IsomorphicHelper(Nodeptr & p, Nodeptr & q);
        void Isomorphic(Arbol & unArbol);

	private:
		Nodo * miArbol;    //el root del arbol
};
