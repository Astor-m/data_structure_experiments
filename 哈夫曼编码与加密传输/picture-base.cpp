#include <string>
#include <iostream>
#include "base64.h"
#include <fstream>
#include <stdlib.h>

using namespace std;

int main(int argc, char** argv){
    fstream f, f2;
    f.open("a.jpg", ios::in|ios::binary);
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
    f2.open("out.jpg", ios::out|ios::binary);
    f2 << imgdecode64;
    f2.close();
    return 0;
}
