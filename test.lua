function func(vec)
  for k, v in pairs(vec) do print(k,v) end
  return 0.0
end

function plot(a, b)
  t = {}
  for i=a,b,0.01 do
    table.insert(t, math.sin(i))
  end
  return t
end

function age()
  t = {arden=20,sean=20,anna=21,amber=22}
  return t
end
