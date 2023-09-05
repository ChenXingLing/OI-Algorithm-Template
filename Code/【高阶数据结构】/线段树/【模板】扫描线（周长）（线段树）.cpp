#include<algorithm>
#include<cstring>
#include<cstdio>
#define y1 yyyy
#define LL long long
#define Re register int
using namespace std;
const int N=5e4+3,M=2e4+3;
int n,m,ans,Max=10000,x1[N],y1[N],x2[N],y2[N];
inline void in(Re &x){
    int f=0;x=0;char c=getchar();
    while(c<'0'||c>'9')f|=c=='-',c=getchar();
    while(c>='0'&&c<='9')x=(x<<1)+(x<<3)+(c^48),c=getchar();
    x=f?-x:x;
}
struct Segment_Tree{
	#define pl (p<<1)
	#define pr (p<<1|1)
	#define mid ((L+R)>>1)
	struct QAQ{int S,cnt;}tr[M<<2];
	inline void pushup(Re p,Re L,Re R){
		if(tr[p].cnt)tr[p].S=R-L+1;
		else tr[p].S=(L==R)?0:tr[pl].S+tr[pr].S;
	}
	inline void change(Re p,Re L,Re R,Re l,Re r,Re v){
		if(l<=L&&R<=r){tr[p].cnt+=v,pushup(p,L,R);return;}
		if(l<=mid)change(pl,L,mid,l,r,v);
		if(r>mid)change(pr,mid+1,R,l,r,v);
		pushup(p,L,R);
	}
}TR1,TR2;
struct Line{
	int x,y1,y2,k;Line(Re X=0,Re Y1=0,Re Y2=0,Re K=0){x=X,y1=Y1,y2=Y2,k=K;}
	inline bool operator<(const Line &O)const{return x!=O.x?x<O.x:k>O.k;}//x相等时必须把添加操作放在前面
}L1[N<<1],L2[N<<1];
int main(){
//	freopen("123.txt","r",stdin);
	in(n);
	for(Re i=1;i<=n;++i)
		in(x1[i]),in(y1[i]),in(x2[i]),in(y2[i]),x1[i]+=Max,y1[i]+=Max,x2[i]+=Max,y2[i]+=Max,
		L1[++m]=Line(x1[i],y1[i],y2[i],1),L2[m]=Line(y1[i],x1[i],x2[i],1),
		L1[++m]=Line(x2[i],y1[i],y2[i],-1),L2[m]=Line(y2[i],x1[i],x2[i],-1);
	sort(L1+1,L1+m+1),sort(L2+1,L2+m+1);
	for(Re i=1,j=0;i<=m;i=j+1){
		Re last=TR1.tr[1].S;
		++j,TR1.change(1,1,Max<<1,L1[j].y1+1,L1[j].y2,L1[j].k);
		while(j+1<=m&&L1[j].x==L1[j+1].x&&L1[j].k==L1[j+1].k)++j,TR1.change(1,1,Max<<1,L1[j].y1+1,L1[j].y2,L1[j].k);
		ans+=abs(last-TR1.tr[1].S);
	}
	for(Re i=1,j=0;i<=m;i=j+1){
		Re last=TR2.tr[1].S;
		++j,TR2.change(1,1,Max<<1,L2[j].y1+1,L2[j].y2,L2[j].k);
		while(j+1<=m&&L2[j].x==L2[j+1].x&&L2[j].k==L2[j+1].k)++j,TR2.change(1,1,Max<<1,L2[j].y1+1,L2[j].y2,L2[j].k);
		ans+=abs(last-TR2.tr[1].S);
	}
	printf("%d\n",ans);
}
