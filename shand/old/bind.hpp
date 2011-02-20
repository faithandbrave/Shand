#ifndef SHAND_BIND_INCLUDE
#define SHAND_BIND_INCLUDE

#include "./mem_fn.hpp"

namespace shand {
    // arg
    template<int I> class arg { };

    template<int I> bool operator==(arg<I> const &, arg<I> const &)
    {
        return true;
    }

    // type
    template<class T> class type { };

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

        // storage1
        template<class A1>
		struct storage1 {
            explicit storage1(A1 a1) : a1_(a1) { }
            A1 a1_;
        };

        template<int I>
		struct storage1<shand::arg<I> > {
            explicit storage1(shand::arg<I>) { }
            static shand::arg<I> a1_() { return shand::arg<I>(); }
        };

        // storage2
        template<class A1, class A2>
		struct storage2 : public storage1<A1> {
            storage2(A1 a1, A2 a2) : storage1<A1>(a1), a2_(a2) {}
            A2 a2_;
        };

        template<class A1, int I>
		struct storage2<A1, shand::arg<I> > : public storage1<A1> {
            storage2(A1 a1, shand::arg<I>) : storage1<A1>(a1) { }
            static shand::arg<I> a2_() { return shand::arg<I>(); }
        };

        // storage3
        template<class A1, class A2, class A3>
		struct storage3 : public storage2<A1, A2> {
            storage3(A1 a1, A2 a2, A3 a3) : storage2<A1, A2>(a1, a2), a3_(a3) { }
            A3 a3_;
        };

        template<class A1, class A2, int I>
		struct storage3<A1, A2, shand::arg<I> > : public storage2<A1, A2> {
            storage3(A1 a1, A2 a2, shand::arg<I>) : storage2<A1, A2>(a1, a2) { }
            static shand::arg<I> a3_() { return shand::arg<I>(); }
        };

		// storage4
        template<class A1, class A2, class A3, class A4>
		struct storage4 : public storage3<A1, A2, A3> {
            storage4(A1 a1, A2 a2, A3 a3, A4 a4) : storage3<A1, A2, A3>(a1, a2, a3), a4_(a4) { }
            A4 a4_;
        };

        template<class A1, class A2, class A3, int I>
		struct storage4<A1, A2, A3, shand::arg<I> > : public storage3<A1, A2, A3> {
            storage4(A1 a1, A2 a2, A3 a3, shand::arg<I>) : storage3<A1, A2, A3>(a1, a2, a3) { }
            static shand::arg<I> a4_() { return shand::arg<I>(); }
        };

		// storage5
        template<class A1, class A2, class A3, class A4, class A5>
		struct storage5 : public storage4<A1, A2, A3, A4> {
            storage5(A1 a1, A2 a2, A3 a3, A4 a4, A5 a5) : storage4<A1, A2, A3, A4>(a1, a2, a3, a4), a5_(a5) { }
            A5 a5_;
        };

        template<class A1, class A2, class A3, class A4, int I>
		struct storage5<A1, A2, A3, A4, shand::arg<I> > : public storage4<A1, A2, A3, A4> {
            storage5(A1 a1, A2 a2, A3 a3, A4 a4, shand::arg<I>) : storage4<A1, A2, A3, A4>(a1, a2, a3, a4) { }
            static shand::arg<I> a5_() { return shand::arg<I>(); }
        };

		// storage6
        template<class A1, class A2, class A3, class A4, class A5, class A6>
		struct storage6 : public storage5<A1, A2, A3, A4, A5> {
            storage6(A1 a1, A2 a2, A3 a3, A4 a4, A5 a5, A6 a6)
				: storage5<A1, A2, A3, A4, A5>(a1, a2, a3, a4, a5), a6_(a6) { }
            A6 a6_;
        };

        template<class A1, class A2, class A3, class A4, class A5, int I>
		struct storage6<A1, A2, A3, A4, A5, shand::arg<I> > : public storage5<A1, A2, A3, A4, A5> {
            storage6(A1 a1, A2 a2, A3 a3, A4 a4, A5 a5, shand::arg<I>)
				: storage5<A1, A2, A3, A4, A5>(a1, a2, a3, a4, a5) { }
            static shand::arg<I> a6_() { return shand::arg<I>(); }
        };

		// storage7
        template<class A1, class A2, class A3, class A4, class A5, class A6, class A7>
		struct storage7 : public storage6<A1, A2, A3, A4, A5, A6> {
            storage7(A1 a1, A2 a2, A3 a3, A4 a4, A5 a5, A6 a6, A7 a7)
				: storage6<A1, A2, A3, A4, A5, A6>(a1, a2, a3, a4, a5, a6), a7_(a7) { }
            A7 a7_;
        };

        template<class A1, class A2, class A3, class A4, class A5, class A6, int I>
		struct storage7<A1, A2, A3, A4, A5, A6, shand::arg<I> > : public storage6<A1, A2, A3, A4, A5, A6> {
            storage7(A1 a1, A2 a2, A3 a3, A4 a4, A5 a5, A6 a6, shand::arg<I>)
				: storage6<A1, A2, A3, A4, A5, A6>(a1, a2, a3, a4, a5, a6) { }
            static shand::arg<I> a7_() { return shand::arg<I>(); }
        };

		// storage8
        template<class A1, class A2, class A3, class A4, class A5, class A6, class A7, class A8>
		struct storage8 : public storage7<A1, A2, A3, A4, A5, A6, A7> {
            storage8(A1 a1, A2 a2, A3 a3, A4 a4, A5 a5, A6 a6, A7 a7, A8 a8)
				: storage7<A1, A2, A3, A4, A5, A6, A7>(a1, a2, a3, a4, a5, a6, a7), a8_(a8) { }
            A8 a8_;
        };

        template<class A1, class A2, class A3, class A4, class A5, class A6, class A7, int I>
		struct storage8<A1, A2, A3, A4, A5, A6, A7, shand::arg<I> > : public storage7<A1, A2, A3, A4, A5, A6, A7> {
            storage8(A1 a1, A2 a2, A3 a3, A4 a4, A5 a5, A6 a6, A7 a7, shand::arg<I>)
				: storage7<A1, A2, A3, A4, A5, A6, A7>(a1, a2, a3, a4, a5, a6, a7) { }
            static shand::arg<I> a8_() { return shand::arg<I>(); }
        };

		// storage9
        template<class A1, class A2, class A3, class A4, class A5, class A6, class A7, class A8, class A9>
		struct storage9 : public storage8<A1, A2, A3, A4, A5, A6, A7, A8> {
            storage9(A1 a1, A2 a2, A3 a3, A4 a4, A5 a5, A6 a6, A7 a7, A8 a8, A9 a9)
				: storage8<A1, A2, A3, A4, A5, A6, A7, A8>(a1, a2, a3, a4, a5, a6, a7, a8), a9_(a9) { }
            A9 a9_;
        };

        template<class A1, class A2, class A3, class A4, class A5, class A6, class A7, class A8, int I>
		struct storage9<A1, A2, A3, A4, A5, A6, A7, A8, shand::arg<I> > : public storage8<A1, A2, A3, A4, A5, A6, A7, A8> {
            storage9(A1 a1, A2 a2, A3 a3, A4 a4, A5 a5, A6 a6, A7 a7, A8 a8, shand::arg<I>)
				: storage8<A1, A2, A3, A4, A5, A6, A7, A8>(a1, a2, a3, a4, a5, a6, a7, a8) { }
            static shand::arg<I> a9_() { return shand::arg<I>(); }
        };

        // list0
        class list0 {
        public:
            template<class T> T & operator[] (T& v) const { return v; }

            template<class R, class F, class A> R operator()(type<R>, F& f, A&)
            {
                return f();
            }
        };

        // list1
        template<class A1>
		class list1 : private storage1<A1> {
        private:
            typedef storage1<A1> base_type;

        public:
            explicit list1(A1 a1) : base_type(a1) { }

			A1 operator[] (shand::arg<1>) const { return base_type::a1_; }

            A1 operator[] (shand::arg<1> (*) ()) const { return base_type::a1_; }
            template<class T> T& operator[] (T& v) const { return v; }

            template<class R, class F, class A> R operator()(type<R>, F& f, A& a)
            {
                return f(a[base_type::a1_]);
            }
        };

        // list2
        template<class A1, class A2>
		class list2 : private storage2<A1, A2> {
        private:
            typedef storage2<A1, A2> base_type;

        public:
            list2(A1 a1, A2 a2) : base_type(a1, a2) {}

			A1 operator[] (shand::arg<1>) const { return base_type::a1_; }
			A2 operator[] (shand::arg<2>) const { return base_type::a2_; }

            A1 operator[] (shand::arg<1> (*)()) const { return base_type::a1_; }
            A2 operator[] (shand::arg<2> (*)()) const { return base_type::a2_; }
            template<class T> T operator[] (T v) const { return v; }

            template<class R, class F, class A> R operator()(type<R>, F& f, A& a)
            {
                return f(a[base_type::a1_], a[base_type::a2_]);
            }
        };

        // list3
        template<class A1, class A2, class A3>
		class list3 : private storage3<A1, A2, A3> {
        private:
            typedef storage3<A1, A2, A3> base_type;

        public:
            list3(A1 a1, A2 a2, A3 a3) : base_type(a1, a2, a3) {}

			A1 operator[] (shand::arg<1>) const { return base_type::a1_; }
			A2 operator[] (shand::arg<2>) const { return base_type::a2_; }
			A3 operator[] (shand::arg<3>) const { return base_type::a3_; }

            A1 operator[] (shand::arg<1> (*)()) const { return base_type::a1_; }
            A2 operator[] (shand::arg<2> (*)()) const { return base_type::a2_; }
            A3 operator[] (shand::arg<3> (*)()) const { return base_type::a3_; }
            template<class T> T & operator[] (T& v) const { return v; }

            template<class R, class F, class A> R operator()(type<R>, F& f, A& a)
            {
                return f(a[base_type::a1_], a[base_type::a2_], a[base_type::a3_]);
            }
        };

		// list4
        template<class A1, class A2, class A3, class A4>
		class list4 : private storage4<A1, A2, A3, A4> {
        private:
            typedef storage4<A1, A2, A3, A4> base_type;

        public:
            list4(A1 a1, A2 a2, A3 a3, A4 a4) : base_type(a1, a2, a3, a4) {}

			A1 operator[] (shand::arg<1>) const { return base_type::a1_; }
			A2 operator[] (shand::arg<2>) const { return base_type::a2_; }
			A3 operator[] (shand::arg<3>) const { return base_type::a3_; }
			A4 operator[] (shand::arg<4>) const { return base_type::a4_; }

            A1 operator[] (shand::arg<1> (*)()) const { return base_type::a1_; }
            A2 operator[] (shand::arg<2> (*)()) const { return base_type::a2_; }
            A3 operator[] (shand::arg<3> (*)()) const { return base_type::a3_; }
			A4 operator[] (shand::arg<4> (*)()) const { return base_type::a4_; }
            template<class T> T & operator[] (T& v) const { return v; }

            template<class R, class F, class A> R operator()(type<R>, F& f, A& a)
            {
				return f(a[base_type::a1_], a[base_type::a2_], a[base_type::a3_],
						 a[base_type::a4_]);
            }
        };

		// list5
        template<class A1, class A2, class A3, class A4, class A5>
		class list5 : private storage5<A1, A2, A3, A4, A5> {
        private:
            typedef storage5<A1, A2, A3, A4, A5> base_type;

        public:
            list5(A1 a1, A2 a2, A3 a3, A4 a4, A5 a5) : base_type(a1, a2, a3, a4, a5) {}

			A1 operator[] (shand::arg<1>) const { return base_type::a1_; }
			A2 operator[] (shand::arg<2>) const { return base_type::a2_; }
			A3 operator[] (shand::arg<3>) const { return base_type::a3_; }
			A4 operator[] (shand::arg<4>) const { return base_type::a4_; }
			A5 operator[] (shand::arg<5>) const { return base_type::a5_; }

            A1 operator[] (shand::arg<1> (*)()) const { return base_type::a1_; }
            A2 operator[] (shand::arg<2> (*)()) const { return base_type::a2_; }
            A3 operator[] (shand::arg<3> (*)()) const { return base_type::a3_; }
			A4 operator[] (shand::arg<4> (*)()) const { return base_type::a4_; }
			A5 operator[] (shand::arg<5> (*)()) const { return base_type::a5_; }
            template<class T> T & operator[] (T& v) const { return v; }

            template<class R, class F, class A> R operator()(type<R>, F& f, A& a)
            {
				return f(a[base_type::a1_], a[base_type::a2_], a[base_type::a3_],
						 a[base_type::a4_], a[base_type::a5_]);
            }
        };

		// list6
        template<class A1, class A2, class A3, class A4, class A5, class A6>
		class list6 : private storage6<A1, A2, A3, A4, A5, A6> {
        private:
            typedef storage6<A1, A2, A3, A4, A5, A6> base_type;

        public:
            list6(A1 a1, A2 a2, A3 a3, A4 a4, A5 a5, A6 a6) : base_type(a1, a2, a3, a4, a5, a6) {}

			A1 operator[] (shand::arg<1>) const { return base_type::a1_; }
			A2 operator[] (shand::arg<2>) const { return base_type::a2_; }
			A3 operator[] (shand::arg<3>) const { return base_type::a3_; }
			A4 operator[] (shand::arg<4>) const { return base_type::a4_; }
			A5 operator[] (shand::arg<5>) const { return base_type::a5_; }
			A6 operator[] (shand::arg<6>) const { return base_type::a6_; }

            A1 operator[] (shand::arg<1> (*)()) const { return base_type::a1_; }
            A2 operator[] (shand::arg<2> (*)()) const { return base_type::a2_; }
            A3 operator[] (shand::arg<3> (*)()) const { return base_type::a3_; }
			A4 operator[] (shand::arg<4> (*)()) const { return base_type::a4_; }
			A5 operator[] (shand::arg<5> (*)()) const { return base_type::a5_; }
			A6 operator[] (shand::arg<6> (*)()) const { return base_type::a6_; }
            template<class T> T & operator[] (T& v) const { return v; }

            template<class R, class F, class A> R operator()(type<R>, F& f, A& a)
            {
				return f(a[base_type::a1_], a[base_type::a2_], a[base_type::a3_],
						 a[base_type::a4_], a[base_type::a5_], a[base_type::a6_]);
            }
        };

		// list7
        template<class A1, class A2, class A3, class A4, class A5, class A6, class A7>
		class list7 : private storage7<A1, A2, A3, A4, A5, A6, A7> {
        private:
            typedef storage7<A1, A2, A3, A4, A5, A6, A7> base_type;

        public:
            list7(A1 a1, A2 a2, A3 a3, A4 a4, A5 a5, A6 a6, A7 a7) : base_type(a1, a2, a3, a4, a5, a6, a7) {}

			A1 operator[] (shand::arg<1>) const { return base_type::a1_; }
			A2 operator[] (shand::arg<2>) const { return base_type::a2_; }
			A3 operator[] (shand::arg<3>) const { return base_type::a3_; }
			A4 operator[] (shand::arg<4>) const { return base_type::a4_; }
			A5 operator[] (shand::arg<5>) const { return base_type::a5_; }
			A6 operator[] (shand::arg<6>) const { return base_type::a6_; }
			A7 operator[] (shand::arg<7>) const { return base_type::a7_; }

            A1 operator[] (shand::arg<1> (*)()) const { return base_type::a1_; }
            A2 operator[] (shand::arg<2> (*)()) const { return base_type::a2_; }
            A3 operator[] (shand::arg<3> (*)()) const { return base_type::a3_; }
			A4 operator[] (shand::arg<4> (*)()) const { return base_type::a4_; }
			A5 operator[] (shand::arg<5> (*)()) const { return base_type::a5_; }
			A6 operator[] (shand::arg<6> (*)()) const { return base_type::a6_; }
			A7 operator[] (shand::arg<7> (*)()) const { return base_type::a7_; }
            template<class T> T & operator[] (T& v) const { return v; }

            template<class R, class F, class A> R operator()(type<R>, F& f, A& a)
            {
				return f(a[base_type::a1_], a[base_type::a2_], a[base_type::a3_],
						 a[base_type::a4_], a[base_type::a5_], a[base_type::a6_],
						 a[base_type::a7_]);
            }
        };

		// list8
        template<class A1, class A2, class A3, class A4, class A5, class A6, class A7, class A8>
		class list8 : private storage8<A1, A2, A3, A4, A5, A6, A7, A8> {
        private:
            typedef storage8<A1, A2, A3, A4, A5, A6, A7, A8> base_type;

        public:
            list8(A1 a1, A2 a2, A3 a3, A4 a4, A5 a5, A6 a6, A7 a7, A8 a8)
				: base_type(a1, a2, a3, a4, a5, a6, a7, a8) {}

			A1 operator[] (shand::arg<1>) const { return base_type::a1_; }
			A2 operator[] (shand::arg<2>) const { return base_type::a2_; }
			A3 operator[] (shand::arg<3>) const { return base_type::a3_; }
			A4 operator[] (shand::arg<4>) const { return base_type::a4_; }
			A5 operator[] (shand::arg<5>) const { return base_type::a5_; }
			A6 operator[] (shand::arg<6>) const { return base_type::a6_; }
			A7 operator[] (shand::arg<7>) const { return base_type::a7_; }
			A8 operator[] (shand::arg<8>) const { return base_type::a8_; }

            A1 operator[] (shand::arg<1> (*)()) const { return base_type::a1_; }
            A2 operator[] (shand::arg<2> (*)()) const { return base_type::a2_; }
            A3 operator[] (shand::arg<3> (*)()) const { return base_type::a3_; }
			A4 operator[] (shand::arg<4> (*)()) const { return base_type::a4_; }
			A5 operator[] (shand::arg<5> (*)()) const { return base_type::a5_; }
			A6 operator[] (shand::arg<6> (*)()) const { return base_type::a6_; }
			A7 operator[] (shand::arg<7> (*)()) const { return base_type::a7_; }
			A8 operator[] (shand::arg<8> (*)()) const { return base_type::a8_; }
            template<class T> T & operator[] (T& v) const { return v; }

            template<class R, class F, class A> R operator()(type<R>, F& f, A& a)
            {
				return f(a[base_type::a1_], a[base_type::a2_], a[base_type::a3_],
						 a[base_type::a4_], a[base_type::a5_], a[base_type::a6_],
						 a[base_type::a7_], a[base_type::a8_]);
            }
        };

		// list9
        template<class A1, class A2, class A3, class A4, class A5, class A6, class A7, class A8, class A9>
		class list9 : private storage9<A1, A2, A3, A4, A5, A6, A7, A8, A9> {
        private:
            typedef storage9<A1, A2, A3, A4, A5, A6, A7, A8, A9> base_type;

        public:
            list9(A1 a1, A2 a2, A3 a3, A4 a4, A5 a5, A6 a6, A7 a7, A8 a8, A9 a9)
				: base_type(a1, a2, a3, a4, a5, a6, a7, a8, a9) {}

			A1 operator[] (shand::arg<1>) const { return base_type::a1_; }
			A2 operator[] (shand::arg<2>) const { return base_type::a2_; }
			A3 operator[] (shand::arg<3>) const { return base_type::a3_; }
			A4 operator[] (shand::arg<4>) const { return base_type::a4_; }
			A5 operator[] (shand::arg<5>) const { return base_type::a5_; }
			A6 operator[] (shand::arg<6>) const { return base_type::a6_; }
			A7 operator[] (shand::arg<7>) const { return base_type::a7_; }
			A8 operator[] (shand::arg<8>) const { return base_type::a8_; }
			A9 operator[] (shand::arg<9>) const { return base_type::a9_; }

            A1 operator[] (shand::arg<1> (*)()) const { return base_type::a1_; }
            A2 operator[] (shand::arg<2> (*)()) const { return base_type::a2_; }
            A3 operator[] (shand::arg<3> (*)()) const { return base_type::a3_; }
			A4 operator[] (shand::arg<4> (*)()) const { return base_type::a4_; }
			A5 operator[] (shand::arg<5> (*)()) const { return base_type::a5_; }
			A6 operator[] (shand::arg<6> (*)()) const { return base_type::a6_; }
			A7 operator[] (shand::arg<7> (*)()) const { return base_type::a7_; }
			A8 operator[] (shand::arg<8> (*)()) const { return base_type::a8_; }
			A9 operator[] (shand::arg<9> (*)()) const { return base_type::a9_; }
            template<class T> T & operator[] (T& v) const { return v; }

            template<class R, class F, class A> R operator()(type<R>, F& f, A& a)
            {
				return f(a[base_type::a1_], a[base_type::a2_], a[base_type::a3_],
						 a[base_type::a4_], a[base_type::a5_], a[base_type::a6_],
						 a[base_type::a7_], a[base_type::a8_], a[base_type::a9_]);
            }
        };

        // bind_t
        template <class R, class F, class L>
		class bind_t {
        public:
			typedef typename result_traits<R, F>::type result_type;

            bind_t(F f, L const & l) : f_(f), l_(l) {}

            result_type operator()()
            {
                list0 a;
                return l_(type<result_type>(), f_, a);
            }

            template<class A1>
			result_type operator()(A1 a1)
            {
                list1<A1> a(a1);
                return l_(type<result_type>(), f_, list1<A1>(a1));
            }

            template<class A1, class A2>
			result_type operator()(A1 a1, A2 a2)
            {
                list2<A1, A2> a(a1, a2);
                return l_(type<result_type>(), f_, a);
            }

            template<class A1, class A2, class A3>
			result_type operator()(A1 a1, A2 a2, A3 a3)
            {
                list3<A1, A2, A3> a(a1, a2, a3);
                return l_(type<result_type>(), f_, a);
            }

			template<class A1, class A2, class A3, class A4>
			result_type operator()(A1 a1, A2 a2, A3 a3, A4 a4)
            {
                list4<A1, A2, A3, A4> a(a1, a2, a3, a4);
                return l_(type<result_type>(), f_, a);
            }

			template<class A1, class A2, class A3, class A4, class A5>
			result_type operator()(A1 a1, A2 a2, A3 a3, A4 a4, A5 a5)
            {
                list5<A1, A2, A3, A4, A5> a(a1, a2, a3, a4, a5);
                return l_(type<result_type>(), f_, a);
            }

			template<class A1, class A2, class A3, class A4, class A5, class A6>
			result_type operator()(A1 a1, A2 a2, A3 a3, A4 a4, A5 a5, A6 a6)
            {
                list6<A1, A2, A3, A4, A5, A6> a(a1, a2, a3, a4, a5, a6);
                return l_(type<result_type>(), f_, a);
            }

			template<class A1, class A2, class A3, class A4, class A5, class A6, class A7>
			result_type operator()(A1 a1, A2 a2, A3 a3, A4 a4, A5 a5, A6 a6, A7 a7)
            {
                list7<A1, A2, A3, A4, A5, A6, A7> a(a1, a2, a3, a4, a5, a6, a7);
                return l_(type<result_type>(), f_, a);
            }

			template<class A1, class A2, class A3, class A4, class A5, class A6, class A7, class A8>
			result_type operator()(A1 a1, A2 a2, A3 a3, A4 a4, A5 a5, A6 a6, A7 a7, A8 a8)
            {
                list8<A1, A2, A3, A4, A5, A6, A7, A8> a(a1, a2, a3, a4, a5, a6, a7, a8);
                return l_(type<result_type>(), f_, a);
            }

			template<class A1, class A2, class A3, class A4, class A5, class A6, class A7, class A8, class A9>
			result_type operator()(A1 a1, A2 a2, A3 a3, A4 a4, A5 a5, A6 a6, A7 a7, A8 a8, A9 a9)
            {
                list9<A1, A2, A3, A4, A5, A6, A7, A8, A9> a(a1, a2, a3, a4, a5, a6, a7, a8, a9);
                return l_(type<result_type>(), f_, a);
            }

        private:
            F f_;
            L l_;
        };

    } // namespace shand::_bi

    // bind for function
	template<class R>
	_bi::bind_t<R, R (*)(), _bi::list0>
		bind(R (*f)())
    {
        typedef R (*F)();
        typedef _bi::list0 list_type;
        return _bi::bind_t<R, F, list_type> (f, list_type());
    }

    template<class R, class B1, class A1>
    _bi::bind_t<R, R (*)(B1), _bi::list1<A1> >
        bind(R (*f)(B1), A1 a1)
    {
        typedef R (*F)(B1);
        typedef typename _bi::list1<A1> list_type;
        return _bi::bind_t<R, F, list_type>(f, list_type(a1));
    }

    template<class R, class B1, class B2, class A1, class A2>
    _bi::bind_t<R, R (*)(B1, B2), typename _bi::list2<A1, A2> >
        bind(R (*f)(B1, B2), A1 a1, A2 a2)
    {
        typedef R (*F)(B1, B2);
        typedef typename _bi::list2<A1, A2> list_type;
        return _bi::bind_t<R, F, list_type>(f, list_type(a1, a2));
    }

    template<class R, class B1, class B2, class B3, class A1, class A2, class A3>
    _bi::bind_t<R, R (*)(B1, B2, B3), typename _bi::list3<A1, A2, A3> >
        bind(R (*f)(B1, B2, B3), A1 a1, A2 a2, A3 a3)
    {
        typedef R (*F)(B1, B2, B3);
        typedef typename _bi::list3<A1, A2, A3> list_type;
        return _bi::bind_t<R, F, list_type>(f, list_type(a1, a2, a3));
    }

	template<class R, class B1, class B2, class B3, class B4, class A1, class A2, class A3, class A4>
    _bi::bind_t<R, R (*)(B1, B2, B3, B4), typename _bi::list4<A1, A2, A3, A4> >
        bind(R (*f)(B1, B2, B3, B4), A1 a1, A2 a2, A3 a3, A4 a4)
    {
        typedef R (*F)(B1, B2, B3, B4);
        typedef typename _bi::list4<A1, A2, A3, A4> list_type;
        return _bi::bind_t<R, F, list_type>(f, list_type(a1, a2, a3, a4));
    }

	template<class R, class B1, class B2, class B3, class B4, class B5,
					  class A1, class A2, class A3, class A4, class A5>
    _bi::bind_t<R, R (*)(B1, B2, B3, B4, B5), typename _bi::list5<A1, A2, A3, A4, A5> >
        bind(R (*f)(B1, B2, B3, B4, B5), A1 a1, A2 a2, A3 a3, A4 a4, A5 a5)
    {
        typedef R (*F)(B1, B2, B3, B4, B5);
        typedef typename _bi::list5<A1, A2, A3, A4, A5> list_type;
        return _bi::bind_t<R, F, list_type>(f, list_type(a1, a2, a3, a4, a5));
    }

	template<class R, class B1, class B2, class B3, class B4, class B5, class B6,
					  class A1, class A2, class A3, class A4, class A5, class A6>
    _bi::bind_t<R, R (*)(B1, B2, B3, B4, B5, B6), typename _bi::list6<A1, A2, A3, A4, A5, A6> >
        bind(R (*f)(B1, B2, B3, B4, B5, B6), A1 a1, A2 a2, A3 a3, A4 a4, A5 a5, A6 a6)
    {
        typedef R (*F)(B1, B2, B3, B4, B5, B6);
        typedef typename _bi::list6<A1, A2, A3, A4, A5, A6> list_type;
        return _bi::bind_t<R, F, list_type>(f, list_type(a1, a2, a3, a4, a5, a6));
    }

	template<class R, class B1, class B2, class B3, class B4, class B5, class B6, class B7,
					  class A1, class A2, class A3, class A4, class A5, class A6, class A7>
    _bi::bind_t<R, R (*)(B1, B2, B3, B4, B5, B6, B7), typename _bi::list7<A1, A2, A3, A4, A5, A6, A7> >
        bind(R (*f)(B1, B2, B3, B4, B5, B6, B7), A1 a1, A2 a2, A3 a3, A4 a4, A5 a5, A6 a6, A7 a7)
    {
        typedef R (*F)(B1, B2, B3, B4, B5, B6, B7);
        typedef typename _bi::list7<A1, A2, A3, A4, A5, A6, A7> list_type;
        return _bi::bind_t<R, F, list_type>(f, list_type(a1, a2, a3, a4, a5, a6, a7));
    }

	template<class R, class B1, class B2, class B3, class B4, class B5, class B6, class B7, class B8,
					  class A1, class A2, class A3, class A4, class A5, class A6, class A7, class A8>
    _bi::bind_t<R, R (*)(B1, B2, B3, B4, B5, B6, B7, B8), typename _bi::list8<A1, A2, A3, A4, A5, A6, A7, A8> >
        bind(R (*f)(B1, B2, B3, B4, B5, B6, B7, B8), A1 a1, A2 a2, A3 a3, A4 a4, A5 a5, A6 a6, A7 a7, A8 a8)
    {
        typedef R (*F)(B1, B2, B3, B4, B5, B6, B7, B8);
        typedef typename _bi::list8<A1, A2, A3, A4, A5, A6, A7, A8> list_type;
        return _bi::bind_t<R, F, list_type>(f, list_type(a1, a2, a3, a4, a5, a6, a7, a8));
    }

	template<class R, class B1, class B2, class B3, class B4, class B5, class B6, class B7, class B8, class B9,
					  class A1, class A2, class A3, class A4, class A5, class A6, class A7, class A8, class A9>
    _bi::bind_t<R, R (*)(B1, B2, B3, B4, B5, B6, B7, B8, B9), typename _bi::list9<A1, A2, A3, A4, A5, A6, A7, A8, A9> >
        bind(R (*f)(B1, B2, B3, B4, B5, B6, B7, B8, B9), A1 a1, A2 a2, A3 a3, A4 a4, A5 a5, A6 a6, A7 a7, A8 a8, A9 a9)
    {
        typedef R (*F)(B1, B2, B3, B4, B5, B6, B7, B8, B9);
        typedef typename _bi::list9<A1, A2, A3, A4, A5, A6, A7, A8, A9> list_type;
        return _bi::bind_t<R, F, list_type>(f, list_type(a1, a2, a3, a4, a5, a6, a7, a8, a9));
    }

	// adaptable function objects
	template<class F>
	_bi::bind_t<_bi::unspecified, F, _bi::list0>
		bind(F f)
	{
		typedef _bi::list0 list_type;
        return _bi::bind_t<_bi::unspecified, F, list_type> (f, list_type());
	}

	template<class F, class A1>
	_bi::bind_t<_bi::unspecified, F, typename _bi::list1<A1>>
		bind(F f, A1 a1)
	{
		typedef typename _bi::list1<A1> list_type;
		return _bi::bind_t<_bi::unspecified, F, list_type>(f, list_type(a1));
	}

	template<class F, class A1, class A2>
	_bi::bind_t<_bi::unspecified, F, typename _bi::list2<A1, A2>>
		bind(F f, A1 a1, A2 a2)
	{
		typedef typename _bi::list2<A1, A2> list_type;
		return _bi::bind_t<_bi::unspecified, F, list_type>(f, list_type(a1, a2));
	}

	template<class F, class A1, class A2, class A3>
	_bi::bind_t<_bi::unspecified, F, typename _bi::list3<A1, A2, A3> >
		bind(F f, A1 a1, A2 a2, A3 a3)
	{
		typedef typename _bi::list3<A1, A2, A3> list_type;
		return _bi::bind_t<_bi::unspecified, F, list_type>(f, list_type(a1, a2, a3));
	}

	template<class F, class A1, class A2, class A3, class A4>
	_bi::bind_t<_bi::unspecified, F, typename _bi::list4<A1, A2, A3, A4> >
		bind(F f, A1 a1, A2 a2, A3 a3, A4 a4)
	{
		typedef typename _bi::list4<A1, A2, A3, A4> list_type;
		return _bi::bind_t<_bi::unspecified, F, list_type>(f, list_type(a1, a2, a3, a4));
	}

	template<class F, class A1, class A2, class A3, class A4, class A5>
	_bi::bind_t<_bi::unspecified, F, typename _bi::list5<A1, A2, A3, A4, A5> >
		bind(F f, A1 a1, A2 a2, A3 a3, A4 a4, A5 a5)
	{
		typedef typename _bi::list5<A1, A2, A3, A4, A5> list_type;
		return _bi::bind_t<_bi::unspecified, F, list_type>(f, list_type(a1, a2, a3, a4, a5));
	}

	template<class F, class A1, class A2, class A3, class A4, class A5, class A6>
	_bi::bind_t<_bi::unspecified, F, typename _bi::list6<A1, A2, A3, A4, A5, A6> >
		bind(F f, A1 a1, A2 a2, A3 a3, A4 a4, A5 a5, A6 a6)
	{
		typedef typename _bi::list6<A1, A2, A3, A4, A5, A6> list_type;
		return _bi::bind_t<_bi::unspecified, F, list_type>(f, list_type(a1, a2, a3, a4, a5, a6));
	}

	template<class F, class A1, class A2, class A3, class A4, class A5, class A6, class A7>
	_bi::bind_t<_bi::unspecified, F, typename _bi::list7<A1, A2, A3, A4, A5, A6, A7> >
		bind(F f, A1 a1, A2 a2, A3 a3, A4 a4, A5 a5, A6 a6, A7 a7)
	{
		typedef typename _bi::list7<A1, A2, A3, A4, A5, A6, A7> list_type;
		return _bi::bind_t<_bi::unspecified, F, list_type>(f, list_type(a1, a2, a3, a4, a5, a6, a7));
	}

	template<class F, class A1, class A2, class A3, class A4, class A5, class A6, class A7, class A8>
	_bi::bind_t<_bi::unspecified, F, typename _bi::list8<A1, A2, A3, A4, A5, A6, A7, A8> >
		bind(F f, A1 a1, A2 a2, A3 a3, A4 a4, A5 a5, A6 a6, A7 a7, A8 a8)
	{
		typedef typename _bi::list8<A1, A2, A3, A4, A5, A6, A7, A8> list_type;
		return _bi::bind_t<_bi::unspecified, F, list_type>(f, list_type(a1, a2, a3, a4, a5, a6, a7, a8));
	}

	template<class F, class A1, class A2, class A3, class A4, class A5, class A6, class A7, class A8, class A9>
	_bi::bind_t<_bi::unspecified, F, typename _bi::list9<A1, A2, A3, A4, A5, A6, A7, A8, A9> >
		bind(F f, A1 a1, A2 a2, A3 a3, A4 a4, A5 a5, A6 a6, A7 a7, A8 a8, A9 a9)
	{
		typedef typename _bi::list9<A1, A2, A3, A4, A5, A6, A7, A8, A9> list_type;
		return _bi::bind_t<_bi::unspecified, F, list_type>(f, list_type(a1, a2, a3, a4, a5, a6, a7, a8, a9));
	}

	// member function
	template<class R, class T, class A1>
	_bi::bind_t<R, mem_fn_t<R, T, R (T::*)()>, _bi::list1<A1> >
		bind(R (T::*f)(), A1 a1)
    {
        typedef mem_fn_t<R, T, R (T::*)()> F;
        typedef typename _bi::list1<A1> list_type;
		return _bi::bind_t<R, F, list_type>(mem_fn(f), list_type(a1));
    }

	template<class R, class T, class A1>
	_bi::bind_t<R, const mem_fn_t<R, T, R (T::*)() const>, _bi::list1<const A1&> >
		bind(R (T::*f)() const, A1 a1)
    {
        typedef const mem_fn_t<R, T, R (T::*)() const> F;
        typedef typename _bi::list1<const A1&> list_type;
		return _bi::bind_t<R, F, list_type>(mem_fn(f), list_type(a1));
    }

	template<class R, class T, class A1,
			 class B2,
			 class A2>
	_bi::bind_t<R, mem_fn_t<R, T, R (T::*)(B2)>, _bi::list2<A1, A2> >
		bind(R (T::*f)(B2), A1 a1, A2 a2)
    {
        typedef mem_fn_t<R, T, R (T::*)(B2)> F;
        typedef typename _bi::list2<A1, A2> list_type;
		return _bi::bind_t<R, F, list_type>(mem_fn(f), list_type(a1, a2));
    }

	template<class R, class T, class A1,
			 class B2,
			 class A2>
	_bi::bind_t<R, const mem_fn_t<R, T, R (T::*)(B2) const>, _bi::list2<const A1&, A2> >
		bind(R (T::*f)(B2) const, A1 a1, A2 a2)
    {
        typedef const mem_fn_t<R, T, R (T::*)(B2) const> F;
        typedef typename _bi::list2<const A1&, A2> list_type;
		return _bi::bind_t<R, F, list_type>(mem_fn(f), list_type(a1, a2));
    }

	template<class R, class T, class A1,
			 class B2, class B3,
			 class A2, class A3>
	_bi::bind_t<R, mem_fn_t<R, T, R (T::*)(B2, B3)>, _bi::list3<A1, A2, A3> >
		bind(R (T::*f)(B2, B3), A1 a1, A2 a2, A3 a3)
    {
        typedef mem_fn_t<R, T, R (T::*)(B2, B3)> F;
        typedef typename _bi::list3<A1, A2, A3> list_type;
		return _bi::bind_t<R, F, list_type>(mem_fn(f), list_type(a1, a2, a3));
    }

	template<class R, class T, class A1,
			 class B2, class B3,
			 class A2, class A3>
	_bi::bind_t<R, const mem_fn_t<R, T, R (T::*)(B2, B3) const>, _bi::list3<const A1&, A2, A3> >
		bind(R (T::*f)(B2, B3) const, A1 a1, A2 a2, A3 a3)
    {
        typedef const mem_fn_t<R, T, R (T::*)(B2, B3) const> F;
        typedef typename _bi::list3<const A1&, A2, A3> list_type;
		return _bi::bind_t<R, F, list_type>(mem_fn(f), list_type(a1, a2, a3));
    }

	template<class R, class T, class A1,
			 class B2, class B3, class B4,
			 class A2, class A3, class A4>
	_bi::bind_t<R, mem_fn_t<R, T, R (T::*)(B2, B3, B4)>, _bi::list4<A1, A2, A3, A4> >
		bind(R (T::*f)(B2, B3, B4), A1 a1, A2 a2, A3 a3, A4 a4)
    {
        typedef mem_fn_t<R, T, R (T::*)(B2, B3, B4)> F;
        typedef typename _bi::list4<A1, A2, A3, A4> list_type;
		return _bi::bind_t<R, F, list_type>(mem_fn(f), list_type(a1, a2, a3, a4));
    }

	template<class R, class T, class A1,
			 class B2, class B3, class B4,
			 class A2, class A3, class A4>
	_bi::bind_t<R, const mem_fn_t<R, T, R (T::*)(B2, B3, B4) const>, _bi::list4<const A1&, A2, A3, A4> >
		bind(R (T::*f)(B2, B3, B4) const, A1 a1, A2 a2, A3 a3, A4 a4)
    {
        typedef const mem_fn_t<R, T, R (T::*)(B2, B3, B4) const> F;
        typedef typename _bi::list4<const A1&, A2, A3, A4> list_type;
		return _bi::bind_t<R, F, list_type>(mem_fn(f), list_type(a1, a2, a3, a4));
    }

	template<class R, class T, class A1,
			 class B2, class B3, class B4, class B5,
			 class A2, class A3, class A4, class A5>
	_bi::bind_t<R, mem_fn_t<R, T, R (T::*)(B2, B3, B4, B5)>, _bi::list5<A1, A2, A3, A4, A5> >
		bind(R (T::*f)(B2, B3, B4, B5), A1 a1, A2 a2, A3 a3, A4 a4, A5 a5)
    {
        typedef mem_fn_t<R, T, R (T::*)(B2, B3, B4, B5)> F;
        typedef typename _bi::list5<A1, A2, A3, A4, A5> list_type;
		return _bi::bind_t<R, F, list_type>(mem_fn(f), list_type(a1, a2, a3, a4, a5));
    }

	template<class R, class T, class A1,
			 class B2, class B3, class B4, class B5,
			 class A2, class A3, class A4, class A5>
	_bi::bind_t<R, const mem_fn_t<R, T, R (T::*)(B2, B3, B4, B5) const>, _bi::list5<const A1&, A2, A3, A4, A5> >
		bind(R (T::*f)(B2, B3, B4, B5) const, A1 a1, A2 a2, A3 a3, A4 a4, A5 a5)
    {
        typedef const mem_fn_t<R, T, R (T::*)(B2, B3, B4, B5) const> F;
        typedef typename _bi::list5<const A1&, A2, A3, A4, A5> list_type;
		return _bi::bind_t<R, F, list_type>(mem_fn(f), list_type(a1, a2, a3, a4, a5));
    }

	template<class R, class T, class A1,
			 class B2, class B3, class B4, class B5, class B6,
			 class A2, class A3, class A4, class A5, class A6>
	_bi::bind_t<R, mem_fn_t<R, T, R (T::*)(B2, B3, B4, B5, B6)>, _bi::list6<A1, A2, A3, A4, A5, A6> >
		bind(R (T::*f)(B2, B3, B4, B5, B6), A1 a1, A2 a2, A3 a3, A4 a4, A5 a5, A6 a6)
    {
        typedef mem_fn_t<R, T, R (T::*)(B2, B3, B4, B5, B6)> F;
        typedef typename _bi::list6<A1, A2, A3, A4, A5, A6> list_type;
		return _bi::bind_t<R, F, list_type>(mem_fn(f), list_type(a1, a2, a3, a4, a5, a6));
    }

	template<class R, class T, class A1,
			 class B2, class B3, class B4, class B5, class B6,
			 class A2, class A3, class A4, class A5, class A6>
	_bi::bind_t<R, const mem_fn_t<R, T, R (T::*)(B2, B3, B4, B5, B6) const>, _bi::list6<const A1&, A2, A3, A4, A5, A6> >
		bind(R (T::*f)(B2, B3, B4, B5, B6) const, A1 a1, A2 a2, A3 a3, A4 a4, A5 a5, A6 a6)
    {
        typedef const mem_fn_t<R, T, R (T::*)(B2, B3, B4, B5, B6) const> F;
        typedef typename _bi::list6<const A1&, A2, A3, A4, A5, A6> list_type;
		return _bi::bind_t<R, F, list_type>(mem_fn(f), list_type(a1, a2, a3, a4, a5, a6));
    }

	template<class R, class T, class A1,
			 class B2, class B3, class B4, class B5, class B6, class B7,
			 class A2, class A3, class A4, class A5, class A6, class A7>
	_bi::bind_t<R, mem_fn_t<R, T, R (T::*)(B2, B3, B4, B5, B6, B7)>, _bi::list7<A1, A2, A3, A4, A5, A6, A7> >
		bind(R (T::*f)(B2, B3, B4, B5, B6, B7), A1 a1, A2 a2, A3 a3, A4 a4, A5 a5, A6 a6, A7 a7)
    {
        typedef mem_fn_t<R, T, R (T::*)(B2, B3, B4, B5, B6, B7)> F;
        typedef typename _bi::list7<A1, A2, A3, A4, A5, A6, A7> list_type;
		return _bi::bind_t<R, F, list_type>(mem_fn(f), list_type(a1, a2, a3, a4, a5, a6, a7));
    }

	template<class R, class T, class A1,
			 class B2, class B3, class B4, class B5, class B6, class B7,
			 class A2, class A3, class A4, class A5, class A6, class A7>
	_bi::bind_t<R, const mem_fn_t<R, T, R (T::*)(B2, B3, B4, B5, B6, B7) const>, _bi::list7<const A1&, A2, A3, A4, A5, A6, A7> >
		bind(R (T::*f)(B2, B3, B4, B5, B6, B7) const, A1 a1, A2 a2, A3 a3, A4 a4, A5 a5, A6 a6, A7 a7)
    {
        typedef const mem_fn_t<R, T, R (T::*)(B2, B3, B4, B5, B6, B7) const> F;
        typedef typename _bi::list7<const A1&, A2, A3, A4, A5, A6, A7> list_type;
		return _bi::bind_t<R, F, list_type>(mem_fn(f), list_type(a1, a2, a3, a4, a5, a6, a7));
    }

	template<class R, class T, class A1,
			 class B2, class B3, class B4, class B5, class B6, class B7, class B8,
			 class A2, class A3, class A4, class A5, class A6, class A7, class A8>
	_bi::bind_t<R, mem_fn_t<R, T, R (T::*)(B2, B3, B4, B5, B6, B7, B8)>, _bi::list8<A1, A2, A3, A4, A5, A6, A7, A8> >
		bind(R (T::*f)(B2, B3, B4, B5, B6, B7, B8), A1 a1, A2 a2, A3 a3, A4 a4, A5 a5, A6 a6, A7 a7, A8 a8)
    {
        typedef mem_fn_t<R, T, R (T::*)(B2, B3, B4, B5, B6, B7, B8)> F;
        typedef typename _bi::list8<A1, A2, A3, A4, A5, A6, A7, A8> list_type;
		return _bi::bind_t<R, F, list_type>(mem_fn(f), list_type(a1, a2, a3, a4, a5, a6, a7, a8));
    }

	template<class R, class T, class A1,
			 class B2, class B3, class B4, class B5, class B6, class B7, class B8,
			 class A2, class A3, class A4, class A5, class A6, class A7, class A8>
	_bi::bind_t<R, const mem_fn_t<R, T, R (T::*)(B2, B3, B4, B5, B6, B7, B8) const>, _bi::list8<const A1&, A2, A3, A4, A5, A6, A7, A8> >
		bind(R (T::*f)(B2, B3, B4, B5, B6, B7, B8) const, A1 a1, A2 a2, A3 a3, A4 a4, A5 a5, A6 a6, A7 a7, A8 a8)
    {
        typedef const mem_fn_t<R, T, R (T::*)(B2, B3, B4, B5, B6, B7, B8) const> F;
        typedef typename _bi::list8<const A1&, A2, A3, A4, A5, A6, A7, A8> list_type;
		return _bi::bind_t<R, F, list_type>(mem_fn(f), list_type(a1, a2, a3, a4, a5, a6, a7, a8));
    }

	template<class R, class T, class A1,
			 class B2, class B3, class B4, class B5, class B6, class B7, class B8, class B9,
			 class A2, class A3, class A4, class A5, class A6, class A7, class A8, class A9>
	_bi::bind_t<R, mem_fn_t<R, T, R (T::*)(B2, B3, B4, B5, B6, B7, B8, B9)>, _bi::list9<A1, A2, A3, A4, A5, A6, A7, A8, A9> >
		bind(R (T::*f)(B2, B3, B4, B5, B6, B7, B8, B9), A1 a1, A2 a2, A3 a3, A4 a4, A5 a5, A6 a6, A7 a7, A8 a8, A9 a9)
    {
        typedef mem_fn_t<R, T, R (T::*)(B2, B3, B4, B5, B6, B7, B8, B9)> F;
        typedef typename _bi::list9<A1, A2, A3, A4, A5, A6, A7, A8, A9> list_type;
		return _bi::bind_t<R, F, list_type>(mem_fn(f), list_type(a1, a2, a3, a4, a5, a6, a7, a8, a9));
    }

	template<class R, class T, class A1,
			 class B2, class B3, class B4, class B5, class B6, class B7, class B8, class B9,
			 class A2, class A3, class A4, class A5, class A6, class A7, class A8, class A9>
	_bi::bind_t<R, const mem_fn_t<R, T, R (T::*)(B2, B3, B4, B5, B6, B7, B8, B9) const>, _bi::list9<const A1&, A2, A3, A4, A5, A6, A7, A8, A9> >
		bind(R (T::*f)(B2, B3, B4, B5, B6, B7, B8, B9) const, A1 a1, A2 a2, A3 a3, A4 a4, A5 a5, A6 a6, A7 a7, A8 a8, A9 a9)
    {
        typedef const mem_fn_t<R, T, R (T::*)(B2, B3, B4, B5, B6, B7, B8, B9) const> F;
        typedef typename _bi::list9<const A1&, A2, A3, A4, A5, A6, A7, A8, A9> list_type;
		return _bi::bind_t<R, F, list_type>(mem_fn(f), list_type(a1, a2, a3, a4, a5, a6, a7, a8, a9));
    }

} // namespace shand

namespace shand { namespace placeholders {
	static shand::arg<1> _1;
	static shand::arg<2> _2;
	static shand::arg<3> _3;
	static shand::arg<4> _4;
	static shand::arg<5> _5;
	static shand::arg<6> _6;
	static shand::arg<7> _7;
	static shand::arg<8> _8;
	static shand::arg<9> _9;
}} // namespace shand::placeholders


#endif // SHAND_BIND_INCLUDE


