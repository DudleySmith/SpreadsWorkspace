#pragma once


#define PAGE_2_Name "_General"
#define PAGE_3_Name "_MSA"

#define NikkingsFolder  "Nikkings/"

#define max_viscosity 0.005

// Ext addons
#include "ofxSimpleGuiToo.h"
#include "ofxFensterManager.h"
// My addons
#include "ofdSpreadDisplay.h"

#include "ofdColorSet.h"
#include "ofdOsc.h"

//#include "msaFluidParticlesApp.h"
//#include "ofdFx.h" // Removed fx because of syphon + Resolume
//#include "ofdTools.h"

typedef struct {
    string  name;
    bool    action;
}nikking;

class testApp: public ofBaseApp{
    
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
    
    void MSAload();
    
protected:
private:
    // VARIABLES for Interface -------------------------------
    ofdTrace m_trace;
    ofdPart partToSetup;
    //ofdFX   fxToList;
    
public:
    ofdSpreadGuiToApp mOut_vars;
    string m_strTrace;
    
private:
    //        string  m_presets[PRESET_MAX_COUNT+1];
    //        bool    m_loadActionPreset[PRESET_MAX_COUNT+1];
    //
    vector<nikking>  m_nikkings;
    
    nikking     m_currentNikking;
    void    loadPresetsFromFolder(string _folder);
    void    savePresetsAs();
    
    
public:
    //        int getPresetGlobalNum(){return m_presetGlobalNum;};
    //        string getCurrentPreset_name(){return m_presets[getPresetGlobalNum()].name;};
    //
    //        int getPresetGlobalNum(){return m_presetGlobalNum;};
    //        string getCurrentPreset_name(){return m_presetGlobalNum.name;};
    
    //    private:
    //        int m_presetMSA;
    bool m_loadActionPresetMSA;
    //    public:
    //        int getPresetMSANum(){return m_presetMSA;};
    //
private:
    ofdColorSetAnimated m_ColorSetBase;
    int m_colorSetNum;
    bool m_loadColorsFromSet;
    
private:
    //        ofdMidiForGui m_MPD;
    
    
    // Settings -------------------------------------------
    void loadSettings();
    
    int     mx_minRaysPeriod, mx_maxRaysPeriod, mx_minTubePeriod, mx_maxTubePeriod;
    float   mx_minRaysDelay, mx_maxRaysDelay, mx_minTubeDelay, mx_maxTubeDelay;
    
    
    // OSC ----------------------------------------------
    ofdOsc m_oOsc;
    void updateOSC();
    
    // TOOLS ---------------------------------------------
    //ofdTools m_oTools;

private:
    // New display system
    ofdSpreadDisplay m_spreadDisplay;
    //ofxFenster* mp_pointerSpreadDisplay;
    
};
