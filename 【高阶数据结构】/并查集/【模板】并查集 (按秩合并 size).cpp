#include<algorithm>
#include<cstdio>
#define Re register int
const int N=1e4+3;
int n,x,y,T,op,fa[N],size[N],deep[N];
inline void in(Re &x){
    int f=0;x=0;char c=getchar();
    while(c<'0'||c>'9')f|=c=='-',c=getchar();
    while(c>='0'&&c<='9')x=(x<<1)+(x<<3)+(c^48),c=getchar();
    x=f?-x:x;
}
inline int find(Re x){return x==fa[x]?x:find(fa[x]);}
inline void merge(Re x,Re y){
	x=find(x),y=find(y);
	if(x==y)return;
	if(size[x]>size[y])std::swap(x,y);
	fa[x]=y,size[y]+=size[x];
}
int main(){
	in(n),in(T);
	for(Re i=1;i<=n;++i)fa[i]=i,size[i]=1;
	while(T--){
		in(op),in(x),in(y);
		if(op<2)merge(x,y);
		else puts(find(x)==find(y)?"Y":"N");
	}
}
