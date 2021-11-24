void git_init()
{

    string path = cwd + "/git/version/v_1";
    string idxfile = path + "/index.txt";
    string logfile = cwd + "/git/log.txt";
    string versionfile = cwd + "/git/version.txt";
    string add_commit = cwd + "/git/add_commit.txt";
    string pushFile = cwd + "/git/push_index.txt";

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

    cout << BROWN_B("       Provide remote repository name with full path: ");
    string push_directory;
    cin >> push_directory;

    // creating add_commit file (for storig whether the file has pushed or not) 0-add 0-commit and also push_directory path
    ofstream add_commit_file(add_commit.c_str());
    add_commit_file << "00 " << push_directory;
    add_commit_file.close();

    // creating the push file
    ofstream push_file(pushFile.c_str());
    push_file.close();

    // creating remote reposirtory if doesn't exists
    string push_dir = push_directory;
    struct stat sb;
    stat(push_dir.c_str(), &sb);
    bool isdir = S_ISDIR(sb.st_mode);
    if (!isdir) //If the remote repo does not exists
    {
        // creating push directory in the specified path
        check(mkdir(push_dir.c_str(), 0777), "unable to create directory");
    }

    cout << YELLOW_B("       Git Initialised") << endl;
}
