//
// Created by kurlyana on 07.06.2020.
//

#include <cmath>
#include <fstream>
#include <vector>
#include <sstream>

#include <mpi.h>
#include <zconf.h>

#include "read_config.h"

int main(int argc, char *argv []){
    int commsize, rank, len ;
//    char procname[MPI_MAX_PROCESSOR_NAME];  //test

    MPI_Init(&argc, &argv);
    MPI_Comm_size(MPI_COMM_WORLD, &commsize);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
//    MPI_Get_processor_name(procname, &len); //test

    if (rank == 0) {
        auto config = read_conf();

        std::string matrix_file=config["matrix_file"];
        double delta_t=std::stod(config["delta_t"]);
        double delta_x=std::stod(config["delta_x"]);
        double delta_y=std::stod(config["delta_y"]);
        double density=std::stod(config["density"]);
        double temp_capacity=std::stod(config["temp_capacity"]);
        double temp_conduct=std::stod(config["temp_conduct"]);
        size_t save_interval=std::stoi(config["save_interval"]);
        size_t width = std::stoi(config["width"]);
        size_t height = std::stoi(config["height"]);

        double alpha = temp_conduct / (density * temp_capacity);

        if ((std::pow(std::max(delta_x, delta_y), 2) / (4 * alpha)) <= delta_t) {
            std::cerr << "Unstable" << std::endl;
            exit(1);
        }

        std::vector<std::vector<double>> matrix;
        std::string line;
        int value;

        std::ifstream in_file{matrix_file};
        while(std::getline(in_file, line)) {
            std::vector<double> row;
            std::istringstream iss(line);
            while(iss >> value){
                row.push_back(value);
            }
            matrix.push_back(row);
        }

        int process_num = commsize - 1;
        size_t delta_rows = height / process_num;

        size_t curr_rows;

        for (int i = 0; i <= process_num - 1; i++) {
            MPI_Request req;
            
            curr_rows = matrix[i*delta_rows];
            // to be recieved
//            general req?
            
            MPI_Isend(&curr_rows, 1, MPI_INT, i, 0, MPI_COMM_WORLD, &req);
            MPI_Isend(&width, 1, MPI_INT, i, 0, MPI_COMM_WORLD, &req);
            MPI_Isend(&delta_x, 1, MPI_DOUBLE, i, 0, MPI_COMM_WORLD, &req);
            MPI_Isend(&delta_y, 1, MPI_DOUBLE, i, 0, MPI_COMM_WORLD, &req);
            MPI_Isend(&delta_t, 1, MPI_DOUBLE, i, 0, MPI_COMM_WORLD, &req);
            MPI_Isend(&save_interval, 1, MPI_INT, i, 0, MPI_COMM_WORLD, &req);
            MPI_Isend(&alpha, 1, MPI_DOUBLE, i, 0, MPI_COMM_WORLD, &req);            

        }

        MPI_Status status;

//       TODO: image_process

        MPI_Finalize();
        }

    else {
//        TODO: Irecv
    }

    MPI_Finalize();
    return 0;
}

