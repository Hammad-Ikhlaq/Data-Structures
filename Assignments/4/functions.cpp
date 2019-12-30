#include"header file.h"
#include<fstream>
#include<iostream>
using namespace std;
int matrix::getNumCols()
{
	cout << "Columns: " << col << endl;
	return col;
}
int matrix::getNumRows()
{
	cout << "Rows: " << rows << endl;
	return rows;
}
void matrix::printmatrix()
{

	for (int i = 0; i < rows; i++)
	{
		for (int j = 0; j < col; j++)
		{
			cout << arr[i][j] << " ";
		}
		cout << endl;
	}
}
matrix::matrix(char*filename)
{
	ifstream fin;
	fin.open(filename);
	if (fin.fail())
	{
		cout << "File can not be opened empty matrix created.\n";
		rows = 0;
		col = 0; 
		arr = nullptr;
	}
	else
	{
		fin >> rows;
		fin >> col;
		char buff[100];
		fin.getline(buff, 99);
		arr = new int*[rows];
		for (int i = 0; i < rows; i++)
		{
			arr[i] = new int[col];
		}
		for (int i = 0; i < rows; i++)
		{
			fin.getline(buff, 99);
			char*context = NULL;
			char*temp = strtok_s(buff, ",", &context);
			arr[i][0] = atoi(temp);
			for (int k = 1; temp != nullptr;)
			{
				temp = strtok_s(NULL, ",", &context);
				if (temp != NULL)
				{
					arr[i][k] = atoi(temp);
					k++;
				}
				else
					break;
			}
		}
	}
}
matrix::matrix(int r, int c)
{
	rows = r;
	col = c;
	arr = new int*[rows];
	for (int i = 0; i < rows; i++)
	{
		arr[i] = new int[col];
	}
	for (int i = 0; i < rows; i++)
	{
		for (int j = 0; j < col; j++)
		{
			arr[i][j] = rand();
		}
	}
}
matrix::matrix()
{
	rows = 0;
	col = 0;
	arr = nullptr;
}
matrix::~matrix()
{
	if (arr != nullptr)
	{
		for (int i = 0; i < rows; i++)
		{
			delete[] arr[i];
		}
		delete[] arr;
	}
}
matrix::matrix(const matrix &obj)
{
	rows = obj.rows;
	col = obj.col;
	arr = new int*[rows];
	for (int i = 0; i < rows; i++)
	{
		arr[i] = new int[col];
	}
	for (int i = 0; i < rows; i++)
	{
		for (int j = 0; j < col; j++)
		{
			arr[i][j] = obj.arr[i][j];
		}
	}
}
const matrix & matrix::operator=(const matrix &obj)
{
	if (arr != nullptr)
	{
		for (int i = 0; i < rows; i++)
		{
			delete[] arr[i];
		}
		delete[] arr;
	}
	rows = obj.rows;
	col = obj.col;
	arr = new int*[rows];
	for (int i = 0; i < rows; i++)
	{
		arr[i] = new int[col];
	}
	for (int i = 0; i < rows; i++)
	{
		for (int j = 0; j < col; j++)
		{
			arr[i][j] = obj.arr[i][j];
		}
	}
	return*this;
}
matrix matrix::operator+(const matrix &obj)
{
	matrix ans;
	if (obj.rows == rows && obj.col == col)
	{
		ans.rows = rows;
		ans.col = col;
		ans.arr = new int*[rows];
		for (int i = 0; i < rows; i++)
		{
			ans.arr[i] = new int[col];
		}
		for (int i = 0; i < rows; i++)
		{
			for (int j = 0; j < col; j++)
			{
				ans.arr[i][j] = arr[i][j] + obj.arr[i][j];
			}
		}
	}
	else
		cout << "These Matrixs are not compatible for addition.\n";
	return ans;
}

matrix matrix::operator-(const matrix &obj)
{
	{
		matrix ans;
		if (obj.rows == rows && obj.col == col)
		{
			ans.rows = rows;
			ans.col = col;
			ans.arr = new int*[rows];
			for (int i = 0; i < rows; i++)
			{
				ans.arr[i] = new int[col];
			}
			for (int i = 0; i < rows; i++)
			{
				for (int j = 0; j < col; j++)
				{
					ans.arr[i][j] = arr[i][j] - obj.arr[i][j];
				}
			}
		}
		else
			cout << "These Matrixs are not compatible for substraction.\n";
		return ans;
	}
}
bool matrix::operator==(const matrix &obj)
{
	if (rows != obj.rows || col != obj.col)
	{
		return false;
	}
	for (int i = 0; i < rows; i++)
	{
		for (int j = 0; j < col; j++)
		{
			if (arr[i][j] != obj.arr[i][j])
			{
				return false;
			}
		}
	}
	return true;
}
matrix matrix::operator - ()
{
	matrix ans;
	ans.rows = rows;
	ans.col = col;
	ans.arr = new int*[rows];
	for (int i = 0; i < rows; i++)
	{
		ans.arr[i] = new int[col];
	}
	for (int i = 0; i < rows; i++)
	{
		for (int j = 0; j < col; j++)
		{
			ans.arr[i][j] = arr[i][j]*-1 ;
		}
	}
	return ans;
}
const matrix& matrix::operator+=(const int &n)        //works with by reference only
{
	for (int i = 0; i < rows; i++)
	{
		for (int j = 0; j < col; j++)
		{
			arr[i][j] = n + arr[i][j];
		}
	}
	return *this;
}
const matrix& matrix::operator*=(const int & n)
{
	for (int i = 0; i < rows; i++)
	{
		for (int j = 0; j < col; j++)
		{
			arr[i][j] = n * arr[i][j];
		}
	}
	return *this;
}
matrix matrix::operator*(const matrix &obj)
{
	matrix answ;
	answ.rows = rows;
	answ.col = obj.col;
	if (rows == obj.col)
	{
		answ.arr = new int*[rows];
		for (int i = 0; i < rows; i++)
		{
			answ.arr[i] = new int[obj.col];
		}
		int ans = 0;
		for (int i = 0; i < rows; i++)
		{

			for (int j = 0; j < obj.col; j++)
			{

				for (int k = 0; k < col; k++)
				{

					ans = ans + (arr[i][k] * obj.arr[k][j]);
				}
				answ.arr[i][j] = ans;
				ans = 0;
			}

		}

		return answ;
	}
	else
		cout << "These matrixs are not compatible for multification.";
}
void matrix::transpose()
{
	for (int i = 0; i < col; i++)
	{
		for (int j = 0; j < rows; j++)
		{
			cout << arr[j][i] << " ";
		}
		cout << endl;
	}
}
