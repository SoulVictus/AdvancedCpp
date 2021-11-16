#include <vector>
#include <iostream>
#include <string>

template <class T, std::size_t N>
class Wektor {
    private:
        T* array;

    public:
        using value_type = T;
        Wektor() {
            array = new T[N];
            for (std::size_t i = 0; i < N; i++)
            {
                array[i] = 0;
            }
        }

        ~Wektor()
        {
            delete [] array;
        }

        std::size_t size() const
        {
            return N;
        }

        value_type& operator[](std::size_t i)
        {
            return array[i];
        }

        value_type const & operator[](std::size_t i) const
        {
            return array[i];
        }

        template<typename U>
        auto operator*(U const& other) const
        {
            auto sum = 0.0;
            try {
                if (this->size() == 0 || other.size() == 0)
                    throw "Array size is equal zero";
                if (this->size() != other.size())
                    throw "Arrays size must be equal";
                
                for (std::size_t i = 0; i < this->size(); i++)
                {
                    sum += array[i] * other[i];
                }
            }
            catch (char const* err) {
                std::cout << err << "\n";
                return value_type(-1);
            }

            return sum;
        }
};

int main()
{
    Wektor<int, 10> vec1;
    vec1[5] = 3;
    vec1[6] = 1;

    Wektor<double, 10> vec2;
    vec2[6] = 2.5;
    vec2[5] = 7.8;

    std::vector<int> vec3 {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};

    const Wektor<double, 8> vec4;
    const Wektor<double, 0> vec5;

    std::cout << "vec1 [5] = " << vec1[5] << "\n";
    std::cout << "vec2 [5] = " << vec2[5] << "\n";
    std::cout << "result = " << vec2 * vec1 << "\n";
    std::cout << "result2 = " << vec2 * vec3 << "\n";

    std::cout << vec4 * vec2 << "\n";
    std::cout << vec5 * vec4 << "\n";

    return 0;
}