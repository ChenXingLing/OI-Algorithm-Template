#include<algorithm>
#include<cstring>
#include<cstdio>
#define LL long long
#define Re register int
using namespace std;
const int N=1e5+3;
int o,n,m,x,y,t,K,tmp,A[N],Q[N],cnt[N],son[N],size[N],head[N];LL ans,Ans[N];
struct QAQ{int to,next;}a[N<<1];
inline void add(Re x,Re y){a[++o].to=y,a[o].next=head[x],head[x]=o;}
inline void in(Re &x){
    int f=0;x=0;char c=getchar();
    while(c<'0'||c>'9')f|=c=='-',c=getchar();
    while(c>='0'&&c<='9')x=(x<<1)+(x<<3)+(c^48),c=getchar();
    x=f?-x:x;
}
inline void dfs(Re x,Re fa){//Ԥ�����ض���
	size[x]=1;
	for(Re i=head[x],to;i;i=a[i].next)
		if((to=a[i].to)!=fa){
			dfs(to,x),size[x]+=size[to];
			if(size[to]>size[son[x]])son[x]=to;
		}
}
inline void CL(){//��չ��ף���zero��ʼ
	while(t)cnt[Q[t--]]=0;ans=tmp=0;
}
inline void insert(Re x){//�����x�Ĺ���
	++cnt[Q[++t]=A[x]];
	if(cnt[A[x]]>tmp)tmp=cnt[ans=A[x]];
	else if(cnt[A[x]]==tmp)ans+=A[x];
}
inline void addson(Re x,Re fa){//����subtree(x)�Ĺ��ף���xΪ��������������
	insert(x);
	for(Re i=head[x],to;i;i=a[i].next)
		if((to=a[i].to)!=fa)addson(to,x);
}
inline void sakura(Re x,Re fa){
	for(Re i=head[x],to;i;i=a[i].next)
		if((to=a[i].to)!=fa&&to!=son[x])sakura(to,x),CL();//��������ӵĴ𰸲���չ���
	if(son[x])sakura(son[x],x);//�����ض��ӵĴ𰸲�����subtree(son[x])����son[x]Ϊ���������������ף�
	for(Re i=head[x],to;i;i=a[i].next)
		if((to=a[i].to)!=fa&&to!=son[x])addson(to,x);//����subtree(x)-subtree(son[x])-x����x�����������Ϊ�����������ף�
	insert(x),Ans[x]=ans;//ע�⻹Ҫ��x�Ĺ���Ҳ�ӽ�ȥ
}
int main(){
//	freopen("123.txt","r",stdin);
	in(n),m=n-1;
	for(Re i=1;i<=n;++i)in(A[i]);
	while(m--)in(x),in(y),add(x,y),add(y,x);
	dfs(1,0),sakura(1,0);
	for(Re i=1;i<=n;++i)printf("%lld ",Ans[i]);
}
