#include "calculator.h"

#include <vector>
#include <string>
#include <sstream>
#include <iterator>
#include <unordered_map>
#include <functional>
#include <stack>
#include <cassert>
#include <algorithm>

bool containsAnyLetter(const std::string& str)
{
    return std::any_of(str.cbegin(), str.cend(), [](char c) { return (::islower(c) || ::isupper(c)); });
}

bool containsOnlyDigits(const std::string& str)
{
    return std::all_of(str.cbegin(), str.cend(), ::isdigit);
}

const std::unordered_map<std::string, std::function<double(double,double)>> OPERATIONS
{
    { "+", std::plus<double>() },
    { "-", std::minus<double>() },
    { "*", std::multiplies<double>() },
    { "/", std::divides<double>() }
};

std::pair<tResultType, double> evalRPN(const std::vector<std::string>& tokens)
{
    std::stack<double> stack;

    for (const auto& token : tokens)
    {
        const auto& it = OPERATIONS.find(token);
        if (it != OPERATIONS.end())
        {
            if(stack.size() < 2)
            {
                return std::make_pair(false, 0.0);
            }
            double rhs = stack.top(); stack.pop();
            double lhs = stack.top(); stack.pop();
            if(it->first == "/" && rhs == 0.0)
            {
                return std::make_pair(false, 0.0);
            }
            stack.push(it->second(lhs, rhs));
        }
        else
        {
            if(!containsOnlyDigits(token))
            {
                return std::make_pair(false, 0.0);
            }
            stack.push(std::stoi(token));
        }
    }

    assert(stack.size() == 1);
    return std::make_pair(true, stack.top());
}

std::pair<tResultType,double> calculate(const std::string& evals)
{
    std::istringstream iss{evals};
    if (evals.empty() || containsAnyLetter(evals))
    {
        return std::make_pair(false, 0.0);
    }

    std::vector<std::string> strippedString(std::istream_iterator<std::string>{iss},
                                            std::istream_iterator<std::string>());
    return evalRPN(strippedString);
}
