#include<algorithm>
#include<cstring>
#include<cstdio>
#define LL long long
#define Re register LL
using namespace std;
const LL N=1e4+3;
inline void in(Re &x){
	int f=0;x=0;char ch=getchar();
	while(ch<'0'||ch>'9')f|=ch=='-',ch=getchar();
	while(ch>='0'&&ch<='9')x=(x<<1)+(x<<3)+(ch^48),ch=getchar();
	x=f?-x:x;
}
LL n,m,x,y,t,K,Ans,b[N];
struct QAQ{LL x,y,v;inline bool operator<(const QAQ &O)const{return v<O.v;}}a[N<<3];
struct Point{LL x,y,id;inline bool operator<(const Point &O)const{return x!=O.x?x<O.x:y<O.y;}}P[N];
inline LL Abs(LL a){return a<0?-a:a;}
inline LL Dis(Re x,Re y){return Abs(P[x].x-P[y].x)+Abs(P[x].y-P[y].y);}
struct BIT{
	LL n,C[N],id[N];
	inline void CL(){memset(C,127,sizeof(C));}
	inline void add(Re x,Re v,Re ID){while(x){if(v<C[x])C[x]=v,id[x]=ID;x-=x&-x;}}
	inline LL ask(Re x){Re Min=1e18,ID=0;while(x<=n){if(C[x]<Min)Min=C[x],ID=id[x];x+=x&-x;}return ID;}
}TR;
inline LL find_(Re x){
	Re l=1,r=t;
	while(l<r){
		Re mid=(l+r+1)>>1;
		if(b[mid]<=x)l=mid;
		else r=mid-1;
	}
	return l;
}
LL fa[N];
inline LL find(Re x){return fa[x]==x?x:fa[x]=find(fa[x]);}
inline void kruscal(){
	for(Re O=1;O<=4;++O){
		if(!(O&1))for(Re i=1;i<=n;++i)swap(P[i].x,P[i].y);
		else if(O==3)for(Re i=1;i<=n;++i)P[i].x*=-1;
		sort(P+1,P+n+1);
		for(Re i=1;i<=n;++i)b[i]=P[i].y-P[i].x;
		sort(b+1,b+n+1),t=unique(b+1,b+n+1)-b-1;
		TR.n=t,TR.CL();
		for(Re i=n;i>=1;--i){
			Re I=find_(P[i].y-P[i].x),j=TR.ask(I);
			if(j)a[++m]=(QAQ){P[i].id,P[j].id,Dis(i,j)};
			TR.add(I,P[i].x+P[i].y,i);
		}
	}
	sort(a+1,a+m+1);
	for(Re i=1;i<=n;++i)fa[i]=i;
	for(Re i=1,t=0;i<=m&&t<n-1;++i)if((x=find(a[i].x))!=(y=find(a[i].y))){
		fa[x]=y,Ans+=a[i].v;
		if(++t==K)printf("%lld\n",a[i].v);//输出生成树上第K小的边
	}
}
int main(){
//	freopen("123.txt","r",stdin);
	in(n),in(K),K=n-1-K+1;//把第K大转换为第n-K小
	for(Re i=1;i<=n;++i)in(P[i].x),in(P[i].y),P[i].id=i;
	kruscal();
}
