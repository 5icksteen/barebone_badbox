// #pragma once

// #include <cstddef>
// #include <type_traits>
// #include <iterator>

// namespace bad
// {
// template <typename value_type, size_t _Nm>
// struct __array_traits
// {
//   typedef value_type _Type[_Nm];

//   static constexpr value_type&
//   _S_ref(const _Type& __t, size_t __n) noexcept
//   {
//     return const_cast<value_type&>(__t[__n]);
//   }

//   static constexpr value_type*
//   _S_ptr(const _Type& __t) noexcept
//   {
//     return const_cast<value_type*>(__t);
//   }
// };

// template <typename value_type>
// struct __array_traits<value_type, 0>
// {
//   struct _Type
//   {
//   };

//   static constexpr value_type&
//   _S_ref(const _Type&, size_t) noexcept
//   {
//     return *static_cast<value_type*>(nullptr);
//   }

//   static constexpr value_type*
//   _S_ptr(const _Type&) noexcept
//   {
//     return nullptr;
//   }
// };

// template <typename value_type, size_t _Nm>
// struct enum_array
// {
//   // Support for zero-sized arrays mandatory.
//   typename __array_traits<value_type, _Nm>::_Type _M_elems;

//   // Iterators.
//   value_type* begin() noexcept
//   {
//     return value_type(data());
//   }

//   const value_type* begin() const noexcept
//   {
//     return value_type(data());
//   }

//   value_type* end() noexcept
//   {
//     return value_type(data() + _Nm);
//   }

//   const value_type* end() const noexcept
//   {
//     return value_type(data() + _Nm);
//   }

//   std::reverse_iterator<value_type*> rbegin() noexcept
//   {
//     return std::reverse_iterator<value_type*>(end());
//   }

//   std::reverse_iterator<const value_type*> rbegin() const noexcept
//   {
//     return std::reverse_iterator<const value_type*>(end());
//   }

//   std::reverse_iterator<value_type*> rend() noexcept
//   {
//     return std::reverse_iterator<value_type*>(begin());
//   }

//   std::reverse_iterator<const value_type*> rend() const noexcept
//   {
//     return std::reverse_iterator<const value_type*>(begin());
//   }

//   const value_type* cbegin() const noexcept
//   {
//     return value_type(data());
//   }

//   const value_type* cend() const noexcept
//   {
//     return value_type(data() + _Nm);
//   }

//   std::reverse_iterator<const value_type*> crbegin() const noexcept
//   {
//     return std::reverse_iterator<const value_type*>(end());
//   }

//   std::reverse_iterator<const value_type*> crend() const noexcept
//   {
//     return std::reverse_iterator<const value_type*>(begin());
//   }

//   // Capacity.
//   constexpr size_t size() const noexcept { return _Nm; }

//   constexpr size_t max_size() const noexcept { return _Nm; }

//   constexpr bool empty() const noexcept { return size() == 0; }

//   // Element access.
//   // value_type&
//   // operator[](size_t __n) noexcept
//   // {
//   //   return __array_traits<value_type, _Nm>::_S_ref(_M_elems, __n);
//   // }

//   // constexpr const value_type&
//   // operator[](size_t __n) const noexcept
//   // {
//   //   return __array_traits<value_type, _Nm>::_S_ref(_M_elems, __n);
//   // }
//   value_type& operator[](auto __n) noexcept
//   {
//     return __array_traits<value_type, _Nm>::_S_ref(_M_elems, static_cast<size_t>(__n));
//   }

//   constexpr const value_type& operator[](auto __n) const noexcept
//   {
//     return __array_traits<value_type, _Nm>::_S_ref(_M_elems, static_cast<size_t>(__n));
//   }

//   value_type* data() noexcept
//   {
//     return __array_traits<value_type, _Nm>::_S_ptr(_M_elems);
//   }

//   const value_type* data() const noexcept
//   {
//     return __array_traits<value_type, _Nm>::_S_ptr(_M_elems);
//   }
// };

// template <typename value_type, typename... _Up>
// enum_array(value_type, _Up...)
//     -> enum_array<std::enable_if_t<(std::is_same_v<value_type, _Up> && ...), value_type>,
//                   1 + sizeof...(_Up)>;

// }  // namespace bad
