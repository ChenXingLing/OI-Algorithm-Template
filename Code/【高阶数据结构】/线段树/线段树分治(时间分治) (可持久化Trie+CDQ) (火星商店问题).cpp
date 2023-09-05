#include<algorithm>
#include<cstring>
#include<cstdio>
#include<vector>
#define LL long long
#define Re register int
using namespace std;
const int N=1e5+3,logN=18;
int n,x,y,z,w,op,m1,m2,T,A[N],t1[N],t2[N],Ans[N];
struct Change{int i,v,t;inline bool operator<(const Change &O)const{return i<O.i;}}C[N],tmp[N];
struct Query{int x,l,r,id;}Q[N];
inline void in(Re &x){
    int f=0;x=0;char c=getchar();
    while(c<'0'||c>'9')f|=c=='-',c=getchar();
    while(c>='0'&&c<='9')x=(x<<1)+(x<<3)+(c^48),c=getchar();
    x=f?-x:x;
}
int pt[N];
struct Trie{
	int O,cnt[N*(logN+2)],tr[N*(logN+2)][2];
	inline void insert(Re p,Re q,Re o,Re x){
		if(o<0)return;Re i=(x>>o)&1;
		tr[p][i]=++O,tr[p][i^1]=tr[q][i^1];
		cnt[tr[p][i]]=cnt[tr[q][i]]+1;
		insert(tr[p][i],tr[q][i],o-1,x);
	}
	inline int ask(Re p,Re q,Re o,Re x){
		if(o<0)return 0;Re i=(x>>o)&1;
		if(cnt[tr[q][i^1]]>cnt[tr[p][i^1]])return (1<<o)+ask(tr[p][i^1],tr[q][i^1],o-1,x);
		else return ask(tr[p][i],tr[q][i],o-1,x);
	}
}T1;
struct Segment_Tree{
	#define pl (p<<1)
	#define pr (p<<1|1)
	#define mid ((L+R)>>1)
	vector<Query>tr[N<<2];
	inline void change(Re p,Re L,Re R,Re l,Re r,Query &v){
		if(l>r)return;
		if(l<=L&&R<=r){tr[p].push_back(v);return;}
		if(l<=mid)change(pl,L,mid,l,r,v);
		if(r>mid)change(pr,mid+1,R,l,r,v);
	}
	inline int find1(Re l,Re r,Re id){//第一个大于等于id的位置
		if(C[r].i<id)return r+1;
		while(l<r){
			Re Mid=l+r>>1;
			if(C[Mid].i>=id)r=Mid;
			else l=Mid+1;
		}
		return r;
	}
	inline int find2(Re l,Re r,Re id){//第一个大于id的位置
		if(C[r].i<=id)return r+1;
		while(l<r){
			Re Mid=l+r>>1;
			if(C[Mid].i>id)r=Mid;
			else l=Mid+1;
		}
		return r;
	}
	inline void CDQ(Re p,Re L,Re R,Re l,Re r){
		if(l>r)return;
		T1.O=pt[l-1]=0;
		for(Re i=l;i<=r;++i)T1.insert(pt[i]=++T1.O,pt[i-1],logN,C[i].v);
		for(vector<Query>::iterator it=tr[p].begin();it!=tr[p].end();++it){
			Re ll=find1(l,r,it->l)-1,rr=find2(l,r,it->r)-1;
			if(ll<rr)Ans[it->id]=max(Ans[it->id],T1.ask(pt[ll],pt[rr],logN,it->x));
		}
		if(L==R)return;
		Re p1=l-1;for(Re i=l;i<=r;++i)if(C[i].t<=mid)tmp[++p1]=C[i];
		Re p2=p1;for(Re i=l;i<=r;++i)if(C[i].t>mid)tmp[++p2]=C[i];
		for(Re i=l;i<=r;++i)C[i]=tmp[i];
		CDQ(pl,L,mid,l,p1),CDQ(pr,mid+1,R,p1+1,r);
	}
}TR;
int main(){
//	freopen("123.txt","r",stdin);
	in(n),in(T);
	for(Re i=1;i<=n;++i)in(A[i]),T1.insert(pt[i]=++T1.O,pt[i-1],logN,A[i]);
	for(Re i=1;i<=T;++i){
		in(op),in(x),in(y);
		if(!op)++m1,C[m1]=(Change){x,y,m1};
		else in(z),in(w),++m2,Q[m2]=(Query){z,x,y,m2},t1[m2]=max(1,m1-w+1),t2[m2]=m1;
	}
	for(Re i=1;i<=m2;++i)Ans[i]=T1.ask(pt[Q[i].l-1],pt[Q[i].r],logN,Q[i].x),TR.change(1,1,m1,t1[i],t2[i],Q[i]);
	sort(C+1,C+m1+1),TR.CDQ(1,1,m1,1,m1);
	for(Re i=1;i<=m2;++i)printf("%d\n",Ans[i]);
}
