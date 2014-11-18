// Some awesome note.
// http://cppcodereviewers.com/readable-for_each-loop-for-maps/

#include <iostream>
#include <map>
#include <vector>
#include <numeric>

// DATA
auto student_points = std::map<std::string, std::vector<int>> {
    {"Filip", {1,2,3}},
    {"Adrian", {5,6,7}}
};

// BEFORE
namespace before
{
    void sum()
    {
        for (const auto& e : student_points)
        {
            std::cout << "Sum of points for student: '" << e.first << "' is "
                << std::accumulate(e.second.begin(), e.second.end(), 0) << std::endl;
        }
    }
}

// AFTER
namespace after
{
    template <typename Range, typename Fun>
    void map_for_each(const Range& range, Fun f)
    {
        for(const auto& e : range)
            f(e.first, e.second);
    }

    void sum()
    {
        map_for_each(student_points, [](auto& student, auto& points){
            std::cout << "Sum of points for student: '" << student << "' is "
                << std::accumulate(points.begin(), points.end(), 0) << std::endl;
        });
    }
}

int main()
{
    std::cout << "---- BEFORE" << std::endl;
    before::sum();
    std::cout << "---- AFTER" << std::endl;
    after::sum();
}
