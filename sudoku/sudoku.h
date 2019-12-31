#pragma once
//sudoku.h
//定义数独棋盘类，来表示数独的棋盘
#ifndef BITSE_SUDUKU
#define BITSE_SUDUKU
#include <sal.h>
#include <iostream>
using namespace std;

//合法的横纵坐标(0到8)
#define _pos_range_ _In_range_(0, 8)
//格里合法的值(0-9, 含空位0)
#define _val_range_ _In_range_(0, 9)
//格里合法的答案(1-9, 不含空位0)
#define _ans_range_ _In_range_(1, 9)

class Sudoku
{
private:
	int board[9][9];

	/// <summary>
	///	交换棋盘上两行
	/// </summary>
	/// <param name="lineA">要交换的一行</param>
	/// <param name="lineB">要交换的一行</param>
	void SwapLine(_pos_range_ int lineA, _pos_range_ int lineB);

public:
	/// <summary>
	///	用0初始化一个新的数独棋盘
	/// </summary>
	Sudoku();

	/// <summary>
	///	用指定的编码和左上角数字初始化一个新的数独棋盘，相当于终局生成模块
	/// </summary>
	/// <param name="id">数独的编码值</param>
	/// <param name="upLeft">数独棋盘左上角的数字</param>
	Sudoku(
		_In_range_(0, 2903039) int id,
		_ans_range_ int upLeft
	);

	/// <summary>
	///	判断当前数独棋盘是否合法
	/// </summary>
	/// <param name="slotOk">指示空位(填入0的位置)是否视为合法。为true表示视为合法。</param>
	bool IsValid(bool slotOk);

	/// <summary>
	///	递归地尝试解一个数独。参数表示当前应首先考虑的位置。若那个位置不是空位，则任选一个空位处理。
	/// </summary>
	/// <param name="line">当前首要空位的行，从0开始</param>
	/// <param name="col">当前首要空位的列，从0开始</param>
	bool Solve(
		_pos_range_ int line = 0,
		_pos_range_ int col = 0
	);

	inline int& At(_pos_range_ int line, _pos_range_ int col);

	friend ostream& operator<<(ostream& os, const Sudoku& sudoku);
	friend istream& operator>>(istream& s, Sudoku& sudoku);
};

ostream& operator<<(ostream& os, const Sudoku& sudoku);
istream& operator>>(istream& s, Sudoku& sudoku);

#endif