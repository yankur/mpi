//
// Created by kurlyana on 07.06.2020.
//

#ifndef MPI_READ_CONFIG_H
#define MPI_READ_CONFIG_H

#include <unordered_map>

std::unordered_map<std::string, std::string> read_conf(const std::string &conf_file_name="../data/config.dat");

#endif //MPI_READ_CONFIG_H
