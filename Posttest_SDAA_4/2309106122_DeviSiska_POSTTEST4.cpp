#include <iostream>
#include <string>
#include <limits>
#include <stack>
#include <queue>
#include <algorithm>

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
stack<string> operationHistory; 
stack<Alumni*> deletedAlumni;   
queue<Alumni*> verifikasiQueue; 

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

string inputTanggalLahir() {
    string tanggal;
    while (true) {
        cout << "Masukkan Tanggal Lahir (DD/MM/YYYY): ";
        getline(cin, tanggal);
        if (tanggal.length() == 10 && tanggal[2] == '/' && tanggal[5] == '/') {
            return tanggal;
        } else {
            cout << "Format tanggal tidak valid. Coba lagi." << endl;
        }
    }
}

string inputTahunLulus() {
    string tahun;
    while (true) {
        cout << "Masukkan Tahun Lulus: ";
        getline(cin, tahun);
        if (tahun.length() == 4 && all_of(tahun.begin(), tahun.end(), ::isdigit)) {
            return tahun;
        } else {
            cout << "Tahun lulus harus 4 digit angka." << endl;
        }
    }
}

void tambahAlumni() {
    Alumni* newAlumni = new Alumni;
    newAlumni->id = inputID();

    cout << "Masukkan Nama: ";
    getline(cin, newAlumni->nama);

    newAlumni->tanggalLahir = inputTanggalLahir();
    newAlumni->tahunLulus = inputTahunLulus();

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

    verifikasiQueue.push(newAlumni);
    operationHistory.push("Tambah Alumni: " + newAlumni->nama);

    cout << "Alumni berhasil ditambahkan dan sedang dalam antrean verifikasi!" << endl;
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

            temp->tanggalLahir = inputTanggalLahir();
            temp->tahunLulus = inputTahunLulus();

            cout << "Masukkan Jurusan baru: ";
            getline(cin, temp->jurusan);

            for (int j = 0; j < 2; j++) {
                cout << "Masukkan Prestasi baru " << j + 1 << ": ";
                getline(cin, temp->prestasi[j]);
            }

            operationHistory.push("Update Alumni: " + temp->nama);

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
            operationHistory.push("Hapus Alumni: " + temp->nama);
            deletedAlumni.push(temp); 
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

void undo() {
    if (!deletedAlumni.empty()) {
        Alumni* restoredAlumni = deletedAlumni.top();
        deletedAlumni.pop();

        if (head == nullptr) {
            head = restoredAlumni;
            restoredAlumni->next = nullptr;
        } else {
            Alumni* temp = head;
            while (temp->next != nullptr) {
                temp = temp->next;
            }
            temp->next = restoredAlumni;
            restoredAlumni->next = nullptr;
        }
        operationHistory.push("Undo: Mengembalikan Alumni " + restoredAlumni->nama);
        cout << "Alumni berhasil dikembalikan." << endl;
    } else {
        cout << "Tidak ada alumni yang bisa di-undo." << endl;
    }
}

void tampilkanHistory() {
    if (operationHistory.empty()) {
        cout << "Tidak ada riwayat operasi." << endl;
    } else {
        cout << "Riwayat Operasi:" << endl;
        stack<string> tempStack(operationHistory);
        while (!tempStack.empty()) {
            cout << tempStack.top() << endl;
            tempStack.pop();
        }
    }
}

void verifikasiAlumni() {
    if (verifikasiQueue.empty()) {
        cout << "Tidak ada alumni yang menunggu verifikasi." << endl;
    } else {
        cout << "Memverifikasi alumni berikut:" << endl;
        while (!verifikasiQueue.empty()) {
            Alumni* alumni = verifikasiQueue.front();
            cout << "- " << alumni->nama << " (ID: " << alumni->id << ")" << endl;
            verifikasiQueue.pop();
        }
    }
}

void tampilkanMenu() {
    cout << "=== Sistem Manajemen Data Alumni Sekolah ===" << endl;
    cout << "1. Tambah Alumni" << endl;
    cout << "2. Tampilkan Semua Alumni" << endl;
    cout << "3. Update Alumni Berdasarkan ID" << endl;
    cout << "4. Hapus Alumni Berdasarkan ID" << endl;
    cout << "5. Lihat Riwayat Operasi" << endl;
    cout << "6. Verifikasi Alumni" << endl;
    cout << "7. Undo Hapus Alumni" << endl;
    cout << "8. Keluar" << endl;
    cout << "Pilih menu: ";
}

int inputPilihanMenu() {
    int pilihan;
    while (true) {
        cin >> pilihan;
        if (cin.fail() || pilihan < 1 || pilihan > 8) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Input tidak valid. Pilih antara 1-8: ";
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
                tampilkanHistory();
                break;
            case 6:
                verifikasiAlumni();
                break;
            case 7:
                undo();
                break;
            case 8:
                cout << "Terima kasih telah menggunakan sistem ini." << endl;
                break;
            default:
                cout << "Pilihan tidak valid!" << endl;
        }
    } while (pilihan != 8);

    Alumni* current = head;
    while (current != nullptr) {
        Alumni* toDelete = current;
        current = current->next;
        delete toDelete;
    }

    return 0;
}

