	dirs = os.listdir(path)
				for file in dirs:
								checkfile=path+"/"+file
								if(os.path.isfile(checkfile)):
												if(map.get(file)==None):
																print(Fore.RED+"untracked : " +file)
																untracked.append(file)
												else:
																sha1 = hash_file(file)
																if(map.get(file)==sha1):
																				print(Fore.GREEN+"newfile added : " +file)
																				newfile.append(file)
																else:
																				print(Fore.RED+"modified : " +file)
																				modified.append(file)