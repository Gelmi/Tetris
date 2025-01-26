/**
 * @file main.cpp
 * @author Gabriel and Guilherme
 * @brief This file handles the initial of the program
 * @version 0.1
 * @date 2025-01-26
 * 
 * @copyright Copyright (c) 2025
 * 
 */
#include "application.hpp"

/**
 * @brief add main function to initialize and run the application
 * 
 * @param argc 
 * @param argv 
 * @return int 
 */
int main(int argc, char ** argv) {
    Application app;
    if(argc==2) return app.Run(argv[1]);
    if(argc==1) return app.Run("localhost");
    return 0;
}

