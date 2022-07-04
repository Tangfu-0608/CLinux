#include "complier.h"
//先哈希处理
//得到单词哈希值，通过哈希值在单词哈希表中定位并查看对应位置是否为NULL，
//如果不为NULL，则说明该单词存在，直接取出tkcode（TOKEN值）
int elf_hash(string key) {
	int h = 0, g, i = 0;
	while (key[i]) {
		h = (h << 4) + key[i++];
		g = h & 0xf0000000;
		if (g)
			h ^= g >> 24;
		h &= ~g;
	}
	return h % MAXKEY;
}

//初始化哈希表
void InitKeywords(pTkWord keywords, int keywordsLen, pTkWord* tk_Hashtable) {
	for (int i = 0; i < keywordsLen - 1; ++i)
	{
		if (tk_Hashtable[elf_hash(keywords[i].spelling)])
		{
			printf("冲突\n");
			return;
		}
		tk_Hashtable[elf_hash(keywords[i].spelling)] = &keywords[i];
	}//每个keyword的hash值作为tk_Hashtable哈希表下标，填入该keyword所属结构体地址&keywords[i]
}
//根据对应token值打印颜色，不同类别的keyword用不同颜色打印，可遵循混色原则，INTENSITY为亮色
void printColor(string str, tokencode token) {
	HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
	if (token >= TK_IDENT) {//变量名，或者函数名为灰色
		SetConsoleTextAttribute(h, FOREGROUND_INTENSITY);
	}
	else if (token >= KW_CHAR) {//关键字为绿色
		SetConsoleTextAttribute(h, FOREGROUND_GREEN | FOREGROUND_INTENSITY);
	}
	else if (token >= TK_CINT) {//整型常量、浮点型常量、字符常量、字符串常量等为褐色
		SetConsoleTextAttribute(h, FOREGROUND_RED | FOREGROUND_GREEN);
	}
	else {//运算符为红色
		SetConsoleTextAttribute(h, FOREGROUND_RED | FOREGROUND_INTENSITY);
	}
	if (-1 == str[0]) {//EOF
		printf("\n End Of File");
		SetConsoleTextAttribute(h, FOREGROUND_RED | FOREGROUND_INTENSITY | FOREGROUND_BLUE | FOREGROUND_INTENSITY);
	}
	else {
		cout << str;//根据设定颜色打印字符
	}
}

//将字符串进行分割、判断、染色输出、存储到word字符串数组中
int split(vector<string>& word, const string str) {
	for (int i = 0; i < str.length(); i++) {
		if (isalpha(str[i]) || str[i] == '_') {//变量名，必须以英文字母和下划线开头
			string temp;
			while (isalnum(str[i]) || str[i] == '_') {//变量名中可以为英文字母、数字和下划线
				temp.push_back(str[i]);
				i++;
			}
			word.push_back(temp);
			--i;
		}
		else if (str[i] == 34) {//字符串常量，从"一直读到下一个"
			string temp;
			temp.push_back(str[i]);
			i++;
			while (str[i] != 34) {
				temp.push_back(str[i]);
				i++;
			}
			temp.push_back(str[i]);
			word.push_back(temp);
		}
		else if (str[i] == 39) {//字符常量.一次性读入'X'三个字符
			string temp;
			int n = 3;
			while (n--) {
				temp.push_back(str[i]);
				i++;
			}
			word.push_back(temp);
		}
		else if (ispunct(str[i]) || str[i] == ' ') {//其余可打印标点和空格
			string temp;
			temp.push_back(str[i]);
			word.push_back(temp);
		}
		else if (isdigit(str[i])) {//纯数字，整型和浮点
			string temp;
			while (isdigit(str[i])) {
				temp.push_back(str[i]);
				++i;
			}
			if (str[i] == '.') {
				++i;
				if (isdigit(str[i])) {
					temp.push_back('.');
					while (isdigit(str[i])) {
						temp.push_back(str[i]);
						i++;
					}
				}
				else {
					return -1;
				}
			}
			word.push_back(temp);
			--i;
		}
		else if (str[i] == '\t') {
			string temp = "    ";//tab键用四个空格代替
			word.push_back(temp);
		}
	}
}
