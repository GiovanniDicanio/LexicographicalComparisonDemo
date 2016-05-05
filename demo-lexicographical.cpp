///////////////////////////////////////////////////////////////////////////////
//
// C++ Lexicographical Comparisons Demo of std::tie, tuple and make_tuple.
//
// By Giovanni Dicanio <email: <first>.<last>@gmail.com>
//
// Web Blog: http://blogs.msmvps.com/gdicanio/
//
// Associated article on Pluralsight's blog: http://bit.ly/1rwGfCc
//
///////////////////////////////////////////////////////////////////////////////


#include <algorithm>    // for std::sort
#include <iostream>     // for console output
#include <tuple>        // for std::tie, std::tuple, std::make_tuple
#include <vector>       // for std::vector

// Time representing hours, minutes and seconds
class Time {
 public:
  Time() : m_hours{}, m_minutes{}, m_seconds{} 
  {}

  Time(int hours, int minutes, int seconds)
      : m_hours{hours}
      , m_minutes{minutes}
      , m_seconds{seconds}
  {}
  
  int hours()   const { return m_hours; }
  int minutes() const { return m_minutes; }
  int seconds() const { return m_seconds; }

#ifdef CASE1
  friend bool operator<(const Time& lhs, const Time& rhs) {
    // NOTE how we can just use std::tie and op< instead of a
	// cumbersome bug-prone sequence of ifs!
    return std::tie(lhs.m_hours, lhs.m_minutes, lhs.m_seconds)
           < std::tie(rhs.m_hours, rhs.m_minutes, rhs.m_seconds);
  }
#endif
 
 private:
  int m_hours;
  int m_minutes;
  int m_seconds;
};

#ifdef CASE2
// Error-generating code (std::tie with temporaries)
bool operator<(const Time& lhs, const Time& rhs) {
  return std::tie(lhs.hours(), lhs.minutes(), lhs.seconds())
         < std::tie(rhs.hours(), rhs.minutes(), rhs.seconds());
}
#endif

// Working code: std::make_tuple
bool operator<(const Time& lhs, const Time& rhs) {
  return std::make_tuple(lhs.hours(), lhs.minutes(), lhs.seconds())
         < std::make_tuple(rhs.hours(), rhs.minutes(), rhs.seconds());
}


int main() {
  std::vector<Time> times{ {11, 20, 30}, {10, 10, 10}, {12, 41, 25} };
  std::sort(times.begin(), times.end());
  
  // Print sorted times
  for (const auto & t : times) {
    std::cout << t.hours() << ':' << t.minutes() << ':' << t.seconds() << '\n';
  }
}
