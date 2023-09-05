#include<algorithm>
#include<cstdio>
#include<queue>
#define Re register int
#define LL long long
using namespace std;
const int N=2e6+5;
int n;char ch[N];
inline void in(Re &x){
    int fu=0;x=0;char c=getchar();
    while(c<'0'||c>'9')fu|=c=='-',c=getchar();
    while(c>='0'&&c<='9')x=(x<<1)+(x<<3)+(c^48),c=getchar();
    x=fu?-x:x;
}
struct Suffix_Automaton{
    int O,link[N],maxlen[N],trans[N][26];
    //link[i]: 后缀链接
    //trans[i]: 状态转移数组
    Suffix_Automaton(){O=1;}//根初始化为1
    inline int insert(Re ch,Re last){
        if(trans[last][ch]){
            Re p=last,x=trans[p][ch];
            if(maxlen[p]+1==maxlen[x])return x;//即最初的特判1
            else{
                Re y=++O;maxlen[y]=maxlen[p]+1;
                for(Re i=0;i<26;++i)trans[y][i]=trans[x][i];
                while(p&&trans[p][ch]==x)trans[p][ch]=y,p=link[p];
                link[y]=link[x],link[x]=y;
                return y;//即最初的特判2
            }
        }
        Re z=++O,p=last;maxlen[z]=maxlen[last]+1;
        while(p&&!trans[p][ch])trans[p][ch]=z,p=link[p];
        if(!p)link[z]=1;
        else{
            Re x=trans[p][ch];
            if(maxlen[p]+1==maxlen[x])link[z]=x;
            else{
                Re y=++O;maxlen[y]=maxlen[p]+1;
                for(Re i=0;i<26;++i)trans[y][i]=trans[x][i];
                while(p&&trans[p][ch]==x)trans[p][ch]=y,p=link[p];
                link[y]=link[x],link[z]=link[x]=y;
            }
        }
        return z;
    }
    inline void sakura(){
        LL ans=0;
        for(Re i=2;i<=O;++i)ans+=maxlen[i]-maxlen[link[i]];
        printf("%lld\n",ans);
    }
}SAM;
int main(){
//    freopen("123.txt","r",stdin);
    in(n);
    for(Re i=1;i<=n;++i){
        scanf("%s",ch+1);Re last=1;
        for(Re j=1;ch[j];++j)last=SAM.insert(ch[j]-'a',last);
    }
    SAM.sakura();
}
