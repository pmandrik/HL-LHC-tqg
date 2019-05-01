
inline bool exists_test(const std::string& name) {
    if (FILE *file = fopen(name.c_str(), "r")) {
        fclose(file);
        return true;
    } else {
        return false;
    }   
}

string get_chanal(string pname, vector<string> input_path, vector<string> dataset_names){
  //cout << "\n\n\nprocess_datasets() ... begin" << endl;
  vector<string> files;
  vector<string> result_names;
  Long64_t nevents_total = 0;
  long double sum_of_weights = 0;

  for(string path : input_path){
    for(string dataset_name : dataset_names){
      //cout << " dataset " << dataset_name << endl;
      for(int i = 0; i < 100; i++){
        string file_name = path + "/" + dataset_name + "_part" + to_string(i) + ".root";
        if(not exists_test( file_name ) ) break;
        TFile * f = TFile::Open( file_name.c_str() );
        if(not f) break;
        TTree * tree = (TTree*)f->Get("ntuple/Event");
        if(not tree) cout << "cant find tree \"ntuple/Event\"!!!" << endl;
        //cout << "   add " << file_name << " with "<< tree->GetEntries() << " events" << endl;
        Long64_t nevents = tree->GetEntries();
        nevents_total   += nevents;
        f->Close();
      }
    }

    for(int j = 0; j < 5; j++){
      for(string dataset_name : dataset_names){
        //cout << " dataset " << dataset_name << endl;
        for(int i = 0; i < 100; i++){
          string file_name = path + "/" + dataset_name + "_reanalyzing_v" + to_string(j) + "_part" + to_string(i) + ".root";
          if(not exists_test( file_name ) ) break;
          TFile * f = TFile::Open( file_name.c_str() );
          if(not f) break;
          TTree * tree = (TTree*)f->Get("ntuple/Event");
          if(not tree) cout << "cant find tree \"ntuple/Event\"!!!" << endl;
          //cout << "   add " << file_name << " with "<< tree->GetEntries() << " events" << endl;
          Long64_t nevents = tree->GetEntries();
          nevents_total   += nevents;
          f->Close();
        }
      }
    }
  }

  if(nevents_total == 0) return "";
  cout << pname << " & " << nevents_total << " &  \\\\" << endl;
  return "";
}

string get_chanal_lumi(string pname, map<string, double> map_lumi, vector<string> input_path, vector<string> dataset_names){
  double lumi = 3000*1000; // pb-1

  double xsec = 0;
  for(int i = 0; i < dataset_names.size(); i++)
    xsec += map_lumi.find( dataset_names.at(0) )->second;
  cout << pname << " & " << (long long int)(lumi * xsec)/1000000 << " &  \\\\" << endl;
  return "";
}

void process_datasets(string path, string dname, double lumi, double xsec, string pname){
  //cout << "\n\n\nprocess_datasets() ... begin" << endl;
  vector<string> files;
  vector<string> result_names;
  Long64_t nevents_total = 0;
  long double sum_of_weights = 0;

  vector<string> dataset_names = { dname };
  for(string dataset_name : dataset_names){
    //cout << " dataset " << dataset_name << endl;
    for(int i = 0; i < 100; i++){
      string file_name = path + "/" + dataset_name + "_part" + to_string(i) + ".root";
      if(not exists_test( file_name ) ) break;
      TFile * f = TFile::Open( file_name.c_str() );
      if(not f) break;
      TTree * tree = (TTree*)f->Get("ntuple/Event");
      if(not tree) cout << "cant find tree \"ntuple/Event\"!!!" << endl;
      //cout << "   add " << file_name << " with "<< tree->GetEntries() << " events" << endl;
      Long64_t nevents = tree->GetEntries();
      nevents_total   += nevents;

      /*
      Float_t Weight[500];
      tree->SetBranchAddress("Weight", Weight);
      for(Long64_t nevent = 0; nevent < nevents; nevent++){
        tree->GetEntry( nevent );
        sum_of_weights += Weight[0];
      }

      files.push_back( file_name );
      result_names.push_back( "hzura_" + dataset_name + "_part" + to_string(i) + ".root" );
      */
      f->Close();
    }
  }

  // https://indico.cern.ch/event/402279/contributions/960421/attachments/805964/1104514/mcaod-Jun17-2015.pdf
  // https://indico.cern.ch/event/494682/contributions/1172505/attachments/1223578/1800218/mcaod-Feb15-2016.pdf#search=GenEventInfoProduct
  // https://indico.cern.ch/event/555805/contributions/2287180/attachments/1328032/1994393/2016_08_29__Sherpa_Tutorial__Sherpa_in_CMSSW.pdf#search=GenEventInfoProduct
  double dataset_weight_old = lumi / nevents_total * xsec;
  double dataset_weight_new = lumi / sum_of_weights * xsec;
  //cout << " MC events number " << nevents_total << endl;
  //cout << " Expected events number " << (long long int)(lumi * xsec) << " for lumi " << lumi << "pb-1" <<  endl;
  //cout << " dataset_weight old = " << (long long int)dataset_weight_old << " " << nevents_total  << endl;
  //cout << " dataset_weight new = " << (long long int)dataset_weight_new << " " << sum_of_weights << endl;

  if(nevents_total == 0) return;
  cout << pname << " & " << nevents_total << " & " << xsec << " \\\\" << "%" << dname << endl;
}

map<string, double> prepare_xsec_map(vector<string> names, double xsec){
  map<string, double> answer;
  for(auto name : names) answer[name] = xsec;
  return answer;
}

template<typename... Args> map<string, double> prepare_xsec_map(vector<string> names, double xsec, Args... args){
  map<string, double> answer = prepare_xsec_map(args...);
  for(auto name : names) answer[name] = xsec;
  return answer;
}

void event_couter(){
  map<string, string> dataset_map;
  dataset_map["crab_dec_24_v2_8_QCD_Flat_P_v2_ext1-v1"] = "\\texttt{QCD\\_Flat\\_Pt-15to7000\\_TuneCUETP8M1\\_14TeV\\_pythia8/...\\_ext1-v1/...}";
  dataset_map["crab_dec_24_v2_9_QCD_Flat_P_stic_v2-v2"] = "\\texttt{QCD\\_Flat\\_Pt-15to7000\\_TuneCUETP8M1\\_14TeV\\_pythia8/...\\_v2-v2/...}";
  dataset_map["crab_dec_24_v2_0_DYJetsToLL_v2_ext1-v1"] = "\\texttt{DYJetsToLL\\_M-10to50\\_TuneCUETP8M1\\_14TeV-madgraphMLM-pythia8/...\\_ext1-v1/...}";
  dataset_map["crab_dec_24_v2_1_DYToLL-M-5_stic_v2-v2"] = "\\texttt{DYToLL-M-50\\_0J\\_14TeV-madgraphMLM-pythia8/...\\_v2-v2/...}";
  dataset_map["crab_dec_24_v2_2_DYToLL-M-5_v2_ext1-v1"] = "\\texttt{DYToLL-M-50\\_0J\\_14TeV-madgraphMLM-pythia8/...\\_ext1-v1/...}";
  dataset_map["crab_dec_24_v2_3_DYToLL-M-5_stic_v2-v2"] = "\\texttt{DYToLL-M-50\\_1J\\_14TeV-madgraphMLM-pythia8/...\\_v2-v2/...}";
  dataset_map["crab_dec_24_v2_4_DYToLL-M-5_v2_ext1-v1"] = "\\texttt{DYToLL-M-50\\_1J\\_14TeV-madgraphMLM-pythia8/...\\_ext1-v1/...}";
  dataset_map["crab_dec_24_v2_5_DYToLL-M-5_stic_v2-v2"] = "\\texttt{DYToLL-M-50\\_2J\\_14TeV-madgraphMLM-pythia8/...\\_v2-v2/...}";
  dataset_map["crab_dec_24_v2_6_DYToLL-M-5_v2_ext1-v1"] = "\\texttt{DYToLL-M-50\\_2J\\_14TeV-madgraphMLM-pythia8/...\\_ext1-v1/...}";
  dataset_map["crab_dec_24_v2_7_DYToLL-M-5_stic_v2-v1"] = "\\texttt{DYToLL-M-50\\_3J\\_14TeV-madgraphMLM-pythia8/...\\_v2-v1/...}";
  dataset_map["crab_dec_24_v2_10_ST_tch_14T_stic_v2-v2"] = "\\texttt{ST\\_tch\\_14TeV\\_antitop\\_incl-powheg-pythia8-madspin/...\\_v2-v2/...}";
  dataset_map["crab_dec_24_v2_12_ST_tch_14T_stic_v2-v2"] = "\\texttt{ST\\_tch\\_14TeV\\_top\\_incl-powheg-pythia8-madspin/...\\_v2-v2/...}";
  dataset_map["crab_dec_24_v2_13_ST_tch_14T_v2_ext1-v1"] = "\\texttt{ST\\_tch\\_14TeV\\_top\\_incl-powheg-pythia8-madspin/...\\_ext1-v1/...}";
  dataset_map["crab_dec_24_v2_14_TT_TuneCUE_stic_v2-v3"] = "\\texttt{TT\\_TuneCUETP8M2T4\\_14TeV-powheg-pythia8/...\\_v2-v3/...}";
  dataset_map["crab_dec_24_v2_15_TT_TuneCUE_v2_ext1-v1"] = "\\texttt{TT\\_TuneCUETP8M2T4\\_14TeV-powheg-pythia8/...\\_ext1-v1/...}";
  dataset_map["crab_dec_24_v2_16_ZZTo2Q2L_1_stic_v2-v2"] = "\\texttt{ZZTo2Q2L\\_14TeV\\_powheg\\_pythia8/...\\_v2-v2/...}";
  dataset_map["crab_dec_24_v2_17_ZZTo2Q2L_1_v2_ext1-v1"] = "\\texttt{ZZTo2Q2L\\_14TeV\\_powheg\\_pythia8/...\\_ext1-v1/...}";
  dataset_map["crab_dec_24_v2_18_ZZTo4L_14T_stic_v2-v1"] = "\\texttt{ZZTo4L\\_14TeV\\_powheg\\_pythia8\\_v2/...\\_v2-v1/...}";
  dataset_map["crab_dec_24_v2_19_WToLNu_0J__stic_v2-v2"] = "\\texttt{WToLNu\\_0J\\_14TeV-madgraphMLM-pythia8/...\\_v2-v2/...}";
  dataset_map["crab_dec_24_v2_20_WToLNu_0J__v2_ext1-v1"] = "\\texttt{WToLNu\\_0J\\_14TeV-madgraphMLM-pythia8/...\\_ext1-v1/...}";
  dataset_map["crab_dec_24_v2_22_WToLNu_2J__stic_v2-v2"] = "\\texttt{WToLNu\\_2J\\_14TeV-madgraphMLM-pythia8/...\\_v2-v2/...}";
  dataset_map["crab_dec_24_v2_23_WToLNu_2J__v2_ext1-v1"] = "\\texttt{WToLNu\\_2J\\_14TeV-madgraphMLM-pythia8/...\\_ext1-v1/...}";
  dataset_map["crab_dec_24_v2_25_WToLNu_3J__v2_ext1-v1"] = "\\texttt{WToLNu\\_3J\\_14TeV-madgraphMLM-pythia8/...\\_ext1-v1/...}";
  dataset_map["crab_dec_24_v2_26_ST_tW_DR_1_stic_v2-v2"] = "\\texttt{ST\\_tW\\_DR\\_14TeV\\_antitop\\_incl-powheg-pythia8/...\\_v2-v2/...}";
  dataset_map["crab_dec_24_v2_27_ST_tW_DR_1_v2_ext1-v1"] = "\\texttt{ST\\_tW\\_DR\\_14TeV\\_antitop\\_incl-powheg-pythia8/...\\_ext1-v1/...}";
  dataset_map["crab_dec_24_v2_28_ST_tW_DR_1_stic_v2-v2"] = "\\texttt{ST\\_tW\\_DR\\_14TeV\\_top\\_incl-powheg-pythia8/...\\_v2-v2/...}";
  dataset_map["crab_dec_24_v2_29_ST_tW_DR_1_v2_ext1-v1"] = "\\texttt{ST\\_tW\\_DR\\_14TeV\\_top\\_incl-powheg-pythia8/...\\_ext1-v1/...}";
  dataset_map["crab_jan_1_ST_tch_14TeV_antitop_incl-powheg-pythia8-madspin_ext1-v2"] = "\\texttt{ST\\_tch\\_14TeV\\_antitop\\_incl-powheg-pythia8-madspin/...\\_ext1-v2/...}";
  dataset_map["crab_jan_1_WToLNu_1J_14TeV-madgraphMLM-pythia8_v2-v2"] = "\\texttt{WToLNu\\_1J\\_14TeV-madgraphMLM-pythia8/...\\_v2-v2/...}";
  dataset_map["crab_jan_1_WToLNu_3J_14TeV-madgraphMLM-pythia8_v2-v2"] = "\\texttt{WToLNu\\_3J\\_14TeV-madgraphMLM-pythia8/...\\_v2-v2/...}";
  dataset_map["crab_jan_1_WZTo3LNu_0Jets_14TeV-madgraphMLM-pythia8_v2-v2"] = "\\texttt{WZTo3LNu\\_0Jets\\_14TeV-madgraphMLM-pythia8/...\\_v2-v2/...}";
  dataset_map["crab_jan_1_WZTo3LNu_1Jets_14TeV-madgraphMLM-pythia8_v2-v2"] = "\\texttt{WZTo3LNu\\_1Jets\\_14TeV-madgraphMLM-pythia8/...\\_v2-v2/...}";
  dataset_map["crab_jan_1_WZTo3LNu_2Jets_14TeV-madgraphMLM-pythia8_ext1-v2"] = "\\texttt{WZTo3LNu\\_2Jets\\_14TeV-madgraphMLM-pythia8/...\\_v2-v2/...}";
  dataset_map["crab_jan_1_WZTo3LNu_2Jets_14TeV-madgraphMLM-pythia8_v2-v2"] = "\\texttt{WZTo3LNu\\_2Jets\\_14TeV-madgraphMLM-pythia8/...\\_ext1-v2/...}";
  dataset_map["crab_jan_22_v0_tGluon_FCNC_tGc_14TeV_CompHEP_v2-v2"] = "\\texttt{tGluon\\_FCNC_tGc\\_14TeV\\_CompHEP/...\\_v2-v2/...";
  dataset_map["crab_jan_12_v3_tGluon_FCNC_tGu_14TeV_CompHEP_v2-v1"] = "\\texttt{tGluon\\_FCNC_tGu\\_14TeV\\_CompHEP/...\\_v2-v1/...";
  dataset_map["crab_jan_16_v1_WToLNu_1J_14TeV-madgraphMLM-pythia8_ext1-v3"] = "\\texttt{WToLNu\\_1J\\_14TeV-madgraphMLM-pythia8/...\\_ext1-v3/...}";

  map<string, double> xsec_map = prepare_xsec_map(
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
      vector<string>({"crab_dec_24_v2_14_TT_TuneCUE_stic_v2-v3", "crab_dec_24_v2_15_TT_TuneCUE_v2_ext1-v1"}),      864.4,
      vector<string>({"crab_jan_1_ST_tch_14TeV_antitop_incl-powheg-pythia8-madspin_ext1-v2"}),      93.28,
      vector<string>({"crab_jan_1_WToLNu_1J_14TeV-madgraphMLM-pythia8_v2-v2"}),                     10330,
      vector<string>({"crab_jan_16_v1_WToLNu_1J_14TeV-madgraphMLM-pythia8_ext1-v3"}),               10330,
      vector<string>({"crab_jan_1_WToLNu_3J_14TeV-madgraphMLM-pythia8_v2-v2"}),                      1891,
      vector<string>({"crab_jan_1_WZTo3LNu_0Jets_14TeV-madgraphMLM-pythia8_v2-v2"}),                3.11,
      vector<string>({"crab_jan_1_WZTo3LNu_1Jets_14TeV-madgraphMLM-pythia8_v2-v2"}),                0.954,
      vector<string>({"crab_jan_1_WZTo3LNu_2Jets_14TeV-madgraphMLM-pythia8_v2-v2"}),                0.274,
      vector<string>({"crab_jan_1_WZTo3LNu_2Jets_14TeV-madgraphMLM-pythia8_ext1-v2"}),              0.274,
      vector<string>({"crab_jan_22_v0_tGluon_FCNC_tGc_14TeV_CompHEP_v2-v2" }),      30,      // 2.191e+09 pb
      vector<string>({"crab_jan_12_v3_tGluon_FCNC_tGu_14TeV_CompHEP_v2-v1" }),     156.3
    );

  if(true){
    string path;
    path = "/eos/user/p/pmandrik/lsf_delphy_samples/tgs_samples/dec_24";
    double lumi = 3000*1000; // pb-1

    for(auto it = dataset_map.begin(); it!= dataset_map.end(); it++){
      string dname = it->first;
      float  xsec  = xsec_map.find(dname)->second;
      string  pname = it->second;
      process_datasets(path, dname, lumi, xsec, pname);
    }

    path = "/eos/user/p/pmandrik/lsf_delphy_samples/tgs_samples/jan_03";
    for(auto it = dataset_map.begin(); it!= dataset_map.end(); it++){
      string dname = it->first;
      float  xsec  = xsec_map.find(dname)->second;
      string  pname = it->second;
      process_datasets(path, dname, lumi, xsec, pname);
    }
  }

  if(false){
    vector<string> input_path = {"/eos/user/p/pmandrik/lsf_delphy_samples/tgs_samples/dec_24", "/eos/user/p/pmandrik/lsf_delphy_samples/tgs_samples/jan_03"};
    vector<string> chs = {
        get_chanal("tcg",         input_path,     {"result_kc"}),
        get_chanal("tug",         input_path,     {"result_ku"}),
        get_chanal("TT",          input_path,     {"crab_dec_24_v2_14_TT_TuneCUE_stic_v2-v3", "crab_dec_24_v2_15_TT_TuneCUE_v2_ext1-v1"}),
        get_chanal("W+jets",      input_path,     {"crab_dec_24_v2_19_WToLNu_0J__stic_v2-v2", "crab_dec_24_v2_20_WToLNu_0J__v2_ext1-v1",
                                                   "crab_jan_1_WToLNu_1J_14TeV-madgraphMLM-pythia8_v2-v2", 
                                                   "crab_dec_24_v2_22_WToLNu_2J__stic_v2-v2","crab_dec_24_v2_23_WToLNu_2J__v2_ext1-v1",
                                                   "crab_jan_1_WToLNu_3J_14TeV-madgraphMLM-pythia8_v2-v2","crab_dec_24_v2_25_WToLNu_3J__v2_ext1-v1"}),
        get_chanal("ST",          input_path,     {"crab_dec_24_v2_10_ST_tch_14T_stic_v2-v2", "crab_jan_1_ST_tch_14TeV_antitop_incl-powheg-pythia8-madspin_ext1-v2",
                                                   "crab_dec_24_v2_12_ST_tch_14T_stic_v2-v2", "crab_dec_24_v2_13_ST_tch_14T_v2_ext1-v1"}),
        get_chanal("tW",          input_path,     {"crab_dec_24_v2_26_ST_tW_DR_1_stic_v2-v2", "crab_dec_24_v2_27_ST_tW_DR_1_v2_ext1-v1",
                                                   "crab_dec_24_v2_28_ST_tW_DR_1_stic_v2-v2", "crab_dec_24_v2_29_ST_tW_DR_1_v2_ext1-v1"}),
        get_chanal("Drell--Yan",  input_path,     {"crab_dec_24_v2_1_DYToLL-M-5_stic_v2-v2",  "crab_dec_24_v2_2_DYToLL-M-5_v2_ext1-v1", 
                                                   "crab_dec_24_v2_3_DYToLL-M-5_stic_v2-v2",  "crab_dec_24_v2_4_DYToLL-M-5_v2_ext1-v1",
                                                   "crab_dec_24_v2_5_DYToLL-M-5_stic_v2-v2",  "crab_dec_24_v2_6_DYToLL-M-5_v2_ext1-v1",
                                                   "crab_dec_24_v2_7_DYToLL-M-5_stic_v2-v1"}),
        get_chanal("QCD",         input_path,     {"crab_dec_24_v2_8_QCD_Flat_P_v2_ext1-v1", "crab_dec_24_v2_9_QCD_Flat_P_stic_v2-v2"}),

        get_chanal("Diboson",     input_path,     {"crab_dec_24_v2_16_ZZTo2Q2L_1_stic_v2-v2", "crab_dec_24_v2_17_ZZTo2Q2L_1_v2_ext1-v1",
                                                   "crab_dec_24_v2_18_ZZTo4L_14T_stic_v2-v1", 
                                                   "crab_jan_1_WZTo3LNu_0Jets_14TeV-madgraphMLM-pythia8_v2-v2",
                                                   "crab_jan_1_WZTo3LNu_1Jets_14TeV-madgraphMLM-pythia8_v2-v2",
                                                   "crab_jan_1_WZTo3LNu_2Jets_14TeV-madgraphMLM-pythia8_ext1-v2",
                                                   "crab_jan_1_WZTo3LNu_2Jets_14TeV-madgraphMLM-pythia8_v2-v2"})};
  }
  
  if(false){
    double lumi = 3000*1000; // pb-1
    vector<string> input_path = {"/eos/user/p/pmandrik/lsf_delphy_samples/tgs_samples/dec_24", "/eos/user/p/pmandrik/lsf_delphy_samples/tgs_samples/jan_03"};
    vector<string> chs = {
        get_chanal_lumi("tcg",         xsec_map, input_path,     {"result_kc"}),
        get_chanal_lumi("tug",         xsec_map, input_path,     {"result_ku"}),
        get_chanal_lumi("TT",          xsec_map, input_path,     {"crab_dec_24_v2_14_TT_TuneCUE_stic_v2-v3"}),
        get_chanal_lumi("W+jets",      xsec_map, input_path,     {"crab_dec_24_v2_19_WToLNu_0J__stic_v2-v2",
                                                                  "crab_jan_1_WToLNu_1J_14TeV-madgraphMLM-pythia8_v2-v2", 
                                                                  "crab_dec_24_v2_22_WToLNu_2J__stic_v2-v2",
                                                                  "crab_jan_1_WToLNu_3J_14TeV-madgraphMLM-pythia8_v2-v2"}),
        get_chanal_lumi("ST",          xsec_map, input_path,     {"crab_dec_24_v2_10_ST_tch_14T_stic_v2-v2", "crab_jan_1_ST_tch_14TeV_antitop_incl-powheg-pythia8-madspin_ext1-v2",
                                                                  "crab_dec_24_v2_12_ST_tch_14T_stic_v2-v2", "crab_dec_24_v2_13_ST_tch_14T_v2_ext1-v1"}),
        get_chanal_lumi("tW",          xsec_map, input_path,     {"crab_dec_24_v2_26_ST_tW_DR_1_stic_v2-v2",
                                                                  "crab_dec_24_v2_28_ST_tW_DR_1_stic_v2-v2"}),
        get_chanal_lumi("Drell--Yan",  xsec_map, input_path,     {"crab_dec_24_v2_1_DYToLL-M-5_stic_v2-v2", 
                                                                 "crab_dec_24_v2_3_DYToLL-M-5_stic_v2-v2",
                                                                 "crab_dec_24_v2_5_DYToLL-M-5_stic_v2-v2",
                                                                 "crab_dec_24_v2_7_DYToLL-M-5_stic_v2-v1"}),
        get_chanal_lumi("QCD",         xsec_map, input_path,     {"crab_dec_24_v2_8_QCD_Flat_P_v2_ext1-v1"}),

        get_chanal_lumi("Diboson",     xsec_map, input_path,     {"crab_dec_24_v2_16_ZZTo2Q2L_1_stic_v2-v2",
                                                                 "crab_dec_24_v2_18_ZZTo4L_14T_stic_v2-v1", 
                                                                 "crab_jan_1_WZTo3LNu_0Jets_14TeV-madgraphMLM-pythia8_v2-v2",
                                                                 "crab_jan_1_WZTo3LNu_1Jets_14TeV-madgraphMLM-pythia8_v2-v2",
                                                                 "crab_jan_1_WZTo3LNu_2Jets_14TeV-madgraphMLM-pythia8_ext1-v2",
                                                                 "crab_jan_1_WZTo3LNu_2Jets_14TeV-madgraphMLM-pythia8_v2-v2"})};
  }
}



