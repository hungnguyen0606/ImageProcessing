#include "header.h"

int		getSelection(char* name, int nArr, const char** selectArr)
{
	int selection = -1;
	while (selection < 0 || selection > nArr)
	{
		cout << name << ": " << endl;
		cout << "\t0. Exit.\n";
		for (int i = 0; i < nArr; ++i)
			cout << "\t" << i + 1 << ". " << selectArr[i] << ".\n";
		cout << "Your selection: ";
		cin >> selection;
		wrtCrss;

		if (selection == 0)
			break;
	}
	return selection;
}




