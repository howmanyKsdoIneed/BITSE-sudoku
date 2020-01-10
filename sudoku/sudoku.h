#pragma once
//sudoku.h
//定义数独棋盘类，来表示数独的棋盘
#ifndef BITSE_SUDUKU
#define BITSE_SUDUKU
#include <sal.h>
#include <iostream>
#include "defines.h"
using namespace std;

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
	Sudoku()noexcept;

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
	///	用指定的编码和左上角数字生成数独终局
	/// </summary>
	/// <param name="id">数独的编码值</param>
	/// <param name="upLeft">数独棋盘左上角的数字</param>
	void Build(
		_In_range_(0, 2903039) int id,
		_ans_range_ int upLeft
	);

	/// <summary>
	///	判断当前数独棋盘是否合法
	/// </summary>
	/// <param name="slotOk">指示空位(填入0的位置)是否视为合法。为true表示视为合法。</param>
	bool IsValid(bool slotOk);
	
	inline int& At(_pos_range_ int line, _pos_range_ int col);

	Sudoku& operator=(const Sudoku& src);
	bool operator==(const Sudoku& another);

	friend ostream& operator<<(ostream& os, const Sudoku& sudoku);
	friend istream& operator>>(istream& s, Sudoku& sudoku);
};

ostream& operator<<(ostream& os, const Sudoku& sudoku);
istream& operator>>(istream& s, Sudoku& sudoku);

#endif