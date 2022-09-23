#include<bits/stdc++.h>

using namespace std;

class SegTree{
    public:
    vector<long long int>seg;
    vector<long long int>lazy;

    SegTree(long long int n){
        seg.resize(4*n+1);
        lazy.resize(4*n+1,0);
    }

    void build(long long int idx,long long int low,long long int high,vector<long long int>&arr){
        if(low==high){
            seg[idx]=arr[low];
            return;
        }

        long long int mid=(low+high)/2;
        build(2*idx+1,low,mid,arr);
        build(2*idx+2,mid+1,high,arr);

        seg[idx]=seg[2*idx+1]+seg[2*idx+2];
    }

    void update(long long int idx,long long int low,long long int high,long long int l,long long int r){
        if(lazy[idx]!=0){
            seg[idx]=(high-low+1)-seg[idx];
            if(low!=high){
                lazy[2*idx+1]=!lazy[2*idx+1];
                lazy[2*idx+2]=!lazy[2*idx+2];
            }
            lazy[idx]=0;
        }

        if(r<low||l>high){
            return;
        }

        if(low>=l&&high<=r){
            seg[idx]=(high-low+1)-seg[idx];
            if(low!=high){
                lazy[2*idx+1]=!lazy[2*idx+1];
                lazy[2*idx+2]=!lazy[2*idx+2];
            }
            return;
        }

        long long int mid=(low+high)/2;
        update(2*idx+1,low,mid,l,r);
        update(2*idx+2,mid+1,high,l,r);

        seg[idx]=seg[2*idx+1]+seg[2*idx+2];
        
    }

    long long int query(long long int idx,long long int low,long long int high,long long int l,long long int r){
        if(lazy[idx]!=0){
            seg[idx]=(high-low+1)-seg[idx];
            if(low!=high){
                lazy[2*idx+1]=!lazy[2*idx+1];
                lazy[2*idx+2]=!lazy[2*idx+2];
            }
            lazy[idx]=0;
        }
        
        if(r<low||l>high){
            return 0;
        }
        
        if(low>=l&&high<=r){
            return seg[idx];
        }

        long long int mid=(low+high)/2;

        long long int left=query(2*idx+1,low,mid,l,r);
        long long int right=query(2*idx+2,mid+1,high,l,r);

        return left+right;
    }


};

int main(){
    long long int i,n,q,t,l,r;
    cin>>n;
    vector<long long int>arr(n);
    for(i=0;i<n;i++){
        cin>>arr[i];
    }
    SegTree st(n);
    st.build(0,0,n-1,arr);
    cin>>q;
    for(i=0;i<q;i++){
        cin>>t>>l>>r;
        if(t==1){
           cout<<st.query(0,0,n-1,l,r)<<"\n";
        }
        else{
            st.update(0,0,n-1,l,r);
        }
    }
    return 0;
}