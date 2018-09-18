#include <iostream>
#include <vector>
#include <numeric>
#include <limits>
#include <string.h>   
#include <set>
#include <algorithm>
#include <map>

using namespace std;

int main(){
    string str;
    cin>>str;
    char*s=(char*)str.data();
	char* delim = " ";
	char* tmp;
	tmp = strtok(s, delim);
    vector<string> vec;
	while(tmp != NULL)
	{	
		printf("%s\n",tmp);
        vec.push_back(tmp);
		tmp = strtok(NULL, delim);	
	}
    return 0;  
}