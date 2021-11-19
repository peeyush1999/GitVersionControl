// void copyFile(string SfilePath, string DfilePath)
// {
//     int source = open(SfilePath.c_str(), O_RDONLY, 0);
//     int dest = open(DfilePath.c_str(), O_WRONLY | O_CREAT, S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
//     struct stat stat_source;
//     fstat(source, &stat_source);
//     sendfile(dest, source, 0, stat_source.st_size);
//     chmod(DfilePath.c_str(), stat_source.st_mode);
//     chown(DfilePath.c_str(), stat_source.st_uid, stat_source.st_gid);
//     close(source);
//     close(dest);
// }
// bool checkDir(string file)
// {
//     struct stat fileInfo;
//     check(stat((const char *)file.c_str(), &fileInfo), "unable to get file details");
//     return ((fileInfo.st_mode & S_IFMT) == S_IFDIR);
// }
// void copyDirectory(string SfilePath, string DfilePath)
// {
//     DIR *dir;
//     struct dirent *diread;
//     struct stat stat_source;

//     // Use stat() to get the info
//     check(stat((const char *)SfilePath.c_str(), &stat_source), "source file path does not exixts");
//     check(mkdir((const char *)DfilePath.c_str(), stat_source.st_mode), "unable to create directory");

//     if ((dir = opendir(SfilePath.c_str())) != nullptr)
//     {
//         while ((diread = readdir(dir)) != nullptr)
//         {
//             string SnextD = SfilePath + "/" + diread->d_name;
//             string DnextD = DfilePath + "/" + diread->d_name;
//             if (!(strcmp(diread->d_name, ".")) || !(strcmp(diread->d_name, "..")))
//                 continue;
//             if (!checkDir(SnextD))
//                 copyFile(SnextD, DnextD);
//             else
//                 copyDirectory(SnextD, DnextD);
//         }
//         closedir(dir);
//     }
//     else
//     {
//         perror("opendir");
//     }
// }
// void copyFileandDir(vector<string> files, string spath, string dpath)
// {

//     for (int i = 0; i < files.size() - 1; i++)
//     {
//         string SfilePath = spath + "/" + files[i];
//         string DfilePath = dpath + "/" + files[i];
//         if (checkDir(SfilePath))
//         {
//             copyDirectory(SfilePath, DfilePath);
//         }
//         else
//         {
//             copyFile(SfilePath, DfilePath);
//         }
//     }
// }
void git_push()
{
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

    if (ver_num == "0")
    {
        cout << YELLOW("No commits yet");
        exit(0);
    }

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

    string push_dir = cwd + "/push";

    struct stat sb;
    stat(push_dir.c_str(), &sb);
    bool isdir = S_ISDIR(sb.st_mode);

    if (!isdir)
    {
        // storing the files and their sha which are pushed
        string pushFile = cwd + "/git/push.txt";
        ofstream push_file(pushFile.c_str());
        for (auto name : fileDetails)
            push_file << name.first << " " << name.second[0];
        push_file.close();

        // getting filenames which are needed to be pushed
        vector<string> filenames;
        for (auto name : fileDetails)
            filenames.push_back(name.first);

        check(mkdir(push_dir.c_str(), 0777), "unable to create directory");
        // copyFileandDir(filenames, path, push_dir);
    }
    else
    {
    }
}