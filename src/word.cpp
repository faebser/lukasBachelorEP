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
		ofSetColor(color);
		font.drawStringAsShapes(string, pos.x, pos.y);
	}
	
	void fab::Word::draw() {
		ofSetColor(color);
		font.drawString(string, pos.x, pos.y);
	}
}