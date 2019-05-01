
#ifndef tqgamma_Event_hh
#define tqgamma_Event_hh 1

class tqgamma_Event {
  public:
    tqgamma_Event(){
      fChain_MuonLoose = nullptr;
      fChain_ElectronTight = nullptr;
      fChain_ElectronLoose = nullptr;
      fChain_Particle = nullptr;
      fChain_ElectronMedium = nullptr;
      fChain_Vertex = nullptr;
      fChain_GenJet = nullptr;
      fChain_MuonTight = nullptr;
      fChain_PhotonLoose = nullptr;
      fChain_PhotonTight = nullptr;
      fChain_JetPUPPI = nullptr;
      fChain_PuppiMissingET = nullptr;
      fChain_Event = nullptr;
      fChain_GenPhoton = nullptr;

    }

    void Init(TFile * file){
      file->cd("ntuple");
      fChain_MuonLoose = (TTree*) gDirectory->Get("MuonLoose");
      fChain_ElectronTight = (TTree*) gDirectory->Get("ElectronTight");
      fChain_ElectronLoose = (TTree*) gDirectory->Get("ElectronLoose");
      // fChain_Particle = (TTree*) gDirectory->Get("Particle");
      fChain_ElectronMedium = (TTree*) gDirectory->Get("ElectronMedium");
      fChain_Vertex = (TTree*) gDirectory->Get("Vertex");
      // fChain_GenJet = (TTree*) gDirectory->Get("GenJet");
      fChain_MuonTight = (TTree*) gDirectory->Get("MuonTight");
      // fChain_PhotonLoose = (TTree*) gDirectory->Get("PhotonLoose");
      // fChain_PhotonTight = (TTree*) gDirectory->Get("PhotonTight");
      fChain_JetPUPPI = (TTree*) gDirectory->Get("JetPUPPI");
      fChain_PuppiMissingET = (TTree*) gDirectory->Get("PuppiMissingET");
      fChain_Event = (TTree*) gDirectory->Get("Event");
      // fChain_GenPhoton = (TTree*) gDirectory->Get("GenPhoton");


      if(fChain_MuonLoose == nullptr){
        cout << "tqgamma_Event.Init(): fChain_MuonLoose == nullptr, return" << endl;
        return;
      };
      if(fChain_ElectronTight == nullptr){
        cout << "tqgamma_Event.Init(): fChain_ElectronTight == nullptr, return" << endl;
        return;
      };
      if(fChain_ElectronLoose == nullptr){
        cout << "tqgamma_Event.Init(): fChain_ElectronLoose == nullptr, return" << endl;
        return;
      };
      /*
      if(fChain_Particle == nullptr){
        cout << "tqgamma_Event.Init(): fChain_Particle == nullptr, return" << endl;
        return;
      };
      */
      if(fChain_ElectronMedium == nullptr){
        cout << "tqgamma_Event.Init(): fChain_ElectronMedium == nullptr, return" << endl;
        return;
      };
      if(fChain_Vertex == nullptr){
        cout << "tqgamma_Event.Init(): fChain_Vertex == nullptr, return" << endl;
        return;
      };
      /*
      if(fChain_GenJet == nullptr){
        cout << "tqgamma_Event.Init(): fChain_GenJet == nullptr, return" << endl;
        return;
      };
      */
      if(fChain_MuonTight == nullptr){
        cout << "tqgamma_Event.Init(): fChain_MuonTight == nullptr, return" << endl;
        return;
      };
      /*
      if(fChain_PhotonLoose == nullptr){
        cout << "tqgamma_Event.Init(): fChain_PhotonLoose == nullptr, return" << endl;
        return;
      };
      if(fChain_PhotonTight == nullptr){
        cout << "tqgamma_Event.Init(): fChain_PhotonTight == nullptr, return" << endl;
        return;
      };
      */
      if(fChain_JetPUPPI == nullptr){
        cout << "tqgamma_Event.Init(): fChain_JetPUPPI == nullptr, return" << endl;
        return;
      };
      if(fChain_PuppiMissingET == nullptr){
        cout << "tqgamma_Event.Init(): fChain_PuppiMissingET == nullptr, return" << endl;
        return;
      };
      if(fChain_Event == nullptr){
        cout << "tqgamma_Event.Init(): fChain_Event == nullptr, return" << endl;
        return;
      };
      /*
      if(fChain_GenPhoton == nullptr){
        cout << "tqgamma_Event.Init(): fChain_GenPhoton == nullptr, return" << endl;
        return;
      };
      */

      // Set branch addresses
      fCurrent = -1;
      fChain_Event->SetBranchAddress("Run", &Run);
      fChain_Event->SetBranchAddress("Event", &Event);
      fChain_Event->SetBranchAddress("Lumi", &Lumi);
      fChain_Event->SetBranchAddress("Weight_size", &Weight_size);
      fChain_Event->SetBranchAddress("Weight", Weight);
      // fChain_Particle->SetBranchAddress("Particle_size", &Particle_size);
      // fChain_GenPhoton->SetBranchAddress("GenPhoton_size", &GenPhoton_size);
      fChain_Vertex->SetBranchAddress("Vertex_size", &Vertex_size);
      // fChain_GenJet->SetBranchAddress("GenJet_size", &GenJet_size);
      fChain_ElectronLoose->SetBranchAddress("ElectronLoose_size", &ElectronLoose_size);
      fChain_ElectronMedium->SetBranchAddress("ElectronMedium_size", &ElectronMedium_size);
      fChain_ElectronTight->SetBranchAddress("ElectronTight_size", &ElectronTight_size);
      fChain_MuonLoose->SetBranchAddress("MuonLoose_size", &MuonLoose_size);
      fChain_MuonTight->SetBranchAddress("MuonTight_size", &MuonTight_size);
      fChain_JetPUPPI->SetBranchAddress("JetPUPPI_size", &JetPUPPI_size);
      fChain_PuppiMissingET->SetBranchAddress("PuppiMissingET_size", &PuppiMissingET_size);
      // fChain_PhotonLoose->SetBranchAddress("PhotonLoose_size", &PhotonLoose_size);
      // fChain_PhotonTight->SetBranchAddress("PhotonTight_size", &PhotonTight_size);


      //fChain_Particle->SetBranchAddress("PID", Particle_PID);
      //fChain_Particle->SetBranchAddress("Charge", Particle_Charge);
      //fChain_Particle->SetBranchAddress("Status", Particle_Status);
      //fChain_Particle->SetBranchAddress("P", Particle_P);
      //fChain_Particle->SetBranchAddress("Px", Particle_Px);
      //fChain_Particle->SetBranchAddress("Py", Particle_Py);
      //fChain_Particle->SetBranchAddress("Pz", Particle_Pz);
      //fChain_Particle->SetBranchAddress("E", Particle_E);
      //fChain_Particle->SetBranchAddress("PT", Particle_PT);
      //fChain_Particle->SetBranchAddress("Eta", Particle_Eta);
      //fChain_Particle->SetBranchAddress("Phi", Particle_Phi);
      //fChain_Particle->SetBranchAddress("Mass", Particle_Mass);
      //fChain_Particle->SetBranchAddress("IsolationVar", Particle_IsolationVar);
      //fChain_GenPhoton->SetBranchAddress("Status", GenPhoton_Status);
      //fChain_GenPhoton->SetBranchAddress("P", GenPhoton_P);
      //fChain_GenPhoton->SetBranchAddress("Px", GenPhoton_Px);
      //fChain_GenPhoton->SetBranchAddress("Py", GenPhoton_Py);
      //fChain_GenPhoton->SetBranchAddress("Pz", GenPhoton_Pz);
      //fChain_GenPhoton->SetBranchAddress("E", GenPhoton_E);
      //fChain_GenPhoton->SetBranchAddress("PT", GenPhoton_PT);
      //fChain_GenPhoton->SetBranchAddress("Eta", GenPhoton_Eta);
      //fChain_GenPhoton->SetBranchAddress("Phi", GenPhoton_Phi);
      fChain_Vertex->SetBranchAddress("SumPT2", Vertex_SumPT2);
      //fChain_GenJet->SetBranchAddress("PT", GenJet_PT);
      //fChain_GenJet->SetBranchAddress("Eta", GenJet_Eta);
      //fChain_GenJet->SetBranchAddress("Phi", GenJet_Phi);
      //fChain_GenJet->SetBranchAddress("Mass", GenJet_Mass);
      fChain_ElectronLoose->SetBranchAddress("Charge", ElectronLoose_Charge);
      fChain_ElectronLoose->SetBranchAddress("Particle", ElectronLoose_Particle);
      fChain_ElectronLoose->SetBranchAddress("PT", ElectronLoose_PT);
      fChain_ElectronLoose->SetBranchAddress("Eta", ElectronLoose_Eta);
      fChain_ElectronLoose->SetBranchAddress("Phi", ElectronLoose_Phi);
      fChain_ElectronLoose->SetBranchAddress("Mass", ElectronLoose_Mass);
      fChain_ElectronLoose->SetBranchAddress("IsolationVar", ElectronLoose_IsolationVar);
      fChain_ElectronLoose->SetBranchAddress("BDTScore", ElectronLoose_BDTScore);
      fChain_ElectronLoose->SetBranchAddress("SF", ElectronLoose_SF);
      fChain_ElectronMedium->SetBranchAddress("Charge", ElectronMedium_Charge);
      fChain_ElectronMedium->SetBranchAddress("Particle", ElectronMedium_Particle);
      fChain_ElectronMedium->SetBranchAddress("PT", ElectronMedium_PT);
      fChain_ElectronMedium->SetBranchAddress("Eta", ElectronMedium_Eta);
      fChain_ElectronMedium->SetBranchAddress("Phi", ElectronMedium_Phi);
      fChain_ElectronMedium->SetBranchAddress("Mass", ElectronMedium_Mass);
      fChain_ElectronMedium->SetBranchAddress("IsolationVar", ElectronMedium_IsolationVar);
      fChain_ElectronMedium->SetBranchAddress("BDTScore", ElectronMedium_BDTScore);
      fChain_ElectronMedium->SetBranchAddress("SF", ElectronMedium_SF);
      fChain_ElectronTight->SetBranchAddress("Charge", ElectronTight_Charge);
      fChain_ElectronTight->SetBranchAddress("Particle", ElectronTight_Particle);
      fChain_ElectronTight->SetBranchAddress("PT", ElectronTight_PT);
      fChain_ElectronTight->SetBranchAddress("Eta", ElectronTight_Eta);
      fChain_ElectronTight->SetBranchAddress("Phi", ElectronTight_Phi);
      fChain_ElectronTight->SetBranchAddress("Mass", ElectronTight_Mass);
      fChain_ElectronTight->SetBranchAddress("IsolationVar", ElectronTight_IsolationVar);
      fChain_ElectronTight->SetBranchAddress("BDTScore", ElectronTight_BDTScore);
      fChain_ElectronTight->SetBranchAddress("SF", ElectronTight_SF);
      fChain_MuonLoose->SetBranchAddress("Charge", MuonLoose_Charge);
      fChain_MuonLoose->SetBranchAddress("Particle", MuonLoose_Particle);
      fChain_MuonLoose->SetBranchAddress("PT", MuonLoose_PT);
      fChain_MuonLoose->SetBranchAddress("Eta", MuonLoose_Eta);
      fChain_MuonLoose->SetBranchAddress("Phi", MuonLoose_Phi);
      fChain_MuonLoose->SetBranchAddress("Mass", MuonLoose_Mass);
      fChain_MuonLoose->SetBranchAddress("IsolationVar", MuonLoose_IsolationVar);
      fChain_MuonLoose->SetBranchAddress("SF", MuonLoose_SF);
      fChain_MuonTight->SetBranchAddress("Charge", MuonTight_Charge);
      fChain_MuonTight->SetBranchAddress("Particle", MuonTight_Particle);
      fChain_MuonTight->SetBranchAddress("PT", MuonTight_PT);
      fChain_MuonTight->SetBranchAddress("Eta", MuonTight_Eta);
      fChain_MuonTight->SetBranchAddress("Phi", MuonTight_Phi);
      fChain_MuonTight->SetBranchAddress("Mass", MuonTight_Mass);
      fChain_MuonTight->SetBranchAddress("IsolationVar", MuonTight_IsolationVar);
      fChain_MuonTight->SetBranchAddress("SF", MuonTight_SF);
      fChain_JetPUPPI->SetBranchAddress("ID", JetPUPPI_ID);
      fChain_JetPUPPI->SetBranchAddress("GenJet", JetPUPPI_GenJet);
      fChain_JetPUPPI->SetBranchAddress("PT", JetPUPPI_PT);
      fChain_JetPUPPI->SetBranchAddress("Eta", JetPUPPI_Eta);
      fChain_JetPUPPI->SetBranchAddress("Phi", JetPUPPI_Phi);
      fChain_JetPUPPI->SetBranchAddress("Mass", JetPUPPI_Mass);
      fChain_JetPUPPI->SetBranchAddress("MVAv2", JetPUPPI_MVAv2);
      fChain_JetPUPPI->SetBranchAddress("DeepCSV", JetPUPPI_DeepCSV);
      fChain_JetPUPPI->SetBranchAddress("PartonFlavor", JetPUPPI_PartonFlavor);
      fChain_JetPUPPI->SetBranchAddress("HadronFlavor", JetPUPPI_HadronFlavor);
      fChain_JetPUPPI->SetBranchAddress("GenPartonPID", JetPUPPI_GenPartonPID);
      fChain_JetPUPPI->SetBranchAddress("SF", JetPUPPI_SF);
      fChain_PuppiMissingET->SetBranchAddress("MET", PuppiMissingET_MET);
      fChain_PuppiMissingET->SetBranchAddress("Phi", PuppiMissingET_Phi);
      fChain_PuppiMissingET->SetBranchAddress("Eta", PuppiMissingET_Eta);
      fChain_PuppiMissingET->SetBranchAddress("SF", PuppiMissingET_SF);
      //fChain_PhotonLoose->SetBranchAddress("Particle", PhotonLoose_Particle);
      //fChain_PhotonLoose->SetBranchAddress("IsEB", PhotonLoose_IsEB);
      //fChain_PhotonLoose->SetBranchAddress("PT", PhotonLoose_PT);
      //fChain_PhotonLoose->SetBranchAddress("Eta", PhotonLoose_Eta);
      //fChain_PhotonLoose->SetBranchAddress("Phi", PhotonLoose_Phi);
      //fChain_PhotonLoose->SetBranchAddress("E", PhotonLoose_E);
      //fChain_PhotonLoose->SetBranchAddress("PT_multi", PhotonLoose_PT_multi);
      //fChain_PhotonLoose->SetBranchAddress("Eta_multi", PhotonLoose_Eta_multi);
      //fChain_PhotonLoose->SetBranchAddress("Phi_multi", PhotonLoose_Phi_multi);
      //fChain_PhotonLoose->SetBranchAddress("E_multi", PhotonLoose_E_multi);
      //fChain_PhotonLoose->SetBranchAddress("BDTScore", PhotonLoose_BDTScore);
      //fChain_PhotonLoose->SetBranchAddress("SF", PhotonLoose_SF);
      //fChain_PhotonTight->SetBranchAddress("Particle", PhotonTight_Particle);
      //fChain_PhotonTight->SetBranchAddress("IsEB", PhotonTight_IsEB);
      //fChain_PhotonTight->SetBranchAddress("PT", PhotonTight_PT);
      //fChain_PhotonTight->SetBranchAddress("Eta", PhotonTight_Eta);
      //fChain_PhotonTight->SetBranchAddress("Phi", PhotonTight_Phi);
      //fChain_PhotonTight->SetBranchAddress("E", PhotonTight_E);
      //fChain_PhotonTight->SetBranchAddress("PT_multi", PhotonTight_PT_multi);
      //fChain_PhotonTight->SetBranchAddress("Eta_multi", PhotonTight_Eta_multi);
      //fChain_PhotonTight->SetBranchAddress("Phi_multi", PhotonTight_Phi_multi);
      //fChain_PhotonTight->SetBranchAddress("E_multi", PhotonTight_E_multi);
      //fChain_PhotonTight->SetBranchAddress("BDTScore", PhotonTight_BDTScore);
      //fChain_PhotonTight->SetBranchAddress("SF", PhotonTight_SF);

    }

    Int_t GetEntry(Long64_t entry){
      // Read contents of entry.
      fChain_MuonLoose->GetEntry(entry);
      fChain_ElectronTight->GetEntry(entry);
      fChain_ElectronLoose->GetEntry(entry);
      // fChain_Particle->GetEntry(entry);
      fChain_ElectronMedium->GetEntry(entry);
      fChain_Vertex->GetEntry(entry);
      // fChain_GenJet->GetEntry(entry);
      fChain_MuonTight->GetEntry(entry);
      // fChain_PhotonLoose->GetEntry(entry);
      // fChain_PhotonTight->GetEntry(entry);
      fChain_JetPUPPI->GetEntry(entry);
      fChain_PuppiMissingET->GetEntry(entry);
      fChain_Event->GetEntry(entry);
      // fChain_GenPhoton->GetEntry(entry);


      return 0;
    }

    TTree *fChain_MuonLoose;
    TTree *fChain_ElectronTight;
    TTree *fChain_ElectronLoose;
    TTree *fChain_Particle;
    TTree *fChain_ElectronMedium;
    TTree *fChain_Vertex;
    TTree *fChain_GenJet;
    TTree *fChain_MuonTight;
    TTree *fChain_PhotonLoose;
    TTree *fChain_PhotonTight;
    TTree *fChain_JetPUPPI;
    TTree *fChain_PuppiMissingET;
    TTree *fChain_Event;
    TTree *fChain_GenPhoton;

    Int_t fCurrent; //!current Tree number in a TChain

     // Declaration of leave types
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


    Int_t Particle_PID[100];
    Int_t Particle_Charge[100];
    Int_t Particle_Status[100];
    Float_t Particle_P[100];
    Float_t Particle_Px[100];
    Float_t Particle_Py[100];
    Float_t Particle_Pz[100];
    Float_t Particle_E[100];
    Float_t Particle_PT[100];
    Float_t Particle_Eta[100];
    Float_t Particle_Phi[100];
    Float_t Particle_Mass[100];
    Float_t Particle_IsolationVar[100];
    Int_t GenPhoton_Status[100];
    Float_t GenPhoton_P[100];
    Float_t GenPhoton_Px[100];
    Float_t GenPhoton_Py[100];
    Float_t GenPhoton_Pz[100];
    Float_t GenPhoton_E[100];
    Float_t GenPhoton_PT[100];
    Float_t GenPhoton_Eta[100];
    Float_t GenPhoton_Phi[100];
    Float_t Vertex_SumPT2[100];
    Float_t GenJet_PT[100];
    Float_t GenJet_Eta[100];
    Float_t GenJet_Phi[100];
    Float_t GenJet_Mass[100];
    Int_t ElectronLoose_Charge[100];
    Int_t ElectronLoose_Particle[100];
    Float_t ElectronLoose_PT[100];
    Float_t ElectronLoose_Eta[100];
    Float_t ElectronLoose_Phi[100];
    Float_t ElectronLoose_Mass[100];
    Float_t ElectronLoose_IsolationVar[100];
    Float_t ElectronLoose_BDTScore[100];
    Float_t ElectronLoose_SF[100];
    Int_t ElectronMedium_Charge[100];
    Int_t ElectronMedium_Particle[100];
    Float_t ElectronMedium_PT[100];
    Float_t ElectronMedium_Eta[100];
    Float_t ElectronMedium_Phi[100];
    Float_t ElectronMedium_Mass[100];
    Float_t ElectronMedium_IsolationVar[100];
    Float_t ElectronMedium_BDTScore[100];
    Float_t ElectronMedium_SF[100];
    Int_t ElectronTight_Charge[100];
    Int_t ElectronTight_Particle[100];
    Float_t ElectronTight_PT[100];
    Float_t ElectronTight_Eta[100];
    Float_t ElectronTight_Phi[100];
    Float_t ElectronTight_Mass[100];
    Float_t ElectronTight_IsolationVar[100];
    Float_t ElectronTight_BDTScore[100];
    Float_t ElectronTight_SF[100];
    Int_t MuonLoose_Charge[100];
    Int_t MuonLoose_Particle[100];
    Float_t MuonLoose_PT[100];
    Float_t MuonLoose_Eta[100];
    Float_t MuonLoose_Phi[100];
    Float_t MuonLoose_Mass[100];
    Float_t MuonLoose_IsolationVar[100];
    Float_t MuonLoose_SF[100];
    Int_t MuonTight_Charge[100];
    Int_t MuonTight_Particle[100];
    Float_t MuonTight_PT[100];
    Float_t MuonTight_Eta[100];
    Float_t MuonTight_Phi[100];
    Float_t MuonTight_Mass[100];
    Float_t MuonTight_IsolationVar[100];
    Float_t MuonTight_SF[100];
    Int_t JetPUPPI_ID[100];
    Int_t JetPUPPI_GenJet[100];
    Float_t JetPUPPI_PT[100];
    Float_t JetPUPPI_Eta[100];
    Float_t JetPUPPI_Phi[100];
    Float_t JetPUPPI_Mass[100];
    Int_t JetPUPPI_MVAv2[100];
    Int_t JetPUPPI_DeepCSV[100];
    Int_t JetPUPPI_PartonFlavor[100];
    Int_t JetPUPPI_HadronFlavor[100];
    Int_t JetPUPPI_GenPartonPID[100];
    Float_t JetPUPPI_SF[100];
    Float_t PuppiMissingET_MET[100];
    Float_t PuppiMissingET_Phi[100];
    Float_t PuppiMissingET_Eta[100];
    Float_t PuppiMissingET_SF[100];
    Int_t PhotonLoose_Particle[100];
    Int_t PhotonLoose_IsEB[100];
    Float_t PhotonLoose_PT[100];
    Float_t PhotonLoose_Eta[100];
    Float_t PhotonLoose_Phi[100];
    Float_t PhotonLoose_E[100];
    Float_t PhotonLoose_PT_multi[100];
    Float_t PhotonLoose_Eta_multi[100];
    Float_t PhotonLoose_Phi_multi[100];
    Float_t PhotonLoose_E_multi[100];
    Float_t PhotonLoose_BDTScore[100];
    Float_t PhotonLoose_SF[100];
    Int_t PhotonTight_Particle[100];
    Int_t PhotonTight_IsEB[100];
    Float_t PhotonTight_PT[100];
    Float_t PhotonTight_Eta[100];
    Float_t PhotonTight_Phi[100];
    Float_t PhotonTight_E[100];
    Float_t PhotonTight_PT_multi[100];
    Float_t PhotonTight_Eta_multi[100];
    Float_t PhotonTight_Phi_multi[100];
    Float_t PhotonTight_E_multi[100];
    Float_t PhotonTight_BDTScore[100];
    Float_t PhotonTight_SF[100];


    // List of branches
/*
    TBranch *b_Run; //!
    TBranch *b_Event; //!
    TBranch *b_Lumi; //!
    TBranch *b_Weight_size; //!
    TBranch *b_Weight; //!
    TBranch *b_Particle_size; //!
    TBranch *b_GenPhoton_size; //!
    TBranch *b_Vertex_size; //!
    TBranch *b_GenJet_size; //!
    TBranch *b_ElectronLoose_size; //!
    TBranch *b_ElectronMedium_size; //!
    TBranch *b_ElectronTight_size; //!
    TBranch *b_MuonLoose_size; //!
    TBranch *b_MuonTight_size; //!
    TBranch *b_JetPUPPI_size; //!
    TBranch *b_PuppiMissingET_size; //!
    TBranch *b_PhotonLoose_size; //!
    TBranch *b_PhotonTight_size; //!


    TBranch *b_Particle_PID; //!
    TBranch *b_Particle_Charge; //!
    TBranch *b_Particle_Status; //!
    TBranch *b_Particle_P; //!
    TBranch *b_Particle_Px; //!
    TBranch *b_Particle_Py; //!
    TBranch *b_Particle_Pz; //!
    TBranch *b_Particle_E; //!
    TBranch *b_Particle_PT; //!
    TBranch *b_Particle_Eta; //!
    TBranch *b_Particle_Phi; //!
    TBranch *b_Particle_Mass; //!
    TBranch *b_Particle_IsolationVar; //!
    TBranch *b_GenPhoton_Status; //!
    TBranch *b_GenPhoton_P; //!
    TBranch *b_GenPhoton_Px; //!
    TBranch *b_GenPhoton_Py; //!
    TBranch *b_GenPhoton_Pz; //!
    TBranch *b_GenPhoton_E; //!
    TBranch *b_GenPhoton_PT; //!
    TBranch *b_GenPhoton_Eta; //!
    TBranch *b_GenPhoton_Phi; //!
    TBranch *b_Vertex_SumPT2; //!
    TBranch *b_GenJet_PT; //!
    TBranch *b_GenJet_Eta; //!
    TBranch *b_GenJet_Phi; //!
    TBranch *b_GenJet_Mass; //!
    TBranch *b_ElectronLoose_Charge; //!
    TBranch *b_ElectronLoose_Particle; //!
    TBranch *b_ElectronLoose_PT; //!
    TBranch *b_ElectronLoose_Eta; //!
    TBranch *b_ElectronLoose_Phi; //!
    TBranch *b_ElectronLoose_Mass; //!
    TBranch *b_ElectronLoose_IsolationVar; //!
    TBranch *b_ElectronLoose_BDTScore; //!
    TBranch *b_ElectronLoose_SF; //!
    TBranch *b_ElectronMedium_Charge; //!
    TBranch *b_ElectronMedium_Particle; //!
    TBranch *b_ElectronMedium_PT; //!
    TBranch *b_ElectronMedium_Eta; //!
    TBranch *b_ElectronMedium_Phi; //!
    TBranch *b_ElectronMedium_Mass; //!
    TBranch *b_ElectronMedium_IsolationVar; //!
    TBranch *b_ElectronMedium_BDTScore; //!
    TBranch *b_ElectronMedium_SF; //!
    TBranch *b_ElectronTight_Charge; //!
    TBranch *b_ElectronTight_Particle; //!
    TBranch *b_ElectronTight_PT; //!
    TBranch *b_ElectronTight_Eta; //!
    TBranch *b_ElectronTight_Phi; //!
    TBranch *b_ElectronTight_Mass; //!
    TBranch *b_ElectronTight_IsolationVar; //!
    TBranch *b_ElectronTight_BDTScore; //!
    TBranch *b_ElectronTight_SF; //!
    TBranch *b_MuonLoose_Charge; //!
    TBranch *b_MuonLoose_Particle; //!
    TBranch *b_MuonLoose_PT; //!
    TBranch *b_MuonLoose_Eta; //!
    TBranch *b_MuonLoose_Phi; //!
    TBranch *b_MuonLoose_Mass; //!
    TBranch *b_MuonLoose_IsolationVar; //!
    TBranch *b_MuonLoose_SF; //!
    TBranch *b_MuonTight_Charge; //!
    TBranch *b_MuonTight_Particle; //!
    TBranch *b_MuonTight_PT; //!
    TBranch *b_MuonTight_Eta; //!
    TBranch *b_MuonTight_Phi; //!
    TBranch *b_MuonTight_Mass; //!
    TBranch *b_MuonTight_IsolationVar; //!
    TBranch *b_MuonTight_SF; //!
    TBranch *b_JetPUPPI_ID; //!
    TBranch *b_JetPUPPI_GenJet; //!
    TBranch *b_JetPUPPI_PT; //!
    TBranch *b_JetPUPPI_Eta; //!
    TBranch *b_JetPUPPI_Phi; //!
    TBranch *b_JetPUPPI_Mass; //!
    TBranch *b_JetPUPPI_MVAv2; //!
    TBranch *b_JetPUPPI_DeepCSV; //!
    TBranch *b_JetPUPPI_PartonFlavor; //!
    TBranch *b_JetPUPPI_HadronFlavor; //!
    TBranch *b_JetPUPPI_GenPartonPID; //!
    TBranch *b_JetPUPPI_SF; //!
    TBranch *b_PuppiMissingET_MET; //!
    TBranch *b_PuppiMissingET_Phi; //!
    TBranch *b_PuppiMissingET_Eta; //!
    TBranch *b_PuppiMissingET_SF; //!
    TBranch *b_PhotonLoose_Particle; //!
    TBranch *b_PhotonLoose_IsEB; //!
    TBranch *b_PhotonLoose_PT; //!
    TBranch *b_PhotonLoose_Eta; //!
    TBranch *b_PhotonLoose_Phi; //!
    TBranch *b_PhotonLoose_E; //!
    TBranch *b_PhotonLoose_PT_multi; //!
    TBranch *b_PhotonLoose_Eta_multi; //!
    TBranch *b_PhotonLoose_Phi_multi; //!
    TBranch *b_PhotonLoose_E_multi; //!
    TBranch *b_PhotonLoose_BDTScore; //!
    TBranch *b_PhotonLoose_SF; //!
    TBranch *b_PhotonTight_Particle; //!
    TBranch *b_PhotonTight_IsEB; //!
    TBranch *b_PhotonTight_PT; //!
    TBranch *b_PhotonTight_Eta; //!
    TBranch *b_PhotonTight_Phi; //!
    TBranch *b_PhotonTight_E; //!
    TBranch *b_PhotonTight_PT_multi; //!
    TBranch *b_PhotonTight_Eta_multi; //!
    TBranch *b_PhotonTight_Phi_multi; //!
    TBranch *b_PhotonTight_E_multi; //!
    TBranch *b_PhotonTight_BDTScore; //!
    TBranch *b_PhotonTight_SF; //!

*/
};

#endif
