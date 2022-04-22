#include <iostream>
#include <cstdlib>
#include <string>
#include <vector>
#include <time.h>

using namespace std;

//Fixed point multiplication
int fxdMulScalar(int num1, int q1, int num2, int q2, int resq){
	long long temp=(long long)num1*num2;
	int res;
	res=temp/(1<<(q1+q2-resq));
	return res;
}

//Fixed point addition
int fxdAddScalar(int num1, int num2){
	return num1+num2;
}

//Bitshift
int bitshift(int num, int shift){
	return num*(1<<shift);
}						
	
//Fixed-point convolution...returns result of convolution	
vector<int> convolutionfxd(vector<int> X, vector<int> H,int lenX, int lenH, int Q){
	vector<int>Y;
	int temp;
	int lenY=lenX+lenH-1;
	for(int n=0;n<lenY;n++){
		temp=0;
		for(int k=0;k<=n;k++){
			if(n-k>=lenH||k>=lenX)
			continue;
			temp=fxdAddScalar(bitshift(temp,0),fxdMulScalar(X[k],Q,H[n-k],Q,Q));
		}
		Y.push_back(temp);
	}
	return Y;
}	

//Floating-point convolution...returns result of convolution
vector<float> convolutionflt(vector<float> X,vector<float> H,int lenX, int lenH){
	vector<float>Y;
	float temp;
	int lenY=lenX+lenH-1;
	for(int n=0;n<lenY;n++){
		temp=0;
		for(int k=0;k<=n;k++){
			if(n-k>=lenH||k>=lenX)
			continue;
			temp+=X[k]*H[n-k];
		}
		Y.push_back(temp);
	}	
	return Y;
}	

/* Takes random X and H, calculates Y_float and Y_fixed and returns MSE */	
double mse(int lenX, int lenH,int Q){
	srand(time(0));
	vector<float>X;
	vector<int>X_fxd;
	for(int i=0;i<lenX;i++){
		X.push_back((float)rand()/RAND_MAX);
		X_fxd.push_back(X.back()*(1<<Q));
		
	}
	vector<float>H;
	vector<int>H_fxd;
	for(int i=0;i<lenH;i++){
		H.push_back((float)rand()/RAND_MAX);
		H_fxd.push_back(H.back()*(1<<Q));
		
	}
	vector<float>Y_flt=convolutionflt(X,H,lenX,lenH);
	vector<int>Y_fxd=convolutionfxd(X_fxd,H_fxd,lenX,lenH,Q);
	int lenY=(int)Y_flt.size();
	vector<float>Y_fxd_converted;
	for(int i=0;i<lenY;i++)
	Y_fxd_converted.push_back((float)Y_fxd[i]/(1<<Q));
	double err=0;
	for(int i=0;i<lenY;i++)
	err+=(Y_flt[i]-Y_fxd_converted[i])*(Y_flt[i]-Y_fxd_converted[i]);
	err/=lenY;
	
	return err;
}



int main(){
	//For this simulation, length of X is being taken as 10 and length of H=25.
	int lenX=10;
	int lenH=25;
	double avg;
	//Q from 5 to 31
	for(int q=5;q<=31;q++){
		avg=0;
		int sample=0;
		//Averaging over 10000 samples
		while(sample<10000){
			avg+=mse(lenX,lenH,q);
			sample++;
		}
		avg/=10000;
		cout<<"Error (Q="<<q<<")= "<<avg<<endl;
	}
	return 0;
}		
		
		
		
	
			
			
	
