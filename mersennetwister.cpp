#include "mersennetwister.h"


MersenneTwister::MersenneTwister()
{
    // You are expected to reseed
    m_index = 0;
}

MersenneTwister::MersenneTwister(unsigned int seed)
{
    reseed(seed);
}

void MersenneTwister::reseed(unsigned int seed)
{
    // Initialize by filling with the seed, then iterating
    // the algorithm a bunch of times to shuffle things up.
    m_buffer[0] = seed;
    for (int i = 1; i < MT_LEN; i++)
        m_buffer[i] = 0x6c078965u * (m_buffer[i-1] ^ (m_buffer[i-1] >> 30)) + i;
    m_index = 0;
    for (int i = 0; i < MT_LEN * 4; i++)
        integer();
}

unsigned int MersenneTwister::integer()
{
    // Indices
    int i = m_index;
    int i2 = m_index + 1; if (i2 >= MT_LEN) i2 = 0; // wrap-around
    int j = m_index + MT_IA; if (j >= MT_LEN) j -= MT_LEN; // wrap-around

    // Twist
    unsigned int s = (m_buffer[i] & 0x80000000) | (m_buffer[i2] & 0x7fffffff);
    unsigned int r = m_buffer[j] ^ (s >> 1) ^ ((s & 1) * 0x9908B0DF);
    m_buffer[m_index] = r;
    m_index = i2;

    // Swizzle
    r ^= (r >> 11);
    r ^= (r << 7) & 0x9d2c5680UL;
    r ^= (r << 15) & 0xefc60000UL;
    r ^= (r >> 18);
    return r;
}
