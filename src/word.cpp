#include "word.h"

namespace fab
{

	Word::Word() {
	}

	Word::~Word() {
	}
	
	fab::Word::Word(ofVec2f pos, std::string string) {
		this->pos = pos;
		this->string = string;
	}


	void fab::Word::drawPDF() {
		//ofSetColor(color); TODO add colors
		font.drawStringAsShapes(string, pos.x, pos.y);
	}
	
	void fab::Word::draw() {
		//ofSetColor(color); TODO add colors
		font.drawString(string, pos.x, pos.y);
	}
}