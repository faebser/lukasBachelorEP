#pragma once

#include "ofMain.h"
//#include "ofxCairo.h"
#include "json/json.h"
#include <FTGL/ftgl.h>
#include "word.h"
#include "line.h"

class testApp : public ofBaseApp {

	public:
		void setup();
		void update();
		void draw();

		void keyPressed  (int key);
		void keyReleased(int key);
		void mouseMoved(int x, int y );
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void windowResized(int w, int h);
		void dragEvent(ofDragInfo dragInfo);
		void gotMessage(ofMessage msg);
		
		void reloadAllConfig();
		void newPair(int index);
		
		std::string getRandomStringFromTrack(std::string name);
		ofVec2f getRandomMovementFromTrack(std::string name);
		ofTrueTypeFont getRandomFontFromTrack(std::string name);
		ofColor getRandomColorFromTrack(std::string name);
		
		ofTrueTypeFont mainFont;
		std::vector<ofTrueTypeFont> fonts;
		ofColor mainColor;
		std::vector<ofColor> colors;
		Json::Reader reader;
		Json::Value config;
		ofFile jsonFile;
		
		std::vector<fab::Line> leftLines, rightLines;
		std::string leftString, rightString;
		
		std::vector<std::string> machinesOf, uberMorrow, geometrie, retina;
		std::vector<ofVec2f> movMachinesOf, movUberMorrow, movGeometrie, movRetina;
		
		int amountOfLines = 150; // put into json
		float timeToLife = 1.46;
		
		const float inchToCmScale = 2.54;
		
		bool pdfTest = false;
		
		// calculate the size
		// 1 inch = 2.54 centimeters
		float printHeight; // size in cm
		float printWidth; // size in cm
		float dpi; // dots per inch
		
		float virtualHeight; // height in pixels of the output-PDF
		float virtualWidth; // width in pixels of ouput PDF
		
};
