#ifndef SHAND_TYPE_TRAITS_INCLUDE
#define SHAND_TYPE_TRAITS_INCLUDE

namespace shand {

namespace detail {
    struct sfinae_types {
        typedef char one;
        typedef struct { char arr[2]; } two;
    };

    template<typename Type>
    struct in_array : public sfinae_types {
    private:
        template<typename Up>
        static one test(Up(*)[1]);

        template<typename>
        static two test(...);

    public:
        static const bool value = sizeof(test<Type>(0)) == 1;
    };
} // namespace detail


template <typename Type, Type Value>
struct integral_constant {
    static const Type value = Value;
    typedef Type value_type;
};

typedef integral_constant<bool, true>  true_type;
typedef integral_constant<bool, false> false_type;

// w’è‚³‚ê‚½Œ^‚ğ“Áê‰»
#define SHAND_TRAITS_SPEC0(Spec, Value) \
    template <> \
    struct Spec : public integral_constant<bool, Value> {};

#define SHAND_TRAITS_SPEC1(Spec, Value) \
    template <typename Type> \
    struct Spec : public integral_constant<bool, Value> {};

#define SHAND_TRAITS_SPEC2(Spec, Value) \
    template <typename Type, typename ClassName> \
    struct Spec : public integral_constant<bool, Value> {};

// Type, Type const, Type volatile, Type const volatile‚Ì4‚Â‚ğˆê‹C‚É“Áê‰»
#define SHAND_TRAITS_SPEC(Order, Traits, SpecialType, Value)              \
    SHAND_TRAITS_SPEC##Order##(Traits<SpecialType>,                Value) \
    SHAND_TRAITS_SPEC##Order##(Traits<SpecialType const>,          Value) \
    SHAND_TRAITS_SPEC##Order##(Traits<SpecialType volatile>,       Value) \
    SHAND_TRAITS_SPEC##Order##(Traits<SpecialType const volatile>, Value)


// is_void : voidŒ^
template <typename Type>
struct is_void : public false_type {};
SHAND_TRAITS_SPEC(0, is_void, void, true)

// is_integral : ®”Œ^
template <typename Type>
struct is_integral : public false_type {};
SHAND_TRAITS_SPEC(0, is_integral, bool,               true)
SHAND_TRAITS_SPEC(0, is_integral, char,               true)
SHAND_TRAITS_SPEC(0, is_integral, signed char,        true)
SHAND_TRAITS_SPEC(0, is_integral, unsigned char,      true)
SHAND_TRAITS_SPEC(0, is_integral, wchar_t,            true)
SHAND_TRAITS_SPEC(0, is_integral, short,              true)
SHAND_TRAITS_SPEC(0, is_integral, unsigned short,     true)
SHAND_TRAITS_SPEC(0, is_integral, int,                true)
SHAND_TRAITS_SPEC(0, is_integral, unsigned int,       true)
SHAND_TRAITS_SPEC(0, is_integral, long,               true)
SHAND_TRAITS_SPEC(0, is_integral, unsigned long,      true)
SHAND_TRAITS_SPEC(0, is_integral, long long,          true)
SHAND_TRAITS_SPEC(0, is_integral, unsigned long long, true)

// is_float : •‚“®¬”“_Œ^
template <typename Type>
struct is_float : public false_type {};
SHAND_TRAITS_SPEC(0, is_float, float,       true)
SHAND_TRAITS_SPEC(0, is_float, double,      true)
SHAND_TRAITS_SPEC(0, is_float, long double, true)

// is_array : ”z—ñŒ^
template <typename Type>
struct is_array : public false_type {};

template <typename Type, int Size>
struct is_array<Type[Size]> : public true_type {};

template <typename Type>
struct is_array<Type[]> : public true_type {};

// is_reference : QÆŒ^
template <typename Type>
struct is_reference : public false_type {};

template <typename Type>
struct is_reference<Type&> : public true_type {};

// is_pointer : ƒ|ƒCƒ“ƒ^Œ^
template <typename Type>
struct is_pointer : false_type {};
SHAND_TRAITS_SPEC(1, is_pointer, Type*, true)

// is_const : constCü‚³‚ê‚½Œ^
template <typename Type>
struct is_const : public false_type {};

template <typename Type>
struct is_const<Type const> : public true_type {};

// is_volatile : volatileCü‚³‚ê‚½Œ^
template <typename Type>
struct is_volatile : public false_type {};

template <typename Type>
struct is_volatile<Type volatile> : true_type {};

// is_same : “¯‚¶Œ^
template <typename, typename>
struct is_same : public false_type {};

template <typename Type>
struct is_same<Type, Type> : public true_type {};


namespace detail {
    template<typename Type>
    struct is_union_or_class_helper : public sfinae_types {
    private:
        template<typename Up>
        static one test(int Up::*);

        template<typename>
        static two test(...);

    public:
        static const bool value = sizeof(test<Type>(0)) == 1;
    };

    template<typename Type>
    struct is_union_or_class : public integral_constant<bool, is_union_or_class_helper<Type>::value> {};
} // namespace detail

// is_function : ŠÖ”Œ^
template<typename Type>
struct is_function
    : public integral_constant<bool, !(detail::in_array<Type>::value
                                   ||  detail::is_union_or_class<Type>::value
                                   ||  is_reference<Type>::value
                                   ||  is_void<Type>::value)>
   {};

// is_member_object_pointer : ƒf[ƒ^ƒƒ“ƒoƒ|ƒCƒ“ƒ^Œ^
template <typename Type>
struct is_member_object_pointer : public  false_type {};
SHAND_TRAITS_SPEC(2, is_member_object_pointer, Type ClassName::*, !is_function<Type>::value)

// is_member_function_pointer : ƒƒ“ƒoŠÖ”ƒ|ƒCƒ“ƒ^Œ^
template <typename Type>
struct is_member_function_pointer : public  false_type {};
SHAND_TRAITS_SPEC(2, is_member_function_pointer, Type ClassName::*, is_function<Type>::value)

// is_member_pointer : ƒƒ“ƒoƒ|ƒCƒ“ƒ^Œ^
template <typename Type>
struct is_member_pointer : public integral_constant<bool,
                                  (is_member_object_pointer<Type>::value || is_member_function_pointer<Type>::value)> {};

// is_arithmetic : ZpŒ^(®”Œ^/•‚“®¬”“_Œ^)
template <typename Type>
struct is_arithmetic : public integral_constant<bool, (is_integral<Type>::value || is_float<Type>::value)> {};

// is_fundamental : Šî–{Œ^(®”Œ^/•‚“®¬”“_Œ^/voidŒ^)
template <typename Type>
struct is_fundamental : public integral_constant<bool, (is_arithmetic<Type>::value || is_void<Type>::value)> {};

// is_enum : enumŒ^
template <typename Type>
struct is_enum : public integral_constant<bool,
                                  !(is_fundamental<Type>::value
                                 || is_array<Type>::value
                                 || is_pointer<Type>::value
                                 || is_reference<Type>::value
                                 || is_member_pointer<Type>::value
                                 || detail::is_union_or_class<Type>::value)>
    {};

// is_object : ƒIƒuƒWƒFƒNƒgŒ^( not(ŠÖ”Œ^/QÆŒ^/voidŒ^) )
template <typename Type>
struct is_object : public integral_constant<bool,
                                !(is_function<Type>::value
                               || is_reference<Type>::value
                               || is_void<Type>::value)>
    {};

// is_scalar : ƒXƒJƒ‰Œ^(®”Œ^/•‚“®¬”“_”Œ^/ƒ|ƒCƒ“ƒ^Œ^/ƒƒ“ƒoƒ|ƒCƒ“ƒ^Œ^)
template <typename Type>
struct is_scalar : public integral_constant<bool,
                                (is_arithmetic<Type>::value
                              || is_member_pointer<Type>::value
                              || is_pointer<Type>::value
                              || is_enum<Type>::value)>
    {};

// is_compound : •¡‡Œ^( not(Šî–{Œ^...®”Œ^/•‚“®¬”“_”Œ^/voidŒ^) )
template <typename Type>
struct is_compound : public integral_constant<bool, !(is_fundamental<Type>::value)> {};


namespace detail {
    template <typename Type, bool = !is_union_or_class<Type>::value>
    struct is_empty_helper {
    private:
        template <typename>
        struct first {};

        template <typename Up>
        struct second : public Up {};

    public:
        static const bool value = sizeof(first<Type>) == sizeof(second<Type>);
    };

    template <typename Type>
    struct is_empty_helper<Type, true> {
        static const bool value = false;
    };

} // namespace detail

// is_empty : ‹ó‚Ì\‘¢‘Ì/ƒNƒ‰ƒX
template <typename Type>
struct is_empty : public integral_constant<bool, detail::is_empty_helper<Type>::value> {};


namespace detail {
    template <typename Type, bool = !is_union_or_class<Type>::value>
    struct is_polymorphic_helper {
    private:
        template <typename Up>
        struct first : public Up {};

        template <typename Up>
        struct second : public Up {
            virtual void dummy();
            virtual ~second() throw();
        };

    public:
        static const bool value = sizeof(first<Type>) == sizeof(second<Type>);
    };

    template <typename Type>
    struct is_polymorphic_helper<Type, true> {
        static const bool value = false;
    };

} // namespace detail

// is_polymorphic : ‰¼‘zŠÖ”ƒe[ƒuƒ‹‚ğ‚Á‚Ä‚¢‚éƒNƒ‰ƒX
template <typename Type>
struct is_polymorphic : public integral_constant<bool, detail::is_polymorphic_helper<Type>::value> {};

// is_abstract : ’ŠÛƒNƒ‰ƒX
template <typename Type>
struct is_abstract : public integral_constant<bool,
    (!detail::in_array<Type>::value && detail::is_union_or_class<Type>::value)> {};

// is_signed : signedŒ^
template <typename Type>
struct is_signed : public false_type {};
SHAND_TRAITS_SPEC(0, is_signed, signed char, true)
SHAND_TRAITS_SPEC(0, is_signed, short,       true)
SHAND_TRAITS_SPEC(0, is_signed, int,         true)
SHAND_TRAITS_SPEC(0, is_signed, long,        true)
SHAND_TRAITS_SPEC(0, is_signed, long long,   true)

// is_unsigned : unsignedŒ^
template <typename Type>
struct is_unsigned : public false_type {};
SHAND_TRAITS_SPEC(0, is_unsigned, unsigned char,      true)
SHAND_TRAITS_SPEC(0, is_unsigned, unsigned short,     true)
SHAND_TRAITS_SPEC(0, is_unsigned, unsigned int,       true)
SHAND_TRAITS_SPEC(0, is_unsigned, unsigned long,      true)
SHAND_TRAITS_SPEC(0, is_unsigned, unsigned long long, true)

// remove_const : constCü‚Ìœ‹
template <typename Type>
struct remove_const {
    typedef Type type;
};

template <typename Type>
struct remove_const<Type const> {
    typedef Type type;
};

// remove_volatile : volatileCü‚Ìœ‹
template <typename Type>
struct remove_volatile {
    typedef Type type;
};

template <typename Type>
struct remove_volatile<Type volatile> {
    typedef Type type;
};

// remove_cv : const/volatileCü‚Ìœ‹
template <typename Type>
struct remove_cv {
    typedef typename remove_const<typename remove_volatile<Type>::type>::type type;
};

// remove_pointer : *(ƒ|ƒCƒ“ƒ^)œ‹
template <typename Type>
struct remove_pointer {
    typedef Type type;
};

template <typename Type>
struct remove_pointer<Type*> {
    typedef Type type;
};

// remove_reference : &(QÆ)œ‹
template <typename Type>
struct remove_reference {
    typedef Type type;
};

template <typename Type>
struct remove_reference<Type&> {
    typedef Type type;
};

// remove_extent : ”z—ñ‚Ì—v‘fŒ^æ“¾
template<typename Type>
struct remove_extent {
    typedef Type type;
};

template<typename Type, int Size>
struct remove_extent<Type[Size]> {
    typedef Type type;
};

template<typename Type>
struct remove_extent<Type[]> {
    typedef Type type;
};

// remove_all_extents : ‘½ŸŒ³”z—ñ‚Ì—v‘fŒ^æ“¾
template <typename Type>
struct remove_all_extents {
    typedef Type type;
};

template <typename Type, int Size>
struct remove_all_extents<Type[Size]> {
    typedef typename remove_all_extents<Type>::type type;
};

template <typename Type>
struct remove_all_extents<Type[]> {
    typedef typename remove_all_extents<Type>::type type;
};

// add_const : constCü•t‰Á
template <typename Type>
struct add_const {
    typedef Type const type;
};

// add_volatile : volatileCü•t‰Á
template <typename Type>
struct add_volatile {
    typedef Type volatile type;
};

// add_cv : const volatileCü•t‰Á
template <typename Type>
struct add_cv {
    typedef typename add_const<typename add_volatile<Type>::type>::type type;
};

// add_pointer : *(ƒ|ƒCƒ“ƒ^)•t‰Á
template <typename Type>
struct add_pointer {
    typedef typename remove_reference<Type>::type* type;
};

namespace detail {
    template<typename Type, bool = (is_void<Type>::value || is_reference<Type>::value)>
    struct add_reference_helper {
        typedef Type& type;
    };

    template<typename Type>
    struct add_reference_helper<Type, true> {
        typedef Type type;
    };

} // namespace detail

// add_reference : &(QÆ)•t‰Á
template<typename Type>
struct add_reference : public detail::add_reference_helper<Type> {};

// is_pod : PODŒ^
template <typename Type>
struct is_pod : public integral_constant<bool,
                        (is_void<Type>::value
                      || is_scalar<typename remove_all_extents<Type>::type>::value)>
    {};

namespace detail {
    template <typename Base, typename Derived,
        bool = (!is_union_or_class<Base>::value
             || !is_union_or_class<Derived>::value
             || is_same<Base, Derived>::value)>
    struct is_base_of_helper : public sfinae_types {
    private:
        typedef typename remove_cv<Base>::type    NoCv_Base;
        typedef typename remove_cv<Derived>::type NoCv_Derived;

        template <typename Up>
        static one test(NoCv_Derived&, Up);

        static two test(NoCv_Base&, int);

        struct Conv {
            operator NoCv_Derived&();
            operator NoCv_Base&() const;
        };

    public:
        static const bool value = sizeof(test(Conv(), 0)) == 1;
    };

    template <typename Base, typename Derived>
    struct is_base_of_helper<Base, Derived, true> {
        static const bool value = is_same<Base, Derived>::value;
    };

} // namespace detail

// is_base_of : Œp³ŠÖŒW‚ğ”»’f
template <typename Base, typename Derived>
struct is_base_of : public integral_constant<bool, detail::is_base_of_helper<Base, Derived>::value> {};


namespace detail {
    template <typename From, typename To>
    struct is_convertible_simple : public sfinae_types {
    private:
        static one test(To);
        static two test(...);
    static From make_from();

    public:
        static const bool value = sizeof(test(make_from())) == 1;
    };

    template <typename Type>
    struct is_int_or_cref {
        typedef typename remove_reference<Type>::type RefRemoveType;
        static const bool value = (is_integral<Type>::value
                                    || (is_integral<RefRemoveType>::value
                                     && is_const<RefRemoveType>::value
                                     && !is_volatile<RefRemoveType>::value));
    };

    template <typename From, typename To,
        bool = (is_void<From>::value || is_void<To>::value
             || is_function<To>::value || is_array<To>::value
             || (is_float<typename remove_reference<From>::type>::value
              && is_int_or_cref<To>::value))>
    struct is_convertible_helper {
        static const bool value = (is_convertible_simple<typename add_reference<From>::type, To>::value);
    };

    template<typename From, typename To>
    struct is_convertible_helper<From, To, true> {
        static const bool value = (is_void<To>::value || (is_int_or_cref<To>::value && !is_void<From>::value));
    };

} // namespace detail

// is_convertible : •ÏŠ·‰Â”\‚©”»’f
template <typename From, typename To>
struct is_convertible : public integral_constant<bool, detail::is_convertible_helper<From, To>::value> {};

#undef SHAND_TRAITS_SPEC0
#undef SHAND_TRAITS_SPEC1
#undef SHAND_TRAITS_SPEC2
#undef SHAND_TRAITS_SPEC

} // namespace shand

#endif // SHAND_TYPE_TRAITS_INCLUDE

