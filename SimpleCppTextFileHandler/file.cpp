#include "file.hpp"

string readFile(string filename){

  std::ifstream ifs(filename);
  std::string content( (std::istreambuf_iterator<char>(ifs) ),
                       (std::istreambuf_iterator<char>()    ) );

  return(content);
}

void writeFile(string filename, string content){
	ofstream file;
	file.open(filename);
	file << content;
	file.close();
	return;
}


