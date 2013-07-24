#include "testApp.h"

//--------------------------------------------------------------
void testApp::setup(){
	
	ofBackground(255, 255, 255);
	ofSetVerticalSync(true);
	
	reloadAllConfig();
}

//--------------------------------------------------------------
void testApp::update() {
	
}

//--------------------------------------------------------------
void testApp::draw(){
	ofSetColor(mainColor);
	if(pdfTest == false) {
		int leftSize = leftLines.size();
		for(int i = 0; i < leftSize; ++i) {
			leftLines.at(i).draw();
		}
		
		int rightSize = rightLines.size();
		for(int i = 0; i < rightSize; ++ i) {
			rightLines.at(i).draw();
		}
	}
	else if(pdfTest == true) {
		ofBeginSaveScreenAsPDF("screenshot-"+ofGetTimestampString()+".pdf", true);
		
		ofSetColor(0, 0, 0);
		
		int leftSize = leftLines.size();
		for(int i = 0; i < leftSize; ++i) {
			/*std::vector<fab::Word> words = leftLines.at(i).GetWords();
			int wordsSize = words.size();
			for(int j = 0; j < wordsSize; ++j) {
				fab::Word currentWord = words.at(j);
				ofVec2f pos = currentWord.GetPos();0
				mainFont.drawStringAsShapes(currentWord.GetString(), pos.x, pos.y);
			}*/
			leftLines.at(i).drawPDF();
		}
		
		int rightSize = rightLines.size();
		for(int i = 0; i < rightSize; ++ i) {
			rightLines.at(i).drawPDF();
		}
		
		ofEndSaveScreenAsPDF();
		pdfTest = false;
	}
}

//--------------------------------------------------------------
void testApp::keyPressed(int key){
	
	cout << key << endl;
	
	if(key == 'p') {
		pdfTest = true;
	}
	if(key == 'r') {
		reloadAllConfig();
	}
	if(key == '1') {
		newPair(0);
	}
	if(key == '2') {
		newPair(1);
	}
	if(key == '3') {
		newPair(2);
	}
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
	
	jsonFile.open(ofToDataPath("config.json"));
	
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
	}
	
	cout << "reloading config" << endl;
	
	printHeight = config["print"]["height"].asInt();
	printWidth = config["print"]["width"].asInt();
	dpi = config["print"]["dpi"].asInt();
	
	amountOfLines = config["parameters"]["amountOfLines"].asInt();
	timeToLife = config["parameters"]["timeToLife"].asFloat();
	timeToLifeStepper = config["parameters"]["timeToLifeStepper"].asFloat();
	fontName = config["parameters"]["fontName"].asString();
	chanceForNotTakingMainColor = config["parameters"]["chanceForNotTakingMainColor"].asFloat();
	chanceForNotTakingMainFont = config["parameters"]["chanceForNotTakingMainFont"].asFloat();
	
	
	virtualHeight = (printHeight * inchToCmScale) * dpi;
	virtualWidth = (printWidth * inchToCmScale) * dpi;
	
	cout << "clearing all the stuff" << endl;
	
	machinesOf.clear();
	uberMorrow.clear();
	geometrie.clear();
	retina.clear();
	colors.clear();
	fonts.clear();
	movGeometrie.clear();
	movMachinesOf.clear();
	movRetina.clear();
	movUberMorrow.clear();
	
	
	mainColor = ofColor(config["mainColor"]["r"].asInt(), config["mainColor"]["g"].asInt(), config["mainColor"]["b"].asInt());
	Json::Value jsonColors = config["colors"];
	int length = jsonColors.size();
	for(int i = 0; i < length; ++i) {
		//cout << "r " << jsonColors[i]["r"].asInt() /*<< " / g " << jsonColors[i]["g"].asInt() << " / b " << jsonColors[i]["b"].asInt()*/ << endl;
		colors.push_back(ofColor(jsonColors[i]["r"].asInt(), jsonColors[i]["g"].asInt(), jsonColors[i]["b"].asInt()));
	}
 
	mainFont.loadFont(ofToDataPath(fontName), config["mainFont"]["size"].asInt(), true, true, true, 0.3);
	cout << "full charset " << mainFont.hasFullCharacterSet() << endl;
	Json::Value jsonFonts = config["fonts"];
	length = jsonFonts.size();
	for(int i = 0; i < length; ++i) {
		//cout << jsonFonts[i]["size"].asInt() << endl;
		ofTrueTypeFont newFont;
		newFont.loadFont(ofToDataPath(fontName), jsonFonts[i]["size"].asInt(), true, true, true, 0.3);
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
	cout << "loading pair at 0" << endl;
	newPair(0);
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
	ofVec2f stepper = ofVec2f(0, ofGetWindowHeight() / (amountOfLines - (amountOfLines * 0.1)));
	
	for(int i = 0; i < amountOfLines; ++i) {
		// add line to left-side
		fab::Line newLeftline = fab::Line();
		newLeftline.SetPos(leftPos);
		newLeftline.SetDirection(fab::Line::LEFTTORIGHT);
		float ttl = 0;
		while(ttl <= timeToLife) {
			std::string newString = getRandomStringFromTrack(leftString);
			cout << "adding string / " << newString << " / to left side" << endl;
			ofTrueTypeFont currentFont = getRandomFontFromTrack(leftString);
			ofColor currentColor = getRandomColorFromTrack(leftString);
			fab::Word newWord = fab::Word(leftPos + getRandomMovementFromTrack(leftString), newString);
			leftPos.x += currentFont.stringWidth(newString);
			newWord.SetColor(currentColor);
			newWord.SetFont(currentFont);
			newLeftline.addNewWord(newWord);
			ttl += ofRandom(timeToLifeStepper);
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
			cout << "adding string /" << newString << " / to right side" << endl; 
			ofTrueTypeFont currentFont = getRandomFontFromTrack(rightString);
			ofColor currentColor = getRandomColorFromTrack(rightString);
			rightPos += getRandomMovementFromTrack(rightString);
			rightPos.x -= currentFont.stringWidth(newString);
			fab::Word newWord = fab::Word(rightPos, newString); // 
			newWord.SetColor(currentColor);
			newWord.SetFont(currentFont);
			newRightLine.addNewWord(newWord);
			ttl += ofRandom(timeToLifeStepper);
		}
		rightLines.push_back(newRightLine);
		rightPos += stepper;
		rightPos.set(ofGetWindowWidth(), rightPos.y);
		
		cout << "---------------------------" << endl;
		jsonFile.close();
	}
}
std::string testApp::getRandomStringFromTrack(std::string name) {
	
	if(name.compare("machinesOf") == 0) {
		int randomIndex = (int)floor(ofRandom(machinesOf.size()));
		return machinesOf.at(randomIndex);
	}
	else if(name.compare("uberMorrow") == 0) {
		int randomIndex = (int)floor(ofRandom(uberMorrow.size()));
		return uberMorrow.at(randomIndex);
	}
	else if(name.compare("geometrie") == 0) {
		int randomIndex = (int)floor(ofRandom(geometrie.size()));
		return geometrie.at(randomIndex);
	}
	else if(name.compare("retina") == 0) {
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
	if(ofRandom(1) > chanceForNotTakingMainFont) {
		int size = fonts.size();
		return fonts.at((int)floor(ofRandom(size)));
	}
	return mainFont;
}

ofColor testApp::getRandomColorFromTrack(std::string name) {
	if(ofRandom(1) > chanceForNotTakingMainColor) {
		int size = colors.size();
		return colors.at((int)floor(ofRandom(size)));
	}
	return mainColor;
}
