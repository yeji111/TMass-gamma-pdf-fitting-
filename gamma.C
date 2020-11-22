void gamma(){
  
//  TF1 *f = new TF1("f1","TMath::GammaDist(x,1.+(0.778-0.0004424*[0]),0.,(5.014+0.1335*[0]))(1+exp((20-x)/0.1))",0,250);
  TF1 *f = new TF1("f1","TMath::GammaDist(x,1.+[0],20.,[1])(1+exp((20-x)/0.1))",0,250);
  f->Draw();
}
