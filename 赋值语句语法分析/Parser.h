#pragma once
#include<iostream>
#include<string>
#include<stack>
#include<vector>
//#include"DataStructure.h"
//#include"LexicalAnalysis.h"

using namespace std;
#define GSIZE 13	// �ķ�����ʽ�ĸ���
#define SLRSIZE 20	// ״̬����

static map<string, char> G[GSIZE];
static map<char, int> SLR[SLRSIZE];
static stack<string> res; // ��������ڵ�����
//bool parser(map<string,int> outMap);
// ��ʼ��
void init();
// �﷨��������
bool parser(vector<char> inputStr);
void test();