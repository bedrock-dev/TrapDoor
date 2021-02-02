#ifndef TRAPDOOR_EVAL_H
#define TRAPDOOR_EVAL_H

#include <numeric>
#include <vector>
#include <map>
#include <cmath>
#include <random>
#include <string>
#include "lib/CppEval.h"
#include "trapdoor.h"

namespace mod {
    class EvalFunctions {
    public:
        double operator()(const char *name, const std::vector<double> &params) {
            std::string mName(name);
            if (mName == "sin") {
                if (params.size() == 1)
                    return sin(params[0]);
            } else if (mName == "cos") {
                if (params.size() == 1)
                    return cos(params[0]);
            } else if (mName == "sign") {
                if (params.size() == 1)
                    return params[0] == 0.0 ? 0.0
                                            : (params[0] > 0.0 ? 1.0 : -1.0);
            } else if (mName == "lg") {
                if (params.size() == 1)
                    return log10(params[0]);
            } else if (mName == "ln") {
                if (params.size() == 1)
                    return log(params[0]);
            } else if (mName == "log2") {
                if (params.size() == 1)
                    return log2(params[0]);
            } else if (mName == "round") {
                if (params.size() == 1)
                    return round(params[0]);
            } else if (mName == "floor") {
                if (params.size() == 1)
                    return floor(params[0]);
            } else if (mName == "ceil") {
                if (params.size() == 1)
                    return ceil(params[0]);
            } else if (mName == "exp") {
                if (params.size() == 1)
                    return exp(params[0]);
            } else if (mName == "exp2") {
                if (params.size() == 1)
                    return exp2(params[0]);
            } else if (mName == "sqrt") {
                if (params.size() == 1)
                    return sqrt(params[0]);
            } else if (mName == "tan") {
                if (params.size() == 1)
                    return tan(params[0]);
            } else if (mName == "atan") {
                if (params.size() == 1)
                    return atan(params[0]);
            } else if (mName == "atan2") {
                if (params.size() == 2)
                    return atan2(params[0], params[0]);
            } else if (mName == "asin") {
                if (params.size() == 1)
                    return asin(params[0]);
            } else if (mName == "acos") {
                if (params.size() == 1)
                    return acos(params[0]);
            } else if (mName == "sinh") {
                if (params.size() == 1)
                    return sinh(params[0]);
            } else if (mName == "cosh") {
                if (params.size() == 1)
                    return cosh(params[0]);
            } else if (mName == "tanh") {
                if (params.size() == 1)
                    return tanh(params[0]);
            } else if (mName == "gamma") {
                if (params.size() == 1)
                    return tgamma(params[0]);
            } else if (mName == "isslimechunk") {
                if (params.size() == 2) {
                    trapdoor::BlockPos2 p2(params[0], params[1]);
                    return p2.isSlimeChunk();
                }
            } else if (mName == "sum") {
                return std::accumulate(params.begin(), params.end(), 0.0);
            } else if (mName == "min") {
                return *min_element(params.begin(), params.end());
            } else if (mName == "max") {
                return *max_element(params.begin(), params.end());
            }
            return 0;
        }
    };

    void eval(trapdoor::Actor *player, const std::string &s);
}  // namespace mod
#endif