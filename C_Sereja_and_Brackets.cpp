#include<bits/stdc++.h>

using namespace std;

struct Node{
    long long int open=0;
    long long int close=0;
    long long int full=0;
};

class SegTree{
    public:
    vector<Node>seg;

    SegTree(long long int n){
        seg.resize(4*n+1);
    }
    
    void build(long long int idx,long long int low,long long int high,string&s){
        if(low==high){
             if(s[low]=='(')
             seg[idx].open=1;
             else
             seg[idx].close=1;

             return;
        }
        
        long long int mid=(low+high)/2;
        build(2*idx+1,low,mid,s);
        build(2*idx+2,mid+1,high,s);
        

        seg[idx].full=seg[2*idx+1].full+seg[2*idx+2].full+min(seg[2*idx+1].open,seg[2*idx+2].close);
        seg[idx].open=seg[2*idx+1].open+seg[2*idx+2].open-min(seg[2*idx+1].open,seg[2*idx+2].close);
        seg[idx].close=seg[2*idx+1].close+seg[2*idx+2].close-min(seg[2*idx+1].open,seg[2*idx+2].close);
    }

    Node query(long long int idx,long long int low,long long int high,long long int l,long long int r){
        if(high<l||r<low){
            Node node;
            return node;
        }
        else if(low>=l&&high<=r){
            return seg[idx];
        }

        long long int mid=(low+high)/2;

        Node left=query(2*idx+1,low,mid,l,r);
        Node right=query(2*idx+2,mid+1,high,l,r);

        Node node;
        node.full=left.full+right.full+min(left.open,right.close);
        node.open=left.open+right.open-min(left.open,right.close);
        node.close=left.close+right.close-min(left.open,right.close);

        return node;
    }
};


int main(){
    string s;
    long long int i,m,l,r;
    cin>>s;
    SegTree segobj(s.size());
    segobj.build(0,0,s.size()-1,s);
    cin>>m;
    for(i=0;i<m;i++){
        cin>>l>>r;
        cout<<2*segobj.query(0,0,s.size()-1,l-1,r-1).full<<"\n";
    }
    return 0;
}

