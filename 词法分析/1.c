#pragma warning(disable:4996);
#include<string.h>
#include<stdio.h>
#include<stdlib.h>
#include<ctype.h>
char *Key[30] = {"do","while","then","main","void","int","char","char","float","double","printf","scanf","else","if","return", };
char *bottom[30];
char Word[20], ch;                   
int z=0;
int n = 0;
int m = 0;

int Alpha(char c) {                //�ж��Ƿ�Ϊ��ĸ
	if (((c <= 'z') && (c >= 'a')) || ((c <= 'Z') && (c >= 'A'))) return 1;
	else return 0;
}

int Num(char c) {                //�ж��Ƿ�Ϊ����
	if (c >= '0'&&c <= '9') return 1;
	else return 0;
}

int Key1(char *Word) {          //ʶ�����ֺ���
	int m, i;
	for (i = 0; i<15; i++) {
		if ((m = strcmp(Word, Key[i])) == 0)
		{
			if (i == 0)
				return 2;
			return 1;
		}
	}
	return 0;
}

void saomiao(FILE *fp) {        //ɨ�躯��
	char Word[20] = { '\0' };
	char ch;
	int i, c;
	ch = fgetc(fp);        //��ȡ�ַ���ָ��fp���Զ�ָ����һ���ַ�
	if (Alpha(ch)) {            //�жϸ��ַ��Ƿ�����ĸ
		Word[0] = ch;
		ch = fgetc(fp);
		i = 1;
		while (Num(ch) || Alpha(ch)) {   //�жϸ��ַ��Ƿ�����ĸ������
			Word[i] = ch;
			i++;
			ch = fgetc(fp);
		}
		Word[i] = '\0';       //'\0' �����ַ�����(�ո�)
		fseek(fp, -1, 1);                              //����һ���ַ�
		c = Key1(Word);                              //�ж��Ƿ��Ǳ�����
		if (c == 0) {
			n++;
			bottom[n] = Word;

			printf("(1,%d)\n",n);
			

		}
		//	printf("(1,'%s')\n", Word);//���Ǳ�����
		else if (c == 2)
			printf("(3,'%s')\n", Word);
	 //���������
		else printf("(3,'%s')\n",Word);
	}

	else                          //��ʼ�жϵ��ַ�������ĸ
		if (Num(ch)) {                //�ж��Ƿ�������
			Word[0] = ch;
			ch = fgetc(fp);
			i = 1;
			while (Num(ch)) {
				Word[i] = ch;
				i++;
				ch = fgetc(fp);
			}
			Word[i] = '\0';
			fseek(fp, -1, 1);            //����
		 printf("(2,'%s')\n", Word);
		}
		else         //��ʼ�жϵ��ַ�������ĸҲ��������
		{
			Word[0] = ch;
			switch (ch) {
			case'[':
			case']':
			case'(':
			case')':
			case'{':
			case'}':
			case',':
			case'"':
			case';': printf("(5,'%s')\n", Word);break;
			case':':ch = fgetc(fp);
				Word[1] = ch;
				if (ch == '=') {
					printf("(4,'%s')\n", Word);//�������:=��
				}
				else {
					fseek(fp, -1, 1);
					printf("(4,'%s')\n", Word); //�жϽ��Ϊ��:��
				}
				break;

			case'+':ch = fgetc(fp);
				Word[1] = ch;
				if (ch == '=') {
					printf("(4,'%s')\n", Word);//�������+=��
				}
				else if (ch == '+') {
					printf("(4,'%s')\n", Word); //�жϽ��Ϊ��++��
				}
				else {
					fseek(fp, -1, 1);
					printf("(4,'%s')\n", Word); //�жϽ��Ϊ��+��
				}
				break;
			case'-':ch = fgetc(fp);
				Word[1] = ch;
				if (ch == '=') {
					printf("(4,'%s')\n", Word); //������� -= ��
				}
				else if (ch == '-') {
					printf("(4,'%s')\n", Word); //�жϽ��Ϊ��--��
				}
				else {
					fseek(fp, -1, 1);
					printf("(4,'%s')\n", Word); //�жϽ��Ϊ��-��
				}
				break;
			case'*':
			case'/':
			case'!':
			case'=':ch = fgetc(fp);
				if (ch == '=') {
					printf("(4,'%s')\n", Word);
				}
				else {
					fseek(fp, -1, 1);
					printf("(4,'%s')\n", Word);
				}
				break;
			case'<':ch = fgetc(fp);
				Word[1] = ch;
				if (ch == '=') {
					printf("(4,'%s')\n", Word); //�жϽ��Ϊ�������<=��
				}
				else if (ch == '<') {
					printf("(4,'%s')\n", Word); //�жϽ��Ϊ��<<��
				}
				else {
					fseek(fp, -1, 1);
					printf("(4,'%s')\n", Word); //�жϽ��Ϊ��<��
				}
				break;
			case'>':ch = fgetc(fp);
				Word[1] = ch;
				if (ch == '=') printf("(4,'%s')\n", Word);
				else {
					fseek(fp, -1, 1);
					printf("(4,'%s')\n", Word);
				}
				break;
			case'%':ch = fgetc(fp);
				Word[1] = ch;
				if (ch == '=') { printf("(4,'%s')\n", Word); }
				else {
					fseek(fp, -1, 1);
					printf("(4,'%s')\n", Word);
				}
				break;
			default:printf("�޷�ʶ��\n\n"); break;
			}
		}
	
	}



int main()
{
	char in_fn[30];                          //�ļ�·��
	FILE *fp;
	printf("\nInput:");
	while (1) {
		gets(in_fn);
		if ((fp = fopen(in_fn, "r")) != NULL)  break;  
		else printf("·������:");
	}
	printf("\n");
	/*do {
		ch = fgetc(fp);
		if (ch == EOF)   break;         
		else if (ch == ' ' || ch == '\t' || ch == '\n') {} 
		else {
			fseek(fp, -1, 1);           //����һ���ֽڿ�ʼʶ�𵥴���
			saomiao(fp);
		}
	} while (ch != EOF);*/
	for (int z = 0; z <= 200; z++) {
		ch = fgetc(fp);
		if (ch == EOF)   break;         //�ļ���#��β����Ϊɨ���������
		else if (ch == ' ' || ch == '\t' || ch == '\n') {} 
		else {
			fseek(fp, -1, 1);           //����һ���ֽڿ�ʼʶ�𵥴���
			saomiao(fp);

		}
	}
	system("pause");
	return 0;
}
