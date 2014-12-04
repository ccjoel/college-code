//BinTree.cpp
#include "BinTree.h"
#include <queue>
using namespace std;
//Ver las funciones escritas por mi mas abajo
Arbol::Arbol()
{
  miArbol = NULL;
}

Arbol::Arbol(ElementType item)
{
	Nodeptr p = new Nodo;
	p->info = item;
	p->left = NULL;
	p->right = NULL;
	miArbol = p;
}

bool Arbol::Empty() const
{
	return (miArbol == NULL);
}

void Arbol::Insertar(ElementType item)
{
	Nodeptr nuevo = new Nodo;
	nuevo ->info = item;
	nuevo ->left = nuevo ->right = NULL;
	if (Empty())
	{	
		miArbol = nuevo;
		return;
	}
	Nodeptr p = miArbol, padre = NULL;
	while (p != NULL)
	{
		padre = p;
		if (item < p->info)
			p = p->left;
		else
			p = p->right;
	}
	if (item < padre ->info)
		padre -> left = nuevo;
	else
		padre ->right = nuevo;
}

void Arbol::Imprimir()
{
	Nodeptr p = miArbol;
	enorden(p);
	cout<<endl;
}

void Arbol::enorden(Nodeptr p) 
{
	if (p != NULL)
	{
		enorden(p ->left);
		cout<<p->info<<" ";
		enorden(p->right);
	}
}

void Arbol::Buscar(ElementType item, Nodeptr & p, Nodeptr & padre)
{
	p = miArbol;
	padre = NULL;
	while (p!=NULL)
		if (item == p->info)
			return;
		else
		{
			padre = p;
			if (item < p->info)
				p = p->left;
			else
				p = p->right;
		}
	return;
}

void Arbol::Eliminar(ElementType item)
{
	Nodeptr p, padre, sus, padresus;
	Buscar(item, p, padre);
	if (p == NULL) 
	{
		cout<<item<<"No esta en la lista."<<endl;
		return;
	}
	if (p->left !=NULL && p->right !=NULL)
	{
		padresus = p;
		sus = p-> right;
		while (sus -> left != NULL)
		{
			padresus = sus;
			sus = sus -> left;
		}
		p -> info = sus -> info;
		p = sus;
		padre = padresus;
	}
	if (padre == NULL)
		if (p->left == NULL)
			miArbol = miArbol -> right;
		else
			miArbol = miArbol -> left;
	else
		if (p->left == NULL && p->right == NULL)
			if (p == padre ->left)
				padre->left = NULL;
			else 
				padre -> right = NULL;
		else
			if (padre -> left == p && p->left != NULL)
				padre -> left = p -> left;
			else
				if (padre ->left == p)
					padre -> left = p -> right;
				else 
					if (p ->left != NULL)
						padre -> right = p -> left;
					else
						padre -> right = p -> right;

          delete p;
}

//Comienzan funciones para ccom5050

void Arbol::LevelOrder()
{
   queue<Nodeptr> queue1;
   Nodeptr p, q;
   p = miArbol;
   if ( p != 0 )
      queue1.push( p );
   while ( !queue1.empty() )
   {
      q = queue1.front();
      queue1.pop();
      cout << q->info << ' ';
      if ( q->left != 0 )
         queue1.push( q->left );
      if ( q->right != 0 )
         queue1.push( q->right );
   }
}

void Arbol::getRoot(Nodeptr & p)
{
    p = miArbol;
}

bool Arbol::SimilarHelper(Nodeptr & p, Nodeptr & q)   //Recursivo
{
   if(p == NULL && q == NULL)
      return true;
   else if( p != NULL && q != NULL)
   {
        return
        (
           p->info == q->info
           &&
           SimilarHelper(p->left, q->left)
           &&
           SimilarHelper(p->right, q->right)
        );
    }
    else
       return false;
}

void Arbol::Similar(Arbol & unArbol)
{
   Nodeptr p=miArbol;
   Nodeptr q;
   unArbol.getRoot(q);
   if ( SimilarHelper(p,q) )
      cout<< "Los arboles son similares";
   else
      cout<< "Los arboles no son similares";
}

bool Arbol::IsomorphicHelper(Nodeptr & p, Nodeptr & q)     //Amo la recursion :)
{
     if(p == NULL && q ==NULL)
        return true;
     if(p->left == q->right && p->right == q->left)
     {
        IsomorphicHelper(p->left, q->right);
        IsomorphicHelper(p->right, q->left);
     }
     else 
        return false;
}

void Arbol::Isomorphic(Arbol & unArbol)
{
     Nodeptr p = miArbol;
     Nodeptr q;
     unArbol.getRoot(q);
     
     if(p==NULL || q == NULL)
     {
        cout<<"No isomorficos";
        return;
     }
     
     if( IsomorphicHelper(p,q) )
       cout<<"Son isomorficos";
     else
       cout<<"No isomorficos";

}
