#include "AOC.h"

chrono::time_point<std::chrono::steady_clock> day01(input_t &inp)
{
	int p1(0), p2(0);
	vector<int> l1, l2;
	int a, b;
	for (auto &line : inp)
	{
		sscanf(line.c_str(), "%d %d", &a, &b);
		l1.push_back(a);
		l2.push_back(b);
	}
	sort(l1.begin(), l1.end());
	sort(l2.begin(), l2.end());
	for (int i = 0; i < l1.size(); i++)
	{
		p1 += abs(l2[i] - l1[i]);
		for (int j = 0; j < l2.size(); j++)
		{
			if (l2[j] == l1[i])
			{
				p2 += l2[j];
			}
		}
	}
	auto done = chrono::steady_clock::now();
	cout << "[P1] " << p1 << "\n[P2] " << p2 << endl;
	return done;
}