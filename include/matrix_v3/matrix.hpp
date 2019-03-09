#ifndef MATRIX_HPP
#define MATRIX_HPP

#include "dynamic_engine.hpp"
#include "static_engine.hpp"
#include "shape.hpp"
#include "operations.hpp"
#include <cassert>

namespace sm_v3{
    template<typename Engine_t,typename MatrixType, typename OperationPolicy>
    struct Matrix : public BaseExpression<Matrix<Engine_t,MatrixType, OperationPolicy >>,
        public MatrixType{
        
        using Type = typename MatrixType::value_type;
        using MatrixType::m_data;

        Matrix():MatrixType(Engine_t()){}
    
        Matrix(Matrix const& other):MatrixType(static_cast<MatrixType const&>(other)){}
        Matrix(Matrix && other):MatrixType(std::move(static_cast<MatrixType &&>(other))){}
        
        Matrix& operator=(Matrix const& other){
            auto temp = Matrix(other);
            MatrixType::swap(temp);
            return *this;
        }
        Matrix& operator=(Matrix && other){
            auto temp = Matrix(std::move(other));
            MatrixType::swap(temp);
            return *this;
        }
        
        Matrix(typename MatrixType::size_type rows, 
            typename MatrixType::size_type cols):MatrixType(Engine_t(rows, cols)){}
        
        Matrix(typename MatrixType::storage_type const& other, 
            typename MatrixType::size_type rows,
            typename MatrixType::size_type cols):MatrixType(other,Engine_t(rows, cols)){}
        
        Matrix(typename MatrixType::storage_type const& other):MatrixType(other, Engine_t()){}

        // Matrix(typename EnginePolicy::reference other,
        //     typename EnginePolicy::size_type rows, 
        //     typename EnginePolicy::size_type cols):EnginePolicy(other, rows, cols){}
        
        // Matrix(typename EnginePolicy::const_reference other,
        //     typename EnginePolicy::size_type rows, 
        //     typename EnginePolicy::size_type cols):EnginePolicy(other, rows, cols){}

        template<typename Expression>
        Matrix(BaseExpression<Expression> const& m):Matrix(m.self().rows(),m.self().cols()){
            Expression const& temp = m.self();
            for(auto i = 0 ; i < MatrixType::rows() ; i++){
                for(auto j = 0 ; j < MatrixType::cols() ; j++){
                    MatrixType::set_element(temp(i,j),i,j);
                }
            }
        }

        template<
        typename Operation, 
        typename Op1, 
        typename Op2>
        Matrix(BinaryExpression< Operation , Op1, Op2 >  const& m):Matrix(m.rows(),m.cols()){
            for(auto i = 0; i < m.rows(); i++){
                for(auto j = 0; j < m.cols(); j++){
                    MatrixType::set_element(m(i,j),i,j);
                }
            }
        }

        template<typename Expression>
        constexpr Matrix& operator=(BaseExpression<Expression> const &rhs){
            auto temp = Matrix(rhs);
            MatrixType::swap(temp);
            return *this;
        }

        /**
         * Operator+= Overloading
         * for addtion of two matrices
         * and assigns them
         * @return Matrix
         */
        template<typename Expression>
        constexpr Matrix& operator+=(BaseExpression<Expression> const &rhs){
            auto temp = Matrix(*this + rhs);
            MatrixType::swap(temp);
            return *this;
        }
    
        /**
         * Operator-= Overloading
         * for subtraction of two matrices
         * and assigns them
         * @return Matrix
         */
        template<typename Expression>
        constexpr Matrix& operator-=(BaseExpression<Expression> const &rhs){
            auto temp = Matrix(*this - rhs);
            MatrixType::swap(temp);
            return *this;
        }
        /**
         * Operator*= Overloading
         * for multipication of two matrices
         * and assigns them
         * @return Matrix
         */
        template<typename Expression>
        constexpr Matrix& operator*=(BaseExpression<Expression> const &rhs){
            auto temp = Matrix(*this * rhs);
            MatrixType::swap(temp);
            return *this;
        }
    
        /**
         * Operator== Overloading
         * for comparision of two matrices
         * @return bool true if they are equal
         * otherwise false
         */
        template<typename Expression>
        constexpr bool operator==(BaseExpression<Expression> const &rhs){
            Expression const& n_rhs = rhs.self();
            if(MatrixType::cols() != n_rhs.cols() && MatrixType::rows() != n_rhs.rows()
                && m_data.size() != n_rhs.size()) return false;
            for(auto i = 0; i < n_rhs.rows(); i++){
                for(auto j = 0; j < n_rhs.cols(); j++){
                    if( MatrixType::operator()(i,j) != n_rhs(i,j) ) return false;
                }
            }
            return true;
        }

        template<typename Expression>
        constexpr friend auto &operator<<(std::ostream &os, BaseExpression<Expression> const &m){
            Expression const& temp = m.self();
            os<<'['<<' '<<'\n';
            for(size_t i = 0; i < temp.rows(); i++){
                os<<' '<<'('<<' ';
                for (size_t j = 0; j < temp.cols(); j++){
                    os << temp(i,j)<<',';
                    if(j != temp.cols() - 1){
                        os<<' ';
                    }
                }
                os<<')'<<','<<'\n';
            }
            os<<']'<<'\n';
            return os;
        }
    
        /**
         * Operator!= Overloading
         * for comparision of two matrices
         * @return bool true if they are not equal
         * otherwise false
         */
        template<typename Expression>
        constexpr bool operator!=(BaseExpression<Expression> const &rhs){
            return !(*this == rhs);
        }

        ~Matrix() = default;

    };

    template<typename T>
    using DMatrix = Matrix<DyanmicEngine,Dense<T>,Operation_Add_Sub_Mul>;

    template<typename T, size_t rows, size_t cols>
    using SMatrix = Matrix<StaticEngine<rows,cols>,Dense<T>,Operation_Add_Sub_Mul>;

    template<typename T>
    using DMatrix_S = Matrix<DyanmicEngine,Sparse<T>,Operation_Add_Sub_Mul>;

    template<typename T, size_t rows, size_t cols>
    using SMatrix_S = Matrix<StaticEngine<rows,cols>,Sparse<T>,Operation_Add_Sub_Mul>;

}

#endif // MATRIX_HPP
