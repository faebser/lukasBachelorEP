#include "testApp.h"

//--------------------------------------------------------------
void testApp::setup(){
	mainFont.loadFont(ofToDataPath("LTe50186.ttf"), 40, true, true, true);
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
}

//--------------------------------------------------------------
void testApp::update(){
}

//--------------------------------------------------------------
void testApp::draw(){
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
	
	mainColor = ofColor_(config["mainColor"].asString());
	Json::Value jsonColors = config["colors"];
	int length = jsonColors.size();
	for(int i = 0; i < length; ++i) {
		colors.push_back(ofColor(jsonColors[i].asString()));
	}
 
	mainFont.loadFont(ofToDataPath("LTe50186.ttf"), config["mainFont"]["size"].asInt(), true, true, true);
	Json::Value jsonFonts = config["fonts"];
	length = jsonFonts.size();
	for(int i = 0; i < length; ++i) {
		fonts.at(i).loadFont(ofToDataPath("LTe50186.ttf"), jsonFonts[i]["size"].asInt(), true, true, true);
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
	
	cout << "reloading config finished" << endl;
}
