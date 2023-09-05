#include<algorithm>
#include<cstring>
#include<cstdio>
#include<vector>
#define LL long long
#define Re register int
using namespace std;
const int N=1e5+3,inf=2e9,logN=17;
int n,m,o,x,y,T,op,lastans,A[N],head[N];
struct QAQ{int to,next;}a[N<<1];
inline void add(Re x,Re y){a[++o].to=y,a[o].next=head[x],head[x]=o;}
inline void in(Re &x){
    int f=0;x=0;char c=getchar();
    while(c<'0'||c>'9')f|=c=='-',c=getchar();
    while(c>='0'&&c<='9')x=(x<<1)+(x<<3)+(c^48),c=getchar();
    x=f?-x:x;
}
struct BIT{
	int n;vector<int>C;
	inline void build(Re N){C.resize((n=N)+1);}//ʹ�õ�������Ϊn,�ռ俪n+1
	inline void add(Re x,Re v){++x;while(x<=n)C[x]+=v,x+=x&-x;}//����dis����Ϊ0,������BIT����ͳ�������һλ����ѯͬ��
	inline int ask(Re x){++x,x=min(x,n);Re ans=0;while(x)ans+=C[x],x-=x&-x;return ans;}//ע��Ҫ��ά�����Ͻ�ȡ��Сֵ����ֹԽ��
}TR1[N],TR2[N];
int rt,sum,gs[N],vis[N],maxp[N],size[N],frt[N][20],fdis[N][20];
inline void getrt(Re x,Re fa){//��ȡ����ͨ�������
	size[x]=1,maxp[x]=0;
	for(Re i=head[x],to;i;i=a[i].next)
		if(!vis[to=a[i].to]&&to!=fa)
			getrt(to,x),size[x]+=size[to],maxp[x]=max(maxp[x],size[to]);
	maxp[x]=max(maxp[x],sum-size[x]);
	if(maxp[x]<maxp[rt])rt=x;
}
inline void getdis(Re x,Re rt,Re fa,Re d){//��������ͨ��Ԥ����dis
	frt[x][++gs[x]]=rt,fdis[x][gs[x]]=d;//˳�ְ�����Ҳ������������һ�����
	for(Re i=head[x],to;i;i=a[i].next)
		if(!vis[to=a[i].to]&&to!=fa)getdis(to,rt,x,d+1);
}
inline void sakura(Re x){//��������x����������ͨ��
	Re now=sum;vis[x]=1,getdis(x,x,0,0);
	TR1[x].build(now/2+1),TR2[x].build(now+1);//���������ʿ�֪,TR1��ʹ��[0,now/2],TR2��ʹ��[1,now]�������һλ��Ϊ[1,now/2+1]��[2,now+1]
	for(Re i=head[x],to;i;i=a[i].next)
		if(!vis[to=a[i].to])
			sum=size[to]>size[x]?now-size[x]:size[to],maxp[rt=0]=inf,getrt(to,0),sakura(rt);//ע������ͨ���С��Ҫֱ����size[to]
}
inline void change(Re x,Re v){
	TR1[x].add(0,v);//subtree(x)
	for(Re i=gs[x];i>=2;--i){//ע��Ҫ����ö��
		Re tmp=fdis[x][i-1];
		TR1[frt[x][i-1]].add(tmp,v);
		TR2[frt[x][i]].add(tmp,v);
	}
}
inline int ask(Re x,Re K){
	Re ans=TR1[x].ask(K);//subtree(x)
	for(Re i=gs[x];i>=2;--i){//ע��Ҫ����ö��
		Re tmp=fdis[x][i-1];if(tmp>K)continue;
		ans+=TR1[frt[x][i-1]].ask(K-tmp);
		ans-=TR2[frt[x][i]].ask(K-tmp);
	}
	return ans;
}
int main(){
//	freopen("123.txt","r",stdin);
	in(n),in(T),m=n-1;
	for(Re i=1;i<=n;++i)in(A[i]);
	while(m--)in(x),in(y),add(x,y),add(y,x);
	sum=n,maxp[rt=0]=inf,getrt(1,0),sakura(rt);
	for(Re i=1;i<=n;++i)change(i,A[i]);
	while(T--){
		in(op),in(x),in(y),x^=lastans,y^=lastans;
		if(op)change(x,y-A[x]),A[x]=y;
		else printf("%d\n",lastans=ask(x,y));
	}
}
