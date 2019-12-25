
struct page
{
	string name;
	string comment;
};
vector<page> manp;
void initM()
{
	manp.resize(11);
	manp[0].name="gen0";manp[0].comment="gen matrix zero";
	manp[1].name="gen1";manp[1].comment="gen matrix one";
	manp[2].name="genR";manp[2].comment="gen matrix reandom";
	manp[3].name="summ";manp[3].comment="gen summ two matrix";
	manp[4].name="genF";manp[4].comment="read matrix from file";
	manp[5].name="outm";manp[5].comment="write matrix";
	manp[6].name="cins";manp[6].comment="read scalar";
	manp[7].name="outs";manp[7].comment="write scalar";
	manp[8].name="muls";manp[8].comment="multiply matrix & scalar";
	manp[9].name="mulc";manp[9].comment="multiply matrix & scalar number";
    manp[9].name="wrtF";manp[9].comment="write matrix to file";
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
void man()
{
	for(int i=0;i<manp.size();i++)
		cout<<manp[i].name<<" - "<<manp[i].comment<<endl;


}