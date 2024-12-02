#include "AOC.h"

chrono::time_point<std::chrono::steady_clock> day02(input_t &inp)
{
	int p1(0), p2(0);

	for (auto &line : inp)
	{
		istringstream iss(line);
		vector<int> nums;
		int num;
		while (iss >> num)
			nums.push_back(num);
		bool increasing;
		bool valid = true;
		for (int i = 0; i < nums.size(); i++)
		{
			if (i == 0)
			{
				increasing = nums[i + 1] > nums[i];
			}
			else
			{
				if (increasing && nums[i - 1] >= nums[i] || ((abs(nums[i - 1] - nums[i]) != 1) && (abs(nums[i - 1] - nums[i] != 3))))
				{
					valid = false;
					break;
				}
			}
		}
		p1 += valid;
		if (valid)
			cout << nums << endl;
	}

	auto done = chrono::steady_clock::now();
	cout << "[P1] " << p1 << "\n[P2] " << p2 << endl;
	return done;
}