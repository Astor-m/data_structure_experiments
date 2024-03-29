#include<iostream>
#include<cstdio>
#include<vector>
#include<map>
#include<stack>
#include<cstring>
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

void readfile() {
	cout << "请输入文件的绝对路径:" << endl;
	string filename;
	cin >> filename;
	FILE *fp;
	char ch;
	if ((fp = fopen(filename.c_str(), "rt")) == NULL) {
		printf("\nCannot open file strike any key exit!");
//	    getch();
		exit(1);
	}
	ch = fgetc(fp);
	memset(weight, -1, sizeof weight);
	cout << "保存的字符有：";
	while (ch != EOF) {
//	    putchar(ch);
		printf("\"%c\",", ch);
		if (weight[ch] == -1) {
			weight[ch] = 0;
		}
		data += ch;
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

void find_two_min(int end) {
	int weight1 = 999, weight2 = 999;
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

void create_hfm() {
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

void print_hfm() {
	cout<<"------------------------"<<endl;
	cout<<"哈夫曼表："<<endl;
	for (int i = 0; i < 2 * MAXN; i++) {
		if (H[i].is_have)
			printf("%d\t%c\t%d\t%d\t%d\t%d\n", i, H[i].data, H[i].value, H[i].lchild, H[i].rchild, H[i].parent);

	}
	cout<<"-------------------------"<<endl;
}

void build_hfm_data() {
	cout <<"从文件读取的数据："<<data << endl;
	FILE *fp = NULL;
	FILE *fp2 = NULL;
	fp = fopen("D:\\BaiduNetdiskDownload\\output.txt", "w+");
	fp2 = fopen("D:\\BaiduNetdiskDownload\\outputkey.txt", "w+");
	if (fp == NULL) {
		cout << "error" << endl;
		return;
	}
	cout<<"------------------------------"<<endl;
	cout<<"每个字符对应的哈夫曼编码："<<endl;
	for (int i = 0; i < data.length(); i++) {
		int temp = data[i];
		fprintf(fp2, "%c", data[i]);
		cout << data[i] << ":";
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
			cout << s.top();
			s.pop();
		}
		fprintf(fp2, "\n");
		cout << endl;
	}
	fclose(fp);
	fclose(fp2);
	cout<<"-------------------------------"<<endl;
	cout << "生成的hfm编码文件在D:\\BaiduNetdiskDownload\\output.txt" << endl;
	cout << "生成的hfm编码在D:\\BaiduNetdiskDownload\\outputkey.txt" << endl;
	cout<<"-------------------------------"<<endl;
}
void Readkey() {

	char filename[] = "D:\\BaiduNetdiskDownload\\outputkey.txt"; //文件名
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

void decode() {
	cout<<"-------------------------------"<<endl;
	cout<<"进行哈夫曼编码"<<endl;
	Readkey();
	string temp = "";
	char ch ;
	FILE *file = fopen("D:\\BaiduNetdiskDownload\\output.txt", "rt");
	if (!file)
		return;
	cout<<"解码后的内容：";
	while (EOF != (ch = fgetc(file))) {
		temp+=ch;
		if(m[temp]!=NULL){
			cout<<m[temp];
			temp="";
		}
	}
	fclose(file);
}

int main() {
	create_hfm();
	print_hfm();
	build_hfm_data();
	decode();

	return 0;
}
