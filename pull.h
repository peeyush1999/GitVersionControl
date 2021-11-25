void git_pull()
{
    // to get remote repository path
    string add_commit = cwd + "/git/add_commit.txt";
    ifstream add_commit_file;
    add_commit_file.open(add_commit.c_str(), ios::in);
    string check_bit, push_directory;
    getline(add_commit_file, check_bit, ' ');
    getline(add_commit_file, push_directory, ' ');
    add_commit_file.close();

    // if the push_index file is empty (2 scenarios)
    // 1.newly initialized repositroy pulling from remote (taken care by pull command)
    // 2.newly initialized repository pushing for the first time (taken care by push command)

    string remote_dir = push_directory;
    string pushFile = cwd + "/git/push_index.txt";
    ifstream pushFilein(pushFile.c_str());
    string check_line;
    pushFilein >> check_line;
    pushFilein.close();

    if (check_line == "") // This is the first pull
    {
        // copying from remote repository
        vector<string> filenames = getAndSortFiles(remote_dir);
        unordered_map<string, string> fileDetails;

        for (string fname : filenames)
        {
            string fpath = remote_dir + "/" + fname;
            string bash_cmd = "cp " + fpath + " " + cwd + "/" + fname;
            system(&bash_cmd[0]);
            fpath = cwd + "/" + fname;
            string sha = get_sha(fpath);
            fileDetails[fname] = sha;
        }

        // upating the push_index file with filename->sha
        ofstream push_file(pushFile.c_str());
        for (auto name : fileDetails)
            push_file << name.first << " " << name.second << "\n";
        push_file.close();
    }
    else // This is nth pull other than first one
    {
        // getting filenames and their sha of local repo
        ifstream infile;
        infile.open(pushFile, ios::in);
        unordered_map<string, string> localfileDetails;

        string line;

        while (getline(infile, line))
        {
            string fname, sha;
            stringstream ss(line);
            getline(ss, fname, ' ');
            getline(ss, sha, ' ');
            localfileDetails[fname] = sha;
        }
        infile.close();

        // getting filedetails of remote repo
        vector<string> filenames = getAndSortFiles(remote_dir);
        unordered_map<string, string> remotefileDetails;

        for (string fname : filenames)
        {
            string fpath = remote_dir + "/" + fname;
            string sha = get_sha(fpath);
            remotefileDetails[fname] = sha;
        }

        for (auto fname : remotefileDetails)
        {
            // if the file is present in remote repo but not in local repo
            // copying from remote to local repo
            if (localfileDetails.find(fname.first) == localfileDetails.end())
            {
                string fpath = remote_dir + "/" + fname.first;
                string bash_cmd = "cp " + fpath + " " + cwd + "/" + fname.first;
                system(&bash_cmd[0]);
                fpath = cwd + "/" + fname.first;
                localfileDetails[fname.first] = get_sha(fpath);
            }
            else
            {
                // if sha is not matching then replacing the file with remote repo file
                if (localfileDetails[fname.first] != remotefileDetails[fname.first])
                {
                    string fpath = cwd + "/" + fname.first;
                    remove(fpath.c_str());
                    fpath = remote_dir + "/" + fname.first;
                    string bash_cmd = "cp " + fpath + " " + cwd + "/" + fname.first;
                    system(&bash_cmd[0]);
                    fpath = cwd + "/" + fname.first;
                    localfileDetails[fname.first] = get_sha(fpath);
                }
            }
        }

        // upating the push_index file with filename->sha
        ofstream push_file(pushFile.c_str());
        for (auto name : localfileDetails)
            push_file << name.first << " " << name.second << "\n";
        push_file.close();
    }

    string src = push_directory + "/git";
    string dest = cwd;
    string rmsrc = cwd + "/git";
    remove_git(rmsrc);
    copy_git(src, dest);

    cout << YELLOW_B("\t\tPulled Successfully!!!") << endl;
}