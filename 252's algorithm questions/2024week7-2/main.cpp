#include<iostream>
#include<vector>
#include<algorithm>

using namespace std;

struct score
{
    int id;
    int total;
    int math;
    int chi;
    int eng;

    score(int id,int chi, int math, int eng):id(id),chi(chi),math(math),eng(eng){
        total=chi+math+eng;
    }
    void print(){
        cout<<id<<" "<<total<<endl;
    }
};

bool cmp(score &a,score &b){
    bool boo;
    if(a.total!=b.total){
        return a.total>b.total;
    }
    if(a.chi!=b.chi){
        return a.chi>b.chi;
    }
    
    return a.id<b.id;
}


int main(){
    int n;
    while(cin>>n){
        vector<score> student;
        for (int i = 0; i < n; i++)
        {
            int chi,math,eng;
            cin>>chi>>math>>eng;
            student.push_back(score(i+1,chi,math,eng));
        }
        sort(student.begin(),student.end(),cmp);
        for(int i=0;i<5;i++){
            student[i].print();
        }
        
    }

    return 0;
}