#include<algorithm>
#include<cstring>
#include<cstdio>
#define LL long long
#define Re register int
using namespace std;
const int N=1e5+3,logN=17;
inline void in(Re &x){
    int f=0;x=0;char c=getchar();
    while(c<'0'||c>'9')f|=c=='-',c=getchar();
    while(c>='0'&&c<='9')x=(x<<1)+(x<<3)+(c^48),c=getchar();
    x=f?-x:x;
}
int n,x,y,T,lg[N],f[N][logN+1];
inline int ask(Re l,Re r){
	Re k=lg[r-l+1];
	return max(f[l][k],f[r-(1<<k)+1][k]);
}
int main(){
//	freopen("123.txt","r",stdin);
	in(n),in(T),lg[1]=0;
	for(Re i=2;i<=n;i++)lg[i]=lg[i>>1]+1;//‘§¥¶¿Ìlog÷µ 
	for(Re i=1;i<=n;++i)in(f[i][0]);
	for(Re p=1;p<=lg[n];++p)
		for(Re i=1;i+(1<<p)-1<=n;++i)
			f[i][p]=max(f[i][p-1],f[i+(1<<p-1)][p-1]);
	while(T--)in(x),in(y),printf("%d\n",ask(x,y));
}
