//////////////////////////////////////////////////////////////////////////////
//
//  Cpp Eval
//
//  https://blog.csdn.net/hollysky/article/details/345125
//

#ifndef CPP_EVAL_H_DFF520DB406EDCF31AB9A538F7E1C3BD_20040721__
#define CPP_EVAL_H_DFF520DB406EDCF31AB9A538F7E1C3BD_20040721__

#include <cmath>
#include <map>
#include <vector>
#include <sstream>
#include <stdexcept>
#include <cstdlib>

namespace cpp_eval {
    template<typename number>
    number eval(const char *expression);

    template<typename number>
    number eval(const char *expression,
                const ::std::map<::std::string, number> &variables);

    template<typename number, typename functions>
    number eval(const char *expression,
                const ::std::map<::std::string, number> &variables,
                functions &funcs);

    template<typename number>
    class dummy_functions {
    public:
        number operator()(const char *, const ::std::vector<number> &params) {
            return 0;
            //        return number();
        }
    };

    template<typename number>
    number eval(const char *expression) {
        ::std::map<::std::string, number> variables;
        dummy_functions<number> funcs;
        return eval(expression, variables, funcs);
    }

    template<typename number>
    number eval(const char *expression,
                const ::std::map<::std::string, number> &variables) {
        dummy_functions<number> funcs;
        return eval(expression, variables, funcs);
    }

    template<typename number, typename functions>
    class evaler {
        const ::std::map<::std::string, number> &mVariables;
        functions &mFuncs;
        const char *mCurrent;
        enum Type {
            LEFT_BRACKET = '(',
            RIGHT_BRACKET = ')',
            PARAMETER_SEPERATOR = ',',
            IDENTIFIER = 257,
            NUMBER = 258,
            FINISHED = 259,

            POWER = 260,  //**

            MULTIPLY = '*',
            DIVIDE = '/',
            MOD = '%',

            ADD_OR_POSITIVE = '+',
            SUBTRACT_OR_NEGATIVE = '-',

            LESS_THAN = '<',              //<
            LESS_THAN_OR_EQUAL = 262,      //<=
            GREATER_THAN = '>',              //>
            GREATER_THAN_OR_EQUAL = 264,  //>=

            EQUAL = '=',      //==
            NOT_EQUAL = 266,  //!=

            AND = '&',
            XOR = '^',
            OR = '|',

            LOGIC_AND = 267,  //&&
            LOGIC_OR = 268      //||
        };
        Type mType;
        std::string mIdentifier;
        number mValue;

        void look_ahead() {
            for (;;) {
                if (isspace(*mCurrent)) {
                    ++mCurrent;
                    continue;
                } else if (*mCurrent == '*' && *(mCurrent + 1) == '*')
                    mType = POWER, mCurrent += 2;
                else if (*mCurrent == '<' && *(mCurrent + 1) == '=')
                    mType = LESS_THAN_OR_EQUAL, mCurrent += 2;
                else if (*mCurrent == '>' && *(mCurrent + 1) == '=')
                    mType = GREATER_THAN_OR_EQUAL, mCurrent += 2;
                else if (*mCurrent == '!' && *(mCurrent + 1) == '=')
                    mType = NOT_EQUAL, mCurrent += 2;
                else if (*mCurrent == '&' && *(mCurrent + 1) == '&')
                    mType = LOGIC_AND, mCurrent += 2;
                else if (*mCurrent == '|' && *(mCurrent + 1) == '|')
                    mType = LOGIC_OR, mCurrent += 2;
                else if (*mCurrent == ADD_OR_POSITIVE ||
                         *mCurrent == SUBTRACT_OR_NEGATIVE ||
                         *mCurrent == MULTIPLY || *mCurrent == DIVIDE ||
                         *mCurrent == MOD || *mCurrent == LEFT_BRACKET ||
                         *mCurrent == RIGHT_BRACKET ||
                         *mCurrent == PARAMETER_SEPERATOR ||
                         *mCurrent == LESS_THAN || *mCurrent == GREATER_THAN ||
                         *mCurrent == EQUAL || *mCurrent == AND ||
                         *mCurrent == XOR || *mCurrent == OR)
                    mType = (Type) *mCurrent, ++mCurrent;
                else if (isalpha(*mCurrent)) {
                    mType = IDENTIFIER;
                    mIdentifier.clear();
                    mIdentifier += *mCurrent;
                    ++mCurrent;
                    while (isalpha(*mCurrent) || isdigit(*mCurrent))
                        mIdentifier += *mCurrent, ++mCurrent;
                } else if (*mCurrent == 0)
                    mType = FINISHED;
                else {
                    mType = NUMBER;
                    std::istringstream iss(mCurrent);
                    // iss.setf(std::ios::fixed);
                    // iss.precision(18);
                    iss >> mValue;
                    if (!iss)
                        return;
                    mCurrent +=
                            iss.rdbuf()->pubseekoff(0, std::ios::cur, std::ios::in);
                }
                break;
            }
        }

        void match(Type type) {
            if (mType == type)
                look_ahead();
            else
                return;
        }

        number expression() {  // expression        ->    higher_expression
            // expression_R
            number result = expression_LOGIC_OR(LOGIC_AND_expression());
            return result;
        }

        number expression_LOGIC_OR(const number &left) {
            number result = left;
            if (mType == LOGIC_OR)
                match(LOGIC_OR),
                        result = expression_LOGIC_OR(
                                (((left > 0.5) ? 1.0 : 0.0) +
                                 ((LOGIC_AND_expression() > 0.5) ? 1.0 : 0.0) >
                                 0.5)
                                ? 1.0
                                : 0.0);
            return result;
        }

        number LOGIC_AND_expression() {
            return expression_LOGIC_AND(OR_expression());
        }

        number expression_LOGIC_AND(const number &left) {
            number result = left;
            if (mType == LOGIC_AND)
                match(LOGIC_AND), result = expression_LOGIC_AND(
                        ((left > 0.5) ? 1.0 : 0.0) *
                        ((OR_expression() > 0.5) ? 1.0 : 0.0));
            return result;
        }

        number OR_expression() { return expression_OR(XOR_expression()); }

        number expression_OR(const number &left) {
            number result = left;
            if (mType == OR)
                match(OR),
                        result = expression_OR(static_cast<number>(
                                                       static_cast<long long>(round(left)) |
                                                       static_cast<long long>(round(XOR_expression()))));
            return result;
        }

        number XOR_expression() { return expression_XOR(AND_expression()); }

        number expression_XOR(const number &left) {
            number result = left;
            if (mType == XOR)
                match(XOR),
                        result = expression_XOR(static_cast<number>(
                                                        static_cast<long long>(round(left)) ^
                                                        static_cast<long long>(round(AND_expression()))));
            return result;
        }

        number AND_expression() { return expression_AND(EQUAL_expression()); }

        number expression_AND(const number &left) {
            number result = left;
            if (mType == AND)
                match(AND),
                        result = expression_AND(static_cast<number>(
                                                        static_cast<long long>(round(left)) &
                                                        static_cast<long long>(round(EQUAL_expression()))));
            return result;
        }

        number EQUAL_expression() {
            return expression_EQUAL(COMPARE_expression());
        }

        number expression_EQUAL(const number &left) {
            number result = left;
            if (mType == NOT_EQUAL)
                match(NOT_EQUAL), result = expression_EQUAL(
                        left != COMPARE_expression() ? 1.0 : 0.0);
            else if (mType == EQUAL)
                match(EQUAL), result = expression_EQUAL(
                        left == COMPARE_expression() ? 1.0 : 0.0);
            return result;
        }

        number COMPARE_expression() {
            return expression_COMPARE(low_expression());
        }

        number expression_COMPARE(const number &left) {
            number result = left;
            if (mType == GREATER_THAN_OR_EQUAL)
                match(GREATER_THAN_OR_EQUAL),
                        result = expression_COMPARE(left >= low_expression() ? 1.0
                                                                             : 0.0);
            else if (mType == GREATER_THAN)
                match(GREATER_THAN),
                        result =
                                expression_COMPARE(left > low_expression() ? 1.0 : 0.0);
            else if (mType == LESS_THAN_OR_EQUAL)
                match(LESS_THAN_OR_EQUAL),
                        result = expression_COMPARE(left <= low_expression() ? 1.0
                                                                             : 0.0);
            else if (mType == LESS_THAN)
                match(LESS_THAN),
                        result =
                                expression_COMPARE(left < low_expression() ? 1.0 : 0.0);
            return result;
        }

        number low_expression() { return expression_R(higher_expression()); }

        number expression_R(
                const number &left) {  // expression_R        ->    +
            // higher_expression expression_R | -
            // higher_expression expression_R | /e/
            number result = left;
            if (mType == ADD_OR_POSITIVE)
                match(ADD_OR_POSITIVE),
                        result = expression_R(left + higher_expression());
            else if (mType == SUBTRACT_OR_NEGATIVE)
                match(SUBTRACT_OR_NEGATIVE),
                        result = expression_R(left - higher_expression());
            return result;
        }

        number higher_expression() {  // higher_expression    -> sign_expression
            // higher_expression_R
            return higher_expression_R(sign_expression());
        }

        number higher_expression_R(
                const number &left) {  // higher_expression_R    ->    *
            // sign_expression higher_expression_R | /
            // sign_expression higher_expression_R | /e/
            number result = left;
            if (mType == MULTIPLY)
                match(MULTIPLY),
                        result = higher_expression_R(left * sign_expression());
            else if (mType == DIVIDE)
                match(DIVIDE),
                        result = higher_expression_R(left / sign_expression());
            else if (mType == MOD)
                match(MOD),
                        result = higher_expression_R(fmod(left, sign_expression()));
            return result;
        }

        number
        sign_expression() {     // sign_expression        ->    + sign_expression |
            // - sign_expression | power_expression
            number result;
            if (mType == ADD_OR_POSITIVE)
                match(ADD_OR_POSITIVE), result = sign_expression();
            else if (mType == SUBTRACT_OR_NEGATIVE)
                match(SUBTRACT_OR_NEGATIVE), result = -sign_expression();
            else
                result = power_expression();
            return result;
        }

        number power_expression() {     // power_expression    ->    factor **
            // power_expression | factor
            number result = factor();
            if (mType == POWER)
                match(POWER), result = std::pow(result, (power_expression()));
            return result;
        }

        number factor() {  // factor            ->    number | ( expression ) |
            // lang_structure
            number result;
            if (mType == NUMBER)
                result = mValue, match(NUMBER);
            else if (mType == LEFT_BRACKET)
                match(LEFT_BRACKET), result = expression(),
                        match(RIGHT_BRACKET);
            else
                result = lang_structure();
            return result;
        }

        number
        lang_structure() {    // lang_structure        ->    identifier lang_tail
            std::string id = mIdentifier;
            match(IDENTIFIER);
            return lang_tail(id);
        }

        number lang_tail(const std::string &id) {  // lang_tail        ->    (
            // parameter_list | /e/
            number result;
            if (mType == LEFT_BRACKET) {
                match(LEFT_BRACKET);
                std::vector<number> param = parameter_list();
                result = mFuncs(id.c_str(), param);
            } else {
                if (mVariables.find(id) == mVariables.end())
                    return 0;
                result = mVariables.find(id)->second;
            }
            return result;
        }

        std::vector<number> parameter_list() {    // parameter_list        ->    )
            // | expression parameter_tail
            std::vector<number> result;
            for (;;) {
                if (mType == RIGHT_BRACKET) {
                    match(RIGHT_BRACKET);
                    break;
                }
                result.push_back(expression());
                parameter_tail(result);
            }
            return result;
        }

        void parameter_tail(
                std::vector<number> &param) {  // parameter_tail        ->    ,
            // expression parameter_tail | /e/
            if (mType == PARAMETER_SEPERATOR)
                match(PARAMETER_SEPERATOR), param.push_back(expression()),
                        parameter_tail(param);
        }

    public:
        evaler(const ::std::map<::std::string, number> &variables,
               functions &funcs)
                : mVariables(variables), mFuncs(funcs) {}

        number operator()(const char *expr) {
            mCurrent = expr;
            look_ahead();
            number result = expression();
            if (mType != FINISHED)
                return 0;
            return result;
        }
    };

    template<typename number, typename functions>
    number eval(const char *expression,
                const ::std::map<::std::string, number> &variables,
                functions &funcs) {
        return evaler<number, functions>(variables, funcs)(expression);
    }
};    // namespace cpp_eval

#endif    // CPP_EVAL_H_DFF520DB406EDCF31AB9A538F7E1C3BD_20040721__