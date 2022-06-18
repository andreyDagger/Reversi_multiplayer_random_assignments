#include <string>

#include "Server.h"
#include "../Common classes/service.h"

using namespace std;

int main()
{
    string linker_dir = read_ini("Files", "Linking_dir", "../Reversi.ini");
    string linker_filename = read_ini("Files", "Linker_filename", "../Reversi.ini");
    
    Server* server = new Server(linker_dir + linker_filename);
    server->start_server();

    return 0;
}