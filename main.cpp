#include "headers.h"
#include "misc.h"
#include "init.h"
#include "commit.h"
#include "add.h"
#include "get_logs.h"
#include "status.h"
#include "add_file.h"
#include "git_diff.h"
#include "push.h"
#include "rollback.h"
#include "pull.h"

int main(int argc, char *argv[])
{
    if (argc < 3)
    {
        cout << "Arguments format: ./main command pathoflocalrepository" << endl;
        cout << RED("Insufficient arguments") << endl;
        exit(0);
    }
    if (argc == 3)
    {
        if (argv[2][0] != '/')
        {
            cout << RED("last argument should be path of local repository") << endl;
            exit(0);
        }
        cwd = argv[2];
    }
    else if (argc == 4)
    {
        if (argv[3][0] != '/')
        {
            cout << RED("last argument should be path of local repository") << endl;
            exit(0);
        }
        cwd = argv[3];
    }
    string gitdir = cwd + "/git";
    struct stat sb;
    stat(gitdir.c_str(), &sb);
    bool isdir = S_ISDIR(sb.st_mode);
    string cmd = argv[1];
    if (argc == 3)
    {
        if (cmd == "init")
        {
            if (!(isdir))
            {
                git_init();
                exit(0);
            }
            else
            {
                cout << RED("Already created") << endl;
                exit(0);
            }
        }
        if (cmd == "commit")
        {
            if (isdir)
            {
                git_commit();
                exit(0);
            }
            else
            {
                cout << RED("Git directory not Initialised") << endl;
                exit(0);
            }
        }
        if (cmd == "status")
        {
            if (isdir)
            {
                git_status();
                exit(0);
            }
            else
            {
                cout << RED("Git directory not Initialised") << endl;
                exit(0);
            }
        }
        if (cmd == "push")
        {
            if (isdir)
            {
                git_push();
                exit(0);
            }
            else
            {
                cout << RED("Git directory not Initialised") << endl;
                exit(0);
            }
        }
        if (cmd == "log")
        {
            if (isdir)
            {
                get_logs();
                cout << endl;
                exit(0);
            }
            else
            {
                cout << RED("Git directory not Initialised") << endl;
                exit(0);
            }
        }
        if (cmd == "rollback")
        {
            if (isdir)
            {
                git_rollback();
                cout << endl;
                exit(0);
            }
            else
            {
                cout << RED("Git directory not Initialised") << endl;
                exit(0);
            }
        }
        if (cmd == "pull")
        {
            if (isdir)
            {
                git_pull();
                exit(0);
            }
            else
            {
                cout << RED("Git directory not Initialised") << endl;
                exit(0);
            }
        }
    }
    if (argc == 4)
    {
        string attr = argv[2];
        if (cmd == "add" && attr == ".")
        {
            if (isdir)
            {
                git_add();
                exit(0);
            }
            else
            {
                cout << RED("Git directory not Initialised") << endl;
                exit(0);
            }
        }
        if (cmd == "add" && attr != ".")
        {
            if (isdir)
            {
                string filename = argv[2];
                git_add_file(filename);
                exit(0);
            }
            else
            {
                cout << RED("Git directory not Initialised") << endl;
                exit(0);
            }
        }
        if (cmd == "diff" && attr != ".")
        {
            if (isdir)
            {
                string filename = argv[2];
                git_diff_file(filename);
                exit(0);
            }
            else
            {
                cout << RED("Git directory not Initialised") << endl;
                exit(0);
            }
        }
        if (cmd == "diff" && attr == ".")
        {
            if (isdir)
            {
                git_diff();
                exit(0);
            }
            else
            {
                cout << RED("Git directory not Initialised") << endl;
                exit(0);
            }
        }
    }

    return 0;
}
