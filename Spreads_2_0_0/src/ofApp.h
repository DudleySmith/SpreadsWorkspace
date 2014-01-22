#pragma once

#define NikkingsFolder  "Nikkings/"

// Ext addons
//#include "ofxSimpleGuiToo.h"
#include "ofxGui.h"
#include "ofxFensterManager.h"
// My addons
#include "ofdSpreadDisplay.h"

#include "ofxColorSet.h"
#include "ofxLiveGrabber.h"

//#include "msaFluidParticlesApp.h"
//#include "ofdFx.h" // Removed fx because of syphon + Resolume
//#include "ofdTools.h"

typedef struct {
    string  name;
    bool    action;
}nikking;

class ofApp: public ofBaseApp{
    
public:
    
    void setup();
    void draw();
    
    void createDisplay();
    void setupGUI();
    void setupOSC();
    
    void update();
    
    void keyPressed(int key);
    void keyReleased(int key);
    void windowResized(int _width, int _height);
    
    //void MSAload();
    
protected:
private:
    // VARIABLES for Interface -------------------------------
    ofdTrace m_trace;
    ofxParticle partToSetup;
    
public:
    ofdSpreadGuiToApp mOut_vars;
    string m_strTrace;
    
private:
    vector<nikking>  m_nikkings;
    
    nikking     m_currentNikking;
    void    loadPresetsFromFolder(string _folder);
    
    
public:
    bool m_loadActionPresetMSA;
    
private:
    int m_colorSetNum;
    bool m_loadColorsFromSet;
    
private:
    // OSC ----------------------------------------------
    ofxOscLiveGrabberParameterSync m_oLiveGrabberColors;
    ofxOscLiveGrabberParameterSync m_oLiveGrabberParts;
    ofxOscLiveGrabberParameterSync m_oLiveGrabberTubesPatterns;
    ofxOscLiveGrabberParameterSync m_oLiveGrabberMSA;
    
    void updateOSC();
    
private:
    // New display system
    ofdSpreadDisplay m_spreadDisplay;
    //ofxFenster* mp_pointerSpreadDisplay;
    
    // -------------------------------------------------
    // GUI -------------------------------------------------
    // -------------------------------------------------
    
    ofxPanel m_uiColors;
    ofxPanel m_uiParts;
    ofxPanel m_uiTubesPatterns;
    ofxPanel m_uiMSA;
    ofxPanel m_uiEasyOsc;
    
    
    // OSC
    ofParameterGroup     m_gpEasyOsc;
    
    
};
