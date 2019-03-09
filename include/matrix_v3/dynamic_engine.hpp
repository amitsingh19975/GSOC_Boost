#ifndef DYNAMIC_ENGINE_HPP
#define DYNAMIC_ENGINE_HPP

#include "storage.hpp"
#include <iostream>

namespace sm_v3{
    struct DyanmicEngine{

        DyanmicEngine() = default;

        DyanmicEngine(size_t rows, size_t cols):m_rows(rows),m_cols(cols){}

        constexpr auto rows() const noexcept{
            return m_rows;
        }

        constexpr auto cols() const noexcept{
            return m_rows;
        }

    private:
        size_t m_rows;
        size_t m_cols;
    };
}

#endif // DYNAMIC_ENGINE_HPP
