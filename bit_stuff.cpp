#include <bits/stdc++.h>
using namespace std;

// Bit Stuffing - Sender
string bit_stuff_sender(string data) {
    string stuffed = "";
    int ones = 0;

    for (int i = 0; i < data.size(); i++) {
        stuffed += data[i];

        if (data[i] == '1') {
            ones++;

            if (ones == 5) {
                stuffed += '0';  // Insert 0
                ones = 0;
            }
        }
        else {
            ones = 0;
        }
    }

    return stuffed;
}

// Bit Stuffing - Receiver
string bit_stuff_receiver(string stuffed) {
    string original = "";
    int ones = 0;
    int i = 0;

    while (i < stuffed.size()) {
        original += stuffed[i];

        if (stuffed[i] == '1') {
            ones++;

            if (ones == 5) {
                i++;  // Skip stuffed 0
                ones = 0;
            }
        }
        else {
            ones = 0;
        }

        i++;
    }

    return original;
}

// Add FLAG to beginning and end
string add_frame(string data) {
    string FLAG = "01111110";

    string stuffed = bit_stuff_sender(data);

    return FLAG + stuffed + FLAG;
}

// Remove FLAG and perform unstuffing
string remove_frame(string frame) {
    string FLAG = "01111110";

    int flag_len = FLAG.size();
    int frame_len = frame.size();

    // Check flags
    if (frame.substr(0, flag_len) != FLAG ||
        frame.substr(frame_len - flag_len) != FLAG) {

        cout << "Error: Invalid frame!\n";
        return "";
    }

    // Extract data without flags
    string temp = frame.substr(flag_len, frame_len - 2 * flag_len);

    return bit_stuff_receiver(temp);
}

int main() {

    string data;

    cout << "Enter binary data: ";
    cin >> data;

    cout << "\n[1] ORIGINAL DATA:\n";
    cout << data << endl;

    // Sender adds flags and stuffs bits
    string frame = add_frame(data);

    cout << "\n[2] AFTER BIT STUFFING (Sender):\n";
    cout << frame << endl;

    // Receiver removes flags and unstuffs bits
    string recovered = remove_frame(frame);

    cout << "\n[3] AFTER BIT UNSTUFFING (Receiver):\n";
    cout << recovered << endl;

    // Verify
    if (data == recovered) {
        cout << "\nSUCCESS: Original data recovered!\n";
    }
    else {
        cout << "\nERROR: Data mismatch!\n";
    }

    return 0;
}