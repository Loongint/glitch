#include "ofApp.h"

void ofApp::setup(){
  bgsound.loadSound("1.mp3");
  bgsound.setLoop(true);
  bgsound.play();

  colorFucked.addListener(this,&ofApp::colorFuckedChange);
  tint.addListener(this,&ofApp::tintChange);
  melting.addListener(this, &ofApp::meltingChange);
  pattern.addListener(this, &ofApp::patternChange);

  gui.setup();

  gui.add(title.setup(ofToString("         Glitch"), 200, 30));
  gui.add(blockGlitch.setup("block", true));
  gui.add(linesGlitch.setup("lines", true));
  gui.add(disloc.setup("dislocation", true));
  gui.add(channelShuffle.setup("channelShuffle", true));

  gui.add(pixellate.setup("pixellate", false));

  gui.add(colorFucked.setup("colorFucked", true));
  gui.add(tint.setup("tint", true));
  gui.add(gray.setup("gray", true));

  gui.add(melting.setup("melting", true));
  gui.add(pattern.setup("pattern", true));
  gui.add(frame.setup("frameRate: ", ofToString(ofGetFrameRate())));

  randomize = 1;
  ranrandomize = 0;
  ranranrandomize = 0;

  camWidth = 640;
  camHeight = 360;

  myCam.setDeviceID(1);
  //myCam.setDesiredFrameRate(60);
  myCam.initGrabber(camWidth,camHeight);
}

void ofApp::colorFuckedChange(bool &colorFucked) {
    if(colorFucked) {
        if(tint) {
          tint = false;
        }
    }
}

void ofApp::tintChange(bool &tint) {
    if(tint) {
        if(colorFucked){
          colorFucked = false;
        }
    }
}

void ofApp::meltingChange(bool &melting) {
    if(melting) {
        if(pattern) {
                pattern = false;
        }
    }
}

void ofApp::patternChange(bool &pattern) {
    if(pattern) {
        if(melting) {
            melting=false;
        };
    }
}


void ofApp::update(){
  myCam.update();

  img.setFromPixels(myCam.getPixelsRef());
  img.update();
}

void ofApp::draw(){
    ofSeedRandom(randomize);

    ranrandomize ++;
    if(ranrandomize == (int)ofRandom(3, 7)) {
        randomize ++;
        ranrandomize = 0;
    }

    ranranrandomize ++;
    if(ranranrandomize == 100) {
        blockGlitch = randomBool(.3);
        linesGlitch = randomBool(.3);
        channelShuffle = randomBool(.3);
        disloc = randomBool(.3);
		pixellate = randomBool(.7);
		colorFucked = randomBool(.5);
		tint = randomBool(.5);
		gray = randomBool(.3);
		melting = randomBool(.5);
		pattern = randomBool(.5);

        ranranrandomize = 0;

        cout<<ranranrandomize<<endl;
    }

    cout<<ranranrandomize<<endl;

    glitch_1();

    glitch_3();

    img.draw(0,0,ofGetWidth(),ofGetHeight());

    glitch_2();

    ofSetColor(255);

    glitch_4();

    gui.draw();
}

bool ofApp::randomBool(float piu) {
  float biu = ofRandom(0,1);
  if(biu > piu) {
    return true;
  } else {
    return false;
  }
}

void ofApp::glitch_1() {
  if(tint){addTint();}
  if(colorFucked){glitch_colors(int(ofRandom(-40,40)), int(ofRandom(-5,5)));}
  if(gray){glitch_gray();}
}

void ofApp::glitch_2() {
  if(blockGlitch){glitch_block();}
  if(linesGlitch){glitch_lines();}
  if(disloc){glitch_disloc();}
  if(channelShuffle){glitch_channelShuffle();}
}

void ofApp::glitch_3() {
  if(melting){glitch_melt();}
  if(pattern){glitch_pattern();}
}

void ofApp::glitch_4() {
  if(pixellate){glitch_pixel(int(ofRandom(2, 20)));}
}

int ofApp::min(int a, int b) {
  if(a < b) {
    return a;
  } else {
    return b;
  }
}

int ofApp::max(int a, int b) {
  if(a > b) {
    return a;
  } else {
    return b;
  }
}

void ofApp::swapAB(int a, int b) {
  int tmp;
  tmp = a;
  a = b;
  b = tmp;
}
void ofApp::glitch_block() {
  int num = int(ofRandom(5, 20));

  for(int i = 0; i < num; i++) {
    int startX = int(ofRandom(0, ofGetWidth()));
    int startY = int(ofRandom(0, ofGetHeight()));
    int randWidth = int(ofRandom(3, 10));
    int randHeight = int(ofRandom(3, 10));
    int placeX = int(ofRandom(0, ofGetWidth()));
    int placeY = int(ofRandom(0, ofGetWidth()));
    int placeWidth = int(ofRandom(30, 70));
    int placeHeight = int(ofRandom(30, 70));

    img.drawSubsection(placeX, placeY, placeWidth, placeHeight,startX, startY, randWidth, randHeight);
  }

  img.update();
}

void ofApp::glitch_lines() {
  int num = int(ofRandom(5, 30));
  for(int i = 0; i < num; i++) {
    int startX = int(ofRandom(0, ofGetWidth()));
    int startY = int(ofRandom(0, ofGetHeight()));
    int randWidth = int(ofRandom(3, 10));
    int randHeight = int(ofRandom(3, 10));
    int placeX = 0;
    int placeY = int(ofRandom(0, ofGetWidth()));
    int placeWidth = ofGetWidth();
    int placeHeight = 2;

    img.drawSubsection(placeX, placeY, placeWidth, placeHeight,startX, startY, randWidth, randHeight);
  }

  img.update();
}

void ofApp::glitch_disloc() {
  int num = (int)ofRandom(1,3);
  for (int i = 0; i <= num; i++) {
    int h = (int)ofRandom(0,camHeight - 100);
    int hh = (int)ofRandom(30, 100);
    int a = (int)ofRandom(camWidth/1.1 ,camWidth);

    float hbiu = h * ofGetHeight() / camHeight;
    float hhbiu = hh * ofGetHeight() / camHeight;
    float abiu = a * ofGetWidth() / camWidth;
    img.drawSubsection(0,hbiu,ofGetWidth() - abiu,hhbiu,a,h,camWidth - a,hh);
    img.drawSubsection(ofGetWidth()-abiu,hbiu,abiu,hhbiu,0,h,a,hh);
  }
  num = (int)ofRandom(1,3);
  for (int i = 0; i <= num; i++) {
    int h = (int)ofRandom(0,camHeight - 100);
    int hh = (int)ofRandom(30, 100);
    int a = (int)ofRandom(10 , 64);

    float hbiu = h * ofGetHeight() / camHeight;
    float hhbiu = hh * ofGetHeight() / camHeight;
    float abiu = a * ofGetWidth() / camWidth;
    img.drawSubsection(0,hbiu,ofGetWidth() - abiu,hhbiu,a,h,camWidth - a,hh);
    img.drawSubsection(ofGetWidth()-abiu,hbiu,abiu,hhbiu,0,h,a,hh);
  }
  img.update();
}

void ofApp::glitch_channelShuffle() {
  int num = int(ofRandom(1, 20));
  for(int x = 0; x < num; x++) {
    int channel = int(ofRandom(0, 2.5));
    int startX = int(ofRandom(0, ofGetWidth()));
    int startY = int(ofRandom(0, ofGetHeight()));
    int randWidth = int(ofRandom(70, 300));
    int randHeight = int(ofRandom(40, 100));
    int randX = int(ofRandom(-100, 100));
    int randY = int(ofRandom(-100, 100));

    if(channel == 0) {
      ofSetColor(255,0,0,70);
    } else if(channel == 1) {
      ofSetColor(0,255,0,70);
    } else {
      ofSetColor(0,0,255,70);
    }
    img.drawSubsection(startX+randX, startY+randY, randWidth, randHeight,startX, startY, randWidth, randHeight);
  }

  img.update();
}

void ofApp::glitch_pixel(int size) {
  for (int x = 0; x < camWidth - size; x += size) {
    for (int y = 0; y < camHeight - size; y += size) {
      ofSetColor(img.getColor(x + size, y + size));
      ofRect(x * ofGetWidth() / camWidth, y * ofGetWidth() / camWidth, size * ofGetWidth() / camWidth + 3, size * ofGetWidth() / camWidth+ 3);
    }
  }
}

void ofApp::glitch_colors(int hueShift, int satShift) {
  int biu = (int)ofRandom(0, camHeight);
  int biubiu = (int)ofRandom(biu, camHeight);

  while((biubiu - biu) < 100) {
    biu = (int)ofRandom(0, camHeight);
    biubiu = (int)ofRandom(biu, camHeight);
  }
  for(int x = 0; x < camWidth; x++) {
    for(int y = biu; y < biubiu; y++) {
      ofColor pixel;
      pixel.set(img.getColor(x,y));
      pixel.set(pixel.getHue() + hueShift, pixel.getSaturation() + satShift, pixel.getBrightness());
      img.setColor(x, y, pixel);
    }
  }
  img.update();
}

void ofApp::glitch_gray() {
  int biu = (int)ofRandom(0, camHeight);
  int biubiu = (int)ofRandom(biu, camHeight);

  while((biubiu - biu) < 100) {
    biu = (int)ofRandom(0, camHeight);
    biubiu = (int)ofRandom(biu, camHeight);
  }
  for(int x = 0; x < camWidth; x++) {
    for(int y = biu; y < biubiu; y++) {
      ofColor pixel;
      pixel.set(img.getColor(x,y));
      pixel.set((pixel.r*30 + pixel.g*59 + pixel.b*11 + 50) / 100);
      img.setColor(x, y, pixel);
    }
  }
  img.update();
}

void ofApp::addTint() {
    int rr = int(ofRandom(100));
    int gg = int(ofRandom(100));
    int bb = int(ofRandom(100));

    for(int i = 0; i < camWidth; i++){
      for(int j = 0; j < camHeight; j++){
        ofColor c;
        c.set(img.getColor(i,j));
        c.r += rr;
        if(c.r>255){c.r=255;}
        c.b += bb;
        if(c.b>255){c.b=255;}
        c.g += gg;
        if(c.g>255){c.g=255;}
        img.setColor(i,j,c);
      }
    }
    img.update();
}

void ofApp::glitch_melt() {
  int melts = int(ofRandom(30, 80));
  for(int j = 0; j < melts; j++) {
    int startX = int(ofRandom(0, camWidth));
    int startY = int(ofRandom(0, camHeight));
    int meltLength = int(ofRandom(20, 40));
    int meltWidth = int(ofRandom(3, 5));
    ofColor c = img.getColor(startX, startY);

    while((startX + meltWidth)>camWidth) {
        startX--;
    }
    while((startY + meltLength)>camHeight) {
        startY--;
    }
    for(int i = 0; i < meltLength; i++) {
      for(int k = 0; k < meltWidth; k++) {
        img.setColor(startX+k, startY+i, c);
      }
    }
  }
  img.update();
}

void ofApp::glitch_pattern() {
  int num = int(ofRandom(5, 10));
  for(int count = 0; count < num; count++) {
    int randX = int(ofRandom(0, camWidth));
    int randY = int(ofRandom(0, camHeight));
    int randHeight = int(ofRandom(1, camHeight-randY));
    int randWidth = int(ofRandom(1, camWidth-randX));

    int shifts[randHeight];
    shifts[0] = 0;
    int mostLeft = 0;
    int mostRight = 0;
    for(int i = 1; i < randHeight; i++) {
      int shift = int(ofRandom(-1.5, 1.5));
      shifts[i] = shifts[i-1] + shift;
      if(shifts[i] < mostLeft) { mostLeft = shifts[i]; }
      else if (shifts[i] > mostRight) { mostRight = shifts[i]; }
    }

    int start = int(ofRandom(0, camWidth));
    int stop = int(ofRandom(start, camWidth));

    for(int inY = 0; inY < randHeight; inY++) {
      int offset = (randX +shifts[inY] ) % randWidth;
      int counter = offset;
      for(int x = start; x < stop; x++) {
         ofColor c = img.getColor(randX+(counter), randY+inY);
         if(x<0){x=0;}
         if(x>camWidth){x=camWidth;}
         int tmpy = randY+inY;
         if(tmpy<0){tmpy=0;}
         if(tmpy>camHeight){tmpy=camHeight;}
         img.setColor(x, tmpy, c);
         counter++;
         if (counter > randWidth) { counter = 0; }
      }
    }
  }

  img.update();
}

void ofApp::keyPressed(int key){
  if(key == ' ') {
     randomize ++;
  } else {
     ofSaveScreen("2.png");
  }
}
