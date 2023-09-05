#include<algorithm>
#include<cstring>
#include<cstdio>
#include<queue>
#include<map>
#define Re register int
#define LL long long
using namespace std;
const int N=2e5+5;
int n,t,T,x,s[N],ch[N],Len[N];
inline void in(Re &x){
    int fu=0;x=0;char c=getchar();
    while(c<'0'||c>'9')fu|=c=='-',c=getchar();
    while(c>='0'&&c<='9')x=(x<<1)+(x<<3)+(c^48),c=getchar();
    x=fu?-x:x;
}
struct Suffix_Automaton{	
	int O,pos[N],cnt[N],link[N],maxlen[N],minlen[N];queue<int>Q;map<int,int>trans[N];
	Suffix_Automaton(){O=1;}
	inline int insert(Re ch,Re last){
		if(trans[last][ch]&&maxlen[last]+1==maxlen[trans[last][ch]])return trans[last][ch];
		Re x,y,z=++O,p=last,flag=0;maxlen[z]=maxlen[last]+1;
		while(p&&!trans[p][ch])trans[p][ch]=z,p=link[p];
		if(!p)link[z]=1;
		else{
			x=trans[p][ch];
			if(maxlen[p]+1==maxlen[x])link[z]=x;
			else{
				if(maxlen[p]+1==maxlen[z])flag=1;
				y=++O;maxlen[y]=maxlen[p]+1;
				trans[y]=trans[x];
				while(p&&trans[p][ch]==x)trans[p][ch]=y,p=link[p];
				link[y]=link[x],link[z]=link[x]=y;
			}
		}
		return flag?y:z;
	}
	int co[N];
	inline void updata(Re p,Re id){//处理每个节点p属于多少个不同模式串
		while(p&&co[p]!=id)++cnt[p],co[p]=id,p=link[p];
	}
	int gs[N],Ans[N];
	inline void updata_(Re p,Re id){//累加得到有多少个询问串是该模式串id的子串 
		while(p&&co[p]!=id)Ans[id]+=gs[p],co[p]=id,p=link[p];
	}
	inline void ask(Re ch[],Re L){
		Re p=1,flag=1;
		for(Re i=1;i<=L&&flag;++i){
			Re a=ch[i];
			if(trans[p][a])p=trans[p][a];
			else flag=0;
		}
		if(flag)++gs[p];
		printf("%d\n",flag?cnt[p]:0);//询问该串属于多少个模式串
	}
}SAM;
int main(){
//	freopen("123.txt","r",stdin);
	in(n),in(T);
	for(Re i=1;i<=n;++i){
		in(Len[(i<<1)-1]);Re last=1;
		for(Re j=1;j<=Len[(i<<1)-1];++j)in(x),last=SAM.insert(s[++t]=x,last);
		in(Len[i<<1]);last=1;
		for(Re j=1;j<=Len[i<<1];++j)in(x),last=SAM.insert(s[++t]=x,last);
	}
	for(Re i=1,t=0;i<=n;++i){
		for(Re j=1,p=1;j<=Len[(i<<1)-1];++j)
			SAM.updata(p=SAM.trans[p][s[++t]],i);
		for(Re j=1,p=1;j<=Len[i<<1];++j)
			SAM.updata(p=SAM.trans[p][s[++t]],i);
	}
	while(T--){
		in(Len[0]);
		for(Re i=1;i<=Len[0];++i)in(ch[i]);
		SAM.ask(ch,Len[0]);
	}
	memset(SAM.co,0,sizeof(SAM.co));
	for(Re i=1,t=0;i<=n;++i){
		for(Re j=1,p=1;j<=Len[(i<<1)-1];++j)
			SAM.updata_(p=SAM.trans[p][s[++t]],i);
		for(Re j=1,p=1;j<=Len[i<<1];++j)
			SAM.updata_(p=SAM.trans[p][s[++t]],i);
	}
	for(Re i=1;i<=n;++i)printf("%d ",SAM.Ans[i]);
}
