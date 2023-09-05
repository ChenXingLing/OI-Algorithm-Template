#include<iostream>
#include<cstring>
#include<cstdio>
#include<cctype>
#define LL long long
using namespace std;
int n,f,t1,t2,i,power[300],ch[40];
LL x,sum[40];string a;
LL mi(LL x,LL k){
    LL s=1;
    while(k){
        if(k&1)s=(s*x);
        x=(x*x);k>>=1;
    }
    return s;
}
inline void pop(char fh){
    t1--;t2--;
    if(fh=='+')sum[t1]+=sum[t1+1];
    if(fh=='-')sum[t1]-=sum[t1+1];
    if(fh=='*')sum[t1]*=sum[t1+1];
    if(fh=='/')sum[t1]/=sum[t1+1];
    if(fh=='^')sum[t1]=mi(sum[t1],sum[t1+1]);
}
int main(){
    cin>>a;a='('+a+')';n=a.size();
    power['(']=0;power['+']=power['-']=1;power['*']=power['/']=2;power['^']=3;
    while(i<n){
        x=0,f=0;
        while(isdigit(a[i]))x=x*10+a[i++]-'0',f=1;
        if(f)sum[++t1]=x;
        if(a[i]=='(')ch[++t2]=a[i++];
        if(a[i]==')'){
            while(ch[t2]!='(')pop(ch[t2]);
            i++;t2--;
        }
        if(power[a[i]]){
            if(a[i]=='-'&&a[i-1]=='('){
                x=0,i++;
                while(isdigit(a[i]))x=x*10+a[i++]-'0';
                sum[++t1]=-x;
            }
            else {
                while(power[a[i]]<=power[ch[t2]])pop(ch[t2]);
                ch[++t2]=a[i++];
            }
        }
    }
    while(t2)pop(ch[t2]);
    printf("%lld",sum[1]);
}
