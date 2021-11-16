#include "headers.h"
#include "misc.h"
#include "init.h"
#include "commit.h"




//void fetch_file(int vno, string filename, vector<string> list, string path1);


int main()
{
    char tmp[256];
    getcwd(tmp, 256);
    cwd = tmp;
    
    git_init();
    git_commit();
    
    return 0;
}