#include<bits/stdc++.h>

using namespace std;

class SegTree{
    
    public:
    vector<long long int>seg;

    SegTree(long long int n){
        seg.resize(4*n+1);
    }

    void build(long long int idx,long long int low,long long int high,unordered_map<long long int,long long int>&arr){
        if(low==high){
            seg[idx]=arr[low];
            return;
        }

        long long int mid=(low+high)/2;

        build(2*idx+1,low,mid,arr);
        build(2*idx+2,mid+1,high,arr);

        seg[idx]=seg[2*idx+1]+seg[2*idx+2];
    }

    void update(long long int idx,long long int low,long long int high,long long int i,long long int val){
        if(low==high){
            seg[idx]+=val;
            return;
        }

        long long int mid=(low+high)/2;

        if(i<=mid){
            update(2*idx+1,low,mid,i,val);
        }
        else{
            update(2*idx+2,mid+1,high,i,val);
        }

        seg[idx]=seg[2*idx+1]+seg[2*idx+2];
    }

    long long int query(long long int idx,long long int low,long long int high,long long int l,long long int r){
        if(high<l||low>r){
            return 0;
        }
        else if(low>=l&&high<=r){
            return seg[idx];
        }

        long long int mid=(low+high)/2;

        return query(2*idx+1,low,mid,l,r)+query(2*idx+2,mid+1,high,l,r);
    }

};



int main(){

    long long int t,i,j,n;
    cin>>t;
    while(t--){

        cin>>n;
        vector<long long int>arr(n);
        long long int maxi=LONG_LONG_MIN,mini=LONG_LONG_MAX;
        for(i=0;i<n;i++){
            cin>>arr[i];
            mini=min(mini,arr[i]);
            maxi=max(maxi,arr[i]);
        }

        unordered_map<long long int,long long int>freq;

        for(i=mini;i<=maxi;i++){
            freq[i]=0;
        }

        for(i=0;i<n;i++){
            freq[arr[i]]++;
        }

        SegTree obj(maxi-mini+1);

        obj.build(0,mini,maxi,freq);

        long long int cnt=0;
        for(i=0;i<n;i++){
            freq[arr[i]]-=1;
            obj.update(0,mini,maxi,arr[i],-1);
            cnt+=obj.query(0,mini,maxi,mini,arr[i]-1);
        }

        cout<<cnt<<"\n";
        
    }

    return 0;
}