//#pragma GCC optimize(3,"Ofast","inline")
//#pragma GCC optimize(2)
#include<algorithm>
#include<cstdio>
#define Re register int
#define pl tr[p].ps[0]
#define pr tr[p].ps[1]
#define pf tr[p].fa 
#define pv tr[p].v
using namespace std;
const int N=1e5+5,inf=2e9;
int T,a,b,n,o,root;
struct Splay{int v,fa,ps[2],cnt,size;}tr[N];
inline void in(Re &x){
    int fu=0;x=0;char c=getchar();
    while(c<'0'||c>'9')fu|=c=='-',c=getchar();
    while(c>='0'&&c<='9')x=(x<<1)+(x<<3)+(c^48),c=getchar();
    x=fu?-x:x;
}
inline void pushup(Re p){if(!p)return;/*这里必需要加判断return，否则会崩死*/tr[p].size=tr[p].cnt+tr[pl].size+tr[pr].size;}
inline void connect(Re p,Re f,Re o){tr[tr[p].fa=f].ps[o]=p;}//让p成为f的o儿子 
inline int which(Re p){return tr[pf].ps[1]==p;}//查询p是哪个儿子 
inline void rotate(Re p){//Treap是把p往下拉，这里是把p往上拉到pf的头上去 
	Re y=pf,ys=which(p);//【y】x的父结点。【ys】x是它父亲的哪个儿子 
	Re R=tr[y].fa,Rs=which(y);//【R】y的父亲。【Rs】y是它父亲的哪个儿子 
	Re B=tr[p].ps[ys^1];//p的儿子中与pf同方向的点(需要将其连到y上) 
	connect(B,y,ys),connect(y,p,ys^1),connect(p,R,Rs);//改线 
	pushup(y),pushup(p);//p被拉到了y头上去，先02更新y，再更新p 
}
inline void Splay(Re p){//无论如何都一定要一次旋两下，NOI的巨毒瘤数据会卡这里 
	for(Re fa;fa=pf;rotate(p))
		if(tr[fa].fa)rotate(which(p)==which(fa)?fa:p);
	root=p;
//线性卡单旋，人字形卡双旋 
}
inline void New(Re x,Re fa){//建一个新点x并接到 fa下面 
	tr[++o].v=x,tr[o].fa=fa,tr[o].cnt=tr[o].size=1;
	if(fa)tr[fa].ps[tr[fa].v<x]=o;
}
inline void insert(Re x){
	if(!root){New(x,0);root=o;return;}//空树则直接简单接入 
	int p=root,fa=0;
	while(1){
		if(x==pv){++tr[p].cnt,pushup(p),pushup(fa),Splay(p);break;}//发现了副本 
		fa=p,p=tr[p].ps[pv<x];//继续往下遍历 
		if(!p){New(x,fa),pushup(fa),Splay(o);break;}//到达叶子节点位置，插入并将其拉到顶上去 
	}
}
inline int ask_level(Re p,Re x){//查询数x的排名 
//printf("p: %d\n",p);exit(0);
	if(x==pv){Re ans=tr[pl].size+1;Splay(p);return ans;}//找到了这个数
	else return x<pv?ask_level(pl,x):tr[p].cnt+tr[pl].size+ask_level(pr,x);
}
inline int ask_v(Re p,Re x){//查询排名为x的数
//	if(!p)return 0;//如果没找到这个数
	if(x<=tr[pl].size)return ask_v(pl,x);
	else{
		Re tmp=tr[pl].size+tr[p].cnt;
		return x<=tmp?pv:ask_v(pr,x-tmp);
	}
}
inline int ask_nex_p(Re p){p=pr;while(pl)p=pl;return p;}//从节点p开始查询猴急的位置 
inline int ask_pri_p(Re p){p=pl;while(pr)p=pr;return p;}//从节点p开始查询前驱的位置 
inline void del(Re x){
	ask_level(root,x);Re p=root;//找到这个点并拉成root 
	if(tr[p].cnt>1){--tr[p].cnt,--tr[p].size;return;}//有副本
	if(!pl&&!pr){root=0;return;}//没有儿子 
	if(!pl||!pr){tr[root=pl+pr].fa=0;return;}//只有一个儿子,直接将其儿子改为根 
	Splay(ask_pri_p(root));//把它的前驱拉上去，然后它的右儿子就是原root(即x) 
	tr[root].ps[1]=pr,tr[pr].fa=root;//删除原root(即x) 
	pushup(root);
}
int main(){
	in(T);
	while(T--){
		in(a),in(b);
		if(a==1)insert(b);
		if(a==2)del(b);
		if(a==3)printf("%d\n",ask_level(root,b));
		if(a==4)printf("%d\n",ask_v(root,b));
		if(a==5)insert(b),printf("%d\n",tr[ask_pri_p(root)].v),del(b);
		if(a==6)insert(b),printf("%d\n",tr[ask_nex_p(root)].v),del(b);
	}
}
