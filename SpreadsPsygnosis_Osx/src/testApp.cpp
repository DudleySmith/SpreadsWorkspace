#include "testApp.h"

// DECLARATION DES ELEMENTS D'INTERFACE ----------------------
void testApp::setup()
{
    m_trace.init(true, "GUI");
    
    ofSetWindowTitle("Spreads : Interface");
    createDisplay();
    
    // First Load Settings -----------------------------------
    loadSettings();
    // GUI Interface -----------------------------------------
    m_trace.go("Setup GUI");
    setupGUI();
    setupMSA();
    // MIDI Links -----------------------------------------
    //    m_trace.go("Setup MIDI");
    // OSC ------------------------------------------------
    m_oOsc.setup();
    m_trace.go("Setup OSC");
    
    setupOSC();
    
}


void testApp::createDisplay(){
    //spreadDisplay=ofxFensterManager::get()->createFenster(400, 300, 1024, 800, OF_WINDOW);;
    //spreadDisplay->addListener(new ofdSpreadDisplay());
    //:spreadDisplay->setBackgroundColor(ofRandom(255), ofRandom(255), ofRandom(255));
    
    mp_pointerSpreadDisplay = ofxFensterManager::get()->createFenster(1600, 0, 1600, 900, OF_WINDOW);
    mp_pointerSpreadDisplay->addListener(&m_spreadDisplay);
    mp_pointerSpreadDisplay->setBackgroundColor(0,0,0);
    
    //setup of fensterListener does not get called automatically yet
	mp_pointerSpreadDisplay->setup();
}

void testApp::setupMSA(){
    
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

void testApp::setupGUI(){
    
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
    
    // PAGE 1 : PRESETS
    // -------------------------------------------------------------------
    //    loadPresetsFromFolder("Nikkings");
    
    // Presets MSA
    //    for(int i=0; i<PRESET_MAX_COUNT; i++){
    //        string buttonName = "LOAD " + m_nikkings[i].name;
    //        gui.addButton("LOAD " + m_nikkings[i].name, m_nikkings[i].action);
    //    }
    //    vector<nikking>::iterator    onePreset;
    //    for(onePreset=m_nikkings.begin(); onePreset!=m_nikkings.end(); onePreset++){
    //        gui.addButton((*onePreset).name, (*onePreset).action);
    //    }
    //    gui.addTitle("Save as").setNewColumn(true);
    //    gui.addButton("Do save", (*onePreset).action);
    
    // PAGE 2 : General
    // -------------------------------------------------------------------
    //    gui.addPage(PAGE_2_Name);
    
    // PARTICLES SECTION ----------------------------------------------------------
    gui.addTitle("PARTICLES");
    gui.addToggle("particulesOn", mOut_vars.mI_particulesOn);
    
    partToSetup.setup();
    gui.addComboBox("Mode Parts", mOut_vars.mI_modeParts,partToSetup.m_iNbAvailableTypes, partToSetup.m_aAvailableTypes);
    gui.addSlider("emitSize", mOut_vars.mI_emitSize, 1, 20);
    gui.addSlider("Forces", mOut_vars.mI_coefForces, 0, 1);
    gui.addSlider("ForcesX", mOut_vars.mI_coefForces_X, 0, 1);
    gui.addSlider("ForcesY", mOut_vars.mI_coefForces_Y, 0, 1);
    gui.addSlider("speedRotation", mOut_vars.mI_speedRotation, 0, 1);
    gui.addSlider("Pulse", mOut_vars.mI_pulse, 0, 5);
    gui.addSlider("lifeBase", mOut_vars.mI_lifeBase, 0, 50);
    
    //    gui.addSlider("emitFlow", mOut_vars.mI_emitFlow, 0, 0.1);
    gui.addTitle("TUBES");
    gui.addToggle("raysOn", mOut_vars.mI_raysOn);
    gui.addToggle("traitsOn", mOut_vars.mI_traitsOn);
    
    gui.addSlider("restartIntensity", mOut_vars.mI_restartIntensity, 0, 255);
    gui.addSlider("Tube Delay", mOut_vars.mI_tubeDelay, mx_minTubeDelay, mx_maxTubeDelay);
    gui.addSlider("Tube Period", mOut_vars.mI_tubePeriod, mx_minTubePeriod,  mx_maxTubePeriod);
    gui.addSlider("Rays Delay", mOut_vars.mI_raysDelay, mx_minRaysDelay, mx_maxRaysDelay);
    gui.addSlider("Rays Period", mOut_vars.mI_raysPeriod, mx_minRaysPeriod, mx_maxRaysPeriod);
    
    // SPREADS SECTION ----------------------------------------------------------
    gui.addTitle("SPREADS");
    gui.addSlider("Pattern Family", mOut_vars.mI_numFamily, 0 , 20);
    gui.addSlider("Num Pattern", mOut_vars.mI_numPattern, 0 , 11);
    gui.addSlider("seqMinRate", mOut_vars.mI_seqMinRate, 0, 1);
    gui.addSlider("seqMaxRate", mOut_vars.mI_seqMaxRate, 0, 1);
    
    gui.addComboBox("modeTypo2", mOut_vars.mI_modeSeq, 4, modeSeq_Lbl);
    
    // FXs ---------------------------------------------------
    gui.addTitle("FX");
    fxToList.initList();
    
    gui.addComboBox("Mode FX", mOut_vars.mI_FX_mode, fxToList.modeListNb(), fxToList.modeList());
    gui.addSlider("Radius", mOut_vars.mI_FX_radius, 0, 1);
    gui.addSlider("Kal Nb Faces", mOut_vars.mI_FX_kalNbFaces, 1, 12);
    gui.addSlider("Kal Rot Period", mOut_vars.mI_FX_kalRotPeriod, 0, 1000);
    
    
    // SPREADS SECTION ----------------------------------------------------------
    gui.addTitle("COLORS").setNewColumn(true);
    // Manual casting for list of colors sets
    //    string listOfSets[m_ColorSetBase.nbSets()];
    //    for(int i=0; i<m_ColorSetBase.nbSets(); i++){
    //        listOfSets[i] = m_ColorSetBase.getList()[i];
    //    }
    //    gui.addComboBox("ColorSet", m_ColorSetBase.m_currentSet, m_ColorSetBase.nbSets(), listOfSets);
    //    gui.addButton("Load colors from Set", m_loadColorsFromSet);
    gui.addColorPicker("Color 1", mOut_vars._myColor_1);
    gui.addColorPicker("Color 2", mOut_vars._myColor_2);
    gui.addColorPicker("Color 3", mOut_vars._myColor_3);
    gui.addColorPicker("Color 4", mOut_vars._myColor_4);
    gui.addSlider("PERIOD", mOut_vars.mI_colorPeriod, 0, 10);
    gui.addSlider("HUE DECAY", mOut_vars.mI_hueDecay, 0, 1);
    gui.addSlider("DESAT", mOut_vars.mI_satDesat, 0, 1);
    
    // Audio réaction ---------------------------------------------------
    gui.addTitle("AUDIO");
    gui.addToggle("mode Audio", mOut_vars.mI_AudioR_mode);
    gui.addSlider("Bass_BangLevel", mOut_vars.mI_Bass_BangLevel, 0, 1);
    gui.addSlider("Mid_BangLevel", mOut_vars.mI_Mid_BangLevel, 0, 1);
    gui.addSlider("High_BangLevel", mOut_vars.mI_High_BangLevel, 0, 1);
    
    gui.addTitle("MSA Useful");
    gui.addComboBox("drawMode"               , mOut_vars.mI_MSAmode, 6, modeMSA);
    gui.addSlider("viscocity"                , mOut_vars.mI_MSAfluidSolverViscocity, 0.0, max_viscosity);
    gui.addSlider("colorDiffusion"           , mOut_vars.mI_MSAfluidSolverColorDiffusion, 0.0, 0.0003);
    gui.addSlider("fadeSpeed"                , mOut_vars.mI_MSAfluidSolverFadeSpeed, 0.0, 0.1);
    gui.addSlider("deltaT"                   , mOut_vars.mI_MSAfluidSolverDeltaT, 0.1, 5);
    gui.addSlider("colorMult"                , mOut_vars.mI_MSAcolorMult, 0, 100);
    gui.addSlider("velocityMult"             , mOut_vars.mI_MSAvelocityMult, 0, 100);
    // MOVES ---------------------------------------------------
    //    gui.addTitle("MOVES");
    //    gui.addSlider("Shake X", mOut_vars.mI_moveShakeX, 0, 0.05);
    //    gui.addSlider("Shake Y", mOut_vars.mI_moveShakeY, 0, 0.05);
    
    //    gui.currentPage().setXMLName(ofToString(NikkingsFolder)+m_currentNikking.name+PAGE_2_Name+".xml");
    //    gui.loadFromXML();
    
    // PAGE 3 : AUDIO + MSA parameters
    // -------------------------------------------------------------------
    gui.addPage(PAGE_3_Name);
    
    
    
    gui.addTitle("MSA Useless");
    gui.addSlider("fluidCellsX"              , mOut_vars.mI_MSAfluidCellsX, 20, 400);
    gui.addButton("resizeFluid"              , mOut_vars.mI_MSAResizeFluid);
    gui.addSlider("solverIterations"         , mOut_vars.mI_MSAfluidSolverSolverIterations, 1, 50);
    gui.addToggle("doRGB"                    , mOut_vars.mI_MSAdoRGB);
    gui.addToggle("doVorticityConfinement"   , mOut_vars.mI_MSAdoVorticityConfinement);
    gui.addToggle("drawFluid"                , mOut_vars.mI_MSAdrawFluid);
    gui.addToggle("drawParticles"            , mOut_vars.mI_MSAdrawParticles);
    gui.addToggle("wrapX"                    , mOut_vars.mI_MSAfluidSolverWrap_x);
    gui.addToggle("wrapY"                    , mOut_vars.mI_MSAfluidSolverWrap_y);
    
    //    gui.currentPage().setXMLName(NikkingsFolder+m_currentNikking.name+PAGE_3_Name+".xml");
    //    gui.loadFromXML();
    
    gui.setAutoSave(false);
    gui.setDefaultKeys(false);                          // Pas de touches
    gui.setPage(1);
    gui.show();
    
}

void testApp::setupOSC(){
    
    // PARTICLES SECTION ----------------------------------------------------------
    m_oOsc.add_link("/Tubes/On", 0, mOut_vars.mI_traitsOn);
    m_oOsc.add_link("/Tubes/Intensity", 0, mOut_vars.mI_restartIntensity, 0, 255);
    m_oOsc.add_link("/Tubes/Delay", 0, mOut_vars.mI_tubeDelay, mx_minTubeDelay, mx_maxTubeDelay);
    m_oOsc.add_link("/Tubes/Period", 0, mOut_vars.mI_tubePeriod, mx_minTubePeriod,  mx_maxTubePeriod);
    
    m_oOsc.add_link("/Rays/On", 0, mOut_vars.mI_raysOn);
    m_oOsc.add_link("/Rays/Delay", 0, mOut_vars.mI_raysDelay, mx_minRaysDelay, mx_maxRaysDelay);
    m_oOsc.add_link("/Rays/Period", 0, mOut_vars.mI_raysPeriod,mx_minRaysPeriod, mx_maxRaysPeriod);
    
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
    m_oOsc.add_link("/FXs/Mode", 0, mOut_vars.mI_FX_mode, 0, fxToList.modeListNb()-1);
    m_oOsc.add_link("/FXs/Radius", 0, mOut_vars.mI_FX_radius, 0, 1);
    m_oOsc.add_link("/FXs/KalNbFaces", 0, mOut_vars.mI_FX_kalNbFaces, 1, 12);
    m_oOsc.add_link("/FXs/KalRotPeriod", 0, mOut_vars.mI_FX_kalRotPeriod, 0, 1000);
    
    
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

void testApp::updateOSC(){
    
    m_oOsc.update();
    mOut_vars.m_messages = m_oOsc;
    
}

void testApp::loadSettings(){
    
    mx_minRaysPeriod = 100;
    mx_maxRaysPeriod = 500;
    
    mx_minRaysDelay = 0;
    mx_maxRaysDelay = 0.015;
    
    mx_minTubePeriod = 100;
    mx_maxTubePeriod = 1000;
    
    mx_minTubeDelay = 0;
    mx_maxTubeDelay = 0.500;
    
    // Fix values for ever
    mOut_vars.mI_emitFlow = 0.005;
    
    mOut_vars.mI_FX_kalNbFaces = 1;
    
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



void    testApp::savePresetsAs(){
    
    // Page 3 - MSA
    //    gui.page(PAGE_3_Name).setXMLName(NikkingsFolder+m_currentNikking.name+PAGE_3_Name+".xml");
    //    gui.page(PAGE_3_Name).;
    
}

void testApp::draw(){
    // Dessins des contrôles
    gui.draw();
    // Affichage des messages de fonctionnement
    ofPushStyle();
    ofSetColor(255);
    m_strTrace += " : " +m_currentNikking.name;
    ofDrawBitmapString(m_strTrace, 20, 20);
    
    ofPopStyle();
    
    /*
     //ofDrawBitmapString("Controls", 0.5*ofGetWidth(), 0.5*ofGetHeight());
     ofSetColor(mOut_vars.mI_ColorSet.ofdColorSet::getCurrentSetByIndex(0));
     ofRect(0.5*ofGetWidth(), 0.5*ofGetHeight(), 150, 150);
     
     ofSetColor(mOut_vars.mI_ColorSet.ofdColorSet::getCurrentSetByIndex(1));
     ofRect(0.5*ofGetWidth(), 0.5*ofGetHeight(), 120, 120);
     
     ofSetColor(mOut_vars.mI_ColorSet.ofdColorSet::getCurrentSetByIndex(2));
     ofRect(0.5*ofGetWidth(), 0.5*ofGetHeight(), 90, 90);
     
     ofSetColor(mOut_vars.mI_ColorSet.ofdColorSet::getCurrentSetByIndex(3));
     ofRect(0.5*ofGetWidth(), 0.5*ofGetHeight(), 50, 50);
     
     ofSetColor(mOut_vars._myColor_4);
     ofRect(0.5*ofGetWidth(), 0.5*ofGetHeight(), 20, 20);
     */
}

void testApp::update(){
    
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

void testApp::keyPressed(int key){
    mOut_vars.event_type = event_keyPressed;
    mOut_vars.key_pressed = key;
}

void testApp::keyReleased(int key){
    mOut_vars.event_type = event_keyReleased;
    mOut_vars.key_released = key;
}

void testApp::windowResized(int w, int h){
    //
    mOut_vars.event_type = event_winResized;
}

void testApp::MSAload(){
    // Changement de page MSA
    gui.page(PAGE_3_Name).setXMLName(NikkingsFolder+m_currentNikking.name+PAGE_3_Name+".xml");
    gui.page(PAGE_3_Name).loadFromXML();
}

void    testApp::loadPresetsFromFolder(string _folder){
    
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
