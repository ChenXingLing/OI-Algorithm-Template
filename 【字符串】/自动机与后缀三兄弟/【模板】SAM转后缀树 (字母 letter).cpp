#include<algorithm>
#include<cstring>
#include<cstdio>
#define LL long long
#define Re register int
using namespace std;
const int N=4e5+10;
int n,x,y,T;LL P,M,G,K;char s[N>>1];
inline void in(Re &x){
    int f=0;x=0;char c=getchar();
    while(c<'0'||c>'9')f|=c=='-',c=getchar();
    while(c>='0'&&c<='9')x=(x<<1)+(x<<3)+(c^48),c=getchar();
    x=f?-x:x;
}
struct Sakura2{
    int O,last,pos[N],siz[N],link[N],maxlen[N],trans[N][26];
    //siz[x]: 节点x的出现次数 (endpos的大小)
    //link[x]: x在parent树上的父亲
    //pos[x]: 节点x某一次出现位置 (用于构建后缀树中的压缩边link[x]->x），
    ///翻转后的s中 倒序遍历pos[x]-maxlen[link[x]] -> pos[x]-maxlen[x]+1得到的字符串 即为后缀树中的压缩边 link[x]->x
    inline void insert(Re ch,Re id){//SAM新建节点
        Re z=++O,p=last;pos[z]=id,siz[z]=1,maxlen[z]=maxlen[last]+1;
        while(p&&!trans[p][ch])trans[p][ch]=z,p=link[p];
        if(!p)link[z]=1;
        else{
            Re x=trans[p][ch];
            if(maxlen[p]+1==maxlen[x])link[z]=x;
            else{
                Re y=++O;maxlen[y]=maxlen[p]+1,pos[y]=pos[x];
                for(Re i=0;i<26;++i)trans[y][i]=trans[x][i];
                while(p&&trans[p][ch]==x)trans[p][ch]=y,p=link[p];
                link[y]=link[x],link[z]=link[x]=y;
            }
        }
        last=z;
    }
    int t,ID[N],to[N][26];LL S[N];
    //to[x][ch]: 后缀树的trans数组
    //ID[x]: 顺序遍历后缀树的第x个节点编号 
    //S[x]: 顺序遍历后缀树的前x个节点总共代表了多少个字符
    inline void dfs1(Re x){//遍历 SAM的parent树\后缀树 获取siz
        for(Re i=0;i<26;++i)
            if(to[x][i])dfs1(to[x][i]),siz[x]+=siz[to[x][i]];
    }
    inline void dfs2(Re x){//遍历 SAM的parent树\后缀树 获取节点顺序
        if(x!=1)ID[++t]=x;//没有储存信息的根节点1就不要了
        for(Re i=0;i<26;++i)if(to[x][i])dfs2(to[x][i]);
    }
    inline LL calc(Re L,Re R){return 1ll*(L+R)*(R-L+1)/2;}//计算从L加到R的等差数列 
    inline void build(){
        last=O=1;//根节点设为1
        for(Re i=1;i<=n/2;++i)swap(s[i],s[n-i+1]);//翻转原字符串
        for(Re i=1;i<=n;++i)insert(s[i]-'a',i);
        for(Re i=2;i<=O;++i)to[link[i]][s[pos[i]-maxlen[link[i]]]-'a']=i;//构建后缀树。
        //由于pos[x]是endpos[x]中的任意一个，所以获取边link[x]->x压缩掉的字符串信息时只能用pos[x]，不能用pos[link[x]]
        dfs1(1),dfs2(1);//遍历 SAM的parent树\后缀树
        for(Re i=1;i<=t;++i)x=ID[i],S[i]=S[i-1]+1ll*siz[x]*calc(maxlen[link[x]]+1,maxlen[x]);
    }
    inline char ask(LL K){
        Re l=1,r=t,x;
        while(l<r){//二分找到第一个大于等于K的位置
            Re mid=l+r>>1;
            if(S[mid]<K)l=mid+1;
            else r=mid;
        }
        x=ID[l],K-=S[l-1],l=maxlen[link[x]]+1,r=maxlen[x];
        while(l<r){//二分找到第一个大于等于K的位置
            Re mid=l+r>>1;
            if(1ll*siz[x]*calc(maxlen[link[x]]+1,mid)<K)l=mid+1;
            else r=mid;
        }
        K-=1ll*siz[x]*calc(maxlen[link[x]]+1,l-1),K=(K-1)%l+1;//注意取模的方式 
        return s[pos[x]-K+1];//注意方向：往左数第K位
    }
    char ans;
    inline void sakura(){
        build();
        while(T--)scanf("%lld%lld",&P,&M),K=P*G%M+1,G+=(ans=ask(K)),putchar(ans),puts("");
    }
}T2;
int main(){
    freopen("letter.in","r",stdin);
    freopen("letter.out","w",stdout);
    scanf("%s",s+1),n=strlen(s+1);in(T);
    T2.sakura();
    fclose(stdin);
    fclose(stdout);
}
