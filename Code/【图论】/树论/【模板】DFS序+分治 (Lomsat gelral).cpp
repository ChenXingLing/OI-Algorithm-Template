#include<algorithm>
#include<cstring>
#include<cstdio>
#define LL long long
#define Re register int
using namespace std;
const int N=1e5+3;
int o,n,m,x,y,t,tmp,dfn_O,A[N],Q[N],cnt[N],dfn[N],idx[N],size[N],head[N];LL ans,Ans[N];
struct QAQ{int to,next;}a[N<<1];
inline void add(Re x,Re y){a[++o].to=y,a[o].next=head[x],head[x]=o;}
inline void in(Re &x){
    int f=0;x=0;char c=getchar();
    while(c<'0'||c>'9')f|=c=='-',c=getchar();
    while(c>='0'&&c<='9')x=(x<<1)+(x<<3)+(c^48),c=getchar();
    x=f?-x:x;
}
inline void dfs(Re x,Re fa){//Ԥ����dfn��
    idx[dfn[x]=++dfn_O]=x,size[x]=1;
    for(Re i=head[x],to;i;i=a[i].next)
        if((to=a[i].to)!=fa)dfs(to,x),size[x]+=size[to];
}
inline void CL(){//��չ��ף���zero��ʼ
    while(t)cnt[Q[t--]]=0;ans=tmp=0;
}
inline void insert(Re x){//�����x�Ĺ���
    ++cnt[Q[++t]=A[x]];
    if(cnt[A[x]]>tmp)tmp=cnt[ans=A[x]];
    else if(cnt[A[x]]==tmp)ans+=A[x];
}
inline void sakura(Re L,Re R){//���ν��(L,R)
    if(L==R){if(size[idx[L]]==1)Ans[idx[L]]=A[idx[L]];return;}
    Re mid=L+R>>1;
    sakura(L,mid),sakura(mid+1,R);//�ݹ��������
    Re p=mid;CL();//��һ��ָ��p
    for(Re i=mid,j;i>=L&&(j=i+size[idx[i]]-1)<=R;--i){//��j=Rdfn(i)����Rʱ�Ϳ��Խ�����
        insert(idx[i]);
        if(j<=mid)continue;//ֻ�������j>mid�Ĳ���
        while(p<j)insert(idx[++p]);//�����ʿ�֪�������mid���ǲ���j�ǵ��������ģ������ƶ�ָ��p����
        Ans[idx[i]]=ans;//��ô�
    }
}
int main(){
//  freopen("123.txt","r",stdin);
    in(n),m=n-1;
    for(Re i=1;i<=n;++i)in(A[i]);
    while(m--)in(x),in(y),add(x,y),add(y,x);
    dfs(1,0),sakura(1,n);
    for(Re i=1;i<=n;++i)printf("%lld ",Ans[i]);
}
