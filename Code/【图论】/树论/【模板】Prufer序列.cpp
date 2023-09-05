#include<algorithm>
#include<cstring>
#include<cstdio>
#define LL long long
#define Re register int
using namespace std;
const int N=5e6+3;
int n,op,fa[N],pf[N],son[N];LL ans;
inline void in(Re &x){
    int f=0;x=0;char c=getchar();
    while(c<'0'||c>'9')f|=c=='-',c=getchar();
    while(c>='0'&&c<='9')x=(x<<1)+(x<<3)+(c^48),c=getchar();
    x=f?-x:x;
}
inline LL get_prufer(){
	for(Re i=1;i<=n-1;++i)in(fa[i]),++son[fa[i]];
	for(Re i=1,j=1;i<=n-2;++i,++j){
		while(son[j])++j;pf[i]=fa[j];
		while(i<=n-2&&!--son[pf[i]]&&pf[i]<j)pf[i+1]=fa[pf[i]],++i;
	}
//	printf("Prufer: ");for(Re i=1;i<=n-2;++i)printf("%d ",pf[i]);puts("");
	for(Re i=1;i<=n-2;++i)ans^=(LL)i*pf[i];
	return ans;
}
inline LL get_fa(){
	for(Re i=1;i<=n-2;++i)in(pf[i]),++son[pf[i]];pf[n-1]=n;
	for(Re i=1,j=1;i<=n-1;++i,++j){
		while(son[j])++j;fa[j]=pf[i];
		while(i<=n-1&&!--son[pf[i]]&&pf[i]<j)fa[pf[i]]=pf[i+1],++i;
	}
//	printf("fa: ");for(Re i=1;i<=n-1;++i)printf("%d ",fa[i]);puts("");
	for(Re i=1;i<=n-1;++i)ans^=(LL)i*fa[i];
	return ans;
}
int main(){
//	freopen("123.txt","r",stdin);
	in(n),in(op),printf("%lld\n",op<2?get_prufer():get_fa());
}
