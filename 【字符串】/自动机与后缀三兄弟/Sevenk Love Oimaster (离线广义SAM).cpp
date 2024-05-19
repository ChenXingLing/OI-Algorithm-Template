#include<algorithm>
#include<cstdio>
#include<queue>
#define Re register int
#define LL long long
using namespace std;
const int N=2e5+5;
int n,t,T,Len[N];char s[N],ch[360003];
inline void in(Re &x){
    int fu=0;x=0;char c=getchar();
    while(c<'0'||c>'9')fu|=c=='-',c=getchar();
    while(c>='0'&&c<='9')x=(x<<1)+(x<<3)+(c^48),c=getchar();
    x=fu?-x:x;
}
struct Trie{
	int O,c[N],fa[N],tr[N][26];
	Trie(){O=1;}
	inline void insert(char ch[],Re id){
		Re p=1;
		for(Re i=1;ch[i];Len[id]=i,++i){
			Re a=ch[i]-'a';s[++t]=a;
			if(!tr[p][a])tr[p][a]=++O,fa[O]=p,c[O]=a;
			p=tr[p][a];
		}
	}
}T1;
struct Suffix_Automaton{
	int O,pos[N],cnt[N],link[N],maxlen[N],trans[N][26];queue<int>Q;
	//pos[x]:Trie上的x节点（路径1->x所表示的字符串）在SAM上的对应节点编号 
	//cnt[x]:节点x上不同的模式串个数
	Suffix_Automaton(){O=1;}
	inline int insert(Re ch,Re last){//和普通SAM一样
		Re x,y,z=++O,p=last,flag=0;maxlen[z]=maxlen[last]+1;
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
		return flag?y:z;
	}
	int co[N];
	//co[x]:目前节点x上的模式串编号 
	inline void updata(Re p,Re id){//暴力跳link树更新cnt 
		while(p&&co[p]!=id)++cnt[p],co[p]=id,p=link[p];
	}
	inline void build(){//bfs遍历Trie树构造广义SAM 
		for(Re i=0;i<26;++i)if(T1.tr[1][i])Q.push(T1.tr[1][i]);
		pos[1]=1;
		while(!Q.empty()){
			Re x=Q.front();Q.pop();
			pos[x]=insert(T1.c[x],pos[T1.fa[x]]);
			for(Re i=0;i<26;++i)if(T1.tr[x][i])Q.push(T1.tr[x][i]);
		}
		for(Re i=1,t=0;i<=n;++i)
			for(Re j=1,p=1;j<=Len[i];++j)
				updata(pos[p=T1.tr[p][s[++t]]],i);
	}
	inline void ask(char ch[]){
		Re p=1,flag=1;
		for(Re i=1;ch[i]&&flag;++i){
			Re a=ch[i]-'a';
			if(trans[p][a])p=trans[p][a];
			else flag=0;
		}
		printf("%d\n",flag?cnt[p]:0);
	}
}SAM;
int main(){
//	freopen("123.txt","r",stdin);
	in(n),in(T);
	for(Re i=1;i<=n;++i)scanf("%s",ch+1),T1.insert(ch,i);
	SAM.build();
	while(T--)scanf("%s",ch+1),SAM.ask(ch);
}
