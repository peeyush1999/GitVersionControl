void git_commit()
{
    if (!added)
    {
        LOG(RED("No data is added to commit"));
        exit(0);
    }

    // getting version number from version.txt
    string versionfile = cwd + "/git/version.txt";
    ifstream infile;
    infile.open(versionfile, ios::in);
    int v_no;
    infile >> v_no;
    infile.close();

    // incrementing the version number
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
    copyFile(prevIndexPath, newIndexPath);

    // to get current time
    auto currTime = std::chrono::system_clock::now();
    time_t time = std::chrono::system_clock::to_time_t(currTime);
    string Time = ctime(&time);

    // copying the commit time in log.txt
    string log_file = cwd + "/git/log.txt";
    outfile.open(log_file, ios::app);

    // writing commit time into log file
    string toLog = "Commit No:" + to_string(v_no - 1) + "Commit Time: " + Time;
    outfile << toLog;
    outfile.close();

    added = false;
}