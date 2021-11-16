#include <bits/stdc++.h>
#include <filesystem>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fstream>
#include <chrono>
#include <ctime>
#include <fcntl.h>
#include <termios.h>
#include <sys/sendfile.h>

using namespace std;

string cwd; //stores current working directory

// This function is used for displaying all errors (for readability of code)
int check(int exp, const char *msg)
{
    if (exp == -1)
    {
        perror(msg);
        exit(1);
    }
    return exp;
}

// copy file with same permissions
void copyFile(string SfilePath, string DfilePath)
{
    int source = open(SfilePath.c_str(), O_RDONLY, 0);
    int dest = open(DfilePath.c_str(), O_WRONLY | O_CREAT, S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
    struct stat stat_source;
    fstat(source, &stat_source);
    sendfile(dest, source, 0, stat_source.st_size);
    chmod(DfilePath.c_str(), stat_source.st_mode);
    chown(DfilePath.c_str(), stat_source.st_uid, stat_source.st_gid);
    close(source);
    close(dest);
}
void git_init()
{
    
    string path = cwd + "/git/version/v_1";
    string idxfile = path + "/index.txt";
    string logfile = cwd + "/git/log.txt";
    string versionfile = cwd + "/git/version.txt";

    // creating the directories
    check(mkdir("git", 0777), "unable to create directory");
    check(mkdir("git/version", 0777), "unable to create directory");
    check(mkdir("git/version/v_1", 0777), "unable to create directory");

    // creating log file
    ofstream log_file(logfile.c_str());
    log_file.close();

    // creating version.txt and writing the version as 1
    ofstream version_file(versionfile.c_str());
    version_file << "1";
    log_file.close();

    // creating index file
    ofstream index_file(idxfile.c_str());
    index_file << "Hello I am in index file";
    index_file.close();

    cout << "Git Initialised" << endl;
}
void git_commit()
{
    // getting version number from version.txt
    string versionfile = cwd + "/git/version.txt";
    ifstream infile;
    infile.open(versionfile, ios::in);
    string data;
    infile >> data;
    infile.close();

    // converting version number to integer and incrementing the version number
    stringstream con(data);
    int v_no = 0;
    con >> v_no;
    v_no += 1;

    // writing version number to the version.txt
    ofstream outfile;
    outfile.open(versionfile, ios::out);
    outfile << v_no;
    outfile.close();

    // creating new directory with new version number
    string newDirectory = cwd + "/git/version/v_" + to_string(v_no);
    check(mkdir(newDirectory.c_str(), 0777), "unable to create directory");


    // copying index file contents to new index file
    string prevIndexPath = cwd + "/git/version/v_" + to_string(v_no - 1) + "/index.txt";
    string newIndexPath = cwd + "/git/version/v_" + to_string(v_no) + "/index.txt";
    copyFile(prevIndexPath,newIndexPath);

    // to get current time
    auto currTime = std::chrono::system_clock::now();
    time_t time = std::chrono::system_clock::to_time_t(currTime);
    string Time = ctime(&time);

    // copying the commit time in log.txt
    string log_file = cwd + "/git/log.txt";
    outfile.open(log_file, ios::app);

    // writing commit time into log file
    string toLog = "Commit No:" + to_string(v_no - 1) + "\nCommit Time: " + Time + "\n";
    outfile << toLog;
    outfile.close();
}
int main()
{
    // getting current working directory
    char tmp[256];
    getcwd(tmp, 256);
    cwd = tmp;
    
    git_init();
    git_commit();
    return 0;
}