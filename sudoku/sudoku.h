#pragma once
//sudoku.h
//�������������࣬����ʾ����������
#ifndef BITSE_SUDUKU
#define BITSE_SUDUKU
#include <sal.h>
#include <iostream>
using namespace std;

//�Ϸ��ĺ�������(0��8)
#define _pos_range_ _In_range_(0, 8)
//����Ϸ���ֵ(0-9, ����λ0)
#define _val_range_ _In_range_(0, 9)
//����Ϸ��Ĵ�(1-9, ������λ0)
#define _ans_range_ _In_range_(1, 9)

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
	Sudoku();

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
	///	�жϵ�ǰ���������Ƿ�Ϸ�
	/// </summary>
	/// <param name="slotOk">ָʾ��λ(����0��λ��)�Ƿ���Ϊ�Ϸ���Ϊtrue��ʾ��Ϊ�Ϸ���</param>
	bool IsValid(bool slotOk);

	/// <summary>
	///	�ݹ�س��Խ�һ��������������ʾ��ǰӦ���ȿ��ǵ�λ�á����Ǹ�λ�ò��ǿ�λ������ѡһ����λ����
	/// </summary>
	/// <param name="line">��ǰ��Ҫ��λ���У���0��ʼ</param>
	/// <param name="col">��ǰ��Ҫ��λ���У���0��ʼ</param>
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