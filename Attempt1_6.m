clc
E=input('Elastic modulus=')
s=input('No. of supports=')
disp('enter 1 for fixed support, 2 for pin joint');
for i=1:s
    S(1,i)=input('type of support');
    S(2,i)=input('Postion of support');
end
S
p=input('number of loads=')
disp('enter 1 for point load, 2 for UDL, 3 for moment');
for i=1:p
    P(i,1)=input('Type of load');
    P(i,2)=input('Magnitude');
    P(i,3)=input('Position or from');
    if P(i,1)==2
        P(i,4)=input('to');
    end
end
e=input('No. of elements=')
for i=1:e
    L(1,1:2)=0;
    L(i+1,1)=input('Length of elements');
    L(i+1,2)=L(i,2)+L(i+1,1);
    c=input('Enter 1 for circular element or 2 for rectangular element or 3 for moment of inertia');
    if c==1
        r=input('radius=')
        I=11*r^4/14
    elseif c==2
        b=input('breadth=')
        h=input('height=')
        I=b*h^3/12
    else
        I=input('I=')
    end
end
L
K=zeros(2*e+2,2*e+2);
for i=1:e
    l=L(i+1,1);
    k=zeros(2*e+2,2*e+2);
    k(2*i-1:2*i+2,2*i-1:2*i+2)=[12 6*l -12 6*l;6*l 4*l^2 -6*l 2*l^2;-12 -6*l 12 -6*l;6*l 2*l^2 -6*l 4*l^2]*E*I/L(i+1,1)^3;
    K=K+k
end
f1=zeros(2*e+2,1);
for i=1:p
    for j=1:e+1
        if P(i,3)==L(j,2) && P(i,1)==1
            f1(2*j-1,1)=P(i,2);
        end
    end
end
f2=zeros(2*e+2,1);
for j=1:e
    for i=1:p
        if P(i,1)==2 && P(i,3)<=L(j,2)
            if P(i,4)>=L(j+1,2)
               f2(2*j-1:2*j+2,1)=[P(i,2)*L(j+1,1)/2;P(i,2)*L(j+1,1)^2/12;P(i,2)*L(j+1,1)/2;-P(i,2)*L(j+1,1)^12/2]
            end
        end
    end
end
f3=zeros(2*e+2,1);
for i=1:p
    for j=1:e+1
        if P(i,3)==L(j,2) && P(i,1)==3
            f3(2j,1)=P(i,2);
        end
    end
end
f3
F=(f1+f2+f3)*(-1)
A=K;
t=e
w=1
for j=1:s
    for i=1:t+1
        if S(2,j)==L(i,2)
            d(1,w)=2*i-1;
            w=w+1;
        end
        if S(2,j)==L(i,2) && S(1,j)==1
            d(1,w)=2*i;
            w=w+1;
        end
    end
end
A([d],:)=[]
A(:,[d])=[]
F([d],:)=[]
U=A\F