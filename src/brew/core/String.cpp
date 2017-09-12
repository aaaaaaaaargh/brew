/**
 *
 *  |_  _ _
 *  |_)| (/_VV
 *
 *  Copyright 2015-2017 random arts
 *
 *  Created on: 04.09.17
 *
 */

#include "String.h"

#include <algorithm>

namespace brew {
namespace string {

String toString(const WideString& str) {
    return String(str.begin(), str.end());
}

WideString toWideString(const String& str) {
    return WideString(str.begin(), str.end());
}

void trim(String& str, const String& chars) {
    auto from = str.find_first_not_of(chars);
    auto to = str.find_last_not_of(chars);
    if (to != String::npos)
        str.erase(to + 1, str.length() - 1);
    if (from != String::npos)
        str.erase(0, from);
}

void trim(WideString& str, const WideString& chars) {
    auto from = str.find_first_not_of(chars);
    auto to = str.find_last_not_of(chars);

    if (from == WideString::npos && to == WideString::npos) {
        str.clear();
    }

    if (to != WideString::npos && to < str.length() - 1)
        str.erase(to + 1, str.length() - 1);
    if (from != WideString::npos)
        str.erase(0, from);

}

std::vector<String>
tokenize(const String& str, const std::vector<String>& separators, bool trim, bool skip_empty, bool keep_separators) {
    std::vector<WideString> separators_w;

    for (auto& separator : separators) {
        separators_w.push_back(toWideString(separator));
    }

    auto wr = tokenize(toWideString(str), separators_w, trim, skip_empty, keep_separators);
    std::vector<String> r;
    for (auto& wstr : wr) {
        r.push_back(toString(wstr));
    }
    return r;
}

std::vector<WideString>
tokenize(const WideString& str, const std::vector<WideString>& separators, bool trim, bool skip_empty,
         bool keep_separators) {
    // since find_first_of seeks for any char in the given string, we need to make substring checks here
    WideString::size_type n = 0, offset = 0;
    std::vector<WideString> r;

    while (n < str.length()) {
        bool found = false;
        for (const auto& separator : separators) {
            if (n + separator.length() >= str.length())
                continue;
            WideString sub = str.substr(n, separator.length());
            if (sub == separator) {
                found = true;
                WideString token = str.substr(offset, n - offset);
                if (trim) {
                    string::trim(token);
                }
                n += separator.length();
                offset = n;
                if (!skip_empty || !token.empty()) {
                    if (!token.empty() || !r.empty()) // Do not allow first token to be empty.
                        r.push_back(token);
                }

                if (keep_separators) {
                    r.push_back(sub);
                }
                break;
            }
        }
        if (!found)
            ++n;
    }

    WideString remaining = str.substr(offset);
    if (!remaining.empty()) {
        if (trim) {
            string::trim(remaining);
        }

        r.push_back(remaining);
    }

    return r;

}

String toSnakeCase(const String& str) {
    auto tokens = tokenize(str, std::vector<String>({" ", "\t", "-", "_"}), true, true, false);
    String s = implode<String>("_", tokens);
    std::transform(s.begin(), s.end(), s.begin(), ::tolower);
    return s;
}

String toKebabCase(const String& str) {
    auto tokens = tokenize(str, std::vector<String>({" ", "\t", "-", "_"}), true, true, false);
    String s = implode<String>("-", tokens);
    std::transform(s.begin(), s.end(), s.begin(), ::tolower);
    return s;
}

String toCamelCase(const String& str, bool capitalizeFirstLetter) {
    auto tokens = tokenize(str, std::vector<String>({" ", "\t", "-", "_"}), true, true, false);
    StringStream ss;
    bool first = true;
    for (auto& t : tokens) {
        if (!first || capitalizeFirstLetter) {
            ss << std::toupper(t[0]);
            ss << t.substr(1);
        } else if (first) {
            first = false;
            ss << t;
        }
    }
    return ss.str();
}

String join(const String& separator, const std::vector<String>& components) {
    String result;
    bool first = true;

    for (const String& c : components) {
        if (!first) {
            result += separator;
        } else {
            first = false;
        }

        result += c;
    }
    return result;
}

WideString join(const WideString& separator, const std::vector<WideString>& components) {
    WideString result;
    bool first = true;

    for (const WideString& c : components) {
        if (!first) {
            result += separator;
        } else {
            first = false;
        }

        result += c;
    }
    return result;
}

} /* namespace string */

const String EmptyString = "";

} /* namespace brew */