#include<algorithm>
#include<cstdlib>
#include<cstdio>
int g,i,j,n,m,p,x,y,c,ans,k,f[2010];
struct QAQ{int l,r,w;}a[40010];
inline int fi(int x){if(x!=f[x])f[x]=fi(f[x]);return f[x];}
inline int cmp(const QAQ &a,const QAQ &b){return a.w<b.w;}
int main(){
    scanf("%d%d",&n,&m);
    for(i=1;i<=n;i++)f[i]=i;
    for(i=1;i<=m;i++){
        scanf("%d%d%d%d",&p,&x,&y,&c);
        if(p==1){ans+=c,f[fi(y)]=fi(x);}
        else a[++g].l=x,a[g].r=y,a[g].w=c;
    }
    std::sort(a+1,a+g+1,cmp);
    for(i=1;i<=g;i++){
        x=fi(a[i].l),y=fi(a[i].r);
        if(x!=y){
            f[y]=x;k++;
            ans+=a[i].w;
        }
    }
    printf("%d",ans);
    return 0;
}
