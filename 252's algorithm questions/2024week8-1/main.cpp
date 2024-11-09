#include <iostream>
#include <vector>
#include <string>
#include <iomanip>

using namespace std;

int numName(string name){
    int sum=0;
    for(int i=0;i<name.length();i++){
        sum+=name[i]-'a'+1;
    }
    return sum;
}

int main(){
    int m,n;
    cin>>n>>m;
    int roomnum;
    vector<string> names;
    vector<string> rooms(m,"NULL");
    vector<int> namenums;
    for(int i=0;i<n;i++){
        string sin;
        cin>>sin;
        names.push_back(sin);
        namenums.push_back(numName(sin));
    }
    int sum=0;
    for(int i=0;i<n;i++){
        int roomnum=namenums[i]%m;
        int step=0;
        while(rooms[roomnum]!="NULL"){
            step++;
            roomnum=(namenums[i] + step * step) % m;
        }
        rooms[roomnum]=names[i];
        step++;
        sum+=step;
    }
    for (int i = 0; i < m; i++) {
        cout << i << ":" << rooms[i] << endl;
    }
    printf("%.3lf",sum/double(n));
    return 0;
}