//lower(x): primer elemento mayor o igual a x
//upper(x): primer elemento mayor a x
int lowerBound(vi &nums, int a) {
    int l = 0, r = nums.size() - 1;
    while(l <= r) {
        int m = ((r - l) >> 1) + l;
	//  if(nums[m] == a) return m;//binary
		nums[m] < a ? l = m + 1 : r = m - 1;  //lower & binary
	//  nums[m] <= a ? l = m + 1 : r = m - 1; //upper
    }
    return l;//return -1; //binary
}