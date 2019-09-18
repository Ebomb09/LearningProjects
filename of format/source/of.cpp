#include "of.h"
#include <iostream>

void strSplit(const string& input, char delim, string& ref1, string& ref2){

	//Check each char for delimiter
	for(unsigned int i = 0;i < input.size();i ++){
		
		//When found split in half and remove unused spaces
		if(input[i] == delim){
			ref1 = strRemoveBuffer(input.substr(0, i));
			ref2 = strRemoveBuffer(input.substr(i + 1, input.size() - i + 1));
			break;
		}
	}
}

string strRemoveBuffer(const string& input){
	int start = 0;
	int end = input.size();
	
	//Start from start till find non-empty space
	for(unsigned int i = 0;i < input.size();i ++){
		
		if(input[i] == ' ' || input[i] == '\t')
			start = i + 1;
			break;
	}	
	
	//Start from end till find non-empty space
	for(unsigned int i = input.size() - 1;i >= 0;i --){
		
		if(input[i] == ' ' || input[i] == '\t')
			end = i - 1;
			break;
	}
	
	//Return start and end locations, add one for minimum length
	return input.substr(start, end - start + 1);
}

OF::OF(string fname){
	
	//Get data from file
	fstream file;
	file.open(fname.c_str(), fstream::in);
	
	//store string
	string temp;
	
	//Hold Data To Be Stored
	ofObject* startObject = 0;
	ofObject* tempObject = 0;
	ofNode* tempNodes = 0;
	
	//Cycle Through Lines of File
	while(std::getline(file, temp)){
		
		for(unsigned int i = 0;i < temp.size();i ++){
			
			//Add Properties
			if(temp[i] == '='){
				string Key;
				string Value;
				strSplit(temp, '=', Key, Value);
				tempNodes = new ofNode{Key, Value, tempNodes};
			}

			//Finish With Object
			if(temp[i] == '}'){
				tempObject = new ofObject(tempNodes, tempObject);
				tempNodes = 0;

				if(!startObject)
					startObject = tempObject;
			}
			
		}
	}

	//Finished Reading
	file.close();
	
	//Count Objects
	ofObject* store = startObject;
	int _c = 1;

	while(store->Next){
		store = store->Next;
		_c ++;
	}
	Count = _c;

	//Set Object Pointer as array
	Objects = new ofObject*[Count];

	//Change from nodal to array
	store = startObject;
	_c = 0;

	do{
		Objects[_c] = store;
		_c++;
		store = store->Next;
	}while(store);
}

OF::~OF(){
	delete[] Objects;
}

string OF::GetValue(const int& index, const string& Key){
	return Objects[index]->GetValue(Key);
}

void OF::GetKeys(const int& index, string* _k, int& _c){
	Objects[index]->GetKeys(_k, _c);
}

int OF::GetObjectCount(){
	return Count;
}

ofObject::ofObject(ofNode* Nodes, ofObject* _n){
	//Store Other ofObjects
	Next = _n;
	
	//Count Nodes Connected
	int _c = 1;
	ofNode* store = Nodes;
	while(store->Next){
		store = store->Next;
		_c ++;
	}
	
	//Creater Pointers For Their Values
	Count = _c;
	Keys = new string[Count];
	Values = new string[Count];

	//Store Their Values	
	_c = 0;
	store = Nodes;
	do{
		Keys[_c] = store->Key;
		Values[_c] = store->Value;
		
		store = store->Next;
		_c ++;
	}while(store);
		
	//Clear Node Chain
	Nodes->Clear();
}

ofObject::~ofObject(){
	delete[] Keys;
	delete[] Values;
}

string ofObject::GetValue(const string& Key){
	
	for(unsigned int i = 0;i < Count;i ++){
		
		if(Keys[i] == Key){
			return Values[i];
		}
	}
}

void ofObject::GetKeys(string* _k, int& _c){
	_k = Keys;
	_c = Count;
}

void ofNode::Clear(){
	
	if(Next)
		Next->Clear();
	
	delete this;
}