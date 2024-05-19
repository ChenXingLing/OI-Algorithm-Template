#include<algorithm>
#include<cstdio>
#include<cmath>


/*一：【准备工作】*/
#define LD double
#define LL long long
#define Re register int
#define Vector Point
using namespace std;
const int N=262144+3;
const LD eps=1e-8,Pi=acos(-1.0);
inline int dcmp(LD a){return a<-eps?-1:(a>eps?1:0);}//处理精度
inline LD Abs(LD a){return a*dcmp(a);}//取绝对值
struct Point{
    LD x,y;Point(LD X=0,LD Y=0){x=X,y=Y;}
    inline void in(){scanf("%lf%lf",&x,&y);}
    inline void out(){printf("%.2lf %.2lf\n",x,y);}
};


/*二：【向量】*/
inline LD Dot(Vector a,Vector b){return a.x*b.x+a.y*b.y;}//【点积】
inline LD Cro(Vector a,Vector b){return a.x*b.y-a.y*b.x;}//【叉积】
inline LD Len(Vector a){return sqrt(Dot(a,a));}//【模长】
inline LD Angle(Vector a,Vector b){return acos(Dot(a,b)/Len(a)/Len(b));}//【两向量夹角】
inline Vector Normal(Vector a){return Vector(-a.y,a.x);}//【法向量】
inline Vector operator+(Vector a,Vector b){return Vector(a.x+b.x,a.y+b.y);}
inline Vector operator-(Vector a,Vector b){return Vector(a.x-b.x,a.y-b.y);}
inline Vector operator*(Vector a,LD b){return Vector(a.x*b,a.y*b);}
inline bool operator==(Point a,Point b){return !dcmp(a.x-b.x)&&!dcmp(a.y-b.y);}//两点坐标重合则相等


/*三：【点、向量的位置变换】*/

/*1.【点、向量的旋转】*/
inline Point turn_P(Point a,LD theta){//【点A\向量A顺时针旋转theta(弧度)】
    LD x=a.x*cos(theta)+a.y*sin(theta);
    LD y=-a.x*sin(theta)+a.y*cos(theta);
    return Point(x,y);
}
inline Point turn_PP(Point a,Point b,LD theta){//【将点A绕点B顺时针旋转theta(弧度)】
    LD x=(a.x-b.x)*cos(theta)+(a.y-b.y)*sin(theta)+b.x;
    LD y=-(a.x-b.x)*sin(theta)+(a.y-b.y)*cos(theta)+b.y;
    return Point(x,y);
}


/*四：【图形与图形之间的关系】*/

/*1.【点与线段】*/
inline int pan_PL(Point p,Point a,Point b){//【判断点P是否在线段AB上】
    return !dcmp(Cro(p-a,b-a))&&dcmp(Dot(p-a,p-b))<=0;//做法一
//  return !dcmp(Cro(p-a,b-a))&&dcmp(min(a.x,b.x)-p.x)<=0&&dcmp(p.x-max(a.x,b.x))<=0&&dcmp(min(a.y,b.y)-p.y)<=0&&dcmp(p.y-max(a.y,b.y))<=0;//做法二
    //PA,AB共线且P在AB之间(其实也可以用len(p-a)+len(p-b)==len(a-b)判断，但是精度损失较大)
}
inline LD dis_PL(Point p,Point a,Point b){//【点P到线段AB距离】
    if(a==b)return Len(p-a);//AB重合
    Vector x=p-a,y=p-b,z=b-a;
    if(dcmp(Dot(x,z))<0)return Len(x);//P距离A更近
    if(dcmp(Dot(y,z))>0)return Len(y);//P距离B更近
    return Abs(Cro(x,z)/Len(z));//面积除以底边长
}

/*2.【点与直线】*/
inline int pan_PL_(Point p,Point a,Point b){//【判断点P是否在直线AB上】
    return !dcmp(Cro(p-a,b-a));//PA,AB共线
}
inline Point FootPoint(Point p,Point a,Point b){//【点P到直线AB的垂足】
    Vector x=p-a,y=p-b,z=b-a;
    LD len1=Dot(x,z)/Len(z),len2=-1.0*Dot(y,z)/Len(z);//分别计算AP,BP在AB,BA上的投影
    return a+z*(len1/(len1+len2));//点A加上向量AF
}
inline Point Symmetry_PL(Point p,Point a,Point b){//【点P关于直线AB的对称点】
    return p+(FootPoint(p,a,b)-p)*2;//将PF延长一倍即可
}

/*3.【线与线】*/
inline Point cross_LL(Point a,Point b,Point c,Point d){//【两直线AB,CD的交点】
    Vector x=b-a,y=d-c,z=a-c;
    return a+x*(Cro(y,z)/Cro(x,y));//点A加上向量AF
}
inline int pan_cross_L_L(Point a,Point b,Point c,Point d){//【判断直线AB与线段CD是否相交】
    return pan_PL(cross_LL(a,b,c,d),c,d);//直线AB与直线CD的交点在线段CD上
}
inline int pan_cross_LL(Point a,Point b,Point c,Point d){//【判断两线段AB,CD是否相交】
    LD c1=Cro(b-a,c-a),c2=Cro(b-a,d-a);
    LD d1=Cro(d-c,a-c),d2=Cro(d-c,b-c);
    return dcmp(c1)*dcmp(c2)<0&&dcmp(d1)*dcmp(d2)<0;//分别在两侧
}

/*4.【点与多边形】*/
inline int PIP(Point *P,Re n,Point a){//【射线法】判断点A是否在任意多边形Poly以内
    Re cnt=0;LD tmp;
    for(Re i=1;i<=n;++i){
        Re j=i<n?i+1:1;
        if(pan_PL(a,P[i],P[j]))return 2;//点在多边形上
        if(a.y>=min(P[i].y,P[j].y)&&a.y<max(P[i].y,P[j].y))//纵坐标在该线段两端点之间
            tmp=P[i].x+(a.y-P[i].y)/(P[j].y-P[i].y)*(P[j].x-P[i].x),cnt+=dcmp(tmp-a.x)>0;//交点在A右方
    }
    return cnt&1;//穿过奇数次则在多边形以内
}
inline int judge(Point a,Point L,Point R){//判断AL是否在AR右边
    return dcmp(Cro(L-a,R-a))>0;//必须严格以内
}
inline int PIP_(Point *P,Re n,Point a){//【二分法】判断点A是否在凸多边形Poly以内
    //点按逆时针给出
    if(judge(P[1],a,P[2])||judge(P[1],P[n],a))return 0;//在P[1_2]或P[1_n]外
    if(pan_PL(a,P[1],P[2])||pan_PL(a,P[1],P[n]))return 2;//在P[1_2]或P[1_n]上
    Re l=2,r=n-1;
    while(l<r){//二分找到一个位置pos使得P[1]_A在P[1_pos],P[1_(pos+1)]之间
        Re mid=l+r+1>>1;
        if(judge(P[1],P[mid],a))l=mid;
        else r=mid-1;
    }
    if(judge(P[l],a,P[l+1]))return 0;//在P[pos_(pos+1)]外
    if(pan_PL(a,P[l],P[l+1]))return 2;//在P[pos_(pos+1)]上
    return 1;
}

/*5.【线与多边形】*/

/*6.【多边形与多边形】*/
inline int judge_PP(Point *A,Re n,Point *B,Re m){//【判断多边形A与多边形B是否相离】
    for(Re i1=1;i1<=n;++i1){
        Re j1=i1<n?i1+1:1;
        for(Re i2=1;i2<=m;++i2){
            Re j2=i2<m?i2+1:1;
            if(pan_cross_LL(A[i1],A[j1],B[i2],B[j2]))return 0;//两线段相交
            if(PIP(B,m,A[i1])||PIP(A,n,B[i2]))return 0;//点包含在内
        }
    }
    return 1;
}


/*五：【图形面积】*/

/*1.【任意多边形面积】*/
inline LD PolyArea(Point *P,Re n){//【任意多边形P的面积】
    LD S=0;
    for(Re i=1;i<=n;++i)S+=Cro(P[i],P[i<n?i+1:1]);
    return S/2.0;
}

/*2.【圆的面积并】*/

/*3.【三角形面积并】*/


/*六：【凸包】*/

/*1.【求凸包】*/
inline bool cmp1(Vector a,Vector b){return a.x==b.x?a.y<b.y:a.x<b.x;};//按坐标排序
inline int ConvexHull(Point *P,Re n,Point *cp){//【水平序Graham扫描法（Andrew算法）】求凸包
    sort(P+1,P+n+1,cmp1);
    Re t=0;
    for(Re i=1;i<=n;++i){//下凸包
        while(t>1&&dcmp(Cro(cp[t]-cp[t-1],P[i]-cp[t-1]))<=0)--t;
        cp[++t]=P[i];
    }
    Re St=t;
    for(Re i=n-1;i>=1;--i){//上凸包
        while(t>St&&dcmp(Cro(cp[t]-cp[t-1],P[i]-cp[t-1]))<=0)--t;
        cp[++t]=P[i];
    }
    return --t;//要减一
}
/*2.【旋转卡壳】*/

/*3.【半平面交】*/
struct Line{
    Point a,b;LD k;Line(Point A=Point(0,0),Point B=Point(0,0)){a=A,b=B,k=atan2(b.y-a.y,b.x-a.x);}
    inline bool operator<(const Line &O)const{return dcmp(k-O.k)?dcmp(k-O.k)<0:judge(O.a,O.b,a);}//如果角度相等则取左边的
}L[N],Q[N];
inline Point cross(Line L1,Line L2){return cross_LL(L1.a,L1.b,L2.a,L2.b);}//获取直线L1,L2的交点
inline int judge(Line L,Point a){return dcmp(Cro(a-L.a,L.b-L.a))>0;}//判断点a是否在直线L的右边
inline int halfcut(Line *L,Re n,Point *P){//【半平面交】
    sort(L+1,L+n+1);Re m=n;n=0;
    for(Re i=1;i<=m;++i)if(i==1||dcmp(L[i].k-L[i-1].k))L[++n]=L[i];
    Re h=1,t=0;
    for(Re i=1;i<=n;++i){
        while(h<t&&judge(L[i],cross(Q[t],Q[t-1])))--t;//当队尾两个直线交点不是在直线L[i]上或者左边时就出队
        while(h<t&&judge(L[i],cross(Q[h],Q[h+1])))++h;//当队头两个直线交点不是在直线L[i]上或者左边时就出队
        Q[++t]=L[i];
    }
    while(h<t&&judge(Q[h],cross(Q[t],Q[t-1])))--t;
    while(h<t&&judge(Q[t],cross(Q[h],Q[h+1])))++h;
    n=0;
    for(Re i=h;i<=t;++i)P[++n]=cross(Q[i],Q[i<t?i+1:h]);
    return n;
}

/*4.【闵可夫斯基和】*/
Vector V1[N],V2[N];
inline int Mincowski(Point *P1,Re n,Point *P2,Re m,Vector *V){//【闵可夫斯基和】求两个凸包{P1},{P2}的向量集合{V}={P1+P2}构成的凸包
    for(Re i=1;i<=n;++i)V1[i]=P1[i<n?i+1:1]-P1[i];
    for(Re i=1;i<=m;++i)V2[i]=P2[i<m?i+1:1]-P2[i];
    Re t=0,i=1,j=1;V[++t]=P1[1]+P2[1];
    while(i<=n&&j<=m)++t,V[t]=V[t-1]+(dcmp(Cro(V1[i],V2[j]))>0?V1[i++]:V2[j++]);
    while(i<=n)++t,V[t]=V[t-1]+V1[i++];
    while(j<=m)++t,V[t]=V[t-1]+V2[j++];
    return t;
}

/*5.【动态凸包】*/

/*七：【圆】*/

/*1.【三点确定一圆】*/
#define S(a) ((a)*(a))
struct Circle{Point O;LD r;Circle(Point P,LD R=0){O=P,r=R;}};
inline Circle getCircle(Point A,Point B,Point C){//【三点确定一圆】暴力解方程
    LD x1=A.x,y1=A.y,x2=B.x,y2=B.y,x3=C.x,y3=C.y;
    LD D=((S(x2)+S(y2)-S(x3)-S(y3))*(y1-y2)-(S(x1)+S(y1)-S(x2)-S(y2))*(y2-y3))/((x1-x2)*(y2-y3)-(x2-x3)*(y1-y2));
    LD E=(S(x1)+S(y1)-S(x2)-S(y2)+D*(x1-x2))/(y2-y1);
    LD F=-(S(x1)+S(y1)+D*x1+E*y1);
    return Circle(Point(-D/2.0,-E/2.0),sqrt((S(D)+S(E)-4.0*F)/4.0));
}
inline Circle getcircle(Point A,Point B,Point C){//【三点确定一圆】向量垂心法
    Point P1=(A+B)*0.5,P2=(A+C)*0.5;
    Point O=cross_LL(P1,P1+Normal(B-A),P2,P2+Normal(C-A));
    return Circle(O,Len(A-O));
}

/*2.【最小覆盖圆】*/
inline int PIC(Circle C,Point a){return dcmp(Len(a-C.O)-C.r)<=0;}//判断点A是否在圆C内
inline void Random(Point *P,Re n){for(Re i=1;i<=n;++i)swap(P[i],P[rand()%n+1]);}//随机一个排列
inline Circle Min_Circle(Point *P,Re n){//【求点集P的最小覆盖圆】
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

/*3.【三角剖分】*/
inline LD calc(Point A,Point B,Point O,LD R){//【三角剖分】
    if(A==O||B==O)return 0;
    Re op=dcmp(Cro(A-O,B-O))>0?1:-1;LD ans=0;
    Vector x=A-O,y=B-O;
    Re flag1=dcmp(Len(x)-R)>0,flag2=dcmp(Len(y)-R)>0;
    if(!flag1&&!flag2)ans=Abs(Cro(A-O,B-O))/2.0;//两个点都在里面
    else if(flag1&&flag2){//两个点都在外面
        if(dcmp(dis_PL(O,A,B)-R)>=0)ans=R*R*Angle(x,y)/2.0;//完全包含了圆弧
        else{//分三段处理 △+圆弧+△
            if(dcmp(Cro(A-O,B-O))>0)swap(A,B);//把A换到左边
            Point F=FootPoint(O,A,B);LD lenx=Len(F-O),len=sqrt(R*R-lenx*lenx);
            Vector z=turn_P(F-O,Pi/2.0)*(len/lenx);Point B_=F+z,A_=F-z;
            ans=R*R*(Angle(A-O,A_-O)+Angle(B-O,B_-O))/2.0+Cro(B_-O,A_-O)/2.0;
        }
    }
    else{//一个点在里面，一个点在外面
        if(flag1)swap(A,B);//使A为里面的点，B为外面的点
        Point F=FootPoint(O,A,B);LD lenx=Len(F-O),len=sqrt(R*R-lenx*lenx);
        Vector z=turn_P(F-O,Pi/2.0)*(len/lenx);Point C=dcmp(Cro(A-O,B-O))>0?F-z:F+z;
        ans=Abs(Cro(A-O,C-O))/2.0+R*R*Angle(C-O,B-O)/2.0;
    }
    return ans*op;
}

int main(){}
