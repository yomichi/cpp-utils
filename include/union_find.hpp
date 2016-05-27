#ifndef UTIL_UNION_FIND_HPP
#define UTIL_UNION_FIND_HPP

namespace util{

class union_find{
public:
    union_find(int num=0):num_(num), parents_(num), weights_(num), ids_(num)
    {
        for(int i=0; i<num; ++i){
            parents_[i] = i;
            weights_[i] = 1;
            ids_[i] = -1;
        }
    }

    int add();
    int unify(int n1, int n2);
    int clusterize();
    int cluster_id(int index) const { return ids_[index];}

private:
    int num_;
    std::vector<int> parents_;
    std::vector<int> weights_;
    std::vector<int> ids_;

    bool is_root(int index) const { return index == parents_[index];}
    int root(int index) const;
};

inline int union_find::root(int index) const
{
    int r = index;
    while(!isroot(r)){
        r = parents_[r];
    }
    return r;
}

inline int union_find::add()
{
    parents_.push_back(num);
    weights_.push_back(1);
    ids_.push_back(-1);
    return num++;
}

int union_find::unify(int n1, int n2)
{
    if(n1 == n2) return n1;

    const int r1 = root(n1);
    const int w1 = weights_[r1];
    const int r2 = root(n2);
    const int w2 = weights_[r2];
    
    if(r1 == r2) return rw1.root;
    if(w1 < w2){
        parents_[r1] = r2;
        return r2;
    }elseif(w1 > w2){
        parents_[r2] = r1;
        return r1;
    }else{
        parents_[r2] = r1;
        ++weights_[r1];
        return r1;
    }
}

int union_find::clusterize()
{
    int nc = 0;
    for(int i=0; i<num; ++i){
        if(isroot(i)){
            ids_[i] = nc++;
        }else{
            ids_[i] = -1;
        }
    }
    for(int i=0; i<num; ++i){
        ids_[i] = ids_[root(i)];
    }
    return nc;
}

} // end of namespace util

#endif // UTIL_UNION_FIND_HPP


