#include<algorithm>
#include<cstdio>
#include<queue>
#define Re register int
#define LL long long
using namespace std;
const int N=2e5+5;
int n,t,T,Len[N];char s[N],ch[360003];
inline void in(Re &x){
    int fu=0;x=0;char c=getchar();
    while(c<'0'||c>'9')fu|=c=='-',c=getchar();
    while(c>='0'&&c<='9')x=(x<<1)+(x<<3)+(c^48),c=getchar();
    x=fu?-x:x;
}
struct Suffix_Automaton{
	int O,cnt[N],link[N],maxlen[N],trans[N][26];
	//cnt[x]:�ڵ�x�ϲ�ͬ��ģʽ������
	Suffix_Automaton(){O=1;}
	inline int insert(Re ch,Re last){
		if(trans[last][ch]&&maxlen[last]+1==maxlen[trans[last][ch]])return trans[last][ch];//��Trie����̬�����������������ڵ�Ͳ��ٹ����� 
		Re x,y,z=++O,p=last,flag=0;maxlen[z]=maxlen[last]+1;
		while(p&&!trans[p][ch])trans[p][ch]=z,p=link[p];
		if(!p)link[z]=1;
		else{
			x=trans[p][ch];
			if(maxlen[p]+1==maxlen[x])link[z]=x;
			else{
				if(maxlen[p]+1==maxlen[z]/*����д��p==last*/)flag=1;
				//p��ȻΪlast��������trans[last][ch]����ôz�϶���һ��û���κ��ô��Ŀսڵ�
				//���Կ�ֱ�ӽ�z��Ϊx�ĸ��Ƶ㣬Ҳ���Ժ���z���ظ��Ƶ�y��������õ��Ǻ��� 
				//��ͨSAM�������������
				y=++O;maxlen[y]=maxlen[p]+1;
				for(Re i=0;i<26;++i)trans[y][i]=trans[x][i];
				while(p&&trans[p][ch]==x)trans[p][ch]=y,p=link[p];
				link[y]=link[x],link[z]=link[x]=y;
			}
		}
		return flag?y:z;
	}
	int co[N];
	//co[x]:Ŀǰ�ڵ�x�ϵ�ģʽ����� 
	inline void updata(Re p,Re id){//������link������cnt 
		while(p&&co[p]!=id)++cnt[p],co[p]=id,p=link[p];
	}
	inline void ask(char ch[]){
		Re p=1,flag=1;
		for(Re i=1;ch[i]&&flag;++i){
			Re a=ch[i]-'a';
			if(trans[p][a])p=trans[p][a];
			else flag=0;
		}
		printf("%d\n",flag?cnt[p]:0);
	}
}SAM;
int main(){
//	freopen("123.txt","r",stdin);
	in(n),in(T);
	for(Re i=1;i<=n;++i){
		scanf("%s",ch+1);Re last=1;
		for(Re j=1;ch[j];Len[i]=j,++j)last=SAM.insert(s[++t]=ch[j]-'a',last);
	}
	for(Re i=1,t=0;i<=n;++i)
		for(Re j=1,p=1;j<=Len[i];++j)
			SAM.updata(p=SAM.trans[p][s[++t]],i);
	while(T--)scanf("%s",ch+1),SAM.ask(ch);
}
