#include "ofApp.h"

// DECLARATION DES ELEMENTS D'INTERFACE ----------------------
void ofApp::setup()
{
    m_trace.init(true, "GUI");
    ofSetLogLevel(OF_LOG_VERBOSE);
    
    ofSetWindowTitle("Spreads : Interface");
    createDisplay();
    ofSetBackgroundAuto(true);
    
    // First Load Settings -----------------------------------
    loadSettings();
    
    // COLORS -------------------------
    // Load colors
    mOut_vars.mI_ColorSet.setup("colorSets.xml");
    
    // GUI Interface -----------------------------------------
    m_trace.go("Setup GUI");
    setupGUI();
    setupMSA();
    // MIDI Links -----------------------------------------
    //    m_trace.go("Setup MIDI");
    // OSC ------------------------------------------------
//    m_oOsc.setup();
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

void ofApp::setupMSA(){
    
    mOut_vars.mI_MSAfluidCellsX = 120;
    mOut_vars.mI_MSAResizeFluid = 0;
    mOut_vars.mI_MSAfluidSolverSolverIterations = 45.345001221;
    mOut_vars.mI_MSAdoRGB = 1;
    mOut_vars.mI_MSAdoVorticityConfinement = 0;
    mOut_vars.mI_MSAdrawFluid = 1;
    mOut_vars.mI_MSAdrawParticles = 0;
    mOut_vars.mI_MSAfluidSolverWrap_x = 1;
    mOut_vars.mI_MSAfluidSolverWrap_y = 1;
    
}

void ofApp::setupGUI(){
    
    // GUI Interface -----------------------------------------
    
    string modeSeq_Lbl[4];
    modeSeq_Lbl[0] = "1 - Debut->Fin";
    modeSeq_Lbl[1] = "2 - Fin->Debut";
    modeSeq_Lbl[2] = "3 - Milieu";
    modeSeq_Lbl[3] = "4 - Random";
    
    string modeMSA[6];
    modeMSA[0] = "None";
    modeMSA[1] = "Vectors";
    modeMSA[2] = "Colors";
    modeMSA[3] = "Speed";
    modeMSA[4] = "Motion";
    modeMSA[5] = "DrawCount";
    
    // TUBES ---------------------------------------------------------------------
    m_gpTubes.setName("Tubes");
    m_gpTubes.add(m_btRaysOn.set("RaysOn", mOut_vars.mI_raysOn));
    m_gpTubes.add(m_btTraitsOn.set("TraitsOn", mOut_vars.mI_traitsOn));
    m_gpTubes.add(m_slRestartIntensity.set("RestartIntensity", mOut_vars.mI_restartIntensity, 0, 255));
    m_gpTubes.add(m_slTubeDelay.set("TubesDelay", mOut_vars.mI_tubeDelay, mx_minTubeDelay, mx_maxTubeDelay));
    m_gpTubes.add(m_slTubePeriod.set("TubesPeriod", mOut_vars.mI_tubePeriod, mx_minTubePeriod,  mx_maxTubePeriod));
    m_gpTubes.add(m_slRaysDelay.set("RaysDelay", mOut_vars.mI_raysDelay, mx_minRaysDelay, mx_maxRaysDelay));
    m_gpTubes.add(m_slRaysPeriod.set("RaysPeriod", mOut_vars.mI_raysPeriod, mx_minRaysPeriod, mx_maxRaysPeriod));
    m_gpTubesPatterns.add(m_gpTubes);
    
    // SPREADS SECTION ----------------------------------------------------------
    m_gpPatterns.setName("Patterns");
    m_gpPatterns.add(m_slPatternFamily.set("PatternFamily", mOut_vars.mI_numFamily, 0 , 20));
    m_gpPatterns.add(m_slNumPattern.set("NumPattern", mOut_vars.mI_numPattern, 0 , 11));
    m_gpPatterns.add(m_slSeqMinRate.set("SeqMinRate", mOut_vars.mI_seqMinRate, 0, 1));
    m_gpPatterns.add(m_slSeqMaxRate.set("SeqMaxRate", mOut_vars.mI_seqMaxRate, 0, 1));
    m_gpPatterns.add(m_slModeTypo2.set("ModeTypo", mOut_vars.mI_modeSeq, 0, 3));
    // TODO : ajouter un label
    m_gpTubesPatterns.add(m_gpPatterns);
    
//    m_uiOthers.setup(m_gpGen);
    
    
    // Audio réaction ---------------------------------------------------
    /*
    m_gpAudio.setName("Audio");
    m_gpAudio.add(m_btModeAudio.set("mode Audio", mOut_vars.mI_AudioR_mode));
    m_gpAudio.add(m_slBass_BangLevel.set("Bass_BangLevel", mOut_vars.mI_Bass_BangLevel, 0, 1));
    m_gpAudio.add(m_slMid_BangLevel.set("Mid_BangLevel", mOut_vars.mI_Mid_BangLevel, 0, 1));
    m_gpAudio.add(m_slHigh_BangLevel.set("High_BangLevel", mOut_vars.mI_High_BangLevel, 0, 1));
    m_gpGen.add(m_gpAudio);
    */
    
    // MSA Useful ---------------------------------------------------------
    m_gpMSA_Useful.setName("MSAUseful");
    // TODO : Add Label
    m_gpMSA_Useful.add(m_slDrawMode.set("DrawMode", mOut_vars.mI_MSAmode, 0, 5));
    m_gpMSA_Useful.add(m_slViscocity.set("Viscocity", mOut_vars.mI_MSAfluidSolverViscocity, 0.0, max_viscosity));
    m_gpMSA_Useful.add(m_slColorDiffusion.set("ColorDiffusion", mOut_vars.mI_MSAfluidSolverColorDiffusion, 0.0, 0.0003));
    m_gpMSA_Useful.add(m_slFadeSpeed.set("FadeSpeed", mOut_vars.mI_MSAfluidSolverFadeSpeed, 0.0, 0.1));
    m_gpMSA_Useful.add(m_slDeltaT.set("DeltaT", mOut_vars.mI_MSAfluidSolverDeltaT, 0.1, 5));
    m_gpMSA_Useful.add(m_slColorMult.set("ColorMult", mOut_vars.mI_MSAcolorMult, 0, 100));
    m_gpMSA_Useful.add(m_slVelocityMult.set("VelocityMult", mOut_vars.mI_MSAvelocityMult, 0, 100));
    m_gpMSA.add(m_gpMSA_Useful);
    
    // PAGE 3 : AUDIO + MSA parameters
    m_gpMSA_Useless.setName("MSAUseless");
    m_gpMSA_Useless.add(m_slfluidCellsX.set("FluidCellsX", mOut_vars.mI_MSAfluidCellsX, 20, 400));
    m_gpMSA_Useless.add(m_btResizeFluid.set("ResizeFluid", mOut_vars.mI_MSAResizeFluid));
    m_gpMSA_Useless.add(m_slSolverIterations.set("SolverIterations", mOut_vars.mI_MSAfluidSolverSolverIterations, 1, 50));
    m_gpMSA_Useless.add(m_btDoRGB.set("DoRGB", mOut_vars.mI_MSAdoRGB));
    m_gpMSA_Useless.add(m_btDoVorticityConfinement.set("DoVorticityConfinement", mOut_vars.mI_MSAdoVorticityConfinement));
    m_gpMSA_Useless.add(m_btDrawFluid.set("DrawFluid", mOut_vars.mI_MSAdrawFluid));
    m_gpMSA_Useless.add(m_btDrawParticles.set("DrawParticles", mOut_vars.mI_MSAdrawParticles));
    m_gpMSA_Useless.add(m_btWrapX.set("WrapX", mOut_vars.mI_MSAfluidSolverWrap_x));
    m_gpMSA_Useless.add(m_btWrapY.set("WrapY", mOut_vars.mI_MSAfluidSolverWrap_y));
    m_gpMSA.add(m_gpMSA_Useless);
    
    
    // PARTICLES SECTION ----------------------------------------------------------
    m_uiParts.setup(m_spreadDisplay.m_oPartWorld.m_pgSets, "Parts.xml");
    m_uiParts.add(m_btPartsOn.set("ParticulesOn", mOut_vars.mI_particulesOn));
    
    // COULEURS ---------------------------------------------------------------------
    m_uiColors.setName("Colors");
    m_uiColors.setup(mOut_vars.mI_ColorSet.m_oUI.m_gGroup, "Colors.xml");
    m_uiColors.setPosition(10, 30);

    
    // UIs - Setting names and places
    
    m_gpTubesPatterns.setName("TubesPatterns");
    m_uiTubesPatterns.setName("TubesPatterns");
    m_uiTubesPatterns.setup(m_gpTubesPatterns, "TubesPatterns.xml");
    
    m_gpMSA.setName("MSA");
    m_uiMSA.setName("MSA");
    m_uiMSA.setup(m_gpMSA, "MSA.xml");
    
    m_uiColors.loadFromFile("Colors.xml");
    m_uiParts.loadFromFile("Parts.xml");
    m_uiTubesPatterns.loadFromFile("TubesPatterns.xml");
    m_uiMSA.loadFromFile("MSA.xml");
    
    
    int idxUI = 0;
    m_uiColors.setPosition(10 + (idxUI++)*250, 30);
    m_uiParts.setPosition(10 + (idxUI++)*250, 30);
    m_uiTubesPatterns.setPosition(10 + (idxUI++)*250, 30);
    m_uiMSA.setPosition(10 + (idxUI++)*250, 30);
    
    m_oLiveGrabberColors.setup((ofParameterGroup&)m_uiColors.getParameter(),9001,"localhost",9000);
    m_oLiveGrabberParts.setup((ofParameterGroup&)m_uiParts.getParameter(),9002,"localhost",9000);
    m_oLiveGrabberOthers.setup((ofParameterGroup&)m_uiTubesPatterns.getParameter(),9003,"localhost",9000);
    m_oLiveGrabberOthers.setup((ofParameterGroup&)m_uiMSA.getParameter(),9004,"localhost",9000);

}

void ofApp::setupOSC(){
    
    // PARTICLES SECTION ----------------------------------------------------------
    m_oOsc.add_link("/Tubes/On", 0, mOut_vars.mI_traitsOn);
    m_oOsc.add_link("/Tubes/Intensity", 0, mOut_vars.mI_restartIntensity, 0, 255);
    m_oOsc.add_link("/Tubes/Delay", 0, mOut_vars.mI_tubeDelay, mx_minTubeDelay, mx_maxTubeDelay);
    m_oOsc.add_link("/Tubes/Period", 0, mOut_vars.mI_tubePeriod, mx_minTubePeriod,  mx_maxTubePeriod);
    
    m_oOsc.add_link("/Rays/On", 0, mOut_vars.mI_raysOn);
    m_oOsc.add_link("/Rays/Delay", 0, mOut_vars.mI_raysDelay, mx_minRaysDelay, mx_maxRaysDelay);
    m_oOsc.add_link("/Rays/Period", 0, mOut_vars.mI_raysPeriod,mx_minRaysPeriod, mx_maxRaysPeriod);
    
    /*
     
     TODO, link OSC with new ofxParticleWorld GUI setup
     
    partToSetup.setup();
    m_oOsc.add_link("/Parts/On", 0, mOut_vars.mI_particulesOn);
    m_oOsc.add_link("/Parts/Mode", 0, mOut_vars.mI_modeParts, 0, partToSetup.m_iNbAvailableTypes-1);
    m_oOsc.add_link("/Parts/Size", 0, mOut_vars.mI_emitSize, 1, 20);
    m_oOsc.add_link("/Parts/Power", 0, mOut_vars.mI_coefForces, 0, 1);
    m_oOsc.add_link("/Parts/PowerX", 0, mOut_vars.mI_coefForces_X, 0, 1);
    m_oOsc.add_link("/Parts/PowerY", 0, mOut_vars.mI_coefForces_Y, 0, 1);
    m_oOsc.add_link("/Parts/Rotation", 0, mOut_vars.mI_speedRotation, 0, 1);
    m_oOsc.add_link("/Parts/Pulse", 0, mOut_vars.mI_pulse, 0, 5);
    m_oOsc.add_link("/Parts/Life", 0, mOut_vars.mI_lifeBase, 0, 50);
    */
    
    // SPREADS SECTION ----------------------------------------------------------
    m_oOsc.add_link("/Patterns/Family", 0, mOut_vars.mI_numFamily, 0 , 20);
    m_oOsc.add_link("/Patterns/Number", 0, mOut_vars.mI_numPattern, 0 , 11);
    m_oOsc.add_link("/Patterns/Min", 0, mOut_vars.mI_seqMinRate, 0, 1);
    m_oOsc.add_link("/Patterns/Max", 0, mOut_vars.mI_seqMaxRate, 0, 1);
    m_oOsc.add_link("/Patterns/Mode", 0, mOut_vars.mI_modeSeq, 0, 3);
    
    
    // SPREADS SECTION ----------------------------------------------------------
    m_oOsc.add_link("/Colors/1/Hue", 0, mOut_vars._myColor_1_Hue);
    m_oOsc.add_link("/Colors/1/Sat", 0, mOut_vars._myColor_1_Sat);
    m_oOsc.add_link("/Colors/1/Bright", 0, mOut_vars._myColor_1_Brg);
    
    m_oOsc.add_link("/Colors/2/Hue", 0, mOut_vars._myColor_2_Hue);
    m_oOsc.add_link("/Colors/2/Sat", 0, mOut_vars._myColor_2_Sat);
    m_oOsc.add_link("/Colors/2/Bright", 0, mOut_vars._myColor_2_Brg);
    
    m_oOsc.add_link("/Colors/3/Hue", 0, mOut_vars._myColor_3_Hue);
    m_oOsc.add_link("/Colors/3/Sat", 0, mOut_vars._myColor_3_Sat);
    m_oOsc.add_link("/Colors/3/Bright", 0, mOut_vars._myColor_3_Brg);
    
    m_oOsc.add_link("/Colors/4/Hue", 0, mOut_vars._myColor_4_Hue);
    m_oOsc.add_link("/Colors/4/Sat", 0, mOut_vars._myColor_4_Sat);
    m_oOsc.add_link("/Colors/4/Bright", 0, mOut_vars._myColor_4_Brg);
    
    m_oOsc.add_link("/Colors/Period", 0, mOut_vars.mI_colorPeriod, 0, 10);
    m_oOsc.add_link("/Colors/Decay", 0, mOut_vars.mI_hueDecay, 0, 1);
    m_oOsc.add_link("/Colors/Desat", 0, mOut_vars.mI_satDesat, 0, 1);
    
    // MOVES ---------------------------------------------------
    //    0, mOut_vars.mI_moveShakeX = m_oOsc.getSmartValue("/Moves/Shake/X", 0, 0.05);
    //    0, mOut_vars.mI_moveShakeY = m_oOsc.getSmartValue("/Moves/Shake/Y", 0, 0.05);
    
    // FXs ---------------------------------------------------
    /*
    m_oOsc.add_link("/FXs/Mode", 0, mOut_vars.mI_FX_mode, 0, fxToList.modeListNb()-1);
    m_oOsc.add_link("/FXs/Radius", 0, mOut_vars.mI_FX_radius, 0, 1);
    m_oOsc.add_link("/FXs/KalNbFaces", 0, mOut_vars.mI_FX_kalNbFaces, 1, 12);
    m_oOsc.add_link("/FXs/KalRotPeriod", 0, mOut_vars.mI_FX_kalRotPeriod, 0, 1000);
    */
    
    // PAGE 3 : AUDIO + MSA parameters
    m_oOsc.add_link("/MSA/DrawMode", 0, mOut_vars.mI_MSAmode, 0, 5);
    m_oOsc.add_link("/MSA/Viscosity", 0, mOut_vars.mI_MSAfluidSolverViscocity , 0.0, max_viscosity);
    m_oOsc.add_link("/MSA/ColorDiffusion", 0, mOut_vars.mI_MSAfluidSolverColorDiffusion, 0.0, 0.0003);
    m_oOsc.add_link("/MSA/FadeSpeed", 0, mOut_vars.mI_MSAfluidSolverFadeSpeed, 0.0, 0.1);
    m_oOsc.add_link("/MSA/DeltaT", 0, mOut_vars.mI_MSAfluidSolverDeltaT, 0.1, 5);
    m_oOsc.add_link("/MSA/ColorMult", 0, mOut_vars.mI_MSAcolorMult, 0, 100);
    m_oOsc.add_link("/MSA/VelocityMult", 0, mOut_vars.mI_MSAvelocityMult, 0, 100);
    
    
    // NOTES ----------------------------------------------------------------
    // PAD PAGE 1 -----------------------------------------------------------------
    //    int noteStart = m_oTools.midiNoteToInt("C3");
    //    int noteEnd = m_oTools.midiNoteToInt("B3");
    //    int noteLoop = 0;
    //    string noteStr = "C0";
    //
    //
    //    for(noteLoop=noteStart; noteLoop<noteEnd; noteLoop++){
    //        noteStr = m_oTools.midiNoteToString(noteLoop);
    //
    //        mOut_vars.m_notes[noteStr] = false;
    //        m_oOsc.add_link("/notes/" + noteStr, 0, mOut_vars.m_notes[noteStr]);
    //    }
    
}

void ofApp::updateOSC(){
    
    //    m_oOsc.update();
    m_oLiveGrabberColors.update();
    m_oLiveGrabberOthers.update();
    m_oLiveGrabberParts.update();
    mOut_vars.m_messages = m_oOsc;
    
}

void ofApp::loadSettings(){
    
    mx_minRaysPeriod = 100;
    mx_maxRaysPeriod = 500;
    
    mx_minRaysDelay = 0;
    mx_maxRaysDelay = 0.015;
    
    mx_minTubePeriod = 100;
    mx_maxTubePeriod = 1000;
    
    mx_minTubeDelay = 0;
    mx_maxTubeDelay = 0.500;
    
    //mOut_vars.mI_FX_kalNbFaces = 1;
    
    //    gui.addSlider("fluidCellsX"              , mOut_vars.mI_MSAfluidCellsX, 20, 400);
    //    gui.addButton("resizeFluid"              , mOut_vars.mI_MSAResizeFluid);
    //    gui.addSlider("solverIterations"         , mOut_vars.mI_MSAfluidSolverSolverIterations, 1, 50);
    //    gui.addToggle("doRGB"                    , mOut_vars.mI_MSAdoRGB);
    //    gui.addToggle("doVorticityConfinement"   , mOut_vars.mI_MSAdoVorticityConfinement);
    //    gui.addToggle("drawFluid"                , mOut_vars.mI_MSAdrawFluid);
    //    gui.addToggle("drawParticles"            , mOut_vars.mI_MSAdrawParticles);
    //    gui.addToggle("wrapX"                    , mOut_vars.mI_MSAfluidSolverWrap_x);
    //    gui.addToggle("wrapY"                    , mOut_vars.mI_MSAfluidSolverWrap_y);
    
}



void    ofApp::savePresetsAs(){
    
    // Page 3 - MSA
    //    gui.page(PAGE_3_Name).setXMLName(NikkingsFolder+m_currentNikking.name+PAGE_3_Name+".xml");
    //    gui.page(PAGE_3_Name).;
    
}

void ofApp::draw(){
    // Dessins des contrôles
    m_uiColors.draw();
    m_uiMSA.draw();
    m_uiTubesPatterns.draw();
    m_uiParts.draw();
    
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
            if(file.exists() && file.getExtension()=="xml" && ofIsStringInString(file.getBaseName(), PAGE_2_Name)==true){
                shortName = ofSplitString(file.getBaseName(), PAGE_2_Name);
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
