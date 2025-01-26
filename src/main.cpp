#include "application.hpp"

int main(int argc, char ** argv) {
    Application app;
    if(argc==2) return app.Run(argv[1]);
    return 0;
}

