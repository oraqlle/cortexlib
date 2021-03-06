// -*- C++ -*- Header compatibility <normal.hpp>

/// \brief Adapts a non-object iterator to an object iterator 
/// without changing its semantics.
///
/// Author: Tyler Swann (oraqlle@github.com)
/// 
/// Header Version: v1.1.0
///
/// Date: 25-06-2022
///
/// License: MIT
///
/// Copyright: Copyright (c) 2022
/// \file normal.hpp

#ifndef CORTEX_NORMAL_ITERATOR_HPP
#   define CORTEX_NORMAL_ITERATOR_HPP 


#include <utility>
#include <type_traits>
#include <iterator>

#if __cpp_lib_three_way_comparison
#   include <compare>
#endif /// __cpp_lib_three_way_comparison

#if __cpp_concepts >= 201907L
#   include <concepts>
#endif /// __cpp_concepts >= 201907L


#   if __cplusplus >= 201402L

namespace cortex
{    
    
    /// \brief Normal Iterator
    /// 
    /// \details This iterator is used to adapt non-iterator 
    /// objects into objects (ie. pointers). %normal_iterator 
    /// does not change the semantics of the operators of the
    /// underlying iterator of type _Iterator.
    /// 
    /// 
    /// \tparam _Iterator The underlying type of the iterator.
    /// \tparam _Container Allows classes to create different types of iterators even if the _Iterator type is the same.
    template<typename _Iterator, typename _Container>
    class normal_iterator
    {
    protected:
        _Iterator m_current;

        using __traits_type                     = std::iterator_traits<_Iterator>;

    public:
        using iterator_type                     = _Iterator;
        using iterator_category                 = typename __traits_type::iterator_category;

#if __cpp_concepts >= 201907L
        using iterator_concept                  = std::random_access_iterator_tag;
#endif /// __cpp_concepts >= 201907L

        using value_type                        = typename __traits_type::value_type;
        using difference_type                   = typename __traits_type::difference_type;
        using pointer                           = typename __traits_type::pointer;
        using reference                         = typename __traits_type::reference;



        
        /// \brief Default Constructor
        /// 
        /// \details Initialises m_current to the default value of 
        /// the type _Iterator. 
        /// 
        /// [constexpr]
        /// [noexcept] 
        constexpr normal_iterator() noexcept
        : m_current(_Iterator()) { }



        
        /// \brief Copy Constructor.
        /// 
        /// \details Uses copy semantics to initialise m_current from
        /// another %normal_iterator object. Uses the \code {.cpp}
        /// %normal_iterator::base()
        /// \endcode
        /// method to access __other's underlying iterator. 
        /// 
        /// \param __other const reference to a %normal_iterator object.
        /// 
        /// [constexpr]
        /// [noexcept]
        constexpr normal_iterator(const normal_iterator& __other) noexcept
        : m_current(__other.base()) { }



        
        /// \brief Copy Constructor. 
        /// 
        /// \details Uses copy semantics to initialise m_current from
        /// an object as the same type as iterator_type. Because the 
        /// the underlying types must be the same, m_current can be 
        /// directly initialised from __other.
        /// 
        /// \param __other const reference to an object of type iterator_type.
        /// 
        /// [constexpr]
        /// [noexcept]
        constexpr normal_iterator(const iterator_type& __other) noexcept
        : m_current(__other) { }
        


        
        /// \brief Move Constructor.
        /// 
        /// \details Deletes the default move constructor that the 
        /// compiler might generate that would move the \code {.cpp}
        /// %normal_iterator::m_current
        /// \endcode from another %normal_iterator.
        /// 
        /// \param __other rvalue reference to a %normal_iterator object.
        /// 
        /// [constexpr]
        /// [deleted.constructor] 
        
        /// constexpr normal_iterator(normal_iterator&& __other) noexcept = delete;



        
        /// \brief Move Constructor.
        /// 
        /// \details Deletes the default move constructor that the 
        /// compiler might generate that would move __other from its 
        /// source.
        /// 
        /// \param __other rvalue reference to an object of type iterator_type.
        /// 
        /// [constexpr]
        /// [deleted.constructor] 
        
        /// constexpr normal_iterator(iterator_type&& __other) noexcept = delete;
        


        
        /// \notes No explicit destructor is required.
        



        
        /// \brief Copy Assignment.
        /// 
        /// \details Uses copy semantics to assign m_current to the
        /// underlying iterator of __other. Uses the \code {.cpp}
        /// %normal_iterator::base()
        /// \endcode
        /// method to access __other's underlying iterator.
        /// Returns a reference to this.
        /// 
        /// \param __other
        /// \returns constexpr normal_iterator&
        /// 
        /// [constexpr]
        /// [noexcept]
        /// [operator.assigment]
        constexpr normal_iterator& operator= (const normal_iterator& __other) noexcept
        { 
            m_current = __other.base(); 
            return *this;
        }



        
        /// \brief Copy Assignment.
        /// 
        /// \details Uses copy semantics to assign m_current to 
        /// __other. __other must be of type iterator_type.
        /// Returns a reference to this.
        /// 
        /// \param __other
        /// \returns constexpr normal_iterator&
        /// 
        /// [constexpr]
        /// [noexcept]
        /// [operator.assigment]
        constexpr normal_iterator& operator= (const iterator_type& __other) noexcept
        {
            m_current = __other; 
            return *this;
        }

        
        /// \brief Dereference Operator Overload. 
        /// 
        /// \details Dereferences m_current and returns a 
        /// reference of the value to the caller.
        /// 
        /// \returns constexpr reference (T&)
        /// 
        /// [constexpr]
        /// [noexcept]
        constexpr reference operator* () noexcept
        { return *m_current; }


        
        /// \brief Dereference Operator Overload. 
        /// 
        /// \details Dereferences m_current and returns a 
        /// reference of the value to the caller.
        /// 
        /// \returns constexpr reference (T&)
        /// 
        /// [constexpr]
        /// [noexcept]
        /// [trailing.const]
        constexpr reference operator* () const noexcept
        { return *m_current; }


        
        /// \brief Arrow Deference Operator Overload. 
        /// 
        /// \details Returns a pointer of m_current, this
        /// allows for access to the internal members if
        /// m_current is a class or object type throught
        /// "indirection chaining".
        /// 
        /// \returns constexpr pointer (T*)
        /// 
        /// [constexpr]
        /// [noexcept]
        constexpr pointer operator-> () noexcept
#   if __cplusplus > 201703L && __cpp_concepts >= 201907L
            requires std::is_pointer_v<iterator_type>
	     || requires(const iterator_type __i) { __i.operator->(); }
#   endif
        { return _S_to_pointer(m_current); }

        
        /// \brief Arrow Deference Operator Overload. 
        /// 
        /// \details Returns a pointer of m_current, this
        /// allows for access to the internal members if
        /// m_current is a class or object type throught
        /// "indirection chaining".
        /// 
        /// \returns constexpr pointer (T*)
        /// 
        /// [constexpr]
        /// [noexcept]
        /// [trailing.const]
        constexpr pointer operator-> () const noexcept
#   if __cplusplus > 201703L && __cpp_concepts >= 201907L
            requires std::is_pointer_v<iterator_type>
	     || requires(const iterator_type __i) { __i.operator->(); }
#   endif
        { return _S_to_pointer(m_current); }


        
        /// \brief Prefix Increment Operator Overload.
        /// 
        /// \details Applies the prefix increment operator to
        /// m_current and returns a reference to this.
        /// 
        /// \returns constexpr normal_iterator&
        /// 
        /// [constexpr]
        /// [noexcept]
        constexpr normal_iterator& operator++ () noexcept
        {
            ++m_current; 
            return *this;
        }


        
        /// \brief Postfix Increment Operator Overload.
        /// 
        /// \details Constructs a new iterator from m_current
        /// while applying the postifix increment operator on
        /// Construction. This effectively increments m_current 
        /// for this while creating a new iterator with its 
        /// m_current equal to the last value of this m_current. 
        /// 
        /// \returns constexpr normal_iterator
        /// 
        /// [constexpr]
        /// [noexcept] 
        constexpr normal_iterator operator++ (int) noexcept
        { return normal_iterator(m_current++); }


        
        /// \brief Prefix Decrement Operator Overload.
        /// 
        /// \details Applies the prefix decrement operator to
        /// m_current and returns a reference to this.
        /// 
        /// \returns constexpr normal_iterator&
        /// 
        /// [constexpr]
        /// [noexcept]
        constexpr normal_iterator& operator-- () noexcept
        {
            --m_current;
            return *this;
        }


        
        /// \brief Postfix Decrement Operator Overload.
        /// 
        /// \details Constructs a new iterator from m_current
        /// while applying the postifix decrement operator on
        /// construction. This effectively decrements m_current 
        /// for this while creating a new iterator with its 
        /// m_current equal to the last value of this m_current. 
        /// 
        /// \returns constexpr normal_iterator
        /// 
        /// [constexpr]
        /// [noexcept] 
        constexpr normal_iterator operator-- (int) noexcept
        { return normal_iterator(m_current--); }


        
        /// \brief Subscript Operator Overload.
        /// 
        /// \details Accesses the element at an offset to m_current's
        /// location in memory and returns a reference to the value
        /// stored at that location.
        /// 
        /// \param __n 
        /// \returns constexpr reference (T&)
        /// 
        /// [constexpr]
        /// [noexcept]
        /// ![range.validation]
        constexpr reference operator[] (difference_type __n) noexcept
        { return m_current[__n]; }


        
        /// \brief Additive Assignment Operator Overload. 
        ///
        /// \details Increases the m_current's pointer value by 
        /// __step and assigns m_current the new pointer value 
        /// and returns a reference to this. 
        /// 
        /// \param __step 
        /// \returns constexpr normal_iterator&
        /// 
        /// [constexpr]
        /// [noexcept]
        constexpr normal_iterator& operator+= (difference_type __step) noexcept
        {
            m_current += __step;
            return *this;
        }


        
        /// \brief Subtraction Assignment Operator Overload. 
        ///
        /// \details Decreases the m_current's pointer value by 
        /// __step and assigns m_current the new pointer value 
        /// and returns a reference to this. 
        /// 
        /// \param __step 
        /// \returns constexpr normal_iterator&
        /// 
        /// [constexpr]
        /// [noexcept]
        constexpr normal_iterator& operator-= (difference_type __step) noexcept
        {
            m_current -= __step;
            return *this;
        }


        
        /// \brief Addition Operator Overload.
        /// 
        /// \details Constructs a new iterator from the addition 
        /// of m_current and __step. 
        /// 
        /// \param __step 
        /// \returns constexpr normal_iterator 
        /// 
        /// [constexpr]
        /// [noexcept] 
        constexpr normal_iterator operator+ (difference_type __step) const noexcept
        { return normal_iterator(m_current + __step); }


        
        /// \brief Subtraction Operator Overload.
        /// 
        /// \details Constructs a new iterator from the subtraction 
        /// of m_current and __step. 
        /// 
        /// \param __step 
        /// \returns constexpr normal_iterator 
        /// 
        /// [constexpr]
        /// [noexcept] 
        constexpr normal_iterator operator- (difference_type __step) const noexcept
        { return normal_iterator(m_current - __step); }


        
        /// \brief Base Member Access. 
        /// 
        /// \details Returns a raw copy of m_current.
        /// 
        /// \returns constexpr iterator_type (_Iterator)
        /// 
        /// [constexpr]
        /// [noexcept]
        /// [trailing.const]
        
        constexpr const iterator_type& base() const noexcept
        { return m_current; }

    private:

        template<typename _Tp>
	    static constexpr _Tp*
	    _S_to_pointer(_Tp* __p)
        { return __p; }

        template<typename _Tp>
        static constexpr pointer
	    _S_to_pointer(_Tp __t)
        { return __t.operator->(); }

    }; /// class normal_iterator


#if __cpp_lib_three_way_comparison /// C++20

    
    /// \brief Equality Operator Overload.
    /// 
    /// \details Performs an equality comparison of two 
    /// %normal_iterator's whose _Iterator types can be 
    /// different but of they share the same _Container 
    /// type. 
    /// 
    /// \requires 
    /// That the underlying _Iterator types are equality comparable.
    /// \code {.cpp}
    /// { __lhsI == __rhsI } -> bool
    /// \endcode
    /// 
    /// \exception 
    /// Ensures that __lhs.base() == __rhs.base() is noexcept.
    /// 
    /// \notes _IteratorL can equal _IteratorR.
    /// 
    /// \tparam _IteratorL 
    /// \tparam _IteratorR 
    /// \tparam _Container 
    /// \param __lhs 
    /// \param __rhs 
    /// \returns constexpr true
    /// \returns constexpr false
    /// 
    /// [constexpr]
    /// [noexcept.noexcept-clause]
    
    template<typename _IteratorL, typename _IteratorR, typename _Container>
        requires requires (_IteratorL __lhsI, _IteratorR __rhsI)
        { { __lhsI == __rhsI } -> std::convertible_to<bool>; }
    constexpr bool 
    operator== (const normal_iterator<_IteratorL, _Container>& __lhs, 
                    const normal_iterator<_IteratorR, _Container>& __rhs) 
        noexcept (noexcept(__lhs.base() == __rhs.base()))
    { return __lhs.base() == __rhs.base(); }



    
    /// \brief Spaceship Operator Overload.
    /// 
    /// \details Performs a 3-way comparison of two 
    /// %normal_iterator's whose _Iterator types can be 
    /// different but of they share the same _Container 
    /// type. 
    /// 
    /// \exception \code {.cpp}
    /// code noexcept (noexcept(__lhs.base() <=> __rhs.base()))
    /// \endcode
    /// Ensures that the 3-way comparison of __lhs.base() and 
    /// __rhs.base() is noexcept.
    /// 
    /// \notes _IteratorL can equal _IteratorR.
    /// 
    /// \tparam _IteratorL 
    /// \tparam _IteratorR 
    /// \tparam _Container 
    /// \param __lhs 
    /// \param __rhs 
    /// \returns constexpr auto of [std::strong_ordering]
    ///                         : [std::weak_ordering]
    ///                         : [std::partial_ordering]
    /// 
    /// [constexpr]
    /// [noexcept.noexcept-clause]
    
    template<typename _IteratorL, typename _IteratorR, typename _Container>
    constexpr auto
    operator<=> (const normal_iterator<_IteratorL, _Container>& __lhs, 
                 const normal_iterator<_IteratorR, _Container>& __rhs)
        noexcept (noexcept(__lhs.base() <=> __rhs.base()))
    { return std::compare_three_way{}(__lhs.base(), __rhs.base()); }


#else /// ! C++20


    
    /// \brief Equality Operator Overload.
    /// 
    /// \details Performs an equality comparison of two 
    /// %normal_iterator's whose _Iterator types can be
    /// different but of they share the same _Container
    /// type. 
    /// 
    /// \tparam _IteratorL 
    /// \tparam _IteratorR 
    /// \tparam _Container 
    /// \param __lhs 
    /// \param __rhs 
    /// \returns constexpr inline true
    /// \returns constexpr inline false
    /// 
    /// [constexpr]
    /// [noexcept]
    
    template<typename _IteratorL, typename _IteratorR, typename _Container>
    constexpr inline bool
    operator== (const normal_iterator<_IteratorL, _Container>& __lhs, 
                const normal_iterator<_IteratorR, _Container>& __rhs)
        noexcept
    { return __lhs.base() == __rhs.base(); }



   
    /// \brief Equality Operator Overload.
    /// 
    /// \details Performs an equality comparison of two 
    /// %normal_iterator's whose _Iterator types and 
    /// _Container type are the same. 
    /// 
    /// \tparam _Iterator
    /// \tparam _Container 
    /// \param __lhs 
    /// \param __rhs 
    /// \returns constexpr inline true
    /// \returns constexpr inline false
    /// 
    /// [constexpr]
    /// [noexcept]
    
    template<typename _Iterator, typename _Container>
    constexpr inline bool
    operator== (const normal_iterator<_Iterator, _Container>& __lhs, 
                const normal_iterator<_Iterator, _Container>& __rhs)
        noexcept
    { return __lhs.base() == __rhs.base(); } 



    
    /// \brief Inequality Operator Overload.
    /// 
    /// \details Performs an equality comparison of two 
    /// %normal_iterator's whose _Iterator types can be
    /// different but of they share the same _Container
    /// type.  
    /// 
    /// \tparam _IteratorL
    /// \tparam _IteratorR
    /// \tparam _Container 
    /// \param __lhs 
    /// \param __rhs 
    /// \returns constexpr inline true
    /// \returns constexpr inline false
    /// 
    /// [constexpr]
    /// [noexcept]
    
    template<typename _IteratorL, typename _IteratorR, typename _Container>
    constexpr inline bool
    operator!= (const normal_iterator<_IteratorL, _Container>& __lhs, 
                const normal_iterator<_IteratorR, _Container>& __rhs)
    noexcept
    { return __lhs.base() != __rhs.base(); }



    
    /// \brief Inequality Operator Overload.
    /// 
    /// \details Performs an inequality comparison of two 
    /// %normal_iterator's whose _Iterator types and 
    /// _Container type are the same. 
    /// 
    /// \tparam _Iterator
    /// \tparam _Container 
    /// \param __lhs 
    /// \param __rhs 
    /// \returns constexpr inline true
    /// \returns constexpr inline false
    /// 
    /// [constexpr]
    /// [noexcept]
    
    template<typename _Iterator, typename _Container>
    constexpr inline bool
    operator!= (const normal_iterator<_Iterator, _Container>& __lhs, 
                const normal_iterator<_Iterator, _Container>& __rhs)
    noexcept
    { return __lhs.base() != __rhs.base(); }



    
    /// \brief Less-than Operator Overload.
    /// 
    /// \details Performs an less-than comparison of two 
    /// %normal_iterator's whose _Iterator types can be
    /// different but of they share the same _Container
    /// type. 
    /// 
    /// \tparam _IteratorL 
    /// \tparam _IteratorR 
    /// \tparam _Container 
    /// \param __lhs 
    /// \param __rhs 
    /// \returns constexpr inline true
    /// \returns constexpr inline false
    /// 
    /// [constexpr]
    /// [noexcept]
    
    template<typename _IteratorL, typename _IteratorR, typename _Container>
    constexpr inline bool
    operator< (const normal_iterator<_IteratorL, _Container>& __lhs, 
                const normal_iterator<_IteratorR, _Container>& __rhs)
    noexcept
    { return __lhs.base() < __rhs.base(); }



    
    /// \brief Less-than Operator Overload.
    /// 
    /// \details Performs an less-than comparison of two 
    /// %normal_iterator's whose _Iterator types and 
    /// _Container type are the same. 
    /// 
    /// \tparam _Iterator
    /// \tparam _Container 
    /// \param __lhs 
    /// \param __rhs 
    /// \returns constexpr inline true
    /// \returns constexpr inline false
    /// 
    /// [constexpr]
    /// [noexcept]
    
    template<typename _Iterator, typename _Container>
    constexpr inline bool
    operator< (const normal_iterator<_Iterator, _Container>& __lhs, 
                const normal_iterator<_Iterator, _Container>& __rhs)
    noexcept
    { return __lhs.base() < __rhs.base(); }



    
    /// \brief Greater-than Operator Overload.
    /// 
    /// \details Performs an greater-than comparison of two 
    /// %normal_iterator's whose _Iterator types can be
    /// different but of they share the same _Container
    /// type. 
    /// 
    /// \tparam _IteratorL 
    /// \tparam _IteratorR 
    /// \tparam _Container 
    /// \param __lhs 
    /// \param __rhs 
    /// \returns constexpr inline true
    /// \returns constexpr inline false
    /// 
    /// [constexpr]
    /// [noexcept]
    
    template<typename _IteratorL, typename _IteratorR, typename _Container>
    constexpr inline bool
    operator> (const normal_iterator<_IteratorL, _Container>& __lhs, 
                const normal_iterator<_IteratorR, _Container>& __rhs)
    noexcept
    { return __lhs.base() > __rhs.base(); }



    
    /// \brief Greater-than Operator Overload.
    /// 
    /// \details Performs an greater-than comparison 
    /// of two %normal_iterator's whose _Iterator types 
    /// and _Container type are the same. 
    /// 
    /// \tparam _Iterator
    /// \tparam _Container 
    /// \param __lhs 
    /// \param __rhs 
    /// \returns constexpr inline true
    /// \returns constexpr inline false
    /// 
    /// [constexpr]
    /// [noexcept]
    
    template<typename _Iterator, typename _Container>
    constexpr inline bool
    operator> (const normal_iterator<_Iterator, _Container>& __lhs, 
                const normal_iterator<_Iterator, _Container>& __rhs)
    noexcept
    { return __lhs.base() > __rhs.base(); }



    
    /// \brief Less-than-or-Equal Operator Overload.
    /// 
    /// \details Performs an less-than-or-equal comparison 
    /// of two %normal_iterator's whose _Iterator types can 
    /// be different but of they share the same _Container
    /// type. 
    /// 
    /// \tparam _IteratorL 
    /// \tparam _IteratorR 
    /// \tparam _Container 
    /// \param __lhs 
    /// \param __rhs 
    /// \returns constexpr inline true
    /// \returns constexpr inline false
    /// 
    /// [constexpr]
    /// [noexcept]
    
    template<typename _IteratorL, typename _IteratorR, typename _Container>
    constexpr inline bool
    operator<= (const normal_iterator<_IteratorL, _Container>& __lhs, 
                const normal_iterator<_IteratorR, _Container>& __rhs)
    noexcept
    { return __lhs.base() <= __rhs.base(); }



    
    /// \brief Less-than-or-Equal Operator Overload.
    /// 
    /// \details Performs an less-than-or-equal comparison 
    /// of two %normal_iterator's whose _Iterator types and 
    /// _Container type are the same. 
    /// 
    /// \tparam _Iterator
    /// \tparam _Container 
    /// \param __lhs 
    /// \param __rhs 
    /// \returns constexpr inline true
    /// \returns constexpr inline false
    /// 
    /// [constexpr]
    /// [noexcept]
    
    template<typename _Iterator, typename _Container>
    constexpr inline bool
    operator<= (const normal_iterator<_Iterator, _Container>& __lhs, 
                const normal_iterator<_Iterator, _Container>& __rhs)
    noexcept
    { return __lhs.base() <= __rhs.base(); }



    
    /// \brief Greater-than-or-Equal Operator Overload.
    /// 
    /// \details Performs an greater-than-or-equal comparison 
    /// of two %normal_iterator's whose _Iterator types can 
    /// be different but of they share the same _Container
    /// type. 
    /// 
    /// \tparam _IteratorL 
    /// \tparam _IteratorR 
    /// \tparam _Container 
    /// \param __lhs 
    /// \param __rhs 
    /// \returns constexpr inline true
    /// \returns constexpr inline false
    /// 
    /// [constexpr]
    /// [noexcept]
    
    template<typename _IteratorL, typename _IteratorR, typename _Container>
    constexpr inline bool
    operator>= (const normal_iterator<_IteratorL, _Container>& __lhs, 
                const normal_iterator<_IteratorR, _Container>& __rhs)
    noexcept
    { return __lhs.base() >= __rhs.base(); }



    
    /// \brief Greater-than-or-Equal Operator Overload.
    /// 
    /// \details Performs an greater-than-or-equal comparison 
    /// of two %normal_iterator's whose _Iterator types and 
    /// _Container type are the same. 
    /// 
    /// \tparam _Iterator
    /// \tparam _Container 
    /// \param __lhs 
    /// \param __rhs 
    /// \returns constexpr inline true
    /// \returns constexpr inline false
    /// 
    /// [constexpr]
    /// [noexcept]
    
    template<typename _Iterator, typename _Container>
    constexpr inline bool
    operator>= (const normal_iterator<_Iterator, _Container>& __lhs, 
                const normal_iterator<_Iterator, _Container>& __rhs)
    noexcept
    { return __lhs.base() >= __rhs.base(); }


#endif /// __cpp_lib_three_way_comparison



    
    /// \brief Difference Operator Overload.
    /// 
    /// \details Performs a difference operation between 
    /// two %normal_iterator's whose _Iterator types can 
    /// be different but share the same _Container type.
    /// 
    /// \tparam _IteratorL 
    /// \tparam _IteratorR
    /// \tparam _Container 
    /// \param __lhs 
    /// \param __rhs 
    /// \if __cplusplus >= 201103L
    /// \returns constexpr inline auto -> decltype(__lhs.base() - __rhs.base())
    /// \ifnot __cplusplus >= 201103L
    /// \returns inline typename normal_iterator<_IteratorL, _Container>::difference_type
    /// \endif
    /// 
    /// [constexpr]
    /// [noexcept]
    
    template<typename _IteratorL, typename _IteratorR, typename _Container>
#if __cplusplus >= 201103L /// C++11  
    constexpr inline auto
    operator- (const normal_iterator<_IteratorL, _Container>& __lhs, 
                const normal_iterator<_IteratorR, _Container>& __rhs) 
        noexcept
        -> decltype(__lhs.base() - __rhs.base())
#else /// ! C++11
    inline typename normal_iterator<_IteratorL, _Container>::difference_type
    operator- (const normal_iterator<_IteratorL, _Container>& __lhs, 
                const normal_iterator<_IteratorR, _Container>& __rhs) 
#endif /// __cplusplus >= 201103L
    { return __lhs.base() - __rhs.base(); }



    
    /// \brief Difference Operator Overload.
    /// 
    /// \details Performs a difference operation between
    /// two %normal_iterator's whose _Iterator types and
    /// _Container type are the same.
    /// 
    /// \tparam _Iterator 
    /// \tparam _Container 
    /// \param __lhs 
    /// \param __rhs 
    /// \returns constexpr inline typename normal_iterator<_Iterator, _Container>::difference_type 
    /// 
    /// [constexpr]
    /// [noexcept]
    
    template<typename _Iterator, typename _Container>
    constexpr inline typename normal_iterator<_Iterator, _Container>::difference_type
    operator- (const normal_iterator<_Iterator, _Container>& __lhs, 
                const normal_iterator<_Iterator, _Container>& __rhs)
    noexcept
    { return __lhs.base() - __rhs.base(); }



    
    /// \brief Addition Operator Overload.
    /// 
    /// \details Takes an offset \param __n and a %normal_iterator 
    /// \param __i. Constructs a new %normal_iterator by adding
    /// \param __n to \param __i.base().
    /// 
    /// \tparam _Iterator 
    /// \tparam _Container 
    /// \param __n 
    /// \param __i 
    /// \returns constexpr inline normal_iterator<_Iterator, _Container> 
    /// 
    /// [constexpr]
    /// [noexcept]
    
    template<typename _Iterator, typename _Container>
    constexpr inline normal_iterator<_Iterator, _Container>
    operator+ (typename normal_iterator<_Iterator, _Container>::difference_type __n, 
                const normal_iterator<_Iterator, _Container>& __i)
    noexcept
    { return normal_iterator<_Iterator, _Container>(__i.base() + __n); }



    
    /// \brief Makes a new %normal_iterator.
    /// 
    /// \details An adaptor for turning STL container iterators 
    /// into %normal_iterators.
    /// 
    /// \code {.cpp}
    /// auto it = make_normal_iterator<std::container>(c.begin()); 
    /// \endcode 
    /// 
    /// \tparam _Container 
    /// \param __i 
    /// \returns constexpr auto -> normal_iterator<typename _Container::iterator, _Container>
    /// 
    /// [constexpr]
    /// [noexcept]
    
    template<typename _Container>
    constexpr auto
    make_normal(typename _Container::iterator __i)
    noexcept
        -> normal_iterator<typename _Container::iterator, _Container>
    { return normal_iterator<typename _Container::iterator, _Container>(__i); }



    
    /// \brief Makes a new %normal_iterator.
    /// 
    /// \details An adaptor for making C-style array pointers 
    /// into %normal_iterators.
    /// 
    /// \code {.cpp}
    /// auto it =  make_normal<int*, int[]>(arr);
    /// \endcode
    /// 
    /// \tparam _Iterator 
    /// \tparam _Container 
    /// \param __i 
    /// \returns constexpr auto -> normal_iterator<_Iterator, _Container> 
    /// 
    /// [constexpr]
    /// [noexcept]
    
    template<typename _Iterator, typename _Container>
    constexpr auto
    make_normal(_Iterator __i)
    noexcept
        -> normal_iterator<_Iterator, _Container>
    { return normal_iterator<_Iterator, _Container>(__i); }


#   if __cplusplus >= 201703L /// C++17
    
    /// \brief Makes a new %normal_iterator.
    /// 
    /// \details An adaptor for making STL container iterators
    /// into %normal_iterators using C++17 type deduction.
    /// 
    /// \code {.cpp}
    /// auto it = make_normal(c, c.begin());
    /// \endcode
    /// 
    /// \notes \param __c has the attribute [[maybe_unused]]
    /// 
    /// \tparam _Container 
    /// \tparam _Iterator 
    /// \param __c 
    /// \param __i 
    /// \returns constexpr auto -> normal_iterator<_Iterator, _Container> 
    /// 
    /// [constexpr]
    /// [noexcept]
    
    template<typename _Container, typename _Iterator>
    constexpr auto
    make_normal([[maybe_unused]] const _Container& __c, _Iterator __i)
    noexcept
        -> normal_iterator<_Iterator, _Container>
    { return normal_iterator<_Iterator, _Container>(__i); }

#   endif /// __cplusplus >= 201703L

} /// namespace cortex


#   endif /// __cplusplus >= 201402L

#endif /// CORTEX_NORMAL_ITERATOR_HPP