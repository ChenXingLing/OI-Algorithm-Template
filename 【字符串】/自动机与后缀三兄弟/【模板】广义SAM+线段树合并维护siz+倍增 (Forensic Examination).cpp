#include<algorithm>
#include<iostream>
#include<cstring>
#include<cstdio>
#include<string>
#define LL long long
#define Re register int
using namespace std;
const int N=5e5+3,M=5e4+3,logN=21;
int n,m,x,y,l,r,T,pos[N];char s[N],ch[M];
inline void in(Re &x){
    int f=0;x=0;char c=getchar();
    while(c<'0'||c>'9')f|=c=='-',c=getchar();
    while(c>='0'&&c<='9')x=(x<<1)+(x<<3)+(c^48),c=getchar();
    x=f?-x:x;
}
struct QWQ{
    int x,id;QWQ(Re X=0,Re ID=0){x=X,id=ID;}
    inline bool operator>(const QWQ &O)const{return x!=O.x?x>O.x:id<O.id;}
};
inline QWQ max(QWQ A,QWQ B){return A>B?A:B;}
int pt[N+M<<1];
struct Segment_Tree{
    #define pl (tr[p].lp)
    #define pr (tr[p].rp)
    #define mid ((L+R)>>1)
    int O;
    struct QAQ{int lp,rp;QWQ ans;}tr[(M<<1)*30];
    inline void pushup(Re p){
        tr[p].ans=max(tr[pl].ans,tr[pr].ans);
    }
    inline void change(Re &p,Re L,Re R,Re x){
        if(!p)p=++O;
        if(L==R){++tr[p].ans.x,tr[p].ans.id=L;return;}
        if(x<=mid)change(pl,L,mid,x);
        else change(pr,mid+1,R,x);
        pushup(p);
    }
    inline int merge(Re p,Re q,Re L,Re R){
        if(!p||!q)return p+q;
        Re x=++O;
        if(L==R){tr[x]=tr[p],tr[x].ans.x+=tr[q].ans.x;return x;}
        tr[x].lp=merge(pl,tr[q].lp,L,mid);
        tr[x].rp=merge(pr,tr[q].rp,mid+1,R);
        pushup(x);return x;
    }
    inline QWQ ask(Re p,Re L,Re R,Re l,Re r){
        if(!p)return QWQ(0,m+1);
        if(l<=L&&R<=r)return tr[p].ans;
        QWQ ans=QWQ(0,m+1);
        if(l<=mid)ans=max(ans,ask(pl,L,mid,l,r));
        if(r>mid)ans=max(ans,ask(pr,mid+1,R,l,r));
        return ans;
    }
}TR;
struct Suffix_Automaton{
    int O,link[N+M<<1],maxlen[N+M<<1],trans[N+M<<1][26];
    Suffix_Automaton(){O=1;}
    inline int insert(Re ch,Re last,Re id){
        if(trans[last][ch]){
            Re p=last,x=trans[p][ch];
            if(maxlen[p]+1==maxlen[x]){if(id)TR.change(pt[x],1,m,id);return x;}
            else{
                Re y=++O;maxlen[y]=maxlen[p]+1;
                for(Re i=0;i<26;++i)trans[y][i]=trans[x][i];
                while(p&&trans[p][ch]==x)trans[p][ch]=y,p=link[p];
                link[y]=link[x],link[x]=y;
                if(id)TR.change(pt[y],1,m,id);
                return y;
            }
        }
        Re z=++O,p=last;maxlen[z]=maxlen[p]+1;
        while(p&&!trans[p][ch])trans[p][ch]=z,p=link[p];
        if(!p)link[z]=1;
        else{
            Re x=trans[p][ch];
            if(maxlen[x]==maxlen[p]+1)link[z]=x;
            else{
                Re y=++O;maxlen[y]=maxlen[p]+1;
                for(Re i=0;i<26;++i)trans[y][i]=trans[x][i];
                while(p&&trans[p][ch]==x)trans[p][ch]=y,p=link[p];
                link[y]=link[x],link[x]=link[z]=y;
            }
        }
        if(id)TR.change(pt[z],1,m,id);
        return z;
    }
    int o,deep[N+M<<1],head[N+M<<1],ant[N+M<<1][23];
    struct QAQ{int to,next;}a[N+M<<1];
    inline void add(Re x,Re y){a[++o].to=y,a[o].next=head[x],head[x]=o;}
    inline void dfs(Re x,Re fa){
        deep[x]=deep[ant[x][0]=fa]+1;
        for(Re i=1;(1<<i)<=deep[x];++i)ant[x][i]=ant[ant[x][i-1]][i-1];
        for(Re i=head[x],to;i;i=a[i].next)
            dfs(to=a[i].to,x),pt[x]=TR.merge(pt[x],pt[to],1,m);
    }
    inline void build(){
        for(Re i=2;i<=O;++i)add(link[i],i);dfs(1,0);
    }
    inline int get(Re x,Re len){
        Re p=pos[x];
        for(Re i=logN;i>=0;--i)if(ant[p][i]&&maxlen[ant[p][i]]>=len)p=ant[p][i];
        return p;
    }
    inline void sakura(Re l,Re r,Re x,Re y){
        QWQ ans=TR.ask(pt[get(y,y-x+1)],1,m,l,r);
        if(ans.x==0)ans.id=l;
        printf("%d %d\n",ans.id,ans.x);
    }
}SAM;
int main(){
//    freopen("123.txt","r",stdin);
    scanf("%s",s+1),n=strlen(s+1),in(m);
    for(Re i=1;i<=m;++i){
        scanf("%s",ch+1);Re last=1;
        for(Re j=1;ch[j];++j)last=SAM.insert(ch[j]-'a',last,i);
    }
    for(Re i=1,last=1;i<=n;++i)pos[i]=last=SAM.insert(s[i]-'a',last,0);
    SAM.build(),in(T);
    while(T--)in(l),in(r),in(x),in(y),SAM.sakura(l,r,x,y);
}
