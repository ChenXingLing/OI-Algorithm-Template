#include<algorithm>
#include<cstring>
#include<cstdio>
#define LL long long
#define Re register int
using namespace std;
const int N=6e5+5,logN=19;
char s[N>>1];
inline void in(Re &x){
    Re f=0;x=0;char c=getchar();
    while(c<'0'||c>'9')f|=c=='-',c=getchar();
    while(c>='0'&&c<='9')x=(x<<1)+(x<<3)+(c^48),c=getchar();
    x=f?-x:x;
}
struct Suffix_Automaton{
	int O,last,pos[N],siz[N],link[N],maxlen[N],trans[N][26];LL ans;
	Suffix_Automaton(){last=O=1;}
	inline void insert(Re ch){
		Re z=++O,p=last;siz[z]=1,maxlen[z]=maxlen[last]+1;
		while(p&&!trans[p][ch])trans[p][ch]=z,p=link[p];
		if(!p)link[z]=1;
		else{
			Re x=trans[p][ch];
			if(maxlen[p]+1==maxlen[x])link[z]=x;
			else{
				Re y=++O;maxlen[y]=maxlen[p]+1;
				for(Re i=0;i<26;++i)trans[y][i]=trans[x][i];
				while(p&&trans[p][ch]==x)trans[p][ch]=y,p=link[p];
				link[y]=link[x],link[x]=link[z]=y;
			}
		}
		last=z;
	}
	int o,deep[N],head[N],ant[N][20];
	struct QAQ{int to,next;}a[N];
	inline void add(Re x,Re y){a[++o].to=y,a[o].next=head[x],head[x]=o;}
	inline void dfs(Re x,Re fa){
		deep[x]=deep[ant[x][0]=fa]+1;
		for(Re j=1;(1<<j)<=deep[x];++j)ant[x][j]=ant[ant[x][j-1]][j-1];
		for(Re i=head[x];i;i=a[i].next)dfs(a[i].to,x),siz[x]+=siz[a[i].to];
	}
	inline void build(){
		for(Re i=1;s[i];++i)insert(s[i]-'a'),pos[i]=last;
		for(Re i=2;i<=O;++i)add(link[i],i);
		dfs(1,0);
	}
	inline void check(Re x,Re len){
		Re p=pos[x+len-1];
		for(Re i=logN;i>=0;--i)
			if(maxlen[ant[p][i]]>=len)p=ant[p][i];
		ans=max(ans,(LL)len*siz[p]);
	}
	int m,r[N];char b[N];
	inline void sakura(){
		build();
		b[m=0]='$',b[++m]='|';
		for(Re i=1;s[i];++i)b[++m]=s[i],b[++m]='|';
		for(Re i=1,R=0,mid=0;i<=m;++i){
			r[i]=i<=R?min(r[(mid<<1)-i],R-i+1):1;
			while(b[i-r[i]]==b[i+r[i]]){
				++r[i];
				if(i+r[i]-1>R)check(i-r[i]+1+1>>1,r[i]-!(i+r[i]&1));//如果i与r[i]奇偶性相同则长度为r[i]-1否则为r[i]
			}
			if(i+r[i]-1>R)mid=i,R=i+r[i]-1;
		}
		printf("%lld\n",ans);
	}
}SAM;
int main(){
	freopen("123.txt","r",stdin);
	scanf("%s",s+1),SAM.sakura();
}
