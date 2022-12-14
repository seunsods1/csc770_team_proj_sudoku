#include <iostream>
#include <queue>

using namespace std;

// declare function prototypes
void search_empty_cell(int arr[9][9], deque<int> prevI, deque<int> prevJ, deque<int> prevNum, deque<int> temp_prevI, deque<int> temp_prevJ, deque<int> temp_prevNum);
void sudoBackTrack(int arr[9][9], deque<int> prevI, deque<int> prevJ, deque<int> prevNum, deque<int> temp_prevI, deque<int> temp_prevJ, deque<int> temp_prevNum);

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

void search_empty_cell(int arr[9][9], deque<int> prevI, deque<int> prevJ, deque<int> prevNum, deque<int> temp_prevI, deque<int> temp_prevJ, deque<int> temp_prevNum)
{
	if (prevNum.back() == 0 && !prevNum.empty())
	{
		temp_prevNum.push_back(prevNum.back()); temp_prevI.push_back(prevI.back()); temp_prevJ.push_back(prevJ.back());
		prevNum.pop_back(); 
		prevI.pop_back(); 
		prevJ.pop_back();
		sudoBackTrack(arr, prevI, prevJ, prevNum, temp_prevI, temp_prevJ, temp_prevNum);
	}
	else if (prevNum.back() != 0 && !prevNum.empty())
	{
		temp_prevNum.push_back(prevNum.back()); temp_prevI.push_back(prevI.back()); temp_prevJ.push_back(prevJ.back());
		prevNum.pop_back(); prevI.pop_back(); prevJ.pop_back();
		search_empty_cell(arr, prevI, prevJ, prevNum, temp_prevI, temp_prevJ, temp_prevNum);
	}
	if (temp_prevNum.empty())
	{
		return;
	}
}

void sudoBackTrack(int arr[9][9], deque<int> prevI, deque<int> prevJ, deque<int> prevNum, deque<int> temp_prevI, deque<int> temp_prevJ, deque<int> temp_prevNum)
{
	if (prevNum.back() == 0)
	{
		search_empty_cell(arr, prevI, prevJ, prevNum, temp_prevI, temp_prevJ, temp_prevNum);
	}
	else
	{
		string solved_cell_flag = "false"; //flag to check if cell has been solved
		int i = prevI.back(); int j = prevJ.back(); int numSel = prevNum.back() + 1;
		while (!temp_prevNum.empty())
		{
			for (int num = numSel; num < 10; num++)
			{
				string foundinRo = foundinRow(arr, i, num);
				string foundinCol = foundinColumn(arr, j, num);
				string foundinC = foundinCell(i, j, arr, num);
		//		dispSudoku(arr);
				if (foundinRo == "false" && foundinCol == "false" && foundinC == "false")
				{
					// assign choosen number to empty cell
					arr[i][j] = num;
					prevNum.pop_back(), prevI.pop_back(), prevJ.pop_back();
					//populate queues with i,j and num values for filled cell
					prevI.push_back(i); prevJ.push_back(j);prevNum.push_back(num);
					i = temp_prevI.back(); j = temp_prevJ.back();
					temp_prevI.pop_back(); temp_prevJ.pop_back(); temp_prevNum.pop_back();
					prevI.push_back(i); prevJ.push_back(j); prevNum.push_back(num);
					solved_cell_flag = "true";
			//		dispSudoku(arr);
					break;
				}
			}
			if (solved_cell_flag == "false")
			{
				arr[i][j] = 0;
				prevNum.back() = 0;
				search_empty_cell(arr, prevI, prevJ, prevNum, temp_prevI, temp_prevJ, temp_prevNum);
			}
			solved_cell_flag = "false";
			numSel = 0;

		}
		search_empty_cell(arr, prevI, prevJ, prevNum, temp_prevI, temp_prevJ, temp_prevNum);
	}
}

void solveSudoku(int arr[9][9], deque<int> prevI, deque<int> prevJ, deque<int> prevNum, deque<int> temp_prevI, deque<int> temp_prevJ, deque<int> temp_prevNum)
{
	int cnt = 0;
	string cell_unsolved_flag = "false";
	string exit_loop = "false";
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
						cnt++;
						exit_loop = "true";
						//populate queues with i,j and num values for filled cell
						prevI.push_back(i);
						prevJ.push_back(j);
						prevNum.push_back(num);
						break;
					}
				}
				if (exit_loop == "false")
				{
					cnt++;
					//populate queues with i,j and 0 value for unfilled cell
					prevI.push_back(i);
					prevJ.push_back(j);
					prevNum.push_back(0);
					cell_unsolved_flag = "true"; //flag to check if all sudoku empty cells have been solved
					exit_loop = "false";
				}
				exit_loop = "false";
			}
		}
	}
	dispSudoku(arr);
	if (cell_unsolved_flag == "true")
	{
		// pass queues for i,j and num values of previous solved empty cells into SudoBackTrack() function to solve remaining unsolved cells
		search_empty_cell(arr, prevI, prevJ, prevNum, temp_prevI, temp_prevJ, temp_prevNum);

	}
}



int main(int argc, char** argv)
{
	deque<int> prevI; //this deque data structure keeps track of the i values of all the empty cells being filled
	deque<int> prevJ; //this deque data structure keeps track of the j values of all the empty cells being filled
	deque<int> prevNum; //this deque data structure keeps track of the number selection of all the empty cells being filled
	deque<int> temp_prevI; //temporary deque data structure to store data from prevI
	deque<int> temp_prevJ; //temporary deque data structure to store data from prevJ
	deque<int> temp_prevNum; //temporary deque data structure to store data from prevNum

	//Very Easy puzzle with 20 empty cells
	int arr[9][9] = {
		{5, 3, 0, 0, 7, 0, 0, 1, 2},
		{6, 7, 0, 0, 9, 5, 3, 4, 8},
		{1, 9, 8, 3, 4, 0, 0, 6, 7},
		{8, 5, 9, 7, 6, 0, 4, 2, 3},
		{4, 2, 0, 8, 5, 3, 0, 9, 1},
		{7, 1, 0, 9, 2, 4, 0, 5, 6},
		{9, 6, 0, 0, 0, 7, 2, 8, 4},
		{2, 8, 7, 4, 0, 0, 0, 0, 5},
		{3, 4, 5, 2, 8, 6, 1, 7, 9}
	};
	
	//Medium puzzle with 43 empty cells
	int arr2[9][9] = {
		{3,0,0,0,2,9,5,0,1},
		{1,0,8,3,0,0,4,2,9},
		{0,0,6,5,0,0,3,6,0},
		{0,0,0,0,7,6,0,0,0},
		{0,0,0,1,3,8,0,0,7},
		{8,0,0,9,0,0,6,0,0},
		{4,6,0,0,5,0,8,0,2},
		{0,8,0,6,0,3,0,4,0},
		{7,3,5,4,8,0,0,9,0}
	};

	

	cout << "-------------------------Begining of Sudoku Implemented Sequentially-----------------------------------------" << endl;
	cout << endl;
	cout << "------------------Start of Easy sudoku puzzle---------------------------------------------" << endl;
	cout << "------------------Unsolved Easy sudoku puzzle----------------------" << endl;
	dispSudoku(arr);
	cout << "------------------Solved Easy sudoku puzzle------------------------" << endl;
	solveSudoku(arr, prevI, prevJ, prevNum, temp_prevI, temp_prevJ, temp_prevNum);
	cout << "------------------End of Easy sudoku puzzle-----------------------------------------------" << endl;
	cout << endl;
	cout << "------------------Start of Medium sudoku puzzle-------------------------------------------" << endl;
	cout << "------------------Unsolved Medium sudoku puzzle----------------------" << endl;
	dispSudoku(arr2);
	cout << "------------------Solved Medium sudoku puzzle------------------------" << endl;
	solveSudoku(arr2, prevI, prevJ, prevNum, temp_prevI, temp_prevJ, temp_prevNum);
	cout << "------------------End of Medium sudoku puzzle---------------------------------------------" << endl;
	cout << endl;
	cout << "-------------------------End of Sudoku Implemented Sequentially-----------------------------------------------" << endl;
	return 0;
}