class Solution:
    def countLargestGroup(self, n: int) -> int:
        # 初始化计数器（最大数位和为36：9999->9+9+9+9=36）
        count = [0] * 37
        
        # 统计每个数位和对应的数字数量
        for num in range(1, n + 1):
            digit_sum = 0
            current = num
            while current:
                digit_sum += current % 10  # 获取最后一位并累加
                current //= 10            # 移除最后一位
            count[digit_sum] += 1
        
        # 找出最大组的大小
        max_size = max(count)
        
        # 统计达到最大大小的组的数量
        result = 0
        for size in count:
            if size == max_size:
                result += 1
        
        return result