#include "headers.h"
#include "misc.h"
#include "init.h"
#include "commit.h"
#include "add.h"
#include "get_logs.h"




//void fetch_file(int vno, string filename, vector<string> list, string path1);


int main(int argc, char *argv[])
{


    char tmp[256];
    getcwd(tmp, 256);
    cwd = tmp;

    //git_init();
    //git_commit();
    git_add();

    return 0;
}
