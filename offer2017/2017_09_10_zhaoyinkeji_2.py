class Solution(object):
    def addBoldTag(self, s, dict):
        mask = [0 for i in range(len(s))]
        for patt in dict:
            begin = 0
            while True:
                index = s.find(patt, begin)
                if index == -1:
                    break
                else:
                    for i in range(len(patt)):
                        mask[index+i] = 1
                begin = index + 1
        res = ""
        for i in range(len(s)):
            if i == 0 and mask[i] == 1:
                res += "<b>"
                res += s[i]
            elif i == len(s)-1:
                if mask[i] == 1:
                    res += s[i]
                    res += "</b>"
                else:
                    res += s[i]
            elif mask[i] == 0 and mask[i+1] == 1:
                res += s[i]
                res += "<b>"
            elif mask[i] == 1 and mask[i+1] == 0:
                res += s[i]
                res += "</b>"
            else:
                res += s[i]
        return res
            

print Solution().addBoldTag("aaabbcc",["aaa","aab","bc"])
print Solution().addBoldTag("abcxyz123",["abc","123"])
