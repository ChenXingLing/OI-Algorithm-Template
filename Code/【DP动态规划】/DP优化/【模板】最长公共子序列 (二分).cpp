// luogu-judger-enable-o2
#include<bits/stdc++.h>
using namespace std;
int pan[100010],b[100010],f[100010],n,i,a,len=1,l,r,mid;
inline int in(){
    int x=0,fh=1;char c=getchar();
    while(c<'0'||c>'9')c=getchar();
    while(c>='0'&&c<='9')x=x*10+c-'0',c=getchar();
    return x*fh;
}
int main(){
    n=in();
    for(i=1;i<=n;i++)a=in(),pan[a]=i,f[i]=0xfffffff;
    for(i=1;i<=n;i++)a=in(),b[i]=pan[a];
    for(i=1;i<=n;i++)printf("%d ",b[i]);puts("");
    f[1]=b[1];
    for(i=2;i<=n;i++){
    	l=0;r=len;
    	if(b[i]>f[len])f[++len]=b[i];
    	else{
    		while(l<r){
    			mid=(l+r)/2;
    			if(f[mid]<b[i])l=mid+1;
    			else r=mid;
    		}
    		f[l]=min(b[i],f[l]);
    	}
    }
    for(i=1;i<=n;i++)printf("%d ",f[i]);puts("");
    printf("%d",len);
    return 0;
}
