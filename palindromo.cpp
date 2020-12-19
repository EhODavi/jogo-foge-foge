#include <iostream>
#include <cstring>

using namespace std;

bool ehpalindromo(char fraseA[]) {

    char fraseB[50];

    int i, j;

    j = 0;
    for (i = strlen(fraseA) - 1; i >= 0; i--) {
        fraseB[j] = fraseA[i];
        j++;
    }
    fraseB[j] = '\0';

    i = 0;
    j = 0;

    while (fraseA[i] != '\0' && fraseB[j] != '\0') {
        if (!isalnum(fraseA[i])) {
            i++;
            continue;
        }

        if (!isalnum(fraseB[j])) {
            j++;
            continue;
        }

        if (tolower(fraseA[i]) != tolower(fraseB[j])) return false;

        i++;
        j++;

    }

    return true;
}

int main() {

    char fraseA[50];

    cin.getline(fraseA, 50);

    if (ehpalindromo(fraseA)) {
        cout << "EH PALINDROMO!\n";
    } else {
        cout << "NAO EH PALINDROMO!\n";
    }

    return 0;
}
