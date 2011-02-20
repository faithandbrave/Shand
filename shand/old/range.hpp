#ifndef SHAND_RANGE_INCLUDE
#define SHAND_RANGE_INCLUDE

#include <functional>   // std::tr1::result_of
#include <type_traits>  // std::tr1::remove_cv, std::tr1::remove_reference

// TR1ÉâÉCÉuÉâÉäÇ™Ç»Ç¢ä¬ã´Ç≈ÇÕÅ™ÇÃë„ÇÌÇËÇ…Ç±Ç¡Çø
//#include <boost/tr1/functional.hpp>
//#include <boost/tr1/type_traits.hpp>

#include <numeric>      // std::accumulate
#include <algorithm>
#include <vector>

namespace shand {
    namespace range {
        // range_iterator
        template <class Container>
        struct range_iterator {
            typedef typename Container::iterator type;
        };

        template <class Container>
        struct range_iterator< const Container > {
            typedef typename Container::const_iterator type;
        };

        template <class T, std::size_t N>
        struct range_iterator< T[N] > {
            typedef T* type;
        };

        template <class T, std::size_t N>
        struct range_iterator< const T[N] > {
            typedef const T* type;
        };

        template<>
        struct range_iterator< char* > {
            typedef char* type;
        };

        // range_value
        template <class Container>
        struct range_value {
            typedef typename Container::value_type type;
        };

        template <class T, std::size_t N>
        struct range_value< T[N] > {
            typedef T type;
        };

        // begin
        template <class Container>
        inline typename Container::iterator begin(Container& c)
        {
            return c.begin();
        }

        template <class Container>
        inline typename Container::const_iterator begin(const Container& c)
        {
            return c.begin();
        }

        template <class T, int N>
        inline T* begin(T (&ar)[N])
        {
            return ar;
        }

        // end
        template <class Container>
        inline typename Container::iterator end(Container& c)
        {
            return c.end();
        }

        template <class Container>
        inline typename Container::const_iterator end(const Container& c)
        {
            return c.end();
        }

        template <class T, std::size_t N>
        inline T* end(T (&ar)[N])
        {
            return ar + N;
        }

        // result_type
        template <class Signature>
        struct argument_of;

        template <class R, class Arg>
        struct argument_of<R(Arg)> {
            typedef Arg type;
        };

        template <class T>
        class copy_argument {
            typedef typename argument_of<T>::type                           argument_type;
            typedef typename std::tr1::remove_cv<argument_type>::type       non_cv_type;
            typedef typename std::tr1::remove_reference<non_cv_type>::type  non_reference_type;
        public:
            typedef non_reference_type type;
        };

        template <class Signature>
        struct argument_vector {
            typedef std::vector<typename range_value<typename copy_argument<Signature>::type>::type> type;
        };

        template <class Range>
        struct result_vector {
            typedef std::vector<typename range_value<Range>::type> type;
        };

        // count_
        struct count_t {
            typedef std::size_t result_type;

            template <class Range>
            std::size_t call(const Range& r) const
            {
                return std::distance(begin(r), end(r));
            }
        };
        const count_t count_ = {};

        // is_empty_
        struct is_empty_t {
            typedef bool result_type;

            template <class Range>
            bool call(const Range& r) const
            {
                return (r|count_) == 0;
            }
        };
        const is_empty_t is_empty_ = {};

        // sort_
        template <class Compare>
        class comp_sort_t {
            Compare comp_;
        public:
            template <class Signature>
            struct result : public copy_argument<Signature> {};

            comp_sort_t(Compare comp)
                : comp_(comp) {}

            template <class Range>
            Range call(const Range& r) const
            {
                Range result(r);
                std::sort(begin(result), end(result), comp_);
                return result;
            }
        };

        class sort_t {
        public:
            template <class Signature>
            struct result : public copy_argument<Signature> {};

            template <class Range>
            Range call(const Range& r) const
            {
                Range result(r);
                std::sort(begin(result), end(result));
                return result;
            }

            template <class Compare>
            comp_sort_t<Compare> operator()(Compare comp) const
            {
                return comp_sort_t<Compare>(comp);
            }
        };
        const sort_t sort_ = {};

        // reverse
        struct reverse_t {
            template <class Signature>
            struct result : public copy_argument<Signature> {};

            template <class Range>
            Range call(const Range& r) const
            {
                Range result(r);
                std::reverse(begin(result), end(result));
                return result;
            }
        };
        const reverse_t reverse_ = {};

        // transform_
        template <class Range, class Func>
        class transform_result {
            typedef typename range_value<Range>::type argument_type;
            typedef typename std::tr1::result_of<Func(argument_type)>::type func_result_type;
        public:
            typedef std::vector<func_result_type> type;
        };

        template <class Func>
        class transform_t {
            Func func_;
        public:
            transform_t(Func func)
                : func_(func) {}

            template <class Signature>
            struct result : public transform_result<typename copy_argument<Signature>::type, Func> {};

            template <class Range>
            typename transform_result<Range, Func>::type
                call(const Range& r) const
            {
                typename transform_result<Range, Func>::type result;
                std::transform(begin(r), end(r), std::back_inserter(result), func_);
                return result;
            }
        };

        template <class Func>
        inline transform_t<Func> transform_(Func func)
        {
            return func;
        }

        // for_each_
        template <class Func>
        class for_each_t {
            Func func_;
        public:
            for_each_t(Func func)
                : func_(func) {}

            typedef void result_type;

            template <class Range>
            void call(const Range& r) const
            {
                for_each(begin(r), end(r), func_);
            }

            template <class Range>
            void call(Range& r) const
            {
                for_each(begin(r), end(r), func_);
            }
        };

        template <class Func>
        inline for_each_t<Func> for_each_(Func func)
        {
            return func;
        }

        // filter_
        template <class Predicate>
        class filter_t {
            Predicate pred_;
        public:
            filter_t(Predicate pred)
                : pred_(pred) {}

            template <class Signature>
            struct result : public argument_vector<Signature> {};

            template <class Range>
            typename result_vector<Range>::type call(const Range& r) const
            {
                typename result_vector<Range>::type result;

                for (typename range_iterator<const Range>::type first = begin(r), last = end(r);
                     first != last; ++first) {
                     if (pred_(*first))
                         result.push_back(*first);
                }

                return result;
            }
        };

        template <class Predicate>
        inline filter_t<Predicate> filter_(Predicate pred)
        {
            return pred;
        }

        // take_
        class take_ {
            std::size_t count_;
        public:
            explicit take_(std::size_t count)
                : count_(count) {}

            template <class Signature>
            struct result : public argument_vector<Signature> {};

            template <class Range>
            typename result_vector<Range>::type call(const Range& r) const
            {
                typename result_vector<Range>::type result;
                take(begin(r), end(r), std::back_inserter(result), count_);
                return result;
            }

            template <class InputIterator, class OutputIterator>
            static void take(InputIterator first, InputIterator last, OutputIterator result, std::size_t count)
            {
                while (first != last && count-- > 0) {
                    *result = *first;
                    ++result;
                    ++first;
                }
            }
        };

        // take_while_
        template <class Predicate>
        class take_while_t {
            Predicate pred_;
        public:
            take_while_t(Predicate pred)
                : pred_(pred) {}

            template <class Signature>
            struct result : public argument_vector<Signature> {};

            template <class Range>
            typename result_vector<Range>::type call(const Range& r) const
            {
                typename result_vector<Range>::type result;
                take_while(begin(r), end(r), std::back_inserter(result), pred_);
                return result;
            }

            template <class InputIterator, class OutputIterator, class Predicate_>
            static void take_while(InputIterator first, InputIterator last, OutputIterator result, Predicate_ pred)
            {
                while (first != last && pred(*first)) {
                    *result = *first;
                    ++result;
                    ++first;
                }
            }
        };

        template <class Predicate>
        inline take_while_t<Predicate> take_while_(Predicate pred)
        {
            return pred;
        }

        // drop_
        class drop_ {
            std::size_t count_;
        public:
            explicit drop_(std::size_t count)
                : count_(count) {}

            template <class Signature>
            struct result : public argument_vector<Signature> {};

            template <class Range>
            typename result_vector<Range>::type call(const Range& r) const
            {
                typename result_vector<Range>::type result;
                drop(begin(r), end(r), std::back_inserter(result), count_);
                return result;
            }

            template <class InputIterator, class OutputIterator>
            static void drop(InputIterator first, InputIterator last, OutputIterator result, std::size_t count)
            {
                while (first != last && count > 0) {
                    ++first;
                    --count;
                }

                while (first != last) {
                    *result = *first;
                    ++result;
                    ++first;
                }
            }
        };

        // drop_while_
        template <class Predicate>
        class drop_while_t {
            Predicate pred_;
        public:
            drop_while_t(Predicate pred)
                : pred_(pred) {}

            template <class Signature>
            struct result : public argument_vector<Signature> {};

            template <class Range>
            typename result_vector<Range>::type call(const Range& r) const
            {
                typename result_vector<Range>::type result;
                drop_while(begin(r), end(r), std::back_inserter(result), pred_);
                return result;
            }

            template <class InputIterator, class OutputIterator, class Predicate_>
            static void drop_while(InputIterator first, InputIterator last, OutputIterator result, Predicate_ pred)
            {
                while (first != last && pred(*first)) {
                    ++first;
                }

                while (first != last) {
                    *result = *first;
                    ++result;
                    ++first;
                }
            }
        };

        template <class Predicate>
        inline drop_while_t<Predicate> drop_while_(Predicate pred)
        {
            return pred;
        }

        // unique_
        struct unique_t {
            template <class Signature>
            struct result : public argument_vector<Signature> {};

            template <class Range>
            typename result_vector<Range>::type call(const Range& r) const
            {
                typename result_vector<Range>::type result;
                std::unique_copy(begin(r), end(r), std::back_inserter(result));
                return result;
            }
        };
        const unique_t unique_ = {};

        // copy_
        template <class T>
        class container_converter {
            std::vector<T> elements_;
        public:
            typedef T           value_type;
            typedef T&          reference;
            typedef const T&    const_reference;

            void push_back(const T& value)
            {
                elements_.push_back(value);
            }

            template <class U>
            operator U() const
            {
                return U(elements_.begin(), elements_.end());
            }
        };

        struct copy_t {
            template <class Signature>
            class result {
                typedef typename copy_argument<Signature>::type range_type;
            public:
                typedef container_converter<typename range_value<range_type>::type> type;
            };

            template <class Range>
            container_converter<typename range_value<Range>::type>
                call(const Range& r) const
            {
                container_converter<typename range_value<Range>::type> result;
                std::copy(begin(r), end(r), std::back_inserter(result));
                return result;
            }
        };
        const copy_t copy_ = {};

        // find_
        template <class T>
        class find_t {
            const T& value_;
        public:
            find_t(const T& value)
                : value_(value) {}

            template <class Signature>
            class result {
                typedef typename argument_of<Signature>::type argument_type;
                typedef typename std::tr1::remove_reference<argument_type>::type non_ref_type;
            public:
                typedef typename range_iterator<non_ref_type>::type type;
            };

            template <class Range>
            typename range_iterator<Range>::type call(Range& r) const
            {
                return std::find(begin(r), end(r), value_);
            }

            template <class Range>
            typename range_iterator<const Range>::type call(const Range& r) const
            {
                return std::find(begin(r), end(r), value_);
            }
        };

        template <class T>
        inline find_t<T> find_(const T& value)
        {
            return value;
        }

        // find_if_
        template <class Predicate>
        class find_if_t {
            Predicate pred_;
        public:
            find_if_t(Predicate pred)
                : pred_(pred) {}

            template <class Signature>
            class result {
                typedef typename argument_of<Signature>::type argument_type;
                typedef typename std::tr1::remove_reference<argument_type>::type non_ref_type;
            public:
                typedef typename range_iterator<non_ref_type>::type type;
            };

            template <class Range>
            typename range_iterator<Range>::type call(Range& r) const
            {
                return std::find_if(begin(r), end(r), pred_);
            }

            template <class Range>
            typename range_iterator<const Range>::type call(const Range& r) const
            {
                return std::find_if(begin(r), end(r), pred_);
            }
        };

        template <class Predicate>
        inline find_if_t<Predicate> find_if_(Predicate pred)
        {
            return pred;
        }

        // has_
        template <class T>
        class has_t {
            const T& value_;
        public:
            has_t(const T& value)
                : value_(value) {}

            typedef bool result_type;

            template <class Range>
            bool call(const Range& r) const
            {
                return std::find(begin(r), end(r), value_) != end(r);
            }
        };

        template <class T>
        inline has_t<T> has_(const T& value)
        {
            return value;
        }

        // has_if_
        template <class Predicate>
        class has_if_t {
            Predicate pred_;
        public:
            has_if_t(Predicate pred)
                : pred_(pred) {}

            typedef bool result_type;

            template <class Range>
            bool call(const Range& r) const
            {
                return std::find_if(begin(r), end(r), pred_) != end(r);
            }
        };

        template <class Predicate>
        inline has_if_t<Predicate> has_if_(Predicate pred)
        {
            return pred;
        }

        // tail_
        struct tail_t {
            template <class Signature>
            struct result : public copy_argument<Signature> {};

            template <class Range>
            Range call(const Range& r) const
            {
                if (r|is_empty_)
                    return r;

                Range result(r);
                result.erase(begin(result));
                return result;
            }
        };
        const tail_t tail_ = {};

        // front_
        struct front_t {
            template <class Signature>
            struct result {
                typedef typename range_value<typename copy_argument<Signature>::type>::type type;
            };

            template <class Range>
            typename range_value<Range>::type call(const Range& r) const
            {
                return *begin(r);
            }
        };
        const front_t front_ = {};
        const front_t head_ = {};

        // back_
        struct back_t {
            template <class Signature>
            struct result {
                typedef typename range_value<typename copy_argument<Signature>::type>::type type;
            };

            template <class Range>
            typename range_value<Range>::type call(const Range& r) const
            {
                return *back_iterator(begin(r), end(r));
            }

            template <class Iterator>
            static Iterator back_iterator(Iterator first, Iterator last)
            {
                std::size_t size = std::distance(first, last);
                for (std::size_t i = 0; i < size -1; ++i) {
                    ++first;
                }
                return first;
            }
        };
        const back_t back_ = {};

        // sum_
        struct sum_t {
            template <class Signature>
            struct result {
                typedef typename range_value<typename copy_argument<Signature>::type>::type type;
            };

            template <class Range>
            typename range_value<Range>::type call(const Range& r) const
            {
                return std::accumulate(begin(r), end(r), range_value<Range>::type());
            }
        };
        const sum_t sum_ = {};

        // average_
        struct average_t {
            typedef double result_type;

            template <class Range>
            double call(const Range& r) const
            {
                std::size_t size = r|count_;
                return size == 0 ? 0 : static_cast<double>((r|sum_)) / size;
            }
        };
        const average_t average_ = {};

        // min_
        struct min_t {
            template <class Signature>
            struct result {
                typedef typename range_value<typename copy_argument<Signature>::type>::type type;
            };

            template <class Range>
            typename range_value<Range>::type call(const Range& r) const
            {
                return *std::min_element(begin(r), end(r));
            }
        };
        const min_t min_ = {};

        // max_
        struct max_t {
            template <class Signature>
            struct result {
                typedef typename range_value<typename copy_argument<Signature>::type>::type type;
            };

            template <class Range>
            typename range_value<Range>::type call(const Range& r) const
            {
                return *std::max_element(begin(r), end(r));
            }
        };
        const max_t max_ = {};

        // make_range
        template <class Incrementable>
        inline std::vector<Incrementable>
            make_range(Incrementable from, Incrementable to)
        {
            std::vector<Incrementable> result;

            while (from != to) {
                result.push_back(from++);
            }

            return result;
        }

        // operator|
        template <class Range, class Func>
        inline typename std::tr1::result_of<Func(Range&)>::type
            operator|(Range& r, Func f)
        {
            return f.call(r);
        }

        template <class Range, class Func>
        inline typename std::tr1::result_of<Func(const Range&)>::type
            operator|(const Range& r, Func f)
        {
            return f.call(r);
        }

    } // namespace range

    using range::count_;
    using range::is_empty_;

    using range::sort_;
    using range::reverse_;
    using range::transform_;
    using range::for_each_;
    using range::filter_;
    using range::take_;
    using range::take_while_;
    using range::drop_;
    using range::drop_while_;
    using range::unique_;
    using range::copy_;
    using range::find_;
    using range::find_if_;
    using range::has_;
    using range::has_if_;

    using range::head_;
    using range::tail_;
    using range::front_;
    using range::back_;

    using range::sum_;
    using range::average_;
    using range::min_;
    using range::max_;

    using range::make_range;

	#define sorted shand::range::sort_
	#define filtered shand::range::filter_

} // namespace shand

#endif // SHAND_RANGE_INCLUDE
