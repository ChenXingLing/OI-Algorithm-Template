#pragma GCC optimize(2)
#pragma GCC optimize(3,"Ofast","inline")
#include<algorithm>
#include<cstring>
#include<cstdio>
#define mid (L+R>>1)
#define Re register int
#define pl tree[p].lp
#define pr tree[p].rp
#define F(i,a,b) for(Re i=a;i<=b;++i)
#define lo(o) lower_bound(b+1,b+m+1,o)-b
using namespace std;
const int N=1e5+3,inf=2147483647;//��N����2 WA���졿����Ҫ��ɢ�������ϲ�ѯ���n+m(��2*n)������
int x,y,z,n,m,T,t,fu,cnt,tl,tr,a[N],b[N],pt[N],C[N],opt[N],ptl[20],ptr[20]; 
struct QAQ{int g,lp,rp;}tree[N*250];//��Ӧ��17*17=289����,��Сһ��Ҳ����ν����Ϊ�����ò���
struct O_O{int l,r,k;}Q[N];//����Q�β�ѯ�ľ������ݣ�������ɢ��
struct T_T{int i,x;}c[N];//�����޸ĵľ�������
inline void in(Re &x){
    x=fu=0;char c=getchar();
    while(c<'0'||c>'9')fu|=c=='-',c=getchar();
    while(c>='0'&&c<='9')x=(x<<1)+(x<<3)+(c^48),c=getchar();
    x=fu?-x:x;
}
inline int ask_kth(Re L,Re R,Re k){//��ѯ��kС
    if(L==R)return b[R];//��ӳ����� WA���졿ע�⣺���ص�ֵ��Ҫ�õ�������һ��ӳ�����鲻�ܸ��
    Re tmp=0;
    F(i,1,tl)tmp-=tree[tree[ptl[i]].lp].g;//������������Ϣ
    F(i,1,tr)tmp+=tree[tree[ptr[i]].lp].g;//������������Ϣ
    if(tmp>=k){
    	F(i,1,tl)ptl[i]=tree[ptl[i]].lp;//����ptl,ptr��ָ��Ľڵ���
    	F(i,1,tr)ptr[i]=tree[ptr[i]].lp;
    	return ask_kth(L,mid,k);
    }
    else{
    	F(i,1,tl)ptl[i]=tree[ptl[i]].rp;
    	F(i,1,tr)ptr[i]=tree[ptr[i]].rp;
    	return ask_kth(mid+1,R,k-tmp);
    }
}
inline int ask_kth_pre(Re L,Re R,Re k){//��ѯ��kС(��תվ)
    tl=tr=0;//(ע��L-1)
    for(Re i=L-1;i;i-=i&-i)ptl[++tl]=pt[i];//�Ȱ�����Ҫ���µ�λ�õ��߶������ڵ��¼����
    for(Re i=R;i;i-=i&-i)ptr[++tr]=pt[i];//�������ݹ������Ϣ
    return ask_kth(1,m,k);
}
inline void add(Re &p,Re L,Re R,Re w,Re v){//�������޸ġ�
    if(!p)p=++cnt;tree[p].g+=v;
    if(L==R)return;
    if(w<=mid)add(pl,L,mid,w,v);
    else add(pr,mid+1,R,w,v);
}
inline void add_pre(Re x,Re v){//�������޸ġ�
    Re w=lo(a[x]);//��ӳ����� TLE���졿ע�⺯���������Ĳ���x����ԭ���е�λ��c[i].i(�������ԭ����)���������ӳ������ĵ��ò�Ҫ���
    for(Re i=x;i<=n;i+=i&-i)add(pt[i],1,m,w,v);//��״����˼�������Ϣ
}
inline int ask_level(Re p,Re L,Re R,Re x){//��ѯС�ڵ���x�����ĸ���
	if(L==R)return tree[p].g; 
	if(x<=mid)return ask_level(pl,L,mid,x);
	else return tree[pl].g+ask_level(pr,mid+1,R,x);
}
inline int ask_level_pre(Re L,Re R,Re w){//��ѯx������(��תվ)
	Re ans=0;
    for(Re i=R;i;i-=i&-i)ans+=ask_level(pt[i],1,m,w);
    for(Re i=L-1;i;i-=i&-i)ans-=ask_level(pt[i],1,m,w);
    return ans;
}
int main(){
//	printf("%lf\n",(sizeof(tree))/1024.0/1024.0);
//	printf("%lf\n",(sizeof(tree)+sizeof(Q)+sizeof(c)+sizeof(a)+sizeof(b)+sizeof(pt)+sizeof(C))/1024.0/1024.0);
	in(n),in(T),m=n;
    F(i,1,n)in(a[i]),b[i]=a[i];
    F(i,1,T){
    	in(opt[i]);
    	if(opt[i]==3)in(c[i].i),in(c[i].x),b[++m]=c[i].x;
    	else{
    		in(Q[i].l),in(Q[i].r),in(Q[i].k);
    		if(opt[i]!=2)b[++m]=Q[i].k;//������ɢ WA���졿����2�Ĳ�ѯ���ùܣ������ط����ֵ�kȫ����Ҫ��ɢ��
		}
    }
    sort(b+1,b+m+1);
    m=unique(b+1,b+m+1)-b-1;//unique()��-(b+1),lower_bound()��-b
    F(i,1,n)add_pre(i,1);//��ʼ������
    F(i,1,T){
    	if(opt[i]==1)//��ѯx������(��תվ)
    		Q[i].k=lo(Q[i].k),//��ֱ�Ӳ�ѯ WA���졿�Ȳ�ѯQ[i].k��b�еĵ�λ�ã������һ��� ����ǰһ���� ���ܸ���
			printf("%d\n",ask_level_pre(Q[i].l,Q[i].r,Q[i].k-1)+1);//�ټ�һ���Q[i].k�����������Ͽ�����Ч�ܹ�Q[i].k�ĸ�������

    	if(opt[i]==2)
    		printf("%d\n",ask_kth_pre(Q[i].l,Q[i].r,Q[i].k));//��ѯ��kС(��תվ)

		if(opt[i]==3)//�޸�ĳһλֵ�ϵ���ֵ(��תվ)
			add_pre(c[i].i,-1),a[c[i].i]=c[i].x,add_pre(c[i].i,1);
		//�������λ����ԭ����������һ�����������ֺ��ٰ�������һ�����ʹﵽ���滻��Ŀ��

		if(opt[i]==4){//��ѯǰ��(�ϸ�С��)
/*1>ȡλ��*/Q[i].k=lo(Q[i].k);//��ֱ�Ӳ�ѯ WA���졿�Ȳ�ѯQ[i].k��b�е�λ�ã�����λ�ü�һ��ѯ��ǰ�� 
/*2>������*/Re level=ask_level_pre(Q[i].l,Q[i].r,Q[i].k-1);//��Ϊ����ɢ�����������Ҳ���Q[i].k-1������ֵģ����Բ���ֱ�Ӳ�ѯ������ֵ
/*3>������*/if(!level)printf("%d\n",-inf);//���ж��������� WA�����졿��������level��ȡ����ǰ����b�е�λ�ã�����ֻҪ��level>0���Ϳ�����
			//(����㰴�����桾ֱ�Ӳ�ѯ WA���졿��ע�͸��˴��룬ȴû�и�����ġ������жϡ�����ô���level<=1�������㡾WA���졿)��
/*4>�ҽ��*/else printf("%d\n",ask_kth_pre(Q[i].l,Q[i].r,level)); 
		}

		if(opt[i]==5){//��ѯ�Ｑ(�ϸ����)��äĿ���� WA���졿����������ͬ�ϵķ��������������̰�
/*1>ȡλ��*/Q[i].k=lo(Q[i].k);
/*2>������*/Re level=ask_level_pre(Q[i].l,Q[i].r,Q[i].k);//��ֱ�Ӳ�ѯ WA���졿���ͬ�ϣ���Խ�磬�����Խ����b[0]=0���Բ��ţ��ٺ٣�������b[n+1]=0�Ͳ�����Ӵ
/*3>������*/if(level==Q[i].r-Q[i].l+1)printf("%d\n",inf);//���ж��������� WA���졿����ＱӦ��level+1����������Ӧ�ǡ�level�������ܳ��ȡ�
/*4>�ҽ��*/else printf("%d\n",ask_kth_pre(Q[i].l,Q[i].r,level+1));//��äĿ���� WA���졿 �����˼�һ����ǰ����ͬ����
		}
    }
}
