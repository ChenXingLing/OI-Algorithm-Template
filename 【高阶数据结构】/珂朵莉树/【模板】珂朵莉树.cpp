#pragma GCC optimize(3,"Ofast","inline")
#pragma GCC optimize(2)
#include<algorithm>
#include<cstdio>
#include<vector>
#include<set>
#define LL long long
#define Re register int
#define IT set<QAQ>::iterator
using namespace std;
const int N=1e5+5;
struct QAQ{
	int l,r;mutable LL v;
	QAQ(int L,int R=-1,LL V=0):l(L),r(R),v(V){}
	bool operator<(QAQ o)const{return l<o.l;}
};
int l,r,x,y,n,m,fu,op,seed,vmax,a[N];set<QAQ>s;
inline int rnd(){
    Re tmp=seed;
    seed=((LL)seed*7+13)%1000000007;
    return tmp;
}
inline LL mi(LL a,LL k,LL P){
	LL ans=1;a%=P;
	while(k){
		if(k&1)(ans*=a)%=P;
		(a*=a)%=P,k>>=1;
	}
	return ans;
}
inline IT split(Re w){//分裂 
	IT it=s.lower_bound(QAQ(w));
	if(it!=s.end()&&it->l==w)return it;
	--it;
	Re L=it->l,R=it->r;LL V=it->v;
	s.erase(it);
	s.insert(QAQ(L,w-1,V));
	return s.insert(QAQ(w,R,V)).first;
}
inline void assign(Re l,Re r,LL v){//区间推平 
	IT itr=split(r+1),itl=split(l);
	s.erase(itl,itr),s.insert(QAQ(l,r,v));
}
inline void add(Re l,Re r,LL v){//区间加 
	IT itr=split(r+1),itl=split(l);
	while(itl!=itr)itl->v+=v,++itl;
}
inline LL mi_sum(Re l,Re r,Re k,Re P){//区间幂次和 
	IT itr=split(r+1),itl=split(l);LL ans=0;
	while(itl!=itr)(ans+=(LL)(itl->r-itl->l+1)%P*mi(itl->v,(LL)k,(LL)P)%P)%=P,++itl;
	return ans;
}
inline LL ask_k(Re l,Re r,Re k){//区间第k大 
	IT itr=split(r+1),itl=split(l);
	vector<pair<LL,int> >Q;
	Q.clear();
	while(itl!=itr)Q.push_back(pair<LL,int>(itl->v,itl->r-itl->l+1)),++itl;
	sort(Q.begin(),Q.end());
	for(vector<pair<LL,int> >::iterator it=Q.begin();it!=Q.end();++it){
		k-=it->second;
		if(k<=0)return it->first;
	}
}
int main(){
	scanf("%d%d%d%d",&n,&m,&seed,&vmax);
	for(Re i=1;i<=n;++i)a[i]=(rnd()%vmax)+1,s.insert(QAQ(i,i,a[i]));
	s.insert(QAQ(n+1,n+1,0));
	while(m--){
	    op=(rnd()%4)+1,l=(rnd()%n)+1,r=(rnd()%n)+1;
	    if(l>r)swap(l,r);
	    if(op==3)x=(rnd()%(r-l+1))+1;
	    else x=(rnd()%vmax)+1;
	    if(op==4)y=(rnd()%vmax)+1;
	    
	    if(op<2)add(l,r,(LL)x);
		else if(op<3)assign(l,r,(LL)x);
		else if(op<4)printf("%lld\n",ask_k(l,r,x));
		else printf("%lld\n",mi_sum(l,r,x,y));
	}
}
