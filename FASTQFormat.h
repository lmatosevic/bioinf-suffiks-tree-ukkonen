#pragma once
#include<string>

using namespace std;
class FASTQFormat
{
private:
	string sequenceID;
	string sequence;
	string description;
	string qualityOfSequence;
public:
	FASTQFormat(void);
	~FASTQFormat(void);
	void setSequenceID(string);
	void setSequence(string);
	void setDescription(string);
	void setQualityOfSequence(string);
	string getSequenceID(void);
	string getSequence(void);
	string getDescription(void);
	string getQualityOfSequence(void);
	const char* sequneceToCharArray(void);
	void readFASTQFile(string);
};