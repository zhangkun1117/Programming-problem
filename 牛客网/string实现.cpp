#include <iostream>
#include <cstring>
#include <vector>
using namespace std;

class String{
public:
    // 默认构造函数
    String(char *str = NULL);
    // 复制构造函数
    String(String &str);
    // 析构函数
    ~String();
    // 字符串连接
    String operator+(const String & str);
    // 字符串赋值
    String& operator=(const String &str);
    // 判断是否字符串相等
    bool operator==(const String &str);
    // 获取字符串长度
    int length();
    // 求子字符串[start,start+n-1]
    String substr(int start, int n);
    // 重载输出
    friend ostream & operator<<(ostream &o,const String &str);
private:
    char* m_data;
    int m_size;
};

// 构造函数
String::String(char *str = NULL){
//空构造也会创建一个长度为1的字符串数组
    if(str == NULL){
        m_data = new char[1];
        m_data[0] = '\0';
        m_size = 0;
    }
    else{
        m_size = strlen(str);
        m_data = new char[m_size + 1];
        strcpy(m_data,str);
    }
}

//拷贝构造函数
String::String(const String &str){
    m_size = str.m_size;
    m_data = new char[m_size + 1];
    strcpy(m_data, str.m_data);
}

//析构函数
String::~String(){
    delete[] m_data;
}

// 字符串连接
//这里返回的不是引用，而是值
String String::operator+(const String &str){
    String newStr;
    //释放原有空间
    delete[] newStr.m_data;
    //创建长度为两个字符串长度和的空间大小
    newStr.m_size = m_size + str.m_size;
    newStr.m_data = new char[newStr.m_size + 1];
    strcpy(newStr.m_data, m_data);
    strcpy(newStr.m_data + m_size, str.m_data);
    return newStr;
}

//赋值函数
/*
这里为什么返回对象的引用呢?原因有两个：①允许进行连续赋值 ②防止返回对象(返回对象也可以进行连续赋值)的时候调用拷贝构造函数和析构函数导致不必要的开销，降低赋值运算符等的效率。
对于第二点原因：如果用“值传递”的方式，虽然功能仍然正确，但由于return语句要把 *this拷贝到保存返回值的外部存储单元之中，增加了不必要的开销，会降低赋值函数的效率。
因此，如果赋值运算符返回的是对象引用，那么其不会调用类的拷贝构造函数，这是问题的关键所在！！
*/

String& String::operation=(const char * str){
    if (m_data == str){
    return *this;
    }
    delete[] m_data;
    m_size = strlen(str);
    m_data = new char[m_size + 1];
    strcpy(m_data, str);
    return *this;
}

//判断是否相等
bool String::operation==(const char *str){
    return strcmp(m_data, str.m_data) == 0;
}

//获取长度
int String::length(){
    return m_size;
}

//求子字符串[start,start+n-1]
String String::substr(int start, int n){
    String newStr;
    //释放原有内存
    delete[] newStr.m_data;
    //重新申请内存
    newStr.m_data = new char[n + 1];
    for (int i = 0; i < n; i++){
        newStr.m_data[i] = m_data[start + i];   
    }
    newStr.m_data[n] = '\0';
    newStr.m_size = n;
    return newStr;
}

// 重载输出
ostream & operator<<(ostream &o, const String &str){
    o<<str.data;
    return o;
}