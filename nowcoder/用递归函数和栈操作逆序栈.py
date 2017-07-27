# -*- coding:utf-8 -*-

class ReverseStack:
    def reverseStackRecursively(self, stack, top):
        # write code here
        reverse = stack
        self.reverseStackRecursively_R(reverse, 0, top-1)
        return reverse

    def reverseStackRecursively_R(self, arr, left, right):
        if left >= right:
            return
        temp = arr[left]
        arr[left] = arr[right]
        arr[right] = temp
        self.reverseStackRecursively_R(arr,left+1,right-1)
        
print ReverseStack().reverseStackRecursively([1,2,3,4,5],5)
ReverseStack()
