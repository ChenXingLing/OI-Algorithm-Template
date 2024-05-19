#include<algorithm>
#include<cstdio>
#include<queue>
#define Re register int
#define LL long long
using namespace std;
const int N=2e6+5,M=1e6+3;
int n,t;char ch[N];
inline void in(Re &x){
    int fu=0;x=0;char c=getchar();
    while(c<'0'||c>'9')fu|=c=='-',c=getchar();
    while(c>='0'&&c<='9')x=(x<<1)+(x<<3)+(c^48),c=getchar();
    x=fu?-x:x;
}
struct Trie{
    int O,c[M],fa[M],tr[M][26];
    //fa[x]: Trie树上x的父节点
    //c[x]: Trie树上x的颜色
    Trie(){O=1;}//根初始化为1
    inline void insert(char ch[]){
        Re p=1;
        for(Re i=1;ch[i];++i){
            Re a=ch[i]-'a';
            if(!tr[p][a])tr[p][a]=++O,fa[O]=p,c[O]=a;
            p=tr[p][a];
        }
    }
}T1;
struct Suffix_Automaton{
    int O,pos[N],link[N],maxlen[N],trans[N][26];queue<int>Q;
    //pos[x]:Trie上的x节点（路径1->x所表示的字符串）在SAM上的对应节点编号
    //link[i]: 后缀链接
    //trans[i]: 状态转移数组
    Suffix_Automaton(){O=1;}//根初始化为1
    inline int insert(Re ch,Re last){//普通SAM添加特判2 
        if(trans[last][ch]){//不存在特判1的情况 
            Re p=last,x=trans[p][ch];
            Re y=++O;maxlen[y]=maxlen[p]+1;
            for(Re i=0;i<26;++i)trans[y][i]=trans[x][i];
            while(p&&trans[p][ch]==x)trans[p][ch]=y,p=link[p];
            link[y]=link[x],link[x]=y;
            return y;//即最初的特判2
        }
        Re x,y,z=++O,p=last;maxlen[z]=maxlen[last]+1;
        while(p&&!trans[p][ch])trans[p][ch]=z,p=link[p];
        if(!p)link[z]=1;
        else{
            x=trans[p][ch];
            if(maxlen[p]+1==maxlen[x])link[z]=x;
            else{
                y=++O;maxlen[y]=maxlen[p]+1;
                for(Re i=0;i<26;++i)trans[y][i]=trans[x][i];
                while(p&&trans[p][ch]==x)trans[p][ch]=y,p=link[p];
                link[y]=link[x],link[z]=link[x]=y;
            }
        }
        return z;
    }
    inline void dfs(Re x){
		for(Re i=0,to;i<26;++i)if(to=T1.tr[x][i])
			pos[to]=insert(T1.c[to],pos[x]),dfs(to);
	}
    inline void build(){pos[1]=1,dfs(1);}//dfs遍历Trie树构造广义SAM(Tire树上的根1在SAM上的位置为根1)
    inline void sakura(){
        LL ans=0;
        for(Re i=2;i<=O;++i)ans+=maxlen[i]-maxlen[link[i]];
        printf("%lld\n",ans);
    }
}SAM;
int main(){
//    freopen("123.txt","r",stdin);
    in(n);
    for(Re i=1;i<=n;++i)scanf("%s",ch+1),T1.insert(ch);
    SAM.build(),SAM.sakura();
}
