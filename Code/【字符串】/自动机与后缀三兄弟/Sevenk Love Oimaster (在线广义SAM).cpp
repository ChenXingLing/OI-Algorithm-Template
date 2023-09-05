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
struct Suffix_Automaton{
	int O,cnt[N],link[N],maxlen[N],trans[N][26];
	//cnt[x]:节点x上不同的模式串个数
	Suffix_Automaton(){O=1;}
	inline int insert(Re ch,Re last){
		if(trans[last][ch]&&maxlen[last]+1==maxlen[trans[last][ch]])return trans[last][ch];//类Trie树形态建树，如果已有这个节点就不再构造了 
		Re x,y,z=++O,p=last,flag=0;maxlen[z]=maxlen[last]+1;
		while(p&&!trans[p][ch])trans[p][ch]=z,p=link[p];
		if(!p)link[z]=1;
		else{
			x=trans[p][ch];
			if(maxlen[p]+1==maxlen[x])link[z]=x;
			else{
				if(maxlen[p]+1==maxlen[z]/*或者写：p==last*/)flag=1;
				//p仍然为last，即存在trans[last][ch]，那么z肯定是一个没有任何用处的空节点
				//所以可直接将z作为x的复制点，也可以忽略z返回复制点y，这里采用的是后者 
				//普通SAM不存在这种情况
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
	for(Re i=1;i<=n;++i){
		scanf("%s",ch+1);Re last=1;
		for(Re j=1;ch[j];Len[i]=j,++j)last=SAM.insert(s[++t]=ch[j]-'a',last);
	}
	for(Re i=1,t=0;i<=n;++i)
		for(Re j=1,p=1;j<=Len[i];++j)
			SAM.updata(p=SAM.trans[p][s[++t]],i);
	while(T--)scanf("%s",ch+1),SAM.ask(ch);
}
