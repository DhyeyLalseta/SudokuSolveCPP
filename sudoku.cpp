#include <iostream>
#include <utility>
#define NONE make_pair(-1,-1)
#define SIZE 9
constexpr auto EMPTY = 0;
using namespace std;

bool validInRow(int grid[SIZE][SIZE], int row, int num)
{
	for (int i = 0; i<SIZE; i++)
	{
		if (grid[row][i] == num)
			return false;
	}
	return true;
}

bool validInCol(int grid[SIZE][SIZE], int col, int num)
{
	for (int i = 0; i < SIZE; i++)
	{
		if (grid[i][col] == num)
			return false;
	}
	return true;
}

bool validInSquare(int grid[SIZE][SIZE], int row, int col, int num)
{
	int row_min = row - row % 3;
	int col_min = col - col % 3;
	for (int i = row_min; i < row_min + 3; i++)
	{
		for (int j = col_min; j < col_min + 3; j++)
		{
			if (num == grid[i][j])
			{
				return false;
			}
		}
	}
	return true;
}

bool valid(int grid[SIZE][SIZE], int row, int col, int num)
{
	return validInRow(grid, row, num) && validInCol(grid, col, num) && validInSquare(grid, row, col, num);
}

pair<int, int> findEmpty(int grid[SIZE][SIZE])
{
	for (int row = 0; row < SIZE; row++)
	{
		for (int col = 0; col < SIZE; col++)
		{
			if (grid[row][col] == EMPTY)
			{
				return make_pair(row, col);
			}
		}
	}
	return NONE;
}

bool solveSudoku(int grid[SIZE][SIZE])
{
	pair<int, int> empty_location = findEmpty(grid);
	if (empty_location == NONE)
	{
		return true;
	}
	int row = empty_location.first;
	int col = empty_location.second;

	for (int trial = 1; trial <= SIZE; trial++)
	{
		if (valid(grid, row, col, trial))
		{
			grid[row][col] = trial;
			if (solveSudoku(grid))
				return true;
			else 
				grid[row][col] = EMPTY;
		}
	}
	return false;
}

void printGrid(int grid[SIZE][SIZE])
{
	for (int i = 0; i < SIZE; i++)
	{
		for (int j = 0; j < SIZE; j++)
		{
			cout << grid[i][j]<<" ";
		}
		cout << "\n";
	}
}

int main()
{
	int grid[SIZE][SIZE] = {{5, 3, 0, 0, 7, 0, 0, 0, 0},
		{6, 0, 0, 1, 9, 5, 0, 0, 0},
		{0, 9, 8, 0, 0, 0, 0, 6, 0},
		{8, 0, 0, 0, 6, 0, 0, 0, 3},
		{4, 0, 0, 8, 0, 3, 0, 0, 1},
		{7, 0, 0, 0, 2, 0, 0, 0, 6},
		{0, 6, 0, 0, 0, 0, 2, 8, 0},
		{0, 0, 0, 4, 1, 9, 0, 0, 5},
		{0, 0, 0, 0, 8, 0, 0, 7, 9}};
	if (solveSudoku(grid))
	{
		printGrid(grid);
		return 1;
	}
	else
	{
		cout << "Un-solvable";
		return -1;
	}
}
