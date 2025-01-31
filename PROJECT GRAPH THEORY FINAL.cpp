
#include<iostream>
#define E 7
using namespace std;
void multi(  float result [][E] , float p[][E] ,float q[][E] ,int n, int m ,int o  );
void showmatrix(float p[][E] ,int n, int m);
void sum(  float result [][E] , float p[][E] ,float q[][E] ,int n, int m   );
void transpose(float r[][E] , float p[][E] ,int n, int m);
void difference(  float result [][E] , float p[][E] ,float q[][E] ,int n, int m   );
bool inverse(float result[][E],float p[][E],int n);
void getCofactor(float A[][E], float temp[][E], int p, int q, int n);
float determinant(float A[][E], int n);
void adjoint(int A[][E],int adj[][E],int N);
int main()
{
	int node , ele ;
	cout<<"Enter number of element "<<endl;
	cin>>ele;
	cout<<"Enter number of node "<<endl;
	cin>>node;
	float input[ele][5];
	for(int i=0 ;i<ele;i++)
	{
		for(int j=0;j<5;j++)
		{
		 switch(j)
		   {
			case 0:
				cout<<"enter starting node of element "<<i+1<<endl;
				cin>>input[i][j];
				break;			
			case 1:
				cout<<"enter ending node of element "<<i+1<<endl;
				cin>>input[i][j];
				break;
			case 2:
				cout<<"enter souce current of element "<<i+1<<endl;
				cin>>input[i][j];
				break;				
			case 3:
				cout<<"enter souce voltage of element "<<i+1<<endl;
				cin>>input[i][j];
				break;
			case 4:
				cout<<"enter conductance of element "<<i+1<<endl;
				cin>>input[i][j];
				break;
			
		   }
		}
	}
	float ise[ele][E] , vse[ele][E] , conductance[ele][E];
	 for(int i = 0 ; i<ele;i++)
	 {
	 	ise[i][0]=input[i][2];
	 	vse[i][0] =input[i][3];
	 	
	 }
	for(int i=0;i<ele;i++)
	{
		for(int j=0; j<ele; j++)
		{
			if(i==j)
			{
				conductance[i][i]=input[i][4];
			}
			else{
				conductance[i][j] = 0;
			}
		}
	}
	float A[node-1][E];
	for(int i=0;i<ele;i++)
	{
		for(int j=1;j<node;j++)
		{
			if(j==input[i][0])
			{
				A[j-1][i]= 1;
			}else if(j==input[i][1])
			{
				A[j-1][i] =-1;
			}else{
				A[j-1][i] =0;
			}
		}
	}
	cout<<"matrix A ="<<endl;
	showmatrix(A,node-1,ele);
	cout<<endl;
	cout<< " matrix Ise = "<<endl;
	showmatrix(ise,ele,1);
	cout<<endl;
	cout<<"Matrix vse ="<<endl;
	showmatrix(vse,ele,1);
	cout<<endl;
	cout<<"conductance matrix = "<<endl;
	showmatrix(conductance,ele,ele);
	cout<<endl;
	float at[ele][E];
    transpose(at,A,ele,node-1);
    cout<<"matrix A transpose ="<<endl;
    showmatrix(at,ele,node-1);
    float Y1[node-1][E];
    multi(Y1,A,conductance,node-1,ele,ele);
    float Y[node-1][E];
    multi(Y,Y1,at,node-1,node-1,ele);
    cout<<"matrix Y="<<endl;
    showmatrix(Y,node-1,node-1);
    float isn11[node-1][E];
    multi(isn11,A,conductance,node-1,ele,ele);
	float isn1[node-1][E];
	multi(isn1,isn11,vse,node-1,1,ele);
	float isn2[node-1][E];
	multi(isn2,A,ise,node-1,1,ele);
	float isn[node-1][E];
	difference(isn,isn1,isn2,node-1,1);
	cout<<endl;
	cout<<"matrix isn ="<<endl;
	showmatrix(isn,node-1,1);
	float Yin[node-1][E];
    inverse(Yin,Y,node-1);
	float Vn[node-1][E];
	multi(Vn,Yin,isn,node-1,1,node-1);
	cout<<"Vn matrix = "<<endl;
	showmatrix(Vn,node-1,1);
	float Ve[ele][E];
	multi(Ve,at,Vn,ele,1,node-1);
	cout<<"matrix ve = "<<endl;
	showmatrix(Ve,ele,1);
	float ie1[ele][E];
	multi(ie1,conductance,Ve,ele,1,ele);
	float ie2[ele][E];
	multi(ie2,conductance,vse,ele,1,ele);
	float ie3[ele][E];
	difference(ie3,ie1,ie2,ele,1);
	float ie[ele][E];
	sum(ie,ie3,ise,ele,1);
	cout<<"matrix ie = "<<endl;
	showmatrix(ie,ele,1);
   
	return 0;
}

void multi(  float r [][E] , float p[][E] ,float q[][E] ,int n,int m ,int o )
 {
 	for( int i=0;i<n;i++)
 	{
 		for( int j =0 ;j<m;j++)
 		{  float sum =0;
 			for(int k=0;k<o;k++)
 			{
 			r[i][j] += p[i][k]*q[k][j];
			 }
		 }
	 }
 }
void showmatrix(float p[][E] ,int n,  int m)
{
	for(int i=0;i<n;i++)
	{
		for(int j=0;j<m;j++)
		{
			cout<<p[i][j]<<"\t";
		}
		cout<<endl;
	}
}
void sum(  float r [][E] , float p[][E] ,float q[][E] ,int n,int m  )
 {
 	for( int i=0;i<n;i++)
 	{
 		for( int j =0 ;j<m;j++)
 		{  
 			r[i][j]=p[i][j]+q[i][j];
		 }
	 }
 }
void transpose(float r[][E],float p[][E] ,int n,  int m)
{
	for(int i=0;i<n;i++)
	{
		for(int j=0;j<m;j++)
		{
			r[i][j] = p[j][i];
		}
		cout<<endl;
	}
}
void difference(  float r [][E] , float p[][E] ,float q[][E] ,int n,int m  )
 {
 	for( int i=0;i<n;i++)
 	{
 		for( int j =0 ;j<m;j++)
 		{  
 			r[i][j]=p[i][j]-q[i][j];
		 }
}
}
void getCofactor(float A[][E], float temp[][E], int p, int q, int n)
{
    int i = 0, j = 0;
 
    
    for (int row = 0; row < n; row++)
    {
        for (int col = 0; col < n; col++)
        {
        
            
            if (row != p && col != q)
            {
                temp[i][j++] = A[row][col];
 
                if (j == n - 1)
                {
                    j = 0;
                    i++;
                }
            }
        }
    }
}
 

float determinant(float A[][E], int n)
{
    float D = 0; 
 
    
    if (n == 1)
        return A[0][0];
 
    float temp[n][E];
 
    int sign = 1;  
 
     
    for (int f = 0; f < n; f++)
    {
        
        getCofactor(A, temp, 0, f, n);
        D += sign * A[0][f] * determinant(temp, n - 1);
 
        
        sign = -sign;
    }
 
    return D;
}
 

void adjoint(float A[][E],float adj[][E],int N)
{
    if (N == 1)
    {
        adj[0][0] = 1;
        return;
    }
 
    
    int sign = 1;
	float temp[N][E];
 
    for (int i=0; i<N; i++)
    {
        for (int j=0; j<N; j++)
        {
            getCofactor(A, temp, i, j, N);
 
            sign = ((i+j)%2==0)? 1: -1;
 
            adj[j][i] = (sign)*(determinant(temp, N-1));
        }
    }
}
 
bool inverse( float inverse[][E], float A[][E],int N)
{
    
    float det = determinant(A, N);
    if (det == 0)
    {
        cout << "Singular matrix, can't find its inverse";
        return false;
    }
 
    
    float adj[N][E];
    adjoint(A, adj,  N);
 
    // Find Inverse using formula "inverse(A) = adj(A)/det(A)"
    for (int i=0; i<N; i++)
        for (int j=0; j<N; j++)
            inverse[i][j] = adj[i][j]/float(det);
 
    return true;
}
 

