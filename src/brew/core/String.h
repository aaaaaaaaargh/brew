/**
 *
 *  |_  _ _
 *  |_)| (/_VV
 *
 *  Copyright 2015-2018 [insert fancy company name here]
 *
 *  Created on: 04.09.17
 *
 */

#ifndef BREW_STRINGUTILS_H
#define BREW_STRINGUTILS_H

#include <brew/core/Types.h>

#include <vector>

namespace brew {
namespace string {

/**
 * Converts a wide string to a string.
 * @param str  The wide string.
 * @return The converted string.
 */
extern String toString(const WideString& str);

/**
 * Converts a string to a wide string.
 * @param str The string.
 * @return The converted wide string.
 */
extern WideString toWideString(const String& str);

/**
 * Trims a string by removing characters from its left and right.
 * @param str The string to trim.
 * @param chars The characters to remove.
 */
extern void trim(String& str, const String& chars = " \t\n\r");

/**
 * Trims a string by removing characters from its left and right.
 * @param str The string to trim.
 * @param chars The characters to remove.
 */
extern void trim(WideString& str, const WideString& chars = L" \t\n\r");

/**
 * Splits a string into tokens.
 * @param str The string to tokenize.
 * @param separators A list of separators.
 * @param trim Whether to trim the tokens.
 * @param skip_empty Whether to skip empty tokens.
 * @param keep_separators Whether to keep the separators as tokens.
 * @return A list of tokens.
 */
extern std::vector<String> tokenize(
        const String& str,
        const std::vector<String>& separators,
        bool trim = true,
        bool skip_empty = true,
        bool keep_separators = false);

/**
 * Splits a string into tokens.
 * @param str The string to tokenize.
 * @param separators A list of separators.
 * @param trim Whether to trim the tokens.
 * @param skip_empty Whether to skip empty tokens.
 * @param keep_separators Whether to keep the separators as tokens.
 * @return A list of tokens.
 */
extern std::vector<WideString> tokenize(
        const WideString& str,
        const std::vector<WideString>& separator,
        bool trim = true,
        bool skip_empty = true,
        bool keep_separators = false);

/**
 * Splits a string into tokens.
 * @param str The string to tokenize.
 * @param separator The separator.
 * @param trim Whether to trim the tokens.
 * @param skip_empty Whether to skip empty tokens.
 * @param keep_separators Whether to keep the separators as tokens.
 * @return A list of tokens.
 */
inline std::vector<String> tokenize(
        const String& str,
        const String& separator,
        bool trim = true,
        bool skip_empty = true,
        bool keep_separators = false) {
    return tokenize(str, std::vector<String>({separator}), trim, skip_empty, keep_separators);
}

/**
 * Splits a string into tokens.
 * @param str The string to tokenize.
 * @param separator The separator.
 * @param trim Whether to trim the tokens.
 * @param skip_empty Whether to skip empty tokens.
 * @param keep_separators Whether to keep the separators as tokens.
 * @return A list of tokens.
 */
inline std::vector<WideString> tokenize(
        const WideString& str,
        const WideString& separator,
        bool trim = true,
        bool skip_empty = true,
        bool keep_separators = false) {
    return tokenize(str, std::vector<WideString>({separator}), trim, skip_empty, keep_separators);
}

/**
 * Joins a list of strings into a new string.
 * @param separator The separator to put between the string components.
 * @param components The components list.
 * @return The joined string.
 */
extern String join(const String& separator, const std::vector<String>& components);

/**
 * Joins a list of strings into a new string.
 * @param separator The separator to put between the string components.
 * @param components The components list.
 * @return The joined string.
 */
extern WideString join(const WideString& separator, const std::vector<WideString>& components);

/**
 * Converts a string to snake_case.
 * @param str The string.
 * @return The converted string.
 */
extern String toSnakeCase(const String& str);

/**
 * Converts a string to kebab-case.
 * @param str The string.
 * @return The converted string.
 */
extern String toKebabCase(const String& str);

/**
 * Converts a string to camelCase.
 * @param str The string.
 * @param capitalizeFirstLetter Whether to begin the string with a capital letter.
 * @return The converted string.
 */
extern String toCamelCase(const String& str, bool capitalizeFirstLetter = false);

/**
 * Implodes a list of elements into a string.
 * @tparam T The type of the elements to implode, must be string-convertible.
 * @tparam ContainerT The container type, must support range-based-for loops.
 * @param separator The separator to put between the imploded elements.
 * @param container The container of elements.
 * @return The imploded string.
 */
template<typename T, typename ContainerT = std::vector<T> >
String implode(const String& separator, const ContainerT& container) {
    StringStream ss;
    bool first = true;
    for (auto& s : container) {
        if (!first) {
            ss << separator;
        } else {
            first = false;
        }
        ss << s;
    }
    return ss.str();
}

/**
 * Implodes a list of elements into a string.
 * @tparam T The type of the elements to implode, must be string-convertible.
 * @tparam ContainerT The container type, must support range-based-for loops.
 * @param separator The separator to put between the imploded elements.
 * @param container The container of elements.
 * @return The imploded string.
 */
template<typename T, typename ContainerT = std::vector<T> >
WideString implode(const WideString& separator, const ContainerT& container) {
    WideStringStream ss;
    bool first = true;
    for (auto& s : container) {
        if (!first) {
            ss << separator;
        } else {
            first = false;
        }
        ss << s;
    }
    return ss.str();
}

} /* namespace string */

extern const String EmptyString; //< The empty string.

} /* namespace brew */

#endif //BREW_STRINGUTILS_H
