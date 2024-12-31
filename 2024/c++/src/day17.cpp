#include "AOC.h"

bool check_p2(int A, vector<int> instrs) {
    vector<int> regs(3);
    regs[0] = A;

    int ip = 0;
    int outPos = 0;

    while (ip >= 0 && ip < instrs.size()) {
        int opc(instrs[ip]), arg(instrs[ip + 1]);
        if (4 <= arg && arg <= 6) {
            arg = regs[arg - 4];
        }
        switch (opc) {
            case 0:
                regs[0] >>= arg;
                break;
            case 1:
                regs[1] ^= arg;
                break;
            case 2:
                regs[1] = arg % 8;
                break;
            case 3:
                if (regs[0]) {
                    ip = arg;
                    ip -= 2;  // counteract final +2
                }
                break;
            case 4:
                regs[1] ^= regs[2];
                break;
            case 5:
                if (outPos >= instrs.size() || (arg % 8) != instrs[outPos]) {
                    return false;
                }
                outPos++;
                break;
            case 6:
                regs[1] = regs[0] >> arg;
                break;
            case 7:
                regs[2] = regs[0] >> arg;
                break;
        }
        ip += 2;
    }
    return outPos == instrs.size();
}

void hardcoded(int A) {
    int B(0), C(0);
    while (A) {
        // 2 4 (bst A) B = A%8
        cout << A << ", " << B << ", " << C << endl;
        B = A % 8;
        // 1 2 (bxl 2) B ^= 2
        cout << A << ", " << B << ", " << C << endl;
        B ^= 2;
        // 7 5 (cdv B) C = A >> B
        cout << A << ", " << B << ", " << C << endl;
        C = A >> B;
        // 4 5 (bxc B) B ^= C
        cout << A << ", " << B << ", " << C << endl;
        B ^= C;
        // 0 3 (adv 3) A >>= 3
        cout << A << ", " << B << ", " << C << endl;
        A >>= 3;
        // 1 7 (bxl 7) B ^= 7 ?
        cout << A << ", " << B << ", " << C << endl;
        B ^= 7;
        // 5 5 (out B) out B % 8
        cout << A << ", " << B << ", " << C << endl;
        cout << B % 8 << "(" << B << "%8)" << endl;
        // 3 0 (jnz A) if A : ip = 0
    }
}

chrono::time_point<std::chrono::steady_clock> day17(input_t& inp) {
    int p2(0);
    string p1 = "";
    vector<int> regs(3), instrs;

    for (int i = 0; i < 3; i++) {
        regs[i] = stoi(inp[i].substr(12));
    }

    char t;
    string tmp;
    stringstream ss(inp.back());
    ss >> tmp;
    while (ss) {
        int inst;
        ss >> inst >> t;
        instrs.push_back(inst);
    }
    int ip = 0;
    while (ip >= 0 && ip < instrs.size()) {
        int opc(instrs[ip]), arg(instrs[ip + 1]);
        // cout << opc << ", " << arg << '\t' << regs << endl;
        if (4 <= arg && arg <= 6) {
            arg = regs[arg - 4];
        }
        switch (opc) {
            case 0:
                regs[0] >>= arg;
                break;
            case 1:
                regs[1] ^= arg;
                break;
            case 2:
                regs[1] = arg % 8;
                break;
            case 3:
                if (regs[0]) {
                    ip = arg;
                    ip -= 2;  // counteract final +2
                }
                break;
            case 4:
                regs[1] ^= regs[2];
                break;
            case 5:
                p1 += to_string(arg % 8);
                p1 += ",";
                break;
            case 6:
                regs[1] = regs[0] >> arg;
                break;
            case 7:
                regs[2] = regs[0] >> arg;
                break;
        }
        ip += 2;
    }
    p1.pop_back();

    // while (!check_p2(p2, instrs)) {
    //     p2++;
    // }
    // hardcoded(128);
    // p2: 190384615275535

    auto done = chrono::steady_clock::now();
    cout << "[P1] " << p1 << "\n[P2] " << 190384615275535 << endl;
    return done;
}

/**
 * 2 4 (bst A) B = A%8
 * 1 2 (bxl 2) B ^= 2
 * 7 5 (cdv B) C = A >> B
 * 4 5 (bxc B) B ^= C
 * 0 3 (adv 3) A >>= 3
 * 1 7 (bxl 7) B ^= 7 ?
 * 5 5 (out C) out C % 8
 * 3 0 (jnz A) if A : ip = 0
 */