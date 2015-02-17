#include <iostream>
#include <math.h>

using namespace std;

class deltahedging{
     double K,S,r,var,T;
     double call;
     public:
     deltahedging(double K,double S, double r,double var,double T){
     	this->K=K;
     	this->S=S;
     	this->r=r;
     	this->var=var;
     	this->T=T;
     	}
     double hedge[365];
     double N(double);
     double blackscholes(double);
     double deltacal(double);
     void hedging(double);

     };

double deltahedging::N(double x)
{    int neg = (x<0);
     if(neg) x *= -1;
     double k(1/(1+0.2316419*x));
     double y=((((1.330274429*k-1.821255978)*k+1.781477937)*k-0.356563782)*k+0.319381530)*k;
     y = 1.0 - 0.398942280401*exp(-0.5*x*x)*y;
     return (1-neg)*y + neg*(1-y);
}
double deltahedging::blackscholes(double T){
     double d1=(log(S/K)+(r+((var*var)/2))*T)/(var*sqrt(T));
     double d2=(log(S/K)+(r-((var*var)/2))*T)/(var*sqrt(T));
     double nd1=N(d1);
     double nd2=N(d2);
     return call= S*nd1-K*exp(-r*T)*nd2;
    // cout<<"Call price is "<<call<<"\n";
     }     
double deltahedging::deltacal (double t){
     double d1=(log(S/K)+(r+((var*var)/2))*t)/(var*sqrt(t));
     return N(d1);
} 
void deltahedging::hedging(double frequency){
     double dt =frequency/365;
     double option[365];
     hedge[0]=-deltacal(1)*S+ blackscholes(1);
     option[0]=blackscholes(1);
     //cout<<"initial hedge "<<hedge[0];
     for(int k=1;k<=365;k++){
          hedge[k]=0;
     }
     int j=1;
     for(double i=1-dt;i>0;i-=dt){          
          hedge[j]=(hedge[j-1]*r*dt)-(deltacal(i)*S)+(deltacal(i+dt)*S)+call;
          option[j]=blackscholes(i);
          j++;
     }
     cout<<"Hedge values\n";
     for(int i=0;i<=j;i++){
          cout<<hedge[i]<<"\n";
     }
     cout<<"Option values\n";
     for(int i=0;i<=j;i++){
          cout<<option[i]<<"\n";
     }


}    
int main(){
  deltahedging d(99,100,0.06,0.2,1);
  //double call=d.blackscholes(1);
  //double delta=d.deltacal(1);
  //cout<<"black s call"<<call<<"delta "<<delta;
  d.hedging(7);
}
