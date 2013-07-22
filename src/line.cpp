#include "line.h"

namespace fab {

	Line::Line() {
	}

	Line::~Line() {
	}

	void Line::drawPDF() {
		int size = words.size();
		for(int i = 0; i < size; ++i) {
			words.at(i).drawPDF();
		}
	}
	
	void Line::draw() {
		int size = words.size();
		for(int i = 0; i < size; ++i) {
			words.at(i).draw();
		}
	}

}

void fab::Line::addNewWord(std::string string) {
}
void fab::Line::addNewWord(Word word) {
	words.push_back(word);
}

