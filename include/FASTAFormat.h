#pragma once
#include<string>

using namespace std;
/**
Class imeplements reader for FASTA file format.
*/
class FASTAFormat
{
private:
	string sequenceID;
	string description;
	string sequence;
public:
	/*
	Public constructor
	*/
	FASTAFormat(void);
	/*
	Public destructor
	*/
	~FASTAFormat(void);
	/**
	Method adds header for sequence
	*/
	void addHeader(string);
	/**
	Method return sequence ID
	*/
	string getSequenceID();
	/**
	Method add sequence to object. Method gets one parameter, string object of sequence
	*/
	void addSequence(string);
	/**
	Method return string object - sequence
	*/
	string getSequence();
	/**
	Method read FASTA file. Method gets one parameter, path to the FASTA file
	*/
	void readFASTAFile(string);

	/**
	Method character array of sequence
	*/
	const char* sequenceToCharArray();
};

