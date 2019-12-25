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

					p[i][j]=(rand() % maxm);
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
    initM();
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
		if(st=="wrtF")
		{
			char c; char d;
			cin>>c>>d;
			ofstream Fcout;string bc="D:\\";
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
		if(st=="tran")
		{
			char c;char d;
			cin>>c>>d;
			in[d].init(in[c].m,in[c].n,0);
			for(int i=0;i<in[c].n;i++)
				for(int j=0;j<in[c].m;j++)
					in[d].p[j][i]=in[c].p[i][j];
		}
		if(st=="mulm")
		{
        	char c;char d;char e;
			cin>>c>>d>>e;
			in[e].init(in[c].n,in[d].m,0);
			for(int i=0;i<in[e].n;i++)
				for(int j=0;j<in[e].m;j++)
				{
					float r=1;
					for(int l=0;l<in[c].n;l++)
						r*=in[c].p[l][j];
					for(int l=0;l<in[d].m;l++)
						r*=in[d].p[i][l];

					in[e].p[i][j]=r;
				}
		}
		if(st=="mulc")
		{
			char c;float d;char e;
			cin>>c>>d>>e;
            in[e].init(in[c].n,in[c].m,0);
			for(int i=0;i<in[c].n;i++)
				for(int j=0;j<in[c].m;j++)
					in[e].p[i][j]=in[c].p[i][j]*d;
		}
		if(st=="mana")
			man();
		if(st=="mans")
		{
			string a;
			cin>>a;
			man(a);
		}

	}
	return 0;
}
