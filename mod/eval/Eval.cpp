#include "Eval.h"

#include "trapdoor.h"

namespace mod {
    namespace {
        std::map<std::string, double> &getInBuildVariables() {
            static std::map<std::string, double> variables;
            variables["pi"] = 3.14159265358979323846;
            variables["e"] = 2.7182818284590452354;
            return variables;
        }

        std::string toLowerString(std::string str) {
            transform(str.begin(), str.end(), str.begin(),
                      (int (*)(int))tolower);
            return str;
        }

        void stringReplace(std::string &str, const std::string &fstr,
                           const std::string &rep) {
            std::string::size_type pos = 0;
            std::string::size_type a = fstr.length();
            std::string::size_type b = rep.length();
            if (b == 0)
                while ((pos = str.find(fstr, pos)) != std::string::npos) {
                    str.erase(pos, a);
                }
            else
                while ((pos = str.find(fstr, pos)) != std::string::npos) {
                    str.replace(pos, a, rep);
                    pos += b;
                }
        }

    }  // namespace

    void eval(trapdoor::Actor *player, const std::string &str) {
        auto pos = player->getPos()->toBlockPos();
        // build in variable
        getInBuildVariables()["x"] = pos.x;
        getInBuildVariables()["y"] = pos.y - 1;
        getInBuildVariables()["z"] = pos.z;
        getInBuildVariables()["cx"] = pos.toChunkPos().x;
        getInBuildVariables()["cz"] = pos.toChunkPos().z;
        EvalFunctions f;
        std::string s(str);
        std::string origin = s;
        s = toLowerString(s);
        stringReplace(s, "--", "+");
        stringReplace(s, "and", "&&");
        stringReplace(s, "xor", "^");
        stringReplace(s, "or", "||");
        stringReplace(s, "--", "+");
        stringReplace(s, "mod", "%");
        stringReplace(s, "==", "=");
        stringReplace(s, "π", "pi");
        auto result =
            cpp_eval::eval<double>(s.c_str(), getInBuildVariables(), f);
        if (abs(result - round(result)) < 10E-8) {
            trapdoor::info(player, "%s=§l§b%d", origin.c_str(),
                           static_cast<int>(round(result)));

        } else {
            trapdoor::info(player, "%s=§l§b%.3lf", origin.c_str(), result);
        }
    }

}  // namespace mod