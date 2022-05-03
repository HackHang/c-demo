#include "speechManager.h"

SpeechManager::SpeechManager() {
	this->initSpeech();
	this->createSpeaker();
};

//Menu
void SpeechManager::show_Menu() {
	cout<< "**********" << endl;
	cout << "1.start" << endl;
	cout << "2.record" << endl;
	cout << "3.clear record" << endl;
	cout << "0.exit" << endl;
};
//exit
void SpeechManager::exitSystem() {
	cout << "See you again!" << endl;
	system("pause");
	exit(0);
};

//init property
void SpeechManager::initSpeech() {
	this->v1.clear();
	this->v2.clear();
	this->vVictory.clear();
	this->m_map.clear();
	this->m_Index = 1;
};
//creat spearker
void SpeechManager::createSpeaker() {
	string nameseed = "ABCDEFGHIJKL";
	for (int i = 0; i < nameseed.size(); i++) {
		string name = "ѡ��";
		name += nameseed[i];
		Spearker sp;
		sp.m_name = name;
		for (int j = 0; j < sizeof(sp.m_score)/sizeof(sp.m_score[0]); j++) {
			sp.m_score[j] = 0;
		}
		int key = i + 10001;
		v1.push_back(key);
		m_map.insert(make_pair(key,sp));
		
	}
	//print
	/*
	for (map<int, Spearker>::iterator it = m_map.begin(); it != m_map.end(); it++) {
		cout << (*it).first << "   " << ((*it).second).m_name << " �÷�1��"<< ((*it).second).m_score[0] << " �÷�2��" << ((*it).second).m_score[1] << endl;
	}
	*/

};

//start ��ǩ
void SpeechManager::chouQian() {

	if (this->m_Index == 1) {
		std::random_shuffle(v1.begin(), v1.end());
		cout << "��" << m_Index<< "��" << endl;
		cout << "����˳��" << endl;
		for (int i = 0; i < v1.size(); i++) {
			cout << v1[i] << "  ";
		}
		cout << endl;
		cout << "ing ..." << endl;
	}
	else
	{
		cout << "��" << m_Index<< "��" << endl;
		std::random_shuffle(v2.begin(), v2.end());
		cout << "����˳��" << endl;
		for (int i = 0; i < v2.size(); i++) {
			cout << v2[i] << "  ";
		}
		cout << endl;
		cout << "ing ..." << endl;
	}
	
	
}

//����
void SpeechManager::startMatch() {
	vector<int> sRc;
	int num=1;
	multimap<double, int, greater<double>> gc;
	if (m_Index == 1) {
		sRc = v1;
	}
	else
	{
		sRc = v2;
	}
	
	for (vector<int>::iterator it = sRc.begin(); it != sRc.end(); it++) {
		
		deque<double> q;
		for (int i = 0; i < 10; i++) {
			//srand(time(0));
			double sc = (rand() % 401 + 600) / 10.f;
			q.push_back(sc);
			//cout << q[i] << endl;
		}
		sort(q.begin(),q.end());
		q.pop_front();
		q.pop_back();
		double sum = accumulate(q.begin(),q.end(),0);
		double avg = sum / (double)q.size();
		m_map.at(*it).m_score[m_Index - 1] = avg;

		
		gc.insert(make_pair(avg,*it));
		if (num % 6 == 0) {
			cout << "��"<< num/6 <<"С��������Ϊ��" << endl;
			for (multimap<double, int, greater<double>>::iterator i = gc.begin(); i != gc.end(); i++) {
				cout << "ѡ��:" << (*i).second << "�ɼ�Ϊ��" << (*i).first << endl;
			}

			if (m_Index == 1) {
				int j = 0;
				for (multimap<double, int, greater<double>>::iterator i = gc.begin(); i != gc.end() && j < 3; i++) {
					j++;
					v2.push_back((*i).second);
				}
			}
			else
			{
				int j = 0;
				for (multimap<double, int, greater<double>>::iterator i = gc.begin(); i != gc.end() && j < 3; i++) {
					j++;
					vVictory.push_back((*i).second);
				}
			}
			gc.clear();
			system("pause");

		}
		num++;
		
		

	}
	if (m_Index == 1) {
		cout << "���������ѡ��Ϊ��" << endl;
		for (vector<int>::iterator i = v2.begin(); i != v2.end(); i++) {
			cout << "ѡ��:" << *i << endl;
		}
	}
	else
	{
		cout << "������ʤ��ѡ��Ϊ��" << endl;
		for (vector<int>::iterator i = vVictory.begin(); i != vVictory.end(); i++) {
			cout << "ѡ��:" << *i << endl;
		}
	}
}

//start speech
void SpeechManager::startSpeech() {
	//First
	//��ǩ
	this->chouQian();
	//����
	this->startMatch();
	//Second
	this->m_Index++;
	//��ǩ
	this->chouQian();
	//����
	this->startMatch();

	cout << "��ϲ������" << endl;

	//save
	this->saveRecord();
	cout << "over" << endl;
	system("pause");
	system("cls");

}

//sava
void SpeechManager::saveRecord() {
	ofstream ofs;
	ofs.open("speech.csv", ios::out | ios::app);
	for (vector<int>::iterator i = vVictory.begin(); i != vVictory.end(); i++) {
		ofs << (*i) << "," << m_map[*i].m_score[1] << ",";
	}
	ofs << endl;
	ofs.close();
	cout << "Saved!!" << endl;
}

//load
void SpeechManager::loadRecord() {
	ifstream ifs("speech.csv", ios::in);
	if (!ifs.is_open()) {
		this->fileIsEmpty = true;
		cout << "Not Exit!" << endl;
		ifs.close();
		return;
	}
	//�ļ�������
	char ch;
	ifs >> ch;
	if (ifs.eof()) {
		cout << "�ļ�Ϊ��" << endl;
		this->fileIsEmpty = true;
		ifs.close();
		return;
	}
	this->fileIsEmpty = false;

	ifs.putback(ch);
	string data;
	int index = 0;
	while(ifs >> data) {
		int pos = -1;
		int start = 0;
		vector<string> v;
		while (true) {
			pos = data.find(",", start);
			if (pos == -1) {
				//cout << "Not Exit" << endl;
				break;
			}
			string temp = data.substr(start,pos-start);
			start = pos+1;
			v.push_back(temp);
		}
		this->m_Record.insert(make_pair(index,v));
		index++;
	
		
		
	}	
	for (map<int, vector<string>>::iterator it = m_Record.begin();it !=
		m_Record.end();it++) {
		cout << "hao" << (*it).first << " score:" << (*it).second[0] << endl;
	}
	ifs.close();
}



SpeechManager::~SpeechManager() {};
