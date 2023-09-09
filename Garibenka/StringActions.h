﻿#pragma once
#include <string>
#include <sstream>
#include <vector>
#include <algorithm>

namespace StringActions
{
    // for cleaning up the input
    static inline void LeftTrim(std::wstring& s) {
        s.erase(s.begin(), std::find_if(s.begin(), s.end(), [](unsigned char ch) {
            return !std::isspace(ch);
            }));
    }

    static inline void RightTrim(std::wstring& s) {
        s.erase(std::find_if(s.rbegin(), s.rend(), [](unsigned char ch) {
            return !std::isspace(ch);
            }).base(), s.end());
    }

    // for splitting input and answers
    std::vector<std::wstring> SplitByChar(std::wstring& line)
    {
        std::wstringstream lineToSplit(line);
        std::wstring segment;
        std::vector<std::wstring> splitList;

        if (line.find(L",") != std::string::npos)
        {
            while (std::getline(lineToSplit, segment, L','))
            {
                splitList.push_back(segment);
            }
        }
        else
        {
            while (std::getline(lineToSplit, segment, L'、'))
            {
                splitList.push_back(segment);
            }
        }

        return splitList;
    }

    bool CompareLists(std::vector<std::wstring>& userList, std::vector<std::wstring>& correctList)
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