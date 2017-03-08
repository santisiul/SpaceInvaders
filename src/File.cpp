#include "File.h"

File::File(){
	nameFile = "saves.txt";
	readFile();
}
File::File(const File &file){
	nameFile = new char;
	nameFile = "saves.txt";
}

File::~File(){
	delete nameFile;
}


bool File::readFile(){
	ifstream file;
	file.open(nameFile);
//	string text ="";
	if (file.is_open())
	{
		 while(!file.eof()){
		 	string tmp;
		 	getline(file, tmp);
		 	addGamer(tmp);
		 	//cout<<tmp<<endl;
		 }
		 file.close();
	}
	else {
		//writeFile("");
	}
	return true;
}

bool File::writeFile(string cadena){
	ofstream file;
	file.open(nameFile);
	if (file.fail())
	{
		//cout << "ERROR: No se puedo realizar la apertura del archivo";
		return false;
	}
	else {
		file << cadena;
		file.close();
	}
	
	return true;
}

void File::addGamer(string cadena){
	gamers.push_back(cadena);
}

void File::save(){
	stringstream sstrm;
	for (int i = 0; i < gamers.size(); ++i)
	{
		sstrm <<gamers[i]<<endl;
	}
	writeFile(sstrm.str());
}

int File::getGamers(){
	return gamers.size();
}

string File::getGamer(int pos){
	if (getGamers() > 0)
	{
		return gamers[pos];
	}
	else return "error";
}