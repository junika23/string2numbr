//
//  main.cpp
//  Test
//
//  Created by Juniarto Saputra on 26.06.22.
//

#include <iostream>
#include <string>
#include <vector>
#include <stack>
#include <algorithm>


const std::vector<std::string> DIGITS = { "",
    "thousand",
    "million",
    "billion",
    "error",
};

const std::vector<std::string> NUMS = { "",
    "one",
    "two",
    "three",
    "four",
    "five",
    "six",
    "seven",
    "eight",
    "nine"
};

const std::vector<std::string> TENS = { "",
    "",
    "twenty",
    "thirty",
    "forty",
    "fifty",
    "sixty",
    "seventy",
    "eighty",
    "ninety"
};

const std::vector<std::string> TEEN = { "",
    "eleven",
    "twelve",
    "thirteen",
    "fourteen",
    "fifteen",
    "sixteen",
    "seventeen",
    "eighteen",
    "nineteen"
};

// trim from start (in place)
static inline void ltrim(std::string &s) {
    s.erase(s.begin(), std::find_if(s.begin(), s.end(), [](unsigned char ch) {
        return !std::isspace(ch);
    }));
}

// trim from end (in place)
static inline void rtrim(std::string &s) {
    s.erase(std::find_if(s.rbegin(), s.rend(), [](unsigned char ch) {
        return !std::isspace(ch);
    }).base(), s.end());
}

// trim from both ends (in place)
static inline void trim(std::string &s) {
    ltrim(s);
    rtrim(s);
}

std::string convert(unsigned n, unsigned int counter)
{
    // convert function
    std::string res;
    bool has_hundert = false;
    bool has_ten = false;
    bool is_teen = false;
    
    unsigned hundert = (n / 100);
    if (hundert > 0)
    {
        std::string h_str = NUMS[hundert];
        res += h_str + " hundert";
        has_hundert = true;
    }
    unsigned z = n % 100;
    unsigned ten = (z / 10);
    if (ten > 0)
    {
        std::string t_str;
        if (has_hundert)
        {
            res += " and";
        }
        if (ten > 1)
        {
            t_str = TENS[ten];
            res += " ";
            has_ten = true;
        }
        else
        {
            unsigned t = n % 10;
            t_str = " " + TEEN[t];
            is_teen = true;
        }
        res += t_str;
        
    }
    if (!is_teen)
    {
        unsigned e = n % 10;
        if (has_ten && e > 0)
        {
            res += "-";
        }
        res += NUMS[e];
    }
    if (counter > 0)
    {
        res += " " + DIGITS[counter];
    }
    
    return res;
}

std::string get_3digit(const std::string& input)
{
    if (input.length() > 12)
    {
        return "Max number is 999 billion";
    }
    std::stack<std::string> out;
    std::string res;
    unsigned long number = atol(input.c_str());
    unsigned counter = 0;
    while (number != 0)
    {
        unsigned n = number % 1000;
        out.push(convert(n, counter));
        number = number / 1000;
        counter++;
    }
    
    while (!out.empty())
    {
        res += out.top();
        out.pop();
        if (!out.empty())
        {
            res += " ";
        }
    }
    
    trim(res);
    return res;
}

int main(int argc, const char * argv[]) {
    std::string res = get_3digit("1111111320654");
    std::cout << res << std::endl;
    return 0;
}
