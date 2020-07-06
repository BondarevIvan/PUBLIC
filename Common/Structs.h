#pragma once
#include <unordered_map>
#include <unordered_set>
#include <vector>
#include <array>
#include <map>
#include <string>
#include <set>
#include <random>
#include <algorithm>
#include <deque>
#define DEBUG
#ifdef DEBUG
#include <iostream>
#endif
namespace std
{
#ifdef DEBUG
    template<class T>
    void debug(const T& i_element)
    {
        std::cerr << i_element << std::endl;
    }
    template<class T1, class T2>
    void debug(const T1& i_element1, const T2& i_element2)
    {
        std::cerr << i_element1 << ' ' << i_element2 << std::endl;
    }
    template<class T, class ...Args>
    void debug(const T& i_element1, Args... args)
    {
        std::cerr << i_element1 << ' ';
        debug(args...);
        std::cerr << std::endl;
    }
#endif
    namespace Random
    {
        double randomDouble(double i_left = 0., double i_right = 1.);
        int randomInt(int i_left = 0, int i_right = 100);
    }
}