#include <random>
#include <ctime>
namespace bleh::Random
{
	inline std::mt19937_64 generator(std::random_device{}());
	inline uint64_t RandomInt64()
	{
		return generator();
	}
}