#include "headers.h"
#include "misc.h"
#include "init.h"
#include "commit.h"
#include "add.h"
#include "get_logs.h"
#include "status.h"
#include "add_file.h"


int main(int argc, char *argv[])
{
    char tmp[256];
    getcwd(tmp, 256);
    cwd = tmp;
    string gitdir=cwd+"/git";
    struct stat sb;
    stat(gitdir.c_str(), &sb);
    bool isdir = S_ISDIR(sb.st_mode);
    string cmd=argv[1];
    if (argc==2)
    {
        if(cmd=="init")
        {
            if(!(isdir))
            {
                git_init();
                exit(0);
            }
            else
            {
                cout<<"Already created"<<endl;
                exit(0);
            }
        }
        if(cmd=="commit")
        {
            if(isdir)
            {
                git_commit();
                exit(0);
            }
            else
            {
                cout<<"Git directory not Initialised"<<endl;
                exit(0);
            }
        }
        if(cmd=="status")
        {
            if(isdir)
            {
                //git_status();
                exit(0);
            }
            else
            {
                cout<<"Git directory not Initialised"<<endl;
                exit(0);
            }
        }
    }
    if(argc==3)
    {
        string attr=argv[2];
        if(cmd=="add" && attr==".")
        {
            if(isdir)
            {
                git_add();
                exit(0);
            }
            else
            {
                cout<<"Git directory not Initialised"<<endl;
                exit(0);
            }
        }
        if(cmd=="add" && attr!=".")
        {
            if(isdir)
            {
                string filename=argv[2];
                git_add_file(filename);
                exit(0);
            }
            else
            {
                cout<<"Git directory not Initialised"<<endl;
                exit(0);
            }
        }
    }


    return 0;
}
