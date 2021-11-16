void git_init()
{
    char tmp[256];
    getcwd(tmp,256);
    string cwd=tmp;

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
