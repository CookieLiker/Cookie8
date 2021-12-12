#include <iostream>

#include "Application.h"

int main(int argc, char *argv[])
{
    Cookie8::Application application{argc, argv};
    application.Run();
    return 0;
}