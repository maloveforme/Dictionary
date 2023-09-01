#include "test.h"

int main()
{
	GetAPI getapi;
	GetVocabulary getvocabulary;
	getvocabulary.SetVocabulary();
	Test tst;
	
	tst.Run(getapi, getvocabulary);
}