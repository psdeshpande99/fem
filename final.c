#include <stdio.h>
#include <math.h>
#include<string.h>

int main()
{
	int p;
	float E,b,h,I;
	
	printf("Enter E in GPa");
	scanf("%f",&E);
//	E=E*pow(10,9);
	printf("\n E=%f",E);
	printf("\nEnter cross section type r=1,t=2,c=3 if you have I press4");
	scanf("%d",&p);
	switch (p)
{
    case 1: 
    printf("\nEnter breadth and height in meter");
    scanf("%f%f",&b,&h);
    I=(b*h*h*h)/12;
    	break;
    case 2:
    printf("\nEnter base and height in meter");
    scanf("%f%f",&b,&h);
    I=(b*h*h*h)/36;	
        break;
    case 3:
    printf("\nEnter diameter in meter");
    scanf("%f",&b);
	I=b*b*b*b*3.142/64;
	break;
	default:
	printf("\nEnter I in meter^4");
    scanf("%f",&I);
}
	printf("\n I=%f",I);


int n,i,j,k;
	printf("\nEnter Number Of Elements:");
	scanf("%d",&n);
	int lengths[n+1];
	int nod[n+1];
	printf("\nYour nodes are:");
	for(i=1;i<=n+1;i++)
	{
		nod[i]=i;
		printf("\n%d",nod[i]);
	}
	
	for(i=1;i<=n;i++)
	{
		printf("Enter Length Of %dth Element:",i);
		scanf("%d",&lengths[i]);
	}
	int pos[n+2];
	for(i=1;i<=n+1;i++)
	{
		if (i==1)
		pos[1]=0;
		else
		pos[i]=pos[i-1]+lengths[i-1];
	}
	printf("\n\nAnswer:\n");
	for(i=1;i<=n+1;i++)
	{
		printf("Position Of %dth Node :",i);
		printf("%d\n",pos[i]);
	}

	
	/* FORCE */

int z;	
z=2*n+3;	
float concforce[z];
memset(concforce,0,sizeof concforce);
float moment[z];
memset(moment,0,sizeof moment);
int e;
float udl;	
	
	
int t,u;
int node;float concf;
int q;
	printf("\nDo you want to apply conc load?    (1 for YES and 2 for NO)");
		scanf("%d",&u);
		if(u==1)
			{
			printf("\nHow many point loads u want to apply?");	
			scanf("%d",&t);
				for(i=1;i<=t;i++)
				{
					printf("\nEnter the node number and conc. force.");
					scanf("%d %f",&node,&concf);
					q=2*node-1;
						{
							concforce[q]=concf;	
						}
				}
				
				printf("\n\nconc. force matrix is:");
					for(i=1;i<=z;i++)
						{
							printf("\n%f",concforce[i]);
						}
			}
		if(u!=1)
			{
				printf("\n\nNow start applying conc. moment");
			}
int m; float concm;			
printf("\nDo you want to apply conc moment?    (1 for YES and 2 for NO)");
		scanf("%d",&m);
		if(m==1)
			{
				printf("\nHow many conc moments u want to apply?");	
				scanf("%d",&t);
				for(i=1;i<=t;i++)
				{
					printf("\nEnter the node number and conc. moment");
					scanf("%d %f",&node,&concm);
					q=2*node;
						{
							moment[q]=concm;
						}
				}
				printf("\n\nconc. moment matrix is:");
					for(i=1;i<=z;i++)
						{
							printf("\n%f",moment[i]);
						}
			}
		if(m==2)
			{
				printf("\nNow start applying udl");
			}
	
/*printf("\nForce is;\n");*/
float force[z];
memset(force,0,sizeof force);
	for(i=1;i<=z;i++)
	{
		force[i]=moment[i]+concforce[i];
		
	/*	printf("%f",force[i]);*/
	}

int element;	
printf("\nDo you want to apply udl?    (1 for YES and 2 for NO)");
		scanf("%d",&m);
		if(m==1)
			{
				printf("\nHow many udl u want to apply?");	
				scanf("%d",&t);
				for(i=1;i<=t;i++)
				{
					printf("Enter the element no. and value of udl");
					scanf("%d %f",&element,&udl);
					q=2*element-1;
					concforce[q]=(udl*lengths[element]/2)+concforce[q];
					q=q+2;
					concforce[q]=(udl*lengths[element]/2)+concforce[q];
					q=2*element;
					moment[q]=(udl*lengths[element]*lengths[element]/12)+moment[q];
					q=q+2;
					moment[q]=(-udl*lengths[element]*lengths[element]/12)+moment[q];
				}
			}

			


printf("Force finally is;\n");
	for(i=1;i<=z;i++)
	{
		force[i]=moment[i]+concforce[i];
		printf("\n %.2f",force[i]);
	}	

	


int reqsize=2*n+2;
float ke[n+1][reqsize][reqsize];
memset(ke,0,sizeof ke);
int thr=0;

for(i=1;i<n+1;i++)
{
	float tmp[4][4]={
			  {(E*I*12)/(lengths[i]*lengths[i]*lengths[i]), 				(6*E*I)/(lengths[i]*lengths[i]), 				(-12*E*I)/(lengths[i]*lengths[i]*lengths[i]), 			(6*E*I)/(lengths[i]*lengths[i])},
			  {(6*E*I)/(lengths[i]*lengths[i]), 							(4*E*I)/(lengths[i]), 							(-6*E*I)/(lengths[i]*lengths[i]), 						(2*E*I)/(lengths[i])},
			  {(-E*I*12)/(lengths[i]*lengths[i]*lengths[i]), 				(-6*E*I)/(lengths[i]*lengths[i]), 				(E*I*12)/(lengths[i]*lengths[i]*lengths[i]),			(-6*E*I)/(lengths[i]*lengths[i]),},
			  {(6*E*I)/(lengths[i]*lengths[i]),							 	(2*E*I)/(lengths[i]),							(-6*E*I)/(lengths[i]*lengths[i]), 						(4*E*I)/(lengths[i]),}
		  			};
		  
	for(j=0;j<4;j++)
	{
		for(k=0;k<4;k++)
		{
			ke[i][thr+j][thr+k]=tmp[j][k];
		}
	}
	thr+=2;
}

float kg[reqsize][reqsize];
memset(kg,0,sizeof kg);
for(i=1;i<n+1;i++)
{
	for(j=0;j<reqsize;j++)
	{
		for(k=0;k<reqsize;k++)
		{
			kg[j][k]+=ke[i][j][k];
		}
	}
}

printf("\nYour Global Stiffness Matrix is:\n");
float matrix[100][100];
for(j=0;j<reqsize;j++)
{
	for(k=0;k<reqsize;k++)
	{
		printf("%.2f\t ",kg[j][k]);
		matrix[j][k]=kg[j][k];
	}
	printf("\n");
}

int cc;

int y;
printf("Enter the no of fixed supports");
scanf("%d",&y);
if(y>0)
			{
				for(i=1;i<=y;i++)
				{
					printf("Enter the node number at which you want to implement fixed support");
					scanf("%d",&node);
					
					for(k=1;k<=n+1;k++)
					{
						if(nod[k]==node)
						{
							for(cc=k;cc<=n+1;cc++)
								nod[cc]=nod[cc]+1;
								node=nod[k];
						break;
						}
						
						
					}
					
					node=node*2-1;
					m=node-1;
					for(j=node-1;j<=z;j++)
						{
							force[j]=force[j+2];
						}
					for(j=m;j<=z;j++)
						{
							for(k=m;k<=z;k++)
								{
									matrix[j][k]=matrix[j+2][k+2];
								}
						}
						
				}
			}
z=z-2*y;
printf("\nReduced Force Matrix after fixed support is;\n");
	for(i=1;i<=z;i++)
	{
		printf("\n%d Element is\t %.2f",i,force[i]);
	}	
printf("\nReduced Global Matrix after fixed support is;\n");
int reqsizenew;
reqsizenew=reqsize-2*y;
for(j=0;j<reqsizenew;j++)
{
	for(k=0;k<reqsizenew;k++)
	{
		printf("%.2f\t ",matrix[j][k]);
	}
	printf("\n");
}

int aa;
printf("Enter the no of simply supports");
scanf("%d",&aa);
if(aa>0)
			{
				for(i=1;i<=aa;i++)
				{
					printf("Enter the node number at which you want to implement simple support");
					scanf("%d",&node);
					if(y>=node)
					node=y-node;
					else
					node=node-y;
					node=node-i+1;
					z=z-1;
					node=node*2-1;
					m=node-1;
					for(j=node;j<=z;j++)
						{
							force[j]=force[j+1];
						}
					for(j=m;j<=z;j++)
						{
							for(k=m;k<=z;k++)
								{
									matrix[j][k]=matrix[j+1][k+1];
								}
						}
				}
			}

printf("\nReduced Force Matrix after simply support is;\n");
	for(i=1;i<=z;i++)
	{
		printf("\n%d Element is\t %.2f",i,force[i]);
	}	
printf("\nReduced Global Matrix after simply support is;\n");
reqsizenew=reqsize-aa;
for(j=0;j<reqsizenew;j++)
{
	for(k=0;k<reqsizenew;k++)
	{
		printf("%.2f\t ",matrix[j][k]);
	}
	printf("\n");
}
				


/*INVERSE*/
int s=reqsizenew;

    float ratio,a;

    for(i = 0; i < s; i++){
        for(j = s; j < 2*s; j++){
            if(i==(j-s))
                matrix[i][j] = 1.0;
            else
                matrix[i][j] = 0.0;
        }
    }
    for(i = 0; i < s; i++){
        for(j = 0; j < s; j++){
            if(i!=j){
                ratio = matrix[j][i]/matrix[i][i];
                for(k = 0; k < 2*s; k++){
                    matrix[j][k] -= ratio * matrix[i][k];
                }
            }
        }
    }
    for(i = 0; i < s; i++){
        a = matrix[i][i];
        for(j = 0; j < 2*s; j++){
            matrix[i][j] /= a;
        }
    }
    printf("The inverse matrix is: \n");
    for(i = 0; i < s; i++){
        for(j = s; j < 2*s; j++){
            printf("%.2f", matrix[i][j]);
            printf("\t");
        }
        printf("\n");
    }
    return 0;
}


	

