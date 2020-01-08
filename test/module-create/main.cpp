#include "module-create.h"
#include <string>
#include <vector>
using namespace std;

/// <summary>
/// 终局生成模块单元测试的主调模块
/// 从文件中读入id，逐一构造并查重
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
		cerr << "未能打开测试用例文件 " << fnameIDs << endl;
		return -1;
	}

	cout << "正在构造数独终局..." << endl;
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
			cerr << "ID " << id << " 太大，不予生成" << endl;
			continue;
		}
		vEndgames.push_back(Sudoku(id, 3));
		vIDs.push_back(id);
		if (vEndgames[iEndgameCnt].At(0, 0) != 3)
		{
			cerr << "终局#" << id << "的左上角数字不是3，中止进程" << endl;
			cerr << "生成的终局：" << endl << vEndgames[iEndgameCnt] << endl;
			return 0;
		}
		if (!vEndgames[iEndgameCnt].IsValid(false))
		{
			cerr << "终局#" << id << "不合法，中止进程" << endl;
			cerr << "生成的终局：" << endl << vEndgames[iEndgameCnt] << endl;
			return 0;
		}
		iEndgameCnt++;
	}
	cout << "已生成" << iEndgameCnt << "个终局。" << endl;
	fIDs.close();

	cout << "正在查重..." << endl;
	for (int first = 0; first < iEndgameCnt; first++)
	{
		bool correct = true;
		for (int second = first + 1; second < iEndgameCnt; second++)
		{
			if (vEndgames[first] == vEndgames[second])
			{
				/*if (vIDs[first] == vIDs[second])
					continue;*/
				cerr << "终局#" << vIDs[first] << 
					"和终局#" << vIDs[second] << "相同" << endl;
				cerr << "冲突的终局：" << endl << vEndgames[first] << endl;
				correct = false;
			}
		}
		/*if (correct)
			cout << "终局#" << vIDs[first] << "正确" << endl;*/
	}
	vEndgames.clear();
}
