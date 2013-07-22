#ifndef WORD_H
#define WORD_H

#include "ofVec2f.h"
#include "ofColor.h"
#include "ofTrueTypeFont.h"

namespace fab
{

class Word
{
public:
	Word();
	Word(ofVec2f pos, std::string string);
	void SetColor(const ofColor& color) {
		this->color = color;
	}
	void SetFont(const ofTrueTypeFont& font) {
		this->font = font;
	}
	void SetPos(const ofVec2f& pos) {
		this->pos = pos;
	}
	void SetString(const std::string& string) {
		this->string = string;
	}
	void draw();
	void drawPDF();
	~Word();

private:
	ofVec2f pos;
	std::string string;
	
	ofColor color;
	ofTrueTypeFont font;
};
}

#endif // WORD_H
