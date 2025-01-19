class Solution {
public:
	int countMatchingSubarrays(vector<int>& nums, vector<int>& pattern) {
		constexpr int b = 31;
		int n = nums.size(), m = pattern.size();
		ll hp1 = 0, hp2 = 0;
		ll pow1 = 1, pow2 = 1;
		for (int i = 1; i <= m; ++i) {
			hp1 = mod(hp1 + mod(pow1 * (pattern[i-1] + 1), MDL1), MDL1);
			hp2 = mod(hp2 + mod(pow2 * (pattern[i-1] + 1), MDL2), MDL2);
			pow1 = mod(pow1 * b, MDL1);
			pow2 = mod(pow2 * b, MDL2);
		}
		vector<ll> hn1(n + 1), hn2(n + 1);
		pow1 = 1, pow2 = 1;
		for (int i = 2; i <= n; ++i) {
			int p;
			if (nums[i-1] > nums[i-2]) p = 1;
			else if (nums[i-1] == nums[i-2]) p = 0;
			else p = -1;
			hn1[i] = mod(hn1[i-1] + mod(pow1 * (p + 1), MDL1), MDL1);
			hn2[i] = mod(hn2[i-1] + mod(pow2 * (p + 1), MDL2), MDL2);
			pow1 = mod(pow1 * b, MDL1);
			pow2 = mod(pow2 * b, MDL2);
		}
		int res = 0;
		pow1 = 1, pow2 = 1;
		for (int i = 1; i + m <= n; ++i) {
			if (mod(hp1 * pow1, MDL1) == mod(hn1[i+m] - hn1[i], MDL1) &&
				mod(hp2 * pow2, MDL2) == mod(hn2[i+m] - hn2[i], MDL2)) {
				res += 1;
			}
			pow1 = mod(pow1 * b, MDL1);
			pow2 = mod(pow2 * b, MDL2);
		}
		return res;
	}
};

作者：subcrip
链接：https://leetcode.cn/problems/number-of-subarrays-that-match-a-pattern-ii/solutions/2637701/zi-fu-chuan-ha-xi-by-subcrip-r3z4/
来源：力扣（LeetCode）
著作权归作者所有。商业转载请联系作者获得授权，非商业转载请注明出处。
