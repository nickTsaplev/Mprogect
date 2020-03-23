#pragma hdrstop
#pragma argsused

#ifdef _WIN32
#include <tchar.h>
#else
  typedef char _TCHAR;
  #define _tmain main
#endif

#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using namespace std;

#include "man.h"

#define float double

struct matrix
{

	void init(int n_,int m_,int type)
	{
		p.resize(n_);
		for (int i=0;i<n_;i++)
		{
			p[i].resize(m_);
		}
		n=n_;
		m=m_;
		if(type==0)
		   for(int i=0;i<n;i++)
				for(int j=0;j<m;j++)
					p[i][j]=0; 
		if(type==1)
			for(int i=0;i<n;i++)
				for(int j=0;j<m;j++)
				{
					if(i==j)
						p[i][j]=1;
					else
						p[i][j]=0;
                }
    free=false;
	}

	matrix(){}

	void init(int n_,int m_,int type,int maxm)
	{
        auto seed = time(0);
					srand(seed);
		p.resize(n_);
		for (int i=0;i<n_;i++)
		{
			p[i].resize(m_);
		}
		n=n_;
		m=m_;
		if(type==2)
			for(int i=0;i<n;i++)
				for(int j=0;j<m;j++)
				{

					p[i][j]=(rand() % maxm)+1;
				}
    free=false;
	}
  
  void operator=(const matrix& b)
  {
    init(b.n,b.m,0);
    for(int i=0;i<b.n;i++)
      for(int j=0;j<b.m;j++)
        p[i][j]=b.p[i][j];
  }


	int n=0;
	int m=0;
	vector<vector<float> > p; 
  bool free=true;
};

vector<matrix> in;
vector<float> sc;
vector<string> comm;
ifstream Fin;
enum {term,file} inState=term;
int level=0;



void outm(const matrix& a)
{
  for(int i=0;i<a.n;i++)
  {
    for(int j=0;j<a.m;j++)
      cout<<a.p[i][j]<<" ";
    cout<<endl;
  }
}

matrix tran(const matrix& a)
{
  matrix res;
  res.init(a.m,a.n,0);
  for(int i=0;i<a.n;i++)
    for(int j=0;j<a.m;j++)
      res.p[j][i]=a.p[i][j];
  return res;
}

pair<matrix,int> operator*(const matrix& a,const matrix& b)
{
  matrix res;int cost=0;
  res.init(a.n,b.m,0);
  for(int i=0;i<res.n;i++)
    for(int j=0;j<res.m;j++)
    {
      float r=0;
      for(int l=0;l<a.m;l++)
      {
        r+=a.p[i][l]*b.p[l][j];
        cost++;
      }
      res.p[i][j]=r;
    }
  return {res,cost};
}


matrix operator*(const matrix& a,float b)
{
  matrix res;
  res.init(a.n,a.m,0);
  for(int i=0;i<a.n;i++)
    for(int j=0;j<a.m;j++)
      res.p[i][j]=a.p[i][j]*b;
  return res;
}

matrix operator/(const matrix& a,float b)
{
  matrix res;
  res.init(a.n,a.m,0);
  for(int i=0;i<a.n;i++)
    for(int j=0;j<a.m;j++)
      res.p[i][j]=a.p[i][j]/b;
  return res;
}

matrix operator+(const matrix& a,const matrix& b)
{
  matrix res;
  res.init(a.n,a.m,0);
  for(int i=0;i<a.n;i++)
    for(int j=0;j<a.m;j++)
      res.p[i][j]=b.p[i][j]+a.p[i][j];
  return res;
}
pair<matrix,int> genobr(const matrix& p1)
{
  matrix l;int cost=0;
  matrix a=p1;
  l.init(a.n,a.n,1);
  for(int i=0;i<a.n-1;i++)
  {
    for(int j=i+1;j<a.n;j++)
    {
      float k=((a.p[j][i])/(a.p[i][i]));
      cost++;
      l.p[j][i]=k;
    }
    for(int j=i;j<a.n;j++)
      for(int k=i+1;k<a.n;k++)
      {
        a.p[j][k]+=a.p[i][i]*-l.p[j][i];
      }
  }
  return {l,cost};
}


pair<pair<matrix,matrix>,int> gentotrm(const matrix& a)
{
  matrix e;int cost=0;matrix l;
  //ins=genobr(a).first;
  matrix l0;
  l0.init(a.n,a.n,1);
  matrix b=a;
  l.init(a.n,a.n,1);
  for(int i=0;i<a.n-1;i++)
    for(int j=i+1;j<a.n;j++)
    {
      e.init(a.n,a.n,1);
      float k=-((b.p[j][i])/(b.p[i][i]));
      l0.p[j][i]=-k;
      e.p[j][i]=k;
      l=(e*l).first;
      b=(e*b).first;
      cost+=(e*l).second;
      
    }
  return {{l,l0},cost};
}
pair<matrix,int> totrm(const matrix& a)
{
  matrix l;
  int cost=0;
  l=gentotrm(a).first.first;
  cost+=gentotrm(a).second;
  l=(l*a).first;
  cost+=(l*a).second;
  return {l,cost};
}


pair<pair<matrix,matrix>,int> ugentotrm(const matrix& a)
{
  matrix e;int cost=0;matrix l;
  //ins=genobr(a).first;
  matrix l0;
  l0.init(a.n,a.n,1);
  matrix b=a;
  l.init(a.n,a.n,1);
  for(int i=a.n-1;i>0;i--)
    for(int j=i-1;j>-1;j--)
    {
      e.init(a.n,a.n,1);
      float k=-((b.p[j][i])/(b.p[i][i]));
      l0.p[j][i]=-k;
      e.p[j][i]=k;
      l=(e*l).first;
      b=(e*b).first;
      cost+=(e*l).second;
      
    }
  return {{l,l0},cost};
}

pair<matrix,int> utotrm(const matrix& a)
{
  matrix l;
  int cost=0;
  l=ugentotrm(a).first.first;
  cost+=gentotrm(a).second;
  l=(l*a).first;
  cost+=(l*a).second;
  return {l,cost};
}


pair<float,float> opr(const matrix& a)
{
  if(a.n==2)
    return {a.p[0][0]*a.p[1][1]-a.p[1][0]*a.p[0][1],2};
  else
  {
    float sum=0;float c=0;
    matrix m;
    for(int k=0;k<a.n;k++)
    {
      
      m.init(a.n-1,a.m-1,0);
      for(int i=0;i<a.n-1;i++)
      {
        for(int j=0;j<k;j++)
          m.p[i][j]=a.p[i+1][j];
        for(int j=k+1;j<a.n;j++)
          m.p[i][j-1]=a.p[i+1][j];
        
      }
      int buf=a.p[0][k]*opr(m).first;
      c+=opr(m).second+1;
      if(k % 2==0)
        sum+=buf;
      else
        sum-=buf;
    }
    return {sum,c};
  }
}

pair<matrix,int> genobrf(const matrix& a)
{
  matrix c;
  matrix m;
  int cost=0;
  c.init(a.n,a.n,1);
  m.init(a.n-1,a.n-1,1);
  cout<<'b';
  for(int k1=0;k1<a.n;k1++)
    for(int k2=0;k2<a.n;k2++)
    {
      
      for(int i=0;i<k1;i++)
      {
        for(int j=0;j<k2;j++)
          m.p[i][j]=a.p[i][j];
        for(int j=k2+1;j<a.n;j++)
          m.p[i][j-1]=a.p[i][j];
      }
      for(int i=k1+1;i<a.n;i++)
      {
        for(int j=0;j<k2;j++)
          m.p[i-1][j]=a.p[i][j];
        for(int j=k2+1;j<a.n;j++)
          m.p[i-1][j-1]=a.p[i][j];
      }
      if((k1+k2) % 2==0)
        c.p[k1][k2]=opr(m).first;
      else
        c.p[k1][k2]=-1*opr(m).first;
      cost+=opr(m).second;
    }
  c=tran(c);
  c=c/(opr(a).first);
  return {c,cost};
}

pair<matrix,int> GJm(matrix a)
{
  matrix obr;
  int cost=0;
  obr=gentotrm(a).first.first;
  a=totrm(a).first;
  cost+=totrm(a).second;
  obr=(ugentotrm(a).first.first*obr).first;
  cost+=(ugentotrm(a).first.first*obr).second;
  cost+=ugentotrm(a).second;
  //cost+=utotrm(a).second;
  //a=utotrm(a).first;
  matrix k;
  k.init(a.n,a.n,1);
  for(int i=0;i<a.n;i++)
    k.p[i][i]=1/a.p[i][i];
  cost+=a.n;
  //a=(k*a).first;
  obr=(k*obr).first;
  cost+=(k*obr).second;
  return {obr,cost};
}

pair<pair<matrix,int>,pair<matrix,matrix> > GJgm(matrix a)
{
  matrix obr;matrix l;matrix u;
  int cost=0;
  obr=gentotrm(a).first.first;
  a=totrm(a).first;
  cost+=totrm(a).second;
  u=a;l=obr;
  obr=(ugentotrm(a).first.first*obr).first;
  cost+=(ugentotrm(a).first.first*obr).second;
  cost+=ugentotrm(a).second;
  //cost+=utotrm(a).second;
  //a=utotrm(a).first;
  matrix k;
  k.init(a.n,a.n,1);
  for(int i=0;i<a.n;i++)
    k.p[i][i]=1/a.p[i][i];
  cost+=a.n;
  //a=(k*a).first;
  obr=(k*obr).first;
  cost+=(k*obr).second;
  return {{obr,cost},{l,u}};
}

pair<matrix,int> obrp(matrix& a,matrix& b)
{
  matrix ans;
  int cost=0;
  ans.init(a.n,1,0);
  ans.p[a.n-1][0]=b.p[a.n-1][0]/a.p[a.n-1][a.n-1];
  for(int i=a.n-1;i>-1;i--)
  {
    float s=0;
    for(int j=i+1;j<a.n;j++)
    {
      s+=a.p[i][j]*ans.p[j][0];
      cost++;
    }
    s=b.p[i][0]-s;
    ans.p[i][0]=s/a.p[i][i];
    cost++;
  }
  return {ans,cost};
}

pair<matrix,int> prpo(matrix& a,matrix& b)
{
  matrix ans;
  int cost=0;
  ans.init(a.n,1,0);
  ans.p[0][0]=b.p[0][0]/a.p[0][0];
  for(int i=1;i<a.n;i++)
  {
    float s=0;
    for(int j=i-1;j>-1;j--)
    {
      s+=a.p[i][j]*ans.p[j][0];
      cost++;
    }  
    s=b.p[i][0]-s;
    ans.p[i][0]=s/a.p[i][i];
    cost++;
  }
  return {ans,cost};
}


pair<matrix,int> lbmulm(matrix& l,matrix& b)
{
  matrix ans;
  int cost=0;
  ans.init(l.n,1,0);
  
  for(int i=0;i<l.n;i++)
  {
    float s=0;
    for(int j=0;j<i+1;j++)
    {
      s+=b.p[j][0]*l.p[i][j];
      cost++;
    }
    ans.p[i][0]=s;
  }
  return {ans,cost};
}

template<typename t>
void read(t& a)
{
  if(inState==term)
    cin>>a;
  else
    Fin>>a;
}

template<typename t,typename t1>
void read(t& a,t1& b)
{
  read(a);read(b);
}

template<typename t,typename t1,typename t2>
void read(t& a,t1& b,t2& c)
{
  read(a);read(b);read(c);
}
template<typename t,typename t1,typename t2,typename t3>
void read(t& a,t1& b,t2& c,t3& d)
{
  read(a);read(b);read(c);read(d);
}



int _tmain(int argc, _TCHAR* argv[])
{
	in.resize(256);
	sc.resize(256);
    initM();
	while(true)
	{
    if(inState==term)
      cout<<"$ ";
		char cb;
		string st;
		for(int i=0;i<4;i++)
		{
			read(cb);
			st=st+cb;
		}
        //cout<<"OK";
		if(st=="gen0")
		{
			int a;int b;char c;
			read(a,b,c);
			in[c].init(a,b,0);
		}else
		if(st=="gen1")
		{
			int a;int b;char c;
			read(a,b,c);
      in[c].init(a,b,1);
		}else
		if(st=="genR")
		{
			int a;int b;char c;int d;
      read(a,b,d,c);
			in[c].init(a,b,2,d);
		}else
		if(st=="summ")
		{
			char a;char b;char c;
			read(a,b,c);
      in[c]=in[a]+in[b];
		}else
		if(st=="genF")
		{
			char c; char d;int a;int b;
			read(c,d);
			ifstream Fcin;string bc="D:\\";
			bc+=c;
			bc+=".txt";
			Fcin.open(bc);
			Fcin>>a>>b;
			in[d].init(a,b,0);
			for(int i=0;i<in[d].n;i++)
				for(int j=0;j<in[d].m;j++)
					Fcin>>in[d].p[i][j];
            Fcin.close();
		}else if(st=="genH")
		{
			char d;int a;int b;
			
			read(a,b,d);
			in[d].init(a,b,0);
			for(int i=0;i<in[d].n;i++)
				for(int j=0;j<in[d].m;j++)
					read(in[d].p[i][j]);
		}else 
		if(st=="wrtF")
		{
			char c; char d;
			read(c,d);
			ofstream Fcout;
      #ifdef WIN
        string bc="D:\\";
      #else
        string bc="./";
      #endif
			bc+=c;
			bc+=".txt";
			Fcout.open(bc);
			Fcout<<in[d].n<<" "<<in[d].m<<endl;
			for(int i=0;i<in[d].n;i++)
			{
				for(int j=0;j<in[d].m;j++)
					Fcout<<in[d].p[i][j]<<" ";
				Fcout<<endl;
			}
			Fcout.close();
		}else if(st=="exec")
    {
      char d;
      #ifdef WIN
        string bc="D:\\";
      #else
        string bc="./";
      #endif
      read(d);
      bc+=d;
      bc+=".sh";
      Fin.open(bc);
      inState=file;
      level++;
    }else if(st=="exit")
    {
      level--;
      if(inState!=term && level==0)
        inState=term;
      else if(level==-1)
        break;
    }else
		if(st=="outm")
		{
			char c;
			read(c);
      outm(in[c]);
			

		}else
		if(st=="cins")
		{
			char c;
			read(c);
      read(sc[c]);
		}else
		if(st=="outs")
		{
			char c;
			read(c);
			cout<<sc[c];
		}else
		if(st=="muls")
		{
			char c;char d;char e;
			read(c,d,e);
      in[e]=in[c]*sc[d];
		}else
		if(st=="tran")
		{
			char c;char d;
			read(c,d);
      in[d]=tran(in[c]);
			
		}else
		if(st=="mulm")
		{
      char c;char d;char e;int cost=0;
			read(c,d,e);
      in[e]=(in[c]*in[d]).first;
      cout<<"cost: "<<(in[c]*in[d]).second<<endl;
			
		}else
		if(st=="mulc")
		{
			char c;float d;char e;
			read(c,d,e);
      in[e]=in[c]*d;
		}else
		if(st=="mana")
			man();
    else
		if(st=="mans")
		{
			string a;
			read(a);
			man(a);
    }else
    if(st=="manp")
		{
			string a;
			read(a);
			manpa(a);
		}
    else 
    if(st=="sett")
    {
      int a;int b;char c;int d;
      read(a,b,c,d);
      in[c].p[a][b]=d;
    }else if(st=="gmv1")
    {
      
			int a;char b;char c;
			read(a,b,c);
      if(b=='g')
        in[c].init(a,1,1);
      if(b=='v')
        in[c].init(1,a,1);
    }else if(st=="dele")
    {
      char c;
      read(c);
      in[c].free=true;
    }else if(st=="free")
    {
      for(int i=0;i<257;i++)
        if(in[i].free)
          cout<<char(i)<<" ";
      cout<<endl;
    }else if(st=="prtm")
    {
      for(int i=0;i<257;i++)
        if(!in[i].free)
          cout<<char(i)<<" ";
      cout<<endl;
    }else if(st=="name")
    {
      string a;char b;
      read(a,b);
      comm[b]=a;
    }
    else if(st=="outn")
    {
      char b;
      read(b);
      cout<<comm[b];
    }else if(st=="comm")
    {
      char b;
      read(b);
      cout<<comm[b];
    }else if(st=="rstd")
    {
      for(int i=0;i<257;i++)
      {
        in[i].init(0,0,0);
        in[i].free=false;
      }
    } else if(st=="mtsc")
    {
      char c;char d;
      read(c,d);
      sc[d]=in[c].p[0][0];
    }else if(st=="ifco")
    {
      char c;char d='y';int lev=0;
      read(c);
      if(sc[c]==0)
        while(lev>0)
        {
          read(d);
          if(d=='{')
            lev++;
          if(d=='}')
            lev--;
          
        }
    }else if(st=="opre")
    {
      char c;
      read(c);
      cout<<opr(in[c]).first<<" cost: "<<opr(in[c]).second<<endl;
    }else if(st=="totr")
    {
      char a;char b;char c;char d;
      read(a,b,c,d);
      in[b]=totrm(in[a]).first;
      in[c]=gentotrm(in[a]).first.first;
      in[d]=gentotrm(in[a]).first.second;
      cout<<"cost:"<<totrm(in[a]).second<<endl;
    }else if(st=="gp-1")
    {
      char a;char b;
      read(a,b);
      
      in[b]=genobrf(in[a]).first;
      cout<<"cost:"<<genobrf(in[a]).second<<endl;
    }else if(st=="gjme")
    {
      char a;char b;
      read(a,b);
      in[b]=GJm(in[a]).first;
      cout<<"cost:"<<GJm(in[a]).second<<endl;
    }else if(st=="gjms")
    {
      char a,b,c,d;
      read(a,b);
      in[b]=GJgm(in[a]).first.first;
      in[c]=GJgm(in[a]).second.first;
      in[d]=GJgm(in[a]).second.second;
      cout<<"cost:"<<GJgm(in[a]).first.second<<endl;
    }else if(st=="obrp")
    {
      char a;char b;char c;
      read(a,b,c);
      in[c]=obrp(in[a],in[b]).first;
      cout<<"cost:"<<obrp(in[a],in[b]).second<<endl;
      
    }else if(st=="prpo")
    {
      char a;char b;char c;
      read(a,b,c);
      in[c]=prpo(in[a],in[b]).first;
      cout<<"cost:"<<prpo(in[a],in[b]).second<<endl;
    }else if(st=="lbml")
    {
      char a,b,c;
      read(a,b,c);
      in[c]=lbmulm(in[a],in[b]).first;
      cout<<"cost:"<<lbmulm(in[a],in[b]).second<<endl;
      
    }
    else
    {
      char dev;
      read(dev);
      int x;int y;
      read(x,y);
      read(dev);
      cout<<in[st[0]].p[x][y]<<endl;
    }

	}
	return 0;
}
