#pragma GCC optimize(3,"Ofast","inline")
#pragma GCC optimize(2)
#include<algorithm> 
#include<cstdlib> 
#include<cstdio>
#include<ctime>
#define Re register int
#define pl tr[p].lp
#define pr tr[p].rp
#define pv tr[p].v
using namespace std;
const int N=1e5+5,inf=2e9;
int a,b,o,T,root;
inline void in(Re &x){
    int fu=0;x=0;char c=getchar();
    while(c<'0'||c>'9')fu|=c=='-',c=getchar();
    while(c>='0'&&c<='9')x=(x<<1)+(x<<3)+(c^48),c=getchar();
    x=fu?-x:x;
}
struct Treap{int v,rd,lp,rp,cnt,size;}tr[N];//cnt为该节点处这个数v的个数 
inline void pushup(Re p){tr[p].size=tr[p].cnt+tr[pl].size+tr[pr].size;}//更新节点空间信息 
inline void lturn(Re &p){//左旋 
	Re q=pr;pr=tr[q].lp,tr[q].lp=p;//颠倒父子关系 
	pushup(p),pushup(p=q);//先push(p)再push(q)并拉好最上面的线 
//拉线：p=q。这里的p经过无数次取地址符反复调用而来，回溯至初相当于tr[?].lp或者tr[?].rp 
}
inline void rturn(Re &p){//右旋 
	Re q=pl;pl=tr[q].rp,tr[q].rp=p;//颠倒父子关系 
	pushup(p),pushup(p=q);//先push(p)再push(q)并拉好最上面的线 
}
inline void insert(Re &p,Re x){
	if(!p){tr[p=++o].v=x,tr[p].cnt=tr[p].size=1,tr[p].rd=rand();return;}
	++tr[p].size;
	if(x==pv)++tr[p].cnt;
	else if(x<pv){
		insert(pl,x);
		if(tr[pl].rd<tr[p].rd)rturn(p);//小跟堆 
	}
	else{
		insert(pr,x);
		if(tr[pr].rd<tr[p].rd)lturn(p);//小跟堆 
	}
}
inline void del(Re &p,Re x){
	if(!p)return;
    if(x<pv)--tr[p].size,del(pl,x);
	else if(x>pv)--tr[p].size,del(pr,x);
	else{
		if(tr[p].cnt>1)--tr[p].cnt,--tr[p].size;//如果这个数的个数不止一个，直接减一轻松退出
		else{//否则需要删除该节点 
			if(pl*pr==0)p=pl+pr;
//其中一个儿子为空，直接指向这个不空的，那么访问时就可以直接跳过节点p，相当于达到了删除p的目的
//如果都为空，相当于把p赋值成了0 
//否则的话，先调整好两个儿子的次序，然后将p丢到一边并继续删除操作 
			else if(tr[pl].rd<tr[pr].rd)rturn(p),del(p,x);
			else lturn(p),del(p,x);
		}
	}
}
inline int ask_level(Re p,Re x){//查询数x的排名(保证存在x)。 
//	if(!p)return 0;//如果没找到这个数 
	if(x==pv)return tr[pl].size+1;//找到了这个数
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
inline int ask_pri(Re p,Re x){//查询x的前驱 
	if(!p)return -inf;
	if(x<=pv)return ask_pri(pl,x);
	else return max(pv,ask_pri(pr,x));
}
inline int ask_nex(Re p,Re x){//查询x的后继 
	if(!p)return inf;
	if(x>=pv)return ask_nex(pr,x);
	else return min(pv,ask_nex(pl,x));
}
int main(){
	srand((int)time(NULL));
	in(T);
	while(T--){
		in(a),in(b);
		if(a==1)insert(root,b);
		if(a==2)del(root,b);
		if(a==3)printf("%d\n",ask_level(root,b));
		if(a==4)printf("%d\n",ask_v(root,b));
		if(a==5)printf("%d\n",ask_pri(root,b)); 
		if(a==6)printf("%d\n",ask_nex(root,b));
	}
}
