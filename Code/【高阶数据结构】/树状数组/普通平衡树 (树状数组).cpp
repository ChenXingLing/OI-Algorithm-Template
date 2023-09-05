#include<algorithm>
#include<cstdio>
#define Re register int
#define lo(o) lower_bound(b+1,b+m+1,o)-b
using namespace std;
const int N=1e5+3;
int m,T,a[N],b[N],Q[N],op[N]; 
inline void in(Re &x){
    int f=0;x=0;char c=getchar();
    while(c<'0'||c>'9')f|=c=='-',c=getchar();
    while(c>='0'&&c<='9')x=(x<<1)+(x<<3)+(c^48),c=getchar();
    x=f?-x:x;
}
struct BIT{
	int C[N];
	inline void add(Re x,Re v){while(x<=m)C[x]+=v,x+=x&-x;}
	inline int ask(Re x){Re ans=0;while(x>0)ans+=C[x],x-=x&-x;return ans;}
}TR;
inline int ask_kth(Re k){
	Re l=0,r=m;
	while(l<r){
		Re mid=l+r>>1;
		if(TR.ask(mid)>=k)r=mid;
		else l=mid+1;
	}
	return b[l];
}
int main(){
	in(T); 
    for(Re i=1;i<=T;++i){
    	in(op[i]),in(Q[i]);
    	if(op[i]!=4)b[++m]=Q[i];
    }
    sort(b+1,b+m+1),m=unique(b+1,b+m+1)-b-1;
    for(Re i=1;i<=T;++i){
    	if(op[i]==1)TR.add(lo(Q[i]),1);//添加x
    	if(op[i]==2)TR.add(lo(Q[i]),-1);//删除x
		if(op[i]==3)printf("%d\n",TR.ask(lo(Q[i])-1)+1);//查询x的排名
		if(op[i]==4)printf("%d\n",ask_kth(Q[i]));//查询排名为x的数
		if(op[i]==5)printf("%d\n",ask_kth(TR.ask(lo(Q[i])-1)));//查询x的前驱
		if(op[i]==6)printf("%d\n",ask_kth(TR.ask(lo(Q[i]))+1));//查询x的后继
    }
}
