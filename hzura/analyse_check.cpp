
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

  TFile * file = TFile::Open( inp_name.c_str() );
  if(not file){
    cout << " Can't open input file ... " << endl;
  }
  tqgamma_Event event;
  event.Init(file);
  Long64_t nevents = event.fChain_Event->GetEntries();
  event.GetEntry( 0 );

  if(max_events) nevents = TMath::Min(max_events, nevents);

  cout << " begin loop ... " << endl;
  Long64_t event_skiped = 0;
  Long64_t muon_chanel = 0, electron_chanel = 0;
  file->cd();

  double b_jets = 0;
  double c_jets = 0;
  double l_jets = 0;

  double btag_b_jets = 0;
  double btag_c_jets = 0;
  double btag_l_jets = 0;
  for(Long64_t nevent = 0; nevent < nevents; nevent++){
    event.GetEntry( nevent );
    if(false){
      skip_event:;
      event_skiped++;
      continue;
    }

    for(int index = 0; index < event.JetPUPPI_size; index++){
      int true_flavor = event.JetPUPPI_HadronFlavor[index];
      if(true_flavor < 0 or true_flavor > 6)
        cout << true_flavor << endl;

      bool btag = false;
      if(abs(event.JetPUPPI_Eta[index]) > 1.5 and event.JetPUPPI_DeepCSV[index] >= 7) btag = true;
      if(abs(event.JetPUPPI_Eta[index]) < 1.5 and event.JetPUPPI_MVAv2[index]   >= 7) btag = true;

      if(true_flavor == 5){
        b_jets += 1;
        if(btag) btag_b_jets += 1;
      }

      if(true_flavor == 4){
        c_jets += 1;
        if(btag) btag_c_jets += 1;
      }

      if(true_flavor < 4){
        l_jets      += 1.;
        if(btag) btag_l_jets += 1;
      }
    }

    //for(int i = 0; i < 20; i++){
    //  cout << event.Weight[i] << " ";
    //}
  }

  cout << btag_b_jets << " " << b_jets << " " << btag_b_jets / b_jets << endl;
  cout << btag_c_jets << " " << c_jets << " " << btag_c_jets / c_jets << endl;
  cout << btag_l_jets << " " << l_jets << " " << btag_l_jets / l_jets << endl;

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

int analyse_check(){
  double lumi = 3000*1000; // pb-1

  string systemactic_mode = "";
  string samples_out_path = "";
  string samples_path;

  if(true){
    vector<pair< vector<string>, double> > datasets = prepare_dataset_list(
/*
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
*/
      vector<string>({"crab_jan_16_v1_WToLNu_1J_14TeV-madgraphMLM-pythia8_ext1-v3"}),      864.4
    );
    samples_path     = "/scratch/pmandrik/TDR_samples/dec_24";
    samples_path     = "/eos/user/p/pmandrik/lsf_delphy_samples/tgs_samples/jan_03";
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


















