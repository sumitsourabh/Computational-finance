#include <iostream>
#include <math.h>

using namespace std;

class binomial{
     double strike,s0,r,var,n;
     double p,u;
     public:
     binomial(double strike,double s0, double r,double var,double n){
     	this->strike=strike;
     	this->s0=s0;
     	this->r=r;
     	this->var=var;
     	this->n=n;
     	}
     double sf [50][50];
     double co [50][50];
     double po [50][50];
     double aco[50][50];
     double apo[50][50];
     void riskneutralprob();
     void stocktree(); 
     void expirypayoff();
     double calloption();
     double putoption();
     double americancall();
     double americanput();
     double deltacal();
     };

void  binomial::riskneutralprob(){
	double dt=1/n;
	u = exp(var*sqrt(dt));
    double d=exp(-var*sqrt(dt));
    double a=exp(r*dt);
    p=(a-d)/(u-d);
}

void binomial::stocktree(){
	sf[0][0]=s0;
	int factor;
	for (int i=1;i<=n-1;i++){
		factor=i;
		for(int j=0;j<=i;j++){
			sf[i][j]=pow(u,factor)*s0;	
			factor=factor-2;
		}
	}
	
}
void binomial::expirypayoff(){
	int range=n;
	for(int j=0;j<n;j++){
		if( sf[range-1][j] >= strike){
			co[range-1][j] = (sf[range-1][j] - strike);
			po[range-1][j]= 0;

		}
		else{
			co[range-1][j]= 0;
			po[range-1][j] = (strike-sf[range-1][j]);
		}
		
	}
	
}

double binomial::calloption(){
	double dt=1/n;
	for(int i=n-2;i>=0;i--){
		for(int j=0;j<=i;j++){
			co[i][j]=(exp(-r * dt)) * ((p * co[i+1][j])+(1-p) * (co[i+1][j+1]));  
		}
	}
//cout<<"\n"<<"Call option price is: "<< co[0][0];
	return co[0][0];
}
double binomial::putoption(){
	double dt=1/n;
	for(int i=n-2;i>=0;i--){
		for(int j=0;j<=i;j++){
			po[i][j]=(exp(-r * dt)) * ((p * po[i+1][j])+(1-p) * (po[i+1][j+1]));  
		}
	}
	//cout<<"\n"<<"Put option price is: "<< po[0][0]<<"\n";
	return po[0][0];
}

double binomial::deltacal(){
	double delta;
	delta=(co[1][0]-co[1][1])/(s0*(u-(1/u)));
	//cout<<"delta is "<<delta<"\n";
	return delta;
}


double binomial::americancall(){
	double dt=1/n;
	int range=n;
	for(int j=0;j<n;j++){
		if( sf[range-1][j] >= strike){
			aco[range-1][j] = sf[range-1][j]-strike;}
		else{
			aco[range-1][j]= 0;
		}
	}
	
	for(int i=n-2;i>=0;i--){
		for(int j=0;j<=i;j++){
			aco[i][j]=(exp(-r * dt)) * ((p * aco[i+1][j])+(1-p) * (aco[i+1][j+1]));  
			double exercise=(sf[i][j]-strike);
			if(aco[i][j]<=exercise){
				aco[i][j]= exercise;
			}
		}
	}
	//cout<<"\n"<<"American call option price is: "<< aco[0][0];
	return aco[0][0];
}

double binomial::americanput(){
	double dt=1/n;
	int range=n;
	for(int j=0;j<n;j++){
		if( sf[range-1][j] <= strike){
			apo[range-1][j] = strike-sf[range-1][j];}
		else{
			apo[range-1][j]= 0;
		}
	}
	
	for(int i=n-2;i>=0;i--){
		for(int j=0;j<=i;j++){
			apo[i][j]=(exp(-r * dt)) * ((p * apo[i+1][j])+(1-p) * (apo[i+1][j+1]));  
			double exercise=(strike-sf[i][j]);
			if(apo[i][j]<=exercise){
				apo[i][j]= exercise;
			}
			
		}
	}
	//cout<<"\n"<<"American put option price is: "<< apo[0][0]<<"\n";//
	return apo[0][0];
}



int main()
{   double call[200];
	int j=0;
	double steps[200];
	for(double n=1;n<150;n+=3){
	steps[j]=n;
	binomial b(99,100,0.06,0.2,n);
	b.riskneutralprob();
	b.stocktree();
	b.expirypayoff();
	call[j]=b.calloption();
	//delta[j] =b.deltacal();
	j++;
	}
	cout<<" Number of steps are "<<"\n";
	for (int i=0;i<=j;i++){
		cout<<steps[i]<<"\n";
	}
	cout<<" call "<<"\n";
	for (int i=0;i<=j;i++){
		cout<<call[i]<<"\n";
	}

	//binomial b(99,100,0.06,0.2,50);
	//b.riskneutralprob();
	//b.stocktree();
	//b.expirypayoff();
	//double call1=b.americancall();
	//double put1 =b.americanput();
	//cout<<call1<<"\t"<<put1<<"\t";
//	b.americancall();
//	b.americanput();
//	b.deltacal();
    return 0;
}



/*for(int i=0;i<n;i++){
	//for(int k=0;k<=(n/2)-i;k++){
	//	cout<<"\t\t";
	//}
	for(int j=0;j<n;j++){
		if(sf[i][j]>=1){
			cout<<sf[i][j]<<"\t\t";
	    }
	}
		cout<<"\n";
}*/