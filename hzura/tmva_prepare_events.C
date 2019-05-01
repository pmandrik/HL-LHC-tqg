

#include "/afs/cern.ch/user/p/pmandrik/public/global_cfg/mRoot.cpp"
#include "/afs/cern.ch/user/p/pmandrik/public/global_cfg/mRootStackDrawer.cpp"

using namespace mRoot;

inline bool exists_test(const std::string& name) {
    if (FILE *file = fopen(name.c_str(), "r")) {
        fclose(file);
        return true;
    } else {
        return false;
    }   
}

struct chanal_data{
  string physic_name;
  vector<string> file_names;
  bool signal;
  int nevents;
  double weight_sum;
};

chanal_data get_chanal(string physic_name, string input_path, vector<string> dataset_names, bool signal = false){
  vector<string> file_names;
  int nevents = 0;
  double sum_of_weights = 0;
  for(string dataset_name : dataset_names){
    int datast_n_files = 0;
    for(int i = 0; i < 10; i++){
      string file_name = input_path + "/hzura_" + dataset_name + "_part" + to_string(i) + ".root";
      if(not exists_test( file_name ) ) continue;
      file_names.push_back( file_name );

      TFile * f = TFile::Open( file_name.c_str() );
      TTree * tree = (TTree*)gDirectory->Get("ttree");
      nevents += tree->GetEntries();

      float weight;
      tree->SetBranchAddress("weight", &weight);
      int nevents_tree = tree->GetEntries();
      for(Long64_t nevent = 0; nevent < nevents_tree; nevent++){
        tree->GetEntry( nevent );
        sum_of_weights += weight;
      }

      f->Close();
      datast_n_files++;
    }
    if( datast_n_files == 0)
      cout << "CANT FIND ANY FILES FOR THIS DATASET " << dataset_name << endl;
  }

  chanal_data cd;
  cd.file_names  = file_names;
  cd.physic_name = physic_name;
  cd.signal = signal;
  cd.nevents = nevents;
  cd.weight_sum = sum_of_weights;
  return cd;
}

vector<chanal_data> get_current_channals(string input_path){
   vector<chanal_data> chanal_datas = {
      get_chanal("tcg",         input_path,     {"result_kc"},  true),
      get_chanal("tug",         input_path,     {"result_ku"},  true),
      get_chanal("TT",          input_path,     {"crab_dec_24_v2_14_TT_TuneCUE_stic_v2-v3", "crab_dec_24_v2_15_TT_TuneCUE_v2_ext1-v1"}),
      get_chanal("Wjets",       input_path,     {"crab_dec_24_v2_19_WToLNu_0J__stic_v2-v2", "crab_dec_24_v2_20_WToLNu_0J__v2_ext1-v1",
                                                 "crab_jan_1_WToLNu_1J_14TeV-madgraphMLM-pythia8_v2-v2", 
                                                 "crab_dec_24_v2_22_WToLNu_2J__stic_v2-v2","crab_dec_24_v2_23_WToLNu_2J__v2_ext1-v1",
                                                 "crab_jan_1_WToLNu_3J_14TeV-madgraphMLM-pythia8_v2-v2","crab_dec_24_v2_25_WToLNu_3J__v2_ext1-v1"}),
      get_chanal("ST",          input_path,     {"crab_dec_24_v2_10_ST_tch_14T_stic_v2-v2", "crab_jan_1_ST_tch_14TeV_antitop_incl-powheg-pythia8-madspin_ext1-v2",
                                                 "crab_dec_24_v2_12_ST_tch_14T_stic_v2-v2", "crab_dec_24_v2_13_ST_tch_14T_v2_ext1-v1"}),
      get_chanal("tW",          input_path,     {"crab_dec_24_v2_26_ST_tW_DR_1_stic_v2-v2", "crab_dec_24_v2_27_ST_tW_DR_1_v2_ext1-v1",
                                                 "crab_dec_24_v2_28_ST_tW_DR_1_stic_v2-v2", "crab_dec_24_v2_29_ST_tW_DR_1_v2_ext1-v1"}),
      get_chanal("DY",          input_path,     {"crab_dec_24_v2_1_DYToLL-M-5_stic_v2-v2",  "crab_dec_24_v2_2_DYToLL-M-5_v2_ext1-v1", 
                                                 "crab_dec_24_v2_3_DYToLL-M-5_stic_v2-v2",  "crab_dec_24_v2_4_DYToLL-M-5_v2_ext1-v1",
                                                 "crab_dec_24_v2_5_DYToLL-M-5_stic_v2-v2",  "crab_dec_24_v2_6_DYToLL-M-5_v2_ext1-v1",
                                                 "crab_dec_24_v2_7_DYToLL-M-5_stic_v2-v1"}),
      get_chanal("QCD",         input_path,     {"crab_dec_24_v2_8_QCD_Flat_P_v2_ext1-v1", "crab_dec_24_v2_9_QCD_Flat_P_stic_v2-v2"}),

      get_chanal("Diboson",     input_path,     {"crab_dec_24_v2_16_ZZTo2Q2L_1_stic_v2-v2", "crab_dec_24_v2_17_ZZTo2Q2L_1_v2_ext1-v1",
                                                 "crab_dec_24_v2_18_ZZTo4L_14T_stic_v2-v1", 
                                                 "crab_jan_1_WZTo3LNu_0Jets_14TeV-madgraphMLM-pythia8_v2-v2",
                                                 "crab_jan_1_WZTo3LNu_1Jets_14TeV-madgraphMLM-pythia8_v2-v2",
                                                 "crab_jan_1_WZTo3LNu_2Jets_14TeV-madgraphMLM-pythia8_ext1-v2",
                                                 "crab_jan_1_WZTo3LNu_2Jets_14TeV-madgraphMLM-pythia8_v2-v2"})
  };
  return chanal_datas;
}

void tmva_prepare_events(){
  string input_path = "hzura_jan_02";
  string out_path   = "hzura_mva_jan_02";

  // setup list of files
  vector<chanal_data> chanal_datas = get_current_channals( input_path );
  
  TRandom3 rndm;
  // get some percents from this files
  for(chanal_data cd : chanal_datas){
    msg( cd.physic_name, cd.nevents, cd.weight_sum, cd.weight_sum/cd.nevents );
  //continue;
    
    TChain * chain = new TChain();
    for(string fname : cd.file_names) chain->Add( (fname + "/ttree" ).c_str());
    
    
    TFile *outfile = new TFile( (out_path + "/" + cd.physic_name + ".root").c_str(), "RECREATE");
    TTree *train = chain->CloneTree( 0 );
    TTree *test  = chain->CloneTree( 0 );
    TTree *data  = chain->CloneTree( 0 );

    train->SetName("train");
    test->SetName("test");
    data->SetName("data");

    int train_n_events = TMath::Max(TMath::Min(0.10*cd.nevents, 2*75000.), 25.);
    int test_n_events  = TMath::Max(TMath::Min(0.10*cd.nevents, 75000.  ), 25.);
    train_n_events     = 0;
    test_n_events      = 0;

    int train_n_events_counter = train_n_events;
    int test_n_events_counter  = test_n_events;

    for(int i = 0; i < cd.nevents; i++){
      chain->GetEntry(i);
      if( train_n_events_counter and not ((i+train_n_events) % (cd.nevents/train_n_events)) ){
        train->Fill();
        train_n_events_counter--;
        continue;
      }
      if( test_n_events_counter and not ((i+test_n_events+1) % (cd.nevents/test_n_events)) ){
        test->Fill();
        test_n_events_counter--;
        continue;
      }
      data->Fill();
    }

    msg(cd.nevents, cd.nevents-train_n_events-test_n_events, train_n_events, test_n_events);
    msg(data->GetEntries()+train->GetEntries()+test->GetEntries(), data->GetEntries(), train->GetEntries(), test->GetEntries());

    outfile->Write();
    outfile->Close();
  }
}


/*

crab_jan_1_ST_tch_14TeV_antitop_incl-powheg-pythia8-madspin_ext1-v2  /ST_tch_14TeV_antitop_incl-powheg-pythia8-madspin/PhaseIITDRFall17MiniAOD-PU200_93X_upgrade2023_realistic_v2_ext1-v2/MINIAODSIM
crab_jan_1_WToLNu_1J_14TeV-madgraphMLM-pythia8_v2-v2                 /WToLNu_1J_14TeV-madgraphMLM-pythia8/PhaseIITDRFall17MiniAOD-PU200_93X_upgrade2023_realistic_v2-v2/MINIAODSIM
crab_jan_1_WToLNu_3J_14TeV-madgraphMLM-pythia8_v2-v2                 /WToLNu_3J_14TeV-madgraphMLM-pythia8/PhaseIITDRFall17MiniAOD-PU200_93X_upgrade2023_realistic_v2-v2/MINIAODSIM
crab_jan_1_WZTo3LNu_0Jets_14TeV-madgraphMLM-pythia8_v2-v2            /WZTo3LNu_0Jets_14TeV-madgraphMLM-pythia8/PhaseIITDRFall17MiniAOD-PU200_93X_upgrade2023_realistic_v2-v2/MINIAODSIM
crab_jan_1_WZTo3LNu_1Jets_14TeV-madgraphMLM-pythia8_v2-v2            /WZTo3LNu_1Jets_14TeV-madgraphMLM-pythia8/PhaseIITDRFall17MiniAOD-PU200_93X_upgrade2023_realistic_v2-v2/MINIAODSIM
crab_jan_1_WZTo3LNu_2Jets_14TeV-madgraphMLM-pythia8_ext1-v2          /WZTo3LNu_2Jets_14TeV-madgraphMLM-pythia8/PhaseIITDRFall17MiniAOD-PU200_93X_upgrade2023_realistic_v2-v2/MINIAODSIM
crab_jan_1_WZTo3LNu_2Jets_14TeV-madgraphMLM-pythia8_v2-v2            /WZTo3LNu_2Jets_14TeV-madgraphMLM-pythia8/PhaseIITDRFall17MiniAOD-PU200_93X_upgrade2023_realistic_v2_ext1-v2/MINIAODSIM

*/

/*

vector<chanal_data> chanal_datas = {
    get_chanal("tcg",         input_path,     {"result_kc"},  true),
    get_chanal("tug",         input_path,     {"result_ku"},  true),
    get_chanal("TT",          input_path,     {"crab_dec_24_v2_14_TT_TuneCUE_stic_v2-v3", "crab_dec_24_v2_15_TT_TuneCUE_v2_ext1-v1"}),
    get_chanal("Wjets",       input_path,     {"crab_dec_24_v2_19_WToLNu_0J__stic_v2-v2", "crab_dec_24_v2_20_WToLNu_0J__v2_ext1-v1",
                                               "crab_dec_24_v2_21_WToLNu_1J__stic_v2-v2", "crab_dec_24_v2_22_WToLNu_2J__stic_v2-v2", 
                                               "crab_dec_24_v2_23_WToLNu_2J__v2_ext1-v1", "crab_dec_24_v2_24_WToLNu_3J__stic_v2-v2", 
                                               "crab_dec_24_v2_25_WToLNu_3J__v2_ext1-v1"}),
    get_chanal("ST",          input_path,     {"crab_dec_24_v2_10_ST_tch_14T_stic_v2-v2", "crab_dec_24_v2_11_ST_tch_14T_v2_ext1-v2",
                                               "crab_dec_24_v2_12_ST_tch_14T_stic_v2-v2", "crab_dec_24_v2_13_ST_tch_14T_v2_ext1-v1"}),
    get_chanal("tW",          input_path,     {"crab_dec_24_v2_10_ST_tch_14T_stic_v2-v2", "crab_dec_24_v2_11_ST_tch_14T_v2_ext1-v2",
                                               "crab_dec_24_v2_12_ST_tch_14T_stic_v2-v2", "crab_dec_24_v2_13_ST_tch_14T_v2_ext1-v1"}),
    get_chanal("DY",          input_path,     {"crab_dec_24_v2_1_DYToLL-M-5_stic_v2-v2",  "crab_dec_24_v2_2_DYToLL-M-5_v2_ext1-v1", 
                                               "crab_dec_24_v2_3_DYToLL-M-5_stic_v2-v2",  "crab_dec_24_v2_4_DYToLL-M-5_v2_ext1-v1",
                                               "crab_dec_24_v2_5_DYToLL-M-5_stic_v2-v2",  "crab_dec_24_v2_6_DYToLL-M-5_v2_ext1-v1",
                                               "crab_dec_24_v2_7_DYToLL-M-5_stic_v2-v1"}),
    get_chanal("QCD",         input_path,     {"crab_dec_24_v2_8_QCD_Flat_P_v2_ext1-v1", "crab_dec_24_v2_9_QCD_Flat_P_stic_v2-v2"}),

    get_chanal("Diboson",     input_path,     {"crab_dec_24_v2_16_ZZTo2Q2L_1_stic_v2-v2", "crab_dec_24_v2_17_ZZTo2Q2L_1_v2_ext1-v1",
                                               "crab_dec_24_v2_18_ZZTo4L_14T_stic_v2-v1"})
  };

*/
















