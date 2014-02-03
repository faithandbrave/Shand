#ifndef SHAND_SHARED_POINTER_INCLUDE
#define SHAND_SHARED_POINTER_INCLUDE

// (C) Copyright Greg Colvin and Beman Dawes 1998, 1999.
// Copyright (c) 2001-2008 Peter Dimov
// Copyright Akira Takahashi 2007
// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

//------------------------------------------------------------------//
//                                                                  //
//  クラス名 : shared_ptr<Type>                                     //
//  用    途 : 参照カウント付きスマートポインタ                     //
//                                                                  //
// Version : 1.00 2007/06/22 作成                                   //
//           1.10 2007/07/12 カスタム削除子を指定できるようにした   //
//           1.11 2007/07/18 カスタム削除子作成時の例外処理追加     //
//                           shared_ptr<void>を作成できるようにした //
//           1.12 2007/10/25 カスタム削除子のポインタの持ち方変更   //
//           1.13 2007/10/29 reset追加                              //
//                                                                  //
//------------------------------------------------------------------//

#include <functional> // less

namespace shand {

namespace detail {

// shared_ptr<void>を作成するために参照型作成
template<class T> struct shared_ptr_traits
{
    typedef T& reference;
};

template<> struct shared_ptr_traits<void>
{
    typedef void reference;
};

#if !defined(_MSC_VER) || (_MSC_VER > 1300)  // 1300 == VC++ 7.0

template<> struct shared_ptr_traits<void const>
{
    typedef void reference;
};

template<> struct shared_ptr_traits<void volatile>
{
    typedef void reference;
};

template<> struct shared_ptr_traits<void const volatile>
{
    typedef void reference;
};

#endif

// カスタム削除子
template <typename Type>
class shared_deleter_base {
public:
    shared_deleter_base() {}
    virtual ~shared_deleter_base() {}
    virtual void destroy() = 0;
};

template <typename Type, typename Deleter>
class shared_deleter : public shared_deleter_base<Type> {
    Type*   object_;
    Deleter deleter_;
public:
    shared_deleter(Type *object, Deleter deleter)
        : object_(object), deleter_(deleter) {}

    virtual ~shared_deleter() {}

    virtual void destroy()
    {
        deleter_(object_);
    }
};

} // namespace detail


template <class Type>
class shared_ptr {
    Type*                               object_;    // ポインタ
    int*                                counter_;   // 参照カウンタ
    detail::shared_deleter_base<Type>*  deleter_;   // カスタム削除子

public:
    typedef Type element_type;
    typedef Type value_type;
    typedef Type* pointer;
    typedef typename detail::shared_ptr_traits<Type>::reference reference;

    shared_ptr()
        : object_(0), counter_(new int(1)), deleter_(0) {}

    shared_ptr(const shared_ptr& src)
        : object_(0), counter_(0), deleter_(0) { set(src); }

    explicit shared_ptr(Type* object)
        : object_(object), counter_(new int(1)), deleter_(0) {}

    // 削除子指定のコンストラクタ
    template <class Deleter>
    shared_ptr(Type* object, Deleter deleter)
        : object_(object), counter_(new int(1)), deleter_(0)
    {
        try {
            deleter_ = new detail::shared_deleter<Type, Deleter>(object_, deleter);
        }
        catch(...) {
            deleter(object_);
            delete counter_;
            throw;
        }
    }

    ~shared_ptr() { release(); }

    void reset()
    {
        release();
    }

    template <class Object>
    void reset(Object *object)
    {
        release();
        object_     = object;
        counter_    = new int(1);
        deleter_    = 0;
    }

    template <class Object, class Deleter>
    void reset(Object *object, Deleter deleter)
    {
        reset(object);

        try {
            deleter_ = new detail::shared_deleter<Type, Deleter>(object_, deleter);
        }
        catch(...) {
            deleter(object_);
            delete counter_;
            throw;
        }
    }

    // ポインタの取得
    Type* get() const { return object_; }

    // 参照カウント取得
    long use_count() const
    {
        if (!counter_)
            return 0; 
        return *counter_;
    }

    // 参照先が1つか判断
    bool unique() const { return use_count() == 1; }

    shared_ptr& operator=(const shared_ptr& rhs) { set(rhs); return *this; }

    Type*     operator->() const { return get(); }
    reference operator*()  const { return *get(); }
    bool      operator!()  const { return object_ == 0; }

    operator bool() const { return object_ != 0; }

private:
    void set(const shared_ptr& src)
    {
        if (this != &src) {
            // 解放して新しいスマートポインタを作成
            release();
            object_  = src.object_;
            counter_ = src.counter_;
            deleter_ = src.deleter_;

            // 参照カウントを増やす
            if (counter_ != 0)
                ++*counter_;
        }
    }

    void release()
    {
        if (counter_ != 0 && --*counter_ == 0) {
            if (deleter_) {
                deleter_->destroy();
                delete deleter_;
            }
            else {
                delete object_;
            }
            delete counter_;
        }
        object_ = 0;
        counter_ = 0;
        deleter_ = 0;
    }

};

template<class Type>
inline bool operator==(shared_ptr<Type> const & lhs, shared_ptr<Type> const & rhs)
{
    return lhs.get() == rhs.get();
}

template<class Type>
inline bool operator!=(shared_ptr<Type> const & lhs, shared_ptr<Type> const & rhs)
{
    return lhs.get() != rhs.get();
}

// map格納用
template<class Type>
inline bool operator<(shared_ptr<Type> const & lhs, shared_ptr<Type> const & rhs)
{
    return std::less<Type*>()(lhs.get(), rhs.get());
}


} // namespace shand

#endif // SHAND_SHARED_POINTER_INCLUDE

