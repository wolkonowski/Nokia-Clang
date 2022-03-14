#include <iostream>
#include <fstream>
#include <cmath>
#include "structures.cpp"
using namespace std;

int main(int argc, char* argv[])
{
    if(argc<2)
    {
        cout<<"Specify a path to a file."<<endl;
        exit(1);
    }
    MyMap mp;
    MyBigMap mp2;
    int counter = 0;
    ifstream in(argv[1], ios::binary);
    char p = 0;
    char c;
    while(in.is_open()&&!in.eof())
    {
        in.read(&c,1);
        if(!in) break;
        mp[c]++;
        mp2[p][c]++;
        p=c;
        counter++;
    }
    in.close();
    double H = 0;
    for(auto it = mp.begin(); it != mp.end(); it++)
    {
        double t = it->second;
        H += t*log(t/counter)*(-1);
    }
    H /= counter;
    H /= log(2);
    //mp[c]--; //abcdc P(d|c)=1 czy 1/2???
    //mp[c0]--; //aaaaa P(a|0)=1 ale czy P(0)=0?
    /*
    dla "aaaaaaaa"
    P(a|0)=1/8
    P(a|a)=1
    P(a)=1
    P(0)=0
    ?????
    czy usunac ostatnie 'a'?
    czy dopisac jedno 0?
    wówczas na potrzeby entropii warunkowej
    P(a)=7/8
    P(0)=1/8
    */
    //mp[0]++;
    //mp[c]--;
    double H2 = 0;
    for(auto it = mp2.begin();it != mp2.end(); it++)
    {
        double Hx = 0;
        for (auto it2 = (it->second).begin(); it2 != (it->second).end(); it2++)
        {
            double t = (double) (it2->second) / mp[it->first];
            Hx += (it2->second)*log(t)*(-1);
        }
        if(isinf(Hx)) continue;
        H2 += Hx;
    }
    H2 /= counter;
    H2 /= log(2);
    cout<<"H: "<<H<<endl<<"H2: "<<H2<<endl<<"bytes: "<<counter<<endl;
    return 0;
}
