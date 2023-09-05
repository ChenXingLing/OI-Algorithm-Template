// luogu-judger-enable-o2
#include<cstdio>
char a[11550000]={'$'};int T,i,s,l,r;
int main(){
    gets(a+1);
    for(i=1;a[i];++i){
        l=r=i;
        while(a[i]==a[r+1])++r;
        i=r;
        while(a[r+1]==a[l-1])++r,--l;
        if(r-l+1>s)s=r-l+1;
    }
    printf("%d",s);
}
