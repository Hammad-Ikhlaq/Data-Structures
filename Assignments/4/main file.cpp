#include"header file.h"
#include<iostream>
#include<fstream>
#include<string>

using namespace std;

int main()
{
	matrix m1;//empty 0x0 matrix
	matrix m2("mat1.txt"), m3("mat2.txt");//read from files


	m2.getNumRows();
	m2.getNumCols();
	cout << "matrix m2 \n";
	m2.printmatrix();
	
	cout << endl;
	

	cout << "matrix m3 \n";
	m3.printmatrix();
	cout << endl;

	cout << endl;
	matrix m5(5, 7);//create a 5x7 matrix with random values
	cout << "random number matrix generated assuming compatability \n";
	m5.printmatrix();
	cout << endl;

	m1 = m2 + m3;//add matrices
	cout << " m1 matrix (addition is printed of two matrices)\n";
	m1.printmatrix();
	cout << endl;

	matrix m4 = m2 - m3;//subtract matrices
	cout << " m4 matrix (substraction is printed of two matrices) \n";
	m4.printmatrix();
	cout << endl;

	if (m1 == m4)
	{
		cout << "m1 and m4 are equal matrices";
	}


	m5 = m2*m3;//matrix multiplication (assume compatability)
	cout << "m5 matrix (multiplication is printed of two matrices assuming compatability) \n";
	m5.printmatrix();
	cout << endl;

	cout << "transpose is printed of m5 matrix \n";
	m5.transpose();//convert nxm to mxn matrix
	cout << endl;
	cout << "matrix m2 add by 5 \n";
	m2 += 5;//adds 5 to all elements of m2
	m2.printmatrix();
	cout << endl;

	cout << "matrix m2 multiplied by 5 \n";
	m2 *= 5;//multiplies 5 to all elements of m2
	m2.printmatrix();
	cout << endl;

	m2 = -m2; cout<<"negates all elements of m2"<<endl;
	m2.printmatrix();
	cout << endl;

	system("pause>nul");
	return 0;
}