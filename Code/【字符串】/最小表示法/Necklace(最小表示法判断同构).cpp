#include<cstring>
#include<cstdio>
int i,j,k,n,m,x,y,st;char a[2000003],b[2000003];
inline int sakura(char a[]){
    i=1,j=2;
    while(i<=n&&j<=n){
        k=0;
        while(k<n&&a[i+k]==a[j+k])++k;
        if(k==n)break;
        if(a[i+k]>a[j+k]){i+=k+1;if(i==j)++i;}
        else{j+=k+1;if(i==j)++j;}
    }
    return i<j?i:j;
}
inline int judge(char a[],char b[]){
    n=strlen(a+1);
    for(i=1;i<=n;++i)a[i+n]=a[i],b[i+n]=b[i];
    x=sakura(a),y=sakura(b);
    a[x+n]=b[y+n]='\0';
    return !strcmp(a+x,b+y);
}
int main(){
    scanf("%s%s",a+1,b+1);
    if(judge(a,b)){printf("Yes\n");puts(a+x);}
    else printf("No");
}
