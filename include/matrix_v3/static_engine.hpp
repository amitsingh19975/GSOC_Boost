#ifndef STATIC_ENGINE_HPP
#define STATIC_ENGINE_HPP

#include "storage.hpp"
#include <iostream>

namespace sm_v3{
    template<size_t matrix_rows, size_t matrix_cols>
    struct StaticEngine{

        StaticEngine() = default;

        StaticEngine(size_t rows, size_t cols):m_rows(matrix_rows),m_cols(matrix_cols){}

        constexpr auto rows() const noexcept{
            return m_rows;
        }

        constexpr auto cols() const noexcept{
            return m_rows;
        }

    private:
        size_t const m_rows{matrix_rows};
        size_t const m_cols{matrix_cols};
    };
}



#endif // STATIC_ENGINE_HPP
