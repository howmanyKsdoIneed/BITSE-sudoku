#include "module-create.h"
#include <string>
#include <vector>
using namespace std;

/// <summary>
/// �վ�����ģ�鵥Ԫ���Ե�����ģ��
/// ���ļ��ж���id����һ���첢����
/// </summary>
int main(int argc, char** argv)
{
	string fnameIDs = "create_testcase.txt";
	for (int i = 1; i < argc; i++)
	{
		if (argv[i][0] != '-')
			fnameIDs = argv[i];
	}

	ifstream fIDs(fnameIDs);
	if (!fIDs.is_open())
	{
		cerr << "δ�ܴ򿪲��������ļ� " << fnameIDs << endl;
		return -1;
	}

	cout << "���ڹ��������վ�..." << endl;
	vector<Sudoku> vEndgames;
	vector<int> vIDs;
	int iEndgameCnt = 0;
	while (true)
	{
		int id;
		fIDs >> id;
		if (fIDs.eof())
			break;
		if (id > 2903039)
		{
			cerr << "ID " << id << " ̫�󣬲�������" << endl;
			continue;
		}
		vEndgames.push_back(Sudoku(id, 3));
		vIDs.push_back(id);
		if (vEndgames[iEndgameCnt].At(0, 0) != 3)
		{
			cerr << "�վ�#" << id << "�����Ͻ����ֲ���3����ֹ����" << endl;
			cerr << "���ɵ��վ֣�" << endl << vEndgames[iEndgameCnt] << endl;
			return 0;
		}
		if (!vEndgames[iEndgameCnt].IsValid(false))
		{
			cerr << "�վ�#" << id << "���Ϸ�����ֹ����" << endl;
			cerr << "���ɵ��վ֣�" << endl << vEndgames[iEndgameCnt] << endl;
			return 0;
		}
		iEndgameCnt++;
	}
	cout << "������" << iEndgameCnt << "���վ֡�" << endl;
	fIDs.close();

	cout << "���ڲ���..." << endl;
	for (int first = 0; first < iEndgameCnt; first++)
	{
		bool correct = true;
		for (int second = first + 1; second < iEndgameCnt; second++)
		{
			if (vEndgames[first] == vEndgames[second])
			{
				/*if (vIDs[first] == vIDs[second])
					continue;*/
				cerr << "�վ�#" << vIDs[first] << 
					"���վ�#" << vIDs[second] << "��ͬ" << endl;
				cerr << "��ͻ���վ֣�" << endl << vEndgames[first] << endl;
				correct = false;
			}
		}
		/*if (correct)
			cout << "�վ�#" << vIDs[first] << "��ȷ" << endl;*/
	}
	vEndgames.clear();
}
