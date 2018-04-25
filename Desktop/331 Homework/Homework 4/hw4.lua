function pow(a,b)
  c = 1
  for i=1, b do
    c = c*a
  end
  return c
end

function sigma(array)
  total = 0;
  for slot, value in pairs(array) do
    total = total + value
  end
  return total
end

function longestString(a, b, c, d)
  longest=a
  arrayLong = {[1]=a, [2]=b, [3]=c, [4]=d}
  for slot, value in pairs(arrayLong) do
    longest = (a > b) and a or b
  end
  return longest
end

function quadratic(a,b,c)
  xPlus = (-b+math.sqrt((b*b)-(4*a*c)))/(2*a)
  xMinus = (-b-math.sqrt((b*b)-(4*a*c)))/(2*a)
  return xPlus, xMinus
end

function turingSort()
  file = io.open("turing.tsv")
  award_winners = {}
  for line in file:lines() do
    v = string.gmatch( line, "[^\t]+" )
    local award_date = v()
    local award_name = v()
    local research_inst = v()
    local research = v()
    table.insert(award_winners, {award_date, award_name, research_inst, research})
  end
  
  print("-----------Sorted By Area of Research-----------\n")
  table.sort(award_winners, function(a,b) return string.sub(a[4], 1) < string.sub(b[4], 1) end)
  for key,slot in pairs(award_winners) do
    print(slot[1].."  -  "..slot[2].."  -  "..slot[3].."  -  "..slot[4].."\n")
  end
  print("\n\n")
  
  print("-----------Sorted By Institution of Winner-----------\n")
  table.sort(award_winners, function(a,b) return string.sub(string.lower(a[3]), 1) < string.sub(string.lower(b[3]), 1) end)
  for key,slot in pairs(award_winners) do
    print(slot[1].."  -  "..slot[2].."  -  "..slot[3].."  -  "..slot[4].."\n")
  end
  
end
