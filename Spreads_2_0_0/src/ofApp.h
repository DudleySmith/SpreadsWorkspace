#pragma once


#define PAGE_2_Name "_General"
#define PAGE_3_Name "_MSA"

#define NikkingsFolder  "Nikkings/"

#define max_viscosity 0.005

// Ext addons
//#include "ofxSimpleGuiToo.h"
#include "ofxGui.h"
#include "ofxFensterManager.h"
// My addons
#include "ofdSpreadDisplay.h"

#include "ofxColorSet.h"
#include "ofdOsc.h"

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
    void setupMSA();
    
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
    void    savePresetsAs();
    
    
public:
    bool m_loadActionPresetMSA;
    
private:
    int m_colorSetNum;
    bool m_loadColorsFromSet;
    
private:
    // Settings -------------------------------------------
    void loadSettings();
    
    int     mx_minRaysPeriod, mx_maxRaysPeriod, mx_minTubePeriod, mx_maxTubePeriod;
    float   mx_minRaysDelay, mx_maxRaysDelay, mx_minTubeDelay, mx_maxTubeDelay;
    
    // OSC ----------------------------------------------
    ofdOsc m_oOsc;
    void updateOSC();
    
private:
    // New display system
    ofdSpreadDisplay m_spreadDisplay;
    //ofxFenster* mp_pointerSpreadDisplay;
    
    // -------------------------------------------------
    // GUI -------------------------------------------------
    // -------------------------------------------------
    
    ofxPanel            m_uiColors;
    ofParameterGroup    m_gpColors;
    
    ofxPanel             m_uiGen;
    ofParameterGroup     m_gpGen;
    
    ofParameterGroup         m_gpParts;
    ofParameter<bool>        m_btPartsOn;
    
    ofParameterGroup        m_gpTubes;
    ofParameter<bool>       m_btRaysOn;
    ofParameter<bool>       m_btTraitsOn;
    
    ofParameter<float>  m_slRestartIntensity;
    ofParameter<float>  m_slTubeDelay;
    ofParameter<float>  m_slTubePeriod;
    ofParameter<float>  m_slRaysDelay;
    ofParameter<float>  m_slRaysPeriod;
    
    // SPREADS SECTION ----------------------------------------------------------
    ofParameterGroup     m_gpSpreads;
    ofParameter<int>     m_slPatternFamily;
    ofParameter<int>     m_slNumPattern;
    ofParameter<float>   m_slSeqMinRate;
    ofParameter<float>   m_slSeqMaxRate;
    
    ofParameter<int>  m_slModeTypo2;
    
    // Audio réaction ---------------------------------------------------
    ofParameterGroup     m_gpAudio;
    ofParameter<bool>   m_btModeAudio;
    ofParameter<float>  m_slBass_BangLevel;
    ofParameter<float>  m_slMid_BangLevel;
    ofParameter<float>  m_slHigh_BangLevel;
    
    // MSA ------------------
    ofxPanel            m_uiMsa;
    ofParameterGroup     m_gpMsa;
    
    ofParameterGroup     m_gpMSA_Useful;
    ofParameter<int>    m_slDrawMode;
    ofParameter<float>  m_slViscocity;
    ofParameter<float>  m_slColorDiffusion;
    ofParameter<float>  m_slFadeSpeed;
    ofParameter<float>  m_slDeltaT;
    ofParameter<float>  m_slColorMult;
    ofParameter<float>  m_slVelocityMult;
    
    ofParameterGroup        m_gpMSA_Useless;
    ofParameter<int>        m_slfluidCellsX;
    ofParameter<bool>       m_btResizeFluid;
    ofParameter<int>        m_slSolverIterations;
    ofParameter<bool>       m_btDoRGB;
    ofParameter<bool>       m_btDoVorticityConfinement;
    ofParameter<bool>       m_btDrawFluid;
    ofParameter<bool>       m_btDrawParticles;
    ofParameter<bool>       m_btWrapX;
    ofParameter<bool>       m_btWrapY;
    
};
