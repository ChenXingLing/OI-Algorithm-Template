#pragma GCC optimize(2)
#pragma GCC optimize(3,"Ofast","inline")
#include<algorithm>
#include<cstring>
#include<cstdio>
#define mid (L+R>>1)
#define Re register int
#define pl tree[p].lp
#define pr tree[p].rp
#define F(i,a,b) for(Re i=a;i<=b;++i)
#define lo(o) lower_bound(b+1,b+m+1,o)-b
using namespace std;
const int N=1e5+3,inf=2147483647;//【N不乘2 WA上天】由于要离散化，加上查询最多n+m(即2*n)个数据
int x,y,z,n,m,T,t,fu,cnt,tl,tr,a[N],b[N],pt[N],C[N],opt[N],ptl[20],ptr[20]; 
struct QAQ{int g,lp,rp;}tree[N*250];//本应是17*17=289左右,开小一点也无所谓，因为根本用不到
struct O_O{int l,r,k;}Q[N];//储存Q次查询的具体内容，方便离散化
struct T_T{int i,x;}c[N];//单点修改的具体内容
inline void in(Re &x){
    x=fu=0;char c=getchar();
    while(c<'0'||c>'9')fu|=c=='-',c=getchar();
    while(c>='0'&&c<='9')x=(x<<1)+(x<<3)+(c^48),c=getchar();
    x=fu?-x:x;
}
inline int ask_kth(Re L,Re R,Re k){//查询第k小
    if(L==R)return b[R];//【映射混用 WA上天】注意：返回的值需要用到的是哪一个映射数组不能搞错
    Re tmp=0;
    F(i,1,tl)tmp-=tree[tree[ptl[i]].lp].g;//计算左子树信息
    F(i,1,tr)tmp+=tree[tree[ptr[i]].lp].g;//计算左子树信息
    if(tmp>=k){
    	F(i,1,tl)ptl[i]=tree[ptl[i]].lp;//更新ptl,ptr所指向的节点编号
    	F(i,1,tr)ptr[i]=tree[ptr[i]].lp;
    	return ask_kth(L,mid,k);
    }
    else{
    	F(i,1,tl)ptl[i]=tree[ptl[i]].rp;
    	F(i,1,tr)ptr[i]=tree[ptr[i]].rp;
    	return ask_kth(mid+1,R,k-tmp);
    }
}
inline int ask_kth_pre(Re L,Re R,Re k){//查询第k小(中转站)
    tl=tr=0;//(注意L-1)
    for(Re i=L-1;i;i-=i&-i)ptl[++tl]=pt[i];//先把所有要更新的位置的线段树根节点记录下来
    for(Re i=R;i;i-=i&-i)ptr[++tr]=pt[i];//方便后面递归更新信息
    return ask_kth(1,m,k);
}
inline void add(Re &p,Re L,Re R,Re w,Re v){//【单点修改】
    if(!p)p=++cnt;tree[p].g+=v;
    if(L==R)return;
    if(w<=mid)add(pl,L,mid,w,v);
    else add(pr,mid+1,R,w,v);
}
inline void add_pre(Re x,Re v){//【单点修改】
    Re w=lo(a[x]);//【映射混用 TLE上天】注意函数传进来的参数x是在原数列的位置c[i].i(方便更新原数列)，这里各种映射数组的调用不要搞错
    for(Re i=x;i<=n;i+=i&-i)add(pt[i],1,m,w,v);//树状数组思想更新信息
}
inline int ask_level(Re p,Re L,Re R,Re x){//查询小于等于x的数的个数
	if(L==R)return tree[p].g; 
	if(x<=mid)return ask_level(pl,L,mid,x);
	else return tree[pl].g+ask_level(pr,mid+1,R,x);
}
inline int ask_level_pre(Re L,Re R,Re w){//查询x的排名(中转站)
	Re ans=0;
    for(Re i=R;i;i-=i&-i)ans+=ask_level(pt[i],1,m,w);
    for(Re i=L-1;i;i-=i&-i)ans-=ask_level(pt[i],1,m,w);
    return ans;
}
int main(){
//	printf("%lf\n",(sizeof(tree))/1024.0/1024.0);
//	printf("%lf\n",(sizeof(tree)+sizeof(Q)+sizeof(c)+sizeof(a)+sizeof(b)+sizeof(pt)+sizeof(C))/1024.0/1024.0);
	in(n),in(T),m=n;
    F(i,1,n)in(a[i]),b[i]=a[i];
    F(i,1,T){
    	in(opt[i]);
    	if(opt[i]==3)in(c[i].i),in(c[i].x),b[++m]=c[i].x;
    	else{
    		in(Q[i].l),in(Q[i].r),in(Q[i].k);
    		if(opt[i]!=2)b[++m]=Q[i].k;//【不离散 WA上天】除了2的查询不用管，其他地方出现的k全部都要离散化
		}
    }
    sort(b+1,b+m+1);
    m=unique(b+1,b+m+1)-b-1;//unique()是-(b+1),lower_bound()是-b
    F(i,1,n)add_pre(i,1);//初始化建树
    F(i,1,T){
    	if(opt[i]==1)//查询x的排名(中转站)
    		Q[i].k=lo(Q[i].k),//【直接查询 WA上天】先查询Q[i].k在b中的的位置，将其减一查得 ≤他前一个数 的总个数
			printf("%d\n",ask_level_pre(Q[i].l,Q[i].r,Q[i].k-1)+1);//再加一查得Q[i].k的排名，酱紫可以有效避过Q[i].k的副本处理

    	if(opt[i]==2)
    		printf("%d\n",ask_kth_pre(Q[i].l,Q[i].r,Q[i].k));//查询第k小(中转站)

		if(opt[i]==3)//修改某一位值上的数值(中转站)
			add_pre(c[i].i,-1),a[c[i].i]=c[i].x,add_pre(c[i].i,1);
		//先让这个位置上原来的数减少一个，更新数字后再把新数加一个，就达到了替换的目的

		if(opt[i]==4){//查询前驱(严格小于)
/*1>取位置*/Q[i].k=lo(Q[i].k);//【直接查询 WA上天】先查询Q[i].k在b中的位置，将其位置减一查询得前驱 
/*2>找排名*/Re level=ask_level_pre(Q[i].l,Q[i].r,Q[i].k-1);//因为在离散化数组中是找不到Q[i].k-1这个数字的，所以不能直接查询具体数值
/*3>判有无*/if(!level)printf("%d\n",-inf);//【判断条件错误 WA到上天】由于这里level是取出的前驱在b中的位置，所以只要【level>0】就可以啦
			//(如果你按着上面【直接查询 WA上天】的注释改了代码，却没有改这里的【条件判断】，那么你的level<=1将会让你【WA上天】)。
/*4>找结果*/else printf("%d\n",ask_kth_pre(Q[i].l,Q[i].r,level)); 
		}

		if(opt[i]==5){//查询猴急(严格大于)【盲目复制 WA上天】如果你采用了同上的方法，等着死翘翘吧
/*1>取位置*/Q[i].k=lo(Q[i].k);
/*2>找排名*/Re level=ask_level_pre(Q[i].l,Q[i].r,Q[i].k);//【直接查询 WA上天】如果同上，会越界，上面的越界是b[0]=0所以不慌，嘿嘿，而这里b[n+1]=0就不行了哟
/*3>判有无*/if(level==Q[i].r-Q[i].l+1)printf("%d\n",inf);//【判断条件错误 WA上天】这里猴急应是level+1，所以条件应是【level≤区间总长度】
/*4>找结果*/else printf("%d\n",ask_kth_pre(Q[i].l,Q[i].r,level+1));//【盲目复制 WA上天】 别忘了加一，和前驱不同啦！
		}
    }
}
