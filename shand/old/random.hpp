#ifndef SHAND_RANDOM_INCLUDE
#define SHAND_RANDOM_INCLUDE

#include <ctime>
#include <cstdlib>
#include <cassert>
#include <algorithm>

#pragma warning(disable : 4307)

namespace shand {

struct mt32traits
{
	static const int	INTTYPE_BITS	= 32;
	static const size_t	NN				= 624;
	static const size_t	MM				= 397;
	static const size_t	INITVAL			= 1812433253U;
	static const size_t	ARRAYINITVAL_0	= 19650218U;
	static const size_t	ARRAYINITVAL_1	= 1664525U;
	static const size_t	ARRAYINITVAL_2	= 1566083941U;

	static size_t twist(size_t u, size_t v)
	{
		static size_t mag01[2] = {0U, 0x9908b0dfU};
		return ((((u & 0x80000000U) | (v & 0x7fffffffU)) >> 1) ^ mag01[v&1]);
	}

	static size_t temper(size_t value)
	{
		value ^= (value >> 11);
		value ^= (value <<  7) & 0x9d2c5680U;
		value ^= (value << 15) & 0xefc60000U;
		value ^= (value >> 18);
		return value;
	}

	static double to_double1(size_t value)
	{
		// 32bit resolution
		return static_cast<double>(value) * (1.0/4294967295.0);
	}

	static double to_double2(size_t value)
	{
		// 32bit resolution
		return static_cast<double>(value) * (1.0/4294967296.0);
	}

	static double to_double3(size_t value)
	{
		// 32bit resolution
		return (static_cast<double>(value) + 0.5) * (1.0/4294967296.0);
	}
};

struct mt64traits
{
	static const int				INTTYPE_BITS	= 64;
	static const size_t				NN				= 312;
	static const size_t				MM				= 156;
	static const unsigned long long	INITVAL			= 6364136223846793005ULL;
	static const unsigned long long	ARRAYINITVAL_0	= 19650218ULL;
	static const unsigned long long	ARRAYINITVAL_1	= 3935559000370003845ULL;
	static const unsigned long long	ARRAYINITVAL_2	= 2862933555777941757ULL;

	static unsigned long long twist(unsigned long long u, unsigned long long v)
	{
		static unsigned long long mag01[2] = {0ULL, 0xB5026F5AA96619E9ULL};
		return ((((u & 0xFFFFFFFF80000000ULL) | (v & 0x7FFFFFFFULL)) >> 1) ^ mag01[v&1]);
	}

	static unsigned long long temper(unsigned long long value)
	{
		value ^= (value >> 29) & 0x5555555555555555ULL;
		value ^= (value << 17) & 0x71D67FFFEDA60000ULL;
		value ^= (value << 37) & 0xFFF7EEE000000000ULL;
		value ^= (value >> 43);

		return value;
	}

	static double to_double1(unsigned long long value)
	{
		// 53bit resolution
		return static_cast<double>(value >> 11) * (1.0/9007199254740991.0);
	}

	static double to_double2(unsigned long long value)
	{
		// 53bit resolution
		return static_cast<double>(value >> 11) * (1.0/9007199254740992.0);
	}

	static double to_double3(unsigned long long value)
	{
		// 52bit resolution
		return (static_cast<double>(value >> 12) + 0.5) * (1.0/4503599627370496.0);
	}
};


template <typename Traits>
class mt19937
{
protected:
	// member variables
	size_t*		state_;
	size_t		left_;
	size_t*		next_;

protected:
	void next_state()
	{
		size_t *p = state_;

		left_ = Traits::NN;
		next_ = state_;

		size_t index;
		for (index = Traits::NN-Traits::MM+1; --index; p++)
			*p = p[Traits::MM] ^ Traits::twist(p[0], p[1]);

		for (index = Traits::MM; --index; p++)
			*p = p[Traits::MM-Traits::NN] ^ Traits::twist(p[0], p[1]);

		*p = p[Traits::MM-Traits::NN] ^ Traits::twist(p[0], state_[0]);
	}

public:
	mt19937()
	{
		left_ = 1;
		next_ = NULL;

		state_ = new size_t[Traits::NN];
		init(static_cast<size_t>(time(NULL)));
	}

	mt19937(size_t seed)
	{
		left_ = 1;
		next_ = NULL;
		state_ = new size_t[Traits::NN];
		init(seed);
	}

	mt19937(size_t initkeys[], size_t keylen)
	{
		left_ = 1;
		next_ = NULL;
		state_ = new size_t[Traits::NN];
		init(initkeys, keylen);
	}

	virtual ~mt19937()
	{
		if (state_) {
			delete[] state_;
		}
	}
      
	void init(size_t seed)
	{
		// check that INTTYPE_BITS is correct.
		assert(sizeof(size_t) * 8 == static_cast<size_t>(Traits::INTTYPE_BITS));

		state_[0]= seed;
		for (size_t index = 1; index < Traits::NN; index++) {
			state_[index] = (Traits::INITVAL * (state_[index-1] ^ (state_[index-1] >> (Traits::INTTYPE_BITS-2))) + static_cast<size_t>(index)); 
		}
		left_ = 1;
	}
      
	void init(size_t initkeys[], size_t keylen)
	{
		init(Traits::ARRAYINITVAL_0);

		size_t state_index	= 1;
		size_t key_index	= 0;
		size_t loop_index	= (Traits::NN > keylen ? Traits::NN : keylen);

		for (; loop_index > 0; loop_index--) {
			state_[state_index] = (state_[state_index] ^ ((state_[state_index-1] ^ (state_[state_index-1] >> (Traits::INTTYPE_BITS-2)))
							* Traits::ARRAYINITVAL_1)) + initkeys[key_index] + static_cast<size_t>(key_index); // non linear

			state_index++;
			key_index++;

			if (state_index >= Traits::NN) {
				state_[0] = state_[Traits::NN-1];
				state_index = 1;
			}
			if (key_index >= keylen) {
				key_index = 0;
			}
		}

		for (loop_index = Traits::NN - 1; loop_index > 0; loop_index--) {
			state_[state_index] = (state_[state_index] ^ ((state_[state_index-1] ^ (state_[state_index-1] >> (Traits::INTTYPE_BITS-2)))
							* Traits::ARRAYINITVAL_2)) - static_cast<size_t>(state_index); // non linear

			state_index++;

			if (state_index >= Traits::NN) {
				state_[0] = state_[Traits::NN-1];
				state_index = 1;
			}
		}
	 
		// MSB is 1; assuring non-zero initial array
		state_[0] = 1U << (Traits::INTTYPE_BITS-1);
		left_ = 1;
	}
      
	// generates a random number on [0,2^INTTYPE_BITS-1]-interval
	size_t generate_uint()
	{
		if (--left_ == 0)
			next_state();
		return Traits::temper(*next_++);
	}

	// generates a random number on [0,2^(INTTYPE_BITS-1)-1]-interval
	int generate_int()
	{
		if (--left_ == 0)
			next_state();
		return static_cast<int>(Traits::temper(*next_++) >> 1);
	}
      
	// generates a random number on [0,1]-real-interval
	double generate_real1()
	{
		if (--left_ == 0)
			next_state();
		return Traits::to_double1(Traits::temper(*next_++));
	}

	// generates a random number on [0,1)-real-interval
	double generate_real2()
	{
		if (--left_ == 0)
			next_state();
		return Traits::to_double2(Traits::temper(*next_++));
	}
      
	// generates a random number on (0,1)-real-interval
	double generate_real3()
	{
		if (--left_ == 0)
			next_state();
		return Traits::to_double3(Traits::temper(*next_++));
	}
};


typedef mt19937<mt32traits> mersenne_twister;
typedef mt19937<mt32traits> mt19937_32;
typedef mt19937<mt64traits> mt19937_64;


class mt19937generator {
private:
	mersenne_twister mt_rand_;
public:
	int operator()(int value)
	{
		return mt_rand_.generate_int() % value;
	}
};


// メルセンヌ・ツイスターでのrandom_shuffle
template <class RandomAccessIterator>
inline void mt_random_shuffle(RandomAccessIterator first, RandomAccessIterator last)
{
    mt19937generator generator;
    std::random_shuffle(first, last, generator);
}



// SFINAEをサポートしているコンパイラか？
#if !defined(_MSC_VER) || (_MSC_VER > 1300)  // 1300 == VC++ 7.0
	#define SHAND_SUPPORT_SFINAE
#endif

#ifdef SHAND_SUPPORT_SFINAE

// SFINAE版mt_random_shuffle
template <class Type, int Size>
inline void mt_random_shuffle(Type (&ar)[Size])
{
	mt_random_shuffle(ar, ar + Size);
}

template <class Container>
inline void mt_random_shuffle(Container& c)
{
	mt_random_shuffle(c.begin(), c.end());
}

#endif // SHAND_SUPPORT_SFINAE

} // namespace shand

#pragma warning(default : 4307)

#undef SHAND_SUPPORT_SFINAE

#endif // SHAND_RANDOM_INCLUDE
