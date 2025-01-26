#include "application.hpp"

int main(int argc, char ** argv) {
    Application app;
    if(argc==2) return app.Run(argv[1]);
    if(argc==1) return app.Run("localhost");
    return 0;
}

