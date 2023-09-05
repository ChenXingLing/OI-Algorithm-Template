#pragma GCC optimize(2)
#pragma GCC optimize(3,"Ofast","inline")
#include<algorithm>
#include<cstring>
#include<cstdio>
#include<queue>
using namespace std;
struct QAQ{int w,d;}a[10003];
int ans,n,i;
inline bool cmp(QAQ a,QAQ b){return a.d!=b.d?a.d<b.d:a.w>b.w;}
struct QWQ{
	int heap[10003],t;
	inline void CL(){memset(heap,0,sizeof(heap));t=0;}
	inline void up(int p){
		while(p>1)
			if(heap[p>>1]>heap[p])swap(heap[p],heap[p>>1]),p>>=1;
			else break;
	}
	inline void down(int p){
		int s=(p<<1);
		while(s<=t){
			if(s<t&&heap[s]>heap[s|1])s++;
			if(heap[s]<heap[p]){
				swap(heap[s],heap[p]);
				p=s,s<<=1;
			}
			else break;
		}
	}
	inline void pop(){delet(1);}
	inline int top(){return heap[1];}
	inline int size(){return t;}
	inline void push(int x){heap[++t]=x;up(t);}
	inline void delet(int p){swap(heap[p],heap[t--]);down(p);}
}Q;
int main(){
    while(scanf("%d",&n)!=EOF){
        for(i=1;i<=n;i++)scanf("%d%d",&a[i].w,&a[i].d);
        sort(a+1,a+n+1,cmp);ans=0;Q.CL();
        for(i=1;i<=n;i++)
            if(Q.size()<a[i].d)Q.push(a[i].w);
            else if(Q.top()<a[i].w)Q.pop(),Q.push(a[i].w);
        while(Q.size())ans+=Q.top(),Q.pop();
        printf("%d\n",ans);
    }
}
