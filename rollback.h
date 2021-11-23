void git_rollback()
{
	string version = cwd+"/git/version.txt";
	
	ifstream in(version);
	string v_no;
	in >> v_no;
	in.close();



	if(v_no=="1")
	{
		cout<<"No previous Vesion Present";
		return;
	}

	int vnum = stoi(v_no);

	string removePath = cwd+"/git/version/v_"+v_no; 
	//string prevVersion = to_string(vnum-1);


	string path1 =  cwd+"/git/version/v_"+to_string(vnum-1);
	string ind_file = path1 + "/index.txt";

	LOGY("CWD:"+cwd);
	LOGY("Path1 : "+path1);
	LOGY("index file:"+ind_file);

	unordered_map<string, vector<string> > mmap;
	ifstream index(ind_file);

	string line;

	// generating token from index File
	while(getline(index,line))
	{
		
		vector<string> parts = stringToken(line,' ');
		int len=parts.size();
		LOGP("----->"+parts[0]+" "+parts[1]);				
		for(int i=1;i<len;i++)
		{
			mmap[parts[0]].push_back(parts[i]);
			LOG("	|------>"+parts[i]);
		}
	}
	index.close();

	struct stat statbuf,checkFile;  
	struct dirent **namelist=NULL;
	int n = scandir(&cwd[0], &namelist, NULL, alphasort);
	vector<string> currDirItem;

	for(int i=0;i<n;i++)
	   {
	   		string filename(namelist[i]->d_name);
	       	stat(namelist[i]->d_name, &statbuf);
	       	currDirItem.push_back(filename);
	       	

	       	if(statbuf.st_mode & S_IFDIR)//True: Directory
	        {
	            continue;
	        }
	        else
	        {
	            // current object is file calculating sha
	        	//string sha = get_sha(filename);
	        	


	        	if(mmap.find(filename)==mmap.end())
	        	{
	        		LOGR(filename + " removed as not present in previous version!!");
                    string cmd="rm "+filename;
                    system(&cmd[0]);
                    LOGC(cmd);
	        	}
	        	else
	        	{
	        		
	        			//LOGR(filename+" "+sha+" file is modified!!!");		
	        			//mmap[filename][0]=sha;
	        			
        				LOG("Calling retrieve File!!!");
        				retrieve_file(v_no,filename,mmap[filename],path1);
	        				
	        	}


	            
	        }

	   }

	   string cmd="rm -r "+removePath;
	   system(&cmd[0]);

	   	string prevVersion = to_string(vnum-1);

		ofstream out(version, ios::trunc);
		out<<prevVersion;
		out.close();



	   cout<<GREEN("You are succesfully Rollbacked the Change!!! Now you are in version "+ prevVersion);

}