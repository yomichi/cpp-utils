#ifndef UTIL_RANDOM_CHOICE_HPP
#define UTIL_RANDOM_CHOICE_HPP

#include <vector>
#include <iterator>
#include <numeric>
#include <queue>
#include "random.hpp"

namespace util{

template <class RNG>
int random_choose(std::vector<double> weights, RNG &rng)
{
    const int sz = weights.length();
    std::vector<double> accs;
    accs.reserve(sz);
    std::partial_sum(weights.begin(), weights.end(), std::back_inserter(accs));
    const double sm = accs[sz-1];
    std::vector<double>::iterator itr = std::lower_bound(accs.begin(), accs.end(), sm*random_01(rng));
    return std::distance(accs.begin(), itr);
}

class walker{
public:
    walker(std::vector<double> const& weights);
    template <class RNG>
    int operator()(RNG &rng)const;
private:
    int num_;
    std::vector<int> alias_;
    std::vector<double> probs_;
};

walker::walker(std::vector<double> const& weights)
    :num_(length(weights)),
    alias_(num_), probs_(weights)
{
    const double sm = std::accumulate(weights.begin(), weights.end());
    const double mn = sm / num_;
    const double inv_mn = 1.0/mn;
    std::queue<int> large, small;
    for(int i=0; i<num_; ++i){
        if(weights_[i] < mn){
            small.push(i);
        }else{
            large.push(i);
        }
    }
    while(!empty(small)){
        int s = small.front();
        int l = large.front();
        double diff = mn - probs_[s];
        probs_[l] -= diff;
        probs_[s] *= inv_mn;
        alias_[s] = l;
        if(probs_[l] < mn){
            small.push(l);
            large.pop();
        }
        small.pop();
    }
}

template <class RNG>
inline int walker::operator()(RNG &rng)const
{
    const int i = random_int(rng, num_);
    return random_01(rng) < probs_[i] ? i : alias_[i];
}

} // end of namespace util

#endif // UTIL_RANDOM_CHOICE_HPP
