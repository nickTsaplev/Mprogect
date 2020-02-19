#include "INIReader.h"
struct page
{
	string name;
	string comment;
};
vector<page> manp;
INIReader reader("man.ini");
INIReader preader("p.ini");
void initM()
{
	manp.resize(28);
	manp[0].name="gen0";manp[0].comment=reader.Get("gen", "gen0", "ERROR");
	manp[1].name="gen1";manp[1].comment=reader.Get("gen", "gen1", "ERROR");
	manp[2].name="genR";manp[2].comment=reader.Get("gen", "genR", "ERROR");
	manp[3].name="summ";manp[3].comment=reader.Get("action", "summ", "ERROR");
	manp[4].name="genF";manp[4].comment=reader.Get("gen", "genF", "ERROR");
	manp[5].name="outm";manp[5].comment=reader.Get("action", "outm", "ERROR");
	manp[6].name="cins";manp[6].comment=reader.Get("scalar", "cins", "ERROR");
	manp[7].name="outs";manp[7].comment=reader.Get("scalar", "outs", "ERROR");
	manp[8].name="muls";manp[8].comment=reader.Get("scalar", "muls", "ERROR");
	manp[9].name="mulc";manp[9].comment=reader.Get("scalar", "mulc", "ERROR");
  manp[10].name="wrtF";manp[10].comment=reader.Get("action", "wrtF", "ERROR");
  manp[11].name="genH";manp[11].comment=reader.Get("gen", "genH", "ERROR");
  manp[12].name="exec";manp[12].comment=reader.Get("lang", "exec", "ERROR");
  manp[13].name="tran";manp[13].comment=reader.Get("action", "tran", "ERROR");
  manp[14].name="mulm";manp[14].comment=reader.Get("action", "mulm", "ERROR");
  
  manp[15].name="mana";manp[15].comment=reader.Get("help", "mana", "ERROR");
  manp[16].name="mans";manp[16].comment=reader.Get("help", "mans", "ERROR");
  
  manp[17].name="sett";manp[17].comment=reader.Get("action", "sett", "ERROR");
  manp[18].name="gmv1";manp[18].comment=reader.Get("gen", "gmv1", "ERROR");
  
  manp[19].name="dele";manp[19].comment=reader.Get("service", "dele", "ERROR");
  manp[20].name="free";manp[20].comment=reader.Get("service", "free", "ERROR");
  manp[21].name="prtm";manp[21].comment=reader.Get("service", "prtm", "ERROR");
  manp[22].name="name";manp[22].comment=reader.Get("service", "name", "ERROR");
  manp[23].name="outn";manp[23].comment=reader.Get("service", "outn", "ERROR");
  manp[24].name="comm";manp[24].comment=reader.Get("service", "outn", "ERROR");
  
  manp[25].name="rstd";manp[25].comment=reader.Get("service", "rstd", "ERROR");
  manp[26].name="mtsc";manp[26].comment=reader.Get("scalar", "mtsc", "ERROR");
  
  manp[27].name="ifco";manp[27].comment=reader.Get("lang", "ifco", "ERROR");
  
}

void man(int n)
{
	cout<<manp[n].name<<" - "<<manp[n].comment<<endl;
}
void man(string n)
{
	for(int i=0;i<manp.size();i++)
		if(manp[i].name==n)
			cout<<manp[i].name<<" - "<<manp[i].comment<<endl;
}
string tos(int c)
{
  if(c==0)
    return "0";
  if(c==1)
    return "1";
  if(c==2)
    return "2";
  if(c==3)
    return "3";
  if(c==4)
    return "4";
}

void manpa(string n)
{
  for(int j=0;j<preader.GetInteger(n, "len", -1);j++)
    cout<<preader.Get(n, tos(j), "ERROR")<<endl;
}

void man()
{
	for(int i=0;i<manp.size();i++)
		cout<<manp[i].name<<" - "<<manp[i].comment<<endl;


}