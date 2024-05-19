#pragma GCC optimize(3,"Ofast","inline")
#pragma GCC optimize(2)
#include<algorithm>
#include<cstdio>
#include<vector>
#include<set>
#define Re register int
#define IT set<QAQ>::iterator
using namespace std;
const int N=2e5+5;
struct QAQ{
    int l,r;mutable int v;
    QAQ(Re L,Re R=-1,Re V=0):l(L),r(R),v(V){}
    bool operator<(QAQ o)const{return l<o.l;}
};
int x,y,xx,yy,n,m,fu,op;set<QAQ>s;
inline void in(Re &x){
    x=fu=0;char c=getchar();
    while(c<'0'||c>'9')fu|=c=='-',c=getchar();
    while(c>='0'&&c<='9')x=(x<<1)+(x<<3)+(c^48),c=getchar();
    if(fu)x=-x;
}
inline IT split(Re w){
    IT it=s.lower_bound(QAQ(w));
    if(it!=s.end()&&it->l==w)return it;
    --it;
    Re L=it->l,R=it->r,V=it->v;
    s.erase(it);
    s.insert(QAQ(L,w-1,V));
    return s.insert(QAQ(w,R,V)).first;
}
inline void assign(Re l,Re r,Re v){
    IT itr=split(r+1),itl=split(l);
    s.erase(itl,itr),s.insert(QAQ(l,r,v));
}
inline int ask1(Re l,Re r){
	IT itr=split(r+1),itl=split(l);Re tmp=0,ans=0;
	while(itl!=itr){
		if(!itl->v)tmp+=itl->r-itl->l+1;
		else ans=max(ans,tmp),tmp=0;
		++itl;
	}
	return max(ans,tmp);
}
inline void scure(Re l,Re r,Re a,Re b){
	IT itr=split(r+1),itl=split(l),it=itl;Re t=0;
	while(it!=itr)t+=it->v*(it->r-it->l+1),++it;
	s.erase(itl,itr),s.insert(QAQ(l,r,0));
	if(!t)return;
	itr=split(b+1),itl=split(a);
	if(t>=b-a+1){s.erase(itl,itr),s.insert(QAQ(a,b,1));return;}
	for(;itl!=itr;++itl)
		if(!itl->v){
			t-=itl->r-itl->l+1;
			if(t<0){assign(itl->l,itl->r+t,1);break;}
			else itl->v=1;
		}
}
int main(){
    in(n),in(m);
    s.insert(QAQ(1,n,1));
    while(m--){
        in(op),in(x),in(y);
        if(!op)assign(x,y,0);
        else if(op<2)in(xx),in(yy),scure(x,y,xx,yy);
        else printf("%d\n",ask1(x,y));
    }
}
