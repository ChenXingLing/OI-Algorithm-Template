#include<cstring>
#include<cstdio>
#define LL long long
#define Re register int
using namespace std;
const int base=1e8;
const int N=1e4+10;
int aux[N<<3];
struct Int{
    int s[N],l;
    inline void CL(){l=0;memset(s,0,sizeof(s));}
    inline void pr(){
        printf("%d",s[l]);
        for(Re i=l-1;i;i--)printf("%08d",s[i]);
    }
    inline void re_l(){
        Re i,x=0,k=1,L=0,fl,o;char c=getchar();
        for(;c<'0'||c>'9';c=getchar());
        for(;c>='0'&&c<='9';c=getchar()){if(!(L-1)&&!aux[L])L--;aux[++L]=c-'0';}
        CL();l=L/8+((o=L%8)>0);
        for(i=1;i<=o;i++)x=x*10+aux[i];
        if(o)s[l]=x;fl=!o?l+1:l;
        for(i=o+1,x=0;i<=L;i++,k++){
            x=x*10+aux[i];
            if(!(k^8))s[--fl]=x,x=k=0;
        }
        if(!l)l=1;
    }
    inline LL toint(){
        LL x=0;
        for(Re i=l;i;i--)x=x*base+s[i];
        return x;
    }
    inline Int operator=(Re b){
        CL();
        do s[++l]=b%base,b/=base;while(b>0);
        return *this;
    }
    inline Int operator=(LL b){
        CL();
        do s[++l]=b%base,b/=base;while(b>0);
        return *this;
    }
    inline Int operator+(const Re &b){
        Int c=*this;LL x=b;
        for(Re i=1;i<=l&&x;i++)x=x+c.s[i],c.s[i]=x%base,x/=base;
        if(x)c.s[++c.l]=x;
        return c;
    }
    inline Int operator+(const LL &b){
        Int c=*this;LL x=b;
        for(Re i=1;i<=l&&x;i++)x=x+c.s[i],c.s[i]=x%base,x/=base;
        if(x)c.s[++c.l]=x;
        return c;
    }
    inline Int operator+(Int &b){
        if(b.l<3)return *this+b.toint();
        Int c;LL x=0;Re k=l<b.l?b.l:l;c.CL(),c.l=k;
        for(Re i=1;i<=k;i++)x=x+s[i]+b.s[i],c.s[i]=x%base,x/=base;
        if(x)c.s[++c.l]=x;
        return c;
    }
    inline Int operator-(const Int &b){
        Int c,d=*this;LL x=0;c.CL();
        for(Re i=1;i<=l;i++){
            if((x=d.s[i])<b.s[i])d.s[i+1]--,x+=base;
            c.s[i]=x-b.s[i];
        }
        c.l=l;
        for(;!c.s[c.l]&&c.l>1;c.l--);
        return c;
    }
    inline Int operator-(const Re &b){Int c;return *this-(c=b);}
    inline Int operator-(const LL&b){Int c;return *this-(c=b);}
    inline Int operator*(const Re &b){
        Int c;LL x=0;c.CL();
        for(Re i=1;i<=l;i++)x=x+1LL*s[i]*b,c.s[i]=x%base,x/=base;
        for(c.l=l;x;x/=base)c.s[++c.l]=x%base;
        return c;
    }
    inline Int operator*(Int&b){
        if(b.l<2)return *this*b.toint();
        Int c;LL x;Re i,j,k;c.CL();
        for(i=1;i<=l;i++){
            x=0;
            for(j=1;j<=b.l;j++)x=x+1LL*s[i]*b.s[j]+c.s[k=i+j-1],c.s[k]=x%base,x/=base;
            if(x)c.s[i+b.l]=x;
        }
        for(c.l=l+b.l;!c.s[c.l]&&c.l>1;c.l--);
        return c;
    }
    inline Int operator*(const LL &b){
        Int c;
        if(b>2e9){c=b;return *this*c;}
        LL x=0;c.CL();
        for(Re i=1;i<=l;i++)x=x+b*s[i],c.s[i]=x%base,x/=base;
        for(c.l=l;x;x/=base)c.s[++c.l]=x%base;
        return c;
    }
    inline Int operator/(const Re &b){
        Int c;LL x=0;c.CL();
        for(Re i=l;i;i--)c.s[i]=(x*base+s[i])/b,x=(x*base+s[i])%b;
        for(c.l=l;!c.s[c.l]&&c.l>1;c.l--);
        return c;
    }
    inline Int operator/(const LL&b){
        Int c;LL x=0;c.CL();
        for(Re i=l;i;i--)c.s[i]=(x*base+s[i])/b,x=(x*base+s[i])%b;
        for(c.l=l;!c.s[c.l]&&c.l>1;c.l--);
        return c;
    }
    inline Int operator/(Int&b){
        if(b.l<2)return *this/b.toint();
        Int c,d;Re i,j,le,r,mid,k;c.CL();d.CL();
        for(i=l;i;i--){
            for(j=++d.l;j>1;j--)d.s[j]=d.s[j-1];
            d.s[1]=s[i];
            if(d<b)continue;
            le=k=0;r=base-1;
            while(le<=r){
                mid=(le+r)>>1;
                if(b*mid<=d)le=mid+1,k=mid;
                else r=mid-1;
            }
            c.s[i]=k,d=d-b*k;
        }
        for(c.l=l;!c.s[c.l]&&c.l>1;c.l--);
        return c;
    }
    inline Int operator%(const Re &b){
        Int c;LL x=0;c.CL();
        for(Re i=l;i;i--)x=(x*base+s[i])%b;
        return c=x;
    }
    inline Int operator%(const LL&b){
        Int c;LL x=0;c.CL();
        for(Re i=l;i;i--)x=(x*base+s[i])%b;
        return c=x;
    }
    inline Int operator%(Int&b){
        if(b.l<2)return *this%b.toint();
        Int c;Re i,j,le,r,mid,k;c.CL();
        for(i=l;i;i--){
            for(j=++c.l;j>1;j--)c.s[j]=c.s[j-1];
            c.s[1]=s[i];
            if(c<b)continue;
            le=k=0,r=base-1;
            while(le<=r){
                mid=(le+r)>>1;
                if(b*mid<=c)le=mid+1,k=mid;
                else r=mid-1;
            }
            c=c-b*k;
        }
        for(;!c.s[c.l]&&c.l>1;c.l--);
        return c;
    }
    inline Int operator+=(Int&b){return *this=*this+b;}
    inline Int operator+=(LL&b){return *this=*this+b;}
    inline Int operator+=(Re &b){return *this=*this+b;}
    inline Int operator-=(Int&b){return *this=*this-b;}
    inline Int operator-=(LL&b){return *this=*this-b;}
    inline Int operator-=(Re &b){return *this=*this-b;}
    inline Int operator*=(Int&b){return *this=*this*b;}
    inline Int operator*=(LL&b){return *this=*this*b;}
    inline Int operator*=(Re &b){return *this=*this*b;}
    inline Int operator/=(Int&b){return *this=*this/b;}
    inline Int operator/=(LL&b){return *this=*this/b;}
    inline Int operator/=(Re &b){return *this=*this/b;}
    inline Int operator%=(Int&b){return *this=*this%b;}
    inline Int operator%=(LL&b){return *this=*this%b;}
    inline Int operator%=(Re &b){return *this=*this%b;}
    inline bool operator<(const Int&b)const{
        if(l^b.l)return l<b.l;
        for(Re i=l;i;i--)if(s[i]^b.s[i])return s[i]<b.s[i];
        return 0;
    }
    inline bool operator<=(const Int&b)const{
        if(l^b.l)return l<b.l;
        for(Re i=l;i;i--)if(s[i]^b.s[i])return s[i]<b.s[i];
        return 1;
    }
    inline bool operator>(const Int&b)const{
        if(l^b.l)return l>b.l;
        for(Re i=l;i;i--)
            if(s[i]^b.s[i])return s[i]>b.s[i];
        return 0;
    }
    inline bool operator>=(const Int&b)const{
        if(l^b.l)return l>b.l;
        for(Re i=l;i;i--)if(s[i]^b.s[i])return s[i]>b.s[i];
        return 1;
    }
    inline bool operator==(const Int&b)const{
        if(l^b.l)return 0;
        for(Re i=l;i;i--)if(s[i]^b.s[i])return 0;
        return 1;
    }
    inline bool operator!=(const Int&b)const{
        if(l^b.l)return 1;
        for(Re i=l;i;i--)if(s[i]^b.s[i])return 1;
        return 0;
    }
    inline bool operator<(LL b)const{Int c;return *this<(c=b);}
    inline bool operator<=(LL b)const{Int c;return *this<=(c=b);}
    inline bool operator>(LL b)const{Int c;return *this>(c=b);}
    inline bool operator>=(LL b)const{Int c;return *this>=(c=b);}
    inline bool operator==(LL b)const{Int c;return *this==(c=b);}
    inline bool operator!=(LL b)const{Int c;return *this!=(c=b);}
    inline bool operator<(Re b)const{Int c;return *this<(c=b);}
    inline bool operator<=(Re b)const{Int c;return *this<=(c=b);}
    inline bool operator>(Re b)const{Int c;return *this>(c=b);}
    inline bool operator>=(Re b)const{Int c;return *this>=(c=b);}
    inline bool operator==(Re b)const{Int c;return *this==(c=b);}
    inline bool operator!=(Re b)const{Int c;return *this!=(c=b);}
};
Int a,b;
int main(){
    a.re_l();
    b.re_l();
    a.pr();printf("+");b.pr();printf("=");(a+b).pr();printf("\n");
    a.pr();printf("-");b.pr();printf("=");
    if(a<b){putchar('-');(b-a).pr();}
    else(a-b).pr();printf("\n");
    a.pr();printf("*");b.pr();printf("=");(a*b).pr();printf("\n");
    a.pr();printf("/");b.pr();printf("=");(a/b).pr();printf("\n");
    a.pr();printf("%%");b.pr();printf("=");(a%b).pr();printf("\n");
    if(a<b)printf("a<b\n");
    if(a<=b)printf("a<=b\n");
    if(a>b)printf("a>b\n");
    if(a>=b)printf("a>=b\n");
    if(a==b)printf("a==b\n");
    if(a!=b)printf("a!=b\n");
}
