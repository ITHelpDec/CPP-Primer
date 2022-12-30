// Exercise 18.14:
/*
 Suppose we have the following declaration of the operator* that is
 a member of the nested namespace mathLib::MatrixLib:
 
 How would you declare this operator in global scope?
 
 >> This is a great opportunity to benchmark loop interchanging
 >> Surprisingly, there were no differences on my machine!
 
*/

#ifndef non_inter_hpp
#define non_inter_hpp

namespace non_interloop {
namespace mathLib {
namespace MatrixLib {
class matrix {
public:
    matrix() = default;
    
    matrix(std::size_t rows, std::size_t cols) {
        matrix_.resize(rows, std::vector<int>(cols));
    }
    
    void generate() {
        for (auto &vec : matrix_)
            std::generate(vec.begin(), vec.end(), [this] () { return gen(); } );
    }
    
    const std::size_t size() const { return matrix_.size(); }
    std::size_t size() { return matrix_.size(); }
    
    std::vector<int>& operator[](std::size_t i) { return matrix_[i]; }
    const std::vector<int>& operator[](std::size_t i) const { return matrix_[i]; }
    
    void print() {
        for (const auto &v : matrix_) {
            for (const auto &e : v) {
                std::cout << e << " ";
            } std::cout << std::endl;
        } std::cout << std::endl;
    }
    
private:
    std::vector<std::vector<int>> matrix_;
    
    std::size_t gen() {
        static std::default_random_engine e;
        static std::uniform_int_distribution u(1, 9);
        return u(e);
    }
};
}
}

using mathLib::MatrixLib::matrix;

matrix operator*(const matrix &lhs, const matrix &rhs)
{
    std::size_t n = lhs.size();
    
    matrix answer(n, n);
    for (std::size_t i = 0; i != n; ++i) {
        for (std::size_t j = 0; j != n; ++j) {
            for (std::size_t k = 0; k != n; ++k) {
                answer[i][j] += lhs[i][k] * rhs[k][j];
            }
        }
    }
    
    return answer;
}
}

#endif /* non_inter_hpp */
