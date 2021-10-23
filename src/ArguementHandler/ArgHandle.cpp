#include "ArgHandle.hpp"

		vector<int> ArguementHandler::searchStringVector(vector<string> v, string q){
			vector<int> output;
			for(int i=0;i<v.size();i++){
				if(v[i] == q){output.push_back(i);}
			}
			return(output);
		}
		void ArguementHandler::printArgs(){
			for(int i=0;i<args.size();i++){
				cout<<args[i].type + " " + args[i].value<<endl;
			}
		}
		vector<Arguement> ArguementHandler::findArgs(string type){
			vector<Arguement> output;
			for(int i=0;i<args.size();i++){
				if(args[i].type == type){output.push_back(args[i]);}
			}
			return(output);
		}
		bool ArguementHandler::hasArg(string type){
			for(int i=0;i<args.size();i++){
				if(args[i].type == type){return(true);}
			}
			return(false);
		}
		ArguementHandler::ArguementHandler(int argc, char* argv[]){
			std::string current_exec_name = argv[0]; // Name of the current exec program
       			std::vector<std::string> all_args;
			if (argc > 1) {
				all_args.assign(argv + 1, argv + argc);
			}//more or less just finding the args

			for(int i=0;i<all_args.size();i++){
				if(all_args[i].substr(0,1) == "-" && i<all_args.size()-1){
					if(all_args[i+1].substr(0,1) == "-"){
						args.push_back(Arguement(all_args[i], ""));
					}else{	
						args.push_back(Arguement(all_args[i], all_args[i+1]));
						i++;
					}
				}else if(all_args[i].substr(0,1) == "-" && i>=all_args.size()-1){
					args.push_back(Arguement(all_args[i], ""));
				}else{
					args.push_back(Arguement("", all_args[i]));
				}
			}
		}

