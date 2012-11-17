#include <iostream>
#include <vector>
using namespace std;

struct result{
	int depth;
	int width;
	int area;
	int leftLocX;
	int leftLocY;
};
struct point{
	int x;
	int y;
};

void resultToPoint(result* allResult,int m,int n,point *left,point *right){
	left->x = allResult->leftLocX;
	left->y = allResult->leftLocY;
	right->x = left->x + allResult->width;
	right->y = left->y + allResult->depth;
	return;
}

void maxSeq(vector<int>* arr,int start,int end,result* self){
	if(start > end)
		return ;
	int mid = (start+end)/2;
	int depth = (*arr)[mid];

	int pleft=mid;
	while(pleft>=start && (*arr)[pleft]>=depth)
		pleft--;

	int pright = mid;
	while(pright<=end && (*arr)[pright]>=depth)
		pright++;
	
	
	int width = pright - pleft-1;
	int area = depth * width;
	int leftLocX = pleft + 1;
	
	while(pleft >= start || pright <= end){
		int depPos = pright>end?pleft:pright;
		if(pleft >= start && pright <= end)
			depPos = ((*arr)[pleft]>(*arr)[pright])?pleft:pright;

		int tempDepth = (*arr)[depPos];
		while(pleft>=start && (*arr)[pleft]>=tempDepth)
			pleft--;
		while(pright<=end && (*arr)[pright]>=tempDepth)
			pright++;

		int tempWidth = pright - pleft-1;
		int tempArea = tempWidth*tempDepth;
		if(tempArea > area){
			depth = tempDepth;
			width = tempWidth;
			area = tempArea;
			leftLocX = pleft + 1;
		}
	}
	
	if(area > self->area){
		self->leftLocX=leftLocX;
		self->depth = depth;
		self->width = width;
		self->area = area;
	}

	maxSeq(arr,start,mid-1,self);
	maxSeq(arr,mid+1,end,self);	
}

void maxArea(vector<int>* arr,int m,int n, result* allResult){
	for(int i=0;i<m;i++){
		int j=0;
		while(j<n){
			while((*arr)[i*n+j] == 0 && j<n)
				j++;
			int start = j;
			while((*arr)[i*n+j] > 0 && j<n)
				j++;
			int end=j-1;
			if(start<=end && end<n){
				result* tempResult = new result;
				tempResult->leftLocY = i;
				tempResult->area = 0;
				start += i*n;
				end += i*n;
				maxSeq(arr,start,end,tempResult);
				if(tempResult->area > allResult->area){
					allResult->depth = tempResult->depth;
					allResult->width = tempResult->width;
					allResult->area = tempResult->area;
					allResult->leftLocX = tempResult->leftLocX-i*n;
					allResult->leftLocY = tempResult->leftLocY;
				}
			}
		}
	}
}


void process(vector<int>& arr,int m,int n){
	for(int i=m-2;i>=0;i--){
		for(int j=0;j<n;j++)
		{
			if(arr[i*n + j] == 1){
				arr[i*n + j] = arr[(i+1)*n + j] + 1;
			}
		}
	}
}

void core(vector<int>* arr,int m,int n,point *left,point *right){
	result* allResult = new result();
	allResult->area=0;
	maxArea(arr,m,n,allResult);
	/*
	cout<<"area:"<<allResult->area<<endl;
	cout<<"depth:"<<allResult->depth<<endl;
	cout<<"leftLocX:"<<allResult->leftLocX<<endl;
	cout<<"leftLocY:"<<allResult->leftLocY<<endl;
	cout<<"width:"<<allResult->width<<endl;
	*/
	resultToPoint(allResult,m,n,left,right);
}

int main(){
	
	vector<int> arr;
	arr.push_back(1);
	arr.push_back(0);
	arr.push_back(1);
	arr.push_back(1);

	arr.push_back(0);
	arr.push_back(1);
	arr.push_back(1);
	arr.push_back(0);

	arr.push_back(0);
	arr.push_back(1);
	arr.push_back(1);
	arr.push_back(0);

	arr.push_back(1);
	arr.push_back(1);
	arr.push_back(0);
	arr.push_back(1);

	int m =4;
	int n =4;
	for(int i=0;i<m;i++){
		for(int j=0;j<n;j++)
			cout << arr[i*n + j]<<"	";
		cout << endl;
	}
	cout <<"process"<<endl;
	process(arr,m,n);
	for(i=0;i<m;i++){
		for(int j=0;j<n;j++)
			cout << arr[i*n + j]<<"	";
		cout << endl;
	}
	cout <<"result"<<endl;
	point* left = new point;
	point* right = new point;
	core(&arr,m,n,left,right);
	cout << left->x<<"	";
	cout << left->y<<"	";
	cout << right->x<<"	";
	cout << right->y<<endl;
	return 0;
}