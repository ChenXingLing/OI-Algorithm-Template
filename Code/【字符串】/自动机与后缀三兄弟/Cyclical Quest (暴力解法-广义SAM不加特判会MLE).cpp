#include<algorithm>
#include<cstring>
#include<cstdio>
#include<vector>
#include<map>
#define LL long long
#define Re register int
using namespace std;
const int N=3e6+5,M=1e6+3,logN=21;
int n,T,len[M],vis[N<<1],tmp[N<<1];LL ans;char s[M];
inline void in(Re &x){
    int f=0;x=0;char c=getchar();
    while(c<'0'||c>'9')f|=c=='-',c=getchar();
    while(c>='0'&&c<='9')x=(x<<1)+(x<<3)+(c^48),c=getchar();
    x=f?-x:x;
}
vector<int>Q[M];
struct Suffix_Automaton{
	int O,last,siz[N<<1],link[N<<1],maxlen[N<<1];map<int,int>trans[N<<1];
	Suffix_Automaton(){O=1;}
	inline int insert(Re ch,Re op,Re last){
		if(trans[last].find(ch)!=trans[last].end()){
			Re p=last,x=trans[p][ch];
            if(maxlen[p]+1==maxlen[x])return x;
            else{
                Re y=++O;maxlen[y]=maxlen[p]+1;
                for(map<int,int>::iterator it=trans[x].begin();it!=trans[x].end();++it)trans[y].insert(*it);
                while(p&&trans[p][ch]==x)trans[p][ch]=y,p=link[p];
                link[y]=link[x],link[x]=y;
                return y;
            }
		}
		Re z=++O,p=last;if(op)siz[z]=1;maxlen[z]=maxlen[p]+1;
		while(p&&trans[p].find(ch)==trans[p].end())trans[p][ch]=z,p=link[p];
		if(!p)link[z]=1;
		else{
			Re x=trans[p][ch];
			if(maxlen[x]==maxlen[p]+1)link[z]=x;
			else{
				Re y=++O;maxlen[y]=maxlen[p]+1;
				for(map<int,int>::iterator it=trans[x].begin();it!=trans[x].end();++it)trans[y].insert(*it);
				while(p&&trans[p][ch]==x)trans[p][ch]=y,p=link[p];
				link[y]=link[x],link[x]=link[z]=y;
			}
		}
		return z;
	}
	int o,head[N<<1];
	struct QAQ{int to,next;}a[N<<1];
	inline void add(Re x,Re y){a[++o].to=y,a[o].next=head[x],head[x]=o;}
	inline void dfs(Re x){
		for(Re i=head[x];i;i=a[i].next)dfs(a[i].to),siz[x]+=siz[a[i].to];
	}
	inline void build(){
		for(Re i=2;i<=O;++i)add(link[i],i);dfs(1);
	}
	inline int ask(Re p,Re len){
		while(maxlen[link[p]]>=len)p=link[p];return p;
	}
}SAM;
int main(){
//    freopen("123.txt","r",stdin);
    scanf("%s",s+1),n=strlen(s+1),in(T);
    for(Re i=1,last=1;s[i];++i)last=SAM.insert(s[i]-'a',1,last);
    for(Re i=1;i<=T;++i){
    	scanf("%s",s+1),len[i]=strlen(s+1);Re last=1;
    	for(Re j=1;j<len[i];++j)last=SAM.insert(s[j]-'a',0,last);
    	Q[i].push_back(last=SAM.insert(s[len[i]]-'a',0,last));
    	for(Re j=1;j<len[i];++j)Q[i].push_back(last=SAM.insert(s[j]-'a',0,last));
	}
	SAM.build();
    for(Re i=1;i<=T;++i){
    	tmp[0]=ans=0;
    	for(Re j=0,SZ=Q[i].size();j<SZ;++j){
    		Re x=SAM.ask(Q[i][j],len[i]);
    		if(vis[x])continue;
    		tmp[++tmp[0]]=x,vis[x]=1,ans+=SAM.siz[x];
		}
		for(Re j=1;j<=tmp[0];++j)vis[tmp[j]]=0;
		printf("%lld\n",ans);
	}
}
