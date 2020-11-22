void fermi(){

   TF1 *fermi = new TF1("fermi","1/(1+exp((20-x)/0.1))", 0, 250);
   fermi->Draw();

}
