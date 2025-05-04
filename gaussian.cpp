void gaussian() {
    // ファイルを開く
    std::string filename = "7_80deg_3mm";
    std::ifstream infile(("./dat/" + filename + ".dat").c_str());

    // データ格納用ベクトル
    std::vector<double> pc;
    std::vector<double> entry;

    // データ読み込み
    double x, y;
    while (infile >> x >> y) {
        pc.push_back(x);
        entry.push_back(y);
    }

    infile.close();

    // ビン幅を推定（等間隔であると仮定）
    double width = pc[1] - pc[0];
    int nbins = pc.size();

    // ヒストグラム作成
    double xmin = pc[0] - width / 2.0;
    double xmax = pc[nbins - 1] + width / 2.0;
    TH1D* h = new TH1D("h", "Gaussian Fit", nbins, xmin, xmax);

    // ヒストグラムに値を入れる
    for (int i = 0; i < nbins; ++i) {
        h->SetBinContent(i + 1, entry[i]);
    }

    // 描画とフィット
    TCanvas* c = new TCanvas("c", "", 800, 600);
    h->GetXaxis()->SetTitle("charge [pC]");
    h->GetYaxis()->SetTitle("entries");
    h->SetLineColor(kBlue);
    h->Draw();

    // ガウシアン関数を定義してフィット
    TF1* gaus = new TF1("gaus", "gaus", 0, 400);
    gaus->SetParameters(100.0, 300.0, 50.0); //振幅、中心、幅
    h->Fit(gaus, "R");  // "R" は範囲を指定するオプション
    // gStyle->SetOptStat(1111);   // フィットパラメータ（mean, sigma, χ²など）を表示
    gStyle->SetOptFit(1111);

    // 出力を表示
    c->Update();
    c->Draw();
    c->SaveAs(("./datpic/" + filename + "_fit.png").c_str());
}