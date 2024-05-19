#include<algorithm>
#include<cstring>
#include<cstdio>
#include<set>
#define LL long long
#define Re register int
#define IT set<QAQ>::iterator
using namespace std;
const int N=1e5+3;
int n,m,l,r,T,op,A[N],tmp[N],cnt[N],Ans[N];
inline void in(Re &x){
    int f=0;x=0;char c=getchar();
    while(c<'0'||c>'9')f|=c=='-',c=getchar();
    while(c>='0'&&c<='9')x=(x<<1)+(x<<3)+(c^48),c=getchar();
    x=f?-x:x;
}
struct QAQ{
	int l,r;mutable int pt,op; 
	QAQ(Re L=0,Re R=0,Re OP=0,Re PT=0){l=L,r=R,op=OP,pt=PT;};
	inline bool operator<(const QAQ &O)const{return l<O.l;}
};
set<QAQ>s;
struct Segment_Tree{
	#define pl tr[p].lp
	#define pr tr[p].rp
	#define mid ((L+R)>>1)
	int O;
	struct QAQ{int S,lp,rp;}tr[N*60];
	inline void pushup(Re p){tr[p].S=tr[pl].S+tr[pr].S;}
	inline void change(Re &p,Re L,Re R,Re x){
		p=++O;
		if(L==R){tr[p].S=1;return;}
		if(x<=mid)change(pl,L,mid,x);
		else change(pr,mid+1,R,x);
		pushup(p);
	}
	inline int merge(Re p,Re q,Re L,Re R){
		if(!p||!q)return p+q;
		if(L==R){tr[p].S+=tr[q].S;return p;}
		pl=merge(pl,tr[q].lp,L,mid);
		pr=merge(pr,tr[q].rp,mid+1,R);
		pushup(p);return p;
	}
	inline void split1(Re &p,Re q,Re L,Re R,Re k){//保留q中的前k个,其他的剪切给p
		tr[p=++O].S=tr[q].S-k,tr[q].S=k;
		if(L==R)return;
		Re tmp=tr[tr[q].lp].S;
		if(k>tmp)split1(pr,tr[q].rp,mid+1,R,k-tmp);//q的左儿子全部保留，分裂右儿子
		else pr=tr[q].rp,tr[q].rp=0;//右儿子全部剪切
		if(k<tmp)split1(pl,tr[q].lp,L,mid,k);//q的右儿子全部保留，分裂左儿子
	}
	inline void split2(Re &p,Re q,Re L,Re R,Re k){//保留q中的后k个,其他的剪切给p
		tr[p=++O].S=tr[q].S-k,tr[q].S=k;
		if(L==R)return;
		Re tmp=tr[tr[q].rp].S;
		if(k>tmp)split2(pl,tr[q].lp,L,mid,k-tmp);//q的右儿子全部保留，分裂左儿子
		else pl=tr[q].lp,tr[q].lp=0;//左儿子全部剪切
		if(k<tmp)split2(pr,tr[q].rp,mid+1,R,k);//q的左儿子全部保留，分裂右儿子
	}
	inline void dfs(Re p,Re L,Re R){
		if(!p)return;
		if(L==R){cnt[tmp[++tmp[0]]=L]=tr[p].S;return;}
		dfs(pl,L,mid),dfs(pr,mid+1,R);
	}
}T1;
inline IT split(Re w){
	IT it=s.lower_bound(QAQ(w));
	if(it!=s.end()&&it->l==w)return it;
	--it;
	Re L=it->l,R=it->r,op=it->op,pt=it->pt,ptt=0;
	s.erase(it);
	if(op)T1.split1(ptt,pt,1,m,w-1-L+1);//保留pt的前K个，其余丢入ptt
	else T1.split2(ptt,pt,1,m,w-1-L+1);//保留pt的后K个，其余丢入ptt
	s.insert(QAQ(L,w-1,op,pt));
	return s.insert(QAQ(w,R,op,ptt)).first;
}
inline void assign(Re l,Re r,Re op){//op=1:升序 op=0:降序
	if(l==r)return;
	IT itr=split(r+1),itl=split(l),it=itl;
	Re pt=0;
	while(it!=itr)pt=T1.merge(pt,it->pt,1,m),it->pt=0,++it;
	s.erase(itl,itr),s.insert(QAQ(l,r,op,pt));
}
int main(){
//	freopen("123.txt","r",stdin);
	in(n),in(T),m=n;
	for(Re i=1;i<=n;++i)in(A[i]);
	s.insert(QAQ(n+1,n+1));
	for(Re i=1;i<=n;++i){
		QAQ tmp(i,i,0,0);T1.change(tmp.pt,1,m,A[i]),s.insert(tmp);
	}
	while(T--)in(op),in(l),in(r),op^=1,assign(l,r,op);
	IT itl=s.lower_bound(QAQ(1)),itr=s.lower_bound(QAQ(n+1));
	while(itl!=itr){
		tmp[0]=0,T1.dfs(itl->pt,1,m);
		if(itl->op)for(Re i=1;i<=tmp[0];++i)
			for(Re j=1;j<=cnt[tmp[i]];++j)
				Ans[++Ans[0]]=tmp[i];
		else for(Re i=tmp[0];i>=1;--i)
			for(Re j=1;j<=cnt[tmp[i]];++j)
				Ans[++Ans[0]]=tmp[i];
		++itl;
	}
	in(op),printf("%d\n",Ans[op]);
}
