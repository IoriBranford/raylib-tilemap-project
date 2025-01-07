print("hello")
local t = task.run(function(n, t)
    for i = 1, n do
        for _ = 1, t do
            coroutine.yield()
        end
        print("hello", i)
    end
    return "goodbye"
end, 0, 10, 6)
while not t.done do
    coroutine.yield()
end
return t:results()