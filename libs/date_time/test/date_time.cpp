#include <boost/detail/lightweight_test.hpp>
#include <boost/fusion/include/vector.hpp>
#include <boost/fusion/include/at_c.hpp>
#include <boost/fusion/include/adapt_struct.hpp>

#define SHAND_DATE_TIME_CUSTOM_NOW_TIME // 現在時間を返す関数を書き換える
#include <shand/date_time.hpp>

namespace shand {
    std::time_t now_time_t()
    {
        std::tm t;
        t.tm_year   = 2010 - 1900;
        t.tm_mon    = 12 - 1;
        t.tm_yday   = 353;
        t.tm_mday   = 20;
        t.tm_wday   = 1;
        t.tm_hour   = 15;
        t.tm_min    = 30;
        t.tm_sec    = 45;
        t.tm_isdst  = 0;

        return std::mktime(&t);
    }
}

namespace fusion = boost::fusion;

struct UserDate {
    shand::year year;
    shand::month month;
    shand::day day;

    UserDate() {}
    UserDate(const shand::year& year_, const shand::month& month_, const shand::day& day_)
        : year(year_), month(month_), day(day_) {}
};

BOOST_FUSION_ADAPT_STRUCT(
    UserDate,
    (shand::year,  year)
    (shand::month, month)
    (shand::day,   day)
)

int main()
{
    using namespace shand;

    // 現在日時をフォーマット指定して出力
    BOOST_TEST(date_time::now().format("%Y/%m/%d %H:%M:%S") == "2010/12/20 15:30:45");

    // 1年加算
    {
        const date_time tm = date_time::now();
        BOOST_TEST((tm + year(1)).format("%Y/%m/%d %H:%M:%S") == "2011/12/20 15:30:45");
    }

    // 月を書き換え
    {
        date_time tm = date_time::now();
        tm = month(3);
        BOOST_TEST(tm.format("%Y/%m/%d %H:%M:%S") == "2010/03/20 15:30:45");
    }

    // 今月の日数を求める(次の月の1日から1日引く)
    {
        date_time tm = date_time::now();
        BOOST_TEST((((tm + month(1)) = day(1)) - day(1)).format("%d") == "31");
    }

    // &で繋げてまとめて設定(mktimeが1回で済む)
    {
        const date_time tm = year(2010) & month(3) & day(1) & hour(15) & minute(30) & second(12);
        BOOST_TEST(tm.format("%Y/%m/%d %H:%M:%S") == "2010/03/01 15:30:12");
    }
    {
        date_time tm = date_time::now();
        tm = year(2010) & month(3) & day(1) & hour(15) & minute(30) & second(12);
        BOOST_TEST(tm.format("%Y/%m/%d %H:%M:%S") == "2010/03/01 15:30:12");
    }

    // Fusion Sequenceにアダプトされたユーザー定義型を、shand::date_timeとして扱う
    {
        const date_time tm = UserDate(year(2010), month(3), day(1));
        BOOST_TEST(tm.format("%Y/%m/%d") == "2010/03/01");
    }

    // 日数の差を計算
    {
        const date_time a = year(2010) & month(3) & day(1);
        const date_time b = year(2010) & month(3) & day(5);

        BOOST_TEST(diff_day(a, b).value() == 4);
    }

    // 値を取り出す
    {
        const date_time tm = date_time::now();
        const fusion::vector<year, month, day> result = tm.extract<fusion::vector<year, month, day> >();

        BOOST_TEST(fusion::at_c<0>(result).value() == 2010);
        BOOST_TEST(fusion::at_c<1>(result).value() == 12);
        BOOST_TEST(fusion::at_c<2>(result).value() == 20);
    }
    {
        const date_time tm = date_time::now();

        UserDate result;
        tm.extract(result);

        BOOST_TEST(result.year.value()  == 2010);
        BOOST_TEST(result.month.value() == 12);
        BOOST_TEST(result.day.value()   == 20);
    }

    return boost::report_errors();
}
