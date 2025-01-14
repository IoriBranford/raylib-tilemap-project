return function(n, intv)
    n = n or 1
    intv = intv or 1

    print("hello")
    local t = task.run(function(n, intv)
        for i = 1, n do
            for _ = 1, intv do
                io.write('.')
                coroutine.yield()
            end
            print("hello", i)
        end
        return "goodbye"
    end, 0, n, intv)
    while not t.done do
        coroutine.yield()
    end
    return t:results()
end