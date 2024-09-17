#include <iostream>
using namespace std;

int hitungNilaiPascal(int baris, int kolom) {
    if (kolom == 0 || kolom == baris) {
        return 1;
    } else {
        return hitungNilaiPascal(baris - 1, kolom - 1) + hitungNilaiPascal(baris - 1, kolom);
    }
}

void cetakSegitigaPascal(int tingkat) {
    for (int baris = 1; baris <= tingkat; ++baris) {
        for (int kolom = 0; kolom < baris; ++kolom) {
            cout << hitungNilaiPascal(baris - 1, kolom) << " ";
        }
        cout << endl;
    }
}

int main() {
    int tingkatSegitiga = 3;

    cout << "Segitiga Pascal siku-siku dengan " << tingkatSegitiga << " tingkat:" << endl;
    cetakSegitigaPascal(tingkatSegitiga);

    return 0;
}
