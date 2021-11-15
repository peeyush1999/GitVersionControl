#include<bits/stdc++.h>
#include <filesystem>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fstream>
using namespace std;
void git_init()
{
    char tmp[256];
    getcwd(tmp,256);
    string cwd=tmp;
    // cout<<cwd<<endl;
    string path=cwd+"/.git/version/v_1";
    string idxfile=path+"/index.txt";
    string logfile=cwd+"/.git/log.txt";
    string versionfile=cwd+"/.git/version.txt";
    int status;
    // status = mkdir(path.c_str(),S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH);
    status = mkdir(".git",0777);
    if(status!=0)
    {
        cout<<"unable to create Directory: "<<strerror(errno) << endl;
        exit(0);
    }
    status = mkdir(".git/version",0777);
    if(status!=0)
    {
        cout<<"unable to create Directory: "<<strerror(errno) << endl;
        exit(0);
    }
    status = mkdir(".git/version/v_1",0777);
    if(status!=0)
    {
        cout<<"unable to create Directory: "<<strerror(errno) << endl;
        exit(0);
    }
    cout<<"Hello"<<endl;
    ofstream log_file(logfile.c_str());
    log_file.close();
    ofstream version_file(versionfile.c_str());
    version_file<<"1";
    log_file.close();
    ofstream index_file(idxfile.c_str());
    index_file.close();
    getcwd(tmp,256);
    cout<<tmp<<endl;
    cout<<"Git Initialised"<<endl;
    return;
}
int main()
{
    git_init();
    return 0;
}