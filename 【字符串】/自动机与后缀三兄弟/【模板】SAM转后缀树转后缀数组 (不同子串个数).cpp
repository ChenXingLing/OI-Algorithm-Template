#include<algorithm>
#include<cstring>
#include<cstdio>
#define LL long long
#define Re register int
using namespace std;
const int N=1e5+5;
int n;char s[N];LL ans;
inline void in(Re &x){
    int f=0;x=0;char c=getchar();
    while(c<'0'||c>'9')f|=c=='-',c=getchar();
    while(c>='0'&&c<='9')x=(x<<1)+(x<<3)+(c^48),c=getchar();
    x=f?-x:x;
}
struct Suffix_Array{
	int H[N],SA[N],rank[N],height[N];
	inline void get_height(){
		for(Re i=1;i<=n;++i)rank[SA[i]]=i;
		for(Re i=1,k=0;i<=n;++i){
			if(rank[i]==1)continue;
			if(k)--k;
			Re j=SA[rank[i]-1];
			while(i+k<=n&&j+k<=n&&s[i+k]==s[j+k])++k;
			height[rank[i]]=H[i]=k;
		}
	}
}SA;
int pan[N<<1],pos[N<<1];
struct Suffix_Tree{
	int t,tr[N<<1][26];
	inline void add(Re x,Re y,Re c){tr[x][c]=y;}
	inline void dfs(Re x){
		if(pan[x])SA.SA[++t]=pos[x];
		for(Re i=0;i<26;++i)if(tr[x][i])dfs(tr[x][i]);
	}
}ST;
struct Suffix_Automaton{
	int O,last,link[N<<1],maxlen[N<<1],trans[N<<1][26];
	Suffix_Automaton(){last=O=1;}
	inline void insert(Re ch,Re id){
		Re z=++O,p=last;maxlen[z]=maxlen[p]+1,pan[z]=1,pos[z]=id;
		while(p&&!trans[p][ch])trans[p][ch]=z,p=link[p];
		if(!p)link[z]=1;
		else{
			Re x=trans[p][ch];
			if(maxlen[p]+1==maxlen[x])link[z]=x;
			else{
				Re y=++O;maxlen[y]=maxlen[p]+1;
				for(Re i=0;i<26;++i)trans[y][i]=trans[x][i];
				while(p&&trans[p][ch]==x)trans[p][ch]=y,p=link[p];
				pos[y]=pos[x],link[y]=link[x],link[x]=link[z]=y;//注意pos[y]=pos[x]
			}
		}
		last=z;
	}
	inline void build(){
		for(Re i=n;i>=1;--i)insert(s[i]-'a',i);
		for(Re i=2;i<=O;++i)ST.add(link[i],i,s[pos[i]+maxlen[link[i]]]-'a');//转移边上的ch为子节点的首字母
	}
}SAM;
int main(){
//	freopen("123.txt","r",stdin);
	in(n),scanf("%s",s+1),SAM.build(),ST.dfs(1),SA.get_height();
	for(Re i=1;i<=n;++i)ans+=n-SA.SA[i]+1-SA.height[i];
	printf("%lld\n",ans);
}
