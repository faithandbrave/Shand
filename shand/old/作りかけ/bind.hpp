#ifndef SHAND_BIND_INCLUDE
#define SHAND_BIND_INCLUDE

namespace shand {

// place holders
template <int I>
class arg {};

template <int I>
bool operator==(const arg<I>&, const arg<I>&)
{
	return true;
}

namespace placeholder {

static arg<1> _1;
static arg<2> _2;
static arg<3> _3;
static arg<4> _4;
static arg<5> _5;
static arg<6> _6;
static arg<7> _7;
static arg<8> _8;
static arg<9> _9;

} // namespace placeholder

namespace _bi {

// result_traits
template <class R, class F>
struct result_traits {
	typedef R type;
};

struct unspecified {};

template<class F>
struct result_traits<unspecified, F> {
    typedef typename F::result_type type;
};


// visit_each
template<typename Visitor, typename T>
inline void visit_each(Visitor& visitor, const T& t, long)
{
	visitor(t);
}

template<typename Visitor, typename T>
inline void visit_each(Visitor& visitor, const T& t)
{
	visit_each(visitor, t, 0);
}

// storage
template <class A1> struct storage1
{
	explicit storage1(A1 a1) : a1_(a1) {}

	template <class V> void accept(V& v) const
	{
		visit_each(v, a1_, 0);
	}

	A1 a1_;
};

template<int I> struct storage1<arg<I> >
{
	explicit storage1(arg<I>) {}
	template<class V> void accept(V &) const {}
	static arg<I> a1_() { return arg<I>(); }
};

template<int I> struct storage1<arg<I> (*)()> {
	explicit storage1(arg<I> (*)()) {}
	template<class V> void accept(V&) const {}
	static arg<I> a1_() { return arg<I>(); }
};


template<class A1, class A2> struct storage2: public storage1<A1>
{
    typedef storage1<A1> inherited;

    storage2(A1 a1, A2 a2) : storage1<A1>(a1), a2_(a2) {}

    template<class V> void accept(V & v) const
    {
        inherited::accept(v);
        visit_each(v, a2_, 0);
    }

    A2 a2_;
};

template<class A1, int I> struct storage2<A1, arg<I> > : public storage1<A1>
{
    typedef storage1<A1> inherited;

    storage2(A1 a1, arg<I>) : storage1<A1>(a1) {}

    template<class V> void accept(V& v) const
    {
        inherited::accept(v);
    }

    static arg<I> a2_() { return arg<I>(); }
};

template<class A1, int I> struct storage2<A1, arg<I> (*)()> : public storage1<A1>
{
    typedef storage1<A1> inherited;

    storage2(A1 a1, arg<I> (*)()): storage1<A1>( a1 ) {}

    template<class V> void accept(V & v) const
    {
        inherited::accept(v);
    }

    static arg<I> a2_() { return arg<I>(); }
};


template<class A1, class A2, class A3> struct storage3 : public storage2<A1, A2>
{
    typedef storage2<A1, A2> inherited;

    storage3(A1 a1, A2 a2, A3 a3) : storage2<A1, A2>(a1, a2), a3_(a3) {}

    template<class V> void accept(V& v) const
    {
        inherited::accept(v);
        visit_each(v, a3_, 0);
    }

    A3 a3_;
};

template<class A1, class A2, int I> struct storage3<A1, A2, arg<I> > : public storage2<A1, A2>
{
    typedef storage2<A1, A2> inherited;

    storage3(A1 a1, A2 a2, arg<I>) : storage2<A1, A2>(a1, a2) {}

    template<class V> void accept(V& v) const
    {
        inherited::accept(v);
    }

    static arg<I> a3_() { return arg<I>(); }
};

template<class A1, class A2, int I> struct storage3<A1, A2, arg<I> (*)()> : public storage2<A1, A2>
{
    typedef storage2<A1, A2> inherited;

    storage3(A1 a1, A2 a2, arg<I> (*)()) : storage2<A1, A2>(a1, a2) {}

    template<class V> void accept(V& v) const
    {
        inherited::accept(v);
    }

    static arg<I> a3_() { return arg<I>(); }
};

template<class A1, class A2, class A3, class A4> struct storage4 : public storage3<A1, A2, A3>
{
    typedef storage3<A1, A2, A3> inherited;

    storage4(A1 a1, A2 a2, A3 a3, A4 a4) : storage3<A1, A2, A3>(a1, a2, a3), a4_(a4) {}

    template<class V> void accept(V & v) const
    {
        inherited::accept(v);
        visit_each(v, a4_, 0);
    }

    A4 a4_;
};

template<class A1, class A2, class A3, int I> struct storage4<A1, A2, A3, arg<I> > : public storage3<A1, A2, A3>
{
    typedef storage3<A1, A2, A3> inherited;

    storage4(A1 a1, A2 a2, A3 a3, arg<I>) : storage3<A1, A2, A3>(a1, a2, a3) {}

    template<class V> void accept(V& v) const
    {
        inherited::accept(v);
    }

    static arg<I> a4_() { return arg<I>(); }
};

template<class A1, class A2, class A3, int I> struct storage4<A1, A2, A3, arg<I> (*)()> : public storage3<A1, A2, A3>
{
    typedef storage3<A1, A2, A3> inherited;

    storage4(A1 a1, A2 a2, A3 a3, arg<I> (*)()) : storage3<A1, A2, A3>(a1, a2, a3) {}

    template<class V> void accept(V& v) const
    {
        inherited::accept(v);
    }

    static arg<I> a4_() { return arg<I>(); }
};

template<class A1, class A2, class A3, class A4, class A5>
struct storage5 : public storage4<A1, A2, A3, A4>
{
    typedef storage4<A1, A2, A3, A4> inherited;

    storage5(A1 a1, A2 a2, A3 a3, A4 a4, A5 a5) : storage4<A1, A2, A3, A4>(a1, a2, a3, a4), a5_(a5) {}

    template<class V> void accept(V& v) const
    {
        inherited::accept(v);
        visit_each(v, a5_, 0);
    }

    A5 a5_;
};

template<class A1, class A2, class A3, class A4, int I>
struct storage5<A1, A2, A3, A4, arg<I> > : public storage4<A1, A2, A3, A4>
{
    typedef storage4<A1, A2, A3, A4> inherited;

    storage5(A1 a1, A2 a2, A3 a3, A4 a4, arg<I>) : storage4<A1, A2, A3, A4>(a1, a2, a3, a4) {}

    template<class V> void accept(V& v) const
    {
        inherited::accept(v);
    }

    static arg<I> a5_() { return arg<I>(); }
};

template<class A1, class A2, class A3, class A4, int I>
struct storage5<A1, A2, A3, A4, arg<I> (*)()> : public storage4<A1, A2, A3, A4>
{
    typedef storage4<A1, A2, A3, A4> inherited;

    storage5(A1 a1, A2 a2, A3 a3, A4 a4, arg<I> (*)()) : storage4<A1, A2, A3, A4>(a1, a2, a3, a4) {}

    template<class V> void accept(V& v) const
    {
        inherited::accept(v);
    }

    static arg<I> a5_() { return arg<I>(); }
};

template<class A1, class A2, class A3, class A4, class A5, class A6>
struct storage6 : public storage5<A1, A2, A3, A4, A5>
{
    typedef storage5<A1, A2, A3, A4, A5> inherited;

    storage6(A1 a1, A2 a2, A3 a3, A4 a4, A5 a5, A6 a6) : storage5<A1, A2, A3, A4, A5>(a1, a2, a3, a4, a5), a6_(a6) {}

    template<class V> void accept(V& v) const
    {
        inherited::accept(v);
        visit_each(v, a6_, 0);
    }

    A6 a6_;
};

template<class A1, class A2, class A3, class A4, class A5, int I>
struct storage6<A1, A2, A3, A4, A5, arg<I> > : public storage5<A1, A2, A3, A4, A5>
{
    typedef storage5<A1, A2, A3, A4, A5> inherited;

    storage6(A1 a1, A2 a2, A3 a3, A4 a4, A5 a5, arg<I>): storage5<A1, A2, A3, A4, A5>(a1, a2, a3, a4, a5) {}

    template<class V> void accept(V& v) const
    {
        inherited::accept(v);
    }

    static arg<I> a6_() { return arg<I>(); }
};

template<class A1, class A2, class A3, class A4, class A5, int I>
struct storage6<A1, A2, A3, A4, A5, arg<I> (*)()> : public storage5<A1, A2, A3, A4, A5>
{
    typedef storage5<A1, A2, A3, A4, A5> inherited;

    storage6(A1 a1, A2 a2, A3 a3, A4 a4, A5 a5, arg<I> (*)()) : storage5<A1, A2, A3, A4, A5>(a1, a2, a3, a4, a5) {}

    template<class V> void accept(V& v) const
    {
        inherited::accept(v);
    }

    static arg<I> a6_() { return arg<I>(); }
};

template<class A1, class A2, class A3, class A4, class A5, class A6, class A7>
struct storage7 : public storage6<A1, A2, A3, A4, A5, A6>
{
    typedef storage6<A1, A2, A3, A4, A5, A6> inherited;

    storage7(A1 a1, A2 a2, A3 a3, A4 a4, A5 a5, A6 a6, A7 a7) : storage6<A1, A2, A3, A4, A5, A6>( a1, a2, a3, a4, a5, a6 ), a7_(a7) {}

    template<class V> void accept(V& v) const
    {
        inherited::accept(v);
        visit_each(v, a7_, 0);
    }

    A7 a7_;
};

template<class A1, class A2, class A3, class A4, class A5, class A6, int I>
struct storage7<A1, A2, A3, A4, A5, A6, arg<I> > : public storage6<A1, A2, A3, A4, A5, A6>
{
    typedef storage6<A1, A2, A3, A4, A5, A6> inherited;

    storage7(A1 a1, A2 a2, A3 a3, A4 a4, A5 a5, A6 a6, arg<I>) : storage6<A1, A2, A3, A4, A5, A6>(a1, a2, a3, a4, a5, a6) {}

    template<class V> void accept(V& v) const
    {
        inherited::accept(v);
    }

    static arg<I> a7_() { return arg<I>(); }
};

template<class A1, class A2, class A3, class A4, class A5, class A6, int I>
struct storage7<A1, A2, A3, A4, A5, A6, arg<I> (*)()> : public storage6<A1, A2, A3, A4, A5, A6>
{
    typedef storage6<A1, A2, A3, A4, A5, A6> inherited;

    storage7(A1 a1, A2 a2, A3 a3, A4 a4, A5 a5, A6 a6, arg<I> (*)()) : storage6<A1, A2, A3, A4, A5, A6>(a1, a2, a3, a4, a5, a6) {}

    template<class V> void accept(V& v) const
    {
        inherited::accept(v);
    }

    static arg<I> a7_() { return arg<I>(); }
};

template<class A1, class A2, class A3, class A4, class A5, class A6, class A7, class A8>
struct storage8 : public storage7<A1, A2, A3, A4, A5, A6, A7>
{
    typedef storage7<A1, A2, A3, A4, A5, A6, A7> inherited;

    storage8(A1 a1, A2 a2, A3 a3, A4 a4, A5 a5, A6 a6, A7 a7, A8 a8)
		: storage7<A1, A2, A3, A4, A5, A6, A7>(a1, a2, a3, a4, a5, a6, a7), a8_(a8) {}

    template<class V> void accept(V& v) const
    {
        inherited::accept(v);
        visit_each(v, a8_, 0);
    }

    A8 a8_;
};

template<class A1, class A2, class A3, class A4, class A5, class A6, class A7, int I>
struct storage8<A1, A2, A3, A4, A5, A6, A7, arg<I> > : public storage7<A1, A2, A3, A4, A5, A6, A7>
{
    typedef storage7<A1, A2, A3, A4, A5, A6, A7> inherited;

    storage8(A1 a1, A2 a2, A3 a3, A4 a4, A5 a5, A6 a6, A7 a7, arg<I>)
		: storage7<A1, A2, A3, A4, A5, A6, A7>(a1, a2, a3, a4, a5, a6, a7) {}

    template<class V> void accept(V& v) const
    {
        inherited::accept(v);
    }

    static arg<I> a8_() { return arg<I>(); }
};

template<class A1, class A2, class A3, class A4, class A5, class A6, class A7, int I>
struct storage8<A1, A2, A3, A4, A5, A6, A7, arg<I> (*)()> : public storage7< A1, A2, A3, A4, A5, A6, A7>
{
    typedef storage7<A1, A2, A3, A4, A5, A6, A7> inherited;

    storage8(A1 a1, A2 a2, A3 a3, A4 a4, A5 a5, A6 a6, A7 a7, arg<I> (*)())
		: storage7<A1, A2, A3, A4, A5, A6, A7>(a1, a2, a3, a4, a5, a6, a7) {}

    template<class V> void accept(V& v) const
    {
        inherited::accept(v);
    }

    static arg<I> a8_() { return arg<I>(); }
};

template<class A1, class A2, class A3, class A4, class A5, class A6, class A7, class A8, class A9>
struct storage9 : public storage8<A1, A2, A3, A4, A5, A6, A7, A8>
{
    typedef storage8<A1, A2, A3, A4, A5, A6, A7, A8> inherited;

    storage9(A1 a1, A2 a2, A3 a3, A4 a4, A5 a5, A6 a6, A7 a7, A8 a8, A9 a9)
		: storage8<A1, A2, A3, A4, A5, A6, A7, A8>(a1, a2, a3, a4, a5, a6, a7, a8), a9_(a9) {}

    template<class V> void accept(V& v) const
    {
        inherited::accept(v);
        visit_each(v, a9_, 0);
    }

    A9 a9_;
};

template<class A1, class A2, class A3, class A4, class A5, class A6, class A7, class A8, int I>
struct storage9< A1, A2, A3, A4, A5, A6, A7, A8, arg<I> > : public storage8<A1, A2, A3, A4, A5, A6, A7, A8>
{
    typedef storage8<A1, A2, A3, A4, A5, A6, A7, A8> inherited;

    storage9(A1 a1, A2 a2, A3 a3, A4 a4, A5 a5, A6 a6, A7 a7, A8 a8, arg<I>)
		: storage8<A1, A2, A3, A4, A5, A6, A7, A8>(a1, a2, a3, a4, a5, a6, a7, a8) {}

    template<class V> void accept(V& v) const
    {
        inherited::accept(v);
    }

    static arg<I> a9_() { return arg<I>(); }
};

template<class A1, class A2, class A3, class A4, class A5, class A6, class A7, class A8, int I>
struct storage9<A1, A2, A3, A4, A5, A6, A7, A8, arg<I> (*)()> : public storage8<A1, A2, A3, A4, A5, A6, A7, A8>
{
    typedef storage8<A1, A2, A3, A4, A5, A6, A7, A8> inherited;

    storage9(A1 a1, A2 a2, A3 a3, A4 a4, A5 a5, A6 a6, A7 a7, A8 a8, arg<I> (*)())
		: storage8<A1, A2, A3, A4, A5, A6, A7, A8>(a1, a2, a3, a4, a5, a6, a7, a8) {}

    template<class V> void accept(V& v) const
    {
        inherited::accept(v);
    }

    static arg<I> a9_() { return arg<I>(); }
};



// return functors
template <class R, class F, class L>
class bind_t {
	F f_;
	L l_;
public:
	typedef typename result_traits<R, F>::type result_type;

	bind_t(F f, const L& l) : f_(f), l_(l) {}

	result_type operator()()
	{
		return f_(l_);
	}

	result_type operator()() const
	{
		return f_(l_);
	}
};

} // namespace shand::_bi

// bind
template <class R, class F, class P1>
_bi::bind_t<R, F, P1> bind(F f, P1 p1)
{
	return _bi::bind_t<R, F, P1>(f, p1);
}

} // namespace shand

#endif // SHAND_BIND_INCLUDE

