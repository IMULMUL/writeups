impl Solution {
    pub fn trailing_zeroes(n: i32) -> i32 {
        let mut i = n;
        let mut count = 0;
        
        while i > 0 {
            count += i / 5;
            i = i / 5;
        }
        
        return count;
    }
}
