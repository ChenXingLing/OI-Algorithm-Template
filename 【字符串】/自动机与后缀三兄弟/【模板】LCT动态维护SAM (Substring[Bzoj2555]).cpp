#include<algorithm>
#include<cstring>
#include<cstdio>
#include<string>
#include<queue>
#define LL long long
#define Re register int
using namespace std;
const int N=12e5+3;
int T,ans,mask;char op[10],s[N];
inline void in(Re &x){
    int f=0;x=0;char c=getchar();
    while(c<'0'||c>'9')f|=c=='-',c=getchar();
    while(c>='0'&&c<='9')x=(x<<1)+(x<<3)+(c^48),c=getchar();
    x=f?-x:x;
}
inline string In(Re mask){
    scanf("%s",s);string chars=s;
    for(int j=0;j<chars.length();j++){
        mask=(mask*131+j)%chars.length();
        char t=chars[j];
        chars[j]=chars[mask];
        chars[mask]=t;
    }
    return chars;
}
struct Suffix_Automaton{
	struct Link_Cut_Tree{
		#define pl tr[p].ps[0]
		#define pr tr[p].ps[1]
		#define pf tr[p].fa
		int Q[N];
		struct QAQ{int fa,ans,add,ps[2];}tr[N];
		inline void add(Re p,Re v){tr[p].ans+=v,tr[p].add+=v;}
		inline void pushdown(Re p){
			Re v=tr[p].add;
			if(v){
				if(pl)add(pl,v);
				if(pr)add(pr,v);
				tr[p].add=0;
			}
		}
		inline int nort(Re p){return tr[pf].ps[0]==p||tr[pf].ps[1]==p;}
		inline int which(Re p){return tr[pf].ps[1]==p;}
		inline void connect(Re p,Re fa,Re o){tr[pf=fa].ps[o]=p;}
		inline void rotate(Re p){
			Re fa=pf,fas=which(p);
			Re pa=tr[fa].fa,pas=which(fa);
			Re x=tr[p].ps[fas^1];
			if(nort(fa))tr[pa].ps[pas]=p;pf=pa;
			connect(x,fa,fas),connect(fa,p,fas^1);
		}
		inline void splay(Re p){
			Re x=p,t=0;Q[++t]=x;
			while(nort(x))Q[++t]=x=tr[x].fa;
			while(t)pushdown(Q[t--]);
			for(Re fa;nort(p);rotate(p))
				if(nort(fa=pf))rotate(which(p)==which(fa)?fa:p);
		}
		inline void access(Re p){for(Re son=0;p;son=p,p=pf)splay(p),pr=son;}
		inline void link(Re x,Re y){tr[x].fa=y,access(y),splay(y),add(y,tr[x].ans);}
		inline void cut(Re x){
			access(x),splay(x),add(tr[x].ps[0],-tr[x].ans);
			tr[tr[x].ps[0]].fa=0,tr[x].ps[0]=0;
		}
		inline int ask(Re x){splay(x);return tr[x].ans;}
	}LCT;
	int O,last,link[N],maxlen[N],trans[N][30];
	Suffix_Automaton(){last=O=1;}
	inline void insert(char ch){
		Re z=++O,p=last;LCT.tr[z].ans=1,maxlen[z]=maxlen[last]+1;
		while(p&&!trans[p][ch])trans[p][ch]=z,p=link[p];
		if(!p)link[z]=1,LCT.link(z,1);
		else{
			Re x=trans[p][ch];
			if(maxlen[x]==maxlen[p]+1)link[z]=x,LCT.link(z,x);
			else{
				Re y=++O;maxlen[y]=maxlen[p]+1;
				for(Re i=0;i<26;++i)trans[y][i]=trans[x][i];
				while(p&&trans[p][ch]==x)trans[p][ch]=y,p=link[p];
				link[y]=link[x],LCT.cut(x),LCT.link(y,link[y]);
				link[x]=link[z]=y,LCT.link(x,y),LCT.link(z,y);
			}
		}
		last=z;
	}
	inline void add(string ch){
		for(Re i=0;ch[i];++i)insert(ch[i]-'A');
	}
	inline int ask(string ch){
		Re p=1;
		for(Re i=0;ch[i];++i)if(!(p=trans[p][ch[i]-'A']))return 0;
		return LCT.ask(p);
	}
}SAM;
int main(){
//    freopen("123.txt","r",stdin);
    in(T),scanf("%s",s+1);
    for(Re i=1;s[i];++i)SAM.insert(s[i]-'A');
	while(T--){
		scanf("%s",op);string s=In(mask);
		if(op[0]=='A')SAM.add(s);
		else mask^=(ans=SAM.ask(s)),printf("%d\n",ans);
	}
}
