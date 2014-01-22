#include "ofApp.h"

// DECLARATION DES ELEMENTS D'INTERFACE ----------------------
void ofApp::setup()
{
    m_trace.init(true, "GUI");
    ofSetLogLevel(OF_LOG_VERBOSE);
    
    ofSetWindowTitle("Spreads : Interface");
    createDisplay();
    ofSetBackgroundAuto(true);
    
    // COLORS -------------------------
    // Load colors
    mOut_vars.mI_ColorSet.setup("colorSets.xml");
    
    // GUI Interface -----------------------------------------
    m_trace.go("Setup GUI");
    setupGUI();
    
    // OSC ------------------------------------------------
    m_trace.go("Setup OSC");
    
    setupOSC();
    
}


void ofApp::createDisplay(){
    /*
    mp_pointerSpreadDisplay = ofxFensterManager::get()->createFenster(1600, 0, 1600, 900, OF_WINDOW);
    mp_pointerSpreadDisplay->addListener(&m_spreadDisplay);
    mp_pointerSpreadDisplay->setBackgroundColor(0,0,0);
    */
    
    //setup of fensterListener does not get called automatically yet
    ofxFensterManager::get()->setupWindow(&m_spreadDisplay);
	//mp_pointerSpreadDisplay->setup();
    
}

void ofApp::setupGUI(){
    
    // PARTICLES SECTION ----------------------------------------------------------
    m_spreadDisplay.m_oPartWorld.m_pgSets.setName("MyParts");
    m_uiParts.setup(m_spreadDisplay.m_oPartWorld.m_pgSets, "MyParts.xml");
    
    // COULEURS ---------------------------------------------------------------------
    m_uiColors.setName("Colors");
    m_uiColors.setup(mOut_vars.mI_ColorSet.m_oUI.m_gGroup, "Colors.xml");
    m_uiColors.setPosition(10, 30);

    
    // UIs - Setting names and places
    m_uiTubesPatterns.setName("TubesPatterns");
    m_uiTubesPatterns.setup(m_spreadDisplay.m_gpTubesPatterns, "TubesPatterns.xml");
    

    m_uiMSA.setName("MSA");
    m_uiMSA.setup(m_spreadDisplay.m_gpMSA, "MSA.xml");
    
    m_spreadDisplay.m_oOscEvents.loadParameters();
    m_uiEasyOsc.setup(m_spreadDisplay.m_oOscEvents.getSettings(), "OscEventsSettings.xml");
    
    m_uiColors.loadFromFile("Colors.xml");
    m_uiParts.loadFromFile("Parts.xml");
    m_uiTubesPatterns.loadFromFile("TubesPatterns.xml");
    m_uiMSA.loadFromFile("MSA.xml");
    m_uiEasyOsc.loadFromFile("OscEventsSettings.xml");
    
    int idxUI = 0;
    m_uiColors.setPosition(10 + (idxUI++)*250, 30);
    m_uiParts.setPosition(10 + (idxUI++)*250, 30);
    m_uiTubesPatterns.setPosition(10 + (idxUI++)*250, 30);
    m_uiMSA.setPosition(10 + (idxUI++)*250, 30);
    m_uiEasyOsc.setPosition(10 + (idxUI++)*250, 30);
    
}

void ofApp::setupOSC(){
    
    m_spreadDisplay.m_oOscEvents.setup(EASYOSC_IN, "OscEventsSettings.xml");
    
    m_oLiveGrabberColors.setup((ofParameterGroup&)m_uiColors.getParameter(),9001,"localhost",9000);
    m_oLiveGrabberParts.setup((ofParameterGroup&)m_uiParts.getParameter(),9002,"localhost",9000);
    m_oLiveGrabberTubesPatterns.setup((ofParameterGroup&)m_uiTubesPatterns.getParameter(),9003,"localhost",9000);
    m_oLiveGrabberMSA.setup((ofParameterGroup&)m_uiMSA.getParameter(),9004,"localhost",9000);

    
}

void ofApp::updateOSC(){
    
    //    m_oOsc.update();
    m_oLiveGrabberColors.update();
    m_oLiveGrabberTubesPatterns.update();
    m_oLiveGrabberMSA.update();
    m_oLiveGrabberParts.update();
    
    m_spreadDisplay.m_oOscEvents.update();
    //mOut_vars.m_messages = m_oOsc;
    
}

void ofApp::draw(){
    // Dessins des contrôles
    m_uiColors.draw();
    m_uiMSA.draw();
    m_uiTubesPatterns.draw();
    m_uiParts.draw();
    m_uiEasyOsc.draw();
    
    // Affichage des messages de fonctionnement
    ofPushStyle();
    ofSetColor(255);
    m_strTrace += " : " +m_currentNikking.name;
    ofDrawBitmapString(m_strTrace, 20, 20);
    
    ofPopStyle();
    
    /*
     //ofDrawBitmapString("Controls", 0.5*ofGetWidth(), 0.5*ofGetHeight());
     ofSetColor(mOut_vars.mI_ColorSet.ofxColorSet::getCurrentSetByIndex(0));
     ofRect(0.5*ofGetWidth(), 0.5*ofGetHeight(), 150, 150);
     
     ofSetColor(mOut_vars.mI_ColorSet.ofxColorSet::getCurrentSetByIndex(1));
     ofRect(0.5*ofGetWidth(), 0.5*ofGetHeight(), 120, 120);
     
     ofSetColor(mOut_vars.mI_ColorSet.ofxColorSet::getCurrentSetByIndex(2));
     ofRect(0.5*ofGetWidth(), 0.5*ofGetHeight(), 90, 90);
     
     ofSetColor(mOut_vars.mI_ColorSet.ofxColorSet::getCurrentSetByIndex(3));
     ofRect(0.5*ofGetWidth(), 0.5*ofGetHeight(), 50, 50);
     
     ofSetColor(mOut_vars._myColor_4);
     ofRect(0.5*ofGetWidth(), 0.5*ofGetHeight(), 20, 20);
     */
}

void ofApp::update(){
    
    // Reload Colors
    mOut_vars._myColor_1.setBrightness(mOut_vars._myColor_1_Brg);
    mOut_vars._myColor_1.setSaturation(mOut_vars._myColor_1_Sat);
    mOut_vars._myColor_1.setHue(mOut_vars._myColor_1_Hue);
    
    mOut_vars._myColor_2.setBrightness(mOut_vars._myColor_2_Brg);
    mOut_vars._myColor_2.setSaturation(mOut_vars._myColor_2_Sat);
    mOut_vars._myColor_2.setHue(mOut_vars._myColor_2_Hue);
    
    mOut_vars._myColor_3.setBrightness(mOut_vars._myColor_3_Brg);
    mOut_vars._myColor_3.setSaturation(mOut_vars._myColor_3_Sat);
    mOut_vars._myColor_3.setHue(mOut_vars._myColor_3_Hue);
    
    mOut_vars._myColor_4.setBrightness(mOut_vars._myColor_4_Brg);
    mOut_vars._myColor_4.setSaturation(mOut_vars._myColor_4_Sat);
    mOut_vars._myColor_4.setHue(mOut_vars._myColor_4_Hue);
    
    mOut_vars.mI_ColorSet.setCurrentSetColor(0, mOut_vars._myColor_1);
    mOut_vars.mI_ColorSet.setCurrentSetColor(1, mOut_vars._myColor_2);
    mOut_vars.mI_ColorSet.setCurrentSetColor(2, mOut_vars._myColor_3);
    mOut_vars.mI_ColorSet.setCurrentSetColor(3, mOut_vars._myColor_4);
    
    m_spreadDisplay.mIn_vars = mOut_vars;
    m_strTrace = m_spreadDisplay.m_strTrace; 
    // update de l'intérieur de l'interface
    //m_spreadDisplay.update();
    
    //    vector<nikking>::iterator    onePreset;
    //
    //    for(onePreset=m_nikkings.begin(); onePreset!=m_nikkings.end(); onePreset++){
    ////    for(int i=0; i<PRESET_MAX_COUNT; i++){
    ////        if (m_loadActionPreset[i] == true){
    //        if ((*onePreset).action == true){
    //            // Un des presets souhaite être chargé
    //            m_currentNikking=(*onePreset);
    //            // On charge les 2 pages
    //            // Page 2 - General
    //            gui.page(PAGE_2_Name).setXMLName(NikkingsFolder+m_currentNikking.name+PAGE_2_Name+".xml");
    //            gui.page(PAGE_2_Name).loadFromXML();
    //            // Page 3 - MSA
    //            gui.page(PAGE_3_Name).setXMLName(NikkingsFolder+m_currentNikking.name+PAGE_3_Name+".xml");
    //            gui.page(PAGE_3_Name).loadFromXML();
    //        }
    //    }
    //    // Reload MSA--
    //    if(m_loadActionPresetMSA)   MSAload();
    //
    
    // OSC, now !!!!!!!!!!!!!!!!!!!!!
    updateOSC();
    
}

void ofApp::keyPressed(int key){
    mOut_vars.event_type = event_keyPressed;
    mOut_vars.key_pressed = key;
}

void ofApp::keyReleased(int key){
    mOut_vars.event_type = event_keyReleased;
    mOut_vars.key_released = key;
}

void ofApp::windowResized(int w, int h){
    //
    mOut_vars.event_type = event_winResized;
}

/*
void ofApp::MSAload(){
    // Changement de page MSA
    gui.page(PAGE_3_Name).setXMLName(NikkingsFolder+m_currentNikking.name+PAGE_3_Name+".xml");
    gui.page(PAGE_3_Name).loadFromXML();
}
*/

void    ofApp::loadPresetsFromFolder(string _folder){
    
    ofDirectory dir;
    nikking     nikking_toAdd;
    vector<string>      shortName;
    
    dir.listDir(_folder);
    
    if(dir.exists() && dir.size()){
        
        // you can now iterate through the files and load them into the ofImage vector
        for(int i = 0; i < (int)dir.size(); i++){
            // On charge le fichier pour le vérifier ------------------
            ofFile file;
            string path = dir.getPath(i);
            
            file = path;
            //if(file.exists() && file.getExtension()=="xml" && ofIsStringInString(file.getBaseName(), PAGE_2_Name)==true){
            //    shortName = ofSplitString(file.getBaseName(), PAGE_2_Name);
            if(file.exists() && file.getExtension()=="xml" && ofIsStringInString(file.getBaseName(), "Nikkings")==true){
                shortName = ofSplitString(file.getBaseName(), "Nikkings");
                // Allocate a struct
                nikking_toAdd.name = shortName[0];
                nikking_toAdd.action = false;
                // Add it
                m_nikkings.push_back(nikking_toAdd);
                // Say that you found something
                cout << "Nikkings Found and added : " << shortName[0] << endl;
            }
            
        }
        
    }else{
        cout << "Screw me ! the directory is empty or doe not exist" << endl;
    }
    
    m_currentNikking = m_nikkings[0];
    
    
}
