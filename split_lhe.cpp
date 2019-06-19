

/*
root -l -b -q "split_lhe.cpp(\"/afs/cern.ch/work/p/perfilov/public/fcnc/lhc_fcnc_14tev_kc.lhe\", \"/afs/cern.ch/work/p/pmandrik/tdr_tqgamma/delphy_samples/kc_split\", 10000)"
root -l -b -q "split_lhe.cpp(\"/afs/cern.ch/work/p/perfilov/public/fcnc/lhc_fcnc_14tev_ku.lhe\", \"/afs/cern.ch/work/p/pmandrik/tdr_tqgamma/delphy_samples/ku_split\", 10000)"
*/

void split_lhe(string input_file_name="input.lhe", string out_file_path=".", int events_per_file=1000){
  cout << "split_lhe() ... begin " << endl;
  FILE * fd = fopen(input_file_name.c_str(), "r");
  if(fd == NULL){
    cout << "cant open file " << input_file_name << endl; 
    return;
  }
  FILE * outfile = fopen ( (out_file_path + "/" + "splitLHE0.lhe").c_str() ,"w");
  if(outfile == NULL){
    cout << "cant open out file " << (out_file_path + "/" + "splitLHE0.lhe") << endl; 
    return;
  }

  int nfile = 0, events = 0; 
  char * line = NULL;
  size_t len = 0;
  size_t read;

  bool in_header = true;
  bool in_footer = false;
  string headLines, footLines;

  const char * tag;

  while((read = getline(&line, &len, fd)) != -1) {
    if(in_footer) footLines += line;
    else if( in_header ){
      headLines += line;
      if(strstr(line, "</init>") == NULL) continue;
      in_header = false;
      fputs(headLines.c_str(), outfile);
    }
    else {
      tag = strstr(line, "</LesHouchesEvents>");
      if(tag != NULL){
        in_footer  = true;
        footLines += line;
        continue;
      }

      fputs(line, outfile);
      tag = strstr(line, "</event>");
      if(tag == NULL) continue;
      events++;
      if(events >= events_per_file){
        cout << "finished file #" << nfile << endl;
        // open new file and write header
        fclose(outfile);
        nfile++;
        outfile = fopen ( (out_file_path + "/" + "splitLHE" + to_string(nfile) + ".lhe").c_str() ,"w");
        fputs(headLines.c_str(), outfile);
        events=0;
      }
    }
  }

  //cout << "add footer everywherer " << headLines << "----------" << footLines << endl;
  // add footer everywherer
  ofstream ofile;
  for(int i = 0; i <= nfile; i++){
    ofile.open( (out_file_path + "/" + "splitLHE" + to_string(i) + ".lhe").c_str(), std::ofstream::out | std::ofstream::app);
    ofile << footLines;
    ofile.close();
  }
}


