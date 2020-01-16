#include "module-solve.h"
#include <ctime>
using namespace std;

int main()
{
	clock_t cBegin, cEnd;
	FILE* fPuzzle = nullptr;
	errno_t err = fopen_s(&fPuzzle, "solve_testcase.txt", "r");
	if (err)
	{
		cerr << "错误：无法打开文件" << endl;
		return -1;
	}

	Sudoku inTemp;
	Solver solver;
	inTemp.Read(fPuzzle);
	solver.Reload(inTemp);
	cout << "Puzzle:" << endl;
	cout << solver << endl;
	cout << "Starting solving..." << endl;
	cBegin = clock();
	bool solved = solver.Solve();
	cEnd = clock();
	cout << "Time elapsed: " << (cEnd * 1.0 - cBegin * 1.0) / CLOCKS_PER_SEC << " sec" << endl;
	cout << "Status:" << endl << solver;
	cout << endl;
	if (solved)
		cout << "Solved, ";
	else
		cout << "Not solved, ";
	if (solver.IsValid(true))
		cout << "board valid";
	else
		cout << "board invalid";
	cout << endl;
	return 0;
}
