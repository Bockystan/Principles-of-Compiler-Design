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

int Alpha(char c) {                //判断是否为字母
	if (((c <= 'z') && (c >= 'a')) || ((c <= 'Z') && (c >= 'A'))) return 1;
	else return 0;
}

int Num(char c) {                //判断是否为数字
	if (c >= '0'&&c <= '9') return 1;
	else return 0;
}

int Key1(char *Word) {          //识别保留字函数
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

void saomiao(FILE *fp) {        //扫描函数
	char Word[20] = { '\0' };
	char ch;
	int i, c;
	ch = fgetc(fp);        //获取字符，指针fp并自动指向下一个字符
	if (Alpha(ch)) {            //判断该字符是否是字母
		Word[0] = ch;
		ch = fgetc(fp);
		i = 1;
		while (Num(ch) || Alpha(ch)) {   //判断该字符是否是字母或数字
			Word[i] = ch;
			i++;
			ch = fgetc(fp);
		}
		Word[i] = '\0';       //'\0' 代表字符结束(空格)
		fseek(fp, -1, 1);                              //回退一个字符
		c = Key1(Word);                              //判断是否是保留字
		if (c == 0) {
			n++;
			bottom[n] = Word;

			printf("(1,%d)\n",n);
			

		}
		//	printf("(1,'%s')\n", Word);//不是保留字
		else if (c == 2)
			printf("(3,'%s')\n", Word);
	 //输出保留字
		else printf("(3,'%s')\n",Word);
	}

	else                          //开始判断的字符不是字母
		if (Num(ch)) {                //判断是否是数字
			Word[0] = ch;
			ch = fgetc(fp);
			i = 1;
			while (Num(ch)) {
				Word[i] = ch;
				i++;
				ch = fgetc(fp);
			}
			Word[i] = '\0';
			fseek(fp, -1, 1);            //回退
		 printf("(2,'%s')\n", Word);
		}
		else         //开始判断的字符不是字母也不是数字
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
					printf("(4,'%s')\n", Word);//运算符“:=”
				}
				else {
					fseek(fp, -1, 1);
					printf("(4,'%s')\n", Word); //判断结果为“:”
				}
				break;

			case'+':ch = fgetc(fp);
				Word[1] = ch;
				if (ch == '=') {
					printf("(4,'%s')\n", Word);//运算符“+=”
				}
				else if (ch == '+') {
					printf("(4,'%s')\n", Word); //判断结果为“++”
				}
				else {
					fseek(fp, -1, 1);
					printf("(4,'%s')\n", Word); //判断结果为“+”
				}
				break;
			case'-':ch = fgetc(fp);
				Word[1] = ch;
				if (ch == '=') {
					printf("(4,'%s')\n", Word); //运算符“ -= ”
				}
				else if (ch == '-') {
					printf("(4,'%s')\n", Word); //判断结果为“--”
				}
				else {
					fseek(fp, -1, 1);
					printf("(4,'%s')\n", Word); //判断结果为“-”
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
					printf("(4,'%s')\n", Word); //判断结果为运算符“<=”
				}
				else if (ch == '<') {
					printf("(4,'%s')\n", Word); //判断结果为“<<”
				}
				else {
					fseek(fp, -1, 1);
					printf("(4,'%s')\n", Word); //判断结果为“<”
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
			default:printf("无法识别\n\n"); break;
			}
		}
	
	}



int main()
{
	char in_fn[30];                          //文件路径
	FILE *fp;
	printf("\nInput:");
	while (1) {
		gets(in_fn);
		if ((fp = fopen(in_fn, "r")) != NULL)  break;  
		else printf("路径错误:");
	}
	printf("\n");
	/*do {
		ch = fgetc(fp);
		if (ch == EOF)   break;         
		else if (ch == ' ' || ch == '\t' || ch == '\n') {} 
		else {
			fseek(fp, -1, 1);           //回退一个字节开始识别单词流
			saomiao(fp);
		}
	} while (ch != EOF);*/
	for (int z = 0; z <= 200; z++) {
		ch = fgetc(fp);
		if (ch == EOF)   break;         //文件以#结尾，作为扫描结束条件
		else if (ch == ' ' || ch == '\t' || ch == '\n') {} 
		else {
			fseek(fp, -1, 1);           //回退一个字节开始识别单词流
			saomiao(fp);

		}
	}
	system("pause");
	return 0;
}
