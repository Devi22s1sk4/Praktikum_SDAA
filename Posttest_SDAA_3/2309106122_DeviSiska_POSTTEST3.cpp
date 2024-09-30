#include <iostream>
#include <string>
#include <limits>
#include <sstream>

using namespace std;

struct Alumni {
    int id;                
    string nama;           
    string tanggalLahir;   
    string tahunLulus;     
    string jurusan;        
    string prestasi[2];    
    Alumni* next;  
};

Alumni* head = nullptr;

int inputTahun() {
    int tahun;
    while (true) {
        cout << "Masukkan Tahun Lulus: ";
        cin >> tahun;

        if (cin.fail() || tahun < 1900 || tahun > 2100) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Input tidak valid. Masukkan angka untuk tahun lulus yang valid (1900-2100)." << endl;
        } else {
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            return tahun;
        }
    }
}

int inputID() {
    int id;
    while (true) {
        cout << "Masukkan ID: ";
        cin >> id;

        if (cin.fail() || id <= 0) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Input tidak valid. Masukkan ID yang berupa angka positif." << endl;
        } else {
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            return id;
        }
    }
}

string convertToString(int number) {
    stringstream ss;
    ss << number;
    return ss.str();
}

void tambahAlumni() {
    Alumni* newAlumni = new Alumni;
    newAlumni->id = inputID();

    cout << "Masukkan Nama: ";
    getline(cin, newAlumni->nama);

    cout << "Masukkan Tanggal Lahir (DD/MM/YYYY): ";
    getline(cin, newAlumni->tanggalLahir);

    newAlumni->tahunLulus = convertToString(inputTahun());

    cout << "Masukkan Jurusan: ";
    getline(cin, newAlumni->jurusan);

    for (int i = 0; i < 2; i++) {
        cout << "Masukkan Prestasi " << i + 1 << ": ";
        getline(cin, newAlumni->prestasi[i]);
    }

    newAlumni->next = nullptr;

    if (head == nullptr) {
        head = newAlumni;
    } else {
        Alumni* temp = head;
        while (temp->next != nullptr) {
            temp = temp->next;
        }
        temp->next = newAlumni;
    }

    cout << "Alumni berhasil ditambahkan!" << endl;
}

void tampilkanAlumni() {
    if (head == nullptr) {
        cout << "Tidak ada data alumni." << endl;
    } else {
        cout << "Data Alumni:" << endl;
        Alumni* temp = head;
        while (temp != nullptr) {
            cout << "ID: " << temp->id << endl;
            cout << "Nama: " << temp->nama << endl;
            cout << "Tanggal Lahir: " << temp->tanggalLahir << endl;
            cout << "Tahun Lulus: " << temp->tahunLulus << endl;
            cout << "Jurusan: " << temp->jurusan << endl;
            cout << "Prestasi:" << endl;
            for (int j = 0; j < 2; j++) {
                cout << "- " << temp->prestasi[j] << endl;
            }
            cout << "----------------------------" << endl;
            temp = temp->next;
        }
    }
}

void updateAlumni() {
    int updateID = inputID();
    Alumni* temp = head;
    bool ditemukan = false;

    while (temp != nullptr) {
        if (temp->id == updateID) {
            cout << "Data Alumni Ditemukan. Masukkan data baru:" << endl;

            cout << "Masukkan Nama baru: ";
            getline(cin, temp->nama);

            cout << "Masukkan Tanggal Lahir baru (DD/MM/YYYY): ";
            getline(cin, temp->tanggalLahir);

            temp->tahunLulus = convertToString(inputTahun());

            cout << "Masukkan Jurusan baru: ";
            getline(cin, temp->jurusan);

            for (int j = 0; j < 2; j++) {
                cout << "Masukkan Prestasi baru " << j + 1 << ": ";
                getline(cin, temp->prestasi[j]);
            }

            cout << "Data Alumni berhasil diperbarui!" << endl;
            ditemukan = true;
            break;
        }
        temp = temp->next;
    }

    if (!ditemukan) {
        cout << "Alumni dengan ID " << updateID << " tidak ditemukan." << endl;
    }
}

void hapusAlumni() {
    int hapusID = inputID();
    Alumni* temp = head;
    Alumni* prev = nullptr;
    bool ditemukan = false;

    while (temp != nullptr) {
        if (temp->id == hapusID) {
            if (prev == nullptr) {
                head = temp->next;
            } else {
                prev->next = temp->next;
            }
            delete temp;
            cout << "Alumni dengan ID " << hapusID << " telah dihapus." << endl;
            ditemukan = true;
            break;
        }
        prev = temp;
        temp = temp->next;
    }

    if (!ditemukan) {
        cout << "Alumni dengan ID " << hapusID << " tidak ditemukan." << endl;
    }
}

void tampilkanMenu() {
    cout << "=== Sistem Manajemen Data Alumni Sekolah ===" << endl;
    cout << "1. Tambah Alumni" << endl;
    cout << "2. Tampilkan Semua Alumni" << endl;
    cout << "3. Update Alumni Berdasarkan ID" << endl;
    cout << "4. Hapus Alumni Berdasarkan ID" << endl;
    cout << "5. Keluar" << endl;
    cout << "Pilih menu: ";
}

int inputPilihanMenu() {
    int pilihan;
    while (true) {
        cin >> pilihan;
        if (cin.fail() || pilihan < 1 || pilihan > 5) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Input tidak valid. Pilih antara 1-5: ";
        } else {
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            return pilihan;
        }
    }
}

int main() {
    int pilihan;
    do {
        tampilkanMenu();
        pilihan = inputPilihanMenu();

        switch (pilihan) {
            case 1:
                tambahAlumni();
                break;
            case 2:
                tampilkanAlumni();
                break;
            case 3:
                updateAlumni();
                break;
            case 4:
                hapusAlumni();
                break;
            case 5:
                cout << "Terima kasih telah menggunakan sistem ini." << endl;
                break;
            default:
                cout << "Pilihan tidak valid!" << endl;
        }
    } while (pilihan != 5);

    return 0;
}

