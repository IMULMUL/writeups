# @param {Integer} n
# @return {Integer[]}
def sum_zero(n)
    arr = []
    for i in (1..(n/2))
        arr.push(i)
        arr.push(0-i)
    end
    
    if n % 2 == 1
        arr.push(0)
    end
    
    return arr
end
