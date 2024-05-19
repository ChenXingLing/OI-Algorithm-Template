#include<cstdio>
const int N=1e5+3;
int n,m,x,tmp,ansl;char a[N],ans[N];
inline int n_to_ten(){
	int x=0;
	for(int i=0;a[i];++i){
        x*=n;
        if (a[i]>='A'&&a[i]<='F')x+=(a[i]-'A'+10);
        else x+=(a[i]-'0');
   }
   return x;
}
inline void ten_to_m(){
	do{
		tmp=x%m;
		if(tmp<10)ans[++ansl]='0'+tmp;
		else ans[++ansl]='A'+tmp-10;
		x/=m;
		
	}while(x);
}
int main(){
   scanf("%d%s%d",&n,a,&m);
   x=n_to_ten();
   ten_to_m();
   for(int i=ansl;i;--i)printf("%c",ans[i]);puts("");
}
