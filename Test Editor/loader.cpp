#include "loader.h"

#include <stdlib.h>

enum fArguments{
    argType,
    argSpriteName,
    argSpriteWidth,
    argSpriteHeight,
    argObjectWidth,
    argObjectHeight,
    argPositionX,
    argPositionY
};

string* ReadFile(string source){
	
	vector<int> placement;

	for(unsigned int i = 0;i < source.size();i ++){
		if(source[i] == '|' || source[i] == ':')
			placement.push_back(i);
			
	}

	if(placement.size() > 0){

        //Number of Arguments From File, num of | + 1
        int ar_size = placement.size() + 1;

        //Create Pointer String
		string* _split = new string[ar_size];	

        //Set Position Of The Splitter
		int lPos = 0;

		for(unsigned int i = 0; i < ar_size;i ++){
            //Split
			_split[i] = source.substr(lPos, placement[i] - lPos);

            //Set lPos +1 To Skip Over '|'
			lPos = placement[i] + 1; 
		}

		return _split;

	}else{
		return 0;
	}

}

Object* GetObject (string id){

    //Read Arguments From Line, (Array)
	string* Items = ReadFile(id);

    //Create Pointer To Return
    Object* _Obj;

    //Get Object Type
    if (Items[argType] == "_P")
        _Obj = new Player();

    else if (Items[argType] == "BG")
        _Obj = new BackGround( Items[argSpriteName], atoi(Items[argSpriteWidth].c_str()), atoi(Items[argSpriteHeight].c_str()), atoi(Items[argObjectWidth].c_str()), atoi(Items[argObjectHeight].c_str()) );

    else if (Items[argType] == "FG")
        _Obj = new ForeGround( Items[argSpriteName], atoi(Items[argSpriteWidth].c_str()), atoi(Items[argSpriteHeight].c_str()), atoi(Items[argObjectWidth].c_str()), atoi(Items[argObjectHeight].c_str()) );

    //Set Out Objects Position
    _Obj->Position.X = atof( Items[argPositionX].c_str());
    _Obj->Position.Y = atof( Items[argPositionY].c_str());

	delete [] Items;

	return _Obj;
}

namespace Map{

	bool LoadMap(const string& fname, vector<Object*>& Objects){
		bool success = true;

		std::fstream file;
		file.open(fname.c_str(), std::fstream::in);

        if(file.is_open()){

            string id;
            while(getline(file,id)){
                Objects.push_back(GetObject(id));
            }

        }

        file.close();
        
		return success;
	}

    bool SaveMap(string& fname, vector<Object*>& Objects){
        bool success = true;

        if(fname != "n"){

            std::fstream file;
            file.open(fname + ".map", std::fstream::out | std::fstream::trunc); 

            for(unsigned int i = 0;i < Objects.size();i ++){
                
                string info = "";
                if(dynamic_cast<BackGround*>(Objects[i]))
                    info = "BG";
                if(dynamic_cast<ForeGround*>(Objects[i]))
                    info = "FG";
                if(dynamic_cast<Player*>(Objects[i]))
                    info = "_P";

                file<<info<<"|"<<Objects[i]->Sprite.Name<<"|"<<Objects[i]->Sprite.Size.Width<<":"<<Objects[i]->Sprite.Size.Height<<"|"<<Objects[i]->Width<<":"<<Objects[i]->Height<<"|"<<Objects[i]->Position.X<<":"<<Objects[i]->Position.Y<<"\n";

            }

            file.close();
        }

        return success;
    }

}