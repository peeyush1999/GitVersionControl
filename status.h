string hash_file(string str) {
    string hash = "";
    return hash;
}
inline bool exists_test3 (const std::string& name) {
    struct stat buffer;
    return (stat (name.c_str(), &buffer) == 0);
}

void git_status()
{
    
    char cwd[PATH_MAX];
    getcwd(cwd, sizeof(cwd));
    char path[PATH_MAX];
    // cout<<"hello";
    strcat(path, cwd);
    char *p = "/git/ver.txt";
    strcat(path, p);
    //strcpy(path,p);
    FILE *fptr = fopen(path, "r");
    //cout<<path<<endl;
    //cout<<fptr<<endl;


    char * line = NULL;
    size_t len = 0;
    ssize_t read;

    string data = "";
    while ((read = getline(&line, &len, fptr)) != -1) {    data.push_back(*line);   }
    line = NULL;
    //cout<<data<<endl<<line;
    string path1 = "";

    path1.append(cwd);
    //cout<<endl<<path1<<" line 38 "<<endl;
    char *p1 = "/git/version/v_";
    path1.append(p1);
    //       cout<<endl<<path1<<" line 41 "<<endl;

    path1.append(data);
    //     cout<<endl<<path1<<" line 43 "<<endl;


    string ind_file = "";
    ind_file.append(path1);
    ind_file.append("/index.txt");
    FILE *findex;
    char ind[ind_file.length() + 1];
    for (int i = 0; i < ind_file.length(); i++) {ind[i] = ind_file[i]; }
    //cout<<endl<<path1<<endl;
    ind[ind_file.length()] = '\0';

    findex = fopen(ind, "r");
    //
    //cout<<endl<<ind<<endl;
    data = "";
    len = 0;
    int c = 0;
    string prev, curr;
    map<string, string> map1;

    std::ifstream file(ind);
    string str;
    while (getline(file, str)) {
        stringstream ss(str);
        string word;
        //cout<<str[1]<<endl;
        while (ss >> word) {
            if (c >= 2)break;
            prev = curr;
            curr = word;
            if (c == 1)    // cout << prev << endl<<curr<<endl;
                // map1.insert(prev,curr);
                map1[prev] = curr;
            c++;
        }
        c = 0;
    }

    vector<string> untracked;
    vector<string> newfile;
    vector<string> modified;



    DIR *dir;
    struct dirent *ent;
    if ((dir = opendir (cwd)) != NULL) {
        /* print all the files and directories within directory */
        while ((ent = readdir (dir)) != NULL) {
            // printf ("%s\n", ent->d_name);
            string current = ent->d_name;
            string checkfile;
            checkfile.append(cwd);
            checkfile.push_back('/');
            checkfile.append(current);
            if (exists_test3(checkfile)) {
                //cout<<endl<<checkfile<<endl;
                auto it = map1.find(current);
                if (it == map1.end()) {
                    cout << "untracked : " << current << endl;
                    untracked.push_back(current);
                    // cout<<endl;
                } else {
                    string sha1 = hash_file(current);
                    //cout<<sha1<<endl;
                    if (map1.find(current)->second == sha1) {
                        cout << "newfile added : " << current << endl;
                        newfile.push_back(current);
                    } else {
                        cout << "modified : " << current << endl;
                        modified.push_back(current);
                    }



                }



            }
        }
    }
}
