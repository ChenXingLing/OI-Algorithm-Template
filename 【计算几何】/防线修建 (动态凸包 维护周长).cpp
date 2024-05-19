#include<algorithm>
#include<cstdio>
#include<queue>
#include<cmath>
#include<set>
#define LD double
#define LL long long
#define Vector Point
#define Re register int
using namespace std;
const int N=1e5+3;
const LD eps=1e-8,Pi=acos(-1.0);
inline int dcmp(LD a){return a<-eps?-1:(a>eps?1:0);}
inline LD Abs(LD a){return a*dcmp(a);}
inline void in(Re &x){
    int f=0;x=0;char c=getchar();
    while(c<'0'||c>'9')f|=c=='-',c=getchar();
    while(c>='0'&&c<='9')x=(x<<1)+(x<<3)+(c^48),c=getchar();
    x=f?-x:x;
}
struct Point{
    LL x,y;Point(LL X=0,LL Y=0){x=X,y=Y;}
    inline void In(){Re X,Y;in(X),in(Y),x=X,y=Y;}
    inline bool operator<(const Point &O)const{return x!=O.x?x<O.x:y<O.y;}
};
inline LL Dot(Vector a,Vector b){return a.x*b.x+a.y*b.y;}
inline LL Cro(Vector a,Vector b){return a.x*b.y-a.y*b.x;}
inline LD Len(Vector a){return sqrt((LD)Dot(a,a));}
inline Vector operator-(Vector a,Vector b){return Vector(a.x-b.x,a.y-b.y);}
inline Vector operator+(Vector a,Vector b){return Vector(a.x+b.x,a.y+b.y);}
inline Vector operator*(Vector a,LD b){return Vector(a.x*b,a.y*b);}
inline bool operator==(Vector a,Vector b){return a.x==b.x&&a.y==b.y;}
struct Splay{
	#define pl tr[p].ps[0]
	#define pr tr[p].ps[1]
	#define pf tr[p].fa
	#define pv tr[p].v
	int O,root;queue<int>Q;LD ans;
	struct QAQ{int fa,ps[2];Point v;}tr[N];
	inline int which(Re p){return tr[pf].ps[1]==p;}
	inline void connect(Re p,Re fa,Re o){tr[pf=fa].ps[o]=p;}
	inline void rotate(Re p){
		Re fa=pf,fas=which(p);
		Re pa=tr[fa].fa,pas=which(fa);
		Re x=tr[p].ps[fas^1];
		connect(x,fa,fas),connect(fa,p,fas^1),connect(p,pa,pas);
	}
	inline void splay(Re p){
		for(Re fa;pf;rotate(p))
			if(tr[fa=pf].fa)rotate(which(p)==which(fa)?fa:p);
		root=p;
	}
	inline void CL(Re p){tr[p].v=Point(),pf=pl=pr=0,p=0;}
	inline int New(){
		Re p;
		if(Q.empty())p=++O;
		else p=Q.front(),Q.pop();
		return p;
	}
	inline void del(Re p){CL(p),Q.push(p);}
	inline int pre(Re p){p=pl;while(pr)p=pr;return p;}
	inline int nex(Re p){p=pr;while(pl)p=pl;return p;}
	inline void insert(Point v){
		Re p=root,fa=0;
		while(p)fa=p,p=tr[p].ps[!(pv<v)];
		p=New(),pv=v,pf=fa;
		if(fa)tr[fa].ps[!(tr[fa].v<v)]=p;
		splay(p);Re p1=0,p2=0;
		if(pl)p1=pre(p);if(pr)p2=nex(p);
		if(p1&&p2)ans-=Len(tr[p2].v-tr[p1].v);
		if(p1)ans+=Len(v-tr[p1].v);
		if(p2)ans+=Len(v-tr[p2].v);
	}
	inline void erase(Point v){
		Re p=root;
		while(!(pv==v))p,p=tr[p].ps[!(pv<v)];
		splay(p);
		Re p1=0,p2=0;
		if(pl)p1=pre(p);if(pr)p2=nex(p);
		if(p1&&p2)ans+=Len(tr[p2].v-tr[p1].v);
		if(p1)ans-=Len(v-tr[p1].v);
		if(p2)ans-=Len(v-tr[p2].v);
		if(!pl&&!pr){root=0,del(p);return;}
		if(!pl||!pr){tr[root=pl+pr].fa=0,del(p);return;}
		splay(pre(p)),tr[root].ps[1]=pr,tr[pr].fa=root,del(p);
	}
};
#define IT set<Point>::iterator
struct ConvexHull{
	int op;set<Point>s;LD ans;//Splay ss;
	inline void Insert(Point P){
		s.insert(P);IT p=s.find(P);
		Re o1=0,o2=0;IT p1=p,p2=p;
		if(p1!=s.begin())o1=1,--p1;if(++p2!=s.end())o2=1;
		if(o1&&o2)ans-=Len(*p2-*p1);
		if(o1)ans+=Len(*p-*p1);
		if(o2)ans+=Len(*p-*p2);
	}
	inline void Erase(IT p){
		Re o1=0,o2=0;IT p1=p,p2=p;
		if(p1!=s.begin())o1=1,--p1;if(++p2!=s.end())o2=1;
		if(o1&&o2)ans+=Len(*p2-*p1);
		if(o1)ans-=Len(*p-*p1);
		if(o2)ans-=Len(*p-*p2);
		s.erase(p);
	}
	inline int PIP(Point P){
		IT it=s.lower_bound(Point(P.x,-2e9));
		if(it==s.end())return 0;
		if(it->x==P.x)return (P.y-it->y)*op<=0;
		if(it==s.begin())return 0;
		IT j=it,k=it;--j;return Cro(P-*j,*k-*j)*op>=0;
	}
	inline int judge(IT it){
		IT j=it,k=it;
		if(j==s.begin())return 0;--j;
		if(++k==s.end())return 0;
		return Cro(*it-*j,*k-*j)*op>=0;
	}
	inline void insert(Point P){
		if(PIP(P))return;
		IT tmp=s.lower_bound(Point(P.x,-2e9));if(tmp!=s.end()&&tmp->x==P.x)Erase(tmp);//ss.erase(*tmp),s.erase(tmp);
		Insert(P);/*s.insert(P),ss.insert(P);*/IT it=s.find(P),p=it;
		if(p!=s.begin()){--p;while(judge(p)){IT tmp=p--;Erase(tmp);/*ss.erase(*tmp),s.erase(tmp);*/}}
		if((p=++it)!=s.end())while(judge(p)){IT tmp=p++;Erase(tmp);/*ss.erase(*tmp),s.erase(tmp);*/}
	}
}up,down;
int n,x,T,X[N],op[N],vis[N];LD Ans[N];Point P[N];
int main(){
//	freopen("123.txt","r",stdin);
	in(x),P[0].In(),up.op=1,down.op=-1;
	up.insert(P[0]),down.insert(P[0]);
	up.insert(Point(0,0)),down.insert(Point(0,0));
	up.insert(Point(x,0)),down.insert(Point(x,0));
	in(n);for(Re i=1;i<=n;++i)P[i].In();
	in(T);for(Re i=1;i<=T;++i){in(op[i]);if(op[i]<2)in(x),vis[X[i]=x]=1;}
	for(Re i=1;i<=n;++i)if(!vis[i])up.insert(P[i]),down.insert(P[i]);
	for(Re i=T;i>=1;--i)
		if(op[i]<2)up.insert(P[X[i]]),down.insert(P[X[i]]);
		else Ans[i]=up.ans+Len(*up.s.begin()-*down.s.begin())+Len(*--up.s.end()-*--down.s.end());
	for(Re i=1;i<=T;++i)if(op[i]>1)printf("%.2lf\n",Ans[i]);
}
