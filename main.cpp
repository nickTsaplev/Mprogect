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
		   for(vector<float> u:p)
				for(int y:u)
					y=0;
		if(type==1)
			for(int i=0;i<n;i++)
				for(int j=0;j<m;j++)
				{
					if(i==j)
						p[i][j]=1;
					else
						p[i][j]=0;
                }

	}

	matrix(){}

	void init(int n_,int m_,int type,int maxm)
	{
		p.resize(n_);
		for (int i=0;i<n_;i++)
		{
			p[i].resize(m_);
		}
		n=n_;
		m=m_;
		if(type==2)
			for(vector<float> u:p)
				for(int y:u)
				{
					auto seed = time(0);
					srand(seed);
					y=(rand() % maxm);
				}
	}


	int n;
	int m;
	vector<vector<float> > p;
};

vector<matrix> in;
vector<float> sc;

int _tmain(int argc, _TCHAR* argv[])
{
	in.resize(256);
	sc.resize(256);
	while(true)
	{
        cout<<"$ ";
		char cb;
		string st;
		for(int i=0;i<4;i++)
		{
			cin>>cb;
			st=st+cb;
		}
        //cout<<"OK";
		if(st=="gen0")
		{
			int a;int b;char c;
			cin>>a>>b>>c;
			in[c].init(a,b,0);
		}
		if(st=="gen1")
		{
			int a;int b;char c;
			cin>>a>>b>>c;
			in[c].init(a,b,1);
		}
		if(st=="genR")
		{
			int a;int b;char c;int d;
			cin>>a>>b>>d>>c;
			in[c].init(a,b,2,d);
		}
		if(st=="summ")
		{
			char a;char b;char c;
			cin>>a>>b>>c;
			in[c].init(in[a].n,in[a].m,0);
			for(int i=0;i<in[a].n;i++)
				for(int j=0;j<in[a].m;j++)
                    in[c].p[i][j]=in[b].p[i][j]+in[a].p[i][j];
		}
		if(st=="genF")
		{
			char c; char d;int a;int b;
			cin>>c>>d;
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
		}
		if(st=="outm")
		{
			char c;
			cin>>c;
			for(int i=0;i<in[c].n;i++)
			{
				for(int j=0;j<in[c].m;j++)
					cout<<in[c].p[i][j]<<" ";
				cout<<endl;
			}

		}
		if(st=="cins")
		{
			char c;
			cin>>c;
			cin>>sc[c];
		}
		if(st=="outs")
		{
			char c;
			cin>>c;
			cout<<sc[c];
		}
		if(st=="muls")
		{
			char c;char d;char e;
			cin>>c>>d>>e;
            in[e].init(in[c].n,in[c].m,0);
			for(int i=0;i<in[c].n;i++)
				for(int j=0;j<in[c].m;j++)
                    in[e].p[i][j]=in[c].p[i][j]*sc[d];
        }
	}
	return 0;
}
