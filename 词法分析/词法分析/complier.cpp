#include "complier.h"
//�ȹ�ϣ����
//�õ����ʹ�ϣֵ��ͨ����ϣֵ�ڵ��ʹ�ϣ���ж�λ���鿴��Ӧλ���Ƿ�ΪNULL��
//�����ΪNULL����˵���õ��ʴ��ڣ�ֱ��ȡ��tkcode��TOKENֵ��
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

//��ʼ����ϣ��
void InitKeywords(pTkWord keywords, int keywordsLen, pTkWord* tk_Hashtable) {
	for (int i = 0; i < keywordsLen - 1; ++i)
	{
		if (tk_Hashtable[elf_hash(keywords[i].spelling)])
		{
			printf("��ͻ\n");
			return;
		}
		tk_Hashtable[elf_hash(keywords[i].spelling)] = &keywords[i];
	}//ÿ��keyword��hashֵ��Ϊtk_Hashtable��ϣ���±꣬�����keyword�����ṹ���ַ&keywords[i]
}
//���ݶ�Ӧtokenֵ��ӡ��ɫ����ͬ����keyword�ò�ͬ��ɫ��ӡ������ѭ��ɫԭ��INTENSITYΪ��ɫ
void printColor(string str, tokencode token) {
	HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
	if (token >= TK_IDENT) {//�����������ߺ�����Ϊ��ɫ
		SetConsoleTextAttribute(h, FOREGROUND_INTENSITY);
	}
	else if (token >= KW_CHAR) {//�ؼ���Ϊ��ɫ
		SetConsoleTextAttribute(h, FOREGROUND_GREEN | FOREGROUND_INTENSITY);
	}
	else if (token >= TK_CINT) {//���ͳ����������ͳ������ַ��������ַ���������Ϊ��ɫ
		SetConsoleTextAttribute(h, FOREGROUND_RED | FOREGROUND_GREEN);
	}
	else {//�����Ϊ��ɫ
		SetConsoleTextAttribute(h, FOREGROUND_RED | FOREGROUND_INTENSITY);
	}
	if (-1 == str[0]) {//EOF
		printf("\n End Of File");
		SetConsoleTextAttribute(h, FOREGROUND_RED | FOREGROUND_INTENSITY | FOREGROUND_BLUE | FOREGROUND_INTENSITY);
	}
	else {
		cout << str;//�����趨��ɫ��ӡ�ַ�
	}
}

//���ַ������зָ�жϡ�Ⱦɫ������洢��word�ַ���������
int split(vector<string>& word, const string str) {
	for (int i = 0; i < str.length(); i++) {
		if (isalpha(str[i]) || str[i] == '_') {//��������������Ӣ����ĸ���»��߿�ͷ
			string temp;
			while (isalnum(str[i]) || str[i] == '_') {//�������п���ΪӢ����ĸ�����ֺ��»���
				temp.push_back(str[i]);
				i++;
			}
			word.push_back(temp);
			--i;
		}
		else if (str[i] == 34) {//�ַ�����������"һֱ������һ��"
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
		else if (str[i] == 39) {//�ַ�����.һ���Զ���'X'�����ַ�
			string temp;
			int n = 3;
			while (n--) {
				temp.push_back(str[i]);
				i++;
			}
			word.push_back(temp);
		}
		else if (ispunct(str[i]) || str[i] == ' ') {//����ɴ�ӡ���Ϳո�
			string temp;
			temp.push_back(str[i]);
			word.push_back(temp);
		}
		else if (isdigit(str[i])) {//�����֣����ͺ͸���
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
			string temp = "    ";//tab�����ĸ��ո����
			word.push_back(temp);
		}
	}
}
