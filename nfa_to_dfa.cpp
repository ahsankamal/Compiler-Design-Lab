#include<iostream>
#include<cstdio>
#include<sstream>
#include<vector>
#include<queue>
#include<fstream>
using namespace std;
int main()
{
vector<int> v[1024];
int vis[1024];
string s;
long i,j,k,l,m,n,bit=0;
ifstream f;
f.open("nfa_to_dfa_file.txt");
j=0;
//Reading NFA from file and encoding it
//encoding?
//just doing bitwise manipulation 
//i.e. representing state [3,4] by setting 3rd and 4th bit 
//from the right which is equvalent to 12 in decimal.
getline(f,s);
getline(f,s);
//state 1 means first bit set from right
//state 2 means second bit set from right
//state 1,2 means both bits set from right 
//which is eq to 3 in decimal.

//so, 3 is storing info about 2 different states .
	while(getline(f,s))
	{
		k=1<<j;
		istringstream str(s);
		string n;
			while(str>>n)
				{
					if(n=="q")
						{	v[k].push_back(0);
							break;
						}	
					int no=0;
					bit=0;
					for(int r=0;r<n.length();r++)
					{	
							if(n[r]==','||n[r]==' ')
							{
								bit=bit|(1<<(no-1));
								//cout<<bit<<" "<<no;
								no=0;
								continue;
							}	

						no=no*10+n[r]-'0';

					}	

					bit=bit|(1<<(no-1));
					v[k].push_back(bit);
				}	
				j++;
	}

// displaying NFA
int states[1024];
cout<<"NFA\n";
	for(int r=0;r<1024;r++)
	{
		if(!v[r].empty())
		{
			cout<<v[r][0]<<" "<<v[r][1]<<endl;
			states[r]=1;
		}
	vis[r]=0;
	}

int size=v[1].size();
//using que to avoid visiting the same state again
queue<int> q;
q.push(1);
vis[1]=1;
int tmp[1024],ft;
		while(!q.empty())
		{
		
			k=q.front();
			ft=k;
			q.pop();	
			//states[k]=1 means k is a state having only 1 bit set
			if(states[k]==1)
			{
				for(int r=0;r<v[k].size();r++)
				{
				//cout<<v[k][r]<<" "<<vis[v[k][r]]<<endl;
					if(vis[v[k][r]]==0)
					{
						q.push(v[k][r]);
						vis[v[k][r]]=1;
					}	
			
				}	
		
			}	
			else//state[k]=0 means , k is a state which has 2 or more bit set
			//so combine all the states within this state and form new states
			{

				for(int i=0;i<1024;i++)
				tmp[i]=0;

				while(k>0)
				{

					j=k&-k;
					k=k-j;

					for(int i=0;i<v[j].size();i++)
					{
					tmp[i]=tmp[i]|v[j][i];
					}

				}

				for(int i=0;i<size;i++)
				{
				v[ft].push_back(tmp[i]);
				//cout<<ft<<" "<<v[ft][i]<<endl;
					if(vis[tmp[i]]==0)
					{
						q.push(tmp[i]);
						vis[tmp[i]]=1;
					}					
				}

			}//closing else		
		}//closing while

cout<<"\nDFA\n";
for(int r=0;r<1024;r++)
{
	if(!v[r].empty())
	cout<<v[r][0]<<" "<<v[r][1]<<endl;
//cout<<v[r][0]<<" "<<v[r][1]<<" "<<r<<endl;
//vis[r]=0;
}

return 0;
}
