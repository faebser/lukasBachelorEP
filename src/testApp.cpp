#include "testApp.h"

//--------------------------------------------------------------
void testApp::setup(){
	jsonFile.open(ofToDataPath("config.json"));
	
	ofBackground(255, 255, 255);
	ofSetColor(0);
	
	bool parsingSuccessful = reader.parse( jsonFile, config );
	if ( !parsingSuccessful )
	{
		// report to the user the failure and their locations in the document.
		std::cout  << "Failed to parse configuration\n"
				   << reader.getFormattedErrorMessages();
		return;
	}
	else {
		cout << "parsing successful!" << endl;
		reloadAllConfig();
	}
	
	// get first pair
	// push all the lines into the left and right stuff
	// draw them
	newPair(0);
}

//--------------------------------------------------------------
void testApp::update() {
	
}

//--------------------------------------------------------------
void testApp::draw(){
	int leftSize = leftLines.size();
	for(int i = 0; i < leftSize; ++i) {
		leftLines.at(i).draw();
	}
	
	int rightSize = rightLines.size();
	for(int i = 0; i < rightSize; ++ i) {
		rightLines.at(i).draw();
	}
	mainFont.drawString("hello World", 100, 100);
}

//--------------------------------------------------------------
void testApp::keyPressed(int key){

}

//--------------------------------------------------------------
void testApp::keyReleased(int key){

}

//--------------------------------------------------------------
void testApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void testApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void testApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void testApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void testApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void testApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void testApp::dragEvent(ofDragInfo dragInfo){ 

}
void testApp::reloadAllConfig() {
	
	cout << "reloading config" << endl;
	
	printHeight = config["print"]["height"].asInt();
	printWidth = config["print"]["width"].asInt();
	dpi = config["print"]["dpi"].asInt();
	
	virtualHeight = (printHeight * inchToCmScale) * dpi;
	virtualWidth = (printWidth * inchToCmScale) * dpi;
	
	cout << "clearing all the strings" << endl;
	machinesOf.clear();
	uberMorrow.clear();
	geometrie.clear();
	retina.clear();
	
	mainColor = ofColor(config["mainColor"]["r"].asInt(), config["mainColor"]["g"].asInt(), config["mainColor"]["b"].asInt());
	Json::Value jsonColors = config["colors"];
	int length = jsonColors.size();
	for(int i = 0; i < length; ++i) {
		//cout << "r " << jsonColors[i]["r"].asInt() /*<< " / g " << jsonColors[i]["g"].asInt() << " / b " << jsonColors[i]["b"].asInt()*/ << endl;
		colors.push_back(ofColor(jsonColors[i]["r"].asInt(), jsonColors[i]["g"].asInt(), jsonColors[i]["b"].asInt()));
	}
 
	mainFont.loadFont(ofToDataPath("LTe50186.ttf"), config["mainFont"]["size"].asInt(), true, true, true);
	Json::Value jsonFonts = config["fonts"];
	length = jsonFonts.size();
	for(int i = 0; i < length; ++i) {
		//cout << jsonFonts[i]["size"].asInt() << endl;
		ofTrueTypeFont newFont;
		newFont.loadFont(ofToDataPath("LTe50186.ttf"), jsonFonts[i]["size"].asInt(), true, true, true);
		fonts.push_back(newFont);
	}
	
	cout << "putting all the strings into the lists" << endl;
	
	Json::Value stringsForMachinesOf = config["text"]["machinesOf"];
	length = stringsForMachinesOf.size();
	cout << "adding " << length << " lines to machinesOf" << endl;
	for(int i = 0; i < length; ++i) {
		machinesOf.push_back(stringsForMachinesOf[i].asString());
	}
	
	Json::Value stringsForUberMorrow = config["text"]["uberMorrow"];
	length = stringsForUberMorrow.size();
	cout << "adding " << length << " lines to uberMorrow" << endl;
	for(int i = 0; i < length; ++i) {
		uberMorrow.push_back(stringsForUberMorrow[i].asString());
	}
	
	Json::Value stringsForGeometrie = config["text"]["geometrie"];
	length = stringsForGeometrie.size();
	cout << "adding " << length << " lines to geometrie" << endl;
	for(int i = 0; i < length; ++i) {
		geometrie.push_back(stringsForGeometrie[i].asString());
	}
	
	Json::Value stringsForRetina = config["text"]["retina"];
	length = stringsForRetina.size();
	cout << "adding " << length << " lines to retina" << endl;
	for(int i = 0; i < length; ++i) {
		retina.push_back(stringsForRetina[i].asString());
	}
	
	cout << "getting all the movement data" << endl;
	
	Json::Value movement = config["movement"];
	float scale = movement["scale"].asFloat();
	
	Json::Value movForRetina = config["movement"]["retina"];
	length = movForRetina.size();
	cout << "adding " << length << " vectors to retina" << endl;
	for(int i = 0; i < length; ++i) {
		movRetina.push_back(ofVec2f(movForRetina[i]["x"].asFloat() * scale, movForRetina[i]["y"].asFloat() * scale));
	}
	
	Json::Value movForMachinesOf = config["movement"]["machinesOf"];
	length = movForMachinesOf.size();
	cout << "adding " << length << " vectors to machinesOf" << endl;
	for(int i = 0; i < length; ++i) {
		movMachinesOf.push_back(ofVec2f(movForMachinesOf[i]["x"].asFloat() * scale, movForMachinesOf[i]["y"].asFloat() * scale));
	}
	
	Json::Value movForUberMorrow = config["movement"]["uberMorrow"];
	length = movForUberMorrow.size();
	cout << "adding " << length << " vectors to uberMorrow" << endl;
	for(int i = 0; i < length; ++i) {
		movUberMorrow.push_back(ofVec2f(movForUberMorrow[i]["x"].asFloat() * scale, movForUberMorrow[i]["y"].asFloat() * scale));
	}
	
	Json::Value movForGeometrie = config["movement"]["geometrie"];
	length = movForGeometrie.size();
	cout << "adding " << length << " vectors to geometrie" << endl;
	for(int i = 0; i < length; ++i) {
		movGeometrie.push_back(ofVec2f(movForGeometrie[i]["x"].asFloat() * scale, movForGeometrie[i]["y"].asFloat() * scale));
	}
	
	cout << "reloading config finished" << endl;
}
void testApp::newPair(int index) {
	cout << "getting pair at index: " << index << endl;
	Json::Value pair = config["pairs"][index];
	leftString = pair["left"].asString();
	rightString = pair["right"].asString();
	leftLines.clear();
	rightLines.clear();
	ofVec2f leftPos = ofVec2f(0, 0);
	ofVec2f rightPos = ofVec2f(ofGetWindowWidth(), 0);
	ofVec2f stepper = ofVec2f(0, ofGetWindowHeight() / amountOfLines);
	
	for(int i = 0; i < amountOfLines; ++i) {
		// add line to left-side
		fab::Line newLeftline = fab::Line();
		newLeftline.SetPos(leftPos);
		newLeftline.SetDirection(fab::Line::LEFTTORIGHT);
		float ttl = 0;
		while(ttl <= timeToLife) {
			std::string newString = getRandomStringFromTrack(leftString);
			cout << "adding string " << newString << "to left side" << endl;
			ofTrueTypeFont currentFont = getRandomFontFromTrack(leftString);
			ofColor currentColor = getRandomColorFromTrack(leftString);
			fab::Word newWord = fab::Word(leftPos + getRandomMovementFromTrack(leftString), newString);
			leftPos.x += currentFont.stringWidth(newString);
			//leftPos.y += currentFont.stringHeight(newString);
			newWord.SetColor(currentColor);
			newWord.SetFont(currentFont);
			newLeftline.addNewWord(newWord);
			ttl += ofRandom(0.75f);
		}
		leftLines.push_back(newLeftline);
		leftPos += stepper;
		leftPos.set(0, leftPos.y);
		
		cout << "---------------------------" << endl;
		
		// add line to right side
		fab::Line newRightLine = fab::Line();
		newRightLine.SetPos(rightPos);
		newRightLine.SetDirection(fab::Line::RIGHTTOLEFT);
		ttl = 0;
		while(ttl <= timeToLife) {
			std::string newString = getRandomStringFromTrack(rightString);
			cout << "adding string " << newString << "to right side" << endl; 
			ofTrueTypeFont currentFont = getRandomFontFromTrack(rightString);
			ofColor currentColor = getRandomColorFromTrack(rightString);
			fab::Word newWord = fab::Word(rightPos + getRandomMovementFromTrack(rightString) - currentFont.stringWidth(newString), newString); // add calculation for new word-length
			newWord.SetColor(currentColor);
			newWord.SetFont(currentFont);
			newRightLine.addNewWord(newWord);
			ttl += ofRandom(0.75f);
		}
		rightLines.push_back(newRightLine);
		rightPos += stepper;
		rightPos.set(ofGetWindowWidth(), rightPos.y);
		
		cout << "---------------------------" << endl;
	}
}
std::string testApp::getRandomStringFromTrack(std::string name) {
	if(name.compare("machinesOf")) {
		int randomIndex = (int)floor(ofRandom(machinesOf.size()));
		return machinesOf.at(randomIndex);
	}
	else if(name.compare("uberMorrow")) {
		int randomIndex = (int)floor(ofRandom(uberMorrow.size()));
		return uberMorrow.at(randomIndex);
	}
	else if(name.compare("geometrie")) {
		int randomIndex = (int)floor(ofRandom(geometrie.size()));
		return geometrie.at(randomIndex);
	}
	else if(name.compare("retina")) {
		int randomIndex = (int)floor(ofRandom(retina.size()));
		return retina.at(randomIndex);
	}
	return "ERRORRRR";
}
ofVec2f testApp::getRandomMovementFromTrack(std::string name) {
	if(name.compare("machinesOf")) {
		int randomIndex = (int)floor(ofRandom(movMachinesOf.size()));
		return movMachinesOf.at(randomIndex);
	}
	else if(name.compare("uberMorrow")) {
		int randomIndex = (int)floor(ofRandom(movUberMorrow.size()));
		return movUberMorrow.at(randomIndex);
	}
	else if(name.compare("geometrie")) {
		int randomIndex = (int)floor(ofRandom(movGeometrie.size()));
		return movGeometrie.at(randomIndex);
	}
	else if(name.compare("retina")) {
		int randomIndex = (int)floor(ofRandom(movRetina.size()));
		return movRetina.at(randomIndex);
	}
	return ofVec2f(0, 0);
}
ofTrueTypeFont testApp::getRandomFontFromTrack(std::string name) {
	return mainFont;
}

ofColor testApp::getRandomColorFromTrack(std::string name) {
	return mainColor;
}
