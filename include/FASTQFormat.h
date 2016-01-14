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
	/**
	Public constructor
	*/
	FASTQFormat(void);
	/**
	Public destructor
	*/
	~FASTQFormat(void);
	/**
	Method return sequence ID
	*/
	void setSequenceID(string);
	/**
	Method adds string to current object. Method gets one parameter, string object of sequnece
	*/
	void setSequence(string);
	/**
	Method adds description string to current object. Method gets one parameter, string object of description
	*/
	void setDescription(string);
	/**
	Method adds string to current object. Method gets one parameter, string object - quality of sequence
	*/
	void setQualityOfSequence(string);
	/**
	Method return string object - sequence ID
	*/
	string getSequenceID(void);
	/**
	Method return string object - sequence
	*/
	string getSequence(void);
	/**
	Method return string object - description of sequence
	*/
	string getDescription(void);
	/**
	Method return string object - quality of sequnece
	*/
	string getQualityOfSequence(void);
	/**
	Method return character array - sequence
	*/
	const char* sequneceToCharArray(void);
	void readFASTQFile(string);
};