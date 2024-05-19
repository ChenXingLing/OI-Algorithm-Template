#include<algorithm>
#include<cstdio>
#include<queue>
#define Re register int
#define LL long long
using namespace std;
const int N=8e5+5;
char ch[200003];LL ans;
inline void in(Re &x){
    int fu=0;x=0;char c=getchar();
    while(c<'0'||c>'9')fu|=c=='-',c=getchar();
    while(c>='0'&&c<='9')x=(x<<1)+(x<<3)+(c^48),c=getchar();
    x=fu?-x:x;
}
struct Suffix_Automaton{
    int O,ru[N],link[N],maxlen[N],siz[N][2],trans[N][26];queue<int>Q;
    //siz[x]: |endpos[x]| 即节点x的endpos大小
    Suffix_Automaton(){O=1;}
    inline int insert(Re ch,Re last,Re id){
        if(trans[last][ch]){
            Re p=last,x=trans[p][ch];
            if(maxlen[p]+1==maxlen[x]){siz[x][id]=1;return x;} 
            else{
                Re y=++O;maxlen[y]=maxlen[p]+1;
                for(Re i=0;i<26;++i)trans[y][i]=trans[x][i];
                while(p&&trans[p][ch]==x)trans[p][ch]=y,p=link[p];
                link[y]=link[x],link[x]=y;
                siz[y][id]=1;return y;
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
        siz[z][id]=1;
        return z;
    }
    inline void sakura(){
        for(Re i=2;i<=O;++i)++ru[link[i]];
        for(Re i=1;i<=O;++i)if(!ru[i])Q.push(i);
        while(!Q.empty()){
            Re x=Q.front();Q.pop();
            siz[link[x]][0]+=siz[x][0];//分开更新
            siz[link[x]][1]+=siz[x][1];
            if(!(--ru[link[x]]))Q.push(link[x]);
        }
        for(Re i=2;i<=O;++i)//统计答案
            ans+=(LL)siz[i][0]*siz[i][1]*(maxlen[i]-maxlen[link[i]]);
        printf("%lld\n",ans);
    }
}SAM;
int main(){
//    freopen("123.txt","r",stdin);
    for(Re i=0;i<2;++i){
        scanf("%s",ch+1);Re last=1;
        for(Re j=1;ch[j];++j)last=SAM.insert(ch[j]-'a',last,i);
    }
    SAM.sakura();
}
