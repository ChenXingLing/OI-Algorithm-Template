#include<cstdio>
#include<iostream> 
using namespace std;//有向图最小环 
int minn=0x7fffff,n,f[200005],d[200005];
inline int min(int a,int b){if(a>b) return b;else return a;}

inline int find(int x){
	if(f[x]!=x){
		int l=f[x];
		f[x]=find(f[x]);
		d[x]+=d[l];
	}
	return f[x];
}

inline void sakura(int a,int b){
	int aa=find(a);int bb=find(b);
	if(aa!=bb){
		f[aa]=bb;
		d[a]=d[b]+1;
	}
	else
		minn=min(minn,d[a]+d[b]+1);
}

int main(){
	scanf("%d",&n);
	for(int i=1;i<=n;i++) f[i]=i;
	for(int i=1;i<=n;i++){
		int x;
		scanf("%d",&x);
		sakura(i,x);
	}
	printf("%d",minn);
	return 0;
}

