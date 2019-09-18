#ifndef OF_FORMAT
#define OF_FORMAT
	
	#include <fstream>
	using std::fstream;
	
	#include <string>
	using std::string;

	void strSplit(const string& input, char delim, string& ref1, string& ref2);
	string strRemoveBuffer(const string& input);

	//Temporary Storage To Hold Data without resizing arrays multiple times
	struct ofNode{
		string Key;
		string Value;

		ofNode* Next;
		
		void Clear();
	};

	//Main Elements Holds Important Object Data
	struct ofObject{
		string* Keys;
		string* Values;
		unsigned int Count;

		ofObject* Next;
		
		ofObject(ofNode* Nodes, ofObject* _n);
		~ofObject();
		
		string GetValue(const string& Key);
		void GetKeys(string* _k, int& _c);
	};
	
	//Main User Access
	class OF{
		ofObject** Objects;
		int Count;
		
		public:
			OF(string fname);
			~OF();
			string GetValue(const int& index, const string& Key);
			void GetKeys(const int& index, string* _k, int& _c);
			int GetObjectCount();
	};	

#endif