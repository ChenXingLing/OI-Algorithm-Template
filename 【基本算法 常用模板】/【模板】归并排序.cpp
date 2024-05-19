#pragma GCC optimize(3,"Ofast","inline")
#pragma GCC optimize(2)
#include<cstdio>
#define Re register int
const int N=5e5+3;
int fu,n,s[N],b[N];long long gs;char ch;
inline void in(int &x){
	fu=x=0;ch=getchar();
	while(ch<'0'||ch>'9')fu|=ch=='-',ch=getchar();
	while(ch>='0'&&ch<='9')x=(x<<1)+(x<<3)+(ch^48),ch=getchar();
	x=fu?-x:x;
}
void merge(Re L,Re mid,Re R){
    Re i=L,j=mid+1,w=L;
    while(i<=mid&&j<=R){
        if(s[i]<=s[j])b[w++]=s[i++];
        else b[w++]=s[j++],gs+=mid-i+1;
    }
    for(;i<=mid;i++)b[w++]=s[i];
    for(;j<=R;j++)b[w++]=s[j];
    for(i=L;i<=R;i++)s[i]=b[i];
}
inline void Sort(Re L,Re R){
    if(L<R){
        Re mid=L+R>>1;
        Sort(L,mid),Sort(mid+1,R);
        merge(L,mid,R);
    }
}
int main(){
    in(n);
    for(Re i=1;i<=n;i++)in(s[i]);
    Sort(1,n);
    for(Re i=1;i<=n;i++)printf("%d ",s[i]); 
//    printf("%lld",gs);//输出逆序对个数 
}
