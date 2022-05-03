#pragma once
#include<iostream>
#include<vector>
#include<map>
#include <cstdlib> // Header file needed to use srand and rand
#include <ctime> // Header file needed to use time
#include <algorithm>
#include<deque>
#include <numeric>
#include<fstream>
#include"speaker.h"
using namespace std;

class CmpByValue1 {
public:
	bool operator()(const pair<int, Spearker>& lhs, const pair<int, Spearker>& rhs) {
		return (lhs.second).m_score[0] > (rhs.second).m_score[0];
	}
};
class CmpByValue2 {
public:
	bool operator()(const pair<int, Spearker>& lhs, const pair<int, Spearker>& rhs) {
		return (lhs.second).m_score[1] > (rhs.second).m_score[1];
	}
};

//����ݽ�������
class SpeechManager {
public:
	SpeechManager();

	//Menu
	void show_Menu();

	//enit
	void exitSystem();

	//init property
	void initSpeech();

	//creat spearker
	void createSpeaker();

	//��Ա����
	//�����һ��ѡ�ֱ��
	vector<int> v1;
	vector<int> v2;
	vector<int> vVictory;
	map<int, Spearker> m_map;

	//index
	int m_Index;


	//start speech
	void startSpeech();

	//start ��ǩ
	void chouQian();

	//����
	void startMatch();

	//save
	void saveRecord();

	//load
	void loadRecord();

	bool fileIsEmpty;

	map<int, vector<string>> m_Record;

	~SpeechManager();

};