#include<algorithm>
#include<cstdio>
#include<map>
#define R register int
#define uLL long long
int n,t,p=13333331,re,A[13];
std::map<uLL,int>pan;
inline int sakura(int a[]){
    R i=1,j=2,k;
    while(i<=6&&j<=6){
        k=0;
        while(k<6&&a[i+k]==a[j+k])++k;
        if(k==6)break;
        if(a[i+k]>a[j+k]){i+=k+1;if(i==j)++i;}
        else{j+=k+1;if(i==j)++j;}
    }
    return i<j?i:j;
}
inline uLL Hash(int a[],int st){
    R i=0;uLL x=0;
    for(;i<6;++i)x=x*p+(uLL)a[st+i];
    return x;
}
inline uLL find(int a[]){
    R x,y,i=1,k=0,b[13];
    for(;i<=6;i++)b[i]=a[7-i];
    for(i=1;i<=6;i++)a[i+6]=a[i],b[i+6]=b[i];
	x=sakura(a),y=sakura(b);
    for(i=0;i<6;i++)
		if(a[x+i]<b[y+i])return Hash(a,x);
		else if(a[x+i]>b[y+i])return Hash(b,y);
    return Hash(a,x);
}
int main(){
    scanf("%d",&n);R i,j;
    for(i=1;i<=n;i++){
        for(j=1;j<=6;j++)scanf("%d",&A[j]);
        uLL re=find(A);
        if(pan[re]){printf("Twin snowflakes found.");return 0;}
    	pan[re]=1;
	}
    printf("No two snowflakes are alike.");
}
