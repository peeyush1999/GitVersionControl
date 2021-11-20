void git_add_file(string filename)
{
	string version = cwd+"/git/version.txt";
	
	ifstream in(version);
	string v_no;
	in >> v_no;
	in.close();

	string path1 =  cwd+"/git/version/v_"+v_no;
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
	
    
    string filepath=filename;               //Path of given file.
	struct stat statbuf,checkFile;
	stat(filepath.c_str(), &statbuf);
	cout<<filepath<<endl;
	if(statbuf.st_mode & S_IFDIR)//True: Directory
	{
	    //do nothing
	} 
	else
	{

	    // file exists , calculating sha of file
		string sha = get_sha(filepath);
	
		if(mmap.find(filename)==mmap.end())
		{
			mmap[filename].push_back(sha);
			mmap[filename].push_back(v_no);
			mmap[filename].push_back("O");
			mmap[filename].push_back(v_no);
            copyFile(filename,path1+"/"+filename);
            LOGY(filename+" "+sha+" file is added!!!");
		}
		else                                        
		{
			if(mmap[filename][0]==sha)
			{
				LOGG(filename+" "+sha+" file is not modified!!!");		
				// continue;
			}
			else
			{
				LOGR(filename+" "+sha+" file is modified!!!");		
				mmap[filename][0]=sha;
				if(mmap[filename][1]==v_no)
					copyFile(filename,path1+"/"+filename);
				else
				{
					LOG("Calling Fetch File!!!");
					fetch_file(v_no,filename,mmap[filename],path1);
					
					int len = mmap[filename].size();
					if(mmap[filename][len -1]!=v_no)
						mmap[filename].push_back(v_no);		        				  
                }
            }
        }
    }


	

	// Updating the index file accordingly



	ofstream out(ind_file);
	for(auto it : mmap)
	{
		out<<(it.first);
		for(string s: it.second)
		{
			out<<" "<<(s);
		}
		out<<"\n";
	}
	out.close();


}