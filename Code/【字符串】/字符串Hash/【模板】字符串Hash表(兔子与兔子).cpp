#include<iostream>
#include<string>
#include<cstdio>
#define LL long long
using namespace std;
const int N=1e6+5;
int l1,r1,l2,r2,n,m,i,p=27;
LL f[N],mi[N];string a;
inline LL Hash(int l,int r){return f[r]-f[l-1]*mi[r-l+1];}
int main(){
    cin>>a;n=a.size();a='$'+a;mi[0]=1;
    for(i=1;i<=n;i++)f[i]=f[i-1]*p+a[i]-'a'+1,mi[i]=mi[i-1]*p;
    scanf("%d",&m);
    while(m--){
        scanf("%d%d%d%d",&l1,&r1,&l2,&r2);
        if(Hash(l1,r1)==Hash(l2,r2))printf("Yes\n");
        else printf("No\n");
    }
}
