for i = 1, 10 do
    print("hello", i)
    coroutine.yield()
end