#include<cmath>
#include<vector>
#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
typedef long long LL;
int T,n,xx,yy;
 
struct point
{
  LL x,y;
  point(LL x=0,LL y=0):x(x),y(y){}
  bool operator==(const point&a) const
  {
    return x==a.x||y==a.y;
  }
};
 
LL dis(const point&a,const point&b)
{
  return (a.x-b.x)*(a.x-b.x)+(a.y-b.y)*(a.y-b.y);
}
 
vector<point> a,b;
vector<LL> x,y;
 
bool check()
{
  x.clear();  y.clear();
  int lena=a.size(),lenb=b.size(),flaga=0,flagb=0;
  for (int i=0;i<lena;i++) flaga+=a[i]==a[(i+1)%lena];
  for (int i=0;i<lenb;i++) flagb+=b[i]==b[(i+1)%lenb];
  if (lena==4&&lenb==4&&flaga>=3&&flagb>=3&&flaga==flagb)
  {
    if (flaga==4)
    {
      for (int i=0;i<4;i++) 
      {
        x.push_back(dis(a[i],a[(i+1)%4]));
        y.push_back(dis(b[i],b[(i+1)%4]));
      }
      return x[0]==y[0]||x[0]==y[1]||x[1]==y[0]||x[1]==y[1];
    }
    else 
    {
      for (int i=0;i<4;i++) 
      {
        if (a[i]==a[(i+1)%4]) continue;
        int x1=i,x2=(i+1)%4,x3=(i+2)%4,x4=(i+3)%4;
        x.push_back(dis(a[x1],a[x2]));
        LL k=sqrt(1.0*dis(a[x2],a[x3]))-sqrt(1.0*dis(a[x1],a[x4]));
        x.push_back(k*k);
        x.push_back(dis(a[x3],a[x4]));
      }
      for (int i=0;i<4;i++) 
      {
        if (b[i]==b[(i+1)%4]) continue;
        int x1=i,x2=(i+1)%4,x3=(i+2)%4,x4=(i+3)%4;
        y.push_back(dis(b[x1],b[x2]));
        LL k=sqrt(1.0*dis(b[x2],b[x3]))-sqrt(1.0*dis(b[x1],b[x4]));
        y.push_back(k*k);
        y.push_back(dis(b[x3],b[x4]));
      }
      return x==y;
    }
  }
  if (lena!=3||flaga!=2) return false;
  for (int i=0;i<3;i++) x.push_back(dis(a[i],a[(i+1)%3]));
  if (lenb==3&&flagb==2) for (int i=0;i<3;i++) y.push_back(dis(b[i],b[(i+1)%3]));
  if (lenb==4&&flagb==3)
  {
    for (int i=0;i<4;i++) 
    {
      if (b[i]==b[(i+1)%4]) continue;
      int x1=i,x2=(i+1)%4,x3=(i+2)%4,x4=(i+3)%4;
      y.push_back(dis(b[x1],b[x2]));
      LL k=sqrt(1.0*dis(b[x2],b[x3]))-sqrt(1.0*dis(b[x1],b[x4]));
      y.push_back(k*k);
      y.push_back(dis(b[x3],b[x4]));
    }
  }
  if (lenb==5&&flagb==4)
  {
    for (int i=0;i<5;i++) 
    {
      if (b[i]==b[(i+1)%5]) continue;
      int x1=i,x2=(i+1)%5,x3=(i+2)%5,x4=(i+3)%5,x5=(i+4)%5;
      y.push_back(dis(b[x1],b[x2]));
      LL k=sqrt(1.0*dis(b[x2],b[x3]))-sqrt(1.0*dis(b[x4],b[x5]));
      y.push_back(k*k);
      k=sqrt(1.0*dis(b[x3],b[x4]))-sqrt(1.0*dis(b[x5],b[x1]));
      y.push_back(k*k);
    }
  }
  sort(x.begin(),x.end());
  sort(y.begin(),y.end());
  return x==y;
}
 
int main()
{
  scanf("%d",&T);
  while (T--)
  {
    a.clear();  b.clear();
    scanf("%d",&n); while (n--) {scanf("%d%d",&xx,&yy); a.push_back(point(xx,yy));}
    scanf("%d",&n); while (n--) {scanf("%d%d",&xx,&yy); b.push_back(point(xx,yy));}
    if (a.size()>b.size()) swap(a,b);
    printf("%s\n",check()?"YES":"NO");
  }
  return 0;
}
