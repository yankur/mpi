#include <iostream>
#include <fstream>

#include "read_config.h"


std::unordered_map<std::string, std::string> read_conf(const std::string &conf_file_name) {
    std::ifstream in;
    in.open(conf_file_name);
    std::unordered_map<std::string, std::string> res;
    try
    {
        if (in.is_open()) {
            std::string s;
            while (getline(in, s)) {
                s.erase(std::remove_if(s.begin(), s.end(), isspace), s.end());
                auto eq = s.find('=');
                auto qu = s.find('"');

                if (s.empty() || eq == std::string::npos) {
                    continue;
                }

                auto name = s.substr(0, eq);
                std::string val;
                if (name!="delta_t"&&name!="delta_x"&&name!="delta_y"&&name!="density"
                    &&name!="temp_capacity"
                    &&name!="temp_conduct"
                    &&name!="save_interval"
                    &&name!="width"
                    &&name!="height") {
                    val = s.substr(qu+1, s.size()-qu-2);
                } else {
                    val = s.substr(eq+1, s.size()-eq);
                }
                res[name] = val;
            }

        } else
        {
            std::cerr << "Couldn't open config file for reading. \n";
            exit(2);
        }
    }
    catch(const std::exception& e)
    {
        std::cerr << "Wrong configuration file arguments. \n";
        exit(3);
    }

    in.close();
    return res;
}