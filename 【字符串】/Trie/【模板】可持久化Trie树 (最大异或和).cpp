#include<algorithm>
#include<cstring>
#include<cstdio>
#include<cmath>
#define LL long long
#define Re register int
using namespace std;
const int N=6e5+5,logN=24;
int n,x,y,z,T,A[N],pt[N];char op;
inline void in(Re &x){
	Re fu=0;x=0;char ch=getchar();
	while(ch<'0'||ch>'9')fu|=ch=='-',ch=getchar();
	while(ch>='0'&&ch<='9')x=(x<<1)+(x<<3)+(ch^48),ch=getchar();
	x=fu?-x:x;
}
struct Trie{
	int O,cnt[N*(logN+2)],tr[N*(logN+2)][2];
	inline void insert(Re p,Re q,Re o,Re x){
		if(o<0)return;Re i=(x>>o)&1;
		tr[p][i]=++O,tr[p][i^1]=tr[q][i^1];
		cnt[tr[p][i]]=cnt[tr[q][i]]+1;
		insert(tr[p][i],tr[q][i],o-1,x);
	}
	inline int ask(Re p,Re q,Re o,Re x){
		if(o<0)return 0;Re i=(x>>o)&1;
		if(cnt[tr[q][i^1]]>cnt[tr[p][i^1]])return (1<<o)+ask(tr[p][i^1],tr[q][i^1],o-1,x);
		else return ask(tr[p][i],tr[q][i],o-1,x);
	}
}T1;
int main(){
//	freopen("123.txt","r",stdin);
	in(n),in(T);
	for(Re i=1;i<=n;++i)in(A[i]),A[i]^=A[i-1],T1.insert(pt[i]=++T1.O,pt[i-1],logN,A[i]);
	T1.insert(pt[0]=++T1.O,0,logN,0);
	while(T--){
		scanf(" %c",&op),in(x);
		if(op=='A')++n,A[n]=A[n-1]^x,T1.insert(pt[n]=++T1.O,pt[n-1],logN,A[n]);
		else in(y),in(z),--x,--y,printf("%d\n",T1.ask(x?pt[x-1]:0,pt[y],logN,z^A[n]));
	}
}
