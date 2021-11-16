# GitVersionControl


File Structure :

------>main.cpp (entry point of our program)
		|-----> headers.h
		|-----> misc.h
		|-----> init.h
		|-----> commit.h
		|
		|
		|
		|-----> int main() 




------>misc.h
		|-----> string sha1(string)
		|-----> string &get_file(string name)
		|----->	string get_sha(string filepath) 
		|-----> int check(int , const char* )
		|-----> void copyFile(string , string)
		|-----> void fetch_file(int, string, vector<string>, string)
		

------>init.h
		|-----> void git_init()


------>commit.h
		|-----> void git_commit()

	


//======================================
Notes : Error Handling is not implemented for sha calculation.

steps To calculate Sha of file : pass correct path for that file to get_sha () function in string format.