#include<algorithm>
#include<cstring>
#include<cstdio>
#define R register int
using namespace std;
int n,b,c,d,t,longson[10005],d1[10005],d2[10005],df[10005],head[10005];
struct QAQ{int to,next,w;}a[20005];
inline void add(int x,int y,int w){a[++t].to=y,a[t].w=w,a[t].next=head[x],head[x]=t;}
inline void dfs(int x,int pa){//���ֱײ�������� 
	for(R i=head[x];i;i=a[i].next){// oooO �K������ �L Oooo 
		R s,to=a[i].to;//            ( ��)�����㩧 ��(�� ) 
		if(to==pa)continue;//        \ ( �����̩� �� ) / 
		dfs(to,x);s=d1[to]+a[i].w;// \_)�J������ �I(_/ 
		if(s>d1[x])d2[x]=d1[x],d1[x]=s,longson[x]=to;//��¼�·�����ȵ�ͷ�Ķ��� 
		else d2[x]=max(d2[x],s);
	}
}
inline void dfsf(int x,int pa){//���������������� 
	for(R i=head[x];i;i=a[i].next){
		R to=a[i].to;
		if(to==pa)continue;
		if(longson[x]==to)df[to]=a[i].w+max(d2[x],df[x]);
//����ȹ�������ӵ�ͷ��һ���·����ô�ö��ӵķ�������������λ���׵Ĵδ���������ȡ���  
		else df[to]=a[i].w+max(d1[x],df[x]);
//����·û������ͷ����ô���ķ�������Ǹ��׵������������ȡ��� 
		dfsf(to,x);
	}
}
inline int sakura(){
	while(~scanf("%d",&n)){
		memset(longson,0,sizeof(longson));
		memset(head,0,sizeof(head));
		memset(d1,0,sizeof(d1));
		memset(d2,0,sizeof(d2));
		memset(df,0,sizeof(df));
		memset(a,0,sizeof(a));t=0;
		for(R i=2;i<=n;i++){
			scanf("%d%d",&b,&c);
			add(i,b,c),add(b,i,c);
		}
		dfs(1,0);dfsf(1,0);
		for(R i=1;i<=n;i++)printf("%d\n",max(d1[i],df[i]));
	}
	return 0;
}
int QAQWQ=sakura();
int main(){}
