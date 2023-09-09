#pragma once
#include <string>
#include <sstream>
#include <vector>
#include <algorithm>

namespace StringActions
{
    // for cleaning up the input
    static inline void LeftTrim(std::string& s) {
        s.erase(s.begin(), std::find_if(s.begin(), s.end(), [](unsigned char ch) {
            return !std::isspace(ch);
            }));
    }

    static inline void RightTrim(std::string& s) {
        s.erase(std::find_if(s.rbegin(), s.rend(), [](unsigned char ch) {
            return !std::isspace(ch);
            }).base(), s.end());
    }

    // for splitting input and answers
    std::vector<std::string> SplitByChar(std::string& line, char delim)
    {
        std::stringstream lineToSplit(line);
        std::string segment;
        std::vector<std::string> splitList;


        while (std::getline(lineToSplit, segment, delim))
        {
            splitList.push_back(segment);
        }

        return splitList;
    }

    bool CompareLists(std::vector<std::string>& userList, std::vector<std::string>& correctList)
    {
        // clean up user answers
        for (auto elem : userList)
        {
            LeftTrim(elem);
            RightTrim(elem);
        }

        // clean up correct answers
        for (auto elem : correctList)
        {
            LeftTrim(elem);
            RightTrim(elem);
        }

        for (auto elem : correctList)
        {
            if (std::find(userList.begin(), userList.end(), elem) == userList.end())
            {
                return false;
            }
        }
        return true;
    }
}