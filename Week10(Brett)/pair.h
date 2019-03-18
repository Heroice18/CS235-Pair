//
//  pair.h
//  Assignment 10
//
//  Created by Brett Mills on 3/12/19.
//  Copyright © 2019 Brett Mills. All rights reserved.
//

#ifndef pair_h
#define pair_h

#include <iostream>

namespace custom
{
    template <class T1, class T2>
    class pair
    {
    public:
        // constructors
        pair() {}
        pair(const T1 & first, const T2 & second) : first(first), second(second) {}
        pair(const pair <T1, T2> & rhs) : first(rhs.first), second(rhs.second) {}
        
        // copy the values
        pair <T1, T2> & operator = (const pair <T1, T2> & rhs)
        {
            first  = rhs.first;
            second = rhs.second;
            return *this;
        }
        
        // constant fetchers
        const T1 & getFirst()  const { return first;  }
        const T2 & getSecond() const { return second; }
        
        // compare Pairs.  Only first will be compared!
        bool operator >  (const pair & rhs) const { return first >  rhs.first; }
        bool operator >= (const pair & rhs) const { return first >= rhs.first; }
        bool operator <  (const pair & rhs) const { return first <  rhs.first; }
        bool operator <= (const pair & rhs) const { return first <= rhs.first; }
        bool operator == (const pair & rhs) const { return first == rhs.first; }
        bool operator != (const pair & rhs) const { return first != rhs.first; }
        
        // these are public.  We cannot validate!
        T1 first;
        T2 second;
    };
    
    /*****************************************************
     * PAIR INSERTION
     * Display a pair for debug purposes
     ****************************************************/
    template <class T1, class T2>
    inline std::ostream & operator << (std::ostream & out, const pair <T1, T2> & rhs)
    {
        out << '(' << rhs.first << ", " << rhs.second << ')';
        return out;
    }
    
    /*****************************************************
     * PAIR EXTRACTION
     * input a pair
     ****************************************************/
    template <class T1, class T2>
    inline std::istream & operator >> (std::istream & in, pair <T1, T2> & rhs)
    {
        in >> rhs.first >> rhs.second;
        return in;
    }
}

#endif /* pair_h */
