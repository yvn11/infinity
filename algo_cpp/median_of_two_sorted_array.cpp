class Solution {
public:
    double findMedianSortedArrays(vector<int>& nums1, vector<int>& nums2) {
        vector<int> nums;
        int i = 0, j = 0;
        
        for (; i < nums1.size() && j < nums2.size();) {
            if (nums1[i] < nums2[j]) {
                nums.push_back(nums1[i]);
                i++;
            } else {
                nums.push_back(nums2[j]);
                j++;
            }
        }
        
        if (i < nums1.size()) {
            for (; i < nums1.size(); ++i) {
                nums.push_back(nums1[i]);
            }
        }
        
        if (j < nums2.size()) {
            for (; j < nums2.size(); ++j) {
                nums.push_back(nums2[j]);
            }
        }
        
        int mid = nums.size()/2;
        return nums.size()%2!=0 ? nums[mid] : float(nums[mid-1]+nums[mid])/2;
    }
};
