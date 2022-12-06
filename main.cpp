#include <iostream>
#include <vector>

using namespace std;


string foundinRow(int arr[9][9], int i, int num)
{
	for (int j = 0; j < 9; j++)
	{
		if (num == arr[i][j])
		{
			return "true";
		}
		else
		{
			continue;
		}
	}
	return "false";
	
}

string foundinColumn(int arr[9][9], int j, int num)
{
	for (int i = 0; i < 9; i++)
	{
		if (num == arr[i][j])
		{
			return "true";
		}
		else
		{
			continue;
		}
	}
	return "false";
}

string foundinCell(int i, int j, int arr[9][9], int num)
{
	int cell_or_i = int(i / 3) * 3;
	int cell_or_j = int(j / 3) * 3;

	for (int i = cell_or_i; i < (cell_or_i + 3); i++)
	{
		for (int j = cell_or_j; j < (cell_or_j + 3); j++)
		{
			if (arr[i][j] == num)
			{
				return "true";
			}
			else
			{
				continue;
			}
		}
	}
	return "false";
}



void dispSudoku(int arr[9][9])
{
	cout << endl;
	cout << endl;
	for (int i = 0; i < 9; i++)
	{
		cout << "                  ";
		for (int j = 0; j < 9; j++)
		{
			if (arr[i][j] == 0)
			{
				cout << "." << "   ";
			}
			else
			{
				cout << arr[i][j] << "   ";
			}
		}
		cout << endl;
		cout << endl;
	}
		

}

void solveSudoku(int arr[9][9])
{
	for (int i = 0; i < 9; i++)
	{
		for (int j = 0; j < 9; j++)
		{
			if (arr[i][j] != 0)
			{
				continue;
			}
			else
			{
				for (int num = 1; num < 10; num++)
				{
					string foundinRo = foundinRow(arr, i,num);
					string foundinCol = foundinColumn(arr, j,num);
					string foundinC = foundinCell(i, j, arr, num);
					if (foundinRo == "false" && foundinCol == "false" && foundinC == "false")
					{
						arr[i][j] = num;
						break;
					}
				}
			}
		}
	}
}



int main(int argc, char** argv)
{
	//const int arr_size = 9;
	int arr[9][9] = {
		{5,3,0,0,7,0,0,0,0},
		{6,0,0,1,9,5,0,0,0},
		{0,9,8,0,0,0,0,6,0},
		{8,0,0,0,6,0,0,0,3},
		{4,0,0,8,0,3,0,0,1},
		{7,0,0,0,2,0,0,0,6},
		{0,6,0,0,0,0,2,8,0},
		{0,0,0,4,1,9,0,0,5},
		{0,0,0,0,8,0,0,7,9}
	};
//	cout << arr[6][7] << endl;
	cout << "------------------Start of incomplete sudoku puzzle-----------------------------" << endl;
	dispSudoku(arr);
	cout << "------------------End of incomplete sudoku puzzle-------------------------------" << endl;
	solveSudoku(arr);
	cout << "------------------Start of solved sudoku puzzle---------------------------------" << endl;
	dispSudoku(arr);
	cout << "------------------End of solved sudoku puzzle-----------------------------------" << endl;
	return 0;
}