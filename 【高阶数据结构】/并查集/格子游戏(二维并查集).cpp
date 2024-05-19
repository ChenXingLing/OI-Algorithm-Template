#include<bits/stdc++.h>
using namespace std;
struct T{int x,y;}f[210][210];
int x,y,n,m;char c;T a1,a2;
T s(int x,int y){
    while((x==f[x][y].x)&&(y==f[x][y].y))return f[x][y];
    return s(f[x][y].x,f[x][y].y);
}
int main(){
    scanf("%d%d",&n,&m);
    for(int i=1;i<=n;i++)
        for(int j=1;j<=n;j++)
            f[i][j].x=i,f[i][j].y=j;
    for(int i=1;i<=m;i++)
    {
        cin>>x>>y>>c;
        if(c=='D')a1=s(x,y),a2=s(x+1,y);
        else a1=s(x,y),a2=s(x,y+1);
        if(a1.x==a2.x&&a1.y==a2.y){
            printf("%d\n",i);return 0;
        }
        else f[a2.x][a2.y]=a1;
    }
    printf("draw");
    return 0;
}
