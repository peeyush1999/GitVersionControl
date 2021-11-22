void git_push()
{

    string add_commit = cwd + "/git/add_commit.txt";
    ifstream add_commit_file(add_commit.c_str());
    string check_bit;
    add_commit_file >> check_bit;
    add_commit_file.close();

    if (check_bit == "00")
    {
        cout << "Please add and commit first" << endl;
        exit(0);
    }

    if (check_bit == "10")
    {
        cout << "Please commit first" << endl;
        exit(0);
    }

    char tmp[256];
    getcwd(tmp, 256);
    string cwd = tmp;

    ifstream infile;
    infile.open(cwd + "/git/version.txt", ios::in);

    //to store the version of the current folder
    string ver_num;

    if (infile.is_open())
        infile >> ver_num;
    else
    {
        cout << RED("cannot open file");
        exit(-1);
    }
    infile.close();


    // getting data about files from index file of current version
    string path = cwd + "/git/version/v_" + ver_num;
    string indexPath = path + "/index.txt";

    infile.open(indexPath, ios::in);
    if (!infile.is_open())
    {
        cout << RED("cannot open index file");
        exit(-1);
    }

    // filename -> [sha , rootversion , O , rootversion , next versions]
    string line;
    unordered_map<string, vector<string>> fileDetails;
    while (getline(infile, line))
    {
        vector<string> items;
        string item;
        stringstream ss(line);

        getline(ss, item, ' ');
        string fname = item;

        while (getline(ss, item, ' '))
        {
            items.push_back(item);
        }
        fileDetails[fname] = items;
    }
    infile.close();

    string push_dir = push_directory + "/push";

    struct stat sb;
    stat(push_dir.c_str(), &sb);
    bool isdir = S_ISDIR(sb.st_mode);

    if (!isdir) //This is the first push
    {
        // storing the files and their sha which are pushed in push_file.txt
        string pushFile = cwd + "/git/push_file.txt";
        ofstream push_file(pushFile.c_str());
        for (auto name : fileDetails)
            push_file << name.first << " " << name.second[0] << "\n";
        push_file.close();

        // getting filenames which are needed to be pushed
        vector<string> filenames;
        for (auto name : fileDetails)
            filenames.push_back(name.first);

        // creating push directory in the specified path
        check(mkdir(push_dir.c_str(), 0777), "unable to create directory");

        // pushing the files to the push directory
        for (auto name : fileDetails)
            fetch_file_push(ver_num, name.first, name.second, push_dir);
    }
    else //This occurs for nth push other than one
    {
        // getting filenames and their sha
        string pushFile = cwd + "/git/push_file.txt";
        infile.open(pushFile, ios::in);
        unordered_map<string, string> pushfileDetails;

        line = "";

        while (getline(infile, line))
        {
            string fname, sha;
            stringstream ss(line);
            getline(ss, fname, ' ');
            getline(ss, sha, ' ');
            pushfileDetails[fname] = sha;
        }
        infile.close();

        // comparing the sha of push_file and index file of current
        for (auto name : fileDetails)
        {
            // If the file is newly introduced we are just pushing it to the push directory
            if (pushfileDetails.find(name.first) == pushfileDetails.end())
                fetch_file_push(ver_num, name.first, name.second, push_dir);
            else
            {
                // If the file is changed then we are just pushing the changed file
                // to the push directory
                if (pushfileDetails[name.first] != name.second[0])
                    fetch_file_push(ver_num, name.first, name.second, push_dir);
            }
        }
        // delete the file in push_directory if deleted in working directory
        for (auto name : pushfileDetails)
        {
            if (fileDetails.find(name.first) == fileDetails.end())
            {
                string fpath = push_dir + "/" + name.first;
                remove(fpath.c_str());
            }
        }

        // updating the push_file.txt
        ofstream push_file(pushFile.c_str());
        for (auto name : fileDetails)
            push_file << name.first << " " << name.second[0] << "\n";
        push_file.close();
    }

    ofstream add_commit_file_out(add_commit.c_str());
    add_commit_file_out << "00";
    add_commit_file_out.close();
}