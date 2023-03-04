#include<fstream>
#include<vector>
#include<map>
#include<iostream>
#define max(a,b) a>b?a:b;
using namespace std;
vector<int>g[100010];
vector<int>siz(100010);
int ans1=1,ans2=1;
int akk_n=0;
void dfs(int u,int fa){
    siz[u]=1;
    int cnt1=0;
    for(auto i:g[u]){
        if(i==fa)continue;
        dfs(i,u);
        siz[u]+=siz[i];
        if(siz[i]==1)cnt1++;
    }
    int len=g[u].size()-1;
    if(cnt1){
        ans1+=max(0,len-cnt1-1);
        ans2+=max(0,len-cnt1);
    }else{
        ans1+=max(0,len-1);
        ans2+=max(0,len-1);
    }

}
map<int,double>mp1,mp2;

void get_siz(int n,int id){
    string s="./data/"+to_string(n)+"/"+to_string(id)+".txt";
    ifstream ifs(s,ios::in);
    ans1=1,ans2=1;
    for(int i=1;i<=n;i++){
        if(!g[i].empty())g[i].clear();
        siz[i]=0;
    }
    int u,v;
    while(ifs>>u>>v){
        g[u].push_back(v);
        g[v].push_back(u);
    }
    ifs.close();
    dfs(1,0);
    mp1[n]+=ans1;
    mp2[n]+=ans2;
}

int main(){

    vector<int>ranges({100,500,1000,5000,10000,50000,100000});

    for(auto i:ranges){
        for(int j=1;j<=100;j++){
            akk_n=i;
            get_siz(i,j);
            get_siz(i,j);
        }
    }
    for(auto i:mp1){
        mp1[i.first]=mp1[i.first]/100;
    }
    for(auto i:mp1){
        mp2[i.first]=mp2[i.first]/100;
    }
    ofstream ofs("res.txt",ios::out);
    ofs<<"algorithm1:"<<"\n";
    for(auto i:mp1){
        ofs<<i.first<<" "<<i.second<<"\n";
    }
    ofs<<"algorithm2:"<<"\n";
    for(auto i:mp2){
        ofs<<i.first<<" "<<i.second<<"\n";
    }


}
