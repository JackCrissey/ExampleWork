io.input("game.txt")
numberOfGamesPlayed = 0
numGamesWonPlayer1 = 0
numGamesWonPlayer2 = 0
numMatchesFound1 = 0
numMatchesFound2 = 0
gameNumber = 0
mostGuesses = {0, 0}
leastGuesses = {0, 0}
numGuesses=0
totalGuesses = 0
currStreak = false
streakCounter = 0
longestStreak = 0
while true do
    line = io.read()
    if line == nil then break end 
    if(string.find(line, "Congrats") ~= null and currStreak == false) then
      currStreak = true;
      streakCounter = 1
    end
    if(string.find(line, "Congrats") ~= null and currStreak == true) then
      streakCounter = streakCounter + 1
    end
    if(string.find(line, "Miss") ~= null and currStreak == true) then
      if(longestStreak < streakCounter) then
        longestStreak = streakCounter
      end
      streakCounter = 0
      currStreak = false
    end
    if(string.find(line, "Player") ~= null) then
      
      numberOfGamesPlayed = numberOfGamesPlayed + 1
      i, j = string.find(line, "Player")
      i = j + 2
      j = i 
      player = tonumber(string.sub(line, i, j))
      if(player == 1) then
        numGamesWonPlayer1 = numGamesWonPlayer1 + 1
      	numMatches = tonumber(string.sub(line, 20, 21))
      	numMatchesFound1 = numMatchesFound1 + numMatches
      	numMatchesFound2 = numMatchesFound2 + (26 - numMatches)
      end
      if(player == 2) then
        numGamesWonPlayer2 = numGamesWonPlayer2 + 1
        numMatches = tonumber(string.sub(line, 20, 21))
      	numMatchesFound2 = numMatchesFound2 + numMatches
      	numMatchesFound1 = numMatchesFound1 + (26 - numMatches)
      end
      if(numGuesses > mostGuesses[1]) then
        mostGuesses[0] = numberOfGamesPlayed
        mostGuesses[1] = numGuesses
      end
      if(numGuesses < leastGuesses[1] or leastGuesses[1] == 0) then
        leastGuesses[0] = numberOfGamesPlayed
        leastGuesses[1] = numGuesses
      end
      totalGuesses = totalGuesses + numGuesses
      numGuesses=0
    end
    if(string.find(line, "Congrats") ~= null or string.find(line, "Miss") ~= null) then
      numGuesses = numGuesses +1
    end
end

print("The total number of games was "..numberOfGamesPlayed)
print("The average number of matches found by Player 1 was"..(numMatchesFound1/numberOfGamesPlayed))
print("The average number of matches found by Player 2 was"..(numMatchesFound2/numberOfGamesPlayed))
print("Game that took the most guesses Game #"..mostGuesses[0].." took "..mostGuesses[1].." guesses")
print("Game that took the least guesses Game #"..leastGuesses[0].." took "..leastGuesses[1].." guesses")
print("The average number of guesses per game was "..(totalGuesses/numberOfGamesPlayed))
print("The longest streak was "..longestStreak)
if(numGamesWonPlayer1 > numGamesWonPlayer2) then
  print("The player that won the most was player 1")
end
if(numGamesWonPlayer2 > numGamesWonPlayer1) then
  print("The player that won the most was player 2")
end
if(numGamesWonPlayer1 == numGamesWonPlayer2) then
  print("Both players won the same amount of games")
end

