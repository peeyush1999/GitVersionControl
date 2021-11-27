# GitVersionControl


File Structure :

------>main.cpp (entry point of our program)
		|-----> headers.h
		|-----> misc.h
		|----->status.h
		|-----> init.h
		|-----> commit.h
		|-----> add.h 
		|-----> get_logs.h
		|-----> add_files.h
		|-----> git_diff.h
		|-----> push.h
		|-----> rollback.h
		|-----> int main() 




------>misc.h
		|-----> vector<string> stringToken( string, char)
		|-----> string sha1(string)
		|-----> string &get_file(string name)
		|----->	string get_sha(string filepath) 
		|-----> int check(int , const char* )
		|-----> void copyFile(string , string)
		|-----> void fetch_file(string, string, vector<string>, string)
		|-----> void retrieve_file(string, string, vector<string>, string)
		|-----> void fetch_file_push(string, string, vector<string>, string)
		|-----> void getAndSortFiles(string)
		|-----> void remove_git(string)
		|-----> void copy_git(string,string)
		|-----> bool check_dir(string)
		|-----> void update_remote_git(string src, string dest)
		|-----> void update_files_remote(string src, string dest)
		|-----> unordered_set<string> get_versions_folders(string path)

------>init.h
		|-----> void git_init()


------>commit.h
		|-----> void git_commit()

------>git_diff.h
		|-----> void getdiff(string, string, vector<string>, string)
		|----->	void git_diff()	
	
------>git_push.h
		|----->	void git_push()	

------>rollback.h
		|----->	void git_rollback()	

------>pull.h
		|----->	void git_pull()	

------>git_clone.h
		|-----> void create_remote_repo(string remote_repo_path)
		|----->	void git_clone(string remote_repo_path)	


//======================================
Notes : Error Handling is not implemented for sha calculation.

steps To calculate Sha of file : pass correct path for that file to get_sha () function in string format.


NOTEEEEEEE:
//================================================================
Each command should be executed in the following way
./main command path_of_the_local_repository 


why I changed ?
When working on dfferent local repos if I want to do any operation I need to have all my code in the current working repository.So if we pass the path as CLI we can make any changes for any repository without copying our whole code again to all the repositories.Please make changes to the commands on what you worked accordingly.

I found a problem in add command.There the files are accessed using relative path.So some error is coming.Make the files to be accessed using absolute path acoording to the given input i.e 'path_of_the_local_repository'.Similarly check for every command you worked on.




#Update: 26-November-2021
Steps to Install 'TeamRocket- Version Control System (trgit)'

- Provide Executable permission to 'install.sh' File.
- Execute 'install.sh'
- Once installed you can use it anywhere in your machine

Some Sample Commands:-
	- trgit init
	- trgit status
	- trgit add <filename>
	- trgit add .

==================================================
#### LIMITATION IN OUR PROJECT IS 'USER' NEED TO PULL BEFORE EVERY 'add' command  push after every commit command inorder to be updated w.r.t remote repo.Else our push,pull logic won't work 

Added clone command - syntax: ./main clone remote_repo_path
----> clone can be done only after 'init' same as original GIT.We need to clone whenever we create a new local repository.

added an extra command called 'create_repo'   
syntax: ./main create_repo remote_repo_path 
----> This will create a remote repository just like how we do in original GIT.This command is similar to the action (going to git website and creating the repository)