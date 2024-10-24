#include <iostream>
#include <string>
#include <limits>
#include <stack>
#include <queue>
#include <cmath>
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

Alumni* mergeSorted(Alumni* left, Alumni* right) {
    if (!left) return right;
    if (!right) return left;

    if (left->id < right->id) {
        left->next = mergeSorted(left->next, right);
        return left;
    } else {
        right->next = mergeSorted(left, right->next);
        return right;
    }
}

Alumni* mergeSort(Alumni* head) {
    if (!head || !head->next) {
        return head;
    }

    Alumni* slow = head;
    Alumni* fast = head->next;

    while (fast && fast->next) {
        slow = slow->next;
        fast = fast->next->next;
    }

    Alumni* mid = slow->next;
    slow->next = nullptr;

    Alumni* left = mergeSort(head);
    Alumni* right = mergeSort(mid);

    return mergeSorted(left, right);
}

void sortAlumniAscending() {
    head = mergeSort(head);
    operationHistory.push("Sort Alumni Ascending by ID (Merge Sort)");
    cout << "Data alumni berhasil diurutkan secara ascending berdasarkan ID!" << endl;
    tampilkanAlumni();
}

int jumpSearch(int id) {
    int step = sqrt(id); 
    Alumni* temp = head;
    int count = 0;

    while (temp != nullptr && count < step && temp->id < id) {
        for (int i = 0; i < step && temp != nullptr; ++i) {
            temp = temp->next;
            count++;
        }
    }

    Alumni* prev = head;
    for (int i = 0; i < count && prev != nullptr; ++i) {
        prev = prev->next;
    }

    while (prev != nullptr && prev->id < id) {
        prev = prev->next;
    }

    if (prev != nullptr && prev->id == id) {
        cout << "Data alumni dengan ID " << id << " ditemukan:" << endl;
        cout << "Nama: " << prev->nama << endl;
        return prev->id;
    }

    cout << "Alumni dengan ID " << id << " tidak ditemukan." << endl;
    return -1;
}

int fibonacciSearch(int id) {
    int fibMMm2 = 0;  
    int fibMMm1 = 1;  
    int fibM = fibMMm2 + fibMMm1;
    
    int n = 0;
    Alumni* temp = head;
    while (temp != nullptr) { 
        n++;
        temp = temp->next;
    }
    
    while (fibM < n) {
        fibMMm2 = fibMMm1;
        fibMMm1 = fibM;
        fibM = fibMMm2 + fibMMm1;
    }
    
    int offset = -1;
    Alumni* current = head;

    while (fibM > 1) {
        int i = min(offset + fibMMm2, n - 1);
        Alumni* curr = head;
        for (int j = 0; j < i && curr != nullptr; j++) {
            curr = curr->next;
        }

        if (curr == nullptr || curr->id < id) {
            fibM = fibMMm1;
            fibMMm1 = fibMMm2;
            fibMMm2 = fibM - fibMMm1;
            offset = i;
        } else if (curr->id > id) {
            fibM = fibMMm2;
            fibMMm1 = fibMMm1 - fibMMm2;
            fibMMm2 = fibM - fibMMm1;
        } else {
            cout << "Data alumni dengan ID " << id << " ditemukan:" << endl;
            cout << "Nama: " << curr->nama << endl;
            return curr->id;
        }
    }

    cout << "Alumni dengan ID " << id << " tidak ditemukan." << endl;
    return -1;
}

void computeBadChar(string str, int size, int badchar[256]) {
    for (int i = 0; i < 256; i++)
        badchar[i] = -1;
    
    for (int i = 0; i < size; i++)
        badchar[(int) str[i]] = i;
}

void boyerMooreSearch(string pattern) {
    bool found = false;
    int m = pattern.size();
    int badchar[256];
    
    computeBadChar(pattern, m, badchar);
    
    Alumni* curr = head;
    while (curr != nullptr) {
        string text = curr->nama;
        int n = text.size();
        
        int s = 0;
        while (s <= (n - m)) {
            int j = m - 1;
            
            while (j >= 0 && pattern[j] == text[s + j])
                j--;
                
            if (j < 0) {
                cout << "Alumni ditemukan:" << endl;
                cout << "ID: " << curr->id << endl;
                cout << "Nama: " << curr->nama << endl;
                cout << "----------------------------" << endl;
                found = true;
                s += (s + m < n)? m - badchar[text[s + m]] : 1;
            }
            else
                s += max(1, j - badchar[text[s + j]]);
        }
        curr = curr->next;
    }
    
    if (!found) {
        cout << "Alumni dengan nama mengandung '" << pattern << "' tidak ditemukan." << endl;
    }
}

int main() {
    int pilihan;
    do {
        cout << "===== MENU =====" << endl;
        cout << "1. Tambah Alumni" << endl;
        cout << "2. Tampilkan Alumni" << endl;
        cout << "3. Update Alumni" << endl;
        cout << "4. Hapus Alumni" << endl;
        cout << "5. Undo Hapus" << endl;
        cout << "6. Riwayat Operasi" << endl;
        cout << "7. Verifikasi Alumni" << endl;
        cout << "8. Sortir Alumni (Ascending)" << endl;
        cout << "9. Pencarian Alumni (Jump Search)" << endl;
        cout << "10. Pencarian Alumni (Fibonacci Search)" << endl; 
        cout << "0. Keluar" << endl;
        cout << "Pilih: ";
        cin >> pilihan;
        cin.ignore();

        switch (pilihan) {
            case 1: tambahAlumni(); break;
            case 2: tampilkanAlumni(); break;
            case 3: updateAlumni(); break;
            case 4: hapusAlumni(); break;
            case 5: undo(); break;
            case 6: tampilkanHistory(); break;
            case 7: verifikasiAlumni(); break;
            case 8: sortAlumniAscending(); break;
            case 9: {
                int id;
                cout << "Masukkan ID untuk pencarian (Jump Search): ";
                cin >> id;
                jumpSearch(id);
                break;
            }
            case 10: { 
                int id;
                cout << "Masukkan ID untuk pencarian (Fibonacci Search): ";
                cin >> id;
                fibonacciSearch(id);
                break;
            }
            case 0: cout << "TERIMA KASIH SUDAH MENGGUNAKAN PROGRAM INI." << endl; break;
            default: cout << "Pilihan tidak valid." << endl;
        }
    } while (pilihan != 0);

    return 0;
}
