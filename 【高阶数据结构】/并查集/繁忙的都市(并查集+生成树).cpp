/*
            ！！ 
           |   | 
           |   | 
           |   | 
      ！！！     ！！！ 
    |  隠嗷AC噴忖尺   | 
     ！！！      ！！！ 
           |   | 
           |   | 
           |   | 
            ！！ 
*/
//#include<bits/stdc++.h>
#include<cstdio>
#include<cstdlib>
#include<iostream>
#include<algorithm>
int n,m,k,f[40001],sum;
struct sakura{
	int p,a,b,val;
}sak[40001];
inline int find(int x){return f[x]==x?x:find(f[x]);}
inline bool cmp(const sakura &a,const sakura &b){return a.val<b.val;}
inline bool unions(int x,int y){
	int fx=find(x),fy=find(y);
	if(fx==fy) return 0;
	else f[fy]=fx;
	return 1;
}
int main(){
	scanf("%d%d",&n,&m);
	for(int i=1;i<=n;i++) f[i]=i;
	for(int i=1;i<=m;i++)
		scanf("%d%d%d",&sak[i].a,&sak[i].b,&sak[i].val);
	std::sort(sak+1,sak+1+m,cmp);
	for(int i=1;i<=m;i++){
		if(unions(sak[i].a,sak[i].b)){
			k++;
			sum=sak[i].val;
		}
		if(k==n-1) break;
	}
	printf("%d %d",n-1,sum);
	return 0;
} 
