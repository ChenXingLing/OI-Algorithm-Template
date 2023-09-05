#include<algorithm>
#include<cstring>
#include<cstdio>
#define LL long long
#define Re register int
using namespace std;
const int N=4e5+10;
int n,x,y,T;LL P,M,G,K;char s[N>>1];
inline void in(Re &x){
    int f=0;x=0;char c=getchar();
    while(c<'0'||c>'9')f|=c=='-',c=getchar();
    while(c>='0'&&c<='9')x=(x<<1)+(x<<3)+(c^48),c=getchar();
    x=f?-x:x;
}
struct Sakura2{
    int O,last,pos[N],siz[N],link[N],maxlen[N],trans[N][26];
    //siz[x]: �ڵ�x�ĳ��ִ��� (endpos�Ĵ�С)
    //link[x]: x��parent���ϵĸ���
    //pos[x]: �ڵ�xĳһ�γ���λ�� (���ڹ�����׺���е�ѹ����link[x]->x����
    ///��ת���s�� �������pos[x]-maxlen[link[x]] -> pos[x]-maxlen[x]+1�õ����ַ��� ��Ϊ��׺���е�ѹ���� link[x]->x
    inline void insert(Re ch,Re id){//SAM�½��ڵ�
        Re z=++O,p=last;pos[z]=id,siz[z]=1,maxlen[z]=maxlen[last]+1;
        while(p&&!trans[p][ch])trans[p][ch]=z,p=link[p];
        if(!p)link[z]=1;
        else{
            Re x=trans[p][ch];
            if(maxlen[p]+1==maxlen[x])link[z]=x;
            else{
                Re y=++O;maxlen[y]=maxlen[p]+1,pos[y]=pos[x];
                for(Re i=0;i<26;++i)trans[y][i]=trans[x][i];
                while(p&&trans[p][ch]==x)trans[p][ch]=y,p=link[p];
                link[y]=link[x],link[z]=link[x]=y;
            }
        }
        last=z;
    }
    int t,ID[N],to[N][26];LL S[N];
    //to[x][ch]: ��׺����trans����
    //ID[x]: ˳�������׺���ĵ�x���ڵ��� 
    //S[x]: ˳�������׺����ǰx���ڵ��ܹ������˶��ٸ��ַ�
    inline void dfs1(Re x){//���� SAM��parent��\��׺�� ��ȡsiz
        for(Re i=0;i<26;++i)
            if(to[x][i])dfs1(to[x][i]),siz[x]+=siz[to[x][i]];
    }
    inline void dfs2(Re x){//���� SAM��parent��\��׺�� ��ȡ�ڵ�˳��
        if(x!=1)ID[++t]=x;//û�д�����Ϣ�ĸ��ڵ�1�Ͳ�Ҫ��
        for(Re i=0;i<26;++i)if(to[x][i])dfs2(to[x][i]);
    }
    inline LL calc(Re L,Re R){return 1ll*(L+R)*(R-L+1)/2;}//�����L�ӵ�R�ĵȲ����� 
    inline void build(){
        last=O=1;//���ڵ���Ϊ1
        for(Re i=1;i<=n/2;++i)swap(s[i],s[n-i+1]);//��תԭ�ַ���
        for(Re i=1;i<=n;++i)insert(s[i]-'a',i);
        for(Re i=2;i<=O;++i)to[link[i]][s[pos[i]-maxlen[link[i]]]-'a']=i;//������׺����
        //����pos[x]��endpos[x]�е�����һ�������Ի�ȡ��link[x]->xѹ�������ַ�����Ϣʱֻ����pos[x]��������pos[link[x]]
        dfs1(1),dfs2(1);//���� SAM��parent��\��׺��
        for(Re i=1;i<=t;++i)x=ID[i],S[i]=S[i-1]+1ll*siz[x]*calc(maxlen[link[x]]+1,maxlen[x]);
    }
    inline char ask(LL K){
        Re l=1,r=t,x;
        while(l<r){//�����ҵ���һ�����ڵ���K��λ��
            Re mid=l+r>>1;
            if(S[mid]<K)l=mid+1;
            else r=mid;
        }
        x=ID[l],K-=S[l-1],l=maxlen[link[x]]+1,r=maxlen[x];
        while(l<r){//�����ҵ���һ�����ڵ���K��λ��
            Re mid=l+r>>1;
            if(1ll*siz[x]*calc(maxlen[link[x]]+1,mid)<K)l=mid+1;
            else r=mid;
        }
        K-=1ll*siz[x]*calc(maxlen[link[x]]+1,l-1),K=(K-1)%l+1;//ע��ȡģ�ķ�ʽ 
        return s[pos[x]-K+1];//ע�ⷽ����������Kλ
    }
    char ans;
    inline void sakura(){
        build();
        while(T--)scanf("%lld%lld",&P,&M),K=P*G%M+1,G+=(ans=ask(K)),putchar(ans),puts("");
    }
}T2;
int main(){
    freopen("letter.in","r",stdin);
    freopen("letter.out","w",stdout);
    scanf("%s",s+1),n=strlen(s+1);in(T);
    T2.sakura();
    fclose(stdin);
    fclose(stdout);
}
