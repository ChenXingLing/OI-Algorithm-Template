#include<algorithm>
#include<cstdio>
using namespace std;
const int N=7100005;
int A[N],B[N],C[N],ans[N],h1,t1,h2,t2,h3,t3,s[100005],tmp,re,x,i,n,m,q,u,v,t;
double p;
inline int f(){
    int a=-0xfffffff;
    if(h1<=t1)a=max(a,A[h1]);
    if(h2<=t2)a=max(a,B[h2]);
    if(h3<=t3)a=max(a,C[h3]);
    if(h1<=t1&&a==A[h1])h1++;
    else if(h2<=t2&&a==B[h2])h2++;
    else h3++;
    return a;
}
inline bool cmp(int a,int b){return a>b;}
int main(){
    scanf("%d%d%d%d%d%d",&n,&m,&q,&u,&v,&t);
    p=1.0*u/v;h1=h2=h3=1;
    for(i=1;i<=n;i++)scanf("%d",&s[i]);
    sort(s+1,s+n+1,cmp);
    for(i=1;i<=n;i++)A[++t1]=s[i];
    for(i=1;i<=m;i++){
        x=f();
        x+=tmp;
        if(i%t==0)printf("%d ",x);
        re=p*x;
        B[++t2]=re-tmp-q;
        C[++t3]=x-re-tmp-q;
        tmp+=q;
    }
    printf("\n");
    for(i=h1;i<=t1;i++)ans[++ans[0]]=A[i];
    for(i=h2;i<=t2;i++)ans[++ans[0]]=B[i];
    for(i=h3;i<=t3;i++)ans[++ans[0]]=C[i];
    sort(ans+1,ans+ans[0]+1,cmp);
    for(i=1;i<=ans[0];i++)
        if(i%t==0)printf("%d ",ans[i]+tmp);
    return 0;
}
