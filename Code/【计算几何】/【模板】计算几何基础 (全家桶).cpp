#include<algorithm>
#include<cstdio>
#include<cmath>


/*һ����׼��������*/
#define LD double
#define LL long long
#define Re register int
#define Vector Point
using namespace std;
const int N=262144+3;
const LD eps=1e-8,Pi=acos(-1.0);
inline int dcmp(LD a){return a<-eps?-1:(a>eps?1:0);}//������
inline LD Abs(LD a){return a*dcmp(a);}//ȡ����ֵ
struct Point{
    LD x,y;Point(LD X=0,LD Y=0){x=X,y=Y;}
    inline void in(){scanf("%lf%lf",&x,&y);}
    inline void out(){printf("%.2lf %.2lf\n",x,y);}
};


/*������������*/
inline LD Dot(Vector a,Vector b){return a.x*b.x+a.y*b.y;}//�������
inline LD Cro(Vector a,Vector b){return a.x*b.y-a.y*b.x;}//�������
inline LD Len(Vector a){return sqrt(Dot(a,a));}//��ģ����
inline LD Angle(Vector a,Vector b){return acos(Dot(a,b)/Len(a)/Len(b));}//���������нǡ�
inline Vector Normal(Vector a){return Vector(-a.y,a.x);}//����������
inline Vector operator+(Vector a,Vector b){return Vector(a.x+b.x,a.y+b.y);}
inline Vector operator-(Vector a,Vector b){return Vector(a.x-b.x,a.y-b.y);}
inline Vector operator*(Vector a,LD b){return Vector(a.x*b,a.y*b);}
inline bool operator==(Point a,Point b){return !dcmp(a.x-b.x)&&!dcmp(a.y-b.y);}//���������غ������


/*�������㡢������λ�ñ任��*/

/*1.���㡢��������ת��*/
inline Point turn_P(Point a,LD theta){//����A\����A˳ʱ����תtheta(����)��
    LD x=a.x*cos(theta)+a.y*sin(theta);
    LD y=-a.x*sin(theta)+a.y*cos(theta);
    return Point(x,y);
}
inline Point turn_PP(Point a,Point b,LD theta){//������A�Ƶ�B˳ʱ����תtheta(����)��
    LD x=(a.x-b.x)*cos(theta)+(a.y-b.y)*sin(theta)+b.x;
    LD y=-(a.x-b.x)*sin(theta)+(a.y-b.y)*cos(theta)+b.y;
    return Point(x,y);
}


/*�ģ���ͼ����ͼ��֮��Ĺ�ϵ��*/

/*1.�������߶Ρ�*/
inline int pan_PL(Point p,Point a,Point b){//���жϵ�P�Ƿ����߶�AB�ϡ�
    return !dcmp(Cro(p-a,b-a))&&dcmp(Dot(p-a,p-b))<=0;//����һ
//  return !dcmp(Cro(p-a,b-a))&&dcmp(min(a.x,b.x)-p.x)<=0&&dcmp(p.x-max(a.x,b.x))<=0&&dcmp(min(a.y,b.y)-p.y)<=0&&dcmp(p.y-max(a.y,b.y))<=0;//������
    //PA,AB������P��AB֮��(��ʵҲ������len(p-a)+len(p-b)==len(a-b)�жϣ����Ǿ�����ʧ�ϴ�)
}
inline LD dis_PL(Point p,Point a,Point b){//����P���߶�AB���롿
    if(a==b)return Len(p-a);//AB�غ�
    Vector x=p-a,y=p-b,z=b-a;
    if(dcmp(Dot(x,z))<0)return Len(x);//P����A����
    if(dcmp(Dot(y,z))>0)return Len(y);//P����B����
    return Abs(Cro(x,z)/Len(z));//������Եױ߳�
}

/*2.������ֱ�ߡ�*/
inline int pan_PL_(Point p,Point a,Point b){//���жϵ�P�Ƿ���ֱ��AB�ϡ�
    return !dcmp(Cro(p-a,b-a));//PA,AB����
}
inline Point FootPoint(Point p,Point a,Point b){//����P��ֱ��AB�Ĵ��㡿
    Vector x=p-a,y=p-b,z=b-a;
    LD len1=Dot(x,z)/Len(z),len2=-1.0*Dot(y,z)/Len(z);//�ֱ����AP,BP��AB,BA�ϵ�ͶӰ
    return a+z*(len1/(len1+len2));//��A��������AF
}
inline Point Symmetry_PL(Point p,Point a,Point b){//����P����ֱ��AB�ĶԳƵ㡿
    return p+(FootPoint(p,a,b)-p)*2;//��PF�ӳ�һ������
}

/*3.�������ߡ�*/
inline Point cross_LL(Point a,Point b,Point c,Point d){//����ֱ��AB,CD�Ľ��㡿
    Vector x=b-a,y=d-c,z=a-c;
    return a+x*(Cro(y,z)/Cro(x,y));//��A��������AF
}
inline int pan_cross_L_L(Point a,Point b,Point c,Point d){//���ж�ֱ��AB���߶�CD�Ƿ��ཻ��
    return pan_PL(cross_LL(a,b,c,d),c,d);//ֱ��AB��ֱ��CD�Ľ������߶�CD��
}
inline int pan_cross_LL(Point a,Point b,Point c,Point d){//���ж����߶�AB,CD�Ƿ��ཻ��
    LD c1=Cro(b-a,c-a),c2=Cro(b-a,d-a);
    LD d1=Cro(d-c,a-c),d2=Cro(d-c,b-c);
    return dcmp(c1)*dcmp(c2)<0&&dcmp(d1)*dcmp(d2)<0;//�ֱ�������
}

/*4.���������Ρ�*/
inline int PIP(Point *P,Re n,Point a){//�����߷����жϵ�A�Ƿ�����������Poly����
    Re cnt=0;LD tmp;
    for(Re i=1;i<=n;++i){
        Re j=i<n?i+1:1;
        if(pan_PL(a,P[i],P[j]))return 2;//���ڶ������
        if(a.y>=min(P[i].y,P[j].y)&&a.y<max(P[i].y,P[j].y))//�������ڸ��߶����˵�֮��
            tmp=P[i].x+(a.y-P[i].y)/(P[j].y-P[i].y)*(P[j].x-P[i].x),cnt+=dcmp(tmp-a.x)>0;//������A�ҷ�
    }
    return cnt&1;//�������������ڶ��������
}
inline int judge(Point a,Point L,Point R){//�ж�AL�Ƿ���AR�ұ�
    return dcmp(Cro(L-a,R-a))>0;//�����ϸ�����
}
inline int PIP_(Point *P,Re n,Point a){//�����ַ����жϵ�A�Ƿ���͹�����Poly����
    //�㰴��ʱ�����
    if(judge(P[1],a,P[2])||judge(P[1],P[n],a))return 0;//��P[1_2]��P[1_n]��
    if(pan_PL(a,P[1],P[2])||pan_PL(a,P[1],P[n]))return 2;//��P[1_2]��P[1_n]��
    Re l=2,r=n-1;
    while(l<r){//�����ҵ�һ��λ��posʹ��P[1]_A��P[1_pos],P[1_(pos+1)]֮��
        Re mid=l+r+1>>1;
        if(judge(P[1],P[mid],a))l=mid;
        else r=mid-1;
    }
    if(judge(P[l],a,P[l+1]))return 0;//��P[pos_(pos+1)]��
    if(pan_PL(a,P[l],P[l+1]))return 2;//��P[pos_(pos+1)]��
    return 1;
}

/*5.���������Ρ�*/

/*6.������������Ρ�*/
inline int judge_PP(Point *A,Re n,Point *B,Re m){//���ж϶����A������B�Ƿ����롿
    for(Re i1=1;i1<=n;++i1){
        Re j1=i1<n?i1+1:1;
        for(Re i2=1;i2<=m;++i2){
            Re j2=i2<m?i2+1:1;
            if(pan_cross_LL(A[i1],A[j1],B[i2],B[j2]))return 0;//���߶��ཻ
            if(PIP(B,m,A[i1])||PIP(A,n,B[i2]))return 0;//���������
        }
    }
    return 1;
}


/*�壺��ͼ�������*/

/*1.���������������*/
inline LD PolyArea(Point *P,Re n){//����������P�������
    LD S=0;
    for(Re i=1;i<=n;++i)S+=Cro(P[i],P[i<n?i+1:1]);
    return S/2.0;
}

/*2.��Բ���������*/

/*3.���������������*/


/*������͹����*/

/*1.����͹����*/
inline bool cmp1(Vector a,Vector b){return a.x==b.x?a.y<b.y:a.x<b.x;};//����������
inline int ConvexHull(Point *P,Re n,Point *cp){//��ˮƽ��Grahamɨ�跨��Andrew�㷨������͹��
    sort(P+1,P+n+1,cmp1);
    Re t=0;
    for(Re i=1;i<=n;++i){//��͹��
        while(t>1&&dcmp(Cro(cp[t]-cp[t-1],P[i]-cp[t-1]))<=0)--t;
        cp[++t]=P[i];
    }
    Re St=t;
    for(Re i=n-1;i>=1;--i){//��͹��
        while(t>St&&dcmp(Cro(cp[t]-cp[t-1],P[i]-cp[t-1]))<=0)--t;
        cp[++t]=P[i];
    }
    return --t;//Ҫ��һ
}
/*2.����ת���ǡ�*/

/*3.����ƽ�潻��*/
struct Line{
    Point a,b;LD k;Line(Point A=Point(0,0),Point B=Point(0,0)){a=A,b=B,k=atan2(b.y-a.y,b.x-a.x);}
    inline bool operator<(const Line &O)const{return dcmp(k-O.k)?dcmp(k-O.k)<0:judge(O.a,O.b,a);}//����Ƕ������ȡ��ߵ�
}L[N],Q[N];
inline Point cross(Line L1,Line L2){return cross_LL(L1.a,L1.b,L2.a,L2.b);}//��ȡֱ��L1,L2�Ľ���
inline int judge(Line L,Point a){return dcmp(Cro(a-L.a,L.b-L.a))>0;}//�жϵ�a�Ƿ���ֱ��L���ұ�
inline int halfcut(Line *L,Re n,Point *P){//����ƽ�潻��
    sort(L+1,L+n+1);Re m=n;n=0;
    for(Re i=1;i<=m;++i)if(i==1||dcmp(L[i].k-L[i-1].k))L[++n]=L[i];
    Re h=1,t=0;
    for(Re i=1;i<=n;++i){
        while(h<t&&judge(L[i],cross(Q[t],Q[t-1])))--t;//����β����ֱ�߽��㲻����ֱ��L[i]�ϻ������ʱ�ͳ���
        while(h<t&&judge(L[i],cross(Q[h],Q[h+1])))++h;//����ͷ����ֱ�߽��㲻����ֱ��L[i]�ϻ������ʱ�ͳ���
        Q[++t]=L[i];
    }
    while(h<t&&judge(Q[h],cross(Q[t],Q[t-1])))--t;
    while(h<t&&judge(Q[t],cross(Q[h],Q[h+1])))++h;
    n=0;
    for(Re i=h;i<=t;++i)P[++n]=cross(Q[i],Q[i<t?i+1:h]);
    return n;
}

/*4.���ɿɷ�˹���͡�*/
Vector V1[N],V2[N];
inline int Mincowski(Point *P1,Re n,Point *P2,Re m,Vector *V){//���ɿɷ�˹���͡�������͹��{P1},{P2}����������{V}={P1+P2}���ɵ�͹��
    for(Re i=1;i<=n;++i)V1[i]=P1[i<n?i+1:1]-P1[i];
    for(Re i=1;i<=m;++i)V2[i]=P2[i<m?i+1:1]-P2[i];
    Re t=0,i=1,j=1;V[++t]=P1[1]+P2[1];
    while(i<=n&&j<=m)++t,V[t]=V[t-1]+(dcmp(Cro(V1[i],V2[j]))>0?V1[i++]:V2[j++]);
    while(i<=n)++t,V[t]=V[t-1]+V1[i++];
    while(j<=m)++t,V[t]=V[t-1]+V2[j++];
    return t;
}

/*5.����̬͹����*/

/*�ߣ���Բ��*/

/*1.������ȷ��һԲ��*/
#define S(a) ((a)*(a))
struct Circle{Point O;LD r;Circle(Point P,LD R=0){O=P,r=R;}};
inline Circle getCircle(Point A,Point B,Point C){//������ȷ��һԲ�������ⷽ��
    LD x1=A.x,y1=A.y,x2=B.x,y2=B.y,x3=C.x,y3=C.y;
    LD D=((S(x2)+S(y2)-S(x3)-S(y3))*(y1-y2)-(S(x1)+S(y1)-S(x2)-S(y2))*(y2-y3))/((x1-x2)*(y2-y3)-(x2-x3)*(y1-y2));
    LD E=(S(x1)+S(y1)-S(x2)-S(y2)+D*(x1-x2))/(y2-y1);
    LD F=-(S(x1)+S(y1)+D*x1+E*y1);
    return Circle(Point(-D/2.0,-E/2.0),sqrt((S(D)+S(E)-4.0*F)/4.0));
}
inline Circle getcircle(Point A,Point B,Point C){//������ȷ��һԲ���������ķ�
    Point P1=(A+B)*0.5,P2=(A+C)*0.5;
    Point O=cross_LL(P1,P1+Normal(B-A),P2,P2+Normal(C-A));
    return Circle(O,Len(A-O));
}

/*2.����С����Բ��*/
inline int PIC(Circle C,Point a){return dcmp(Len(a-C.O)-C.r)<=0;}//�жϵ�A�Ƿ���ԲC��
inline void Random(Point *P,Re n){for(Re i=1;i<=n;++i)swap(P[i],P[rand()%n+1]);}//���һ������
inline Circle Min_Circle(Point *P,Re n){//����㼯P����С����Բ��
//  random_shuffle(P+1,P+n+1);
    Random(P,n);Circle C=Circle(P[1],0);
    for(Re i=2;i<=n;++i)if(!PIC(C,P[i])){
        C=Circle(P[i],0);
        for(Re j=1;j<i;++j)if(!PIC(C,P[j])){
            C.O=(P[i]+P[j])*0.5,C.r=Len(P[j]-C.O);
            for(Re k=1;k<j;++k)if(!PIC(C,P[k]))C=getcircle(P[i],P[j],P[k]);
        }
    }
    return C;
}

/*3.�������ʷ֡�*/
inline LD calc(Point A,Point B,Point O,LD R){//�������ʷ֡�
    if(A==O||B==O)return 0;
    Re op=dcmp(Cro(A-O,B-O))>0?1:-1;LD ans=0;
    Vector x=A-O,y=B-O;
    Re flag1=dcmp(Len(x)-R)>0,flag2=dcmp(Len(y)-R)>0;
    if(!flag1&&!flag2)ans=Abs(Cro(A-O,B-O))/2.0;//�����㶼������
    else if(flag1&&flag2){//�����㶼������
        if(dcmp(dis_PL(O,A,B)-R)>=0)ans=R*R*Angle(x,y)/2.0;//��ȫ������Բ��
        else{//�����δ��� ��+Բ��+��
            if(dcmp(Cro(A-O,B-O))>0)swap(A,B);//��A�������
            Point F=FootPoint(O,A,B);LD lenx=Len(F-O),len=sqrt(R*R-lenx*lenx);
            Vector z=turn_P(F-O,Pi/2.0)*(len/lenx);Point B_=F+z,A_=F-z;
            ans=R*R*(Angle(A-O,A_-O)+Angle(B-O,B_-O))/2.0+Cro(B_-O,A_-O)/2.0;
        }
    }
    else{//һ���������棬һ����������
        if(flag1)swap(A,B);//ʹAΪ����ĵ㣬BΪ����ĵ�
        Point F=FootPoint(O,A,B);LD lenx=Len(F-O),len=sqrt(R*R-lenx*lenx);
        Vector z=turn_P(F-O,Pi/2.0)*(len/lenx);Point C=dcmp(Cro(A-O,B-O))>0?F-z:F+z;
        ans=Abs(Cro(A-O,C-O))/2.0+R*R*Angle(C-O,B-O)/2.0;
    }
    return ans*op;
}

int main(){}
