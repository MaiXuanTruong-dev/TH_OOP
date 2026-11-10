#include <iostream>
#include <string>
#include <iomanip>
#include <limits>
#include <cstdlib>
#include <ctime>
using namespace std;
int nhap_so(const string& thong_bao, int nho_nhat, int lon_nhat) {
    int x;
    while (true) {
        cout << thong_bao;
        cin >> x;
        if (cin.fail()) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "  [!] Vui long nhap so nguyen hop le!\n";
            continue;
        }
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        if (x < nho_nhat || x > lon_nhat) {
            cout << "  [!] Gia tri phai nam trong khoang " << nho_nhat << " - " << lon_nhat << "!\n";
            continue;
        }
        return x;
    }
}

char nhap_kich_thuoc() {
    string s;
    while (true) {
        cout << "Kich thuoc (S/M/L): ";
        cin >> s;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        if (s.size() == 1) {
            char c = (char)toupper((unsigned char)s[0]);
            if (c == 'S' || c == 'M' || c == 'L') return c;
        }
        cout << "  [!] Chi chap nhan S, M hoac L!\n";
    }
}

string nhap_loai_xe(const string& thong_bao) {
    string s;
    while (true) {
        cout << thong_bao;
        cin >> s;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        if (s == "Car" || s == "Motorcycle" || s == "Bicycle") return s;
        cout << "  [!] Chi chap nhan Car, Motorcycle hoac Bicycle!\n";
    }
}

class phuong_tien {
private:
    int ma_xe;
    string loai_xe;
    int gio_vao;
    int tg_do;
    double phi;         

    void cap_nhat_phi();

public:
    phuong_tien();
    phuong_tien(int ma, string loai, int gio, int tg);

    int lay_ma_xe() const;
    string lay_loai_xe() const;
    int lay_gio_vao() const;
    int lay_tg_do() const;
    double lay_phi() const;

    void dat_ma_xe(int ma);
    void dat_loai_xe(string loai);
    void dat_gio_vao(int gio);
    void dat_tg_do(int tg);

    double tinh_phi() const;
    void hien_thi() const;
};

phuong_tien::phuong_tien() : ma_xe(0), loai_xe(""), gio_vao(0), tg_do(0), phi(0) {}

phuong_tien::phuong_tien(int ma, string loai, int gio, int tg)
    : ma_xe(ma), loai_xe(loai), gio_vao(gio), tg_do(tg), phi(0) {
    cap_nhat_phi();
}

void phuong_tien::cap_nhat_phi() { phi = tinh_phi(); }

int phuong_tien::lay_ma_xe() const { return ma_xe; }
string phuong_tien::lay_loai_xe() const { return loai_xe; }
int phuong_tien::lay_gio_vao() const { return gio_vao; }
int phuong_tien::lay_tg_do() const { return tg_do; }
double phuong_tien::lay_phi() const { return phi; }

void phuong_tien::dat_ma_xe(int ma) { ma_xe = ma; }
void phuong_tien::dat_loai_xe(string loai) { loai_xe = loai; cap_nhat_phi(); }
void phuong_tien::dat_gio_vao(int gio) { gio_vao = gio; cap_nhat_phi(); }
void phuong_tien::dat_tg_do(int tg) { tg_do = tg; cap_nhat_phi(); }

double phuong_tien::tinh_phi() const {
    double gia = (loai_xe == "Car") ? 6.0 : (loai_xe == "Motorcycle") ? 4.0 : 2.0;
    bool cao_diem = (gio_vao >= 6 && gio_vao <= 9) || (gio_vao >= 15 && gio_vao <= 18);
    double tong = 0;
    for (int h = 0; h < tg_do; ++h) {
        if (h < 2) tong += gia * (cao_diem ? 1.30 : 0.95);
        else       tong += gia * 0.90;
    }
    return tong;
}

void phuong_tien::hien_thi() const {
    cout << "  ID: " << ma_xe << " | " << loai_xe
         << " | " << gio_vao << "h | " << tg_do << "h"
         << " | Phi: $" << fixed << setprecision(2) << phi << "\n";
}

class bai_xe {
private:
    int ma_bai;
    char kich_thuoc;
    static const int MAX_XE = 3;    
    phuong_tien xe[MAX_XE];          
    int so_xe_hien_tai;   
public:
    bai_xe();
    bai_xe(int ma, char kt);

    int lay_ma() const;
    char lay_kich_thuoc() const;
    int lay_so_xe() const;
    int suc_chua() const;           
    bool da_day() const;        
    bool them(const phuong_tien& v);
    bool xoa(int ma_xe);
    int tim_chi_so(int ma_xe) const; 
    bool chua(int ma_xe) const;
    void hien_thi() const;
    bool co_loai(const string& loai, int& dem, double& tong) const;
    void hien_thi_theo_loai(const string& loai) const;
};

bai_xe::bai_xe() : ma_bai(0), kich_thuoc('S'), so_xe_hien_tai(0) {}

bai_xe::bai_xe(int ma, char kt) : ma_bai(ma), kich_thuoc(kt), so_xe_hien_tai(0) {}

int bai_xe::lay_ma() const { return ma_bai; }
char bai_xe::lay_kich_thuoc() const { return kich_thuoc; }
int bai_xe::lay_so_xe() const { return so_xe_hien_tai; }

int bai_xe::suc_chua() const {
    return (kich_thuoc == 'S') ? 1 : (kich_thuoc == 'M') ? 2 : 3;
}

bool bai_xe::da_day() const { return so_xe_hien_tai >= suc_chua(); }

bool bai_xe::them(const phuong_tien& v) {
    if (da_day()) return false;
    xe[so_xe_hien_tai] = v;
    ++so_xe_hien_tai;
    return true;
}

int bai_xe::tim_chi_so(int ma_xe) const {
    for (int i = 0; i < so_xe_hien_tai; ++i)
        if (xe[i].lay_ma_xe() == ma_xe) return i;
    return -1;
}

bool bai_xe::xoa(int ma_xe) {
    int vt = tim_chi_so(ma_xe);
    if (vt == -1) return false;
    // don mang: dich cac phan tu phia sau sang trai
    for (int i = vt; i < so_xe_hien_tai - 1; ++i)
        xe[i] = xe[i + 1];
    --so_xe_hien_tai;
    return true;
}

bool bai_xe::chua(int ma_xe) const { return tim_chi_so(ma_xe) != -1; }

void bai_xe::hien_thi() const {
    cout << "Bai " << ma_bai << " [" << kich_thuoc << "] "
         << so_xe_hien_tai << "/" << suc_chua() << " xe\n";
    for (int i = 0; i < so_xe_hien_tai; ++i)
        xe[i].hien_thi();
}

bool bai_xe::co_loai(const string& loai, int& dem, double& tong) const {
    dem = 0; tong = 0;
    for (int i = 0; i < so_xe_hien_tai; ++i) {
        if (xe[i].lay_loai_xe() == loai) {
            ++dem;
            tong += xe[i].lay_phi();
        }
    }
    return dem > 0;
}

void bai_xe::hien_thi_theo_loai(const string& loai) const {
    cout << "Bai " << ma_bai << " [" << kich_thuoc << "]\n";
    for (int i = 0; i < so_xe_hien_tai; ++i)
        if (xe[i].lay_loai_xe() == loai) xe[i].hien_thi();
}

class SystemInterface {
private:
    static const int MAX_LOTS = 10;  
    bai_xe bai_do[MAX_LOTS];         
    int so_bai;                      

public:
    SystemInterface();
    void runMenu();
    bool isParkIDExists(int pID) const;
    bool isVehicleIDExists(int vID) const;
    int generateRandomID();

private:
    int tim_bai(int pID) const;
    void tao_bai();
    void them_xe();
    void xoa_bai();
    void lay_xe_ra();
    void hien_thi_tat_ca() const;
    void hien_thi_theo_bai() const;
    void liet_ke_theo_loai() const;
    void bao_cao_phi() const;
};

SystemInterface::SystemInterface() : so_bai(0) {
    srand((unsigned)time(0));
}

bool SystemInterface::isParkIDExists(int pID) const {
    return tim_bai(pID) != -1;
}

bool SystemInterface::isVehicleIDExists(int vID) const {
    for (int i = 0; i < so_bai; ++i)
        if (bai_do[i].chua(vID)) return true;
    return false;
}

int SystemInterface::generateRandomID() {
    return rand() % 9000 + 1000;      
}

int SystemInterface::tim_bai(int pID) const {
    for (int i = 0; i < so_bai; ++i)
        if (bai_do[i].lay_ma() == pID) return i;
    return -1;
}

void SystemInterface::tao_bai() {
    if (so_bai >= MAX_LOTS) {
        cout << "Da dat toi da " << MAX_LOTS << " bai do, khong the tao them!\n";
        return;
    }
    int ma = nhap_so("Ma bai: ", 1, 2147483647);
    char kt = nhap_kich_thuoc();
    if (isParkIDExists(ma)) {
        int cu = ma;
        do { ma = generateRandomID(); } while (isParkIDExists(ma));
        cout << "Canh bao: Ma bai " << cu << " bi trung! Tu dong gan ma moi: " << ma << "\n";
    }
    bai_do[so_bai] = bai_xe(ma, kt);
    ++so_bai;
    cout << "Da tao bai " << ma << "\n";
}

void SystemInterface::them_xe() {
    if (so_bai == 0) {
        cout << "Chua co bai do nao, hay tao bai truoc!\n";
        return;
    }
    int ma = nhap_so("Ma xe: ", 1, 2147483647);
    string loai = nhap_loai_xe("Loai (Car/Motorcycle/Bicycle): ");
    int gio = nhap_so("Gio vao (0-23): ", 0, 23);
    int tg = nhap_so("Thoi luong (1-23): ", 1, 23);

    if (isVehicleIDExists(ma)) {
        int cu = ma;
        do { ma = generateRandomID(); } while (isVehicleIDExists(ma));
        cout << "Canh bao: Ma xe " << cu << " bi trung! Tu dong gan ma moi: " << ma << "\n";
    }

    phuong_tien v(ma, loai, gio, tg);
    bool ok = false;
    for (int i = 0; i < so_bai && !ok; ++i)
        ok = bai_do[i].them(v);

    if (ok) cout << "Da them xe " << ma << " | Phi: $" << fixed << setprecision(2) << v.tinh_phi() << "\n";
    else    cout << "Canh bao: Tat ca cac bai da day!\n";
}

void SystemInterface::xoa_bai() {
    int ma = nhap_so("Ma bai can xoa: ", 1, 2147483647);
    int vt = tim_bai(ma);
    if (vt == -1) {
        cout << "Khong tim thay bai " << ma << "\n";
        return;
    }
    for (int i = vt; i < so_bai - 1; ++i)
        bai_do[i] = bai_do[i + 1];
    --so_bai;
    cout << "Da xoa bai " << ma << "\n";
}

void SystemInterface::lay_xe_ra() {
    int ma = nhap_so("Ma xe can lay ra: ", 1, 2147483647);
    bool ok = false;
    for (int i = 0; i < so_bai && !ok; ++i)
        ok = bai_do[i].xoa(ma);
    cout << (ok ? "Da lay xe ra\n" : "Khong tim thay xe\n");
}

void SystemInterface::hien_thi_tat_ca() const {
    if (so_bai == 0) {
        cout << "Chua co bai do nao.\n";
        return;
    }
    for (int i = 0; i < so_bai; ++i)
        bai_do[i].hien_thi();
}

void SystemInterface::hien_thi_theo_bai() const {
    int ma = nhap_so("Ma bai: ", 1, 2147483647);
    int vt = tim_bai(ma);
    if (vt == -1) cout << "Khong tim thay bai " << ma << "\n";
    else          bai_do[vt].hien_thi();
}

void SystemInterface::liet_ke_theo_loai() const {
    string loai = nhap_loai_xe("Loai xe (Car/Motorcycle/Bicycle): ");
    bool thay = false;
    for (int i = 0; i < so_bai; ++i) {
        int dem; double tong;
        if (bai_do[i].co_loai(loai, dem, tong)) {
            bai_do[i].hien_thi_theo_loai(loai);
            thay = true;
        }
    }
    if (!thay) cout << "Khong co xe loai " << loai << "\n";
}

void SystemInterface::bao_cao_phi() const {
    string loai_arr[3] = {"Car", "Motorcycle", "Bicycle"};

    cout << "--- Toan he thong ---\n";
    for (int t = 0; t < 3; ++t) {
        int dem = 0; double tong = 0;
        for (int i = 0; i < so_bai; ++i) {
            int d; double s;
            bai_do[i].co_loai(loai_arr[t], d, s);
            dem += d; tong += s;
        }
        cout << loai_arr[t] << ": ";
        if (dem == 0) cout << "khong co xe\n";
        else cout << dem << " xe | TB: $" << fixed << setprecision(2) << tong / dem << "\n";
    }

    cout << "--- Theo tung bai ---\n";
    for (int i = 0; i < so_bai; ++i) {
        cout << "Bai " << bai_do[i].lay_ma() << ":\n";
        for (int t = 0; t < 3; ++t) {
            int d; double s;
            bai_do[i].co_loai(loai_arr[t], d, s);
            cout << "  " << loai_arr[t] << ": ";
            if (d == 0) cout << "khong co xe\n";
            else cout << d << " xe | TB: $" << fixed << setprecision(2) << s / d << "\n";
        }
    }
}

void SystemInterface::runMenu() {
    int chon;
    do {
        cout << "\n===== QUAN LY BAI DO XE =====\n";
        cout << "1. Tao bai do\n";
        cout << "2. Them xe\n";
        cout << "3. Xoa bai do\n";
        cout << "4. Lay xe ra\n";
        cout << "5. Hien thi tat ca bai do\n";
        cout << "6. Hien thi xe theo bai\n";
        cout << "7. Liet ke xe theo loai\n";
        cout << "8. Bao cao phi trung binh\n";
        cout << "9. Thoat\n";
        chon = nhap_so("Chon: ", 1, 9);

        switch (chon) {
            case 1: tao_bai();          break;
            case 2: them_xe();          break;
            case 3: xoa_bai();          break;
            case 4: lay_xe_ra();        break;
            case 5: hien_thi_tat_ca();  break;
            case 6: hien_thi_theo_bai();break;
            case 7: liet_ke_theo_loai();break;
            case 8: bao_cao_phi();      break;
            case 9: cout << "Tam biet!\n"; break;
        }
    } while (chon != 9);
}

int main() {
    SystemInterface sys;
    sys.runMenu();
    return 0;
}
