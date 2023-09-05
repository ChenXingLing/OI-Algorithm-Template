#include<algorithm>
#include<cstring>
#include<cstdio>
#define LL long long
#define Re register int
using namespace std;
const int N=1e5+3,M=2e5+3;
int n,T;LL Ans[M];char s[N];
struct Query{int l,r,id;inline bool operator<(const Query &O)const{return r<O.r;}}Q[M];
inline void in(Re &x){
    int f=0;x=0;char c=getchar();
    while(c<'0'||c>'9')f|=c=='-',c=getchar();
    while(c>='0'&&c<='9')x=(x<<1)+(x<<3)+(c^48),c=getchar();
    x=f?-x:x;
}
struct Segment_Tree{
	#define pl (p<<1)
	#define pr (p<<1|1)
	#define mid ((L+R)>>1)
	struct QAQ{LL S,add;}tr[N<<2];
	inline void updata(Re p,Re L,Re R,LL v){tr[p].add+=v,tr[p].S+=v*(R-L+1);}
	inline void pushdown(Re p,Re L,Re R){
		if(tr[p].add)updata(pl,L,mid,tr[p].add),updata(pr,mid+1,R,tr[p].add),tr[p].add=0;
	}
	inline void change(Re p,Re L,Re R,Re l,Re r,Re v){
		if(l<=L&&R<=r){updata(p,L,R,v);return;}
		pushdown(p,L,R);
		if(l<=mid)change(pl,L,mid,l,r,v);
		if(r>mid)change(pr,mid+1,R,l,r,v);
		tr[p].S=tr[pl].S+tr[pr].S;
	}
	inline LL ask(Re p,Re L,Re R,Re l,Re r){
		if(l<=L&&R<=r)return tr[p].S;
		pushdown(p,L,R);LL ans=0;
		if(l<=mid)ans+=ask(pl,L,mid,l,r);
		if(r>mid)ans+=ask(pr,mid+1,R,l,r);
		return ans;
	}
	#undef pl
	#undef pr
}TR;
struct Suffix_Automaton{
	int O,last,pos[N],link[N<<1],maxlen[N<<1],trans[N<<1][26];
	Suffix_Automaton(){last=O=1;}
	inline void insert(Re ch,Re id){
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
				link[y]=link[x],link[z]=link[x]=y;
			}
		}
		pos[id]=last=z;
	}
}SAM;
struct Link_Cut_Tree{
	#define pl (tr[p].ps[0])
	#define pr (tr[p].ps[1])
	#define pf (tr[p].fa)
	#define pv (tr[p].v)
	int Q[N<<1];
	struct QAQ{int v,fa,tag,ps[2];}tr[N<<1];
	inline void updata(Re p,Re v){tr[p].tag=tr[p].v=v;}
	inline void pushdown(Re p){
		if(tr[p].tag){
			if(pl)updata(pl,tr[p].tag);
			if(pr)updata(pr,tr[p].tag);
			tr[p].tag=0;
		}
	}
	inline int which(Re p){return tr[pf].ps[1]==p;}
	inline int nort(Re p){return tr[pf].ps[0]==p||tr[pf].ps[1]==p;}
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
		while(tr[x].fa)Q[++t]=x=tr[x].fa;
		while(t)pushdown(Q[t--]);
		for(Re fa;nort(p);rotate(p))
			if(nort(fa=pf))rotate(which(p)==which(fa)?fa:p);
	}
	inline void access(Re p,Re r){
		Re son=0;
		for(;p;son=p,p=pf){
			splay(p);
			if(pv)TR.change(1,1,n,pv-SAM.maxlen[p]+1,pv-SAM.maxlen[pf],-1);//把之前的last减掉
			pr=son;
		}
		updata(son,r),TR.change(1,1,n,1,r,1);//加上新的last
	}
}T1;
int main(){
//    freopen("123.txt","r",stdin);
    scanf("%s",s+1),n=strlen(s+1),in(T);
	for(Re i=1;i<=n;++i)SAM.insert(s[i]-'a',i);
	for(Re i=2;i<=SAM.O;++i)T1.tr[i].fa=SAM.link[i];
	for(Re i=1;i<=T;++i)in(Q[i].l),in(Q[i].r),Q[i].id=i;
    sort(Q+1,Q+T+1);
    for(Re i=1,r=0;i<=T;++i){
    	while(r<Q[i].r)++r,T1.access(SAM.pos[r],r);
    	Ans[Q[i].id]=TR.ask(1,1,n,Q[i].l,Q[i].r);
	}
	for(Re i=1;i<=T;++i)printf("%lld\n",Ans[i]);
}
