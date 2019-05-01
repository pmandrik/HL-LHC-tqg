
#include "tqgamma_fNtuple.hh"

float get_dR2(float x1, float y1, float x2, float y2){
  return pow(x1 - y1, 2) +  pow(x2 - y2, 2);
}

void check_tree(string inp_name){
  TFile * file = TFile::Open( inp_name.c_str() );
  if(not file){
    cout << " Can't open input file ... " << endl;
  }

  file->cd("ntuple");
  auto    fChain_MuonLoose = (TTree*) gDirectory->Get("MuonLoose");
  auto    fChain_ElectronTight = (TTree*) gDirectory->Get("ElectronTight");
  auto    fChain_ElectronLoose = (TTree*) gDirectory->Get("ElectronLoose");
  auto    fChain_Particle = (TTree*) gDirectory->Get("Particle");
  auto    fChain_ElectronMedium = (TTree*) gDirectory->Get("ElectronMedium");
  auto    fChain_Vertex = (TTree*) gDirectory->Get("Vertex");
  auto    fChain_GenJet = (TTree*) gDirectory->Get("GenJet");
  auto    fChain_MuonTight = (TTree*) gDirectory->Get("MuonTight");
  auto    fChain_PhotonLoose = (TTree*) gDirectory->Get("PhotonLoose");
  auto    fChain_PhotonTight = (TTree*) gDirectory->Get("PhotonTight");
  auto    fChain_JetPUPPI = (TTree*) gDirectory->Get("JetPUPPI");
  auto    fChain_PuppiMissingET = (TTree*) gDirectory->Get("PuppiMissingET");
  auto    fChain_Event = (TTree*) gDirectory->Get("Event");
  auto    fChain_GenPhoton = (TTree*) gDirectory->Get("GenPhoton");


  Int_t Run;
    Int_t Event;
    Int_t Lumi;
    Int_t Weight_size;
    Float_t Weight[500];
    Int_t Particle_size;
    Int_t GenPhoton_size;
    Int_t Vertex_size;
    Int_t GenJet_size;
    Int_t ElectronLoose_size;
    Int_t ElectronMedium_size;
    Int_t ElectronTight_size;
    Int_t MuonLoose_size;
    Int_t MuonTight_size;
    Int_t JetPUPPI_size;
    Int_t PuppiMissingET_size;
    Int_t PhotonLoose_size;
    Int_t PhotonTight_size;

fChain_Event->SetBranchAddress("Run", &Run);
      fChain_Event->SetBranchAddress("Event", &Event);
      fChain_Event->SetBranchAddress("Lumi", &Lumi);
      fChain_Event->SetBranchAddress("Weight_size", &Weight_size);
fChain_Event->SetBranchAddress("Weight", Weight);
      fChain_Particle->SetBranchAddress("Particle_size", &Particle_size);
      fChain_GenPhoton->SetBranchAddress("GenPhoton_size", &GenPhoton_size);
      fChain_Vertex->SetBranchAddress("Vertex_size", &Vertex_size);
      fChain_GenJet->SetBranchAddress("GenJet_size", &GenJet_size);
      fChain_ElectronLoose->SetBranchAddress("ElectronLoose_size", &ElectronLoose_size);
      fChain_ElectronMedium->SetBranchAddress("ElectronMedium_size", &ElectronMedium_size);
      fChain_ElectronTight->SetBranchAddress("ElectronTight_size", &ElectronTight_size);
      fChain_MuonLoose->SetBranchAddress("MuonLoose_size", &MuonLoose_size);
      fChain_MuonTight->SetBranchAddress("MuonTight_size", &MuonTight_size);
      fChain_JetPUPPI->SetBranchAddress("JetPUPPI_size", &JetPUPPI_size);
      fChain_PuppiMissingET->SetBranchAddress("PuppiMissingET_size", &PuppiMissingET_size);
      fChain_PhotonLoose->SetBranchAddress("PhotonLoose_size", &PhotonLoose_size);
      fChain_PhotonTight->SetBranchAddress("PhotonTight_size", &PhotonTight_size);


  int entry = 0;
  fChain_MuonLoose->GetEntry(entry);
      fChain_ElectronTight->GetEntry(entry);
      fChain_ElectronLoose->GetEntry(entry);
      fChain_Particle->GetEntry(entry);
      fChain_ElectronMedium->GetEntry(entry);
      fChain_Vertex->GetEntry(entry);
      fChain_GenJet->GetEntry(entry);
      fChain_MuonTight->GetEntry(entry);
      fChain_PhotonLoose->GetEntry(entry);
      fChain_PhotonTight->GetEntry(entry);
      fChain_JetPUPPI->GetEntry(entry);
      fChain_PuppiMissingET->GetEntry(entry);
      fChain_Event->GetEntry(entry);
      fChain_GenPhoton->GetEntry(entry);


cout << Particle_size << endl;
    cout << GenPhoton_size << endl;
    cout << Vertex_size << endl;
    cout << GenJet_size << endl;
    cout << ElectronLoose_size << endl;
    cout << ElectronMedium_size << endl;
    cout << ElectronTight_size << endl;
    cout << MuonLoose_size << endl;
    cout << MuonTight_size << endl;
    cout << JetPUPPI_size << endl;
    cout << PuppiMissingET_size << endl;
    cout << PhotonLoose_size << endl;
    cout << PhotonTight_size << endl;
}


// ================================================================================================================================ //
int analyse_single_file(string inp_name, string out_name, Long64_t max_events=0, const double dataset_weight_old = 1, const double dataset_weight_new = 1, string systematic_mode=""){
  cout << "analyse_single_file(): " << inp_name << " " << out_name << " " << max_events << endl;

  /*
    DONE lumi            ~ 1.5 % of normalisation
    DONE e/mu id, iso    ~ 1.0 % of normalisation
    DONE btag Systematic ~ 1 %, weights
    DONE Scale           ~ ?, weights
    DONE JES  Systematic ~ variation samples

    // https://github.com/piedraj/AnalysisCMS/blob/master/systematics/getPdfQcd.C
    // https://twiki.cern.ch/twiki/bin/viewauth/CMS/LHEReaderCMSSW
  */

  bool is_JES_Up   = ( systematic_mode == "JES_Up"  );
  bool is_JES_Down = ( systematic_mode == "JES_Down");
  if(is_JES_Up or is_JES_Down) cout << "Will use systematic mode " << systematic_mode << endl;

  TFile * file_out = new TFile( out_name.c_str(), "RECREATE");
  TTree * tree = new TTree("ttree", "ttree");

  float Lepton_Pt, Lepton_Phi, Lepton_Eta, Lepton_Px, Lepton_Py, Lepton_Pz, Lepton_E, Lepton_Type;
  float MET_Pt, MET_Phi, MET_Px, MET_Py, W_Pt, W_Mt, bJet_Pt, bJet_Phi, bJet_Eta, t_Pt, t_Phi, t_Eta, t_M, LightJet_Pt, LightJet_Phi, LightJet_Eta;
  float bJetLepton_Mass, bJetLepton_Pt, bJetTop_dPhi, bJetW_dPhi, bJetTop_dEta;
  float LeadingJet_Pt, LeadingJet_Px, LeadingJet_Py, LeadingJet_Pz, LeadingJet_E;
  float SecondJet_Pt, SecondJet_Px, SecondJet_Py, SecondJet_Pz, SecondJet_E;
  float LeadingJetSecondJet_Pt, LeadingJetSecondJet_M, LeadingJetSecondJet_dR;
  float Jets_SumPt, Jets_SumPt_minus_bJet_Pt, Jets_M_without_bJet, JetsW_M, Jets_N;
  float Sphericity, Planarity, Aplanarity;
  float cos_lightJetLepton_tsystem, cos_lightJetW_tsystem, cos_leptonW_Wsystem;

  float weight = 1;
  float weight_old = 1;
  float weight_MC_nominal = 1;
  float weight_MC_alpha_s_Up = -1, weight_MC_alpha_s_Down = -1;
  float weight_MC_RF[20];
  float weight_btagUp = -1, weight_btagDown = -1;

  tree->Branch("weight",             &weight);
  tree->Branch("weight_old",         &weight_old);
  tree->Branch("weight_MC_nominal",  &weight_MC_nominal);
  // Systematic
  tree->Branch("weight_MC_alpha_s_Up",   &weight_MC_alpha_s_Up);
  tree->Branch("weight_MC_alpha_s_Down", &weight_MC_alpha_s_Down);
  for(int i = 0; i < 20; i++){
    weight_MC_RF[i] = -1;
    tree->Branch( ("weight_MC_RF_" + to_string(i)).c_str(),  &(weight_MC_RF[i]) );
  }

  tree->Branch("weight_btagUp",   &weight_btagUp);
  tree->Branch("weight_btagDown", &weight_btagDown);
  // Lepton from W
  tree->Branch("Lepton_Pt",  &Lepton_Pt);
  tree->Branch("Lepton_Phi", &Lepton_Phi);
  tree->Branch("Lepton_Eta", &Lepton_Eta);
  tree->Branch("Lepton_E",   &Lepton_E);
  tree->Branch("Lepton_Px",  &Lepton_Px);
  tree->Branch("Lepton_Py",  &Lepton_Py);
  tree->Branch("Lepton_Pz",  &Lepton_Pz);
  tree->Branch("Lepton_Type",  &Lepton_Type);
  // MET from  W
  tree->Branch("MET_Pt",  &MET_Pt);
  tree->Branch("MET_Phi", &MET_Phi);
  tree->Branch("MET_Px",  &MET_Px);
  tree->Branch("MET_Py",  &MET_Py);
  // W
  tree->Branch("W_Pt", &W_Pt);
  tree->Branch("W_Mt", &W_Mt);              // <---- transverse mass of reconstructed W boson
  // bJet
  tree->Branch("bJet_Pt", &bJet_Pt);        // <---- transverse momentum of b jet 
  tree->Branch("bJet_Phi", &bJet_Phi);
  tree->Branch("bJet_Eta", &bJet_Eta);
  // top
  tree->Branch("t_Pt",  &t_Pt);             // <---- transverse momentum of reconstructed top 
  tree->Branch("t_Phi", &t_Phi);
  tree->Branch("t_Eta", &t_Eta);
  tree->Branch("t_M", &t_M);
  // light jet
  tree->Branch("LightJet_Pt",  &LightJet_Pt);
  tree->Branch("LightJet_Phi", &LightJet_Phi);
  tree->Branch("LightJet_Eta", &LightJet_Eta);
  // leading jet
  tree->Branch("LeadingJet_Pt",  &LeadingJet_Pt);
  tree->Branch("LeadingJet_Px",  &LeadingJet_Px);
  tree->Branch("LeadingJet_Py",  &LeadingJet_Py);
  tree->Branch("LeadingJet_Pz",  &LeadingJet_Pz);
  tree->Branch("LeadingJet_E",   &LeadingJet_E);
  // second jet
  tree->Branch("SecondJet_Pt",  &SecondJet_Pt);
  tree->Branch("SecondJet_Px",  &SecondJet_Px);
  tree->Branch("SecondJet_Py",  &SecondJet_Py);
  tree->Branch("SecondJet_Pz",  &SecondJet_Pz);
  tree->Branch("SecondJet_E",   &SecondJet_E);
  // leading and second
  tree->Branch("LeadingJetSecondJet_Pt",  &LeadingJetSecondJet_Pt);
  tree->Branch("LeadingJetSecondJet_M",   &LeadingJetSecondJet_M);
  tree->Branch("LeadingJetSecondJet_dR",  &LeadingJetSecondJet_dR);
  // all good jets
  tree->Branch("Jets_SumPt",              &Jets_SumPt);
  tree->Branch("Jets_SumPt_minus_bJet_Pt",&Jets_SumPt_minus_bJet_Pt);
  tree->Branch("Jets_M_without_bJet",     &Jets_M_without_bJet);
  tree->Branch("JetsW_M",                 &JetsW_M);
  tree->Branch("Jets_N",                  &Jets_N);

  tree->Branch("Sphericity",              &Sphericity);
  tree->Branch("Planarity",               &Planarity);
  tree->Branch("Aplanarity",              &Aplanarity);

  // MVA INPUT VARIABLES
  tree->Branch("MVA_bJetLepton_Mass", &bJetLepton_Mass);  // <---- invariant mass of lepton and bjet
  tree->Branch("MVA_bJetLepton_Pt",   &bJetLepton_Pt);    // <---- vector sum of pt for b jet and lepton
  tree->Branch("MVA_bJetTop_dPhi",    &bJetTop_dPhi);     // <---- difference in azimuth angle between top and b jet
  tree->Branch("MVA_bJetW_dPhi",      &bJetW_dPhi);       // <---- difference in azimuth angle between W boson and b jet
  tree->Branch("MVA_bJetTop_dEta",    &bJetTop_dEta);     // <---- difference in eta of top and b jet

  // DNN INPUT VARIABLES
  tree->Branch("cos_lightJetLepton_tsystem", &cos_lightJetLepton_tsystem);
  tree->Branch("cos_lightJetW_tsystem",      &cos_lightJetW_tsystem);
  tree->Branch("cos_leptonW_Wsystem",        &cos_leptonW_Wsystem);

  TH1D * skip_hist = new TH1D("selections", "selections", 10, 0, 10);

  TFile * file = TFile::Open( inp_name.c_str() );
  if(not file){
    cout << " Can't open input file ... " << endl;
  }
  tqgamma_Event event;
  event.Init(file);
  Long64_t nevents = event.fChain_Event->GetEntries();
  event.GetEntry( 0 );
/*
  cout << "event.Particle_size " << event.Particle_size << endl;
  cout << "event.GenPhoton_size " <<event.GenPhoton_size << endl;
  cout << "eevent.Vertex_size " <<event.Vertex_size << endl;
  cout << "event.GenJet_size " <<event.GenJet_size << endl;
  cout << "event.ElectronLoose_size " <<event.ElectronLoose_size << endl;
  cout << "event.ElectronMedium_size " <<event.ElectronMedium_size << endl;
  cout << "event.ElectronTight_size " <<event.ElectronTight_size << endl;
  cout << "event.MuonLoose_size " <<event.MuonLoose_size << endl;
  cout << "event.MuonTight_size " <<event.MuonTight_size << endl;
  cout << "event.JetPUPPI_size " <<event.JetPUPPI_size << endl;
  cout << "event.PuppiMissingET_size " <<event.PuppiMissingET_size << endl;
  cout << "eevent.PhotonLoose_size " <<event.PhotonLoose_size << endl;
  cout << "event.PhotonTight_size " <<event.PhotonTight_size << endl;
  event.fChain_MuonTight->Show();
*/
  if(max_events) nevents = TMath::Min(max_events, nevents);

/*
    V X Mass_bl       invariant mass of lepton and bjet
    V X pt_b          transverse momentum of b jet 
    V X Pt_bl         vector sum of pt for b jet and lepton         
    V X mtw           transverse mass of reconstructed W boson 
    V X dphi_lmet     difference in azimuth angle between top and b jet
    V X pt_top        transverse momentum of reconstructed top 
    V X dphi_wb       difference in azimuth angle between W boson and b jet
    V X deta_topb     difference in eta of top and b jet
*/

  cout << " begin loop ... " << endl;
  Long64_t event_skiped = 0;
  Long64_t muon_chanel = 0, electron_chanel = 0;
  file->cd();

  for(Long64_t nevent = 0; nevent < nevents; nevent++){
    event.GetEntry( nevent );
    if(false){
      skip_event:;
      event_skiped++;
      continue;
    }

    // ====== SELECTION PARTS ==============================================================================>
    
    // one tight electron or muon
    int lepton_index = -1;
    int lepton_is_muon = true;
    for(int i = 0; i < event.MuonTight_size; i++){
      if( event.MuonTight_PT[i]           < 25.  ) continue; 
      if( abs(event.MuonTight_Eta[i])     > 2.8  ) continue;
      if( event.MuonTight_IsolationVar[i] > 0.15 ) continue;
      if(lepton_index != -1){ 
        skip_hist->Fill("addition good muon", 1);
        goto skip_event;
      }
      lepton_index = i;
    }

    for(int i = 0; i < event.ElectronTight_size; i++){
      if( event.ElectronTight_PT[i]           < 25.  ) continue; 
      if( abs(event.ElectronTight_Eta[i])     > 2.8  ) continue;
      if( abs(event.ElectronTight_Eta[i]) > 1.4 and abs(event.ElectronTight_Eta[i]) < 1.6) continue; 
      if( event.ElectronTight_IsolationVar[i] > 0.15 ) continue;
      if(lepton_index != -1){ 
        skip_hist->Fill("addition good electron", 1);
        goto skip_event;
      }
      lepton_index = i;
      lepton_is_muon = false;
    }

    if(lepton_index == -1){ 
      skip_hist->Fill("no good muon or electron", 1);
      goto skip_event;
    }

    // Lepton from W
    TLorentzVector lepton;
    double mass;
    if(lepton_is_muon){
      Lepton_Pt  = event.MuonTight_PT[lepton_index];
      Lepton_Phi = event.MuonTight_Phi[lepton_index];
      Lepton_Eta = event.MuonTight_Eta[lepton_index];
      mass = event.MuonTight_Mass[lepton_index];
      Lepton_Type = 1;
    } else {
      Lepton_Pt  = event.ElectronTight_PT[lepton_index];
      Lepton_Phi = event.ElectronTight_Phi[lepton_index];
      Lepton_Eta = event.ElectronTight_Eta[lepton_index];
      mass = event.ElectronTight_Mass[lepton_index];
      Lepton_Type = 0;
    }
    lepton.SetPtEtaPhiM(Lepton_Pt, Lepton_Eta, Lepton_Phi, mass);
    Lepton_Px = lepton.Px();
    Lepton_Py = lepton.Py();
    Lepton_Pz = lepton.Pz();
    Lepton_E  = lepton.E();

    // electron veto
    for(int i = 0; i < event.ElectronLoose_size; i++){
      if( event.ElectronLoose_PT[i]           < 10.  ) continue; 
      if( abs(event.ElectronLoose_Eta[i])     > 2.8  ) continue;
      if( abs(event.ElectronLoose_Eta[i]) > 1.4 and abs(event.ElectronLoose_Eta[i]) < 1.6) continue; 
      if( event.ElectronLoose_IsolationVar[i] > 0.25 ) continue;
      if( not lepton_is_muon and event.ElectronLoose_PT[i] == Lepton_Pt )   continue;
      skip_hist->Fill("loose electron veto", 1);
      goto skip_event;
    }

    for(int i = 0; i < event.ElectronTight_size; i++){
      if( event.ElectronTight_PT[i]           < 10.  ) continue; 
      if( abs(event.ElectronTight_Eta[i])     > 2.8  ) continue;
      if( abs(event.ElectronTight_Eta[i]) > 1.4 and abs(event.ElectronTight_Eta[i]) < 1.6) continue; 
      if( event.ElectronTight_IsolationVar[i] > 0.25 ) continue;
      if( not lepton_is_muon and event.ElectronTight_PT[i] == Lepton_Pt )   continue;
      skip_hist->Fill("delphy tight electron veto", 1);
      goto skip_event;
    }
    // muon veto
    for(int i = 0; i < event.MuonLoose_size; i++){
      if( event.MuonLoose_PT[i]           < 10.  ) continue; 
      if( abs(event.MuonLoose_Eta[i])     > 2.8  ) continue;
      if( event.MuonLoose_IsolationVar[i] > 0.25 ) continue;
      if( lepton_is_muon and event.MuonLoose_PT[i] == Lepton_Pt )   continue;
      skip_hist->Fill("loose muon veto", 1);
      goto skip_event;
    }

    for(int i = 0; i < event.MuonTight_size; i++){
      if( event.MuonTight_PT[i]           < 10.  ) continue; 
      if( abs(event.MuonTight_Eta[i])     > 2.8  ) continue;
      if( event.MuonTight_IsolationVar[i] > 0.25 ) continue;
      if( lepton_is_muon and event.MuonTight_PT[i] == Lepton_Pt )   continue;
      skip_hist->Fill("delphy tight muon veto", 1);
      goto skip_event;
    }

    // aplly JES correction here
    // https://twiki.cern.ch/twiki/bin/view/CMSPublic/WorkBookJetEnergyCorrections?redirectedfrom=CMS.WorkBookJetEnergyCorrections#JetCorUncertainties
    // https://twiki.cern.ch/twiki/bin/view/CMS/UPGAnalysisSystematics
    double JES_uncertantie = 0.01;
    if( is_JES_Up ){
      for(int i = 0; i < event.JetPUPPI_size; i++)
        event.JetPUPPI_PT[i] *= (1. + JES_uncertantie);
    }
    if( is_JES_Down ){
      for(int i = 0; i < event.JetPUPPI_size; i++)
        event.JetPUPPI_PT[i] *= (1. - JES_uncertantie);
    }    


    // two or three jets
    int nJets = 0;
    int jet_index_1 = -1;
    int jet_index_2 = -1;
    int jet_index_3 = -1;
    Jets_SumPt = 0;
    TLorentzVector Jets;
    vector<TLorentzVector> planarity_jets;
    for(int i = 0; i < event.JetPUPPI_size; i++){
      if(event.JetPUPPI_PT[i] < 30) continue;
      if(abs(event.JetPUPPI_Eta[i]) > 4.7) continue;
      double dR2 = pow(event.JetPUPPI_Phi[i] - Lepton_Phi, 2) + pow(event.JetPUPPI_Eta[i] - Lepton_Eta, 2);
      if( dR2 < 0.016 ) continue;

      Jets_SumPt += event.JetPUPPI_PT[i];
      TLorentzVector jet;
      jet.SetPtEtaPhiM(event.JetPUPPI_PT[i], event.JetPUPPI_Eta[i], event.JetPUPPI_Phi[i], event.JetPUPPI_Mass[i]);
      Jets += jet;
      planarity_jets.push_back(jet);
      
      nJets++;
      if(jet_index_1 == -1) jet_index_1 = i;
      else if (jet_index_2 == -1) jet_index_2 = i;
      else if (jet_index_3 == -1) jet_index_3 = i;
    }
    if(nJets != 2 and nJets != 3){
      skip_hist->Fill("not two or three jets", 1);
      goto skip_event;
    }

    vector<int> good_jets = {jet_index_1, jet_index_2};
    if(jet_index_3 != -1)  good_jets.push_back( jet_index_3 );

    // one jet is b-jet
    int nBJets = 0;
    int nNotBJets = 0;
    for(int i = 0; i < good_jets.size(); i++){
      int index = good_jets.at(i);
      if(abs(event.JetPUPPI_Eta[index]) > 1.5){ 
        if(event.JetPUPPI_DeepCSV[index] >= 7) nBJets++; // JetPUPPI_MVAv2
        else if(not event.JetPUPPI_DeepCSV[index]) nNotBJets++;
      } else {
        if(event.JetPUPPI_MVAv2[index] >= 7) nBJets++; // JetPUPPI_MVAv2
        else if(not event.JetPUPPI_MVAv2[index]) nNotBJets++;
      }
    }
    if(not nBJets)    {
      skip_hist->Fill("dont have b jets", 1);
      goto skip_event;
    }
    if(not nNotBJets) {
      skip_hist->Fill("dont have light jets", 1);
      goto skip_event;
    }

    if(not event.PuppiMissingET_size){
      skip_hist->Fill("MET", 1);
      goto skip_event;
    }
    if(event.PuppiMissingET_MET[0] < 30){
      skip_hist->Fill("MET < 30", 1);
      goto skip_event;
    }

    // ====== VARIABLES PARTS ==============================================================================>
    // MET from  W
    TLorentzVector met;
    MET_Pt     = event.PuppiMissingET_MET[0];
    MET_Phi    = event.PuppiMissingET_Phi[0];
    met.SetPtEtaPhiM(MET_Pt, 0, MET_Phi, 0);
    MET_Px = met.Px();
    MET_Py = met.Py();
    // W
    TLorentzVector Wboson = lepton + met;
    W_Pt = Wboson.Pt();
    W_Mt = Wboson.Mt();
    // bJet
    int bJetBest_index = -1;
    double massDelta = 99999;
    TLorentzVector bJetBest;
    for(int i = 0; i < good_jets.size(); i++){
      int index = good_jets.at(i);
      if(abs(event.JetPUPPI_Eta[index]) > 1.5 and event.JetPUPPI_DeepCSV[index] < 7) continue;
      if(abs(event.JetPUPPI_Eta[index]) < 1.5 and event.JetPUPPI_MVAv2[index]   < 7) continue;
      TLorentzVector jetCandidate;
      jetCandidate.SetPtEtaPhiM(event.JetPUPPI_PT[index], event.JetPUPPI_Eta[index], event.JetPUPPI_Phi[index], event.JetPUPPI_Mass[index]);
      double massDeltaCandidat = fabs((Wboson + jetCandidate).M() - 172.5);
	    if(massDeltaCandidat < massDelta){
        bJetBest = jetCandidate;
        bJetBest_index = index;
        massDelta = massDeltaCandidat;
      }
    }

    bJet_Pt    = event.JetPUPPI_PT[bJetBest_index];
    bJet_Phi   = event.JetPUPPI_Phi[bJetBest_index];
    bJet_Eta   = event.JetPUPPI_Eta[bJetBest_index];
    Jets_SumPt_minus_bJet_Pt = Jets_SumPt - bJet_Pt;
    Jets_M_without_bJet      = (Jets - bJetBest).M();
    JetsW_M                  = (Jets + Wboson).M();
    Jets_N                   = good_jets.size();
    // top
    TLorentzVector top = bJetBest + Wboson;
    //cout << "MET"; met.Print();
    //cout << "mu"; lepton.Print();
    //cout << "W"; Wboson.Print();
    //cout << "b"; bJetBest.Print();
    //cout << "t"; top.Print();
    t_Pt       = top.Pt();
    t_Phi      = top.Phi();
    t_Eta      = top.Eta();
    t_M        = top.M();
    // light jet - not btagged and with biggest eta
    int lightJet_index = -1;
    double lightJet_eta = 0;
    TLorentzVector lightJet;
    for(int i = 0; i < good_jets.size(); i++){
      int index = good_jets.at(i);
      if(abs(event.JetPUPPI_Eta[index]) > 1.5 and event.JetPUPPI_DeepCSV[index] >= 7) continue;
      if(abs(event.JetPUPPI_Eta[index]) < 1.5 and event.JetPUPPI_MVAv2[index]   >= 7) continue;
      TLorentzVector jetCandidate;
      jetCandidate.SetPtEtaPhiM(event.JetPUPPI_PT[index], event.JetPUPPI_Eta[index], event.JetPUPPI_Phi[index], event.JetPUPPI_Mass[index]);
      if(abs(lightJet_eta) < abs(event.JetPUPPI_Eta[index])){
        lightJet = jetCandidate;
        lightJet_index = index;
        lightJet_eta   = event.JetPUPPI_Eta[index];
      }
    }

    LightJet_Pt  = event.JetPUPPI_PT[lightJet_index];
    LightJet_Phi = event.JetPUPPI_Phi[lightJet_index];
    LightJet_Eta = event.JetPUPPI_Eta[lightJet_index];

    bJetLepton_Mass = (bJetBest + lepton).M();     // <---- invariant mass of lepton and bjet
    bJetLepton_Pt   = (bJetBest + lepton).Pt();    // <---- vector sum of pt for b jet and lepton
    bJetTop_dPhi    = bJetBest.DeltaPhi( top );    // <---- difference in azimuth angle between top and b jet
    bJetW_dPhi      = bJetBest.DeltaPhi( Wboson ); // <---- difference in azimuth angle between W boson and b jet
    bJetTop_dEta    = top.Eta() - bJetBest.Eta();  // <---- difference in eta of top and b jet

    // leading jet, second jet
    TLorentzVector leadingJet, secondJet;
    for(int i = 0; i < good_jets.size(); i++){
      int index = good_jets.at(i);
      TLorentzVector jetCandidate;
      jetCandidate.SetPtEtaPhiM(event.JetPUPPI_PT[index], event.JetPUPPI_Eta[index], event.JetPUPPI_Phi[index], event.JetPUPPI_Mass[index]);
      double massDeltaCandidat = fabs((Wboson + jetCandidate).M() - 172.5);
	    if(leadingJet.Pt() < jetCandidate.Pt()){
        secondJet  = leadingJet;
        leadingJet = jetCandidate;
        continue;
      }
      if(secondJet.Pt() < jetCandidate.Pt())
        secondJet  = jetCandidate;
    }

    LeadingJet_Pt = leadingJet.Pt();
    LeadingJet_Px = leadingJet.Px();
    LeadingJet_Py = leadingJet.Py();
    LeadingJet_Pz = leadingJet.Pz();
    LeadingJet_E  = leadingJet.E();

    SecondJet_Pt = secondJet.Pt();
    SecondJet_Px = secondJet.Px();
    SecondJet_Py = secondJet.Py();
    SecondJet_Pz = secondJet.Pz();
    SecondJet_E  = secondJet.E();

    LeadingJetSecondJet_Pt = (leadingJet + secondJet).Pt();
    LeadingJetSecondJet_M  = (leadingJet + secondJet).M();
    LeadingJetSecondJet_dR = leadingJet.DeltaR( secondJet );

    // tricky cosinuses
    TLorentzVector lepton_boosted = lepton;
    lepton_boosted.Boost(-top.BoostVector());
    TLorentzVector lightJet_boosted = lightJet;
    lightJet_boosted.Boost(-top.BoostVector());
    cos_lightJetLepton_tsystem = lepton_boosted.Vect().Dot(lightJet_boosted.Vect()) / (lightJet_boosted.Vect().Mag() * lepton_boosted.Vect().Mag());

    TLorentzVector W_boosted = Wboson;
    W_boosted.Boost(-top.BoostVector());
    cos_lightJetW_tsystem = W_boosted.Vect().Dot(lightJet_boosted.Vect()) / (W_boosted.Vect().Mag() * lightJet_boosted.Vect().Mag());

    lepton_boosted = lepton;
    lepton_boosted.Boost(-Wboson.BoostVector());
    cos_leptonW_Wsystem = lepton_boosted.Vect().Dot(Wboson.Vect()) / (lepton_boosted.Vect().Mag() * Wboson.Vect().Mag());

    // Sphericity, Planarity, Aplanarity
    TVector3 Wboson_vec3 = Wboson.Vect();
    double norm =  Wboson_vec3.Mag2();
    TMatrixDSym sphericityTensor(3);

    for(unsigned i = 0; i < 3; ++i){
	    for (unsigned j = 0; j < 3; ++j){
	      sphericityTensor(i, j) = Wboson_vec3[i] * Wboson_vec3[j];
      }
    }
    
    for(int k = 0; k < planarity_jets.size(); k++){
	    auto p3 = planarity_jets.at(k).Vect();
	    norm += p3.Mag2();
	    for (unsigned i = 0; i < 3; ++i){
	      for (unsigned j = 0; j < 3; ++j){
	        sphericityTensor(i, j) += p3[i] * p3[j];
        }
      }
    }
    
    sphericityTensor *= 1. / norm;
    
    TMatrixDSymEigen eigenValCalc(sphericityTensor);
    TVectorD eigenVals(eigenValCalc.GetEigenValues());
    Sphericity = 1.5 * (eigenVals[1] + eigenVals[2]);
    Aplanarity = 1.5 * eigenVals[2];
    Planarity  = eigenVals[1] - eigenVals[2];

    // weight NOMINAL weight from generator
    weight = event.Weight[0] * dataset_weight_new;
    weight_old = event.Weight[0] * dataset_weight_old;
    weight_MC_nominal = event.Weight[0];

    // https://indico.cern.ch/event/402279/contributions/960421/attachments/805964/1104514/mcaod-Jun17-2015.pdf
    // https://indico.cern.ch/event/494682/contributions/1172505/attachments/1223578/1800218/mcaod-Feb15-2016.pdf#search=GenEventInfoProduct
    // https://indico.cern.ch/event/555805/contributions/2287180/attachments/1328032/1994393/2016_08_29__Sherpa_Tutorial__Sherpa_in_CMSSW.pdf#search=GenEventInfoProduct
    if(event.Weight_size > 110){
      /*
        109 2101 0.30668
        110 2102 0.354809
      */
      weight_MC_alpha_s_Up   = event.Weight[109], 
      weight_MC_alpha_s_Down = event.Weight[110];
    }
    if(event.Weight_size > 15){
      /*
        1 1002 0.317413
        2 1003 0.349413
        3 1004 0.307874
        4 1005 0.291439
        5 1006 0.325689
        6 1007 0.362628
        7 1008 0.348633
        8 1009 0.376956
      */
      for(int i = 0; i <= 15; i++)
        weight_MC_RF[i] = event.Weight[i];
    }
    
    // btag uncertanties weights
    // https://twiki.cern.ch/twiki/bin/view/CMSPublic/BtagRecommendation2010OpenData#Data_MC_Scale_Factors
    // https://twiki.cern.ch/twiki/bin/view/CMS/UPGAnalysisSystematics
    // https://twiki.cern.ch/twiki/bin/view/CMSPublic/BTV13TeVDPDeepCSV
    // Efficinces from https://twiki.cern.ch/twiki/bin/view/CMS/Phase2MuonBarrelRecipes#B_tagging
    // Tight working point P(btag_jet != b_jet) == 0.01
  
    for(int i = 0; i < good_jets.size(); i++){
      int index = good_jets.at(i);
      int true_flavor = JetPUPPI_HadronFlavor[index];
      bool btag = false;

      if(abs(event.JetPUPPI_Eta[index]) > 1.5 and event.JetPUPPI_DeepCSV[index] >= 7) btag = true;
      if(abs(event.JetPUPPI_Eta[index]) < 1.5 and event.JetPUPPI_MVAv2[index]   >= 7) btag = true;

      if() // for(int i = 0; i < good_jets.size(); i++){
      int index = good_jets.at(i);
    }
    
    double btag_uncertantie_b = 0.01;
    double btag_uncertantie_c = 0.02;
    double btag_uncertantie_l = 0.10;
    weight_btagUp   = pow((1+btag_uncertantie), nBJets) * pow((1-btag_uncertantie), nNotBJets);
    weight_btagDown = pow((1-btag_uncertantie), nBJets) * pow((1+btag_uncertantie), nNotBJets);

    // other information
    muon_chanel     += lepton_is_muon;
    electron_chanel += not lepton_is_muon;

    tree->Fill();
  }

  cout << " end loop ... " << nevents-event_skiped << "/" << nevents << " events passed" << endl;
  cout << " muon_chanel / electron_chanel ... " << muon_chanel << "/" << electron_chanel << endl;
  for(int i = 1; i <= skip_hist->GetNbinsX(); i++){
    if(skip_hist->GetBinContent(i) == 0) break;
    cout << "  " << skip_hist->GetXaxis()->GetBinLabel(i) << " " << skip_hist->GetBinContent(i) << endl;
  }

  file_out->cd();
  tree->Write();
  skip_hist->Write();
  file_out->Close();
  file->Close();
  return 0;
}

inline bool exists_test(const std::string& name) {
    if (FILE *file = fopen(name.c_str(), "r")) {
        fclose(file);
        return true;
    } else {
        return false;
    }   
}

void process_datasets(string path, vector<string> dataset_names, double lumi, double xsec, string out_path, string systemactic_mode){
  cout << "\n\n\nprocess_datasets() ... begin" << endl;
  vector<string> files;
  vector<string> result_names;
  Long64_t nevents_total = 0;
  long double sum_of_weights = 0;
  
  for(string dataset_name : dataset_names){
    cout << " dataset " << dataset_name << endl;
    for(int i = 0; i < 100; i++){
      string file_name = path + "/" + dataset_name + "_part" + to_string(i) + ".root";
      if(not exists_test( file_name ) ) break;
      TFile * f = TFile::Open( file_name.c_str() );
      if(not f) break;
      TTree * tree = (TTree*)f->Get("ntuple/Event");
      if(not tree) cout << "cant find tree \"ntuple/Event\"!!!" << endl;
      cout << "   add " << file_name << " with "<< tree->GetEntries() << " events" << endl;
      Long64_t nevents = tree->GetEntries();
      nevents_total   += nevents;

      Float_t Weight[500];
      tree->SetBranchAddress("Weight", Weight);
      for(Long64_t nevent = 0; nevent < nevents; nevent++){
        tree->GetEntry( nevent );
        sum_of_weights += Weight[0];
      }

      files.push_back( file_name );
      result_names.push_back( "hzura_" + dataset_name + "_part" + to_string(i) + ".root" );
      f->Close();
    }
  }

  // https://indico.cern.ch/event/402279/contributions/960421/attachments/805964/1104514/mcaod-Jun17-2015.pdf
  // https://indico.cern.ch/event/494682/contributions/1172505/attachments/1223578/1800218/mcaod-Feb15-2016.pdf#search=GenEventInfoProduct
  // https://indico.cern.ch/event/555805/contributions/2287180/attachments/1328032/1994393/2016_08_29__Sherpa_Tutorial__Sherpa_in_CMSSW.pdf#search=GenEventInfoProduct
  double dataset_weight_old = lumi / nevents_total * xsec;
  double dataset_weight_new = lumi / sum_of_weights * xsec;
  cout << " MC events number " << nevents_total << endl;
  cout << " Expected events number " << (long long int)(lumi * xsec) << " for lumi " << lumi << "pb-1" <<  endl;
  cout << " dataset_weight old = " << (long long int)dataset_weight_old << " " << nevents_total  << endl;
  cout << " dataset_weight new = " << (long long int)dataset_weight_new << " " << sum_of_weights << endl;

  if(files.size() == 0) cout << "\n CANT FIND FILES FOR THIS DATASET  !!!!!!!!!!! " << endl << endl << endl;

  for(int i = 0; i < files.size(); i++){
    string file_name = files.at(i);
    string out_name  = result_names.at(i);
    analyse_single_file(file_name.c_str(), out_path + "/" + out_name, 0, dataset_weight_old, dataset_weight_new, systemactic_mode);
    cout << "   " << file_name << " finished!" << endl;
  }
  cout << "process_datasets() ... end" << endl;
}

vector<pair< vector<string>, double> > prepare_dataset_list(vector<string> names, double xsec){
  vector<pair< vector<string>, double> > answer;
  answer.push_back( make_pair(names, xsec) );
  return answer;
}

template<typename... Args> vector<pair< vector<string>, double> > prepare_dataset_list(vector<string> names, double xsec, Args... args){
  vector<pair< vector<string>, double> > answer = prepare_dataset_list(args...);
  answer.push_back( make_pair(names, xsec) );
  return answer;
}

int analyse(){
  if(false){
    analyse_single_file("p2ntuple_kc_0.root",       "huisura_1.root", 100);
    analyse_single_file("MiniEvents_1_ST_tch.root", "huisura_2.root", 100);
    analyse_single_file("MiniEvents_1_TT.root",     "huisura_3.root", 100);
    // check_tree("MiniEvents_1_ST_tch.root");
    return 0;
  }

  double lumi = 3000*1000; // pb-1

  string systemactic_mode = "JES_Down";
  systemactic_mode = "";
  string samples_out_path = "hzura_jan_11";
  string samples_path;

  if(true){
    vector<pair< vector<string>, double> > datasets = prepare_dataset_list(
      vector<string>({"crab_dec_24_v2_8_QCD_Flat_P_v2_ext1-v1",  "crab_dec_24_v2_9_QCD_Flat_P_stic_v2-v2" }),      2.191 * pow(10, 9),      // 2.191e+09 pb
      vector<string>({"crab_dec_24_v2_1_DYToLL-M-5_stic_v2-v2",  "crab_dec_24_v2_2_DYToLL-M-5_v2_ext1-v1" }),      3668,
      vector<string>({"crab_dec_24_v2_3_DYToLL-M-5_stic_v2-v2",  "crab_dec_24_v2_4_DYToLL-M-5_v2_ext1-v1" }),      1094,
      vector<string>({"crab_dec_24_v2_5_DYToLL-M-5_stic_v2-v2",  "crab_dec_24_v2_6_DYToLL-M-5_v2_ext1-v1" }),      369.7,
      vector<string>({"crab_dec_24_v2_7_DYToLL-M-5_stic_v2-v1"                                            }),      190.2,
      vector<string>({"crab_dec_24_v2_10_ST_tch_14T_stic_v2-v2", "crab_dec_24_v2_11_ST_tch_14T_v2_ext1-v2"}),      93.28,                   // 93.28 pb
      vector<string>({"crab_dec_24_v2_12_ST_tch_14T_stic_v2-v2", "crab_dec_24_v2_13_ST_tch_14T_v2_ext1-v1"}),      154.76,
      vector<string>({"crab_dec_24_v2_16_ZZTo2Q2L_1_stic_v2-v2", "crab_dec_24_v2_17_ZZTo2Q2L_1_v2_ext1-v1"}),      2.214,
      vector<string>({"crab_dec_24_v2_18_ZZTo4L_14T_stic_v2-v1"                                           }),      1.357,
      vector<string>({"crab_dec_24_v2_19_WToLNu_0J__stic_v2-v2", "crab_dec_24_v2_20_WToLNu_0J__v2_ext1-v1"}),      38870,
      vector<string>({"crab_dec_24_v2_21_WToLNu_1J__stic_v2-v2"                                           }),      10330,
      vector<string>({"crab_dec_24_v2_22_WToLNu_2J__stic_v2-v2", "crab_dec_24_v2_23_WToLNu_2J__v2_ext1-v1"}),      3314,
      vector<string>({"crab_dec_24_v2_24_WToLNu_3J__stic_v2-v2", "crab_dec_24_v2_25_WToLNu_3J__v2_ext1-v1"}),      1891,
      vector<string>({"crab_dec_24_v2_26_ST_tW_DR_1_stic_v2-v2", "crab_dec_24_v2_27_ST_tW_DR_1_v2_ext1-v1"}),      42.2,
      vector<string>({"crab_dec_24_v2_28_ST_tW_DR_1_stic_v2-v2", "crab_dec_24_v2_29_ST_tW_DR_1_v2_ext1-v1"}),      42.2,
      vector<string>({"crab_dec_24_v2_14_TT_TuneCUE_stic_v2-v3", "crab_dec_24_v2_15_TT_TuneCUE_v2_ext1-v1"}),      864.4
      // "crab_dec_24_v2_0_DYJetsToLL_v2_ext1-v1",        1,
    );
    samples_path     = "/scratch/pmandrik/TDR_samples/dec_24";
    samples_path     = "/eos/user/p/pmandrik/lsf_delphy_samples/tgs_samples/dec_24";
    for(auto item : datasets){
      process_datasets(samples_path, item.first, lumi, item.second, samples_out_path, systemactic_mode);
    }
  }

  if(true){
    vector<pair< vector<string>, double> > datasets = prepare_dataset_list(
      vector<string>({"crab_jan_1_ST_tch_14TeV_antitop_incl-powheg-pythia8-madspin_ext1-v2"}),      93.28,
      vector<string>({"crab_jan_1_WToLNu_1J_14TeV-madgraphMLM-pythia8_v2-v2"}),                     10330,
      vector<string>({"crab_jan_1_WToLNu_3J_14TeV-madgraphMLM-pythia8_v2-v2"}),                      1891,
      vector<string>({"crab_jan_1_WZTo3LNu_0Jets_14TeV-madgraphMLM-pythia8_v2-v2"}),                 3.11,
      vector<string>({"crab_jan_1_WZTo3LNu_1Jets_14TeV-madgraphMLM-pythia8_v2-v2"}),                0.954,
      vector<string>({"crab_jan_1_WZTo3LNu_2Jets_14TeV-madgraphMLM-pythia8_v2-v2"}),                0.274,
      vector<string>({"crab_jan_1_WZTo3LNu_2Jets_14TeV-madgraphMLM-pythia8_ext1-v2"}),              0.274,
      vector<string>({"crab_jan_12_v3_tGluon_FCNC_tGu_14TeV_CompHEP_v2-v1" }),                      156.3
    );

    samples_path     = "/eos/user/p/pmandrik/lsf_delphy_samples/tgs_samples/jan_03";
    for(auto item : datasets){
      process_datasets(samples_path, item.first, lumi, item.second, samples_out_path, systemactic_mode);
    }
  }

  if(true){
    vector<pair< vector<string>, double> > datasets = prepare_dataset_list(
      vector<string>({"result_kc" }),      30,      // 2.191e+09 pb
      vector<string>({"result_ku" }),     156.3
    );

    samples_path = "/afs/cern.ch/work/p/pmandrik/tdr_tqgamma/mensura/";
    samples_path = "/eos/user/p/pmandrik/lsf_delphy_samples/kc_results_new/after_ntupler/";
    for(auto item : datasets){
      process_datasets(samples_path, item.first, lumi, item.second, samples_out_path, systemactic_mode);
    }
  }

  return 0;
};

/*
crab_dec_24_v2_8_QCD_Flat_P_v2_ext1-v1 /QCD_Flat_Pt-15to7000_TuneCUETP8M1_14TeV_pythia8/PhaseIITDRFall17MiniAOD-PU200FEVT_93X_upgrade2023_realistic_v2_ext1-v1/MINIAODSIM
crab_dec_24_v2_9_QCD_Flat_P_stic_v2-v2 /QCD_Flat_Pt-15to7000_TuneCUETP8M1_14TeV_pythia8/PhaseIITDRFall17MiniAOD-PU200_93X_upgrade2023_realistic_v2-v2/MINIAODSIM
crab_dec_24_v2_0_DYJetsToLL_v2_ext1-v1 /DYJetsToLL_M-10to50_TuneCUETP8M1_14TeV-madgraphMLM-pythia8/PhaseIITDRFall17MiniAOD-PU200_93X_upgrade2023_realistic_v2_ext1-v1/MINIAODSIM
crab_dec_24_v2_1_DYToLL-M-5_stic_v2-v2 /DYToLL-M-50_0J_14TeV-madgraphMLM-pythia8/PhaseIITDRFall17MiniAOD-PU200_93X_upgrade2023_realistic_v2-v2/MINIAODSIM
crab_dec_24_v2_2_DYToLL-M-5_v2_ext1-v1 /DYToLL-M-50_0J_14TeV-madgraphMLM-pythia8/PhaseIITDRFall17MiniAOD-PU200_93X_upgrade2023_realistic_v2_ext1-v1/MINIAODSIM
crab_dec_24_v2_3_DYToLL-M-5_stic_v2-v2 /DYToLL-M-50_1J_14TeV-madgraphMLM-pythia8/PhaseIITDRFall17MiniAOD-PU200_93X_upgrade2023_realistic_v2-v2/MINIAODSIM
crab_dec_24_v2_4_DYToLL-M-5_v2_ext1-v1 /DYToLL-M-50_1J_14TeV-madgraphMLM-pythia8/PhaseIITDRFall17MiniAOD-PU200_93X_upgrade2023_realistic_v2_ext1-v1/MINIAODSIM
crab_dec_24_v2_5_DYToLL-M-5_stic_v2-v2 /DYToLL-M-50_2J_14TeV-madgraphMLM-pythia8/PhaseIITDRFall17MiniAOD-PU200_93X_upgrade2023_realistic_v2-v2/MINIAODSIM
crab_dec_24_v2_6_DYToLL-M-5_v2_ext1-v1 /DYToLL-M-50_2J_14TeV-madgraphMLM-pythia8/PhaseIITDRFall17MiniAOD-PU200_93X_upgrade2023_realistic_v2_ext1-v1/MINIAODSIM
crab_dec_24_v2_7_DYToLL-M-5_stic_v2-v1 /DYToLL-M-50_3J_14TeV-madgraphMLM-pythia8/PhaseIITDRFall17MiniAOD-PU200_93X_upgrade2023_realistic_v2-v1/MINIAODSIM
crab_dec_24_v2_10_ST_tch_14T_stic_v2-v2 /ST_tch_14TeV_antitop_incl-powheg-pythia8-madspin/PhaseIITDRFall17MiniAOD-PU200_93X_upgrade2023_realistic_v2-v2/MINIAODSIM
crab_dec_24_v2_11_ST_tch_14T_v2_ext1-v2 /ST_tch_14TeV_antitop_incl-powheg-pythia8-madspin/PhaseIITDRFall17MiniAOD-PU200_93X_upgrade2023_realistic_v2_ext1-v2/MINIAODSIM
crab_dec_24_v2_12_ST_tch_14T_stic_v2-v2 /ST_tch_14TeV_top_incl-powheg-pythia8-madspin/PhaseIITDRFall17MiniAOD-PU200_93X_upgrade2023_realistic_v2-v2/MINIAODSIM
crab_dec_24_v2_13_ST_tch_14T_v2_ext1-v1 /ST_tch_14TeV_top_incl-powheg-pythia8-madspin/PhaseIITDRFall17MiniAOD-PU200_93X_upgrade2023_realistic_v2_ext1-v1/MINIAODSIM
crab_dec_24_v2_14_TT_TuneCUE_stic_v2-v3 /TT_TuneCUETP8M2T4_14TeV-powheg-pythia8/PhaseIITDRFall17MiniAOD-PU200_93X_upgrade2023_realistic_v2-v3/MINIAODSIM
crab_dec_24_v2_15_TT_TuneCUE_v2_ext1-v1 /TT_TuneCUETP8M2T4_14TeV-powheg-pythia8/PhaseIITDRFall17MiniAOD-PU200_93X_upgrade2023_realistic_v2_ext1-v1/MINIAODSIM
crab_dec_24_v2_16_ZZTo2Q2L_1_stic_v2-v2 /ZZTo2Q2L_14TeV_powheg_pythia8/PhaseIITDRFall17MiniAOD-PU200_93X_upgrade2023_realistic_v2-v2/MINIAODSIM
crab_dec_24_v2_17_ZZTo2Q2L_1_v2_ext1-v1 /ZZTo2Q2L_14TeV_powheg_pythia8/PhaseIITDRFall17MiniAOD-PU200_93X_upgrade2023_realistic_v2_ext1-v1/MINIAODSIM
crab_dec_24_v2_18_ZZTo4L_14T_stic_v2-v1 /ZZTo4L_14TeV_powheg_pythia8_v2/PhaseIITDRFall17MiniAOD-PU200_93X_upgrade2023_realistic_v2-v1/MINIAODSIM
crab_dec_24_v2_19_WToLNu_0J__stic_v2-v2 /WToLNu_0J_14TeV-madgraphMLM-pythia8/PhaseIITDRFall17MiniAOD-PU200_93X_upgrade2023_realistic_v2-v2/MINIAODSIM
crab_dec_24_v2_20_WToLNu_0J__v2_ext1-v1 /WToLNu_0J_14TeV-madgraphMLM-pythia8/PhaseIITDRFall17MiniAOD-PU200_93X_upgrade2023_realistic_v2_ext1-v1/MINIAODSIM
crab_dec_24_v2_21_WToLNu_1J__stic_v2-v2 /WToLNu_1J_14TeV-madgraphMLM-pythia8/PhaseIITDRFall17MiniAOD-PU200_93X_upgrade2023_realistic_v2-v2/MINIAODSIM
crab_dec_24_v2_22_WToLNu_2J__stic_v2-v2 /WToLNu_2J_14TeV-madgraphMLM-pythia8/PhaseIITDRFall17MiniAOD-PU200_93X_upgrade2023_realistic_v2-v2/MINIAODSIM
crab_dec_24_v2_23_WToLNu_2J__v2_ext1-v1 /WToLNu_2J_14TeV-madgraphMLM-pythia8/PhaseIITDRFall17MiniAOD-PU200_93X_upgrade2023_realistic_v2_ext1-v1/MINIAODSIM
crab_dec_24_v2_24_WToLNu_3J__stic_v2-v2 /WToLNu_3J_14TeV-madgraphMLM-pythia8/PhaseIITDRFall17MiniAOD-PU200_93X_upgrade2023_realistic_v2-v2/MINIAODSIM
crab_dec_24_v2_25_WToLNu_3J__v2_ext1-v1 /WToLNu_3J_14TeV-madgraphMLM-pythia8/PhaseIITDRFall17MiniAOD-PU200_93X_upgrade2023_realistic_v2_ext1-v1/MINIAODSIM
crab_dec_24_v2_26_ST_tW_DR_1_stic_v2-v2 /ST_tW_DR_14TeV_antitop_incl-powheg-pythia8/PhaseIITDRFall17MiniAOD-PU200_93X_upgrade2023_realistic_v2-v2/MINIAODSIM
crab_dec_24_v2_27_ST_tW_DR_1_v2_ext1-v1 /ST_tW_DR_14TeV_antitop_incl-powheg-pythia8/PhaseIITDRFall17MiniAOD-PU200_93X_upgrade2023_realistic_v2_ext1-v1/MINIAODSIM
crab_dec_24_v2_28_ST_tW_DR_1_stic_v2-v2 /ST_tW_DR_14TeV_top_incl-powheg-pythia8/PhaseIITDRFall17MiniAOD-PU200_93X_upgrade2023_realistic_v2-v2/MINIAODSIM
crab_dec_24_v2_29_ST_tW_DR_1_v2_ext1-v1 /ST_tW_DR_14TeV_top_incl-powheg-pythia8/PhaseIITDRFall17MiniAOD-PU200_93X_upgrade2023_realistic_v2_ext1-v1/MINIAODSIM

crab_jan_1_ST_tch_14TeV_antitop_incl-powheg-pythia8-madspin_ext1-v2  /ST_tch_14TeV_antitop_incl-powheg-pythia8-madspin/PhaseIITDRFall17MiniAOD-PU200_93X_upgrade2023_realistic_v2_ext1-v2/MINIAODSIM
crab_jan_1_WToLNu_1J_14TeV-madgraphMLM-pythia8_v2-v2                 /WToLNu_1J_14TeV-madgraphMLM-pythia8/PhaseIITDRFall17MiniAOD-PU200_93X_upgrade2023_realistic_v2-v2/MINIAODSIM
crab_jan_1_WToLNu_3J_14TeV-madgraphMLM-pythia8_v2-v2                 /WToLNu_3J_14TeV-madgraphMLM-pythia8/PhaseIITDRFall17MiniAOD-PU200_93X_upgrade2023_realistic_v2-v2/MINIAODSIM
crab_jan_1_WZTo3LNu_0Jets_14TeV-madgraphMLM-pythia8_v2-v2            /WZTo3LNu_0Jets_14TeV-madgraphMLM-pythia8/PhaseIITDRFall17MiniAOD-PU200_93X_upgrade2023_realistic_v2-v2/MINIAODSIM
crab_jan_1_WZTo3LNu_1Jets_14TeV-madgraphMLM-pythia8_v2-v2            /WZTo3LNu_1Jets_14TeV-madgraphMLM-pythia8/PhaseIITDRFall17MiniAOD-PU200_93X_upgrade2023_realistic_v2-v2/MINIAODSIM
crab_jan_1_WZTo3LNu_2Jets_14TeV-madgraphMLM-pythia8_ext1-v2          /WZTo3LNu_2Jets_14TeV-madgraphMLM-pythia8/PhaseIITDRFall17MiniAOD-PU200_93X_upgrade2023_realistic_v2-v2/MINIAODSIM
crab_jan_1_WZTo3LNu_2Jets_14TeV-madgraphMLM-pythia8_v2-v2            /WZTo3LNu_2Jets_14TeV-madgraphMLM-pythia8/PhaseIITDRFall17MiniAOD-PU200_93X_upgrade2023_realistic_v2_ext1-v2/MINIAODSIM

*/


















