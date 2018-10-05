#include <bits/stdc++.h>


int myatoi(const char* str) {
    int n = 0;
    char sign;
    int c;
 
    while (isspace(*str))
        ++str;
 
    sign = *str;
    if (sign == '+' || sign == '-')
        ++str;
    while (isdigit(*str))
    {
        c = *str - '0';
//先用n与MAX/10进行比较: 若n>MAX/10(还要考虑n=MAX/10的情况), 说明将要溢出了
//提高溢出处理的健壮性,除法代替乘法
        if (sign != '-' && (n > INT_MAX/10 || (n == INT_MAX/10 && c >= INT_MAX%10)))
        {
            return INT_MAX;
        }
        else if (sign == '-' && (n > (unsigned)INT_MIN/10 
                              || (n == (unsigned)INT_MIN/10 && c >= (unsigned)INT_MIN%10)))
        {
            return INT_MIN;
        }
        n = n * 10 + c;
        ++str;
    }
    return sign == '-' ? -n : n;
}
