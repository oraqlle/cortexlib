// -*- C++ -*- Header compatibility <matrix.hpp>
/**
 * @file matrix
 * @author Tyler Swann (oraqlle@github.com)
 * @brief Two dimensional array
 * @version 0.0.1
 * @date 2022-16-22
 * 
 * @copyright Copyright (c) 2021
 * 
 */

#ifndef CORTEX_MATRIX_H
#   define CORTEX_MATRIX_H 1

#include <iterators/normal.hpp>
#include <concepts.hpp>

#if __cplusplus >= 201703L

#include <memory>
#include <utility>
#include <iterator>
#include <initializer_list>
#include <cassert>
#include <vector>



namespace cortex
{
    /**
     * @brief Matrix - Two Dimensional Array
     * 
     * @details Matrix is a two dimensional array that 
     * stores elements sequentially in memory but is 
     * viewed as a series of rows and columns. Matrix
     * supports standard mathematical operations as long 
     * as the underlying data type supports them. This is 
     * checked at compile time through the use of concepts.
     * 
     * @todo Add support for iterators
     * @todo Add support for range based for loops
     * @todo Add support for basic arithmatic
     * @todo Add support for matrix operations
     * @todo Add support for operator overloads
     * @todo Add support for std::allocator
     * @todo Add support for std::initializer_list
     * @todo Add support for std::swap
     * @todo Add support for swaps of different matrix types
     * @todo Add support for flatten ✔️
     * @todo Add support for assign
     * @todo Add support for clear ✔️
     * @todo Add support for resize
     * @todo Add support for reserve
     * 
     * @tparam _Tp 
     */
    template<typename _Tp>
    class matrix
    {
    public:
        using value_type                    = _Tp;
        using size_type                     = std::size_t;
        using difference_type               = std::ptrdiff_t;
        using reference                     = _Tp&;
        using const_reference               = const _Tp&;
        using pointer                       = _Tp*;
        using const_pointer                 = const _Tp*;
        using iterator                      = cortex::normal_iterator<pointer, matrix<value_type>>;
        using const_iterator                = cortex::normal_iterator<const_pointer, matrix<value_type>>;
        using reverse_iterator              = std::reverse_iterator<iterator>;
        using const_reverse_iterator        = std::reverse_iterator<const_iterator>;


    protected: 
            size_type m_columns;
            size_type m_rows;

            size_type m_size;
            size_type m_capacity;

            pointer m_data;

    public:

        constexpr matrix()
        : m_columns(size_type())
        , m_rows(size_type())
        , m_size(size_type())
        , m_capacity(size_type())
        , m_data(pointer())
        { }

        constexpr matrix(size_type cols, size_type rows)
        : m_columns(cols)
        , m_rows(rows)
        , m_size(cols * rows != 0 ? cols * rows : std::max(cols, rows))
        , m_capacity(m_size)
        , m_data(_M_allocate(m_size))
        { 
            if constexpr (std::is_default_constructible_v<value_type>)
                std::uninitialized_default_construct_n(m_data, m_size);
            else
                std::uninitialized_fill_n(m_data, m_size, value_type());
        }

        constexpr matrix(size_type cols, size_type rows, const value_type& value)
        : m_columns(cols)
        , m_rows(rows)
        , m_size(cols * rows != 0 ? cols * rows : std::max(cols, rows))
        , m_capacity(m_size)
        , m_data(_M_allocate(m_size))
        { std::uninitialized_fill_n(m_data, m_size, value); }

        constexpr matrix(const matrix& other)
        : m_columns(other.m_columns)
        , m_rows(other.m_rows)
        , m_size(other.m_size)
        , m_capacity(other.m_capacity)
        , m_data(_M_allocate(m_size))
        { std::uninitialized_copy_n(other.m_data, m_size, m_data); }

        constexpr matrix(matrix&& other) noexcept
        : m_columns(other.m_columns)
        , m_rows(other.m_rows)
        , m_size(other.m_size)
        , m_capacity(other.m_capacity)
        , m_data(other.m_data)
        { 
            other.m_data = pointer();
            other.m_columns = size_type();
            other.m_rows = size_type();
            other.m_size = size_type(); 
        }

        constexpr matrix& operator=(const matrix& other)
        {
            m_columns = other.m_columns;
            m_rows = other.m_rows;
            m_size = other.m_size;
            m_capacity = other.m_size;
            m_data = _M_allocate(m_size);
            std::uninitialized_copy_n(other.m_data, m_size, m_data);

            return *this;
        }

        constexpr matrix& operator=(matrix&& other) noexcept
        {
            m_columns = other.m_columns;
            m_rows = other.m_rows;
            m_size = other.m_size;
            m_capacity = other.m_capacity;
            m_data = other.m_data;

            other.m_data = pointer();
            other.m_columns = size_type();
            other.m_rows = size_type();
            other.m_size = size_type();

            return *this;
        }

    #if __cplusplus >= 202202L
        constexpr ~matrix()
    #else
        ~matrix()
    #endif
        {
            if (m_data != pointer())
                std::destroy_n(m_data, m_size);

            
            if (m_data != pointer())
                _M_deallocate(m_data, m_size);

            m_columns = size_type();
            m_rows = size_type();
            m_size = size_type();
            m_capacity = size_type();
        }


        /**
         * @brief Swaps two matrices
         * 
         * @todo Implement swap for different types
         * which requires utilising std::allocator.
         * 
         * @param other 
         */
        void swap(matrix& other) noexcept
        {
            matrix tmp = other;
            other = *this;
            *this = tmp;
        }

        constexpr size_type size() const noexcept
        { return m_size; }

        constexpr size_type row_size() const noexcept
        { return m_rows; } 

        constexpr size_type column_size() const noexcept
        { return m_columns; }

        constexpr size_type max_size() const noexcept
        { return m_size; }

        constexpr size_type capacity() const noexcept
        { return m_capacity; }

        constexpr auto dimensions() const noexcept
        { return std::tie(m_columns, m_rows); }

        constexpr bool is_square() const noexcept
        { return m_columns == m_rows; }

        constexpr bool empty() const noexcept
        { return m_size == 0; }

        constexpr pointer data() const noexcept
        { return m_data; }

        /**
         * @brief 
         * 
         * @todo Change to be the access of two dimensions
         * 
         * @param index 
         * @return constexpr reference 
         */
        constexpr reference operator[](size_type index) 
        { return *(m_data + index); }

        constexpr reference at(size_type column, size_type row)
        { 
            _M_range_check(column, row);
            return *(m_data + (m_columns * row) + column);
        }

        constexpr const_reference at(size_type column, size_type row) const
        { 
            _M_range_check(column, row);
            return *(m_data + (m_columns * row) + column); 
        }

        constexpr reference front() noexcept
        { return *m_data; }

        constexpr const_reference front() const noexcept
        { return *m_data; }

        constexpr reference back() noexcept
        { return *(m_data + m_size - 1); }

        constexpr const_reference back() const noexcept
        { return *(m_data + m_size - 1); }

        constexpr std::vector<value_type> flatten() noexcept
        {
            std::vector<value_type> vec(m_size);
            std::copy_n(m_data, m_size, vec.begin());
            return vec;
        }

        constexpr iterator begin() noexcept
        { return iterator(m_data); }

        constexpr const_iterator begin() const noexcept
        { return const_iterator(m_data); }

        constexpr const_iterator cbegin() const noexcept
        { return const_iterator(m_data); }

        constexpr reverse_iterator rbegin() noexcept
        { return reverse_iterator(end()); }

        constexpr const_reverse_iterator rbegin() const noexcept
        { return const_reverse_iterator(end()); }

        constexpr const_reverse_iterator crbegin() const noexcept
        { return const_reverse_iterator(end()); }

        constexpr iterator end() noexcept
        { return iterator(m_data + m_size); }

        constexpr const_iterator end() const noexcept
        { return const_iterator(m_data + m_size); }

        constexpr const_iterator cend() const noexcept
        { return const_iterator(m_data + m_size); }

        constexpr reverse_iterator rend() noexcept
        { return reverse_iterator(begin()); }

        constexpr const_reverse_iterator rend() const noexcept
        { return const_reverse_iterator(begin()); }

        constexpr const_reverse_iterator crend() const noexcept
        { return const_reverse_iterator(begin()); }

        constexpr void clear() noexcept
        {
            if (auto __n { (m_data + m_size) - m_data })
            {
                std::destroy_n(m_data, m_size);
            
                m_size = size_type();
                m_columns = size_type();
                m_rows = size_type();   
            }         
        }

    private:

        constexpr pointer _M_allocate(size_type __n)
        { return __n != 0 ? static_cast<pointer>(::operator new(__n * sizeof(value_type))) : pointer(); }

        constexpr void _M_deallocate(pointer __p, [[maybe_unused]] size_type __n)
        { ::operator delete(__p); }

        constexpr void _M_range_check(size_type __column, size_type __row) const
        {
            if (__column >= this->column_size() || __row >= this->row_size())
                throw std::out_of_range("matrix::_M_range_check - index out of range.");
        }
    };
} // namespace cortex

#endif // __cplusplus >= 201703L

#endif // CORTEX_MATRIX_H