vector<string> stringToken( string s , char tok)
{
	vector<string> token;
	string tmp="";
	for(char ch : s)
	{
		if(ch == tok)
		{
			token.push_back(tmp);
			tmp="";
			continue;
		}

		tmp+=ch;
	}
	if(tmp!="")
	{
		token.push_back(tmp);
	}

	return token;
}
string sha1(string s)
{

    SHA1 checksum;
    checksum.update(s);
    return checksum.final();

}
string& get_file(string name) {
    string *s = new std::string;
    s->reserve(1024);
    fstream fp;


    fp.open(name, std::ios::in);
    if (!(fp.is_open())) {
        fprintf(stderr, "Unable to open the file\n");
        exit(EXIT_FAILURE);
    }
    else {
        std::string line;
        while (fp >> line) {
            s->append(line);
        }
    }
    fp.close();
    return *s;
}
string get_sha(string filepath)
{
    string *buffer = &(get_file(filepath));
    return sha1(*buffer);
}




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




void fetch_file(string vno, string filename, vector<string> list1, string path1)
{

    string v_no = vno;
    vector<string> list(list1.begin()+3,list1.end());
    //no changes required to file in current version
    if(list.size()!=0  && (list[ list.size() -1 ] == v_no ) )
    {
    	list.pop_back();
    }

    //if this is the very first change
    if(list.size()==1)
    {
    	//path where the file introduced for the first time....
    	string parent_path = cwd + "/git/version/v_" + list[0] + "/"+filename;

    	string bash_cmd ="diff "+parent_path+" "+ cwd+"/"+filename + " > " + path1+"/"+filename;
    	system(&bash_cmd[0]);

    	LOGC("Command Executed : "+bash_cmd);
    }
    else
    {
		string parent_path = cwd + "/git/version/v_";
		string temp_file   = cwd + "/git/version/temp";

		// patch <parent_file> <changes file of prev version> ---------------------------
		string generate_file_cmd = "patch "+ parent_path + list[0] + "/" + filename + " " + parent_path + list[1] + "/" + filename + " -o " + temp_file + "2;";
        int i=2;

        while(i<list.size())
        {
            generate_file_cmd += "patch "+temp_file+to_string(i)+" "+parent_path+list[i]+"/"+filename+" -o "+temp_file+to_string(i+1)+";";
            i++;
        }

        LOG(CYAN(generate_file_cmd));

        system(&generate_file_cmd[0]);

        generate_file_cmd = "diff "+temp_file+to_string(i)+" "+cwd+"/"+filename + " > " + path1 + "/" + filename;  

        system(&generate_file_cmd[0]);
        LOG(CYAN(generate_file_cmd));
    }

}


void retrieve_file(string vno, string filename, vector<string> list1, string path1)
{
    string v_no = vno;
    vector<string> list(list1.begin()+3,list1.end());
    //no changes required to file in current version
    if(list.size()!=0  && (list[ list.size() -1 ] == v_no ) )
    {
        list.pop_back();
    }
    if(list.size()==1)
    {
        //path where the file introduced for the first time....
        string parent_path = cwd + "/git/version/v_" + list[0] + "/"+filename;
        LOG(parent_path);
        string bash_cmd ="cp "+parent_path+" "+ cwd+"/"+filename;
        system(&bash_cmd[0]);

        LOGC("Command Executed : "+bash_cmd);
    }
    else
    {
        string parent_path = cwd + "/git/version/v_";
        string temp_file   = cwd + "/git/version/temp";

        // patch <parent_file> <changes file of prev version> ---------------------------
        string generate_file_cmd = "patch "+ parent_path + list[0] + "/" + filename + " " + parent_path + list[1] + "/" + filename + " -o " + temp_file + "2;";
        int i=2;

        while(i<list.size())
        {
            generate_file_cmd += "patch "+temp_file+to_string(i)+" "+parent_path+list[i]+"/"+filename+" -o "+temp_file+to_string(i+1)+";";
            i++;
        }

        LOGC(generate_file_cmd);

        system(&generate_file_cmd[0]);

        generate_file_cmd = "mv "+temp_file+to_string(i)+" "+cwd+"/"+filename;

        system(&generate_file_cmd[0]);
        LOGC(generate_file_cmd);
    }
}
void fetch_file_push(string vno, string filename, vector<string> list1, string path1)
{

    string v_no = vno;
    vector<string> list(list1.begin() + 3, list1.end());

    //if this is the very first change
    if (list.size() == 1)
    {
        //path where the file introduced for the first time....
        string parent_path = cwd + "/git/version/v_" + list[0] + "/" + filename;

        string bash_cmd = "cp " + parent_path + " " + path1 + "/" + filename;
        system(&bash_cmd[0]);

        LOGC("Command Executed : " + bash_cmd);
    }
    else
    {
        string parent_path = cwd + "/git/version/v_";
        string temp_file = cwd + "/git/version/temp";

        // patch <parent_file> <changes file of prev version> ---------------------------
        string generate_file_cmd = "patch " + parent_path + list[0] + "/" + filename + " " + parent_path + list[1] + "/" + filename + " -o " + temp_file + "2"+" > /dev/null;";
        int i = 2;

        while (i < list.size())
        {
            generate_file_cmd += "patch " + temp_file + to_string(i) + " " + parent_path + list[i] + "/" + filename + " -o " + temp_file + to_string(i + 1) + " > /dev/null;";
            i++;
        }

        LOG(CYAN(generate_file_cmd));

        system(&generate_file_cmd[0]);

        string mov_file = "mv " + temp_file + to_string(i) + " " + path1 + "/" + filename;

        system(&mov_file[0]);
        LOG(CYAN(generate_file_cmd));
    }
}
vector<string> getAndSortFiles(string remote_directory)
{
    vector<string> files;
    DIR *dir;
    struct dirent **diread;
    int n, i;
    check(n = scandir(remote_directory.c_str(), &diread, 0, versionsort), "cannot able to scan the directory");
    for (int i = 0; i < n; ++i)
    {
        if (diread[i]->d_name == "." || diread[i]->d_name == "..")
            continue;
        files.push_back(diread[i]->d_name);
        free(diread[i]);
    }
    free(diread);
    return files;
}