#pragma once
//sudoku.h
//�������������࣬����ʾ����������
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
	///	��������������
	/// </summary>
	/// <param name="lineA">Ҫ������һ��</param>
	/// <param name="lineB">Ҫ������һ��</param>
	void SwapLine(_pos_range_ int lineA, _pos_range_ int lineB);

public:
	/// <summary>
	///	��0��ʼ��һ���µ���������
	/// </summary>
	Sudoku()noexcept;

	/// <summary>
	///	��ָ���ı�������Ͻ����ֳ�ʼ��һ���µ��������̣��൱���վ�����ģ��
	/// </summary>
	/// <param name="id">�����ı���ֵ</param>
	/// <param name="upLeft">�����������Ͻǵ�����</param>
	Sudoku(
		_In_range_(0, 2903039) int id,
		_ans_range_ int upLeft
	);


	/// <summary>
	///	��ָ���ı�������Ͻ��������������վ�
	/// </summary>
	/// <param name="id">�����ı���ֵ</param>
	/// <param name="upLeft">�����������Ͻǵ�����</param>
	void Build(
		_In_range_(0, 2903039) int id,
		_ans_range_ int upLeft
	);

	/// <summary>
	///	�жϵ�ǰ���������Ƿ�Ϸ�
	/// </summary>
	/// <param name="slotOk">ָʾ��λ(����0��λ��)�Ƿ���Ϊ�Ϸ���Ϊtrue��ʾ��Ϊ�Ϸ���</param>
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