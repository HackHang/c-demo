#include<iostream>
using namespace std;
#include"speechManager.h"

int main() {
	SpeechManager sm;

	while (true)
	{
		sm.show_Menu();
		int chose;
		cout << "PLease chose:" << endl;
		cin >> chose;
		switch (chose)
		{
		case 1:
			sm.startSpeech();
			break;
		case 2:
			break;
		case 3:
			break;
		case 0:
			sm.exitSystem();
		default:
			system("cls");
			break;
		}
	}
	

	system("pause");
	return 0;
}