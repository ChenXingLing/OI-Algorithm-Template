#include<cstdio>
#include<cstring>
#include<iostream>
using namespace std;
int fa[1001],n,k;
struct sakura{int u,v,next;}sak[4001];
int st[1001],tot=0;
int p[1001],pp[1001];

void add(int x,int y){
    tot++;
    sak[tot].u=x;
    sak[tot].v=y;
    sak[tot].next=st[x];
    st[x]=tot;
}

int find(int x){
    if (fa[x]!=x)
       fa[x]=find(fa[x]);
    return fa[x];
}

void unionn(int r1,int r2){
    fa[r1]=r2;
}

void doit(){
    int i,j;
    for (i=n-1;i>=1;i--){
    	pp[i]=1;
        for (j=st[i];j;j=sak[j].next){
            if (pp[sak[j].v]){
               	int r1=find(sak[j].u);
               	int r2=find(sak[j].v);
               	if (r1!=r2){
                  	unionn(r1,r2);
                  	p[r1]+=p[r2]; 
                  	p[r2]=p[r1];
            	}
            }
        }
        if (p[find(i)]>(n+1)/2){
            printf("%d",i);
        }
    }
}

int main(){
    scanf("%d",&n);
    pp[n]=1;
    for (int i=1;i<=n;i++){
        scanf("%d",&k);
        fa[i]=i;
        p[i]=1; 
        for (int j=1;j<=k;j++){
            int x;
            scanf("%d",&x);
            add(i,x);
        }
    }
    doit();
    return 0;
}
