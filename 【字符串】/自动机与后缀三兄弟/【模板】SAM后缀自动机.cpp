#include<algorithm>
#include<cstdio>
#include<queue>
#define Re register int
#define LL long long
using namespace std;
const int N=2e6+5;
char ch[2000003];
inline void in(Re &x){
    int fu=0;x=0;char c=getchar();
    while(c<'0'||c>'9')fu|=c=='-',c=getchar();
    while(c>='0'&&c<='9')x=(x<<1)+(x<<3)+(c^48),c=getchar();
    x=fu?-x:x;
}
struct Suffix_Automaton{
	int O,last,ru[N],siz[N],link[N],maxlen[N],minlen[N],trans[N][26];queue<int>Q;
	//siz:һ���ȼ���ڵ�endpos��С�������ִ����� 
	Suffix_Automaton(){last=O=1;}//���Ϊ 1 
	inline void insert(char ch){
		Re z=++O,p=last;siz[z]=1,maxlen[z]=maxlen[last]+1;//lenΪ������
		while(p&&!trans[p][ch])trans[p][ch]=z,p=link[p];//û��trans[...][ch]��һ��
		if(!p)link[z]=1;//û�ҵ�trans[...][ch]
		else{
			Re x=trans[p][ch];
			if(maxlen[p]+1==maxlen[x])link[z]=x;//ֱ�ӽ���ȥ 
			else{//��� 
				Re y=++O;maxlen[y]=maxlen[p]+1;//��ԭx���С�ڵ���maxlen[p]+1��һ�Σ���y���ʹ���maxlen[p]+1��һ�Σ�����x��
				
				for(Re i=0;i<26;++i)trans[y][i]=trans[x][i];//����ԭx��trans 
				while(p&&trans[p][ch]==x)trans[p][ch]=y,p=link[p];//��ָ����ԭx����һ�ζ�ָ��y 
				link[y]=link[x];//����ԭx��link
				
				link[z]=link[x]=y;
			}
		}
		last=z;
	}
	inline void Tuopu(){//������link���ɵ�DAG����������siz 
		for(Re i=2;i<=O;++i)++ru[link[i]];
		for(Re i=1;i<=O;++i)if(!ru[i])Q.push(i);
		while(!Q.empty()){
			Re x=Q.front();Q.pop();
			siz[link[x]]+=siz[x];
			if(!(--ru[link[x]]))Q.push(link[x]);
		}
	}
	inline void sakura(){
		for(Re i=2;i<=O;++i)minlen[i]=maxlen[link[i]]+1;
		Tuopu();Re ans=0;
		for(Re i=1;i<=O;++i)if(siz[i]>1)ans=max(ans,siz[i]*maxlen[i]);
		printf("%d\n",ans);
	}
}SAM;
int main(){
//	freopen("123.txt","r",stdin);
	scanf("%s",ch+1);
	for(Re i=1;ch[i];++i)SAM.insert(ch[i]-'a');
	SAM.sakura();
}
