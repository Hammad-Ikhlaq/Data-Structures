class matrix
{
private:
	int rows;
	int col;
	int**arr;
public:
	void printmatrix();
	matrix();
	~matrix();
	matrix(const matrix&);
	int getNumRows();
	int getNumCols();
	matrix(char*);
	matrix(int, int);
	const matrix& operator =(const matrix&);
	matrix operator +(const matrix&);
	matrix operator -(const matrix&);
	bool operator ==(const matrix&);
	matrix operator - ();
	const matrix& operator +=(const int&);
	const matrix& operator *=(const int&);
	matrix operator *(const matrix&);
	void transpose();
};
