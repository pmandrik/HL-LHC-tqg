

#include "/afs/cern.ch/user/p/pmandrik/public/global_cfg/mRoot.cpp"
#include "/afs/cern.ch/user/p/pmandrik/public/global_cfg/mRootStackDrawer.cpp"

#include "tmva_prepare_events.C"

using namespace mRoot;

struct DrawVariable{
  
};

void hzura_drawer(){
  string input_path = "hzura_jan_02";
  string out_path   = "hzura_plot_jan_02_QCD_no_weights_2";

  // setup list of files
  vector<chanal_data> chanal_datas = get_current_channals( input_path );

  vector<string> all_files;
  for(chanal_data cd : chanal_datas){
    cout << cd.physic_name << endl;
    all_files.insert(all_files.end(), cd.file_names.begin(), cd.file_names.end());
  }
  TChain * chain = new TChain("ttree");
  for(auto file : all_files){
    cout << file << endl;
    chain->Add( file.c_str() );
  }

  // setup list of variables
  vector<string> vars = {"Lepton_Pt",  "Lepton_Phi",  "Lepton_Eta",  "Lepton_Px",  "Lepton_Py",  "Lepton_Pz",  "Lepton_E",  "Lepton_Type",  
    "MET_Pt",  "MET_Phi",  "MET_Px",  "MET_Py",  "W_Pt",  "W_Mt",  
    "bJet_Pt",  "bJet_Phi",  "bJet_Eta",  "t_Pt",  "t_Phi",  "t_Eta",  "t_M",  
    "LightJet_Pt",  "LightJet_Phi",  "LightJet_Eta",  "MVA_bJetLepton_Mass",  "MVA_bJetLepton_Pt",  "MVA_bJetTop_dPhi",  "MVA_bJetW_dPhi",  "MVA_bJetTop_dEta",  
    "LeadingJet_Pt",  "LeadingJet_Px",  "LeadingJet_Py",  "LeadingJet_Pz",  "LeadingJet_E",  
    "SecondJet_Pt",  "SecondJet_Px",  "SecondJet_Py",  "SecondJet_Pz",  "SecondJet_E",  
    "LeadingJetSecondJet_Pt",  "LeadingJetSecondJet_M",  "LeadingJetSecondJet_dR",  
    "Jets_SumPt",  "Jets_SumPt_minus_bJet_Pt",  "Jets_M_without_bJet",  "JetsW_M", "Jets_N", 
    "Sphericity",  "Planarity",  "Aplanarity",  "cos_lightJetLepton_tsystem",  "cos_lightJetW_tsystem",  "cos_leptonW_Wsystem" };

  vector<string> log_vars = {"Lepton_Pt", "Lepton_Eta", "bJet_Pt", "bJet_Pt", "bJet_Eta", "W_Pt", "W_Mt", "t_Pt", "t_M", "t_Eta", "MET_Pt", 
                             "MVA_bJetLepton_Mass", "MVA_bJetLepton_Pt", "MVA_bJetTop_dEta", "LightJet_Pt", "LightJet_Eta" };

  // for every var plot stack hist of channals
  for(string var : vars){
    double xmin = chain->GetMinimum( var.c_str() );
    double xmax = chain->GetMaximum( var.c_str() );
    cout << var << "[" << xmin << "," << xmax << "]" << endl;
    xmin -= abs(xmin*0.1);
    xmax += abs(xmax*0.1);
    if(xmax > 1000 or xmin < -1000){
      chain->Draw( (var+ ">>his").c_str() );
      TH1F *his = (TH1F *)gDirectory->Get("his");
      double mean = his->GetMean();
      double rms  = his->GetRMS();

      if(xmax >  mean + 2 * rms) xmax = mean + 2 * rms;
      if(xmin < -mean - 2 * rms) xmin = mean - 2 * rms;
    }

    StackDrawer * drawer = new StackDrawer();
    // drawer->stack_hists
    for(chanal_data cd : chanal_datas){
      string cut = " * (Lepton_Type == 1)";

      TH1D * result;
      if(cd.signal)                      {
        result = fill_hist(cd.physic_name + "@" + var, 20, xmin, xmax, "", cd.file_names, "ttree", var, "weight * 5" + cut);
        result->SetTitle( (cd.physic_name+"*5").c_str() );
      }
      else if(cd.physic_name=="Diboson"){
        result = fill_hist(cd.physic_name + "@" + var, 20, xmin, xmax, "", cd.file_names, "ttree", var, "weight" + cut);
        result->SetTitle( (cd.physic_name).c_str() );
      }
      else if(cd.physic_name=="QCD"    ){
        result = fill_hist(cd.physic_name + "@" + var, 20, xmin, xmax, "", cd.file_names, "ttree", var, "weight_old" + cut);
        result->SetTitle( (cd.physic_name).c_str() );
      }
      else{
        result = fill_hist(cd.physic_name + "@" + var, 20, xmin, xmax, "", cd.file_names, "ttree", var, "weight" + cut);
        result->SetTitle( (cd.physic_name).c_str() );
      }
      if(not cd.signal) drawer->stack_hists.push_back( result );
      else              drawer->signal_hists.push_back( result );
    }

    auto canv = drawer->GetCanvas(var.c_str(), 800, 800);
    drawer->hs->GetXaxis()->SetTitle( var.c_str() );

    if( std::count(log_vars.begin(), log_vars.end(), var) ){
      //((TPad*)canv->GetPrimitive("p1"))->SetLogy();
      // drawer->hs->SetMinimum(0.5);
    }
    canv->Print( (out_path + "/" + var + ".png").c_str() );
  }
  
}







/*
    vector<string>({"crab_dec_24_v2_8_QCD_Flat_P_v2_ext1-v1",  "crab_dec_24_v2_9_QCD_Flat_P_stic_v2-v2" }),      2.191 * pow(10, 9),      // 2.191e+09 pb
    vector<string>({"crab_dec_24_v2_1_DYToLL-M-5_stic_v2-v2",  "crab_dec_24_v2_2_DYToLL-M-5_v2_ext1-v1" }),      3668,
    vector<string>({"crab_dec_24_v2_3_DYToLL-M-5_stic_v2-v2",  "crab_dec_24_v2_4_DYToLL-M-5_v2_ext1-v1" }),      1094,
    vector<string>({"crab_dec_24_v2_5_DYToLL-M-5_stic_v2-v2",  "crab_dec_24_v2_6_DYToLL-M-5_v2_ext1-v1" }),      369.7,
    vector<string>({"crab_dec_24_v2_7_DYToLL-M-5_stic_v2-v1"                                            }),      190.2,
    vector<string>({"crab_dec_24_v2_10_ST_tch_14T_stic_v2-v2", "crab_dec_24_v2_11_ST_tch_14T_v2_ext1-v2"}),      93.28,                   // 93.28 pb
    vector<string>({"crab_dec_24_v2_12_ST_tch_14T_stic_v2-v2", "crab_dec_24_v2_13_ST_tch_14T_v2_ext1-v1"}),      154.76,
    vector<string>({"crab_dec_24_v2_14_TT_TuneCUE_stic_v2-v3", "crab_dec_24_v2_15_TT_TuneCUE_v2_ext1-v1"}),      864.4,
    vector<string>({"crab_dec_24_v2_16_ZZTo2Q2L_1_stic_v2-v2", "crab_dec_24_v2_17_ZZTo2Q2L_1_v2_ext1-v1"}),      2.214,
    vector<string>({"crab_dec_24_v2_18_ZZTo4L_14T_stic_v2-v1"                                           }),      1.357,
    vector<string>({"crab_dec_24_v2_19_WToLNu_0J__stic_v2-v2", "crab_dec_24_v2_20_WToLNu_0J__v2_ext1-v1"}),      38870,
    vector<string>({"crab_dec_24_v2_21_WToLNu_1J__stic_v2-v2"                                           }),      10330,
    vector<string>({"crab_dec_24_v2_22_WToLNu_2J__stic_v2-v2", "crab_dec_24_v2_23_WToLNu_2J__v2_ext1-v1"}),      3314,
    vector<string>({"crab_dec_24_v2_24_WToLNu_3J__stic_v2-v2", "crab_dec_24_v2_25_WToLNu_3J__v2_ext1-v1"}),      1891,
    vector<string>({"crab_dec_24_v2_26_ST_tW_DR_1_stic_v2-v2", "crab_dec_24_v2_27_ST_tW_DR_1_v2_ext1-v1"}),      42.2,
    vector<string>({"crab_dec_24_v2_28_ST_tW_DR_1_stic_v2-v2", "crab_dec_24_v2_29_ST_tW_DR_1_v2_ext1-v1"}),      42.2
*/


