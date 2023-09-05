#include<algorithm>
#include<cstring>
#include<cstdio>
#define Mat Matrix
#define LL long long
#define Re register int
using namespace std;
const int N=1e5+3;
const LL inf=1e18;
int n,m,o,x,y,T,A[N],head[N];
struct QAQ{int to,next;}a[N<<1];
inline void add(Re x,Re y){a[++o].to=y,a[o].next=head[x],head[x]=o;}
inline void in(Re &x){
    int f=0;x=0;char c=getchar();
    while(c<'0'||c>'9')f|=c=='-',c=getchar();
    while(c>='0'&&c<='9')x=(x<<1)+(x<<3)+(c^48),c=getchar();
    x=f?-x:x;
}
struct Matrix{
	LL a[3][3];Mat(){a[1][1]=a[1][2]=a[2][1]=a[2][2]=-inf;}
	inline Mat operator*(const Mat &O)const{
		Mat A;
		for(Re i=1;i<=2;++i)
			for(Re j=1;j<=2;++j)
				for(Re k=1;k<=2;++k)
					A.a[i][j]=max(A.a[i][j],a[i][k]+O.a[k][j]);
		return A;
	}
}G[N];
int idx[N];
struct killed_Tree{
	struct Segment_Tree{
		#define pl (p<<1)
		#define pr (p<<1|1)
		#define mid ((L+R)>>1)
		Mat tr[N<<2];
		inline void pushup(Re p){tr[p]=tr[pl]*tr[pr];}
		inline void build(Re p,Re L,Re R){
			if(L==R){tr[p]=G[idx[L]];return;}
			build(pl,L,mid),build(pr,mid+1,R);
			pushup(p);
		}
		inline void change(Re p,Re L,Re R,Re x,Mat &v){
			if(L==R){tr[p]=v;return;}
			if(x<=mid)change(pl,L,mid,x,v);
			else change(pr,mid+1,R,x,v);
			pushup(p);
		}
		inline Mat ask(Re p,Re L,Re R,Re l,Re r){
			if(l<=L&&R<=r)return tr[p];
			if(r<=mid)return ask(pl,L,mid,l,r);
			else if(l>mid)return ask(pr,mid+1,R,l,r);
			else return ask(pl,L,mid,l,r)*ask(pr,mid+1,R,l,r);
		}
	}TR;
	int id_O,fa[N],st[N],ed[N],son[N],top[N],deep[N],size[N];LL f[N][2],g[N][2];
	inline void dfs1(Re x,Re Fa){
		deep[x]=deep[fa[x]=Fa]+1,size[x]=1;
		for(Re i=head[x],to;i;i=a[i].next)
			if((to=a[i].to)!=Fa){
				dfs1(to,x),size[x]+=size[to];
				if(size[to]>size[son[x]])son[x]=to;
			}
	}
	inline void dfs2(Re x,Re rt){//������ʱ˳�ְѳ�ʼ�Ĵ�����f,g�����
		idx[st[x]=++id_O]=x,ed[rt]=max(ed[rt],id_O),top[x]=rt;
		f[x][0]=g[x][0]=0,f[x][1]=g[x][1]=A[x];//f:�������ж��ӵĴ𰸡�g:ֻ��������ӵĴ𰸡�
		if(son[x])dfs2(son[x],rt),f[x][0]+=max(f[son[x]][0],f[son[x]][1]),f[x][1]+=f[son[x]][0];
		for(Re i=head[x],to;i;i=a[i].next)
			if((to=a[i].to)!=fa[x]&&to!=son[x]){
				dfs2(to,to);
				f[x][0]+=max(f[to][0],f[to][1]),f[x][1]+=f[to][0];
				g[x][0]+=max(f[to][0],f[to][1]),g[x][1]+=f[to][0];
			}
		G[x].a[1][1]=G[x].a[1][2]=g[x][0];
		G[x].a[2][1]=g[x][1],G[x].a[2][2]=-inf;
	}
	inline LL ask(){Mat F=TR.ask(1,1,n,st[1],ed[1]);return max(F.a[1][1],F.a[2][1]);}//ѯ�ʴ�(ע������ȡminʱӦ���ǿ�F�е����������G����עF�İڷ�λ��Ӧ����Ҷ�ӽڵ㴦��G�ж�Ӧֵ��ͬ)
	inline void change(Re x,Re v){//�޸�x�ĵ�Ȩ
		G[x].a[2][1]+=v-A[x],A[x]=v;//�޸�G[x][1]
		while(x){
			Mat F1=TR.ask(1,1,n,st[top[x]],ed[top[x]]);//�������޸�֮ǰ��f����
			TR.change(1,1,n,st[x],G[x]);//�޸ĵ�x��G
			Mat F2=TR.ask(1,1,n,st[top[x]],ed[top[x]]);//�������޸�֮���f����
			x=fa[top[x]];//������һ����
			G[x].a[1][1]+=max(F2.a[1][1],F2.a[2][1])-max(F1.a[1][1],F1.a[2][1]),G[x].a[1][2]=G[x].a[1][1];
			G[x].a[2][1]+=F2.a[1][1]-F1.a[1][1];//����ת�Ʒ��̽��и���
		}
	}
}T1;
int main(){
//	freopen("123.txt","r",stdin);
	in(n),in(T),m=n-1;
	for(Re i=1;i<=n;++i)in(A[i]);
	while(m--)in(x),in(y),add(x,y),add(y,x);
	T1.dfs1(1,0),T1.dfs2(1,1),T1.TR.build(1,1,n);
	while(T--)in(x),in(y),T1.change(x,y),printf("%lld\n",T1.ask());
}
