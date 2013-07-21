#include "line.h"

namespace fab
{

Line::Line()
{
}

Line::~Line()
{
}


}

void fab::Line::addNewWord(std::string string) {
}
void fab::Line::addNewWord(Word word) {
	words.push_back(word);
}
