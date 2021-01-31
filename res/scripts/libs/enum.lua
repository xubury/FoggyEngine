-- assumes the tbl is an array, i.e., all the keys are
-- successive integers - otherwise #tbl will fail
function enum(tbl)
    local length = #tbl
    for i = 1, length do
        local v = tbl[i]
        tbl[v] = i
        tbl[i] = nil
    end
    return tbl
end