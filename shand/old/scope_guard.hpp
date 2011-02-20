#ifndef SHAND_SCOPE_GUARD_INCLUDE
#define SHAND_SCOPE_GUARD_INCLUDE

namespace shand {

class scope_guard_impl_base {
public:
    scope_guard_impl_base() : dismissed_(false) {}

    void dismiss() const { dismissed_ = true; }
    void touch() const {}

protected:
    ~scope_guard_impl_base(){}

    scope_guard_impl_base(const scope_guard_impl_base& other)
        : dismissed_(other.dismissed_)
    {
        other.dismiss();
    }

    template <class J>
    static void safe_execute(J& j) { if(!j.dismissed_) j.execute(); }

    mutable bool dismissed_;

private:
    scope_guard_impl_base& operator=(const scope_guard_impl_base&);
};

typedef const scope_guard_impl_base& scope_guard;

template <class F>
class scope_guard_impl0:public scope_guard_impl_base {
public:
    scope_guard_impl0(F fun) : fun_(fun) {}
    ~scope_guard_impl0() { scope_guard_impl_base::safe_execute(*this); }
    void execute() { fun_(); }

protected:
    F fun_;
};

template <class F> 
inline scope_guard_impl0<F> make_guard(F fun)
{
    return scope_guard_impl0<F>(fun);
}

template <class F, class P1>
class scope_guard_impl1 : public scope_guard_impl_base {
public:
    scope_guard_impl1(F fun, P1 p1) : fun_(fun), p1_(p1) {}
    ~scope_guard_impl1() { scope_guard_impl_base::safe_execute(*this); }
    void execute() { fun_(p1_); }

protected:
    F        fun_;
    const P1 p1_;
};

template <class F, class P1>
inline scope_guard_impl1<F, P1> make_guard(F fun, P1 p1)
{
    return scope_guard_impl1<F, P1>(fun, p1);
}

template<class F, class P1, class P2>
class scope_guard_impl2 : public scope_guard_impl_base {
public:
    scope_guard_impl2(F fun, P1 p1, P2 p2) : fun_(fun), p1_(p1), p2_(p2) {}
    ~scope_guard_impl2(){ scope_guard_impl_base::safe_execute(*this); }
    void execute() { fun_(p1_, p2_); }

protected:
    F        fun_;
    const P1 p1_;
    const P2 p2_;
};

template <class F, class P1, class P2>
inline scope_guard_impl2<F, P1, P2> make_guard(F fun, P1 p1, P2 p2)
{
    return scope_guard_impl2<F, P1, P2>(fun, p1, p2);
}

template <class F, class P1, class P2, class P3>
class scope_guard_impl3 : public scope_guard_impl_base {
public:
    scope_guard_impl3(F fun, P1 p1, P2 p2, P3 p3) : fun_(fun), p1_(p1), p2_(p2), p3_(p3) {}
    ~scope_guard_impl3() { scope_guard_impl_base::safe_execute(*this); }
    void execute() { fun_(p1_, p2_, p3_); }

protected:
    F        fun_;
    const P1 p1_;
    const P2 p2_;
    const P3 p3_;
};

template <class F, class P1, class P2, class P3>
inline scope_guard_impl3<F, P1, P2, P3> make_guard(F fun, P1 p1, P2 p2, P3 p3)
{
    return scope_guard_impl3<F, P1, P2, P3>(fun, p1, p2, p3);
}

template <class F, class P1, class P2, class P3, class P4>
class scope_guard_impl4 : public scope_guard_impl_base {
public:
    scope_guard_impl4(F fun, P1 p1, P2 p2, P3 p3, P4 p4)
        : fun_(fun), p1_(p1), p2_(p2), p3_(p3), p4_(p4) {}
    ~scope_guard_impl4() { scope_guard_impl_base::safe_execute(*this); }
    void execute() { fun_(p1_,p2_,p3_,p4_); }

protected:
    F        fun_;
    const P1 p1_;
    const P2 p2_;
    const P3 p3_;
    const P4 p4_;
};

template <class F, class P1, class P2, class P3, class P4>
inline scope_guard_impl4<F, P1, P2, P3, P4> make_guard(F fun, P1 p1, P2 p2, P3 p3, P4 p4)
{
    return scope_guard_impl4<F, P1, P2, P3, P4>(fun, p1, p2, p3, p4);
}

template <class Obj, class MemFun>
class obj_scope_guard_impl0 : public scope_guard_impl_base {
public:
    obj_scope_guard_impl0(Obj& obj, MemFun mem_fun) : obj_(obj), mem_fun_(mem_fun) {}
    ~obj_scope_guard_impl0() { scope_guard_impl_base::safe_execute(*this); }
    void execute() { (obj_.*mem_fun_)(); }

protected:
    Obj&   obj_;
    MemFun mem_fun_;
};

template <class Obj, class MemFun>
inline obj_scope_guard_impl0<Obj, MemFun> make_obj_guard(Obj& obj, MemFun mem_fun)
{
    return obj_scope_guard_impl0<Obj,MemFun>(obj,mem_fun);
}

template <class Obj, class MemFun, class P1>
class obj_scope_guard_impl1 : public scope_guard_impl_base {
public:
    obj_scope_guard_impl1(Obj& obj, MemFun mem_fun, P1 p1)
        : obj_(obj), mem_fun_(mem_fun), p1_(p1) {}
    ~obj_scope_guard_impl1() { scope_guard_impl_base::safe_execute(*this); }
    void execute() { (obj_.*mem_fun_)(p1_); }

protected:
    Obj&     obj_;
    MemFun   mem_fun_;
    const P1 p1_;
};

template <class Obj, class MemFun, class P1>
inline obj_scope_guard_impl1<Obj, MemFun, P1> make_obj_guard(Obj& obj, MemFun mem_fun, P1 p1)
{
    return obj_scope_guard_impl1<Obj, MemFun, P1>(obj, mem_fun, p1);
}

template <class Obj, class MemFun, class P1, class P2>
class obj_scope_guard_impl2:public scope_guard_impl_base {
public:
    obj_scope_guard_impl2(Obj& obj, MemFun mem_fun, P1 p1, P2 p2)
        : obj_(obj), mem_fun_(mem_fun), p1_(p1), p2_(p2) {}
    ~obj_scope_guard_impl2() { scope_guard_impl_base::safe_execute(*this); }
    void execute() { (obj_.*mem_fun_)(p1_,p2_); }

protected:
    Obj&     obj_;
    MemFun   mem_fun_;
    const P1 p1_;
    const P2 p2_;
};

template <class Obj, class MemFun, class P1, class P2>
inline obj_scope_guard_impl2<Obj, MemFun, P1, P2>
make_obj_guard(Obj& obj, MemFun mem_fun, P1 p1, P2 p2)
{
    return obj_scope_guard_impl2<Obj, MemFun, P1, P2>(obj, mem_fun, p1, p2);
}

template <class Obj, class MemFun, class P1, class P2, class P3>
class obj_scope_guard_impl3 : public scope_guard_impl_base {
public:
    obj_scope_guard_impl3(Obj& obj, MemFun mem_fun, P1 p1, P2 p2, P3 p3)
        : obj_(obj), mem_fun_(mem_fun), p1_(p1), p2_(p2), p3_(p3) {}
    ~obj_scope_guard_impl3() { scope_guard_impl_base::safe_execute(*this); }
    void execute() { (obj_.*mem_fun_)(p1_,p2_,p3_); }

protected:
    Obj&     obj_;
    MemFun   mem_fun_;
    const P1 p1_;
    const P2 p2_;
    const P3 p3_;
};

template <class Obj, class MemFun, class P1, class P2, class P3>
inline obj_scope_guard_impl3<Obj, MemFun, P1, P2, P3>
make_obj_guard(Obj& obj, MemFun mem_fun, P1 p1, P2 p2, P3 p3)
{
    return obj_scope_guard_impl3<Obj, MemFun, P1, P2, P3>(obj, mem_fun, p1, p2, p3);
}


} // namespace shand

#endif // SHAND_SCOPE_GUARD_INCLUDE

