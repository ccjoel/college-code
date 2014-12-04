#include <iostream>
#include <fstream>
#include <cmath>
#include <string>
using namespace std;

#define START 7

int main()
{

	int limite, total_generados=3;
	unsigned long prime, numero, END;
	bool is_prime;

	cout<<"Generador de numeros primos.\nHasta cual numero quieres generar?(min hasta 8):_";
	cin>>END;
	cout<<"Generando numeros primos..."<<endl;
	ifstream entrada;
	ofstream salida;
	salida.open("Primos generados.txt"); salida<<2<<" "<<3<<" "<<5; salida.close();
	
	for( numero = START; numero < END; numero++){	
		
		limite = (unsigned long) sqrt((double)numero);
		if( numero % limite != 0 ){
			is_prime = true;
		
			entrada.open("Primos generados.txt");
			entrada >> prime;
			while( (!entrada.eof()) && (prime < limite) && (is_prime) ){
				if( (numero % prime) == 0 )
					is_prime = false;
				entrada>> prime;
			}
			entrada.close();
			
			if( is_prime ){
				salida.open("Primos generados.txt", ios::app);
				salida<<" "<<numero;
				total_generados++;
				if(total_generados % 10 == 0)
					salida<<endl;
				salida.close();
			}
		}
	}
	salida.open("Primos generados.txt", ios::app);
	salida<<endl<<"Total generados: "<<total_generados<<endl;
	salida.close();
	cout<<"Total generados: "<<total_generados<<endl;
	system("pause");
	return 0;
}
