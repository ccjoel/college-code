#include <iostream>
#include <fstream>
#include <cmath>
#include <string>
#include <algorithm>
using namespace std;

int Det2x2(int **matrix);
void matrixToConsole(int **matrix, int n);
int Determinant(int **matrix, int n);

int main(){
    
    ifstream entrada("matrix.txt");
	if(!entrada.is_open())
		return -1;
    
	int n=0;
    string line;
    getline(entrada, line);
    int spaces = count(line.begin(), line.end(), ' ');
    n = spaces + 1;

	cout<<n<<"x"<<n<<" square matrix:"<<endl<<endl;

	entrada.close();
    entrada.open("matrix.txt");

	int **matrix;
	matrix = new int *[n];
    for (int i=0; i<n; i++){
      matrix[i] = new int [n];
      for (int j=0; j<n;j++)
         entrada>>matrix[i][j];
    }

	matrixToConsole(matrix,n);
	cout<<endl;

	int determinant = Determinant(matrix, n);
	cout<<"The determinant is "<<determinant<<endl;
	if(determinant != 0)
		cout<<"The matrix is invertible"<<endl<<endl;
	else
		cout<<"The matrix is not invertible"<<endl<<endl;
	
	cin.get();
    return 0;
}
    

int Det2x2(int **matrix){
    return (matrix[0][0] * matrix[1][1]) - (matrix[0][1] * matrix[1][0]);
}

void matrixToConsole(int **matrix, int n){
	for(int i = 0; i < n; i++){
		for (int j = 0; j < n ; j++)
			cout<<matrix[i][j]<<" ";
		cout<<endl;
	}
}

int Determinant(int **matrix, int n){
	double determinant;
	if(n == 2)
		return Det2x2(matrix);
	else{
		int i,j,k,l;
		determinant = 0;
		int **partition;
		for(k = 0; k < n; k++){
			partition = new int *[n-1];
			for(i = 0; i < n-1; i++)
				partition[i] = new int [n-1];
			for(i = 1; i < n; i ++){
				l = 0;
				for(j = 0; j < n; j++){
					if(j == k) continue;
					partition[i-1][l] = matrix[i][j];
					l++;
				}
			}
			determinant += pow(-1,(double)k + 2 ) * matrix[0][k] * Determinant(partition, n-1);
		}
	}
	return determinant;
}