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

    while (!check_p2(p2, instrs)) {
        p2++;
    }

    auto done = chrono::steady_clock::now();
    cout << "[P1] " << p1 << "\n[P2] " << p2 << endl;
    return done;
}