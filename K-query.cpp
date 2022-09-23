#include<bits/stdc++.h>

using namespace std;

struct Node{
    vector<long long int>lst;
};

class SegTree{
    public:
    vector<Node>seg;

    SegTree(long long int n){
        seg.resize(4*n+1);
    }

    void build(long long int idx,long long int low,long long int high,vector<long long int>&arr){
        if(low==high){
            seg[idx].lst.push_back(arr[low]);
            return;
        }

        long long int mid=(low+high)/2;

        build(2*idx+1,low,mid,arr);
        build(2*idx+2,mid+1,high,arr);

        merge(seg[2*idx+1].lst.begin(),seg[2*idx+1].lst.end(),seg[2*idx+2].lst.begin(),seg[2*idx+2].lst.end(),back_inserter(seg[idx].lst));
    }

    long long int query(long long int idx,long long int low,long long int high,long long int l,long long int r,long long int k){
        if(r<low||high<l){
            return 0;
        }

        if(l<=low&&high<=r){
            return seg[idx].lst.end()-upper_bound(seg[idx].lst.begin(),seg[idx].lst.end(),k);
        }

        long long int mid=(low+high)/2;

        return query(2*idx+1,low,mid,l,r,k)+query(2*idx+2,mid+1,high,l,r,k);
    }
};

// void print_vector(vector<long long int>&arr){
//     for(auto itr:arr){
//         cout<<itr<<" ";
//     }
//     cout<<"\n";
// }

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    long long int n,i,q,l,r,k;
    cin>>n;
    vector<long long int>arr(n);
    
    for(i=0;i<n;i++){
        cin>>arr[i];
    }

    SegTree obj(n);
    // cout<<(obj.seg[0].lst.size());
    
    obj.build(0,0,n-1,arr);

    // print_vector(obj.seg[0].lst);

    cin>>q;
    for(i=0;i<q;i++){
        cin>>l>>r>>k;
        cout<<obj.query(0,0,n-1,l-1,r-1,k)<<"\n";
    }

    return 0;
}