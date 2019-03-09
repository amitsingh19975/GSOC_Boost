#ifndef SHAPE_HPP
#define SHAPE_HPP

#include <iostream>
#include <algorithm>
#include <unordered_map>
#include "storage.hpp"

namespace sm_v3{
    
    template<typename StoragePolicy>
    struct SparseType{
        
        using storage_type    = typename StoragePolicy::storage_type;
        using size_type       = typename StoragePolicy::size_type;
        using value_type      = typename StoragePolicy::value_type;

        SparseType() = default;
        
        SparseType(SparseType const& other):m_data(other.m_data),m_rows(other.m_rows),m_cols(other.m_cols){}
        SparseType(SparseType&& other):m_data(std::move(other.m_data)),
            m_rows(std::move(other.m_rows)),m_cols(std::move(other.m_cols)){}
        
        template<typename Engine_t>
        SparseType(Engine_t dimension):m_data(dimension.rows() * dimension.cols()),
            m_rows(dimension.rows()),m_cols(dimension.cols()){}
        
        template<typename Engine_t>
        SparseType(storage_type& mat, Engine_t dimension):m_data(mat),
            m_rows(dimension.rows()),m_cols(dimension.cols()){
        }

        auto uncompress() const{
            auto rows = this->m_rows;
            auto get_idx = [rows](auto i, auto j){
                return j * rows + i;
            };
            std::vector<value_type> temp(m_rows * m_cols);
            for(auto i = 0u; i < m_rows; i++){
                for(auto j = 0u; j < m_cols; j++){
                    if(auto it = m_data.find(get_idx(i,j)); it != m_data.end()){
                        temp[get_idx(i,j)] = it->second; 
                    }else{
                        temp[get_idx(i,j)] = 0;
                    }
                }
            }
            return temp;
        }

        constexpr auto compress(storage_type const& m){
            auto rows = this->m_rows;
            auto get_idx = [rows](auto i, auto j){
                return j * rows + i;
            };
            for(auto i = 0u; i < m_rows; i++){
                for(auto j = 0u; j < m_cols; j++){
                    if(m[get_idx(i,j)] != 0){
                        m_data[get_idx(i,j)] = m[get_idx(i,j)]; 
                    }
                }
            }
        }

        constexpr auto operator()(size_t i, size_t j) const{
            assert(i < m_rows && j < m_cols);
            if(auto it = m_data.find(j * m_rows + i); it != m_data.end())
                return it->second;
            else
                return value_type{0};
        }

        constexpr auto set_element(value_type val, size_t i, size_t j){
            assert(i < m_rows && j < m_cols);
            if(val != value_type{0}){
                m_data[j * m_rows + i] = val;
            }else{
                if(auto it = m_data.find(j * m_rows + i); it != m_data.end()){
                    m_data.erase(it);
                }
            }

        }

        constexpr SparseType& operator=(SparseType const& other){
            auto temp = SparseType(other);
            swap(other);
            return *this;
        }

        constexpr SparseType& operator=(SparseType&& other){
            auto temp = SparseType(std::move(other));
            swap(other);
            return *this;
        }

        constexpr friend auto &operator<<(std::ostream &os, SparseType const &m){
            auto rows = m.m_rows;
            auto get_idx = [rows](auto i, auto j){
                return j * rows + i;
            };
            os<<'['<<' '<<'\n';
            for(size_t i = 0; i < m.rows(); i++){
                os<<' '<<'('<<' ';
                for (size_t j = 0; j < m.cols(); j++){
                    if(auto it = m.m_data.find(get_idx(i,j)); it != m.m_data.end()){
                        os << it->second <<',';
                    }else{
                        os<<0<<',';
                    }
                    if(j != m.cols() - 1){
                        os<<' ';
                    }
                }
                os<<')'<<','<<'\n';
            }
            os<<']'<<'\n';
            return os;
        }

        constexpr auto rows() const noexcept{
            return m_rows;
        }

        constexpr auto cols() const noexcept{
            return m_cols;
        }

        constexpr auto size() const noexcept{
            return m_data.size();
        }

        void swap(SparseType& other){
            std::swap(other.m_data,m_data);
            std::swap(other.m_cols,m_cols);
            std::swap(other.m_rows,m_rows);
        }

        ~SparseType() = default;

    protected:
        std::unordered_map<size_t,value_type>  m_data;
        size_type                       m_rows;
        size_type                       m_cols;
    };
    
    template<typename StoragePolicy>
    struct DenseType{
        
        using storage_type    = typename StoragePolicy::storage_type;
        using size_type       = typename StoragePolicy::size_type;
        using difference_type = typename StoragePolicy::difference_type;
        using value_type      = typename StoragePolicy::value_type;

        DenseType() = default;
        
        DenseType(DenseType const& other):m_data(other.m_data),m_rows(other.m_rows),m_cols(other.m_cols){}
        
        DenseType(DenseType&& other):m_data(std::move(other.m_data)),
            m_rows(std::move(other.m_rows)),m_cols(std::move(other.m_cols)){}
        
        template<typename Engine_t>
        DenseType(Engine_t dimension):m_data(dimension.rows() * dimension.cols()),
            m_rows(dimension.rows()),m_cols(dimension.cols()){}
        
        template<typename Engine_t>
        DenseType(storage_type const& mat, Engine_t dimension):m_data(mat),
            m_rows(dimension.rows()),m_cols(dimension.cols()){
        }

        constexpr DenseType& operator=(DenseType const& other){
            auto temp = DenseType(other);
            swap(other);
            return *this;
        }

        constexpr DenseType& operator=(DenseType&& other){
            auto temp = DenseType(std::move(other));
            swap(other);
            return *this;
        }

        constexpr auto operator()(size_t i, size_t j) const{
            assert(i < m_rows && j < m_cols);
            return m_data[ j * m_rows + i];
        }

        constexpr auto& operator()(size_t i, size_t j){
            assert(i < m_rows && j < m_cols);
            return m_data[ j * m_rows + i];
        }


        constexpr auto set_element(value_type &val, size_t i, size_t j){
            assert(i < m_rows && j < m_cols);
            this->operator()(i,j) = val;
        }

        constexpr auto set_element(value_type val, size_t i, size_t j){
            assert(i < m_rows && j < m_cols);
            this->operator()(i,j) = val;
        }

        constexpr auto rows() const noexcept{
            return m_rows;
        }

        constexpr auto cols() const noexcept{
            return m_cols;
        }

        constexpr auto size() const noexcept{
            return m_data.size();
        }

        constexpr friend auto &operator<<(std::ostream &os, DenseType const &m){
            os<<'['<<' '<<'\n';
            for(size_t i = 0; i < m.rows(); i++){
                os<<' '<<'('<<' ';
                for (size_t j = 0; j < m.cols(); j++){
                    os << m(i,j)<<',';
                    if(j != m.cols() - 1){
                        os<<' ';
                    }
                }
                os<<')'<<','<<'\n';
            }
            os<<']'<<'\n';
            return os;
        }

        void swap(DenseType& other){
            std::swap(other.m_data,m_data);
            std::swap(other.m_cols,m_cols);
            std::swap(other.m_rows,m_rows);
        }

        ~DenseType() = default;

    protected:
        storage_type                    m_data;
        size_type                       m_rows;
        size_type                       m_cols;
    };

    template<typename StoragePolicy>
    using BandType = SparseType<StoragePolicy>;

    template<typename T>
    using Dense = DenseType<Storage<std::vector<T>>>;

    template<typename T>
    using Sparse = SparseType<Storage<std::vector<T>>>;

    template<typename T>
    using Band = BandType<Storage<std::vector<T>>>;
}


#endif // SHAPE_HPP
