#include<bits/stdc++.h>

using namespace std;

class SegTree{
    
    public:
    vector<long long int>seg;

    SegTree(long long int n){
        seg.resize(4*n+1);
    }

    void build(long long int idx,long long int low,long long int high,vector<long long int>&arr){
        if(low==high){
            seg[idx]=arr[low];
            return;
        }

        long long int mid=(low+high)/2;

        build(2*idx+1,low,mid,arr);
        build(2*idx+2,mid+1,high,arr);

        long long int p=log2(high-low+1);
        if(p%2==0){
            seg[idx]=seg[2*idx+1]^seg[2*idx+2];
        }
        else{
            seg[idx]=seg[2*idx+1]|seg[2*idx+2];
        }
    }

    void update(long long int idx,long long int low,long long int high,long long int i,long long int val){
        if(low==high){
            seg[idx]=val;
            return;
        }

        long long int mid=(low+high)/2;

        if(i<=mid){
            update(2*idx+1,low,mid,i,val);
        }
        else{
            update(2*idx+2,mid+1,high,i,val);
        }

        long long int p=log2(high-low+1);
        if(p%2==0){
            seg[idx]=seg[2*idx+1]^seg[2*idx+2];
        }
        else{
            seg[idx]=seg[2*idx+1]|seg[2*idx+2];
        }
    }

};

int main(){

    long long int n,m,N,i,p,b;
    cin>>n>>m;
    N=pow(2,n);
    vector<long long int>arr(N);
    for(i=0;i<N;i++){
        cin>>arr[i];
    }
    SegTree seg(N);

    seg.build(0,0,N-1,arr);

    for(i=0;i<m;i++){
        cin>>p>>b;
        seg.update(0,0,N-1,p-1,b);
        arr[p-1]=b;
        cout<<seg.seg[0]<<"\n";
    }

    return 0;
}