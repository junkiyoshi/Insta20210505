#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup() {

	ofSetFrameRate(60);
	ofSetWindowTitle("openFrameworks");

	ofBackground(0);
	ofEnableBlendMode(ofBlendMode::OF_BLENDMODE_ADD);
	ofEnableDepthTest();

	this->mesh.setMode(ofPrimitiveMode::OF_PRIMITIVE_LINES);
}

//--------------------------------------------------------------
void ofApp::update() {

	ofSeedRandom(39);
	this->mesh.clear();

	ofColor color;
	vector<ofColor> base_color_list;
	vector<int> hex_list = { 0xf44336, 0x9C27B0, 0x3F51B5, 0x03A9F4, 0x009688, 0x8BC34A, 0xFFEB3B, 0xFF9800 };
	for (auto hex : hex_list) {

		color.setHex(hex);
		base_color_list.push_back(color);
	}

	int span = 1;
	for (int i = 0; i < 800; i++) {

		int x = ofMap(ofNoise(ofRandom(1000), ofGetFrameNum() * 0.0005), 0, 1, -300, 300);
		int y = 0;
		y = ofRandom(150, 170);
		y *= ofRandom(1) < 0.5 ? 1 : -1;
		int z = ofRandom(-20, 20);

		auto location = glm::vec3(x, y, z);
		auto rotation_x = glm::rotate(glm::mat4(), (ofGetFrameNum() * span + x * span + 300) * (float)DEG_TO_RAD, glm::vec3(1, 0, 0));
		location = glm::vec3(x, 0, 0) + glm::vec4(location, 0) * rotation_x;

		this->mesh.addVertex(location);

		int color_index = ofRandom(base_color_list.size());
		this->mesh.addColor(base_color_list[color_index]);
	}

	for (int i = 0; i < 1000; i++) {

		int x = (int)ofRandom(12) * 50 - 250 + ofRandom(-5, 5);
		int y = ofMap(ofNoise(ofRandom(1000), ofGetFrameNum() * 0.001), 0, 1, -170, 170);
		int z = ofRandom(-10, 10);

		auto location = glm::vec3(x, y, z);
		auto rotation_x = glm::rotate(glm::mat4(), (ofGetFrameNum() * span + x * span + 300) * (float)DEG_TO_RAD, glm::vec3(1, 0, 0));
		location = glm::vec3(x, 0, 0) + glm::vec4(location, 0) * rotation_x;

		this->mesh.addVertex(location);

		int color_index = ofRandom(base_color_list.size());
		this->mesh.addColor(base_color_list[color_index]);
	}

	for (int i = 0; i < this->mesh.getNumVertices(); i++) {

		for (int k = i + 1; k < this->mesh.getNumVertices(); k++) {

			if (distance(this->mesh.getVertex(i), this->mesh.getVertex(k)) < 15) {

				this->mesh.addIndex(i);
				this->mesh.addIndex(k);
			}
		}
	}
}

//--------------------------------------------------------------
void ofApp::draw() {

	this->cam.begin();

	this->mesh.drawWireframe();

	for (int i = 0; i < this->mesh.getNumVertices(); i++) {

		ofSetColor(this->mesh.getColor(i));
		ofDrawSphere(this->mesh.getVertex(i), 2.5);
	}

	this->cam.end();
}

//--------------------------------------------------------------
int main() {

	ofSetupOpenGL(720, 720, OF_WINDOW);
	ofRunApp(new ofApp());
}