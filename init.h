void git_init()
{

    string path = cwd + "/git/version/v_1";
    string idxfile = path + "/index.txt";
    string logfile = cwd + "/git/log.txt";
    string versionfile = cwd + "/git/version.txt";
    string add_commit = cwd + "/git/add_commit.txt";

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
    index_file << "";
    index_file.close();

    // creating add_commit file (for storig whether the file has pushed or not) 0-add 0-commit
    ofstream add_commit_file(add_commit.c_str());
    add_commit_file << "00";
    add_commit_file.close();

    cout << "Git Initialised" << endl;

    
   
}
