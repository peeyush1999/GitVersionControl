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


//======================================
Notes : Error Handling is not implemented for sha calculation.

steps To calculate Sha of file : pass correct path for that file to get_sha () function in string format.
