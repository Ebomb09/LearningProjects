#include "ini.h"

INI::INI(string a) : FName(a), length(0){
    Open();
}

INI::~INI(){
    delete[] lines;
}

void INI::Open(){

	if(length != 0){
		delete[] lines;
	}
	
    fstream file;
    file.open(FName, fstream::in);
    file.seekg(0);
	
    string temp;
    while(std::getline(file, temp)){
        length ++;
    }
	
	if(length == 0){
		length = 1;
	}
    lines = new string[length];
    file.clear();
    file.seekg(0);

    int index = 0;
    while(std::getline(file, temp)){
        lines[index++] = temp;
    }

    file.close();
}

void INI::FindSection(string Section, int& Pos, int& End){
    bool found = false;

    Pos = -1;
    End = -1;

    for(int i = 0;i < length;i ++){

        for(int j = 0;j < lines[i].length();j ++){
            
            if(lines[i][j] == '['){

                if(!found && Section == lines[i].substr(1, lines[i].length() - 2)){
                    Pos = i;
                    found = true;
                    break;
                }else if(found){
                    End = i;
                    break;
                }
            }
        }

        if(found && End != -1){
            break;
        }

    }

    if(End == -1 && Pos != -1){
        End = length - 1;
    }else if(Pos == -1){
        //DEBUG
        //std::cout<<"Unable To Find Section {"<<Section<<"}\n";
    }
}

bool INI::Read(string Section, string Key, string& Out){
    bool good = false;

    int Pos;
    int End;
    FindSection(Section, Pos, End);

    if(Pos != -1){

        for(int i = Pos;i <= End;i ++){
            
            int kPos = lines[i].find("=");
            if(lines[i].substr(0,kPos) == Key){
                Out = lines[i].substr(kPos + 1, lines[i].length() - kPos);
                good = true;
                break;
            }
        }
    }

    if(!good){
        //DEBUG
        //std::cout<<"Unable to find Key {"<<Key<<"}\n";
    }

    return good;
}

bool INI::Write(string Section, string Key, string In){
    int Pos;
    int End;
    FindSection(Section, Pos, End);

    if(Pos != -1){
        bool found = false;
        int key = -1;

        for(int i = Pos;i <= End;i ++){
            
            int kPos = lines[i].find("=");
            if(lines[i].substr(0,kPos) == Key){
                found = true;
                key = i;
                break;
            }
        }

        if(key == -1){
            lines[Pos] += "\n" + Key + "=" + In;
            //DEBUG
            //std::cout<<"Created Key";
        }else{
            lines[key] = Key + "=" + In;
            //DEBUG
            //std::cout<<"Changed Key Value";
        }
    }else{
        lines[0] = "[" + Section + "]\n" +  Key + "=" + In + "\n" + lines[0];
        //DEBUG
        //std::cout<<"Create Section and Key";
    }
    fstream file;
    file.open(FName, fstream::out | fstream::trunc);

    for(int i = 0;i < length;i ++){
        if(lines[i] != ""){
            file<<lines[i]<<"\n";
        }
    }
    file.close();

    Open();
    return true;
}