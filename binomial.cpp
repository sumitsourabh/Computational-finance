#include <iostream>
#include <math.h>

using namespace std;

class binomial{
     double strike,s0,r,var,n;
     double p,u;
     public:
     binomial(double strikec,double s0c, double rc,double varc,double nc){
     	strike=strikec;
     	s0=s0c;
     	r=rc;
     	var=varc;
     	n=nc;
     }
     double sf[50][50];
     void riskneutralprob();
     void stocktree(); 
     };

void  binomial::riskneutralprob(){
	double dt=1/n;
	u = exp(var*sqrt(dt));
    double d=exp(-var*sqrt(dt));
    double a=exp(r*dt);
    p=(a-d)/(u-d);
}

void binomial::stocktree(){
	riskneutralprob();
	sf[0][0]=s0;
	int factor;
	for (int i=1;i<=n-1;i++){
		factor=i;
		for(int j=0;j<=i;j++){
			sf[i][j]=pow(u,factor)*s0;	
			factor=factor-2;
		}
	}
	for(int i=0;i<n;i++){
		for(int j=0;j<n;j++){
			cout<<sf[i][j]<<"\t";
			}
			cout<<"\n";
	}
}


int main()
{ 
	binomial b(99,100,0.06,0.2,7);
	b.stocktree();
    return 0;
}