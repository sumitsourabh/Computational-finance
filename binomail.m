S0=100;
K=99;
r=0.06;
s=0.2;
T=1;
dt=1/50;
n=50;
u=exp(s*sqrt(dt));
d=exp(-s*sqrt(dt));
a=exp(r*dt);

p=(a-d)/(u-d);
SF=zeros(n,n);
SF(1,1)=S0;

for i=2:n
    factor=i-1;
    for j=1:i
        SF(i,j)=power(u,factor)*S0;
        factor=factor-2;
    end
end
SF
f=zeros(n,n);
for j=1:n
    if(SF(n,j)>K)
       f(n,j)=SF(n,j)-K;
    else
        f(n,j)=0;
    end
end
val=(exp(-r*dt))*((p*f(5,1))+(1-p)*(f(5,2)))
for i=n-1:-1:1
    for j=1:i
        f(i,j)=(exp(-r*dt))*((p*f(i+1,j))+(1-p)*(f(i+1,j+1)));  
    end
    
end
f(1,1)

