#include<iostream>
#include<string>
#include"LexicalAnalysis.h"
#include"DataStructure.h"
//using namespace std;

//	保留字、标识符、数字的词法分析程序
int KeyIdentNumAnalysis(string strKeyNumIdWord, string &strTemp, vector<char> &inputStr) {

	if (KeywordAnalysis(strKeyNumIdWord) != ERROR) {
		strTemp = strKeyNumIdWord;
		cout << strTemp << endl;
		inputStr.push_back('K');
		return KEYWORD;
	}
	else if (IdentAnalysis(strKeyNumIdWord) != ERROR) {
		strTemp = strKeyNumIdWord;
		cout << strTemp << "\tf" << endl;
		inputStr.push_back('f');
		return IDENT;
	}
	else if (NumberAnalysis(strKeyNumIdWord) != ERROR) {
		strTemp = strKeyNumIdWord;
		cout << strTemp << "\te" << endl;
		inputStr.push_back('e');
		return CONSTANT;
	}
	else {
		cout << "输入有误！" << endl;
		return ERROR;
	}
}

// 关键字词法分析
int KeywordAnalysis(string strKeyword) {
	const char* strchar = strKeyword.c_str();
	char ch = strchar[0];

	if ((ch >= 'a'&&ch <= 'z') || (ch >= 'A'&&ch <= 'Z')) {
		for (int i = 0; i < CHKEYLEFTNUM; i++) {
			if (strKeyword == chKeyWord[i]) {
				return KEYWORD;
			}
		}
	}
	return ERROR;
}

// 标识符词法分析
int IdentAnalysis(string strIdent) {
	const char* strchar = strIdent.c_str();
	char ch = strchar[0];

	if ((ch >= 'a'&&ch <= 'z') || (ch >= 'A'&&ch <= 'Z')) {
		for (int i = 0; i < CHKEYLEFTNUM; i++) {
			if (strIdent == chKeyWord[i]) {
				return 0;
			}
		}
		return IDENT;
	}
	return ERROR;
}

// 数字词法分析
int NumberAnalysis(string strNum) {
	const char* strchar = strNum.c_str();
	char ch = strchar[0];
	int d = 0;
	int sum = 0;

	for (unsigned int i = 0; i < strNum.length(); i++) {
		if (ch >= '0'&&ch <= '9') {
			d = (int)strchar[i] - 48;	// 因为字符'0'的ASCII码值为48
			sum = sum * 10 + d;
		}
		else {
			return ERROR;
		}
	}
	return sum;
}

// 运算符词法分析
int OperatorAnalysis(string strOperator) {
	for (int i = 0; i < CHOPERNUM; i++) {
		if (strOperator == chOperatorWord[i]) {
			cout << strOperator << "\t"<< strOperator << endl;
			return OPERATOR;
		}
	}
	return ERROR;
}

// 界限符词法分析
int BaundaryAnlysis(string strBaundary) {
	for (int i = 0; i < CHBAUNNUM; i++) {
		if (strBaundary == chBaundaryWord[i]) {
			//string strTemp2 = "( '" + strBaundary + "' , " + "5" + " )";
			cout << strBaundary << "\t" << strBaundary << endl;
			return BAUNDARY;
		}
	}
	return ERROR;
}

// 判断是否是运算符字符
bool IsOperator(char ch) {
	for (int i = 0; i < CHOPERNUM; i++) {
		if (ch == chOperator[i]) {
			return true;
		}
	}
	return false;
}

// 词法分析程序
int LexAnalysis(int &wordIndex, char &ch, string &strWord,
	string &strOperator, string &strBaun, string &strTemp, vector<char> &inputStr) {
	int temp;
	// 过滤掉空格、换行符、制表符 
	if (ch != ' '&&ch != '\n'&&ch != '\t') {
		// 如果是非空格、制表符、回车符、界符、运算符等字符，则添加到strWord字符串中
		if ((ch >= 'a'&&ch <= 'z') || (ch >= 'A'&&ch <= 'Z') || (ch >= '0'&&ch <= '9')) {
			strWord += ch;
			//用于判断操作符是否是>=,<=,:=等
			if (strOperator != "") {
				wordIndex++;
				if (OperatorAnalysis(strOperator) != 0) {
					inputStr.push_back(strOperator.at(0));
					strOperator = "";
				}
				else {
					cout << "第" << wordIndex << "个单词分析有误！" << endl;
					return ERROR;
				}
			}
			return READ;
		}
		// 如果是操作符则添加到strOpertor字符串中
		else if (IsOperator(ch)) {
			wordIndex++;
			strOperator += ch;
			/* 要判断strWord字符串是否为空，可能会出现连续空格、制表符、回车符的情况
			 * 连续遇到空格等分隔符均会被识别为分隔符，进而执行字符串词法分析子程序
			 * 但在识别到第一个空格时，已经执行过词法分析子程序，应当避免重复执行
			 * 所以要判断strWord字符串是否为空，若为空值，则不执行词法分析子程序；反之执行词法分析子程序
			 * 下方判断strWord字符串是否为空的目的与此类似
			*/
			if (!(strWord == "")) {
				wordIndex++;
				// 遇到运算符会分割标识符、关键字等，也要将strWord作判断
				//temp = KeyIdentNumAnalysis(strWord, strTemp, outMAp);
				temp = KeyIdentNumAnalysis(strWord, strTemp, inputStr);
				if (temp != 0) {
					strWord = "";
					//return temp;
					//return READ;
				}
				else {
					cout << "第" << wordIndex << "个单词分析有误！" << endl;
					return ERROR;
				}
			}

			// 可能会出现>=,<=,:=等类型，所以另加一步判断
			//if (ch == '<' || ch == '>' || ch == '：') {
			if (ch == '<' || ch == '>' || ch == '=') {
				wordIndex--;
				return READ;
			}

			if (OperatorAnalysis(strOperator) != 0) {
				inputStr.push_back(strOperator.at(0));
				strOperator = "";
				return OPERATOR;
			}

		}
		else if (ch == '(' || ch == ')' || ch == ',' || ch == ';' || ch == '.') {
			strBaun += ch;
			//用于判断操作符是否是>=,<=,:=等
			if (strOperator != "") {
				wordIndex++;
				if (OperatorAnalysis(strOperator) != 0) {
					inputStr.push_back(strOperator.at(0));
					strOperator = "";
				}
				else {
					cout << "第" << wordIndex << "个单词分析有误！" << endl;
					return ERROR;
				}
			}

			if (!(strWord == "")) {
				wordIndex++;
				// 遇到界符会分割标识符、关键字等，也要将strWord作判断
				//temp = KeyIdentNumAnalysis(strWord, strTemp, outMap);
				temp = KeyIdentNumAnalysis(strWord, strTemp, inputStr);
				if (temp != 0) {
					strWord = "";
					//return temp;
					//return READ;
				}
				else {
					cout << "第" << wordIndex-1 << "个单词分析有误！" << endl;
					return ERROR;
				}

			}

			if (BaundaryAnlysis(strBaun) != 0) {
				wordIndex++;
				inputStr.push_back(strBaun.at(0));
				strBaun = "";
				return BAUNDARY;
			}
			else {
				cout << "第" << wordIndex << "个单词分析有误！" << endl;
				return ERROR;
			}

		}
		else {

			if (int(ch) != -1) {	//ch==-1,则表示读到文件末尾
				strWord = "";
				cout << "第" << wordIndex << "个单词错误！" << endl;
				return 0;
			}
			else {
				//用于判断操作符是否是>=,<=,:=等
				if (strOperator != "") {
					wordIndex++;
					if (OperatorAnalysis(strOperator) != 0) {
						inputStr.push_back(strOperator.at(0));
						strOperator = "";
					}
					else {
						cout << "第" << wordIndex << "个单词分析有误！" << endl;
						return ERROR;
					}
				}

				if (!(strWord == "")) {
					wordIndex++;
					// 读到文件末尾时，应该对字符串进行词法分析
					temp = KeyIdentNumAnalysis(strWord, strTemp, inputStr);
					if (temp != 0) {
						strWord = "";
						return temp;
						//return READ;
					}
					else {
						cout << "第" << wordIndex << "个单词分析有误！" << endl;
						return 0;
					}
				}
			}
		}
	}
	else {
	//用于判断操作符是否是>=,<=,:=等
		if (strOperator != "") {
			wordIndex++;
			if (OperatorAnalysis(strOperator) != 0) {
				inputStr.push_back(strOperator.at(0));
				strOperator = "";
			}
			else {
				cout << "第" << wordIndex << "个单词分析有误！" << endl;
				return ERROR;
			}
		}

		if (!(strWord == "")) {
			wordIndex++;
			// 再次遇到空格等字符时，应该对字符串进行词法分析
			temp = KeyIdentNumAnalysis(strWord, strTemp, inputStr);
			if (temp != 0) {
				strWord = "";
				return temp;
			}
			else {
				cout << "第" << wordIndex << "个单词分析有误！" << endl;
				return 0;
			}
		}	
	}
	return READ;
}