void fetch_file(int vno, string filename, vector<string> list, string path1)
{

	char tmp[256];
    getcwd(tmp,256);
    string cwd(tmp);
    string v_no = to_string(vno);

    //no changes required to file in current version
    if(list.size()!=0  && (list[ list.size() -1 ] == to_string(v_no) ) )
    {
    	list.pop_back();
    }

    //if this is the very first change
    if(list.size()==1)
    {
    	//path where the file introduced for the first time....
    	string parent_path = cwd + "/git/version/v_" + list[0] + "/"+filename;

    	string bash_cmd ="diff "+parent_path+" "+ cwd+"/"+file + " > " + path1+"/"+file ;
    	system(&cmd[0]);

    	cout<<"Command Executed : "+bash_cmd<<endl;
    }
    else
    {
		string parent_path = cwd + "/git/version/v_";
		string temp_file   = cwd + "/git/version/temp";

		// patch <parent_file> <changes file of prev version> ---------------------------
		string generate_file_cmd = "patch "+ parent_path + list[0] + "/" + filename + " " + parent_path + list[1] + "/" filename + " -o " + temp_file + "2;";
        int i=2;

        while(i<list.size())
        {
            generate_file_cmd += "patch "+temp_file+to_string(i)+" "+parent_path+list[i]+"/"+filename+" -o "+temp_file+to_string(i+1)+";";
        }

        cout<<generate_file_cmd<<endl;

        system(generate_file_cmd);

        generate_file_cmd = "diff "+temp_file+to_string(i)+" "+cwd+"/"+filename + " > " + path1 + "/" + filename;  

        system(generate_file_cmd);
        cout<<generate_file_cmd;
    }

}