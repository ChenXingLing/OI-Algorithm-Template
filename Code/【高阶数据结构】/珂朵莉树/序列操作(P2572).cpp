#pragma GCC optimize(3,"Ofast","inline")
#pragma GCC optimize(2)
#include<algorithm>
#include<cstdio>
#include<vector>
#include<set>
#define Re register int
#define IT set<QAQ>::iterator
using namespace std;
const int N=1e5+5;
struct QAQ{
    int l,r;mutable int v;
    QAQ(Re L,Re R=-1,Re V=0):l(L),r(R),v(V){}
    bool operator<(QAQ o)const{return l<o.l;}
};
int x,y,n,m,fu,op;set<QAQ>s;
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
inline int count1(Re l,Re r){
	IT itr=split(r+1),itl=split(l);Re ans=0;
	while(itl!=itr)ans+=itl->v*(itl->r-itl->l+1),++itl;
	return ans;
}
inline int ask1(Re l,Re r){
	IT itr=split(r+1),itl=split(l);Re tmp=0,ans=0;
	while(itl!=itr){
		if(itl->v)tmp+=itl->r-itl->l+1;
		else ans=max(ans,tmp),tmp=0;
		++itl;
	}
	return max(ans,tmp);
}
inline void inverse(Re l,Re r){
	IT itr=split(r+1),itl=split(l);
	while(itl!=itr)itl->v^=1,++itl;
}
int main(){
    in(n),in(m);
    for(Re i=1;i<=n;++i)in(x),s.insert(QAQ(i,i,x));
    s.insert(QAQ(n+1,n+1,-1));
    while(m--){
        in(op),in(x),in(y);++x,++y;
        if(!op)assign(x,y,0);
        else if(op<2)assign(x,y,1);
        else if(op<3)inverse(x,y);
        else if(op<4)printf("%d\n",count1(x,y));
        else printf("%d\n",ask1(x,y));
    }
}
