# Header file `concepts.hpp`

``` cpp
#define CORTEX_CONCEPTS_H

namespace cortex
{
    template <typename T>concept Any = true;

    template <typename T>concept None = false;

    template <typename T>concept Number = std::integral<T> || std::floating_point<T>;

    template <typename T>concept Object = std::is_object_v<T>;

    template <typename _Lt, typename _Rt>concept AddableWith = requires(_Lt __lhs, _Rt __rhs){__lhs+__rhs;};

    template <typename T>concept Addable = requires(T __lhs, T __rhs){__lhs+__rhs;};

    template <typename _Lt, typename _Rt>concept SubtractableWith = requires(_Lt __lhs, _Rt __rhs){__lhs-__rhs;};

    template <typename T>concept Subtractable = requires(T __lhs, T __rhs){__lhs-__rhs;};

    template <typename _Lt, typename _Rt>concept MultiplicableWith = requires(_Lt __lhs, _Rt __rhs){__lhs*__rhs;};

    template <typename T>concept Multiplicable = requires(T __lhs, T __rhs){__lhs*__rhs;};

    template <typename _Lt, typename _Rt>concept DivisibleWith = requires(_Lt __lhs, _Rt __rhs){__lhs / __rhs;};

    template <typename T>concept Divisible = requires(T __lhs, T __rhs){__lhs / __rhs;};

    template <typename _Lt, typename _Rt>concept ModuloWith = requires(_Lt __lhs, _Rt __rhs){__lhs % __rhs;};

    template <typename T>concept Modulo = requires(T __lhs, T __rhs){__lhs % __rhs;};

    template <typename _Lt, typename _Rt>concept BitXorWith = requires(_Lt __lhs, _Rt __rhs){__lhs ^ __rhs;};

    template <typename T>concept BitXor = requires(T __lhs, T __rhs){__lhs ^ __rhs;};

    template <typename _Lt, typename _Rt>concept BitAndWith = requires(_Lt __lhs, _Rt __rhs){__lhs&__rhs;};

    template <typename T>concept BitAnd = requires(T __lhs, T __rhs){__lhs&__rhs;};

    template <typename _Lt, typename _Rt>concept BitOrWith = requires(_Lt __lhs, _Rt __rhs){__lhs | __rhs;};

    template <typename T>concept BitOr = requires(T __lhs, T __rhs){__lhs | __rhs;};

    template <typename _Lt, typename _Rt>concept LeftBitShiftWith = requires(_Lt __lhs, _Rt __rhs){__lhs<<__rhs;};

    template <typename T>concept LeftBitShift = requires(T __lhs, T __rhs){__lhs<<__rhs;};

    template <typename _Lt, typename _Rt>concept RightBitShiftWith = requires(_Lt __lhs, _Rt __rhs){__lhs>>__rhs;};

    template <typename T>concept RightBitShift = requires(T __lhs, T __rhs){__lhs>>__rhs;};

    template <typename T>concept BitNot = requires(T __val){~__val;};

    template <typename _Container, typename _Index>concept Subscriptible = requires{requires Object<_Container> || std::is_array_v<_Container> || std::is_pointer_v<_Container>;} && requires(_Container __container, _Index __index){__container[__index];};

    template <typename _Func, typename..._Arg>concept Invocable = std::is_invocable_v<_Func, _Arg...>;
}
```

Some generalised concepts for use throughout the Cortex Library

Author: Tyler Swann (oraqlle@github.com)

Header Version: v1.0.1

Date: 25-06-2022

License: MIT

Copyright: Copyright (c) 2022

concepts.hpp

### Unexposed entity `cortex::Any`

``` cpp
template <typename T>concept Any = true;
```

Any Concept

A concept for which any type is valid.

-----

### Unexposed entity `cortex::None`

``` cpp
template <typename T>concept None = false;
```

None Concept

A concept for which no type is valid.

-----

### Unexposed entity `cortex::Number`

``` cpp
template <typename T>concept Number = std::integral<T> || std::floating_point<T>;
```

Number Concept

Uses the standard C++20 concepts for std::integral and std::floating\_point to define a concept for a type that is a number.

-----

### Unexposed entity `cortex::Object`

``` cpp
template <typename T>concept Object = std::is_object_v<T>;
```

Object Concept

Uses the type trait std::is\_object\_v to define a concept for a type that is an object.

-----

### Unexposed entity `cortex::AddableWith`

``` cpp
template <typename _Lt, typename _Rt>concept AddableWith = requires(_Lt __lhs, _Rt __rhs){__lhs+__rhs;};
```

AddableWith Concept

Determines if two (potentially different) types are within the domain of operation for the addition operation.

-----

### Unexposed entity `cortex::Addable`

``` cpp
template <typename T>concept Addable = requires(T __lhs, T __rhs){__lhs+__rhs;};
```

Addable Concept

Determines if a type is within the domain of operation for the addition operation.

-----

### Unexposed entity `cortex::SubtractableWith`

``` cpp
template <typename _Lt, typename _Rt>concept SubtractableWith = requires(_Lt __lhs, _Rt __rhs){__lhs-__rhs;};
```

SubtractableWith Concept

Determines if two (potentially different) types are within the domain of operation for the subtraction operation.

-----

### Unexposed entity `cortex::Subtractable`

``` cpp
template <typename T>concept Subtractable = requires(T __lhs, T __rhs){__lhs-__rhs;};
```

Subtractable Concept

Determines if a type is within the domain of operation for the subtraction operation.

-----

### Unexposed entity `cortex::MultiplicableWith`

``` cpp
template <typename _Lt, typename _Rt>concept MultiplicableWith = requires(_Lt __lhs, _Rt __rhs){__lhs*__rhs;};
```

MultiplicableWith Concept

Determines if two (potentially different) types are within the domain of operation for the multiplication operation.

-----

### Unexposed entity `cortex::Multiplicable`

``` cpp
template <typename T>concept Multiplicable = requires(T __lhs, T __rhs){__lhs*__rhs;};
```

Multiplicable Concept

Determines if a type is within the domain of operation for the multiplication operation.

-----

### Unexposed entity `cortex::DivisibleWith`

``` cpp
template <typename _Lt, typename _Rt>concept DivisibleWith = requires(_Lt __lhs, _Rt __rhs){__lhs / __rhs;};
```

DivisibleWith Concept

Determines if two (potentially different) types are within the domain of operation for the division operation.

-----

### Unexposed entity `cortex::Divisible`

``` cpp
template <typename T>concept Divisible = requires(T __lhs, T __rhs){__lhs / __rhs;};
```

Divisible Concept

Determines if a type is within the domain of operation for the division operation.

-----

### Unexposed entity `cortex::ModuloWith`

``` cpp
template <typename _Lt, typename _Rt>concept ModuloWith = requires(_Lt __lhs, _Rt __rhs){__lhs % __rhs;};
```

ModuloWith Concept

Determines if two (potentially different) types are within the domain of operation for the modulus operation.

-----

### Unexposed entity `cortex::Modulo`

``` cpp
template <typename T>concept Modulo = requires(T __lhs, T __rhs){__lhs % __rhs;};
```

Modulo Concept

Determines if a type is within the domain of operation for the modulus operation.

-----

### Unexposed entity `cortex::BitXorWith`

``` cpp
template <typename _Lt, typename _Rt>concept BitXorWith = requires(_Lt __lhs, _Rt __rhs){__lhs ^ __rhs;};
```

BitXorWith Concept

Determines if two (potentially different) types are within the domain of operation for the bitwise `exclusive-or` (`xor`) operation.

-----

### Unexposed entity `cortex::BitXor`

``` cpp
template <typename T>concept BitXor = requires(T __lhs, T __rhs){__lhs ^ __rhs;};
```

BitXor Concept

Determines if a type is withinthe domain of operation for the bitwise `exclusive-or` (`xor`) operation.

-----

### Unexposed entity `cortex::BitAndWith`

``` cpp
template <typename _Lt, typename _Rt>concept BitAndWith = requires(_Lt __lhs, _Rt __rhs){__lhs&__rhs;};
```

BitAndWith Concept

Determines if two (potentially different) types are within the domain of operation for the bitwise `and` operation.

-----

### Unexposed entity `cortex::BitAnd`

``` cpp
template <typename T>concept BitAnd = requires(T __lhs, T __rhs){__lhs&__rhs;};
```

BitAnd Concept

Determines if a type is withinthe domain of operation for the bitwise `and` operation.

-----

### Unexposed entity `cortex::BitOrWith`

``` cpp
template <typename _Lt, typename _Rt>concept BitOrWith = requires(_Lt __lhs, _Rt __rhs){__lhs | __rhs;};
```

BitOrWith Concept

Determines if two (potentially different) types are within the domain of operation for the bitwise `or` operation.

-----

### Unexposed entity `cortex::BitOr`

``` cpp
template <typename T>concept BitOr = requires(T __lhs, T __rhs){__lhs | __rhs;};
```

BitOr Concept

Determines if a type is withinthe domain of operation for the bitwise `or` operation.

-----

### Unexposed entity `cortex::LeftBitShiftWith`

``` cpp
template <typename _Lt, typename _Rt>concept LeftBitShiftWith = requires(_Lt __lhs, _Rt __rhs){__lhs<<__rhs;};
```

LeftBitShiftWith Concept

Determines if two (potentially different) types are within the domain of operation for the bitwise `or` operation.

-----

### Unexposed entity `cortex::LeftBitShift`

``` cpp
template <typename T>concept LeftBitShift = requires(T __lhs, T __rhs){__lhs<<__rhs;};
```

LeftBitShift Concept

Determines if a type is withinthe domain of operation for the `left bitwise shift` operation.

-----

### Unexposed entity `cortex::RightBitShiftWith`

``` cpp
template <typename _Lt, typename _Rt>concept RightBitShiftWith = requires(_Lt __lhs, _Rt __rhs){__lhs>>__rhs;};
```

RightBitShiftWith Concept

Determines if two (potentially different) types are within the domain of operation for the bitwise `or` operation.

-----

### Unexposed entity `cortex::RightBitShift`

``` cpp
template <typename T>concept RightBitShift = requires(T __lhs, T __rhs){__lhs>>__rhs;};
```

RightBitShift Concept

Determines if a type is withinthe domain of operation for the `right bitwise shift` operation.

-----

### Unexposed entity `cortex::BitNot`

``` cpp
template <typename T>concept BitNot = requires(T __val){~__val;};
```

BitNot Concept

Checks if a type is within the domain of operation for the bitwise `not` operation.

-----

### Unexposed entity `cortex::Subscriptible`

``` cpp
template <typename _Container, typename _Index>concept Subscriptible = requires{requires Object<_Container> || std::is_array_v<_Container> || std::is_pointer_v<_Container>;} && requires(_Container __container, _Index __index){__container[__index];};
```

Subscriptible Concept

Determines if a type is within the domain of operation for the increment operation.

-----

### Unexposed entity `cortex::Invocable`

``` cpp
template <typename _Func, typename..._Arg>concept Invocable = std::is_invocable_v<_Func, _Arg...>;
```

Invokable

Determines if function type is invokable. Utilises the template meta-programming struct std::is\_invokable\_v

-----
