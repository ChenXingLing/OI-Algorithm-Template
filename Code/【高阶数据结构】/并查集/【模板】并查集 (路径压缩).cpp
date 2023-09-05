#include<cstdio>
#define Re register int
const int N=1e4+3;
int n,x,y,T,op,fa[N];
inline void in(Re &x){
    int f=0;x=0;char c=getchar();
    while(c<'0'||c>'9')f|=c=='-',c=getchar();
    while(c>='0'&&c<='9')x=(x<<1)+(x<<3)+(c^48),c=getchar();
    x=f?-x:x;
}
inline int find(Re x){return x==fa[x]?x:fa[x]=find(fa[x]);}
int main(){
	in(n),in(T);
	for(Re i=1;i<=n;++i)fa[i]=i;
	while(T--){
		in(op),in(x),in(y);
		if(op<2){if(find(x)!=find(y))fa[find(x)]=find(y);}
		else puts(find(x)==find(y)?"Y":"N");
	}
}
