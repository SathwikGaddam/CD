#include <bits/stdc++.h>
using namespace std;

#define FLAG 0x7E
#define ESC  0x7D

// Character Stuffing - Sender
vector<unsigned char> char_stuff_sender(vector<unsigned char>& data) {
    vector<unsigned char> stuffed;

    for (int i = 0; i < data.size(); i++) {
        if (data[i] == FLAG || data[i] == ESC) {
            stuffed.push_back(ESC);
            stuffed.push_back(data[i] ^ 0x20);
        }
        else {
            stuffed.push_back(data[i]);
        }
    }

    return stuffed;
}

// Character Stuffing - Receiver
vector<unsigned char> char_stuff_receiver(vector<unsigned char>& stuffed) {
    vector<unsigned char> data;

    int i = 0;

    while (i < stuffed.size()) {
        if (stuffed[i] == ESC) {
            i++;
            data.push_back(stuffed[i] ^ 0x20);
        }
        else {
            data.push_back(stuffed[i]);
        }

        i++;
    }

    return data;
}

// Print bytes in hexadecimal
void print_bytes(vector<unsigned char>& bytes, string label) {
    cout << label << ": ";

    for (int i = 0; i < bytes.size(); i++) {
        cout << uppercase << hex << setw(2) << setfill('0')
             << (int)bytes[i] << " ";
    }

    cout << dec << endl;
}

int main() {

    cout << "\n============================================================\n";
    cout << "CHARACTER STUFFING - C++ Implementation\n";
    cout << "============================================================\n";

    // Original data
    vector<unsigned char> original = {
        0x01, 0x7E, 0x02, 0x7D, 0x03, 0x7E, 0x04
    };

    // Print original data
    cout << "\n[1] ORIGINAL DATA:\n";
    print_bytes(original, " ");

    // Sender stuffs data
    vector<unsigned char> stuffed = char_stuff_sender(original);

    cout << "\n[2] AFTER STUFFING (Sender):\n";
    print_bytes(stuffed, " ");

    // Receiver unstuffs data
    vector<unsigned char> recovered = char_stuff_receiver(stuffed);

    cout << "\n[3] AFTER UNSTUFFING (Receiver):\n";
    print_bytes(recovered, " ");

    // Verify
    if (original == recovered) {
        cout << "\nSUCCESS: Original data recovered!\n";
    }
    else {
        cout << "\nERROR: Data mismatch!\n";
    }

    cout << "\n============================================================\n";

    return 0;
}