#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#include<Windows.h>
#include<string.h>
#include<ctype.h>
#include<string>
#include<vector>
#include<fstream>
#include<iostream>
using namespace std;
#define MAXKEY 10000

//ͨ��ö�ٶ�������������ؼ��ֱ��

enum e_TokenCode
{
	/* ��������ָ��� */
	TK_PLUS,		// + �Ӻ�
	TK_MINUS,		// - ����
	TK_STAR,		// * �Ǻ�
	TK_DIVIDE,		// / ����
	TK_MOD,			// % ���������
	TK_EQ,			// == ���ں�
	TK_NEQ,			// != �����ں�
	TK_LT,			// < С�ں�
	TK_LEQ,			// <= С�ڵ��ں�
	TK_GT,			// > ���ں�
	TK_GEQ,			// >= ���ڵ��ں�
	TK_ASSIGN,		// = ��ֵ����� 
	TK_POINTSTO,	// -> ָ��ṹ���Ա�����
	TK_DOT,			// . �ṹ���Ա�����
	TK_AND,         // & ��ַ�������
	TK_OPENPA,		// ( ��Բ����
	TK_CLOSEPA,		// ) ��Բ����
	TK_OPENBR,		// [ ��������
	TK_CLOSEBR,		// ] ��������
	TK_BEGIN,		// { �������
	TK_END,			// } �Ҵ�����
	TK_SEMICOLON,	// ; �ֺ�
	TK_COMMA,		// , ����
	TK_ELLIPSIS,	// ... ʡ�Ժ�
	TK_EOF,			// �ļ�������

	/* ���� */
	TK_CINT,		// ���ͳ���
	TK_CFLOAT,		// �����ͳ���
	TK_CCHAR,		// �ַ�����
	TK_CSTR,		// �ַ�������

	/* �ؼ��� */
	KW_CHAR,		// char�ؼ���
	KW_SHORT,		// short�ؼ���
	KW_INT,			// int�ؼ���
	KW_VOID,		// void�ؼ���
	KW_STRUCT,		// struct�ؼ��� 
	KW_IF,			// if�ؼ���
	KW_ELSE,		// else�ؼ���
	KW_FOR,			// for�ؼ���
	KW_WHILE,       // while�ؼ���
	KW_CONTINUE,	// continue�ؼ���
	KW_BREAK,		// break�ؼ���
	KW_RETURN,		// return�ؼ���
	KW_SIZEOF,		// sizeof�ؼ���
	
	KW_ALIGN,		// _align�ؼ���
	KW_CDECL,		// _cdecl�ؼ��� standard c call
	KW_STDCALL,	    // _stdcall�ؼ��� pascal c call

	/* ��ʶ�� */
	TK_IDENT		// ����

};

typedef enum e_TokenCode tokencode;

/*���ʴ洢�ṹ����*/
typedef struct TkWord
{
	int tkcode;          //���ʱ���,��TOKENֵ
	char spelling[200];	 //�����ַ������浥��
	struct TkWord *next; //ָ���ϣ��ͻ����������
}TkWord,*pTkWord;       //��ŵ��ʱ���enum,��ƴд

/*---------------------------------�ʷ���������----------------------------------------*/

int elf_hash(string key);
void InitKeywords(pTkWord keywords, int keywordsLen, pTkWord* tk_Hashtable);
void printColor(string str, tokencode token);
int split(vector<string>& word, const string str);
