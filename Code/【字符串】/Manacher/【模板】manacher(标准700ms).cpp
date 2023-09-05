// luogu-judger-enable-o2
#include<algorithm>
#include<cstdio>
using namespace std;
const int N=22000003;
char a[N]={'$','|'},c=getchar();int r[N],mid,ans,R,n=1,i;
int main(){
    while(c>='a'&&c<='z')a[++n]=c,a[++n]='|',c=getchar();
    for(i=1;i<=n;i++){
        if(i<=R)r[i]=min(r[(mid<<1)-i],R-i+1);
        else r[i]=1;
        while(a[i-r[i]]==a[i+r[i]])r[i]++;
        if(i+r[i]-1>R)mid=i,R=i+r[i]-1;
        ans=max(ans,r[i]-1);
    }
    printf("%d",ans);
}
