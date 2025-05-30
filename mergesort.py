лfrom heapq import merge

def merge_sort2(m):
    """Sort list, using two part merge sort"""
    if len(m) <= 1:
        return m

    middle = len(m) // 2
    left = m[:middle]
    right = m[middle:]

    right = merge_sort2(right)
    left = merge_sort2(left)

    return list(merge(right, left))

