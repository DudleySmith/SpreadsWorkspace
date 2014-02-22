#include "ofApp.h"

// DECLARATION DES ELEMENTS D'INTERFACE ----------------------
void ofApp::setup()
{
    ofSetLogLevel(OF_LOG_VERBOSE);
    
    createDisplay();
    
    // Display Settings --------------------------------
    ofSetWindowTitle("Spreads : Interface");
    ofSetWindowShape(m_oSpreadDisplay.m_slWidthDisplay, m_oSpreadDisplay.m_slHeightDisplay);
    ofSetBackgroundAuto(true);
    ofSetFrameRate(60);
    
    // COLORS -------------------------
    // Load colors
    // TODO : ColorSet
    m_oSpreadDisplay.m_oColorSet.setup("colorSets.xml");
    
    // GUI Interface -----------------------------------------
    ofLogNotice() << ("Setup GUI");
    setupGUI();
    
    // OSC ------------------------------------------------
    ofLogNotice() << ("Setup OSC");
    
    setupOSC();
    
    m_oSpreadDisplay.m_oColorSet.m_oUI.setCurrentSetIdx(1);
    m_oSpreadDisplay.m_oColorSet.m_oUI.setChange(true);
    
}


void ofApp::createDisplay(){
    //setup of fensterListener does not get called automatically yet
    ofxFensterManager::get()->setupWindow(&m_oSpreadDisplay, WindowWidth, WindowHeight);
}

void ofApp::setupGUI(){
    
    // PARTICLES SECTION ----------------------------------------------------------
    m_oSpreadDisplay.m_oPartWorld.m_pgSets.setName("MyParts");
    m_uiParts.setup(m_oSpreadDisplay.m_oPartWorld.m_pgSets, "XML/MyParts.xml");
    
    // COULEURS ---------------------------------------------------------------------
    m_uiColors.setName("Colors");
    m_uiColors.setup(m_oSpreadDisplay.m_oColorSet.m_oUI.m_gGroup, "XML/Colors.xml");
    m_uiColors.setPosition(10, 30);
    
    // UIs - Setting names and places
    m_uiTubesPatterns.setName("TubesPatterns");
    m_uiTubesPatterns.setup(m_oSpreadDisplay.m_gpTubesPatterns, "XML/TubesPatterns.xml");
    
    m_uiArduino.setup(m_oSpreadDisplay.m_oArduinoServer.m_gpArduino, "XML/MyArduino.xml");
    m_uiArduino.loadFromFile("XML/MyArduino.xml");
    
    // MSA - Blurred particles
    m_uiMSA.setName("MSA");
    m_uiMSA.setup(m_oSpreadDisplay.m_gpMSA, "XML/MSA.xml");
    
    // Display
    m_uiDisplay.setName("Diplay");
    m_uiDisplay.setup(m_oSpreadDisplay.m_gpDisplay, "XML/Display.xml");
    
    
    // OSC Parameters
    m_oSpreadDisplay.m_oOscEventsOnOff.loadParameters("OscOnOff");
    m_uiEasyOscOnOff.setup(m_oSpreadDisplay.m_oOscEventsOnOff.getSettings(), "XML/OscEventsOnOffSettings.xml");
    
    // OSC Parameters
    m_oSpreadDisplay.m_oOscEventsFades.loadParameters("Fades");
    m_uiEasyOscFades.setup(m_oSpreadDisplay.m_oOscEventsFades.getSettings(), "XML/OscEventsFadesSettings.xml");
    
    // Others UI features
    m_uiOthers.setup();
    m_uiOthers.setName("Others");
    m_uiOthers.add(m_slSetLogLevel.setup("Set Log Level", 3, 0, 3));
    m_uiOthers.add(m_lbGetLogLevel.setup("Log", "Log Level"));
    
    //m_uiColors.loadFromFile("Colors.xml");
    m_uiParts.loadFromFile("XML/MyParts.xml");
    m_uiTubesPatterns.loadFromFile("XML/TubesPatterns.xml");
    m_uiMSA.loadFromFile("XML/MSA.xml");
    m_uiEasyOscOnOff.loadFromFile("XML/OscEventsOnOffSettings.xml");
    m_uiEasyOscFades.loadFromFile("XML/OscEventsFadesSettings.xml");
    m_uiOthers.loadFromFile("XML/Others.xml");
    m_uiDisplay.loadFromFile("XML/Display.xml");
    
    int idxUI = 0;
    m_uiColors.setPosition(10 + (idxUI++)*250, 30);
    m_uiParts.setPosition(10 + (idxUI++)*250, 30);
    m_uiTubesPatterns.setPosition(10 + (idxUI++)*250, 30);
    m_uiMSA.setPosition(10 + (idxUI++)*250, 30);
    
    m_uiEasyOscOnOff.setPosition(10 + (idxUI++)*250, 30);
    m_uiEasyOscFades.setPosition(10 + (idxUI-1)*250, 180);
    m_uiDisplay.setPosition(10 + (idxUI-1)*250, 360);
    m_uiOthers.setPosition(10 + (idxUI-1)*250, 560);
    
    
}

void ofApp::setupOSC(){
    
    m_oSpreadDisplay.m_oOscEventsOnOff.setup(EASYOSC_IN);
    m_oSpreadDisplay.m_oOscEventsFades.setup(EASYOSC_IN);
    
    m_oLiveGrabberColors.setup((ofParameterGroup&)m_uiColors.getParameter(),9001,"localhost",9000);
    m_oLiveGrabberParts.setup((ofParameterGroup&)m_uiParts.getParameter(),9002,"localhost",9000);
    m_oLiveGrabberTubesPatterns.setup((ofParameterGroup&)m_uiTubesPatterns.getParameter(),9003,"localhost",9000);
    m_oLiveGrabberMSA.setup((ofParameterGroup&)m_uiMSA.getParameter(),9004,"localhost",9000);

}

void ofApp::updateOSC(){
    
    m_oLiveGrabberColors.update();
    m_oLiveGrabberTubesPatterns.update();
    m_oLiveGrabberMSA.update();
    m_oLiveGrabberParts.update();
    
    m_oSpreadDisplay.m_oOscEventsOnOff.update();
    m_oSpreadDisplay.m_oOscEventsFades.update();
    
}

void ofApp::draw(){
    
    int curWidth = ofGetWidth();
    int curHeight = ofGetHeight();
    
    // Dessins des contrôles
    m_uiColors.draw();
    m_uiMSA.draw();
    m_uiTubesPatterns.draw();
    m_uiParts.draw();
    m_uiEasyOscOnOff.draw();
    m_uiEasyOscFades.draw();
    m_uiOthers.draw();
    m_uiDisplay.draw();
    
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
    
    // OSC, now !!!!!!!!!!!!!!!!!!!!!
    updateOSC();
    
    m_strTrace = m_oSpreadDisplay.m_strTrace;
    
    switch (m_slSetLogLevel) {
        case 0:
            ofSetLogLevel(OF_LOG_ERROR);
            m_lbGetLogLevel = "OF_LOG_ERROR";
            break;
            
        case 1:
            ofSetLogLevel(OF_LOG_WARNING);
            m_lbGetLogLevel = "OF_LOG_WARNING";
            break;
            
        case 2:
            ofSetLogLevel(OF_LOG_NOTICE);
            m_lbGetLogLevel = "OF_LOG_NOTICE";
            break;
            
        case 3:
            ofSetLogLevel(OF_LOG_VERBOSE);
            m_lbGetLogLevel = "OF_LOG_VERBOSE";
            break;
            
        default:
            break;
    }

}

void ofApp::keyPressed(int key){
    m_oSpreadDisplay.keyPressed(key);
}

void ofApp::keyReleased(int key){
    m_oSpreadDisplay.keyReleased(key);
}

void ofApp::windowResized(int w, int h){
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
