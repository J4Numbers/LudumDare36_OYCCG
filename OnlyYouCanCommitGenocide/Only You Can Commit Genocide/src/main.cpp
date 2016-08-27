#include <stdio.h>
#include <Windows.h>

#include "MDB.hpp"

int main(int argc, char** argv)
{
    MDB* m = new MDB();

    if (m->boot() == -1)
    {
        fprintf(stdout, "Error loading SDL: %s\n", m->get_last_error());
    }

    Sleep(5000);

    return 0;
}
