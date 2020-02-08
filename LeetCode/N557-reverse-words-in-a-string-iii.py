class Solution:
    def reverseWords(self, s: str) -> str:
        arr = s.split(" ")
        res = []
        for i in arr:
            res.append(i[::-1])
            
        return " ".join(res)
