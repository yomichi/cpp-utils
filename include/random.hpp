#ifndef UTIL_RANDOM_HPP
#define UTIL_RANDOM_HPP

#include <boost/random/uniform_real.hpp>
#include <boost/random/normal_distribution.hpp>

namespace util{

template <class RNG>
inline double random_01(RNG &rng)
{
    static boost::uniform_real<double> dist(0.0, 1.0);
    return dist(rng);
}

template <class RNG>
inline int random_int(RNG &rng, int N)
{
    return static_cast<int>( N * random_01(rng));
}

template <class RNG>
inline double random_gauss(RNG &rng, double sigma=1.0)
{
    static boost::normal_distribution<double> dist(0.0, 1.0);
    return sigma*dist(rng);
}


}

#endif
