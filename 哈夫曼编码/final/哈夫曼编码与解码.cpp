#include<iostream>
#include<cstdio>
#include<vector>
#include<map>
#include<stack>
#include<cstring>
#include <string>
#include <iostream>
#include "base64.h"
#include <fstream>
#include <stdlib.h>

#define MAXN 999
#define Elemdata char
using namespace std;
struct hfm {
	Elemdata data;
	int parent = 0;
	int lchild = 0;
	int rchild = 0;
	int value = 0;
	bool is_have = false;
};
map<string, char>m;
hfm H[MAXN * MAXN];
string data = "";
int weight[MAXN];
int elem_num;
int index[2];
string filename;

string read_file(){//读取文件，并返回base码 
    fstream f, f2;
    //-----------------------------------------------------------------------------------
    f.open("c.txt", ios::in|ios::binary);//需要哈夫曼解压的文件
    //--
    f.seekg(0, std::ios_base::end);
    std::streampos sp = f.tellg();
    int size = sp;
    cout << size << endl;
    char* buffer = (char*)malloc(sizeof(char)*size);
    f.seekg(0, std::ios_base::beg);//把文件指针移到到文件头位置
    f.read(buffer,size);
    cout << "file size:" << size << endl;     
    string imgBase64 = base64_encode(buffer, size);
    cout<<imgBase64<<endl;
    cout << "img base64 encode size:" << imgBase64.size() << endl;  
    string imgdecode64 = base64_decode(imgBase64);
    cout << "img decode size:" << imgdecode64.size() << endl;     
    f2.open("out.txt", ios::out|ios::binary);
    f2 << imgdecode64;
    f2.close();
    return imgBase64;
}

void writ_file(string str){//将得到的base码写入base_code.txt文件 
	FILE *fp;
	fp = fopen("base_code.txt", "w+");
	for(long long i=0;i<str.length();i++){
		char ch=str[i];
		fprintf(fp, "%c", ch);
	}
	fclose(fp);
}

void readfile() {//读取base_code.txt的base码，并将base码进行huffman编码 
	writ_file(read_file());
//	cout << "请输入文件的绝对路径:" << endl;
//	cin >> filename;
	filename="base_code.txt";
	FILE *fp;
	char ch;
	if ((fp = fopen(filename.c_str(), "rt")) == NULL) {
		printf("\n");
//	    getch();
		exit(1);
	}
	ch = fgetc(fp);
	memset(weight, -1, sizeof weight);
	cout << "保存的字符有：";
	while (ch != EOF) {
//		printf("\"%c\",", ch);
		if (weight[ch] == -1) {
			weight[ch] = 0;
		}
		weight[ch]++;
		ch = fgetc(fp);
	}
	printf("\n");
	for (int i = 0; i < MAXN; i++) {
		if (weight[i] != -1) {
			elem_num++;
		}
	}
	fclose(fp);
}

void find_two_min(int end) {//找到出现次数最少的两个字符 
	int weight1 = 99999999, weight2 = 99999999;
	for (int i = 0; i < end; i++) {
		if (H[i].parent == 0 && H[i].is_have == true) {
			if (H[i].value < weight2) {
				if (H[i].value < weight1) {
					weight2 = weight1;
					weight1 = H[i].value;
					index[1] = index[0];
					index[0] = i;
				} else {
					weight2 = H[i].value;
					index[1] = i;
				}
			}
		}
	}
}

void create_hfm() {//构建huffman树 
	readfile();
	for (int i = 0; i < MAXN; i++) {
		if (weight[i] != -1) {
			H[i].is_have = true;
			H[i].data = char(i);
			H[i].value = weight[i];
		}
	}
	for (int i = MAXN + 1; i <= MAXN + elem_num - 1; i++) {
		find_two_min(i);
		H[i].lchild = index[0];
		H[i].rchild = index[1];
		H[i].value = H[index[0]].value + H[index[1]].value;
		H[index[0]].parent = i;
		H[index[1]].parent = i;
		H[i].is_have = true;
	}
}

void print_hfm() {//打印huffman表 
	cout << "------------------------" << endl;
	cout << "哈夫曼表：" << endl;
	for (int i = 0; i < 2 * MAXN; i++) {
		if (H[i].is_have)
			printf("%d\t%c\t%d\t%d\t%d\t%d\n", i, H[i].data, H[i].value, H[i].lchild, H[i].rchild, H[i].parent);

	}
	cout << "-------------------------" << endl;
}

void build_hfm_data() {//将生成的huffman编码存入huffmancode.txt文件，将huffman表写入huffmanlist.txt文件 
//	cout << "从文件读取的数据：" << data << endl;
	FILE *fp = NULL;
	FILE *fp2 = NULL;
	fp = fopen("huffmancode.txt", "w+");
	fp2 = fopen("huffmanlist.txt", "w+");
	if (fp == NULL) {
		cout << "error" << endl;
		return;
	}
	cout << "------------------------------" << endl;
	cout << "每个字符对应的哈夫曼编码：" << endl;

	FILE *fp3;
	char ch;
	if ((fp3 = fopen(filename.c_str(), "rt")) == NULL) {
		printf("\nCannot open file strike any key exit!");
		//	    getch();
		exit(1);
	}
	ch = fgetc(fp3);
	while (ch != EOF) {
		int temp = ch;
		fprintf(fp2, "%c", ch);
//		cout << ch << ":";
		stack<char> s;
		string str = "";
		while (H[temp].parent != 0) {
			int next = H[temp].parent;
			if (H[next].lchild == temp) {
				s.push('1');
			}
			if (H[next].rchild == temp) {
				s.push('0');
			}
			temp = next;
		}
		while (!s.empty()) {
			fprintf(fp, "%c", s.top());
			fprintf(fp2, "%c", s.top());
			str += s.top();
//			cout << s.top();
			s.pop();
		}
		fprintf(fp2, "\n");
//		cout << endl;
		ch = fgetc(fp3);
	}

//	for (int i = 0; i < data.length(); i++) {
//		int temp = data[i];
//		fprintf(fp2, "%c", data[i]);
//		cout << data[i] << ":";
//		stack<char> s;
//		string str = "";
//		while (H[temp].parent != 0) {
//			int next = H[temp].parent;
//			if (H[next].lchild == temp) {
//				s.push('1');
//			}
//			if (H[next].rchild == temp) {
//				s.push('0');
//			}
//			temp = next;
//		}
//		while (!s.empty()) {
//			fprintf(fp, "%c", s.top());
//			fprintf(fp2, "%c", s.top());
//			str += s.top();
//			cout << s.top();
//			s.pop();
//		}
//		fprintf(fp2, "\n");
//		cout << endl;
//	}
	fclose(fp);
	fclose(fp2);
	cout << "-------------------------------" << endl;
	cout << "生成的hfm编码文件在huffmancode.txt" << endl;
	cout << "生成的hfm编码在huffmanlist.txt" << endl;
	cout << "-------------------------------" << endl;
}
void Readkey() {

	char filename[] = "huffmanlist.txt"; //文件名
	FILE *fp = NULL;
	char StrLine[1024];
	if ((fp = fopen(filename, "r")) == NULL) { //判断文件是否存在及可读
		printf("error!");
		return ;
	}
	while (!feof(fp)) {
		fgets(StrLine, 1024, fp);
//		printf("%s", StrLine);
		string key = "";
		char ch = StrLine[0];
		for (int i = 1; i < strlen(StrLine) - 1; i++) {
			key += StrLine[i];
		}
//		cout << "key: " << key << endl;
//		cout<<"ch: "<<ch<<endl;
		m[key] = ch;
//		cout<<"m[key]="<<m[key]<<endl;
	}
	fclose(fp);
	return;
}
int reback(string imgdecode64) {//将huffman编码转回与源文件格式，并保存在out.jpg问价 
	fstream f2;
	cout << "img decode size:" << imgdecode64.size() << endl;
	f2.open("out.jpg", ios::out | ios::binary);//重新解码后的文件
	imgdecode64 = base64_decode(imgdecode64);
	f2 << imgdecode64;
	f2.close();
	return 0;
}
void decode() {
	cout << "-------------------------------" << endl;
	cout << "进行哈夫曼编码" << endl;
	Readkey();
	string temp = "";
	char ch ;
	FILE *file = fopen("huffmancode.txt", "rt");
	if (!file)
		return;
	cout << "解码后的内容：";
	string rebackfile="";
	while (EOF != (ch = fgetc(file))) {
		temp += ch;
		if (m[temp] != NULL) {
			cout << m[temp];
			rebackfile+=m[temp];
			temp = "";
		}
	}
	fclose(file);
	reback(rebackfile);
}

int main() {
	cin.tie(0);
	cout.tie(0);
	ios::sync_with_stdio(0);
	create_hfm();
	print_hfm();
	build_hfm_data();
	decode();

	return 0;
}
