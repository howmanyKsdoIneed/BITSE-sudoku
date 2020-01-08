#include "module-solve.h"
#include <ctime>
using namespace std;

int main()
{
	clock_t cBegin, cEnd;
	ifstream fPuzzle("solve_testcase.txt");
	if (!fPuzzle.is_open())
	{
		cerr << "Could not open input file" << endl;
		return -1;
	}

	Sudoku inTemp;
	Solver solver;
	fPuzzle >> inTemp;
	solver.Reload(inTemp);
	cout << "Puzzle:" << endl;
	cout << solver << endl;
	cout << "Starting solving..." << endl;
	cBegin = clock();
	bool solved = solver.Solve();
	cEnd = clock();
	cout << "Time elapsed: " << (cEnd - cBegin) / CLOCKS_PER_SEC << " sec" << endl;
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
