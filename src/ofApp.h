#pragma once

#include "ofMain.h"
#include "ofxGui.h"

class ofApp : public ofBaseApp{

	public:
		void setup();
		void update();
		void draw();

        void glitch_1();
        void glitch_2();
        void glitch_3();
        void glitch_4();
        void glitch_block();
        void glitch_lines();
        void glitch_disloc();
        void glitch_channelShuffle();
        void glitch_pixel(int size);
        void glitch_colors(int hueShift, int satShift);
        void glitch_gray();
        void addTint();
        void glitch_melt();
        void glitch_pattern();
        void swapAB(int a, int b);
        int min(int a, int b);
        int max(int a,int b);

        void colorFuckedChange(bool &colorFucked);
        void tintChange(bool &tint);
        void meltingChange(bool &melting);
        void patternChange(bool &pattern);
        bool randomBool(float piu);
		void keyPressed(int key);

		ofImage img,imgbiu;

		ofxPanel gui;
		ofxToggle blockGlitch, linesGlitch, channelShuffle, disloc;
		ofxToggle pixellate;
		ofxToggle colorFucked, tint, gray;
		ofxToggle melting, pattern;
		ofxLabel frame,title;

		int randomize,ranrandomize,ranranrandomize;

		int camWidth,camHeight;

		ofVideoGrabber myCam;

		ofSoundPlayer bgsound;
};
