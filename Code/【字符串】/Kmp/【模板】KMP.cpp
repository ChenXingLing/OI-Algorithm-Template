#include<iostream>
#include<cstdio>
#include<string>
using namespace std;
int i,j,n,m,next[1000005];string a,b;
int main(){
	cin>>a>>b;
	n=a.size();a='$'+a;
	m=b.size();b='$'+b;
	for(i=2,j=0;i<=m;i++){
		while(j&&b[i]!=b[j+1])j=next[j];
		if(b[i]==b[j+1])j++;
		next[i]=j;
	}
	for(i=1,j=0;i<=n;i++){
		while(j&&a[i]!=b[j+1])j=next[j];
		if(a[i]==b[j+1])j++;
		if(j==m){j=next[j];printf("%d\n",i-m+1);}
	}
	for(i=1;i<=m;i++)printf("%d ",next[i]);
}
