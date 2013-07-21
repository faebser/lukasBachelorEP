#ifndef LINE_H
#define LINE_H

#include "ofVec2f.h"
#include "ofTrueTypeFont.h"
#include "word.h"

namespace fab
{

class Line
{
public:
	Line();
	Line(ofVec2f pos);
	void SetFonts(const std::vector<ofTrueTypeFont>& fonts) {
		this->fonts = fonts;
	}
	void SetPos(const ofVec2f& pos) {
		this->pos = pos;
	}
	void SetDirection(int type) {
		this->type = type;
	};
	void addNewWord(std::string string);
	void addNewWord(Word word);
	void draw();
	~Line();
	
	enum Type {
	    LEFTTORIGHT,
	    RIGHTTOLEFT
	};
private:
	ofVec2f pos;
	std::vector<Word> words;
	std::vector<ofTrueTypeFont> fonts;
	int type;
};
}

#endif // LINE_H
