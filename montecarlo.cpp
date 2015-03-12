#include <iostream>
#include <math.h>
#include <random>
using namespace std;

class montecarlo{
    double K,S,r,var,T;
    public:
     montecarlo(double K,double S, double r,double var,double T){
        this->K=K;
        this->S=S;
        this->r=r;
        this->var=var;
        this->T=T;
        }
     double eulermethod(int);
     double N(double);
     double blackscholes(double);
     double random_normal();
     double optionvaleuler(int,int);
     double normalgen();

};
double montecarlo::N(double x)
{    int neg = (x<0);
     if(neg) x *= -1;
     double k(1/(1+0.2316419*x));
     double y=((((1.330274429*k-1.821255978)*k+1.781477937)*k-0.356563782)*k+0.319381530)*k;
     y = 1.0 - 0.398942280401*exp(-0.5*x*x)*y;
     return (1-neg)*y + neg*(1-y);
}
double montecarlo::blackscholes(double T){
    double call;
     double d1=(log(S/K)+(r+((var*var)/2))*T)/(var*sqrt(T));
     double d2=(log(S/K)+(r-((var*var)/2))*T)/(var*sqrt(T));
     double nd1=N(d1);
     double nd2=N(d2);
     return call= S*nd1-K*exp(-r*T)*nd2;
    // cout<<"Call price is "<<call<<"\n";
}  

double montecarlo::normalgen(){
    std::random_device rd;
    std::mt19937 e2(rd());
    std::normal_distribution<> dist(0, 1);
    return dist(e2);
    }
double montecarlo::eulermethod(int n){
    double dt = T/n;
    double SF=S;
    for(int i=1;i<=n;i++){
        SF = SF + SF*((r*dt) + var*normalgen()*(sqrt(dt))); 
    }
    return SF;
}
double montecarlo::optionvaleuler(int n,int m){
    //int m=100;
    double sf[m];
    double payoff=0;
    for(int i=0;i<m;i++){
        sf[i]=eulermethod(n);
    //  cout<<sf[i]<<"\n";
        if(sf[i]>K){
            payoff+=sf[i]-K;
        }
        else{
            payoff+=0;
        }
        
    }
    //cout<<payoff<<"\t";
double optionval= exp(-r*T) * payoff/m;
return optionval;
}
int main(){
montecarlo b(99,100,0.06,0.2,1);
int t[20];
int j=0;
double val[20];
for(int i=0;i<20;i++){
    t[i]=100+500*j;
    val[i]=b.optionvaleuler(180,t[i]);
    j++;
}
cout<<" Number of steps are "<<"\n";
    for (int i=0;i<j;i++){
        cout<<t[i]<<"\n";
    }
    cout<<" call "<<"\n";
    for (int i=0;i<=j;i++){
        cout<<val[i]<<"\n";
    }

    return 0;
}




