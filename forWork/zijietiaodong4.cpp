#include <iostream>
#include <vector>
#include <numeric>
#include <limits>
#include <string>   
#include <set>
#include <algorithm>
#include <map>

using namespace std;

//第二题：


/*
//第五题  60
bool isLucky(long long int num){
    string s = to_string(num);
    for(long long int i=0,j=s.size()-1;i<j;i++,j--){
        if(s[i] == s[j])
            return false;
    }
    return true;
}
int main(){
    long long int a,b;
    cin>>a>>b;
    long long int sum=0;
    for(long long int i=a;i<=b;i++){
        if(isLucky(i)) sum++;
    }
    cout<<sum<<endl;
    return 0;
}
/*
//第三题 40
bool isexist(vector<vector<char>> array,int x,int y,int pos,string s){
    if(pos == s.size()-1)
        return true;
    if(x<0 && x >= array.size()) return false;
    if(y<0 && y >= array[0].size()) return false;
    for(int i=0;i<array.size();i++){
        for(int j=0;j<array[0].size();j++){
            if(array[i][j] == s[pos]){
                bool isup = isexist(array,x-1,y,pos+1,s);
                bool isdown = isexist(array,x+1,y,pos+1,s);
                bool isleft = isexist(array,x,y-1,pos+1,s);
                bool isright = isexist(array,x,y+1,pos+1,s); 
                if(isup || isdown || isleft || isright){
                    return true;
                }
            }
        }
    }
    return false;
}

int main(){
    int N,M,K;
    cin>>M>>N>>K;
    vector<string> arr(K);
    for(int i=0;i<K;i++){
        cin>>arr[i];
    }
    vector<vector<char>> temp(M,vector<char>(N,0));
    for(int i =0;i<M;i++){
        for(int j=0;i<N;j++){
            cin>>temp[i][j];
        }
    }
    for(int i=0;i<K;i++){
        if(isexist(temp,0,0,0,arr[i]))
            cout<<arr[i]<<endl;
    }
    return 0;
}*/

/*
5 5 3
help
p a b h m
f h e c p
o i l l h
b g h o n
h x c m l
*/
/**
 *第四题：30 
import java.util.Scanner;

public class Main {
    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);
        int n = sc.nextInt();
        int m = sc.nextInt();
        int p = sc.nextInt();
        System.out.println(count(n,m,p));

    }

    public static int sumway(int n, int m, int p, int last) {
        if (n < 0 || m < 0 || p < 0) {
            return 0;
        }
        if (n == 1 && m ==0 && p ==0 && last ==0){
            return 1;
        }
        if (n == 0 && m ==1 && p ==0 && last ==1) {
            return 1;
        }
        if (n == 0 && m ==0 && p ==1 && last ==2){
            return 1;
        }
        if (last == 0) {
            return sumway(n-1, m, p, 1) + sumway(n- 1, m, p, 2);
        }
        if (last == 1) {
            return sumway(n, m - 1, p, 0) + sumway(n, m - 1, p, 2);
        }
        if (last == 2) {
            return sumway(n, m, p - 1, 0) + sumway(n, m, p - 1, 1);
        }
        return 0;
    }


    public static int count(int n, int m,int p) {
        return sumway(n,m, p, 0) + sumway(n, m, p, 1) + sumway(n, m, p, 2);
    }
}
*/
//第一题 AC
/*import java.util.Scanner;
import java.util.Stack;
 
public class Main {
	public static void main(String[] args) {
		Scanner in = new Scanner(System.in);
		String path = in.nextLine();
		
		String simplePath = "";
		Stack<String> stack = new Stack<String>();
		
		for(int i=0;i<path.length();i++){
			String name="";
			
			while(i<path.length() && path.charAt(i)=='/')
				i++;	//该操作跳过斜线'/'
			
			while(i<path.length() && path.charAt(i)!='/')
				name += path.charAt(i++);	//记录路径名，也包括'.'和'。。'
			
			if(!name.equals(".") && !name.equals("..")){
				stack.push(name);
			}
			if(!stack.isEmpty() && name.equals(".."))
				stack.pop();	//如果当前文件名为“..”，表示退到上一层目录，需弹出栈
		}
		if(stack.isEmpty())
			System.out.print("/");
		while(!stack.isEmpty()){
			simplePath = "/"+stack.peek()+simplePath;
			stack.pop();
		}
		System.out.println(simplePath);
	}
}
*/
